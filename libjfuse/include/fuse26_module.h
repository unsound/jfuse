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

#ifndef _FUSE_MODULE_H
#define	_FUSE_MODULE_H

#define FUSE_USE_VERSION 26

#include <jni.h>
#include <fuse.h>
#include "jFUSEContext.h"
#include "JNIUtil.h"
#include "FUSE26Util.h"

void jfuse_set_context(jFUSEContext *ctx);

/*
 * Function definitions for our jFUSE callbacks.
 */

int jfuse_getattr(const char *, struct stat *);

int jfuse_readlink(const char *, char *, size_t);

int jfuse_getdir(const char *, fuse_dirh_t, fuse_dirfil_t);

int jfuse_mknod(const char *, mode_t, dev_t);

int jfuse_mkdir(const char *, mode_t);

int jfuse_unlink(const char *);

int jfuse_rmdir(const char *);

int jfuse_symlink(const char *, const char *);

int jfuse_rename(const char *, const char *);

int jfuse_link(const char *, const char *);

int jfuse_chmod(const char *, mode_t);

int jfuse_chown(const char *, uid_t, gid_t);

int jfuse_truncate(const char *, off_t);

int jfuse_utime(const char *, struct utimbuf *);

int jfuse_open(const char *, struct fuse_file_info *);

int jfuse_read(const char *, char *, size_t, off_t,
        struct fuse_file_info *);

int jfuse_write(const char *, const char *, size_t, off_t,
        struct fuse_file_info *);

int jfuse_statfs(const char *, struct statvfs *);

int jfuse_flush(const char *, struct fuse_file_info *);

int jfuse_release(const char *, struct fuse_file_info *);

int jfuse_fsync(const char *, int, struct fuse_file_info *);

#if (__FreeBSD__ >= 10)
int jfuse_setxattr(const char *, const char *, const char *, size_t, int, uint32_t);
#else
int jfuse_setxattr(const char *, const char *, const char *, size_t, int);
#endif /* __FreeBSD__ >= 10 */

#if (__FreeBSD__ >= 10)
int jfuse_getxattr(const char *, const char *, char *, size_t, uint32_t);
#else
int jfuse_getxattr(const char *, const char *, char *, size_t);
#endif /* __FreeBSD__ >= 10 */

int jfuse_listxattr(const char *, char *, size_t);

int jfuse_removexattr(const char *, const char *);

int jfuse_opendir(const char *, struct fuse_file_info *);

int jfuse_readdir(const char *, void *, fuse_fill_dir_t, off_t,
        struct fuse_file_info *);

int jfuse_releasedir(const char *, struct fuse_file_info *);

int jfuse_fsyncdir(const char *, int, struct fuse_file_info *);

void *jfuse_init(struct fuse_conn_info *conn);

void jfuse_destroy(void *);

int jfuse_access(const char *, int);

int jfuse_create(const char *, mode_t, struct fuse_file_info *);

int jfuse_ftruncate(const char *, off_t, struct fuse_file_info *);

int jfuse_fgetattr(const char *, struct stat *, struct fuse_file_info *);

int jfuse_lock(const char *, struct fuse_file_info *, int cmd,
        struct flock *);

int jfuse_utimens(const char *, const struct timespec tv[2]);

int jfuse_bmap(const char *, size_t blocksize, uint64_t *idx);

#define handleError(...) CSPanicWithMessage("%s(%d): Unspecified panic condition.", __FILE__, __LINE__)

static inline jFUSEContext* getjFUSEContext() {
    struct fuse_context *fuse_ctx = fuse_get_context();
    return (jFUSEContext*)fuse_ctx->private_data;
}

/*
#define JAVA_ARG_CSTRING(num, str) \
    CSLogDebug("Processing argument %d (%s) of type byte array (from C string)...", num, #str); \
    jbyteArray java_arg##num = JNIUtil::cstringToJByteArray(env, str); \
    if(java_arg##num == NULL) { \
        if(env->ExceptionCheck() == JNI_TRUE) \
            env->ExceptionDescribe(); \
        CSPanicWithMessage("Could not create new Java byte array from C string \"%s\".", str); \
    }
*/
#define JAVA_ARG_CSTRING_BYTEBUFFER(num, str) \
    CSLogDebug("Processing argument %d (%s) of type read-only ByteBuffer (from C string)...", num, #str); \
    jobject java_arg##num; \
    if(str == NULL) \
        java_arg##num = NULL; \
    else { \
        java_arg##num = JNIUtil::cstringToReadonlyByteBuffer(env, str); \
        if(java_arg##num == NULL) { \
            if(env->ExceptionCheck() == JNI_TRUE) \
                env->ExceptionDescribe(); \
            CSPanicWithMessage("Could not create new Java read-only ByteBuffer from C string \"%s\".", str); \
        } \
    }

/*
#define JAVA_ARG_EMPTY_BYTE_ARRAY(num, len) \
    CSLogDebug("Processing argument %d (%s) of type (new) byte array...", num, #len); \
    jbyteArray java_arg##num = env->NewByteArray(len); \
    if(java_arg##num == NULL) { \
        if(env->ExceptionCheck() == JNI_TRUE) \
            env->ExceptionDescribe(); \
        CSPanicWithMessage("Could not create new Java byte array for java_arg" #num "."); \
    }
*/

#define JAVA_ARG_EMPTY_BYTEBUFFER(num, len) \
    CSLogDebug("Processing argument %d (%s) of type (new) ByteBuffer...", num, #len); \
    jobject java_arg##num = JNIUtil::newByteBuffer(env, len); \
    if(java_arg##num == NULL) { \
        if(env->ExceptionCheck() == JNI_TRUE) \
            env->ExceptionDescribe(); \
        CSPanicWithMessage("Could not create new Java ByteBuffer for java_arg" #num "."); \
    }

/*
#define JAVA_ARG_BYTE_ARRAY(num, buf, len) \
    CSLogDebug("Processing argument %d (%s) of type byte array...", num, #buf); \
    jbyteArray java_arg##num = JNIUtil::bytesToJByteArray(env, buf, len); \
    if(java_arg##num == NULL) { \
        if(env->ExceptionCheck() == JNI_TRUE) \
            env->ExceptionDescribe(); \
        CSPanicWithMessage("Could not create new Java byte array from char* buffer."); \
    }
 */

#define JAVA_ARG_BYTEBUFFER(num, buf, len) \
    CSLogDebug("Processing argument %d (%s) of type ByteByffer...", num, #buf); \
    jobject java_arg##num; \
    if(buf == NULL) \
        java_arg##num = NULL; \
    else { \
        java_arg##num = JNIUtil::bytesToByteBuffer(env, buf, len); \
        if(java_arg##num == NULL) { \
            if(env->ExceptionCheck() == JNI_TRUE) \
                env->ExceptionDescribe(); \
            CSPanicWithMessage("Could not create new Java ByteBuffer from char* buffer."); \
        } \
    }

#define JAVA_ARG_READONLY_BYTEBUFFER(num, buf, len) \
    CSLogDebug("Processing argument %d (%s) of type ByteByffer (read-only)...", num, #buf); \
    jobject java_arg##num; \
    if(buf == NULL) \
        java_arg##num = NULL; \
    else { \
        java_arg##num = JNIUtil::bytesToReadonlyByteBuffer(env, buf, len); \
        if(java_arg##num == NULL) { \
            if(env->ExceptionCheck() == JNI_TRUE) \
                env->ExceptionDescribe(); \
            CSPanicWithMessage("Could not create new Java read-only ByteBuffer from const char* buffer."); \
        } \
    }

#define JAVA_ARG_STAT(num, stbuf) \
    CSLogDebug("Processing argument %d (%s) of type struct stat...", num, #stbuf); \
    jobject java_arg##num = FUSE26Util::newStat(env, stbuf); \
    if(java_arg##num == NULL) { \
        if(env->ExceptionCheck() == JNI_TRUE) \
            env->ExceptionDescribe(); \
        CSPanicWithMessage("Could not create new Java Stat object from stat buffer."); \
    }

#define JAVA_ARG_FUSE_FILE_INFO(num, fi) \
    CSLogDebug("Processing argument %d (%s) of type struct fuse_file_info...", num, #fi); \
    jobject java_arg##num = FUSE26Util::newFUSEFileInfo(env, fi); \
    if(java_arg##num == NULL) { \
        if(env->ExceptionCheck() == JNI_TRUE) \
            env->ExceptionDescribe(); \
        CSPanicWithMessage("Could not create new FUSEFileInfo."); \
    }

#define JAVA_ARG_FLOCK(num, flk) \
    CSLogDebug("Processing argument %d (%s) of type struct flock...", num, #flk); \
    jobject java_arg##num = FUSE26Util::newFlock(env, flk); \
    if(java_arg##num == NULL) { \
        if(env->ExceptionCheck() == JNI_TRUE) \
            env->ExceptionDescribe(); \
        CSPanicWithMessage("Could not create new Flock."); \
    }

#define JAVA_ARG_FUSE_FILL_DIR(num, filler, buf) \
    CSLogDebug("Processing argument %d (%s) of type fuse_fill_dir_t...", num, #filler); \
    jobject java_arg##num = FUSE26Util::newFUSEFillDir(env, filler, buf); \
    if(java_arg##num == NULL) { \
        if(env->ExceptionCheck() == JNI_TRUE) \
            env->ExceptionDescribe(); \
        CSPanicWithMessage("Could not create new FUSEFillDir."); \
    }

#define JAVA_ARG_FUSE_DIRFIL(num, dirfil, dirh) \
    CSLogDebug("Processing argument %d (%s) of type fuse_dirfil_t...", num, #dirfil); \
    jobject java_arg##num = FUSE26Util::newFUSEDirFil(env, dirfil, dirh); \
    if(java_arg##num == NULL) { \
        if(env->ExceptionCheck() == JNI_TRUE) \
            env->ExceptionDescribe(); \
        CSPanicWithMessage("Could not create new FUSEDirFil."); \
    }

#define JAVA_ARG_TIMESPEC(num, ts) \
    CSLogDebug("Processing argument %d (%s) of type struct timespec...", num, #ts); \
    jobject java_arg##num = FUSE26Util::newTimespec(env, ts); \
    if(java_arg##num == NULL) { \
        if(env->ExceptionCheck() == JNI_TRUE) \
            env->ExceptionDescribe(); \
        CSPanicWithMessage("Could not create new Timespec."); \
    }

#define JAVA_ARG_LONGREF(num, lr) \
    CSLogDebug("Processing argument %d (%s) of type uint64_t*...", num, #lr); \
    jobject java_arg##num = FUSE26Util::newLongRef(env, lr); \
    if(java_arg##num == NULL) { \
        if(env->ExceptionCheck() == JNI_TRUE) \
            env->ExceptionDescribe(); \
        CSPanicWithMessage("Could not create new LongRef."); \
    }

#define JAVA_ARG_FUSE_CONN_INFO(num, conn) \
    CSLogDebug("Processing argument %d (%s) of type struct fuse_conn_info...", num, #conn); \
    jobject java_arg##num = FUSE26Util::newFUSEConnInfo(env, conn); \
    if(java_arg##num == NULL) { \
        if(env->ExceptionCheck() == JNI_TRUE) \
            env->ExceptionDescribe(); \
        CSPanicWithMessage("Could not create new FUSEConnInfo."); \
    }

#define JAVA_ARG_UTIMBUF(num, time) \
    CSLogDebug("Processing argument %d (%s) of type struct utimbuf...", num, #time); \
    jobject java_arg##num = FUSE26Util::newUtimbuf(env, time); \
    if(java_arg##num == NULL) { \
        if(env->ExceptionCheck() == JNI_TRUE) \
            env->ExceptionDescribe(); \
        CSPanicWithMessage("Could not create new Utimbuf."); \
    }

#define JAVA_ARG_STATVFS(num, stvfsbuf) \
    CSLogDebug("Processing argument %d (%s) of type struct statvfs...", num, #stvfsbuf); \
    jobject java_arg##num = FUSE26Util::newStatVFS(env, stvfsbuf); \
    if(java_arg##num == NULL) { \
        if(env->ExceptionCheck() == JNI_TRUE) \
            env->ExceptionDescribe(); \
        CSPanicWithMessage("Could not create new StatVFS."); \
    }

#define JAVA_ARG_CLEANUP(num) \
    env->DeleteLocalRef(java_arg##num)

#define JAVA_ARG(num) java_arg##num

#define JAVA_EXCEPTION_CHECK(operation_name) \
    if(env->ExceptionCheck() == JNI_TRUE) { \
        CSLogError("Exception occurred when executing " #operation_name "."); \
        env->ExceptionDescribe(); \
        env->ExceptionClear(); \
    }

#define JFUSE_FS_PROVIDER_MID_OK(name, signature) \
    jmethodID fsProviderMid = context->getFSProviderMethod(name, signature); \
    if(fsProviderMid == NULL || env->ExceptionCheck() == JNI_TRUE) { \
        CSLogError("Could not getFSProviderMethod for \"%s\" with signature %s", \
                name, signature); \
    } \
    else

#define JFUSE_FS_PROVIDER_METHOD_OK(const_name) \
    JFUSE_FS_PROVIDER_MID_OK(OPS_##const_name##_NAME, OPS_##const_name##_SIGNATURE)

#define JFUSE_FS_PROVIDER_MID fsProviderMid

#define JFUSE_MERGE_STAT(stat_object, stbuf) \
        if(env->ExceptionCheck() == JNI_FALSE) { \
            if(!FUSE26Util::mergeStat(env, stat_object, stbuf)) \
                CSPanicWithMessage("Could not merge Stat -> struct stat"); \
        }

#define JFUSE_MERGE_FUSE_FILE_INFO(ffi_object, fi) \
        if(env->ExceptionCheck() == JNI_FALSE) { \
            if (!FUSE26Util::mergeFUSEFileInfo(env, ffi_object, fi)) \
                CSPanicWithMessage("Could not merge FUSEFileInfo -> struct fuse_file_info"); \
        }

#define JFUSE_MERGE_FLOCK(flock_object, flk) \
        if(env->ExceptionCheck() == JNI_FALSE) { \
            if (!FUSE26Util::mergeFlock(env, flock_object, flk)) \
                CSPanicWithMessage("Could not merge Flock -> struct flock"); \
        }

#define JFUSE_MERGE_LONGREF(lr_object, lr) \
        if(env->ExceptionCheck() == JNI_FALSE) { \
            if (!FUSE26Util::mergeLongRef(env, lr_object, lr)) \
                CSPanicWithMessage("Could not merge LongRef -> uint64_t*"); \
        }

#define JFUSE_MERGE_UTIMBUF(time_object, timebuf) \
        if(env->ExceptionCheck() == JNI_FALSE) { \
            if (!FUSE26Util::mergeUtimbuf(env, time_object, timebuf)) \
                CSPanicWithMessage("Could not merge Utimbuf -> struct utimbuf"); \
        }

#define JFUSE_MERGE_STATVFS(statvfs_object, statvfsbuf) \
        if(env->ExceptionCheck() == JNI_FALSE) { \
            if (!FUSE26Util::mergeStatVFS(env, statvfs_object, statvfsbuf)) \
                CSPanicWithMessage("Could not merge StatVFS -> struct statvfs"); \
        }

#define JFUSE_MERGE_TIMESPEC(timespec_object, timespecbuf) \
        if(env->ExceptionCheck() == JNI_FALSE) { \
            if (!FUSE26Util::mergeTimespec(env, timespec_object, timespecbuf)) \
                CSPanicWithMessage("Could not merge Timespec -> struct timespec"); \
        }

#define JFUSE_MERGE_BYTE_ARRAY(javabuf, cbuf, cbuf_len) \
        if(env->ExceptionCheck() == JNI_FALSE) { \
            env->GetByteArrayRegion(javabuf, 0, cbuf_len, (signed char*) (cbuf)); \
        }

#define JFUSE_SET_RETVAL() \
        if(env->ExceptionCheck() == JNI_FALSE) \
            retval = jretval;

#define JFUSE_OPERATION_INIT() \
        jFUSEContext *context = getjFUSEContext(); \
        JNIEnv *env = context->getJNIEnv(); \
        jobject obj = context->getFSProvider();

#define JFUSE_FS_PROVIDER_CALL(...) \
        jint jretval = env->CallIntMethod(obj, JFUSE_FS_PROVIDER_MID, __VA_ARGS__);

#define JFUSE_FS_INIT_CALL(...) \
        jobject jretval = env->CallObjectMethod(obj, JFUSE_FS_PROVIDER_MID, __VA_ARGS__);

#define JFUSE_FS_DESTROY_CALL(...) \
        env->CallVoidMethod(obj, JFUSE_FS_PROVIDER_MID, __VA_ARGS__);

#define JFUSE_HANDLE_INIT_RETVAL() \
        if(env->ExceptionCheck() == JNI_FALSE) { \
            context->setPrivateData(jretval); \
            if(jretval != NULL) \
                env->DeleteLocalRef(jretval); \
        }

#endif	/* _FUSE_MODULE_H */

