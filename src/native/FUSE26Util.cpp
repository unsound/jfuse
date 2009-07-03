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

#include "FUSE26Util.h"

#include "CSLog.h"
#include "FUSEFillDirContext.h"
#include "FUSEDirFilContext.h"
#include "JavaSignatures.h"

#define __STDC_FORMAT_MACROS
#include <inttypes.h>
#include <sys/stat.h>

/**
 * Creates a new Java object from the specified class, init name and init
 * signature. Currently you cannot pass on any arguments to the constructor, so
 * initName and initSignature are really pointless (they will always be "<init>"
 * and "()V".
 */
static inline jobject newObject(JNIEnv *env, const char *className, const char *initName,
        const char *initSignature) {

    jobject res = NULL;

    jclass clazz = env->FindClass(className);
    if(clazz == NULL || env->ExceptionCheck() == JNI_TRUE)
        CSLogError("Could not find class \"%s\"", className);
    else {
        jmethodID constructor = env->GetMethodID(clazz, initName,
                initSignature);
        if(constructor == NULL || env->ExceptionCheck() == JNI_TRUE)
            CSLogError("Could not find method \"%s\" with signature %s.", initName,
                initSignature);
        else {
            jobject obj = env->NewObject(clazz, constructor);
            if(obj == NULL || env->ExceptionCheck() == JNI_TRUE)
                CSLogError("Could not create new FUSEFileInfo instance.");
            else
                res = obj;
        }
    }

    return res;
}

static inline jobject newObjectWithObjectArg(JNIEnv *env, const char *className,
        const char *initName, const char *initSignature, jobject arg) {

    jobject res = NULL;

    jclass clazz = env->FindClass(className);
    if(clazz == NULL || env->ExceptionCheck() == JNI_TRUE)
        CSLogError("Could not find class \"%s\"", className);
    else {
        jmethodID constructor = env->GetMethodID(clazz, initName,
                initSignature);
        if(constructor == NULL || env->ExceptionCheck() == JNI_TRUE)
            CSLogError("Could not find method \"%s\" with signature %s.", initName,
                initSignature);
        else {
            jobject obj = env->NewObject(clazz, constructor, arg);
            if(obj == NULL || env->ExceptionCheck() == JNI_TRUE)
                CSLogError("Could not create new FUSEFileInfo instance.");
            else
                res = obj;
        }
    }

    return res;
}

jobject FUSE26Util::newFUSEFillDir(JNIEnv *env, fuse_fill_dir_t filler, void *buf) {
    CSLogTraceEnter("jobject FUSE26Util::newFUSEFillDir(%p, %p, %p)", env, filler, buf);

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
                CSLogError("Could not create new Java byte array with length %"
                        PRId32, (uint32_t)pointerArrayLength);
            }
            else {
                // 4. Fill pointer array with pointer data.
                env->SetByteArrayRegion(pointerArray, 0, pointerArrayLength,
                        (signed char*) (&ctx));
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

    CSLogTraceLeave("jobject FUSE26Util::newFUSEFillDir(%p, %p, %p): %p", env, filler, buf, result);
    return result;
}

/**
 * Creates a new FUSEDirFil object using <code>dirfil</code> and
 * <code>dirh</code> internally.
 */
jobject FUSE26Util::newFUSEDirFil(JNIEnv *env, fuse_dirfil_t dirfil,
        fuse_dirh_t dirh) {
    CSLogTraceEnter("jobject FUSE26Util::newFUSEDirFil(%p, %p, %p)", env,
            dirfil, dirh);

    jobject result = NULL;
    FUSEDirFilContext *ctx = new FUSEDirFilContext(dirfil, dirh);

    // Create pointer array to be passed as constructor argument.
    jsize pointerArrayLength = sizeof (ctx);
    jbyteArray pointerArray = env->NewByteArray(pointerArrayLength);
    if(pointerArray == NULL || env->ExceptionCheck() == JNI_TRUE) {
        CSLogError("Could not create new Java byte array with length %"
                PRId32, (uint32_t) pointerArrayLength);
    }
    else {
        // Fill pointer array with pointer data.
        env->SetByteArrayRegion(pointerArray, 0, pointerArrayLength,
                (signed char*) (&ctx));
        if(env->ExceptionCheck() == JNI_TRUE) {
            CSLogError("Could not fill array with pointer data.");
        }
        else {
            // Create the object.
            jobject instance = newObjectWithObjectArg(env, FUSEDIRFIL_CLASS,
                    FUSEDIRFIL_INIT_NAME, FUSEDIRFIL_INIT_SIGNATURE,
                    pointerArray);
            if(instance == NULL || env->ExceptionCheck() == JNI_TRUE) {
                CSLogError("Could not create new FUSEDirFil instance.");
            }
            else
                result = instance;
        }
    }

    if(pointerArray != NULL)
        env->DeleteLocalRef(pointerArray);

    if(env->ExceptionCheck() == JNI_TRUE)
        env->ExceptionDescribe();

    CSLogTraceLeave("jobject FUSE26Util::newFUSEDirFil(%p, %p, %p): %p", env,
            dirfil, dirh, result);
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
#ifdef __linux__
        target->st_atim.tv_sec = jl_atimespec_sec;
        target->st_atim.tv_nsec = jl_atimespec_nsec;
        target->st_mtim.tv_sec = jl_mtimespec_sec;
        target->st_mtim.tv_nsec = jl_mtimespec_nsec;
        target->st_ctim.tv_sec = jl_ctimespec_sec;
        target->st_ctim.tv_nsec = jl_ctimespec_nsec;
#else
        target->st_atimespec.tv_sec = jl_atimespec_sec;
        target->st_atimespec.tv_nsec = jl_atimespec_nsec;
        target->st_mtimespec.tv_sec = jl_mtimespec_sec;
        target->st_mtimespec.tv_nsec = jl_mtimespec_nsec;
        target->st_ctimespec.tv_sec = jl_ctimespec_sec;
        target->st_ctimespec.tv_nsec = jl_ctimespec_nsec;
#endif
        target->st_size = jl_size;
        target->st_blocks = jl_blocks;
        target->st_blksize = jl_blocksize;
#ifndef __linux__
        target->st_flags = jl_flags;
        target->st_gen = jl_gen;
#endif

        res = true;
    }
    while(0);

    CSLogTraceLeave("bool FUSE26Util::mergeStat(%p, %p, %p): %d", env, statObject, target, true);
    return res;
}

bool FUSE26Util::fillStat(JNIEnv *env, const struct stat *st, jobject statObject) {
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
#ifdef __linux__
        if(!setLongField(env, statClass, statObject, "st_atimespec_sec", st->st_atim.tv_sec))
            break;
        if(!setLongField(env, statClass, statObject, "st_atimespec_nsec", st->st_atim.tv_nsec))
            break;
        if(!setLongField(env, statClass, statObject, "st_mtimespec_sec", st->st_mtim.tv_sec))
            break;
        if(!setLongField(env, statClass, statObject, "st_mtimespec_nsec", st->st_mtim.tv_nsec))
            break;
        if(!setLongField(env, statClass, statObject, "st_ctimespec_sec", st->st_ctim.tv_sec))
            break;
        if(!setLongField(env, statClass, statObject, "st_ctimespec_nsec", st->st_ctim.tv_nsec))
            break;
#else
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
#endif
        if(!setLongField(env, statClass, statObject, "st_size", st->st_size))
            break;
        if(!setLongField(env, statClass, statObject, "st_blocks", st->st_blocks))
            break;
        if(!setLongField(env, statClass, statObject, "st_blocksize", st->st_blksize))
            break;
#ifndef __linux__
        if(!setLongField(env, statClass, statObject, "st_flags", st->st_flags))
            break;
        if(!setLongField(env, statClass, statObject, "st_gen", st->st_gen))
            break;
#endif
        
        ret = true;
    } while(0);

    CSLogTraceLeave("bool FUSE26Util::fillStat(%p, %p, %p): %d", env, st, statObject, ret);
    return ret;
}

jobject FUSE26Util::newStat(JNIEnv *env, const struct stat *st) {
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

bool FUSE26Util::fillFUSEFileInfo(JNIEnv *env, const struct fuse_file_info *fi, jobject ffiObject) {
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
jobject FUSE26Util::newFUSEFileInfo(JNIEnv *env, const struct fuse_file_info *fi) {
    CSLogTraceEnter("jobject FUSE26Util::newFUSEFileInfo(%p, %p)", env, fi);

    jobject res = NULL;

    jobject obj = newObject(env, FUSEFILEINFO_CLASS, FUSEFILEINFO_INIT_NAME, FUSEFILEINFO_INIT_SIGNATURE);
    if (obj == NULL || env->ExceptionCheck() == JNI_TRUE)
        CSLogError("Could not create new FUSEFileInfo instance.");
    else {
        if (!fillFUSEFileInfo(env, fi, obj))
            CSLogError("fillFUSEFileInfo failed!");
        else
            res = obj;
    }

    if(env->ExceptionCheck() == JNI_TRUE)
        env->ExceptionDescribe();

    CSLogTraceLeave("jobject FUSE26Util::newFUSEFileInfo(%p, %p): %p", env, fi, res);
    return res;
}

/**
 * Merges the contents of source (Java class Flock) with the supplied
 * struct flock.
 */
bool FUSE26Util::mergeFlock(JNIEnv *env, jobject source, struct flock *target) {
    CSLogTraceEnter("bool FUSE26Util::mergeFlock(%p, %p, %p)", env, source, target);
    bool res = false;
    do {
        jclass clazz = env->GetObjectClass(source);
        if(clazz == NULL || env->ExceptionCheck() == JNI_TRUE) {
            CSLogError("Could not get object class!");
            if(env->ExceptionCheck())
                env->ExceptionDescribe();
            break;
        }

        jlong start;
        jlong len;
        jlong pid;
        jshort type;
        jshort whence;

        if(!getLongField(env, clazz, source, "start", &start))
            break;
        if(!getLongField(env, clazz, source, "len", &len))
            break;
        if(!getLongField(env, clazz, source, "pid", &pid))
            break;
        if(!getShortField(env, clazz, source, "type", &type))
            break;
        if(!getShortField(env, clazz, source, "whence", &whence))
            break;

        target->l_start = start;
        target->l_len = len;
        target->l_pid = pid;
        target->l_type = type;
        target->l_whence = whence;
        
        res = true;
    }
    while(0);

    CSLogTraceLeave("bool FUSE26Util::mergeFlock(%p, %p, %p): %d", env, source, target, res);
    return res;
}

/**
 * Fills in the fields of target (Java class Flock) from the fields of source
 * (struct flock).
 */
bool FUSE26Util::fillFlock(JNIEnv *env, const struct flock *source, jobject target) {
    CSLogTraceEnter("bool FUSE26Util::fillFlock(%p, %p, %p)", env, source, target);

    bool ret = false;
    do {
        jclass clazz = env->GetObjectClass(target);
        if(clazz == NULL || env->ExceptionCheck() == JNI_TRUE) {
            CSLogError("Could not get object class!");
            if(env->ExceptionCheck())
                env->ExceptionDescribe();
            break;
        }

        if(!setLongField(env, clazz, target, "l_start", source->l_start))
            break;
        if(!setLongField(env, clazz, target, "l_len", source->l_len))
            break;
        if(!setLongField(env, clazz, target, "l_pid", source->l_pid))
            break;
        if(!setShortField(env, clazz, target, "l_type", source->l_type))
            break;
        if(!setShortField(env, clazz, target, "l_whence", source->l_whence))
            break;

        ret = true;
    } while(0);

    CSLogTraceLeave("bool FUSE26Util::fillFlock(%p, %p, %p): %d", env, source, target, ret);
    return ret;
}

/**
 * Creates a new Flock object and fills it using the fields in
 * <code>source</code>.
 */
jobject FUSE26Util::newFlock(JNIEnv *env, const struct flock *source) {
    CSLogTraceEnter("jobject FUSE26Util::newFlock(%p, %p)", env, source);

    jobject res = NULL;

    jobject obj = newObject(env, FLOCK_CLASS, FLOCK_INIT_NAME, FLOCK_INIT_SIGNATURE);
    if (obj == NULL || env->ExceptionCheck() == JNI_TRUE)
        CSLogError("Could not create new Flock instance.");
    else {
        if (!fillFlock(env, source, obj))
            CSLogError("fillFlock failed!");
        else
            res = obj;
    }

    if(env->ExceptionCheck() == JNI_TRUE)
        env->ExceptionDescribe();

    CSLogTraceLeave("jobject FUSE26Util::newFlock(%p, %p): %p", env, source, res);
    return res;
}

/**
 * Fills in the fields of target (Java class Timespec) from the fields of source
 * (struct timespec).
 */
bool FUSE26Util::fillTimespec(JNIEnv *env, const struct timespec *source, jobject target) {
    CSLogTraceEnter("bool FUSE26Util::fillTimespec(%p, %p, %p)", env, source, target);

    bool ret = false;
    do {
        jclass clazz = env->GetObjectClass(target);
        if(clazz == NULL || env->ExceptionCheck() == JNI_TRUE) {
            CSLogError("Could not get object class!");
            if(env->ExceptionCheck())
                env->ExceptionDescribe();
            break;
        }

        if(!setIntField(env, clazz, target, "tv_sec", source->tv_sec))
            break;
        if(!setIntField(env, clazz, target, "tv_nsec", source->tv_nsec))
            break;
        
        ret = true;
    } while(0);

    CSLogTraceLeave("bool FUSE26Util::fillTimespec(%p, %p, %p): %d", env, source, target, ret);
    return ret;
}

/**
 * Creates a new Timespec object and fills it using the fields in
 * <code>source</code>.
 */
jobject FUSE26Util::newTimespec(JNIEnv *env, const struct timespec *source) {
    CSLogTraceEnter("jobject FUSE26Util::newTimespec(%p, %p)", env, source);

    jobject res = NULL;

    jobject obj = newObject(env, TIMESPEC_CLASS, TIMESPEC_INIT_NAME, TIMESPEC_INIT_SIGNATURE);
    if (obj == NULL || env->ExceptionCheck() == JNI_TRUE)
        CSLogError("Could not create new Timespec instance.");
    else {
        if (!fillTimespec(env, source, obj))
            CSLogError("fillTimespec failed!");
        else
            res = obj;
    }

    if(env->ExceptionCheck() == JNI_TRUE)
        env->ExceptionDescribe();

    CSLogTraceLeave("jobject FUSE26Util::newTimespec(%p, %p): %p", env, source, res);
    return res;
}

/**
 * Merges the contents of source (Java class LongRef) with the supplied
 * uint64_t.
 */
bool FUSE26Util::mergeLongRef(JNIEnv *env, jobject source, uint64_t *target) {
    CSLogTraceEnter("bool FUSE26Util::mergeLongRef(%p, %p, %p)", env, source, target);
    bool res = false;
    do {
        jclass clazz = env->GetObjectClass(source);
        if(clazz == NULL || env->ExceptionCheck() == JNI_TRUE) {
            CSLogError("Could not get object class!");
            if(env->ExceptionCheck())
                env->ExceptionDescribe();
            break;
        }

        jlong ref;

        if(!getLongField(env, clazz, source, "ref", &ref))
            break;

        *target = ref;

        res = true;
    }
    while(0);

    CSLogTraceLeave("bool FUSE26Util::mergeLongRef(%p, %p, %p): %d", env, source, target, res);
    return res;
}

/**
 * Fills in the fields of target (Java class LongRef) from the fields of source
 * (uint64_t).
 */
bool FUSE26Util::fillLongRef(JNIEnv *env, const uint64_t *source, jobject target) {
    CSLogTraceEnter("bool FUSE26Util::fillLongRef(%p, %p, %p)", env, source, target);

    bool ret = false;
    do {
        jclass clazz = env->GetObjectClass(target);
        if(clazz == NULL || env->ExceptionCheck() == JNI_TRUE) {
            CSLogError("Could not get object class!");
            if(env->ExceptionCheck())
                env->ExceptionDescribe();
            break;
        }

        if(!setLongField(env, clazz, target, "ref", *source))
            break;
        
        ret = true;
    } while(0);

    CSLogTraceLeave("bool FUSE26Util::fillLongRef(%p, %p, %p): %d", env, source, target, ret);
    return ret;
}

/**
 * Creates a new LongRef object and fills it using the fields in
 * <code>source</code>.
 */
jobject FUSE26Util::newLongRef(JNIEnv *env, const uint64_t *source) {
    CSLogTraceEnter("jobject FUSE26Util::newLongRef(%p, %p)", env, source);

    jobject res = NULL;

    jobject obj = newObject(env, LONGREF_CLASS, LONGREF_INIT_NAME, LONGREF_INIT_SIGNATURE);
    if (obj == NULL || env->ExceptionCheck() == JNI_TRUE)
        CSLogError("Could not create new LongRef instance.");
    else {
        if (!fillLongRef(env, source, obj))
            CSLogError("fillLongRef failed!");
        else
            res = obj;
    }

    if(env->ExceptionCheck() == JNI_TRUE)
        env->ExceptionDescribe();

    CSLogTraceLeave("jobject FUSE26Util::newLongRef(%p, %p): %p", env, source, res);
    return res;
}

/**
 * Merges the contents of source (Java class LongRef) with the supplied
 * uint64_t.
 */
bool FUSE26Util::mergeFUSEConnInfo(JNIEnv *env, jobject source, struct fuse_conn_info *target) {
    CSLogTraceEnter("bool FUSE26Util::mergeFUSEConnInfo(%p, %p, %p)", env, source, target);
    bool res = false;
    do {
        jclass clazz = env->GetObjectClass(source);
        if(clazz == NULL || env->ExceptionCheck() == JNI_TRUE) {
            CSLogError("Could not get object class!");
            if(env->ExceptionCheck())
                env->ExceptionDescribe();
            break;
        }

        jlong proto_major;
        jlong proto_minor;
        jboolean async_read;
        jlong max_write;
        jlong max_readahead;

        if(!getLongField(env, clazz, source, "proto_major", &proto_major))
            break;
        if(!getLongField(env, clazz, source, "proto_minor", &proto_minor))
            break;
        if(!getBooleanField(env, clazz, source, "async_read", &async_read))
            break;
        if(!getLongField(env, clazz, source, "max_write", &max_write))
            break;
        if(!getLongField(env, clazz, source, "max_readahead", &max_readahead))
            break;

        target->proto_major = proto_major;
        target->proto_minor = proto_minor;
        target->async_read = (async_read == JNI_TRUE ? 1 : 0);
        target->max_write = max_write;
        target->max_readahead = max_readahead;

        res = true;
    }
    while(0);

    CSLogTraceLeave("bool FUSE26Util::mergeFUSEConnInfo(%p, %p, %p): %d", env, source, target, res);
    return res;
}

/**
 * Fills in the fields of target (Java class LongRef) from the fields of source
 * (uint64_t).
 */
bool FUSE26Util::fillFUSEConnInfo(JNIEnv *env, const struct fuse_conn_info *source, jobject target) {
    CSLogTraceEnter("bool FUSE26Util::fillFUSEConnInfo(%p, %p, %p)", env, source, target);

    bool ret = false;
    do {
        jclass clazz = env->GetObjectClass(target);
        if(clazz == NULL || env->ExceptionCheck() == JNI_TRUE) {
            CSLogError("Could not get object class!");
            if(env->ExceptionCheck())
                env->ExceptionDescribe();
            break;
        }

        if(!setLongField(env, clazz, target, "proto_major", source->proto_major))
            break;
        if(!setLongField(env, clazz, target, "proto_minor", source->proto_minor))
            break;
        if(!setBooleanField(env, clazz, target, "async_read", (source->async_read ? JNI_TRUE : JNI_FALSE)))
            break;
        if(!setLongField(env, clazz, target, "max_write", source->max_write))
            break;
        if(!setLongField(env, clazz, target, "max_readahead", source->max_readahead))
            break;

        ret = true;
    } while(0);

    CSLogTraceLeave("bool FUSE26Util::fillFUSEConnInfo(%p, %p, %p): %d", env, source, target, ret);
    return ret;
}

/**
 * Creates a new LongRef object and fills it using the fields in
 * <code>source</code>.
 */
jobject FUSE26Util::newFUSEConnInfo(JNIEnv *env, const struct fuse_conn_info *source) {
    CSLogTraceEnter("jobject FUSE26Util::newFUSEConnInfo(%p, %p)", env, source);

    jobject res = NULL;

    jobject obj = newObject(env, FUSECONNINFO_CLASS, FUSECONNINFO_INIT_NAME, FUSECONNINFO_INIT_SIGNATURE);
    if (obj == NULL || env->ExceptionCheck() == JNI_TRUE)
        CSLogError("Could not create new FUSEConnInfo instance.");
    else {
        if (!fillFUSEConnInfo(env, source, obj))
            CSLogError("fillFUSEConnInfo failed!");
        else
            res = obj;
    }

    if(env->ExceptionCheck() == JNI_TRUE)
        env->ExceptionDescribe();

    CSLogTraceLeave("jobject FUSE26Util::newFUSEConnInfo(%p, %p): %p", env, source, res);
    return res;
}

/**
 * Merges the contents of source (Java class Utimbuf) with the supplied
 * struct utimbuf.
 */
bool FUSE26Util::mergeUtimbuf(JNIEnv *env, jobject source, struct utimbuf *target) {
    CSLogTraceEnter("bool FUSE26Util::mergeUtimbuf(%p, %p, %p)", env, source, target);
    bool res = false;
    do {
        jclass clazz = env->GetObjectClass(source);
        if(clazz == NULL || env->ExceptionCheck() == JNI_TRUE) {
            CSLogError("Could not get object class!");
            if(env->ExceptionCheck())
                env->ExceptionDescribe();
            break;
        }

        jlong actime;
        jlong modtime;

        if(!getLongField(env, clazz, source, "actime", &actime))
            break;
        if(!getLongField(env, clazz, source, "modtime", &modtime))
            break;

        target->actime = actime;
        target->modtime = modtime;

        res = true;
    }
    while(0);

    CSLogTraceLeave("bool FUSE26Util::mergeUtimbuf(%p, %p, %p): %d", env, source, target, res);
    return res;
}

/**
 * Fills in the fields of target (Java class Utimbuf) from the fields of source
 * (struct utimbuf).
 */
bool FUSE26Util::fillUtimbuf(JNIEnv *env, const struct utimbuf *source, jobject target) {
    CSLogTraceEnter("bool FUSE26Util::fillUtimbuf(%p, %p, %p)", env, source, target);

    bool ret = false;
    do {
        jclass clazz = env->GetObjectClass(target);
        if(clazz == NULL || env->ExceptionCheck() == JNI_TRUE) {
            CSLogError("Could not get object class!");
            if(env->ExceptionCheck())
                env->ExceptionDescribe();
            break;
        }

        if(!setLongField(env, clazz, target, "actime", source->actime))
            break;
        if(!setLongField(env, clazz, target, "modtime", source->modtime))
            break;

        ret = true;
    } while(0);

    CSLogTraceLeave("bool FUSE26Util::fillUtimbuf(%p, %p, %p): %d", env, source, target, ret);
    return ret;
}

/**
 * Creates a new Utimbuf object and fills it using the fields in
 * <code>source</code>.
 */
jobject FUSE26Util::newUtimbuf(JNIEnv *env, const struct utimbuf *source) {
    CSLogTraceEnter("jobject FUSE26Util::newUtimbuf(%p, %p)", env, source);

    jobject res = NULL;

    jobject obj = newObject(env, UTIMBUF_CLASS, UTIMBUF_INIT_NAME, UTIMBUF_INIT_SIGNATURE);
    if (obj == NULL || env->ExceptionCheck() == JNI_TRUE)
        CSLogError("Could not create new Utimbuf instance.");
    else {
        if (!fillUtimbuf(env, source, obj))
            CSLogError("fillUtimbuf failed!");
        else
            res = obj;
    }

    if(env->ExceptionCheck() == JNI_TRUE)
        env->ExceptionDescribe();

    CSLogTraceLeave("jobject FUSE26Util::newUtimbuf(%p, %p): %p", env, source, res);
    return res;
}

/**
 * Merges the contents of source (Java class StatVFS) with the supplied
 * struct statvfs.
 */
bool FUSE26Util::mergeStatVFS(JNIEnv *env, jobject source, struct statvfs *target) {
    CSLogTraceEnter("bool FUSE26Util::mergeStatVFS(%p, %p, %p)", env, source, target);
    bool res = false;
    do {
        jclass clazz = env->GetObjectClass(source);
        if(clazz == NULL || env->ExceptionCheck() == JNI_TRUE) {
            CSLogError("Could not get object class!");
            if(env->ExceptionCheck())
                env->ExceptionDescribe();
            break;
        }

        jlong f_bsize;
        jlong f_frsize;
        jlong f_blocks;
        jlong f_bfree;
        jlong f_bavail;
        jlong f_files;
        jlong f_ffree;
        jlong f_favail;
        jlong f_fsid;
        jlong f_flag;
        jlong f_namemax;

        if(!getLongField(env, clazz, source, "f_bsize", &f_bsize))
            break;
        if(!getLongField(env, clazz, source, "f_frsize", &f_frsize))
            break;
        if(!getLongField(env, clazz, source, "f_blocks", &f_blocks))
            break;
        if(!getLongField(env, clazz, source, "f_bfree", &f_bfree))
            break;
        if(!getLongField(env, clazz, source, "f_bavail", &f_bavail))
            break;
        if(!getLongField(env, clazz, source, "f_files", &f_files))
            break;
        if(!getLongField(env, clazz, source, "f_ffree", &f_ffree))
            break;
        if(!getLongField(env, clazz, source, "f_favail", &f_favail))
            break;
        if(!getLongField(env, clazz, source, "f_fsid", &f_fsid))
            break;
        if(!getLongField(env, clazz, source, "f_flag", &f_flag))
            break;
        if(!getLongField(env, clazz, source, "f_namemax", &f_namemax))
            break;

        target->f_bsize = f_bsize;
        target->f_frsize = f_frsize;
        target->f_blocks = f_blocks;
        target->f_bfree = f_bfree;
        target->f_bavail = f_bavail;
        target->f_files = f_files;
        target->f_ffree = f_ffree;
        target->f_favail = f_favail;
        target->f_fsid = f_fsid;
        target->f_flag = f_flag;
        target->f_namemax = f_namemax;

        res = true;
    }
    while(0);

    CSLogTraceLeave("bool FUSE26Util::mergeStatVFS(%p, %p, %p): %d", env, source, target, res);
    return res;
}

/**
 * Fills in the fields of target (Java class StatVFS) from the fields of source
 * (struct statvfs).
 */
bool FUSE26Util::fillStatVFS(JNIEnv *env, const struct statvfs *source, jobject target) {
    CSLogTraceEnter("bool FUSE26Util::fillStatVFS(%p, %p, %p)", env, source, target);

    bool ret = false;
    do {
        jclass clazz = env->GetObjectClass(target);
        if(clazz == NULL || env->ExceptionCheck() == JNI_TRUE) {
            CSLogError("Could not get object class!");
            if(env->ExceptionCheck())
                env->ExceptionDescribe();
            break;
        }

        if(!setLongField(env, clazz, target, "f_bsize", source->f_bsize))
            break;
        if(!setLongField(env, clazz, target, "f_frsize", source->f_frsize))
            break;
        if(!setLongField(env, clazz, target, "f_blocks", source->f_blocks))
            break;
        if(!setLongField(env, clazz, target, "f_bfree", source->f_bfree))
            break;
        if(!setLongField(env, clazz, target, "f_bavail", source->f_bavail))
            break;
        if(!setLongField(env, clazz, target, "f_files", source->f_files))
            break;
        if(!setLongField(env, clazz, target, "f_ffree", source->f_ffree))
            break;
        if(!setLongField(env, clazz, target, "f_favail", source->f_favail))
            break;
        if(!setLongField(env, clazz, target, "f_fsid", source->f_fsid))
            break;
        if(!setLongField(env, clazz, target, "f_flag", source->f_flag))
            break;
        if(!setLongField(env, clazz, target, "f_namemax", source->f_namemax))
            break;

        ret = true;
    } while(0);

    CSLogTraceLeave("bool FUSE26Util::fillStatVFS(%p, %p, %p): %d", env, source, target, ret);
    return ret;
}

/**
 * Creates a new StatVFS object and fills it using the fields in
 * <code>source</code>.
 */
jobject FUSE26Util::newStatVFS(JNIEnv *env, const struct statvfs *source) {
    CSLogTraceEnter("jobject FUSE26Util::newStatVFS(%p, %p)", env, source);

    jobject res = NULL;

    jobject obj = newObject(env, STATVFS_CLASS, STATVFS_INIT_NAME, STATVFS_INIT_SIGNATURE);
    if (obj == NULL || env->ExceptionCheck() == JNI_TRUE)
        CSLogError("Could not create new StatVFS instance.");
    else {
        if (!fillStatVFS(env, source, obj))
            CSLogError("fillStatVFS failed!");
        else
            res = obj;
    }

    if(env->ExceptionCheck() == JNI_TRUE)
        env->ExceptionDescribe();

    CSLogTraceLeave("jobject FUSE26Util::newStatVFS(%p, %p): %p", env, source, res);
    return res;
}
