#include "FUSE26Util.h"

#include "CSLog.h"
#include "FUSEFillDirContext.h"
#include "JavaSignatures.h"

#define __STDC_FORMAT_MACROS
#include <inttypes.h>

jobject FUSE26Util::createFUSEFillDir(JNIEnv *env, fuse_fill_dir_t filler, void *buf) {
    CSLogTraceEnter("jobject FUSE26Util::createFUSEFillDir(%p, %p, %p)", env, filler, buf);

    jobject result = NULL;
    FUSEFillDirContext *ctx = new FUSEFillDirContext(filler, buf);

    // 1. Find FUSEFillDir class.
    jclass clazz = env->FindClass(FUSEFILLDIR_CLASS);
    if(clazz == NULL || env->ExceptionCheck() == JNI_TRUE) {
        CSLogError("Could not find FUSEFillDir class.");
    }
    else {
        // 2. Obtain the method ID of constructor.
        jmethodID constructor = env->GetMethodID(clazz, FUSEFILLDIR_INIT_NAME,
                FUSEFILLDIR_INIT_SIGNATURE);
        if(constructor == NULL || env->ExceptionCheck() == JNI_TRUE) {
            CSLogError("Could not find constructor %s with signature %s",
                    FUSEFILLDIR_INIT_NAME, FUSEFILLDIR_INIT_SIGNATURE);
        }
        else {
            // 3. Create pointer array to be passed as constructor argument.
            jsize pointerArrayLength = sizeof (ctx);
            jbyteArray pointerArray = env->NewByteArray(pointerArrayLength);
            if(pointerArray == NULL || env->ExceptionCheck() == JNI_TRUE) {
                CSLogError("Could not create new Java byte array with length %" PRId32, pointerArrayLength);
            }
            else {
                // 4. Fill pointer array with pointer data.
                env->SetByteArrayRegion(pointerArray, 0, pointerArrayLength, (signed char*) (&ctx));
                if(env->ExceptionCheck() == JNI_TRUE) {
                    CSLogError("Could not fill array with pointer data.");
                }
                else {
                    // 5. Create the new instance.
                    jobject instance = env->NewObject(clazz, constructor, pointerArray);
                    if(instance == NULL || env->ExceptionCheck() == JNI_TRUE) {
                        CSLogError("Could not create new FUSEFillDir instance.");
                    }
                    else
                        result = instance;
                }
            }

            if(pointerArray != NULL)
                env->DeleteLocalRef(pointerArray);
        }
    }
    if(clazz != NULL)
        env->DeleteLocalRef(clazz);

    if(env->ExceptionCheck() == JNI_TRUE)
        env->ExceptionDescribe();

    CSLogTraceEnter("jobject FUSE26Util::createFUSEFillDir(%p, %p, %p): %p", env, filler, buf, result);
    return result;
}

/**
 * Merges the contents of statObject into the struct stat target.
 */
bool FUSE26Util::mergeStat(JNIEnv *env, jobject statObject, struct stat *target) {
    CSLogTraceEnter("bool FUSE26Util::mergeStat(%p, %p, %p)", env, statObject, target);

    bool res = false;
    do {
        //LOG_DEBUG("    - Getting class Stat");
        //jclass statClass = env->FindClass(env, "org/catacombae/jfuse/Stat");
        jclass statClass = env->GetObjectClass(statObject);
        if(statClass == NULL || env->ExceptionCheck() == JNI_TRUE) {
            CSLogError("Could not get object class!");
            if(env->ExceptionCheck())
                env->ExceptionDescribe();
            break;
        }
        //LOG_DEBUG("      - statClass: %X", (int)statClass);
        //LOG_DEBUG("    - Getting field id for st_mode");

        jlong jl_dev;
        jlong jl_ino;
        jlong jl_mode;
        jlong jl_nlink;
        jlong jl_uid;
        jlong jl_gid;
        jlong jl_rdev;
        jlong jl_atimespec_sec;
        jlong jl_atimespec_nsec;
        jlong jl_mtimespec_sec;
        jlong jl_mtimespec_nsec;
        jlong jl_ctimespec_sec;
        jlong jl_ctimespec_nsec;
        jlong jl_size;
        jlong jl_blocks;
        jlong jl_blocksize;
        jlong jl_flags;
        jlong jl_gen;

        if(!getLongField(env, statClass, statObject, "st_dev", &jl_dev))
            break;
        if(!getLongField(env, statClass, statObject, "st_ino", &jl_ino))
            break;
        if(!getLongField(env, statClass, statObject, "st_mode", &jl_mode))
            break;
        if(!getLongField(env, statClass, statObject, "st_nlink", &jl_nlink))
            break;
        if(!getLongField(env, statClass, statObject, "st_uid", &jl_uid))
            break;
        if(!getLongField(env, statClass, statObject, "st_gid", &jl_gid))
            break;
        if(!getLongField(env, statClass, statObject, "st_rdev", &jl_rdev))
            break;
        if(!getLongField(env, statClass, statObject, "st_atimespec_sec", &jl_atimespec_sec))
            break;
        if(!getLongField(env, statClass, statObject, "st_atimespec_nsec", &jl_atimespec_nsec))
            break;
        if(!getLongField(env, statClass, statObject, "st_mtimespec_sec", &jl_mtimespec_sec))
            break;
        if(!getLongField(env, statClass, statObject, "st_mtimespec_nsec", &jl_mtimespec_nsec))
            break;
        if(!getLongField(env, statClass, statObject, "st_ctimespec_sec", &jl_ctimespec_sec))
            break;
        if(!getLongField(env, statClass, statObject, "st_ctimespec_nsec", &jl_ctimespec_nsec))
            break;
        if(!getLongField(env, statClass, statObject, "st_size", &jl_size))
            break;
        if(!getLongField(env, statClass, statObject, "st_blocks", &jl_blocks))
            break;
        if(!getLongField(env, statClass, statObject, "st_blocksize", &jl_blocksize))
            break;
        if(!getLongField(env, statClass, statObject, "st_flags", &jl_flags))
            break;
        if(!getLongField(env, statClass, statObject, "st_gen", &jl_gen))
            break;

        target->st_dev = jl_dev;
        target->st_ino = jl_ino;
        target->st_mode = jl_mode;
        target->st_nlink = jl_nlink;
        target->st_uid = jl_uid;
        target->st_gid = jl_gid;
        target->st_rdev = jl_rdev;
        target->st_atimespec.tv_sec = jl_atimespec_sec;
        target->st_atimespec.tv_nsec = jl_atimespec_nsec;
        target->st_mtimespec.tv_sec = jl_mtimespec_sec;
        target->st_mtimespec.tv_nsec = jl_mtimespec_nsec;
        target->st_ctimespec.tv_sec = jl_ctimespec_sec;
        target->st_ctimespec.tv_nsec = jl_ctimespec_nsec;
        target->st_size = jl_size;
        target->st_blocks = jl_blocks;
        target->st_blksize = jl_blocksize;
        target->st_flags = jl_flags;
        target->st_gen = jl_gen;

        res = true;
    }
    while(0);

    CSLogTraceLeave("bool FUSE26Util::mergeStat(%p, %p, %p): %d", env, statObject, target, true);
    return res;
}

bool FUSE26Util::fillStat(JNIEnv *env, struct stat *st, jobject statObject) {
    CSLogTraceEnter("bool FUSE26Util::fillStat(%p, %p, %p)", env, st, statObject);

    bool ret = false;
    do {
        jclass statClass = env->GetObjectClass(statObject);
        if(statClass == NULL || env->ExceptionCheck() == JNI_TRUE) {
            CSLogError("Could not get object class!");
            if(env->ExceptionCheck())
                env->ExceptionDescribe();
            break;
        }

        if(!setLongField(env, statClass, statObject, "st_dev", st->st_dev))
            break;
        if(!setLongField(env, statClass, statObject, "st_ino", st->st_ino))
            break;
        if(!setLongField(env, statClass, statObject, "st_mode", st->st_mode))
            break;
        if(!setLongField(env, statClass, statObject, "st_nlink", st->st_nlink))
            break;
        if(!setLongField(env, statClass, statObject, "st_uid", st->st_uid))
            break;
        if(!setLongField(env, statClass, statObject, "st_gid", st->st_gid))
            break;
        if(!setLongField(env, statClass, statObject, "st_rdev", st->st_rdev))
            break;
        if(!setLongField(env, statClass, statObject, "st_atimespec_sec", st->st_atimespec.tv_sec))
            break;
        if(!setLongField(env, statClass, statObject, "st_atimespec_nsec", st->st_atimespec.tv_nsec))
            break;
        if(!setLongField(env, statClass, statObject, "st_mtimespec_sec", st->st_mtimespec.tv_sec))
            break;
        if(!setLongField(env, statClass, statObject, "st_mtimespec_nsec", st->st_mtimespec.tv_nsec))
            break;
        if(!setLongField(env, statClass, statObject, "st_ctimespec_sec", st->st_ctimespec.tv_sec))
            break;
        if(!setLongField(env, statClass, statObject, "st_ctimespec_nsec", st->st_ctimespec.tv_nsec))
            break;
        if(!setLongField(env, statClass, statObject, "st_size", st->st_size))
            break;
        if(!setLongField(env, statClass, statObject, "st_blocks", st->st_blocks))
            break;
        if(!setLongField(env, statClass, statObject, "st_blocksize", st->st_blksize))
            break;
        if(!setLongField(env, statClass, statObject, "st_flags", st->st_flags))
            break;
        if(!setLongField(env, statClass, statObject, "st_gen", st->st_gen))
            break;

        ret = true;
    } while(0);

    CSLogTraceLeave("bool FUSE26Util::fillStat(%p, %p, %p): %d", env, st, statObject, ret);
    return ret;
}

jobject FUSE26Util::newStat(JNIEnv *env, struct stat *st) {
    CSLogTraceEnter("jobject FUSE26Util::newStat(%p, %p)", env, st);

    jobject res = NULL;
    jclass clazz = env->FindClass(STAT_CLASS);
    if(clazz == NULL || env->ExceptionCheck() == JNI_TRUE)
        CSLogError("Could not find class \"%s\"", STAT_CLASS);
    else {
        jmethodID constructor = env->GetMethodID(clazz, STAT_INIT_NAME,
                STAT_INIT_SIGNATURE);
        if(constructor == NULL || env->ExceptionCheck() == JNI_TRUE)
            CSLogError("Could not find method \"%s\" with signature %s.", STAT_INIT_NAME,
                STAT_INIT_SIGNATURE);
        else {
            jobject obj = env->NewObject(clazz, constructor);
            if(obj == NULL || env->ExceptionCheck() == JNI_TRUE)
                CSLogError("Could not create new Stat instance.");
            else {
                if(!fillStat(env, st, obj))
                    CSLogError("fillStat failed!");
                else
                    res = obj;
            }

            if(res == NULL && obj != NULL)
                env->DeleteLocalRef(obj);
        }
    }

    if(clazz != NULL)
        env->DeleteLocalRef(clazz);

    if(env->ExceptionCheck() == JNI_TRUE)
        env->ExceptionDescribe();

    CSLogTraceLeave("jobject FUSE26Util::newStat(%p, %p): %p", env, st, res);
    return res;
}

bool FUSE26Util::mergeFUSEFileInfo(JNIEnv *env, jobject ffiObject, struct fuse_file_info *target) {
    CSLogTraceEnter("bool FUSE26Util::mergeFUSEFileInfo(%p, %p, %p)", env, ffiObject, target);
    bool res = false;
    do {
        //LOG_DEBUG("    - Getting class Stat");
        //jclass statClass = env->FindClass(env, "org/catacombae/jfuse/Stat");
        jclass ffiClass = env->GetObjectClass(ffiObject);
        if(ffiClass == NULL || env->ExceptionCheck() == JNI_TRUE) {
            CSLogError("Could not get object class!");
            if(env->ExceptionCheck())
                env->ExceptionDescribe();
            break;
        }
        //LOG_DEBUG("      - statClass: %X", (int)statClass);
        //LOG_DEBUG("    - Getting field id for st_mode");

        jint flags;
        jlong fh_old;
        jint writepage;
        jboolean direct_io;
        jboolean keep_cache;
        jboolean flush;
        jlong fh;
        jlong lock_owner;

        if(!getIntField(env, ffiClass, ffiObject, "flags", &flags))
            break;
        if(!getLongField(env, ffiClass, ffiObject, "fh_old", &fh_old))
            break;
        if(!getIntField(env, ffiClass, ffiObject, "writepage", &writepage))
            break;
        if(!getBooleanField(env, ffiClass, ffiObject, "direct_io", &direct_io))
            break;
        if(!getBooleanField(env, ffiClass, ffiObject, "keep_cache", &keep_cache))
            break;
        if(!getBooleanField(env, ffiClass, ffiObject, "flush", &flush))
            break;
        if(!getLongField(env, ffiClass, ffiObject, "fh", &fh))
            break;
        if(!getLongField(env, ffiClass, ffiObject, "lock_owner", &lock_owner))
            break;

        target->flags = flags;
        target->fh_old = fh_old;
        target->writepage = writepage;
        target->direct_io = direct_io;
        target->keep_cache = keep_cache;
        target->flush = flush;
        target->fh = fh;
        target->lock_owner = lock_owner;
        
        res = true;
    }
    while(0);

    CSLogTraceLeave("bool FUSE26Util::mergeFUSEFileInfo(%p, %p, %p): %d", env, ffiObject, target, res);
    return res;
}

bool FUSE26Util::fillFUSEFileInfo(JNIEnv *env, struct fuse_file_info *fi, jobject ffiObject) {
    CSLogTraceEnter("bool FUSE26Util::fillFUSEFileInfo(%p, %p, %p)", env, fi, ffiObject);

    bool ret = false;
    do {
        jclass ffiClass = env->GetObjectClass(ffiObject);
        if(ffiClass == NULL || env->ExceptionCheck() == JNI_TRUE) {
            CSLogError("Could not get object class!");
            if(env->ExceptionCheck())
                env->ExceptionDescribe();
            break;
        }

        if(!setIntField(env, ffiClass, ffiObject, "flags", fi->flags))
            break;
        if(!setLongField(env, ffiClass, ffiObject, "fh_old", fi->fh_old))
            break;
        if(!setIntField(env, ffiClass, ffiObject, "writepage", fi->writepage))
            break;
        if(!setBooleanField(env, ffiClass, ffiObject, "direct_io", (fi->direct_io == 0 ? JNI_FALSE : JNI_TRUE)))
            break;
        if(!setBooleanField(env, ffiClass, ffiObject, "keep_cache", (fi->keep_cache == 0 ? JNI_FALSE : JNI_TRUE)))
            break;
        if(!setBooleanField(env, ffiClass, ffiObject, "flush", (fi->flush == 0 ? JNI_FALSE : JNI_TRUE)))
            break;
        if(!setLongField(env, ffiClass, ffiObject, "fh", fi->fh))
            break;
        if(!setLongField(env, ffiClass, ffiObject, "lock_owner", fi->lock_owner))
            break;

        ret = true;
    } while(0);

    CSLogTraceLeave("bool FUSE26Util::fillFUSEFileInfo(%p, %p, %p): %d", env, fi, ffiObject, ret);
    return ret;
}

/**
 * Creates a new FUSEFileInfo object and fills it using the fields in
 * <code>fi</code>.
 */
jobject FUSE26Util::newFUSEFileInfo(JNIEnv *env, struct fuse_file_info *fi) {
    CSLogTraceEnter("jobject FUSE26Util::newFUSEFileInfo(%p, %p)", env, fi);

    jobject res = NULL;
    jclass ffiClass = env->FindClass(FUSEFILEINFO_CLASS);
    if(ffiClass == NULL || env->ExceptionCheck() == JNI_TRUE)
        CSLogError("Could not find class \"%s\"", FUSEFILEINFO_CLASS);
    else {
        jmethodID ffiConstructor = env->GetMethodID(ffiClass, FUSEFILEINFO_INIT_NAME,
                FUSEFILEINFO_INIT_SIGNATURE);
        if(ffiConstructor == NULL || env->ExceptionCheck() == JNI_TRUE)
            CSLogError("Could not find method \"%s\" with signature %s.", FUSEFILEINFO_INIT_NAME,
                FUSEFILEINFO_INIT_SIGNATURE);
        else {
            jobject obj = env->NewObject(ffiClass, ffiConstructor);
            if(obj == NULL || env->ExceptionCheck() == JNI_TRUE)
                CSLogError("Could not create new FUSEFileInfo instance.");
            else {
                if(!fillFUSEFileInfo(env, fi, obj))
                    CSLogError("fillFUSEFileInfo failed!");
                else
                    res = obj;
            }
        }
    }

    if(env->ExceptionCheck() == JNI_TRUE)
        env->ExceptionDescribe();

    CSLogTraceLeave("jobject FUSE26Util::newFUSEFileInfo(%p, %p): %p", env, fi, res);
    return res;
}


