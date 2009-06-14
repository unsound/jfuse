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

static inline jFUSEContext* getjFUSEContext() {
    struct fuse_context *fuse_ctx = fuse_get_context();
    return (jFUSEContext*)fuse_ctx->private_data;
}

int jfuse_getattr(const char *path, struct stat *stbuf) {
    CSLogTraceEnter("int jfuse_getattr(%p, %p)",
            path, stbuf);
    CSLogTrace("  path=\"%s\"", path);

    if(false) {
        memset(stbuf, 0, sizeof (struct stat));

        if (strcmp(path, "/") == 0) { /* The root directory of our file system. */
            stbuf->st_mode = S_IFDIR | 0755;
            stbuf->st_nlink = 3;
        } else { /* We reject everything else. */
            return -ENOENT;
        }

        return 0;
    }

    int retval = -EIO;

    jFUSEContext *context = getjFUSEContext();

    JNIEnv *env = context->getJNIEnv();
    jobject obj = context->getFSProvider();

    // Argument 1: path
    int pathlen = strlen(path);
    jbyteArray pathJava = env->NewByteArray(pathlen); // <alloc>
    if(pathJava == NULL || env->ExceptionCheck() == JNI_TRUE)
        CSPanicWithMessage("Could not create new byte array with length %d", pathlen);

    env->SetByteArrayRegion(pathJava, 0, pathlen, (const signed char*) path);
    if(env->ExceptionCheck() == JNI_TRUE)
        CSPanicWithMessage("Could not set byte array region with length %d to \"%s\"", pathlen, path);


    // Argument 2: stbuf
    jclass statClass = env->FindClass(STAT_CLASS);
    if(statClass == NULL || env->ExceptionCheck() == JNI_TRUE)
        CSPanicWithMessage("Could not find class \"%s\"", STAT_CLASS);

    jmethodID statConstructor = env->GetMethodID(statClass, STAT_INIT_NAME, STAT_INIT_SIGNATURE);
    if(statConstructor == NULL || env->ExceptionCheck() == JNI_TRUE)
        CSPanicWithMessage("Could not find constructor Stat.%s with signature %s",
                STAT_INIT_NAME, STAT_INIT_SIGNATURE);

    jobject statInstance = FUSE26Util::newStat(env, stbuf);
    if(statInstance != NULL) {
        jmethodID getattrMID = context->getFSProviderMethod(OPS_GETATTR_NAME, OPS_GETATTR_SIGNATURE);
        if(getattrMID != NULL) {
            jint jretval = env->CallIntMethod(obj, getattrMID, pathJava, statInstance);
            if(env->ExceptionCheck() == JNI_FALSE && FUSE26Util::mergeStat(env, statInstance, stbuf))
                retval = jretval;
        }
        else
            CSLogError("Could not getFSProviderMethod for \"%s\" with signature %s",
                OPS_GETATTR_NAME, OPS_GETATTR_SIGNATURE);

        env->DeleteLocalRef(statInstance);
    }
    else
        CSLogError("Could not create new Stat instance with \"%s\" and signature %s",
            STAT_INIT_NAME, STAT_INIT_SIGNATURE);

    env->DeleteLocalRef(statClass);
    env->DeleteLocalRef(pathJava);

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

    if(true)
        return -ENOENT;

    jFUSEContext *context = getjFUSEContext();

    JNIEnv *env = context->getJNIEnv();
    jobject obj = context->getFSProvider();

    // Argument 1: path
    int pathlen = strlen(path);
    jbyteArray pathJava = env->NewByteArray(pathlen); // <alloc>
    env->SetByteArrayRegion(pathJava, 0, pathlen, (const signed char*)path);

    // Argument 2: fi
    jobject ffiInstance = FUSE26Util::newFUSEFileInfo(env, fi);
    
    jmethodID openMID = context->getFSProviderMethod(OPS_OPEN_NAME, OPS_OPEN_SIGNATURE);
    jint jretval = env->CallIntMethod(obj, openMID, pathJava, ffiInstance);

    // Merge FUSEFileInfo fields into fi
    FUSE26Util::mergeFUSEFileInfo(env, ffiInstance, fi);

    env->DeleteLocalRef(ffiInstance);
    env->DeleteLocalRef(pathJava);

    int retval = -javaErrnoToErrno(jretval);
    CSLogTraceLeave("int jfuse_open(%p, %p): %d",
            path, fi, retval);
    return retval;

}

int jfuse_read(const char *path, char *targetbuf, size_t targetbuf_len, off_t targetbuf_off,
        struct fuse_file_info *fi) {
    CSLogTraceEnter("int jfuse_read(%p, %p, %zu, %" PRId64 ", %p)",
            path, targetbuf, targetbuf_len, targetbuf_off, fi);
    CSLogTrace("  path=\"%s\"", path);

    if(true)
        return -ENOENT;

    jFUSEContext *context = getjFUSEContext();

    JNIEnv *env = context->getJNIEnv();
    jobject obj = context->getFSProvider();

    // Argument 1: path
    int pathlen = strlen(path);
    jbyteArray pathJava = env->NewByteArray(pathlen); // <alloc>
    env->SetByteArrayRegion(pathJava, 0, pathlen, (const signed char*)path);

    // Argument 2-4: targetbuf
    jbyteArray targetArray = env->NewByteArray(targetbuf_len); // <alloc>

    // Argument 5: fi
    jobject ffiInstance = FUSE26Util::newFUSEFileInfo(env, fi); // <alloc>

    jmethodID readMID = context->getFSProviderMethod(OPS_READ_NAME, OPS_READ_SIGNATURE);
    jint jretval = env->CallIntMethod(obj, readMID, pathJava, targetArray,
            0, targetbuf_len, ffiInstance);

    // Merge FUSEFileInfo fields into fi
    FUSE26Util::mergeFUSEFileInfo(env, ffiInstance, fi);

    // Copy data to native buffer
    env->GetByteArrayRegion(targetArray, 0, targetbuf_len, (signed char*)(targetbuf+targetbuf_off));

    env->DeleteLocalRef(ffiInstance); // </alloc>
    env->DeleteLocalRef(targetArray); // </alloc>
    env->DeleteLocalRef(pathJava); // </alloc>

    int retval = -javaErrnoToErrno(jretval);

    CSLogTraceLeave("int jfuse_read(%p, %p, %zu, %" PRId64 ", %p): %d",
            path, targetbuf, targetbuf_len, targetbuf_off, fi, retval);
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

    if(false) {
        // Temp testcode
        if (strcmp(path, "/") != 0) { /* We only recognize the root directory. */
            return -ENOENT;
        }

        filler(buf, ".", NULL, 0); /* Current directory (.)  */
        filler(buf, "..", NULL, 0); /* Parent directory (..)  */

        return 0;
    }
    
    int retval = -EIO;
    jFUSEContext *context = getjFUSEContext();

    JNIEnv *env = context->getJNIEnv();
    jobject obj = context->getFSProvider();

    // Argument 1: path
    CSLogDebug("Processing argument 1 (path)...");
    jbyteArray pathJava = JNIUtil::cstringToJByteArray(env, path);
    if(pathJava == NULL) {
        if(env->ExceptionCheck() == JNI_TRUE)
            env->ExceptionDescribe();
        CSPanicWithMessage("Could not create new Java byte array from string \"%s\".", path);
    }

    // Argument 2: filler
    CSLogDebug("Processing argument 2 (filler)...");
    jobject fillDir = FUSE26Util::createFUSEFillDir(env, filler, buf);
    if(fillDir == NULL) {
        if(env->ExceptionCheck() == JNI_TRUE)
            env->ExceptionDescribe();
        CSPanicWithMessage("Could not create new FUSEFillDir.");
    }

    // Argument 4: fi
    CSLogDebug("Processing argument 4 (fi)...");
    jobject ffiInstance = FUSE26Util::newFUSEFileInfo(env, fi); // <alloc>
    if(fillDir == NULL) {
        if(env->ExceptionCheck() == JNI_TRUE)
            env->ExceptionDescribe();
        CSPanicWithMessage("Could not create new FUSEFileInfo.");
    }

    jmethodID readdirMID = context->getFSProviderMethod(OPS_READDIR_NAME, OPS_READDIR_SIGNATURE);
    if(readdirMID == NULL || env->ExceptionCheck() == JNI_TRUE) {
        CSLogError("Could not getFSProviderMethod for \"%s\" with signature %s",
                OPS_READDIR_NAME, OPS_READDIR_SIGNATURE);
    }
    else {
        jint jretval = env->CallIntMethod(obj, readdirMID, pathJava, fillDir, offset, ffiInstance);

        if(env->ExceptionCheck() == JNI_FALSE) {
            // Merge FUSEFileInfo fields into fi
            FUSE26Util::mergeFUSEFileInfo(env, ffiInstance, fi);
        }

        if(env->ExceptionCheck() == JNI_FALSE) {
            // Return the proper retval.
            retval = jretval;
        }
    }

    env->DeleteLocalRef(ffiInstance); // </alloc>
    env->DeleteLocalRef(pathJava); // </alloc>

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
