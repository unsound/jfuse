#include "fuse26_module.h"

#include "common.h"
#include "JNIUtil.h"
#include "FUSE26Util.h"
#include "CSLog.h"

#include <string.h>
#include <errno.h>
#define __STDC_FORMAT_MACROS
#include <inttypes.h>

#include <fuse.h>
#include <fuse/fuse_common.h>

#include "JavaSignatures.h"

#define handleError(...) CSPanicWithMessage("%s(%d): Unspecified panic condition.", __FILE__, __LINE__)

#define JAVA_ARG_CSTRING(num, str) \
    CSLogDebug("Processing argument %d (%s) of type cstring...", num, #str); \
    jbyteArray java_arg##num = JNIUtil::cstringToJByteArray(env, str); \
    if(java_arg##num == NULL) { \
        if(env->ExceptionCheck() == JNI_TRUE) \
            env->ExceptionDescribe(); \
        CSPanicWithMessage("Could not create new Java byte array from string \"%s\".", str); \
    }

#define JAVA_ARG_EMPTY_BYTE_ARRAY(num, len) \
    CSLogDebug("Processing argument %d (%s) of type byte array...", num, #len); \
    jbyteArray java_arg##num = env->NewByteArray(len); \
    if(java_arg##num == NULL) { \
        if(env->ExceptionCheck() == JNI_TRUE) \
            env->ExceptionDescribe(); \
        CSPanicWithMessage("Could not create new Java byte array for dest."); \
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

#define JAVA_ARG_FUSE_FILL_DIR(num, filler, buf) \
    CSLogDebug("Processing argument %d (%s) of type struct fuse_fill_dir_t...", num, #filler); \
    jobject java_arg##num = FUSE26Util::createFUSEFillDir(env, filler, buf); \
    if(java_arg##num == NULL) { \
        if(env->ExceptionCheck() == JNI_TRUE) \
            env->ExceptionDescribe(); \
        CSPanicWithMessage("Could not create new FUSEFillDir."); \
    }

#define JAVA_ARG_CLEANUP(num) \
    env->DeleteLocalRef(java_arg##num)


static inline jFUSEContext* getjFUSEContext() {
    struct fuse_context *fuse_ctx = fuse_get_context();
    return (jFUSEContext*)fuse_ctx->private_data;
}

int jfuse_getattr(const char *path, struct stat *stbuf) {
    CSLogTraceEnter("int jfuse_getattr(%p, %p)",
            path, stbuf);
    CSLogTrace("  path=\"%s\"", path);

    int retval = -EIO;

    jFUSEContext *context = getjFUSEContext();

    JNIEnv *env = context->getJNIEnv();
    jobject obj = context->getFSProvider();

    JAVA_ARG_CSTRING(1, path);
    JAVA_ARG_STAT(2, stbuf);
    
    jmethodID getattrMID = context->getFSProviderMethod(OPS_GETATTR_NAME, OPS_GETATTR_SIGNATURE);
    if(getattrMID == NULL || env->ExceptionCheck() == JNI_TRUE)
        CSLogError("Could not getFSProviderMethod for \"%s\" with signature %s",
            OPS_GETATTR_NAME, OPS_GETATTR_SIGNATURE);
    else {
        jint jretval = env->CallIntMethod(obj, getattrMID, java_arg1, java_arg2);

        if(env->ExceptionCheck() == JNI_FALSE) {
            if(!FUSE26Util::mergeStat(env, java_arg2, stbuf))
                CSPanicWithMessage("Could not merge Stat -> struct stat");
        }

        if(env->ExceptionCheck() == JNI_FALSE)
            retval = jretval;
    }

    JAVA_ARG_CLEANUP(2);
    JAVA_ARG_CLEANUP(1);
    
    if(env->ExceptionCheck() == JNI_TRUE) {
        CSLogError("Exception occurred when executing jfuse_getattr.");
        env->ExceptionDescribe();
        env->ExceptionClear();
    }

    CSLogTraceLeave("int jfuse_getattr(%p, %p): %d",
                path, stbuf, retval);

    return retval;
}


int jfuse_readlink(const char *path, char *target, size_t target_len) {
    return -ENOTSUP;
}

int jfuse_getdir(const char *path, fuse_dirh_t a, fuse_dirfil_t b) {
    return -ENOTSUP;
}

int jfuse_mknod(const char *path, mode_t a, dev_t b) {
    return -ENOTSUP;
}

int jfuse_mkdir(const char *path, mode_t dirmode) {
    return -ENOTSUP;
}

int jfuse_unlink(const char *path) {
    return -ENOTSUP;
}

int jfuse_rmdir(const char *path) {
    return -ENOTSUP;
}

int jfuse_symlink(const char *from_path, const char *to_path) {
    return -ENOTSUP;
}

int jfuse_rename(const char *from_path, const char *to_path) {
    return -ENOTSUP;
}

int jfuse_link(const char *path, const char *to_path) {
    return -ENOTSUP;
}

int jfuse_chmod(const char *path, mode_t filemode) {
    return -ENOTSUP;
}

int jfuse_chown(const char *path, uid_t uid, gid_t gid) {
    return -ENOTSUP;
}

int jfuse_truncate(const char *path, off_t newsize) {
    return -ENOTSUP;
}

int jfuse_utime(const char *path, struct utimbuf *newtime) {
    return -ENOTSUP;
}

int jfuse_open(const char *path, struct fuse_file_info *fi) {
    CSLogTraceEnter("int jfuse_open(%p, %p)",
            path, fi);
    CSLogTrace("  path=\"%s\"", path);

    if(false)
        return -ENOENT;
    
    int retval = -EIO;
    jFUSEContext *context = getjFUSEContext();

    JNIEnv *env = context->getJNIEnv();
    jobject obj = context->getFSProvider();

    JAVA_ARG_CSTRING(1, path);
    JAVA_ARG_FUSE_FILE_INFO(2, fi);

    jmethodID openMID = context->getFSProviderMethod(OPS_OPEN_NAME, OPS_OPEN_SIGNATURE);
    if(openMID == NULL || env->ExceptionCheck() == JNI_TRUE) {
        CSLogError("Could not getFSProviderMethod for \"%s\" with signature %s",
                OPS_OPEN_NAME, OPS_OPEN_SIGNATURE);
    }
    else {
        jint jretval = env->CallIntMethod(obj, openMID, java_arg1, java_arg2);

        if(env->ExceptionCheck() == JNI_FALSE) {
            // Merge FUSEFileInfo fields into fi
            if(!FUSE26Util::mergeFUSEFileInfo(env, java_arg2, fi))
                CSPanicWithMessage("Could not merge FUSEFileInfo -> struct fuse_file_info");
        }

        if(env->ExceptionCheck() == JNI_FALSE) {
            // Return the proper retval.
            retval = jretval;
        }
    }

    JAVA_ARG_CLEANUP(2);
    JAVA_ARG_CLEANUP(1);

    if(env->ExceptionCheck() == JNI_TRUE) {
        CSLogError("Exception occurred when executing jfuse_open.");
        env->ExceptionDescribe();
        env->ExceptionClear();
    }

    CSLogTraceLeave("int jfuse_open(%p, %p): %d",
            path, fi, retval);
    return retval;

}

int jfuse_read(const char *path, char *targetbuf, size_t targetbuf_len, off_t file_off,
        struct fuse_file_info *fi) {
    CSLogTraceEnter("int jfuse_read(%p, %p, %zu, %" PRId64 ", %p)",
            path, targetbuf, targetbuf_len, file_off, fi);
    CSLogTrace("  path=\"%s\"", path);

    if(false)
        return -ENOENT;

    int retval = -EIO;
    jFUSEContext *context = getjFUSEContext();

    JNIEnv *env = context->getJNIEnv();
    jobject obj = context->getFSProvider();

    JAVA_ARG_CSTRING(1, path);

    // Argument 2: dest
    /*
    CSLogDebug("Processing argument 3, 4 (targetbuf, targetbuf_len)...");
    jbyteArray targetArray = env->NewByteArray(targetbuf_len); // <alloc>
    if(targetArray == NULL) {
        if(env->ExceptionCheck() == JNI_TRUE)
            env->ExceptionDescribe();
        CSPanicWithMessage("Could not create new Java byte array for dest.");
    }
    */
    JAVA_ARG_EMPTY_BYTE_ARRAY(2, targetbuf_len);

    JAVA_ARG_FUSE_FILE_INFO(5, fi);

    jmethodID readMID = context->getFSProviderMethod(OPS_READ_NAME, OPS_READ_SIGNATURE);
    if(readMID == NULL || env->ExceptionCheck() == JNI_TRUE) {
        CSLogError("Could not getFSProviderMethod for \"%s\" with signature %s",
                OPS_READ_NAME, OPS_READ_SIGNATURE);
    }
    else {
        jint jretval = env->CallIntMethod(obj, readMID, java_arg1, java_arg2,
                targetbuf_len, file_off, java_arg5);

        if(env->ExceptionCheck() == JNI_FALSE) {
            // Merge FUSEFileInfo fields into fi
            if(!FUSE26Util::mergeFUSEFileInfo(env, java_arg5, fi))
                CSPanicWithMessage("Could not merge FUSEFileInfo -> struct fuse_file_info");
        }

        if(env->ExceptionCheck() == JNI_FALSE) {
            // Copy data to native buffer
            env->GetByteArrayRegion(java_arg2, 0, targetbuf_len, (signed char*) (targetbuf));
        }

        if(env->ExceptionCheck() == JNI_FALSE) {
            // Return the proper retval.
            retval = jretval;
        }
    }

    JAVA_ARG_CLEANUP(5);
    JAVA_ARG_CLEANUP(2);
    JAVA_ARG_CLEANUP(1);

    if(env->ExceptionCheck() == JNI_TRUE) {
        CSLogError("Exception occurred when executing jfuse_read.");
        env->ExceptionDescribe();
        env->ExceptionClear();
    }

    CSLogTraceLeave("int jfuse_read(%p, %p, %zu, %" PRId64 ", %p): %d",
            path, targetbuf, targetbuf_len, file_off, fi, retval);
    return retval;
}

int jfuse_write(const char *path, const char *sourcebuf,
        size_t sourcebuf_len, off_t sourcebuf_off,
        struct fuse_file_info *fi) {
    return -ENOTSUP;
}

int jfuse_statfs(const char *path, struct statvfs *stvfsbuf) {
    return -ENOTSUP;
}

int jfuse_flush(const char *path, struct fuse_file_info *fi) {
    return -ENOTSUP;
}

int jfuse_release(const char *path, struct fuse_file_info *fi) {
    return -ENOTSUP;
}

int jfuse_fsync(const char *path, int, struct fuse_file_info *fi) {
    return -ENOTSUP;
}

#if (__FreeBSD__ >= 10)

int jfuse_setxattr(const char *path, const char *name, const char *value,
        size_t value_size, int flags, uint32_t position) {
    return -ENOTSUP;
}
#else

int jfuse_setxattr(const char *path, const char *name, const char *value,
        size_t value_size, int flags) {
    return -ENOTSUP;
}
#endif /* __FreeBSD__ >= 10 */

#if (__FreeBSD__ >= 10)

int jfuse_getxattr(const char *path, const char *name, char *value,
        size_t value_size, uint32_t position) {
    return -ENOTSUP;
}
#else

int jfuse_getxattr(const char *path, const char *name, char *value,
        size_t value_size) {
    return -ENOTSUP;
}
#endif /* __FreeBSD__ >= 10 */

int jfuse_listxattr(const char *path, char *namebuf, size_t namebuf_len) {
    return -ENOTSUP;
}

int jfuse_removexattr(const char *path, const char *name) {
    return -ENOTSUP;
}

int jfuse_opendir(const char *path, struct fuse_file_info *fi) {
    return -ENOTSUP;
}

int jfuse_readdir(const char *path, void *buf, fuse_fill_dir_t filler,
        off_t offset, struct fuse_file_info *fi) {
    
    CSLogTraceEnter("int jfuse_readdir(%p, %p, %p, %" PRId64 ", %p)",
            path, buf, filler, offset, fi);
    CSLogTrace("  path=\"%s\"", path);
    
    int retval = -EIO;
    jFUSEContext *context = getjFUSEContext();

    JNIEnv *env = context->getJNIEnv();
    jobject obj = context->getFSProvider();

    JAVA_ARG_CSTRING(1, path);

    JAVA_ARG_FUSE_FILL_DIR(2, filler, buf);
    
    JAVA_ARG_FUSE_FILE_INFO(4, fi);

    jmethodID readdirMID = context->getFSProviderMethod(OPS_READDIR_NAME, OPS_READDIR_SIGNATURE);
    if(readdirMID == NULL || env->ExceptionCheck() == JNI_TRUE) {
        CSLogError("Could not getFSProviderMethod for \"%s\" with signature %s",
                OPS_READDIR_NAME, OPS_READDIR_SIGNATURE);
    }
    else {
        jint jretval = env->CallIntMethod(obj, readdirMID, java_arg1, java_arg2, offset, java_arg4);

        if(env->ExceptionCheck() == JNI_FALSE) {
            // Merge FUSEFileInfo fields into fi
            if(!FUSE26Util::mergeFUSEFileInfo(env, java_arg4, fi))
                CSPanicWithMessage("Could not merge FUSEFileInfo -> struct fuse_file_info");
        }

        if(env->ExceptionCheck() == JNI_FALSE) {
            // Return the proper retval.
            retval = jretval;
        }
    }

    JAVA_ARG_CLEANUP(4);
    JAVA_ARG_CLEANUP(2);
    JAVA_ARG_CLEANUP(1);

    if(env->ExceptionCheck() == JNI_TRUE) {
        CSLogError("Exception occurred when executing jfuse_readdir.");
        env->ExceptionDescribe();
        env->ExceptionClear();
    }

    CSLogTraceLeave("int jfuse_readdir(%p, %p, %p, %" PRId64 ", %p): %d",
            path, buf, filler, offset, fi, retval);
    return retval;
}

int jfuse_releasedir(const char *path, struct fuse_file_info *fi) {
    return -ENOTSUP;
}

int jfuse_fsyncdir(const char *path, int, struct fuse_file_info *fi) {
    return -ENOTSUP;
}

void* jfuse_init(struct fuse_conn_info *conn) {
    return NULL;
}

void jfuse_destroy(void *) {
    return;
}

int jfuse_access(const char *path, int) {
    return -ENOTSUP;
}

int jfuse_create(const char *path, mode_t, struct fuse_file_info *fi) {
    return -ENOTSUP;
}

int jfuse_ftruncate(const char *path, off_t, struct fuse_file_info *fi) {
    return -ENOTSUP;
}

int jfuse_fgetattr(const char *path, struct stat *, struct fuse_file_info *fi) {
    return -ENOTSUP;
}

int jfuse_lock(const char *path, struct fuse_file_info *fi, int cmd,
        struct flock *) {
    return -ENOTSUP;
}

int jfuse_utimens(const char *path, const struct timespec tv[2]) {
    return -ENOTSUP;
}

int jfuse_bmap(const char *path, size_t blocksize, uint64_t *idx) {
    return -ENOTSUP;
}

#if (__FreeBSD__ >= 10)

// Implement these MacFUSE callbacks some time in the future.
/*
int jfuse_setvolname(const char *name) {
}

int jfuse_exchange(const char *, const char *, unsigned long) {
}

int jfuse_getxtimes(const char *, struct timespec *bkuptime,
        struct timespec *crtime) {
}

int jfuse_setbkuptime(const char *, const struct timespec *tv) {
}

int jfuse_setchgtime(const char *, const struct timespec *tv) {
}

int jfuse_setcrtime(const char *, const struct timespec *tv) {
}

int jfuse_chflags(const char *, uint32_t) {
}

int jfuse_setattr_x(const char *, struct setattr_x *) {
}

int jfuse_fsetattr_x(const char *, struct setattr_x *,
        struct fuse_file_info *fi) {
}
*/

#endif /* __FreeBSD__ >= 10 */
