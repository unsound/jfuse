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

static int javaErrnoToErrno(jint javaErrno) {
    switch(javaErrno) {
        case 0: return 0; // All is fine.
        case 1: return EPERM;
        case 2: return ENOENT;
        case 3: return ESRCH;
        case 4: return EINTR;
        case 5: return EIO;
        case 6: return ENXIO;
        case 7: return E2BIG;
        case 8: return ENOEXEC;
        case 9: return EBADF;
        case 10: return ECHILD;
        case 11: return EDEADLK;
        case 12: return ENOMEM;
        case 13: return EACCES;
        case 14: return EFAULT;
        case 15: return ENOTBLK;
        case 16: return EBUSY;
        case 17: return EEXIST;
        case 18: return EXDEV;
        case 19: return ENODEV;
        case 20: return ENOTDIR;
        case 21: return EISDIR;
        case 22: return EINVAL;
        case 23: return ENFILE;
        case 24: return EMFILE;
        case 25: return ENOTTY;
        case 26: return ETXTBSY;
        case 27: return EFBIG;
        case 28: return ENOSPC;
        case 29: return ESPIPE;
        case 30: return EROFS;
        case 31: return EMLINK;
        case 32: return EPIPE;
        case 33: return EDOM;
        case 34: return ERANGE;
        case 35: return EAGAIN;
        case 102: return EWOULDBLOCK;
        case 36: return EINPROGRESS;
        case 37: return EALREADY;
        case 38: return ENOTSOCK;
        case 39: return EDESTADDRREQ;
        case 40: return EMSGSIZE;
        case 41: return EPROTOTYPE;
        case 42: return ENOPROTOOPT;
        case 43: return EPROTONOSUPPORT;
        case 44: return ESOCKTNOSUPPORT;
        case 45: return ENOTSUP;
        case 103: return EOPNOTSUPP;
        case 46: return EPFNOSUPPORT;
        case 47: return EAFNOSUPPORT;
        case 48: return EADDRINUSE;
        case 49: return EADDRNOTAVAIL;
        case 50: return ENETDOWN;
        case 51: return ENETUNREACH;
        case 52: return ENETRESET;
        case 53: return ECONNABORTED;
        case 54: return ECONNRESET;
        case 55: return ENOBUFS;
        case 56: return EISCONN;
        case 57: return ENOTCONN;
        case 58: return ESHUTDOWN;
        case 59: return ETOOMANYREFS;
        case 60: return ETIMEDOUT;
        case 61: return ECONNREFUSED;
        case 62: return ELOOP;
        case 63: return ENAMETOOLONG;
        case 64: return EHOSTDOWN;
        case 65: return EHOSTUNREACH;
        case 66: return ENOTEMPTY;
        case 67: return EPROCLIM;
        case 68: return EUSERS;
        case 69: return EDQUOT;
        case 70: return ESTALE;
        case 71: return EREMOTE;
        case 72: return EBADRPC;
        case 73: return ERPCMISMATCH;
        case 74: return EPROGUNAVAIL;
        case 75: return EPROGMISMATCH;
        case 76: return EPROCUNAVAIL;
        case 77: return ENOLCK;
        case 78: return ENOSYS;
        case 79: return EFTYPE;
        case 80: return EAUTH;
        case 81: return ENEEDAUTH;
        case 82: return EPWROFF;
        case 83: return EDEVERR;
        case 84: return EOVERFLOW;
        case 85: return EBADEXEC;
        case 86: return EBADARCH;
        case 87: return ESHLIBVERS;
        case 88: return EBADMACHO;
        case 89: return ECANCELED;
        case 90: return EIDRM;
        case 91: return ENOMSG;
        case 92: return EILSEQ;
        case 93: return ENOATTR;
        case 94: return EBADMSG;
        case 95: return EMULTIHOP;
        case 96: return ENODATA;
        case 97: return ENOLINK;
        case 98: return ENOSR;
        case 99: return ENOSTR;
        case 100: return EPROTO;
        case 101: return ETIME;

        default: return EOPNOTSUPP; // ??
    }
}

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
