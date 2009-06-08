/*-
 * Copyright (C) 2008 Erik Larsson
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA
 */

#include "jfuse.h"
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <jni.h>

/* For getcwd... */
#include <unistd.h>
#include <sys/param.h>

#define PROGRAM_NAME "rarfs_fuse"

#define FALSE 0
#define TRUE 1
#define USER_CLASSPATH "./java-src:./lib/rarx.jar"
#define HELLO_ENABLED FALSE /* true: the old hello world filesystem is concatenated into the fs tree */
#define USE_DIRECT_BUFFER TRUE /* true: use java.nio.ByteBuffer to directly read into native-code memory locations */

#define LOG_ENABLE_DEBUG TRUE
#if LOG_ENABLE_DEBUG
#define LOG_DEBUG(...) do { FILE *logFile = stderr; fprintf(logFile, "[" PROGRAM_NAME "] DEBUG: "); fprintf(logFile, __VA_ARGS__); fprintf(logFile, "\n"); fflush(logFile); } while(0)
#else
#define LOG_DEBUG(...)
#endif

#define LOG_ENABLE_ERROR TRUE
#if LOG_ENABLE_ERROR
#define LOG_ERROR(...) do { FILE *logFile = stderr; fprintf(logFile, "[" PROGRAM_NAME "] ERROR: "); fprintf(logFile, __VA_ARGS__); fprintf(logFile, "\n"); fflush(logFile); } while(0)
#else
#define LOG_ERROR(...)
#endif

static const char *hello_str = "Hello World!\n";
static const char *hello_path = "/hello";
static JavaVM *staticJvm = NULL;
static char *rarFilename = NULL;
static char workingDirectory[MAXPATHLEN]; // <- a weakness. we should find a way to get cwd without the MAXPATHLEN limitation


static void printProperty(const char* propertyName, JNIEnv *env, jclass cls, jmethodID mid) {
  jstring userdotdir = (*env)->NewStringUTF(env, propertyName);
  jstring userdir = (*env)->CallStaticObjectMethod(env, cls, mid, userdotdir);
  const char *chars = (*env)->GetStringUTFChars(env, userdir, NULL);
  LOG_DEBUG("  - %s = \"%s\"", propertyName, (char*)chars);
  (*env)->ReleaseStringUTFChars(env, userdir, chars);
}

static void printJVMInfo(JavaVM *jvm, JNIEnv *env) {
/*   FILE *testFile = fopen("./printjvminfo_created_this_file", "w"); */
/*   fprintf(testFile, "hej"); */
/*   fclose(testFile); */

  LOG_DEBUG("  - Find class java.lang.System...");
  jclass cls = (*env)->FindClass(env, "java/lang/System");
  LOG_DEBUG("  - Get static method getProperty...");
  jmethodID mid = (*env)->GetStaticMethodID(env, cls, "getProperty", "(Ljava/lang/String;)Ljava/lang/String;");
  
  printProperty("user.name", env, cls, mid);
  printProperty("user.home", env, cls, mid);
  printProperty("user.dir", env, cls, mid);
  printProperty("java.class.path", env, cls, mid);
}

static int createJavaVM() {
  JNIEnv *env;
  JavaVM *jvm;
  jint res;
  
#ifdef JNI_VERSION_1_2
  JavaVMInitArgs vm_args;
  JavaVMOption options[1];
  options[0].optionString =
    "-Djava.class.path=" USER_CLASSPATH;
  vm_args.version = 0x00010002;
  vm_args.options = options;
  vm_args.nOptions = 1;
  vm_args.ignoreUnrecognized = JNI_TRUE;
  /* Create the Java VM */
  res = JNI_CreateJavaVM(&jvm, (void**)&env, &vm_args);
#else
  JDK1_1InitArgs vm_args;
  char classpath[1024];
  vm_args.version = 0x00010001;
  JNI_GetDefaultJavaVMInitArgs(&vm_args);
  /* Append USER_CLASSPATH to the default system class path */
  sprintf(classpath, "%s%c%s",
	  vm_args.classpath, PATH_SEPARATOR, USER_CLASSPATH);
  vm_args.classpath = classpath;
  /* Create the Java VM */
  res = JNI_CreateJavaVM(&jvm, &env, &vm_args);
#endif /* JNI_VERSION_1_2 */
  
  if(res == 0)
    staticJvm = jvm;
  return res;
}

/* Creates a Java VM and runs the static method FuseModule.init. If all goes well, the function
   returns 0. If the VM could not be started, it returns -2. If the class FuseModule could not be
   found, or the method can't be called it returns -1. */
static int init() {
  //FILE *debug = debugFile;
  LOG_DEBUG("  - Trying to get jvm...");
  chdir(workingDirectory); // Working directory gets set to "/" in the new process. no good. I HOPE this won't affect the rest of the operation of fuse... I guess I'll notice.
  int cvmres = createJavaVM();
  if(cvmres < 0) {
    LOG_DEBUG("    - Could not create JVM! Exit code: %d", cvmres);
    //filler(buf, "ERROR_could_not_start_JVM", NULL, 0);
    return -2;
  }
  else {
    LOG_DEBUG("    - JVM created! Exit code: %d. Now trying to initialize FuseModule...", cvmres);
    JNIEnv *env;
    (*staticJvm)->AttachCurrentThread(staticJvm, (void **)&env, NULL);
    printJVMInfo(staticJvm, env);
    LOG_DEBUG("    - Now trying to initialize FuseModule for real...");
    jclass cls = (*env)->FindClass(env, "FuseModule");//org/apache/crimson/jaxp/SAXParserImpl");
    if ((*env)->ExceptionOccurred(env)) {
      (*env)->ExceptionDescribe(env);
      LOG_ERROR("Exception occurred!");
    }
    
    if(cls != NULL) {
      LOG_DEBUG("    - Class FuseModule found.");
      jmethodID mid = (*env)->GetStaticMethodID(env, cls, "init", "(Ljava/lang/String;)I");
      if(mid != NULL) {
	LOG_DEBUG("    - Method FuseModule.init found.");
	jstring jpath = (*env)->NewStringUTF(env, rarFilename);
	if(jpath != NULL) {
	  LOG_DEBUG("    - String converted. Now calling CallStaticIntMethod.");
	  jint status = (*env)->CallStaticIntMethod(env, cls, mid, jpath);
	  if(status == 0) {
	    LOG_DEBUG("    - Success!");
	    return 0;
	  }
	  else if(status == -1) {
	    LOG_ERROR("Could not open RAR... :(");
	  }
	}
      }
    }
    else {
      LOG_ERROR("Could not find class FuseModule!");
    }
  }
  return -1;
}

static void mergeStat(JNIEnv *env, jobject statObject, struct stat *target) {
  LOG_DEBUG("    - Getting class Stat");
  jclass statClass = (*env)->FindClass(env, "Stat");
  LOG_DEBUG("      - statClass: %X", (int)statClass);
  LOG_DEBUG("    - Getting field id for st_mode");
  jfieldID modeFieldID = (*env)->GetFieldID(env, statClass, "st_mode", "S");
  LOG_DEBUG("    - Getting field id for st_nlink");
  jfieldID nlinkFieldID = (*env)->GetFieldID(env, statClass, "st_nlink", "B");
  LOG_DEBUG("    - Getting field id for st_size");
  jfieldID sizeFieldID = (*env)->GetFieldID(env, statClass, "st_size", "J");
  
  jshort modeValue = (*env)->GetShortField(env, statObject, modeFieldID);
  jbyte nlinkValue = (*env)->GetByteField(env, statObject, nlinkFieldID);
  jlong sizeValue = (*env)->GetLongField(env, statObject, sizeFieldID);

  target->st_mode = modeValue;
  target->st_nlink = nlinkValue;
  target->st_size = sizeValue;
  
  LOG_DEBUG("    - st_mode set to: %d", target->st_mode);
  LOG_DEBUG("    - st_nlink set to: %d", target->st_nlink);
  LOG_DEBUG("    - st_size set to: %lld", target->st_size);

  // Now set time accordingly
  jfieldID cfid;
  cfid = (*env)->GetFieldID(env, statClass, "atime_tv_sec", "J"); target->st_atimespec.tv_sec = (*env)->GetLongField(env, statObject, cfid);
  cfid = (*env)->GetFieldID(env, statClass, "mtime_tv_sec", "J"); target->st_mtimespec.tv_sec = (*env)->GetLongField(env, statObject, cfid);
  cfid = (*env)->GetFieldID(env, statClass, "ctime_tv_sec", "J"); target->st_ctimespec.tv_sec = (*env)->GetLongField(env, statObject, cfid);
  target->st_atimespec.tv_nsec = 0;
  target->st_mtimespec.tv_nsec = 0;
  target->st_ctimespec.tv_nsec = 0;
  
  LOG_DEBUG("    - st_atimespec.tv_sec set to: %ld", target->st_atimespec.tv_sec);
  LOG_DEBUG("    - st_mtimespec.tv_sec set to: %ld", target->st_mtimespec.tv_sec);
  LOG_DEBUG("    - st_ctimespec.tv_sec set to: %ld", target->st_ctimespec.tv_sec);
}

int rarfs_getattr(const char *path, struct stat *stbuf)
{
  LOG_DEBUG("rarfs_getattr(\"%s\", ...);", path);
  int res = 0;
  
  memset(stbuf, 0, sizeof(struct stat));
  if(strcmp(path, "/") == 0) {
    stbuf->st_mode = S_IFDIR | 0755;
    stbuf->st_nlink = 2;
  }
  else if(HELLO_ENABLED && strcmp(path, hello_path) == 0) {
    stbuf->st_mode = S_IFREG | 0444;
    stbuf->st_nlink = 1;
    stbuf->st_size = strlen(hello_str);
  }
  else {
    // Query FuseModule for the attributes
    if(staticJvm == NULL && init() == -1) {
      LOG_ERROR("rarfs_getattr could not initialize jvm");
      staticJvm = NULL;
    }
    
    LOG_DEBUG("  - Trying to attach thread.");
    JNIEnv *env;
    (*staticJvm)->AttachCurrentThread(staticJvm, (void **)&env, NULL);
    LOG_DEBUG("  - Trying to get FuseModule class.");
    jclass cls = (*env)->FindClass(env, "FuseModule");
    if(env != NULL && cls != NULL) {
      LOG_DEBUG("  - env and cls aquired. Trying to get static method from env");
      jmethodID mid = (*env)->GetStaticMethodID(env, cls, "rarfsGetattr", "(Ljava/lang/String;LStat;)I");
      
      // Allocate new String containing the requested path
      LOG_DEBUG("  - Converting native string to Java String");
      jstring jpath = (*env)->NewStringUTF(env, path);
      LOG_DEBUG("    - jpath: %X", (int)jpath);

      // Allocate new Stat object
      LOG_DEBUG("  - Creating input Stat object");
      jclass statClass = (*env)->FindClass(env, "Stat");
      LOG_DEBUG("    - statClass: %X", (int)statClass);
      jmethodID statConstructor = (*env)->GetMethodID(env, statClass, "<init>", "()V");
      LOG_DEBUG("    - statConstructor: %X", (int)statConstructor);
      jobject statObject = (*env)->NewObject(env, statClass, statConstructor);
      LOG_DEBUG("    - statObject: %X", (int)statObject);
      
      if(mid != NULL && jpath != NULL && statObject != NULL) {
	LOG_DEBUG("  - Got prerequisites. Trying to call method \"public static Stat FuseModule.rarfsGetattr(String, Stat)\"...");
	jint returnValue = (*env)->CallStaticIntMethod(env, cls, mid, jpath, statObject);
	if(returnValue == 0) {
	  LOG_DEBUG("  - Method returned correctly, calling mergeStat");
	  mergeStat(env, statObject, stbuf);
	  LOG_DEBUG("    - mergeStat completed.");
	}
	else {
	  LOG_ERROR("returnValue=%d", (int)returnValue);
	  res = -ENOENT;
	}
      }
      else {
	LOG_ERROR("mid==%X jpath==%X statObject==%X", (int)mid, (int)jpath, (int)statObject);
	res = -ENOENT;
      }
      
      // Deallocate the allocated objects
      if(jpath != NULL)
	(*env)->DeleteLocalRef(env, jpath);
      if(statObject != NULL)
	(*env)->DeleteLocalRef(env, statObject);
    }
    else {
      LOG_ERROR("env==%X cls==%X", (int)env, (int)cls);
      res = -ENOENT;
    }
  }
  
  
  return res;
}

int rarfs_readdir(const char *path, void *buf, fuse_fill_dir_t filler,
		  off_t offset, struct fuse_file_info *fi)
{
  /* Note 070221:
     What information do we need from the JVM? Two approaches:
     1. We just send everything on to the JVM, and handle everything there. The C code will
        merely act as a translator from C types to Java types.
     2. We simply request the information we need from the JVM and handle the information in
        C code.
     So which one is the best?
     If we do the data processing in Java, there's less probability of error, and data
     manipulation is easier (especially string operations). But how can we translate for
     instance the fuse_fill_dir_t, which is a function pointer, into Java...? That means we
     need JNI code for that as well.
     I still feel better about doing it that way....
     
     Note 070223:
     After some coding, I realize that I can't use the JVM used to start the program in the
     actual fuse module, as fuse terminates the startup process after calling fuse_main...
     thus also terminating the JVM. So the JVM will be started from the new process which has
     the purpose of serving the filesystem data.
  */
  
  LOG_DEBUG("int rarfs_readdir(...): entering...");
/*   (void) offset; */
/*   (void) fi; */
  
/*   if(strcmp(path, "/") != 0) */
/*     return -ENOENT; */
  
  filler(buf, ".", NULL, 0);
  filler(buf, "..", NULL, 0);
  
  /* Now request the file list from the JVM. */
  if(staticJvm == NULL && init() == -1) {
    filler(buf, "could_not_initialize_jvm", NULL, 0);
    staticJvm = NULL;
  }
  else {
    LOG_DEBUG("  - Trying to attach thread (jvm: %X).", (int)staticJvm);
    JNIEnv *env;
    (*staticJvm)->AttachCurrentThread(staticJvm, (void **)&env, NULL);
    LOG_DEBUG("  - Trying to get FuseModule class.");
    jclass cls = (*env)->FindClass(env, "FuseModule");
    if(env != NULL && cls != NULL) {
      LOG_DEBUG("  - env and cls aquired. Trying to get static method from env");
      jmethodID mid = (*env)->GetStaticMethodID(env, cls, "rarfsReaddir", "(Ljava/lang/String;)[Ljava/lang/String;");
      
      // Allocate new String
      LOG_DEBUG("  - Converting native string to Java String");
      jstring jpath = (*env)->NewStringUTF(env, path);
      
      if(mid != NULL && jpath != NULL) {
	LOG_DEBUG("  - Got Java String. Trying to call static object method.");
	jobjectArray res = (*env)->CallStaticObjectMethod(env, cls, mid, jpath);
	LOG_DEBUG("  - Result from method call:");
	jint argc = (*env)->GetArrayLength(env, res);
	int i;
	for(i = 0; i < argc; ++i) {
	  jstring str = (*env)->GetObjectArrayElement(env, res, i);
	  const char *chars = (*env)->GetStringUTFChars(env, str, NULL);
	  LOG_DEBUG("    %d: %s", i, chars);
	  filler(buf, chars+1, NULL, 0);
	  (*env)->ReleaseStringUTFChars(env, str, chars);
	}
      }

      // Deallocate the allocated objects
      if(jpath != NULL)
	(*env)->DeleteLocalRef(env, jpath);
    }
  }
  
  if(HELLO_ENABLED)
    filler(buf, hello_path + 1, NULL, 0);
  
  return 0;
}

int rarfs_open(const char *path, struct fuse_file_info *fi)
{
  LOG_DEBUG("rarfs_open(\"%s\", ...);", path);
  if(!HELLO_ENABLED || strcmp(path, hello_path) != 0) {
    // Query FuseModule for the attributes
    if(staticJvm == NULL && init() == -1) {
      LOG_ERROR("rarfs_open could not initialize jvm!");
      staticJvm = NULL;
    }
    
    int returnCode = 0;
    
    LOG_DEBUG("  - Trying to attach thread.");
    JNIEnv *env;
    (*staticJvm)->AttachCurrentThread(staticJvm, (void **)&env, NULL);
    LOG_DEBUG("  - Trying to get FuseModule class.");
    jclass cls = (*env)->FindClass(env, "FuseModule");
    if(env != NULL && cls != NULL) {
      LOG_DEBUG("  - env and cls aquired. Trying to get static method from env");
      jmethodID mid = (*env)->GetStaticMethodID(env, cls, "rarfsOpen", "(Ljava/lang/String;)I");
      LOG_DEBUG("  - Converting native string to Java String");
      jstring jpath = (*env)->NewStringUTF(env, path);
      if(mid != NULL && jpath != NULL) {
	LOG_DEBUG("  - Got Java String. Trying to call static open method.");
	jint exitcode = (*env)->CallStaticIntMethod(env, cls, mid, jpath);
	if(exitcode != 0)
	  returnCode = -ENOENT;
	else
	  LOG_DEBUG("  - Successfully opened!!");
      }
      else
	returnCode = -ENOENT;
      
      // Deallocate the allocated objects
      if(jpath != NULL)
	(*env)->DeleteLocalRef(env, jpath);
    }
    else
      returnCode = -ENOENT;
      
    return returnCode;
  }
  else if(HELLO_ENABLED) {
    if((fi->flags & 3) != O_RDONLY)
      return -EACCES;
    
    return 0;
  }
  else
    return -ENOENT;
}

int rarfs_read(const char *path, char *buf, size_t size, off_t offset,
	       struct fuse_file_info *fi)
{
  LOG_DEBUG("rarfs_read(\"%s\", ..., %lu, %llu, ...);", path, size, offset);
  if(!HELLO_ENABLED || strcmp(path, hello_path) != 0) {
    if(staticJvm == NULL && init() == -1) {
      LOG_ERROR("- rarfs_read could not initialize jvm!");
      staticJvm = NULL;
    }
    int returnCode = -ENOENT;
    
    LOG_DEBUG("  - Trying to attach thread.");
    JNIEnv *env;
    (*staticJvm)->AttachCurrentThread(staticJvm, (void **)&env, NULL);
    LOG_DEBUG("  - Trying to get FuseModule class.");
    jclass cls = (*env)->FindClass(env, "FuseModule");
    if(env != NULL && cls != NULL) {
      LOG_DEBUG("  - Converting native string to Java String");
      jstring jpath = (*env)->NewStringUTF(env, path);
      if(USE_DIRECT_BUFFER) {
	LOG_DEBUG("  - Trying to get static method from env");
	jmethodID mid = (*env)->GetStaticMethodID(env, cls, "rarfsRead", "(Ljava/lang/String;Ljava/nio/ByteBuffer;JI)I");
	LOG_DEBUG("  - Mapping buf to a direct byte buffer");
	jobject directBuffer = (*env)->NewDirectByteBuffer(env, buf, size);
	if(mid != NULL && jpath != NULL && directBuffer != NULL) {
	  LOG_DEBUG("  - Trying to call static rarfsRead method.");
	  jint exitcode = (*env)->CallStaticIntMethod(env, cls, mid, jpath, directBuffer, offset, size);
	  if(exitcode < 0)
	    returnCode = -ENOENT;
	  else {
	    LOG_DEBUG("  - Read %ld bytes into buf.", exitcode); // I have no idea why jint needs to be casted. should be 32-bit signed.
	    returnCode = exitcode;
	  }
	}
	else
	  returnCode = -ENOENT;
	
	if(directBuffer != NULL)
	  (*env)->DeleteLocalRef(env, directBuffer);
      }
      else {
	LOG_DEBUG("  - Trying to get static method from env");
	jmethodID mid = (*env)->GetStaticMethodID(env, cls, "rarfsRead", "(Ljava/lang/String;[BJI)I");
	LOG_DEBUG("  - Creating new byte array.");
	jbyteArray cache = (*env)->NewByteArray(env, size);
	if(mid != NULL && jpath != NULL && cache != NULL) {
	  LOG_DEBUG("  - Got Java String. Trying to call static read method.");
	  jint exitcode = (*env)->CallStaticIntMethod(env, cls, mid, jpath, cache, offset, size);
	  if(exitcode < 0)
	    returnCode = -ENOENT;
	  else {
	    (*env)->GetByteArrayRegion(env, cache, 0, exitcode, (jbyte*)buf);
	    LOG_DEBUG("  - Read %ld bytes into buf.", exitcode);
	    returnCode = exitcode;
	  }
	}
	else
	  returnCode = -ENOENT;
	
	if(cache != NULL)
	  (*env)->DeleteLocalRef(env, cache);
      }
      
      // Deallocate the allocated objects
      if(jpath != NULL)
	(*env)->DeleteLocalRef(env, jpath);
    }
    else
      returnCode = -ENOENT;

    return returnCode;
  }
  else if(HELLO_ENABLED) {
    size_t len;
    len = strlen(hello_str);
    if (offset < len) {
      if (offset + size > len)
	size = len - offset;
      memcpy(buf, hello_str + offset, size);
    } else
      size = 0;
    return size;
  }
  else return -ENOENT;
}

struct fuse_operations rarfs_oper = {
    .getattr	= rarfs_getattr,
    .readdir	= rarfs_readdir,
    .open	= rarfs_open,
    .read	= rarfs_read,
};

void printUsage(FILE *f, const char *launchCommand) {
  fprintf(f, "usage: %s <rarfile> <mountpoint> [<fuseoptions>]\n", launchCommand);
}

int rarfs_main(int argc, char *argv[])
{
  LOG_DEBUG("argc: %d", argc);
  int i;
  for(i = 0; i < argc; ++i)
    LOG_DEBUG("argv[%d]: %s", i, argv[i]);

  /** Validate argv. */
  if(argc < 3) {
    if(argc >= 1)
      printUsage(stderr, argv[0]);
    else
      fprintf(stderr, "SERIOUS ERROR: Didn't even get launch command line. WTF is wrong with your OS?");
    return -1;
  }

  rarFilename = argv[1];
  argv[1] = argv[0];
  return fuse_main(argc-1, argv+1, &rarfs_oper, NULL);
}

int main(int argc, char *argv[])
{
  if(getcwd(workingDirectory, MAXPATHLEN) == NULL) {
    fprintf(stderr, "Could not get working directory.");
    return -1;
  }
  else {
/*     if(DEBUGMODE) { */
    LOG_DEBUG("Info: cwd = \"%s\"", workingDirectory);
/*       debugFile = stderr;//fopen("debug_log.txt", "a"); */
/*     } */
/*     else */
/*       debugFile = fopen("/dev/null", "a"); */
    
    return rarfs_main(argc, argv);
  }
}
