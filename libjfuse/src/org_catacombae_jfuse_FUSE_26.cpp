/*-
 * jFUSE - FUSE bindings for Java
 * Copyright (C) 2008-2009  Erik Larsson <erik82@kth.se>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#define LOG_ENABLE_TRACE 0

#include "org_catacombae_jfuse_FUSE.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <jni.h>

#define FUSE_USE_VERSION 26
#include <fuse.h>
#if !defined(__NetBSD__)
#include <fuse_common.h>
#else

extern "C" {

#include <stddef.h>
#include <fuse_opt.h>

enum  {
  KEY_HELP,
  KEY_HELP_NOHEADER,
  KEY_VERSION,
};

struct helper_opts {
  int singlethread;
  int foreground;
  int nodefault_subtype;
  char *mountpoint;
};

#define FUSE_HELPER_OPT(t, p) { t, offsetof(struct helper_opts, p), 1 }

static const struct fuse_opt fuse_helper_opts[] = {
  FUSE_HELPER_OPT("-d",foreground),
  FUSE_HELPER_OPT("debug",foreground),
  FUSE_HELPER_OPT("-f",foreground),
  FUSE_HELPER_OPT("-s",singlethread),
  FUSE_HELPER_OPT("fsname=",nodefault_subtype),
  FUSE_HELPER_OPT("subtype=",nodefault_subtype),

  FUSE_OPT_KEY("-h",KEY_HELP),
  FUSE_OPT_KEY("--help",KEY_HELP),
  FUSE_OPT_KEY("-ho",KEY_HELP_NOHEADER),
  FUSE_OPT_KEY("-V",KEY_VERSION),
  FUSE_OPT_KEY("--version",KEY_VERSION),
  FUSE_OPT_KEY("-d",FUSE_OPT_KEY_KEEP),
  FUSE_OPT_KEY("debug",FUSE_OPT_KEY_KEEP),
  FUSE_OPT_KEY("fsname=",FUSE_OPT_KEY_KEEP),
  FUSE_OPT_KEY("subtype=",FUSE_OPT_KEY_KEEP),
  /*FUSE_OPT_END*/ { NULL, 0, 0 }
};

static void usage(const char *progname)
{
  fprintf(stderr,
	  "usage: %s mountpoint [options]\n\n", progname);
  fprintf(stderr,
	  "general options:\n"
	  "    -o opt,[opt...]        mount options\n"
	  "    -h   --help            print help\n"
	  "    -V   --version         print version\n"
	  "\n");
}

static void helper_help(void)
{
  fprintf(stderr,
	  "FUSE options:\n"
	  "    -d   -o debug          enable debug output (implies -f)\n"
	  "    -f                     foreground operation\n"
	  "    -s                     disable multi-threaded operation\n"
	  "\n"
	  );
}

static void helper_version(void)
{
  //fprintf(stderr, "FUSE library version: %s\n", PACKAGE_VERSION);
  // Apparently this is read from config.h... does librefuse have a gettable version?
  fprintf(stderr, "FUSE library version: ?\n");
}

static int fuse_helper_opt_proc(void *data, const char *arg, int key,
				struct fuse_args *outargs)
{
  struct helper_opts *hopts = data;

  switch (key) {
  case KEY_HELP:
    usage(outargs->argv[0]);
    /* fall through */

  case KEY_HELP_NOHEADER:
    helper_help();
    return fuse_opt_add_arg(outargs, "-h");

  case KEY_VERSION:
    helper_version();
    return 1;

  case FUSE_OPT_KEY_NONOPT:
    if (!hopts->mountpoint) {
      char mountpoint[PATH_MAX];
      if (realpath(arg, mountpoint) == NULL) {
	fprintf(stderr,
		"fuse: bad mount point `%s': %s\n",
		arg, strerror(errno));
	return -1;
      }
      return fuse_opt_add_opt(&hopts->mountpoint, mountpoint);
    } else {
      fprintf(stderr, "fuse: invalid argument `%s'\n", arg);
      return -1;
    }

  default:
    return 1;
  }
}

static int add_default_subtype(const char *progname, struct fuse_args *args)
{
  int res;
  char *subtype_opt;
  const char *basename = strrchr(progname, '/');
  if (basename == NULL)
    basename = progname;
  else if (basename[1] != '\0')
    basename++;

  subtype_opt = (char *) malloc(strlen(basename) + 64);
  if (subtype_opt == NULL) {
    fprintf(stderr, "fuse: memory allocation failed\n");
    return -1;
  }
  sprintf(subtype_opt, "-osubtype=%s", basename);
  res = fuse_opt_add_arg(args, subtype_opt);
  free(subtype_opt);
  return res;
}

static int fuse_parse_cmdline(struct fuse_args *args, char **mountpoint,
		       int *multithreaded, int *foreground)
{
  int res;
  struct helper_opts hopts;

  memset(&hopts, 0, sizeof(hopts));
  res = fuse_opt_parse(args, &hopts, fuse_helper_opts,
		       fuse_helper_opt_proc);
  if (res == -1)
    return -1;

  if (!hopts.nodefault_subtype) {
    res = add_default_subtype(args->argv[0], args);
    if (res == -1)
      goto err;
  }
  if (mountpoint)
    *mountpoint = hopts.mountpoint;
  else
    free(hopts.mountpoint);

  if (multithreaded)
    *multithreaded = !hopts.singlethread;
  if (foreground)
    *foreground = hopts.foreground;
  return 0;

 err:
  free(hopts.mountpoint);
  return -1;
}

}

#endif
#include <sys/mount.h>

#include "fuse26_module.h"
#include "macfuse20_module.h"
#include "CSLog.h"
#include "JavaSignatures.h"

#if defined(__sun__)
#define UNMOUNT_FORCE MS_FORCE
#else
#define UNMOUNT_FORCE MNT_FORCE
#endif

#define errorHandling(...) \
    do { \
        fprintf(stderr, "Panic!\n"); \
        char *ptr = NULL; \
        ptr[0] = '\0'; \
        exit(1); \
    } while(0)

static bool getCapability(JNIEnv *env, jclass capabilitiesClass,
        jobject capabilities, const char *name, jboolean *out) {
    jfieldID fid = env->GetFieldID(capabilitiesClass, name, "Z");
    if(fid == NULL) {
        CSLogError("Could not get capability field id: %s", name);
        return false;
    }
    else {
        *out = env->GetBooleanField(capabilities, fid);
        return true;
    }
}

static bool fillFUSE26Operations(JNIEnv *env, jobject capabilities,
        struct fuse_operations *ops) {
    CSLogTraceEnter("fillFUSE26Operations(%p, %p, %p)",
            env, capabilities, ops);

    jclass capabilitiesClass = env->GetObjectClass(capabilities);
    if(capabilitiesClass == NULL || env->ExceptionCheck() == JNI_TRUE) {
        CSLogError("Could not get FUSE 2.6 capabilities class!");
        return false;
    }
    else
        CSLogDebug("Got FUSE 2.6 capabilities class: %p", capabilitiesClass);

    memset(ops, 0, sizeof(struct fuse_operations));

#define AddOperationIfSupported2(a, b) \
    do { \
        jboolean value; \
        if(getCapability(env, capabilitiesClass, capabilities, #b, &value)) { \
            if(value == JNI_TRUE) { \
                ops->a = jfuse_##a; \
                CSLogDebug("Added capability " #b " -> " #a); \
            } \
        } \
        else \
            return false; \
    } while(0)

#define AddOperationIfSupported(a) AddOperationIfSupported2(a, a)

    //ops->getdir = jfuse_get

    AddOperationIfSupported(getattr);
    AddOperationIfSupported(readlink);
    AddOperationIfSupported(getdir);
    AddOperationIfSupported(mknod);
    AddOperationIfSupported(mkdir);
    AddOperationIfSupported(unlink);
    AddOperationIfSupported(rmdir);
    AddOperationIfSupported(symlink);
    AddOperationIfSupported(rename);
    AddOperationIfSupported(link);
    AddOperationIfSupported(chmod);
    AddOperationIfSupported(chown);
    AddOperationIfSupported(truncate);
    AddOperationIfSupported(utime);
    AddOperationIfSupported(open);
    AddOperationIfSupported(read);
    AddOperationIfSupported(write);
    AddOperationIfSupported(statfs);
    AddOperationIfSupported(flush);
    AddOperationIfSupported(release);
    AddOperationIfSupported(fsync);
    AddOperationIfSupported(setxattr);
    AddOperationIfSupported(getxattr);
    AddOperationIfSupported(listxattr);
    AddOperationIfSupported(removexattr);
    AddOperationIfSupported(opendir);
    AddOperationIfSupported(readdir);
    AddOperationIfSupported(releasedir);
    AddOperationIfSupported(fsyncdir);
    AddOperationIfSupported(init);
    AddOperationIfSupported(destroy);
    AddOperationIfSupported(access);
    AddOperationIfSupported(create);
    AddOperationIfSupported(ftruncate);
    AddOperationIfSupported(fgetattr);
    AddOperationIfSupported(lock);
    AddOperationIfSupported(utimens);
    AddOperationIfSupported(bmap);

#undef AddOperationIfSupported
#undef AddOperationIfSupported2

    CSLogTraceLeave("fillFUSE26Operations(%p, %p, %p): %d",
            env, capabilities, ops, true);
    
    return true;
}

#if defined(__APPLE__) || defined(__DARWIN__)
#if (__FreeBSD__ >= 10)
static bool fillMacFUSE20Operations(JNIEnv *env, jobject capabilities,
        struct fuse_operations *ops) {
#define _FNAME_ "fillMacFUSE20Operations"
    CSLogTraceEnter(_FNAME_ "(%p, %p, %p)", env, capabilities, ops);

    jclass capabilitiesClass = env->GetObjectClass(capabilities);
    if(capabilitiesClass == NULL || env->ExceptionCheck() == JNI_TRUE) {
        CSLogError("Could not get MacFUSE 2.0 capabilities class!");
        return false;
    }
    else
        CSLogDebug("Got MacFUSE 2.0 capabilities class: %p", capabilitiesClass);

#define AddOperationIfSupported2(a, b) \
    do { \
        jboolean value; \
        if(getCapability(env, capabilitiesClass, capabilities, #b, &value)) { \
            if(value == JNI_TRUE) { \
                ops->a = jfuse_##a; \
                CSLogDebug("Added capability " #b " -> " #a); \
            } \
        } \
        else \
            return false; \
    } while(0)

#define AddOperationIfSupported(a) AddOperationIfSupported2(a, a)

    AddOperationIfSupported(exchange);
    AddOperationIfSupported(getxtimes);
    AddOperationIfSupported(setbkuptime);
    AddOperationIfSupported(setcrtime);
    AddOperationIfSupported(setchgtime);
    AddOperationIfSupported(chflags);
    AddOperationIfSupported(setattr_x);
    AddOperationIfSupported(fsetattr_x);

#undef AddOperationIfSupported
#undef AddOperationIfSupported2

    CSLogTraceLeave(_FNAME_ "(%p, %p, %p, %p): %d",
            env, capabilitiesClass, capabilities, ops, true);
    return true;
#undef _FNAME_
}
#endif /* __FreeBSD__ >= 10 */
#endif /* defined(__APPLE__) || defined(__DARWIN__) */

static struct fuse_operations jfuse_operations;

/*
 * Class:     org_catacombae_jfuse_FUSE
 * Method:    mountNative26
 * Signature: (Lorg/catacombae/jfuse/FUSE26FileSystem;Ljava/lang/String;[Ljava/lang/String;Lorg/catacombae/jfuse/FUSE26Capabilities;Lorg/catacombae/jfuse/MacFUSE20Capabilities;)Z
 */
JNIEXPORT jboolean JNICALL Java_org_catacombae_jfuse_FUSE_mountNative26(
        JNIEnv *env, jclass cls, jobject fileSystem, jstring mountPoint,
        jobjectArray optionStrings, jobject fuseCapabilities,
        jobject macFuseCapabilities) {
#define _FNAME_ "Java_org_catacombae_jfuse_FUSE_mountNative26"
    CSLogTraceEnter(_FNAME_ "(%p, %p, %p, %p, %p, %p, %p)", env, cls,
            fileSystem, mountPoint, optionStrings, fuseCapabilities,
            macFuseCapabilities);

    jboolean res = JNI_FALSE;

    jFUSEContext *context = new jFUSEContext(env, fileSystem);

    if(!fillFUSE26Operations(env, fuseCapabilities, &jfuse_operations))
        CSPanicWithMessage("Could not fill FUSE 2.6 operations!");
    else
        CSLogDebug("Filled FUSE 2.6 operations.");

    if(jfuse_operations.init != NULL) {
        context->setInitEnabled(true);
    }

#if defined(__APPLE__) || defined(__DARWIN__)
#if (__FreeBSD__ >= 10)
    if(macFuseCapabilities != NULL) {
        if(!fillMacFUSE20Operations(env, macFuseCapabilities,
                &jfuse_operations))
            CSPanicWithMessage("Could not fill MacFUSE 2.0 operations!");
        else {
            CSLogDebug("Filled MacFUSE 2.0 operations.");
            if(jfuse_operations.getxtimes != NULL ||
                    jfuse_operations.setbkuptime != NULL ||
                    jfuse_operations.setcrtime != NULL ||
                    jfuse_operations.setchgtime != NULL) {
                CSLogDebug("Requesting enabling of xtimes.");
                context->setXtimesEnabled(true);
                if(jfuse_operations.init == NULL) {
                    CSLogDebug("Adding operation 'init' to fuse_operations for "
                            "support enabling of xtimes...");
                    jfuse_operations.init = jfuse_init;
                }
            }
        }
    }
    else
        CSLogDebug("No MacFUSE 2.0 operations to fill.");
#endif /*__FreeBSD__ >= 10 */
#endif /* defined(__APPLE__) || defined(__DARWIN__) */

    /* Read mountpoint. */
    jboolean isCopy;
    const char *utf8MountPoint = env->GetStringUTFChars(mountPoint, &isCopy);

    /* Read options. */
    struct fuse_args args = FUSE_ARGS_INIT(0, NULL);
    if(fuse_opt_add_arg(&args, utf8MountPoint) != 0)
        CSPanicWithMessage("fuse_opt_add_arg failed unexpectedly.");

    jsize optionStringsLength = env->GetArrayLength(optionStrings);
    CSLogDebug("Reading option strings (length=%ld)...", (long)optionStringsLength);
    for(int i = 0; i < optionStringsLength; ++i) {
        jstring cur = (jstring)env->GetObjectArrayElement(optionStrings, i);
        const char *utfChars = env->GetStringUTFChars(cur, NULL);

        CSLogDebug("  Adding option %d: \"%s\"", i, utfChars);
        int addArgRetval = fuse_opt_add_arg(&args, utfChars);
        if(addArgRetval != 0)
            CSPanicWithMessage("fuse_opt_add_arg failed unexpectedly with "
                    "retval=%d, errno: %d (%s)", addArgRetval, errno,
                    strerror(errno));

        env->ReleaseStringUTFChars(cur, utfChars);
        env->DeleteLocalRef(cur);
    }

    if(fuse_parse_cmdline(&args, NULL, NULL, NULL) != 0)
        CSLogError("fuse_parse_cmdline didn't return 0.");
    else {
        /*
         * FUSE regular mount procedure:
         *
         * Init:
         * - fuse_mount:
         *     (char *mountpoint, struct fuse_args *args)-> (struct fuse_chan*)
         * - fuse_new:
         *     (struct fuse_chan *ch, struct fuse_args *args,
         *      struct fuse_operations *op, size_t op_size, void *user_data)
         *     ->(struct fuse*)
         * Running:
         * - fuse_loop / fuse_loop_mt:
         *     (struct fuse*)->(int)
         *   Main loop, running until file system is unmounted.
         * Cleanup:
         * - fuse_unmount:
         *     (char *mountpoint, struct fuse_chan *ch)->(void)
         * - fuse_destroy:
         *     (struct fuse* f)->(void)
         *
         *
         * FUSE lowlevel mount procedure:
         *
         * Init:
         * - fuse_mount:
         *     (char *mountpoint, struct fuse_args *args)->(struct fuse_chan*)
         * - fuse_lowlevel_new:
         *     (struct fuse_args *args, struct fuse_lowlevel_ops *op,
         *       size_t op_size, void *userdata) -> (struct fuse_session*)
         * - fuse_session_add_chan:
         *     (struct fuse_session *se, struct fuse_chan *ch)->(void)
         * Running:
         * - fuse_session_loop / fuse_session_loop_mt:
         *     (struct fuse_session *se)->(int)
         * Cleanup:
         * - fuse_session_remove_chan:
         *     (struct fuse_chan *ch)->(void)
         * - fuse_session_destroy:
         *     (struct fuse_session *se)->(void)
         * - fuse_unmount:
         *     (char *mountpoint, struct fuse_chan *ch)->(void)
         */
        fuse_chan *chan = NULL;
        fuse *fh = NULL;

        CSLogDebug("Invoking fuse_mount...");
        chan = fuse_mount(utf8MountPoint, &args);
        CSLogDebug("   done. result=%p", chan);
        if(chan != NULL) {
            CSLogDebug("Invoking fuse_new...");
            fh = fuse_new(chan, &args, &jfuse_operations,
                    sizeof (jfuse_operations), context);
            CSLogDebug("   done. result=%p", fh);
            if(fh != NULL) {
#if defined(__NetBSD__)
	        int sighandler_res = 0;
#else
                int sighandler_res =
		  fuse_set_signal_handlers(fuse_get_session(fh));
#endif /* defined(__NetBSD__) */
		if(sighandler_res == 0) {
                    CSLogDebug("Invoking fuse_loop...");
                    int fuseLoopRetval = fuse_loop(fh);
                    CSLogDebug("  done. result=%d", fuseLoopRetval);
                    if(fuseLoopRetval != 0)
                        CSLogError("fuse_loop exited with a non-zero value: %d "
                            "(errno is %d (%s)", fuseLoopRetval, errno,
                            strerror(errno));
                    else
                        res = JNI_TRUE;

#if !defined(__NetBSD__)
                    fuse_remove_signal_handlers(fuse_get_session(fh));
#endif
                }
                else
                    CSLogError("Couldn't set signal handlers!");
            }
            else
                CSLogError("fuse_new exited with an error. (errno is %d (%s))",
                    errno, strerror(errno));
        }
        else
            CSLogError("fuse_mount exited with an error. (errno is %d (%s))",
                errno, strerror(errno));

        fuse_opt_free_args(&args);

        if(chan != NULL) {
            CSLogDebug("Unmounting \"%s\"... (chan=%p)", utf8MountPoint, chan);
            fuse_unmount(utf8MountPoint, chan);
        }
        if(fh != NULL) {
            CSLogDebug("Destroying fuse filehandle %p...", fh);
            fuse_destroy(fh);
        }

        delete context;
    }

    CSLogTraceLeave(_FNAME_ "(%p, %p, %p, %p, %p, %p, %p): %d", env, cls,
            fileSystem, mountPoint, optionStrings, fuseCapabilities,
            macFuseCapabilities, res);
    return res;
#undef _FNAME_
}

/*
 * Class:     org_catacombae_jfuse_FUSE
 * Method:    getContextNative
 * Signature: ()Lorg/catacombae/jfuse/types/fuse26/FUSEContext;
 */
JNIEXPORT jobject JNICALL Java_org_catacombae_jfuse_FUSE_getContextNative
  (JNIEnv *env, jclass clazz) {
#define _FNAME_ "Java_org_catacombae_jfuse_FUSE_getContextNative"
    CSLogTraceEnter("%s (%p, %p)", _FNAME_, env, clazz);

    jobject res = NULL;

    fuse_context *ctx = fuse_get_context();
    jFUSEContext *jfCtx = (jFUSEContext*)ctx->private_data;

    CSLogDebug("Context fields:");
    CSLogDebug("  fuse=%p", ctx->fuse);
    CSLogDebug("  uid=%d", ctx->uid);
    CSLogDebug("  gid=%d", ctx->gid);
    CSLogDebug("  pid=%d", ctx->pid);
    CSLogDebug("  private_data=%p", ctx->private_data);

    jclass fcClass = env->FindClass(FUSECONTEXT_CLASS);
    if(fcClass != NULL && env->ExceptionCheck() == JNI_FALSE) {
        jmethodID fcInitMid = env->GetMethodID(fcClass, FUSECONTEXT_INIT_NAME,
                FUSECONTEXT_INIT_SIGNATURE);
        if(fcInitMid != NULL && env->ExceptionCheck() == JNI_FALSE) {
            jobject obj = env->NewObject(fcClass, fcInitMid, (jlong)ctx->uid,
                    (jlong)ctx->gid, (jlong)ctx->pid, jfCtx->getPrivateData());
            if(obj == NULL || env->ExceptionCheck() == JNI_TRUE)
                CSLogError("Could not create new FUSEContext instance.");

            //if(obj != NULL)
            //    env->DeleteLocalRef(obj);
            
            res = obj;
        }
        else
            CSLogError("Could not get method ID for %s with signature %s.",
                    FUSECONTEXT_INIT_NAME, FUSECONTEXT_INIT_SIGNATURE);
    }
    else
        CSLogError("Could not find class %s.", FUSECONTEXT_CLASS);

    CSLogTraceLeave("%s (%p, %p): %p", _FNAME_, env, clazz, res);
    return res;
#undef _FNAME_
}

static int do_unmount(const char* mountpoint, int flags) {
#if defined(__linux__) || defined(__sun__)
    return umount2(mountpoint, flags);
#else
    return unmount(mountpoint, flags);
#endif
}

/*
 * Class:     org_catacombae_jfuse_FUSE
 * Method:    unmountNative
 * Signature: (Ljava/lang/String;Z)Z
 */
JNIEXPORT jboolean JNICALL Java_org_catacombae_jfuse_FUSE_unmountNative
  (JNIEnv *env, jclass clazz, jstring mountPoint, jboolean force) {
#define _FNAME_ "Java_org_catacombae_jfuse_FUSE_unmountNative"
    CSLogTraceEnter("%s (%p, %p, %p, %d)", _FNAME_, env, clazz, mountPoint,
            force);

    jboolean res = JNI_FALSE;

    const char *mountPointChars = env->GetStringUTFChars(mountPoint, NULL);

    if(do_unmount(mountPointChars, (force == JNI_TRUE ? UNMOUNT_FORCE : 0)) == 0)
        res = JNI_TRUE;
    else
        CSLogError("Could not unmount \"%s\". errno=%d (%s)", mountPointChars,
                errno, strerror(errno));

    env->ReleaseStringUTFChars(mountPoint, mountPointChars);

    CSLogTraceLeave("%s (%p, %p, %p, %d): %d", _FNAME_, env, clazz, mountPoint,
            force, res);
    return res;
#undef _FNAME_
}
