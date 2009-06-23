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
#include <fuse/fuse.h>

#include "JavaSignatures.h"

#define handleError(...) CSPanicWithMessage("%s(%d): Unspecified panic condition.", __FILE__, __LINE__)

static inline jFUSEContext* getjFUSEContext() {
    struct fuse_context *fuse_ctx = fuse_get_context();
    return (jFUSEContext*)fuse_ctx->private_data;
}

#define JAVA_ARG_CSTRING(num, str) \
    CSLogDebug("Processing argument %d (%s) of type cstring...", num, #str); \
    jbyteArray java_arg##num = JNIUtil::cstringToJByteArray(env, str); \
    if(java_arg##num == NULL) { \
        if(env->ExceptionCheck() == JNI_TRUE) \
            env->ExceptionDescribe(); \
        CSPanicWithMessage("Could not create new Java byte array from string \"%s\".", str); \
    }

#define JAVA_ARG_EMPTY_BYTE_ARRAY(num, len) \
    CSLogDebug("Processing argument %d (%s) of type (new) byte array...", num, #len); \
    jbyteArray java_arg##num = env->NewByteArray(len); \
    if(java_arg##num == NULL) { \
        if(env->ExceptionCheck() == JNI_TRUE) \
            env->ExceptionDescribe(); \
        CSPanicWithMessage("Could not create new Java byte array for dest."); \
    }

#define JAVA_ARG_BYTE_ARRAY(num, buf, len) \
    CSLogDebug("Processing argument %d (%s) of type byte array...", num, #buf); \
    jbyteArray java_arg##num = JNIUtil::bytesToJByteArray(env, buf, len); \
    if(java_arg##num == NULL) { \
        if(env->ExceptionCheck() == JNI_TRUE) \
            env->ExceptionDescribe(); \
        CSPanicWithMessage("Could not create new Java byte array from char* buffer."); \
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


int jfuse_getattr(const char *path, struct stat *stbuf) {
    CSLogTraceEnter("int jfuse_getattr(%p, %p)",
            path, stbuf);
    CSLogTrace("  path=\"%s\"", path);

    int retval = -EIO;
    JFUSE_OPERATION_INIT();
    JAVA_ARG_CSTRING(1, path);
    JAVA_ARG_STAT(2, stbuf);

    JFUSE_FS_PROVIDER_MID_OK(OPS_GETATTR_NAME, OPS_GETATTR_SIGNATURE) {
        JFUSE_FS_PROVIDER_CALL(JAVA_ARG(1), JAVA_ARG(2));

        JFUSE_MERGE_STAT(JAVA_ARG(2), stbuf);

        JFUSE_SET_RETVAL();
    }

    JAVA_ARG_CLEANUP(2);
    JAVA_ARG_CLEANUP(1);

    JAVA_EXCEPTION_CHECK("jfuse_getattr");

    CSLogTraceLeave("int jfuse_getattr(%p, %p): %d",
                path, stbuf, retval);

    return retval;
}


int jfuse_readlink(const char *path, char *target, size_t target_len) {
    CSLogTraceEnter("int jfuse_readlink(%p, %p, %zd)", path, target, target_len);
    CSLogTrace("  path=\"%s\"", path);

    int retval = -EIO;
    JFUSE_OPERATION_INIT();

    JAVA_ARG_CSTRING(1, path);
    JAVA_ARG_BYTE_ARRAY(2, target, target_len);

    JFUSE_FS_PROVIDER_METHOD_OK(READLINK) {
        JFUSE_FS_PROVIDER_CALL(JAVA_ARG(1), JAVA_ARG(2));

        JFUSE_MERGE_BYTE_ARRAY(JAVA_ARG(2), target, target_len);

        JFUSE_SET_RETVAL();
    }

    JAVA_ARG_CLEANUP(2);
    JAVA_ARG_CLEANUP(1);

    JAVA_EXCEPTION_CHECK("jfuse_readlink");

    CSLogTraceLeave("int jfuse_readlink(%p, %p, %zd): %d",
                path, target, target_len, retval);
    return retval;
}

int jfuse_getdir(const char *path, fuse_dirh_t dirh, fuse_dirfil_t dirfil) {
    CSLogTraceEnter("int jfuse_getdir(%p, %p, %p)", path, dirh, dirfil);
    CSLogTrace("  path=\"%s\"", path);

    int retval = -EIO;
    JFUSE_OPERATION_INIT();

    JAVA_ARG_CSTRING(1, path);
    JAVA_ARG_FUSE_DIRFIL(2, dirfil, dirh);

    JFUSE_FS_PROVIDER_METHOD_OK(GETDIR) {
        JFUSE_FS_PROVIDER_CALL(JAVA_ARG(1), JAVA_ARG(2));

        JFUSE_SET_RETVAL();
    }

    JAVA_ARG_CLEANUP(2);
    JAVA_ARG_CLEANUP(1);

    JAVA_EXCEPTION_CHECK("jfuse_getdir");

    CSLogTraceLeave("int jfuse_getdir(%p, %p, %p): %d",
                path, dirh, dirfil, retval);
    return retval;
}

int jfuse_mknod(const char *path, mode_t mode, dev_t dev) {
    CSLogTraceEnter("int jfuse_mknod(%p, %d, %d)", path, mode, dev);
    CSLogTrace("  path=\"%s\"", path);

    int retval = -EIO;
    JFUSE_OPERATION_INIT();

    JAVA_ARG_CSTRING(1, path);

    JFUSE_FS_PROVIDER_METHOD_OK(MKNOD) {
        JFUSE_FS_PROVIDER_CALL(JAVA_ARG(1), (jshort)mode, (jlong)dev);

        JFUSE_SET_RETVAL();
    }

    JAVA_ARG_CLEANUP(1);

    JAVA_EXCEPTION_CHECK("jfuse_mknod");

    CSLogTraceLeave("int jfuse_mknod(%p, %d, %d): %d",
                path, mode, dev, retval);
    return retval;
}

int jfuse_mkdir(const char *path, mode_t mode) {
    CSLogTraceEnter("int jfuse_mkdir(%p, %d)", path, mode);
    CSLogTrace("  path=\"%s\"", path);

    int retval = -EIO;
    JFUSE_OPERATION_INIT();

    JAVA_ARG_CSTRING(1, path);

    JFUSE_FS_PROVIDER_METHOD_OK(MKDIR) {
        JFUSE_FS_PROVIDER_CALL(JAVA_ARG(1), (jshort)mode);

        JFUSE_SET_RETVAL();
    }

    JAVA_ARG_CLEANUP(1);

    JAVA_EXCEPTION_CHECK("jfuse_mkdir");

    CSLogTraceLeave("int jfuse_mkdir(%p, %d): %d",
                path, mode, retval);
    return retval;
}

int jfuse_unlink(const char *path) {
    CSLogTraceEnter("int jfuse_unlink(%p)", path);
    CSLogTrace("  path=\"%s\"", path);

    int retval = -EIO;
    JFUSE_OPERATION_INIT();

    JAVA_ARG_CSTRING(1, path);

    JFUSE_FS_PROVIDER_METHOD_OK(UNLINK) {
        JFUSE_FS_PROVIDER_CALL(JAVA_ARG(1));

        JFUSE_SET_RETVAL();
    }

    JAVA_ARG_CLEANUP(1);

    JAVA_EXCEPTION_CHECK("jfuse_unlink");

    CSLogTraceLeave("int jfuse_unlink(%p): %d",
                path, retval);
    return retval;
}

int jfuse_rmdir(const char *path) {
    CSLogTraceEnter("int jfuse_rmdir(%p)", path);
    CSLogTrace("  path=\"%s\"", path);

    int retval = -EIO;
    JFUSE_OPERATION_INIT();

    JAVA_ARG_CSTRING(1, path);

    JFUSE_FS_PROVIDER_METHOD_OK(RMDIR) {
        JFUSE_FS_PROVIDER_CALL(JAVA_ARG(1));

        JFUSE_SET_RETVAL();
    }

    JAVA_ARG_CLEANUP(1);

    JAVA_EXCEPTION_CHECK("jfuse_rmdir");

    CSLogTraceLeave("int jfuse_rmdir(%p): %d",
                path, retval);
    return retval;
}

int jfuse_symlink(const char *from_path, const char *to_path) {
    CSLogTraceEnter("int jfuse_symlink(%p, %p)", from_path, to_path);
    CSLogTrace("  from_path=\"%s\"", from_path);
    CSLogTrace("  to_path=\"%s\"", to_path);

    int retval = -EIO;
    JFUSE_OPERATION_INIT();

    JAVA_ARG_CSTRING(1, from_path);
    JAVA_ARG_CSTRING(2, to_path);

    JFUSE_FS_PROVIDER_METHOD_OK(SYMLINK) {
        JFUSE_FS_PROVIDER_CALL(JAVA_ARG(1), JAVA_ARG(2));

        JFUSE_SET_RETVAL();
    }

    JAVA_ARG_CLEANUP(2);
    JAVA_ARG_CLEANUP(1);

    JAVA_EXCEPTION_CHECK("jfuse_symlink");

    CSLogTraceLeave("int jfuse_symlink(%p, %p): %d",
                from_path, to_path, retval);
    return retval;
}

int jfuse_rename(const char *from_path, const char *to_path) {
    CSLogTraceEnter("int jfuse_rename(%p, %p)", from_path, to_path);
    CSLogTrace("  from_path=\"%s\"", from_path);
    CSLogTrace("  to_path=\"%s\"", to_path);

    int retval = -EIO;
    JFUSE_OPERATION_INIT();

    JAVA_ARG_CSTRING(1, from_path);
    JAVA_ARG_CSTRING(2, to_path);

    JFUSE_FS_PROVIDER_METHOD_OK(RENAME) {
        JFUSE_FS_PROVIDER_CALL(JAVA_ARG(1), JAVA_ARG(2));

        JFUSE_SET_RETVAL();
    }

    JAVA_ARG_CLEANUP(2);
    JAVA_ARG_CLEANUP(1);

    JAVA_EXCEPTION_CHECK("jfuse_rename");

    CSLogTraceLeave("int jfuse_rename(%p, %p): %d",
                from_path, to_path, retval);
    return retval;
}

int jfuse_link(const char *from_path, const char *to_path) {
    CSLogTraceEnter("int jfuse_link(%p, %p)", from_path, to_path);
    CSLogTrace("  from_path=\"%s\"", from_path);
    CSLogTrace("  to_path=\"%s\"", to_path);

    int retval = -EIO;
    JFUSE_OPERATION_INIT();

    JAVA_ARG_CSTRING(1, from_path);
    JAVA_ARG_CSTRING(2, to_path);

    JFUSE_FS_PROVIDER_MID_OK(OPS_LINK_NAME, OPS_LINK_SIGNATURE) {
        JFUSE_FS_PROVIDER_CALL(JAVA_ARG(1), JAVA_ARG(2));

        JFUSE_SET_RETVAL();
    }

    JAVA_ARG_CLEANUP(2);
    JAVA_ARG_CLEANUP(1);

    JAVA_EXCEPTION_CHECK("jfuse_link");

    CSLogTraceLeave("int jfuse_link(%p, %p): %d",
                from_path, to_path, retval);
    return retval;
}

int jfuse_chmod(const char *path, mode_t mode) {
    CSLogTraceEnter("int jfuse_chmod(%p, %d)", path, mode);
    CSLogTrace("  path=\"%s\"", path);

    int retval = -EIO;
    JFUSE_OPERATION_INIT();

    JAVA_ARG_CSTRING(1, path);

    JFUSE_FS_PROVIDER_MID_OK(OPS_CHMOD_NAME, OPS_CHMOD_SIGNATURE) {
        JFUSE_FS_PROVIDER_CALL(JAVA_ARG(1), (jshort)mode);

        JFUSE_SET_RETVAL();
    }

    JAVA_ARG_CLEANUP(1);

    JAVA_EXCEPTION_CHECK("jfuse_chmod");

    CSLogTraceLeave("int jfuse_chmod(%p, %d): %d",
                path, mode, retval);
    return retval;
}

int jfuse_chown(const char *path, uid_t uid, gid_t gid) {
    CSLogTraceEnter("int jfuse_chown(%p, %d, %d)", path, uid, gid);
    CSLogTrace("  path=\"%s\"", path);

    int retval = -EIO;
    JFUSE_OPERATION_INIT();

    JAVA_ARG_CSTRING(1, path);

    JFUSE_FS_PROVIDER_MID_OK(OPS_CHOWN_NAME, OPS_CHOWN_SIGNATURE) {
        JFUSE_FS_PROVIDER_CALL(JAVA_ARG(1), (jlong)uid, (jlong)gid);

        JFUSE_SET_RETVAL();
    }

    JAVA_ARG_CLEANUP(1);

    JAVA_EXCEPTION_CHECK("jfuse_chown");

    CSLogTraceLeave("int jfuse_chown(%p, %d, %d): %d",
                path, uid, gid, retval);
    return retval;
}

int jfuse_truncate(const char *path, off_t size) {
    CSLogTraceEnter("int jfuse_truncate(%p, %" PRId64 ")", path, size);
    CSLogTrace("  path=\"%s\"", path);

    int retval = -EIO;
    JFUSE_OPERATION_INIT();

    JAVA_ARG_CSTRING(1, path);

    JFUSE_FS_PROVIDER_MID_OK(OPS_TRUNCATE_NAME, OPS_TRUNCATE_SIGNATURE) {
        JFUSE_FS_PROVIDER_CALL(JAVA_ARG(1), size);

        JFUSE_SET_RETVAL();
    }

    JAVA_ARG_CLEANUP(1);

    JAVA_EXCEPTION_CHECK("jfuse_truncate");

    CSLogTraceLeave("int jfuse_truncate(%p, %" PRId64 "): %d",
                path, size, retval);
    return retval;
}

int jfuse_utime(const char *path, struct utimbuf *time) {
    CSLogTraceEnter("int jfuse_utime(%p, %p)", path, time);
    CSLogTrace("  path=\"%s\"", path);

    int retval = -EIO;
    JFUSE_OPERATION_INIT();

    JAVA_ARG_CSTRING(1, path);
    JAVA_ARG_UTIMBUF(2, time);

    JFUSE_FS_PROVIDER_MID_OK(OPS_UTIME_NAME, OPS_UTIME_SIGNATURE) {
        JFUSE_FS_PROVIDER_CALL(JAVA_ARG(1), JAVA_ARG(2));

        JFUSE_MERGE_UTIMBUF(JAVA_ARG(2), time);

        JFUSE_SET_RETVAL();
    }

    JAVA_ARG_CLEANUP(2);
    JAVA_ARG_CLEANUP(1);

    JAVA_EXCEPTION_CHECK("jfuse_utime");

    CSLogTraceLeave("int jfuse_utime(%p, %p): %d",
                path, time, retval);
    return retval;
}

int jfuse_open(const char *path, struct fuse_file_info *fi) {
    CSLogTraceEnter("int jfuse_open(%p, %p)",
            path, fi);
    CSLogTrace("  path=\"%s\"", path);

    int retval = -EIO;
    JFUSE_OPERATION_INIT();

    JAVA_ARG_CSTRING(1, path);
    JAVA_ARG_FUSE_FILE_INFO(2, fi);

    JFUSE_FS_PROVIDER_MID_OK(OPS_OPEN_NAME, OPS_OPEN_SIGNATURE) {
        JFUSE_FS_PROVIDER_CALL(JAVA_ARG(1), JAVA_ARG(2));

        JFUSE_MERGE_FUSE_FILE_INFO(JAVA_ARG(2), fi);

        JFUSE_SET_RETVAL();
    }

    JAVA_ARG_CLEANUP(2);
    JAVA_ARG_CLEANUP(1);

    JAVA_EXCEPTION_CHECK("jfuse_open");

    CSLogTraceLeave("int jfuse_open(%p, %p): %d",
            path, fi, retval);
    return retval;

}

int jfuse_read(const char *path, char *targetbuf, size_t targetbuf_len, off_t file_off,
        struct fuse_file_info *fi) {
    CSLogTraceEnter("int jfuse_read(%p, %p, %zu, %" PRId64 ", %p)",
            path, targetbuf, targetbuf_len, file_off, fi);
    CSLogTrace("  path=\"%s\"", path);

    int retval = -EIO;
    JFUSE_OPERATION_INIT();

    JAVA_ARG_CSTRING(1, path);
    JAVA_ARG_BYTE_ARRAY(2, targetbuf, targetbuf_len);
    JAVA_ARG_FUSE_FILE_INFO(5, fi);

    JFUSE_FS_PROVIDER_MID_OK(OPS_READ_NAME, OPS_READ_SIGNATURE) {
        JFUSE_FS_PROVIDER_CALL(JAVA_ARG(1), JAVA_ARG(2), targetbuf_len, file_off, JAVA_ARG(5));

        JFUSE_MERGE_FUSE_FILE_INFO(JAVA_ARG(5), fi);
        JFUSE_MERGE_BYTE_ARRAY(JAVA_ARG(2), targetbuf, targetbuf_len);

        JFUSE_SET_RETVAL();
    }

    JAVA_ARG_CLEANUP(5);
    JAVA_ARG_CLEANUP(2);
    JAVA_ARG_CLEANUP(1);

    JAVA_EXCEPTION_CHECK("jfuse_read");

    CSLogTraceLeave("int jfuse_read(%p, %p, %zu, %" PRId64 ", %p): %d",
            path, targetbuf, targetbuf_len, file_off, fi, retval);
    return retval;
}

int jfuse_write(const char *path, const char *buf, size_t len, off_t off,
        struct fuse_file_info *fi) {
    CSLogTraceEnter("int jfuse_write(%p, %p, %zu, %" PRId64 ", %p)", path, buf,
            len, off, fi);
    CSLogTrace("  path=\"%s\"", path);

    int retval = -EIO;
    JFUSE_OPERATION_INIT();

    JAVA_ARG_CSTRING(1, path);
    JAVA_ARG_BYTE_ARRAY(2, buf, len);
    JAVA_ARG_FUSE_FILE_INFO(4, fi);

    JFUSE_FS_PROVIDER_MID_OK(OPS_WRITE_NAME, OPS_WRITE_SIGNATURE) {
        JFUSE_FS_PROVIDER_CALL(JAVA_ARG(1), JAVA_ARG(2), off, JAVA_ARG(4));

        JFUSE_MERGE_FUSE_FILE_INFO(JAVA_ARG(4), fi);

        JFUSE_SET_RETVAL();
    }

    JAVA_ARG_CLEANUP(4);
    JAVA_ARG_CLEANUP(2);
    JAVA_ARG_CLEANUP(1);

    JAVA_EXCEPTION_CHECK("jfuse_write");

    CSLogTraceLeave("int jfuse_write(%p, %p, %zu, %" PRId64 ", %p): %d",
                path, buf, len, off, fi, retval);
    return retval;
}

int jfuse_statfs(const char *path, struct statvfs *stvfsbuf) {
    CSLogTraceEnter("int jfuse_statfs(%p, %p)", path, stvfsbuf);
    CSLogTrace("  path=\"%s\"", path);

    int retval = -EIO;
    JFUSE_OPERATION_INIT();

    JAVA_ARG_CSTRING(1, path);
    JAVA_ARG_STATVFS(2, stvfsbuf);

    JFUSE_FS_PROVIDER_MID_OK(OPS_STATFS_NAME, OPS_STATFS_SIGNATURE) {
        JFUSE_FS_PROVIDER_CALL(JAVA_ARG(1), JAVA_ARG(2));

        JFUSE_MERGE_STATVFS(JAVA_ARG(2), stvfsbuf);

        JFUSE_SET_RETVAL();
    }

    JAVA_ARG_CLEANUP(2);
    JAVA_ARG_CLEANUP(1);

    JAVA_EXCEPTION_CHECK("jfuse_statfs");

    CSLogTraceLeave("int jfuse_statfs(%p, %p): %d",
                path, stvfsbuf, retval);
    return retval;
}

int jfuse_flush(const char *path, struct fuse_file_info *fi) {
    CSLogTraceEnter("int jfuse_flush(%p, %p)", path, fi);
    CSLogTrace("  path=\"%s\"", path);

    int retval = -EIO;
    JFUSE_OPERATION_INIT();

    JAVA_ARG_CSTRING(1, path);
    JAVA_ARG_FUSE_FILE_INFO(2, fi);

    JFUSE_FS_PROVIDER_MID_OK(OPS_FLUSH_NAME, OPS_FLUSH_SIGNATURE) {
        JFUSE_FS_PROVIDER_CALL(JAVA_ARG(1), JAVA_ARG(2));

        JFUSE_MERGE_FUSE_FILE_INFO(JAVA_ARG(2), fi);

        JFUSE_SET_RETVAL();
    }

    JAVA_ARG_CLEANUP(2);
    JAVA_ARG_CLEANUP(1);

    JAVA_EXCEPTION_CHECK("jfuse_flush");

    CSLogTraceLeave("int jfuse_flush(%p, %p): %d",
                path, fi, retval);
    return retval;
}

int jfuse_release(const char *path, struct fuse_file_info *fi) {
    CSLogTraceEnter("int jfuse_release(%p, %p)", path, fi);
    CSLogTrace("  path=\"%s\"", path);

    int retval = -EIO;
    JFUSE_OPERATION_INIT();

    JAVA_ARG_CSTRING(1, path);
    JAVA_ARG_FUSE_FILE_INFO(2, fi);

    JFUSE_FS_PROVIDER_MID_OK(OPS_RELEASE_NAME, OPS_RELEASE_SIGNATURE) {
        JFUSE_FS_PROVIDER_CALL(JAVA_ARG(1), JAVA_ARG(2));

        JFUSE_MERGE_FUSE_FILE_INFO(JAVA_ARG(2), fi);

        JFUSE_SET_RETVAL();
    }

    JAVA_ARG_CLEANUP(2);
    JAVA_ARG_CLEANUP(1);

    JAVA_EXCEPTION_CHECK("jfuse_fsync");

    CSLogTraceLeave("int jfuse_release(%p, %p): %d",
                path, fi, retval);
    return retval;
}

int jfuse_fsync(const char *path, int datasync, struct fuse_file_info *fi) {
    CSLogTraceEnter("int jfuse_fsync(%p, %d, %p)", path, datasync, fi);
    CSLogTrace("  path=\"%s\"", path);

    int retval = -EIO;
    JFUSE_OPERATION_INIT();

    JAVA_ARG_CSTRING(1, path);
    JAVA_ARG_FUSE_FILE_INFO(3, fi);

    JFUSE_FS_PROVIDER_MID_OK(OPS_FSYNC_NAME, OPS_FSYNC_SIGNATURE) {

        JFUSE_FS_PROVIDER_CALL(JAVA_ARG(1), (datasync != 0 ? JNI_TRUE : JNI_FALSE), JAVA_ARG(3));

        JFUSE_MERGE_FUSE_FILE_INFO(JAVA_ARG(3), fi);

        JFUSE_SET_RETVAL();
    }

    JAVA_ARG_CLEANUP(3);
    JAVA_ARG_CLEANUP(1);

    JAVA_EXCEPTION_CHECK("jfuse_fsync");

    CSLogTraceLeave("int jfuse_fsync(%p, %d, %p): %d",
                path, datasync, fi, retval);
    return retval;
}

#if (__FreeBSD__ >= 10)

int jfuse_setxattr(const char *path, const char *name, const char *value,
        size_t value_len, int flags, uint32_t position) {
    CSLogTraceEnter("int jfuse_setxattr(%p, %p, %p, %zu, %d, %" PRId32 ")",
            path, name, value, value_len, flags, position);
    CSLogTrace("  path=\"%s\"", path);
    CSLogTrace("  name=\"%s\"", name);

    int retval = -EIO;
    JFUSE_OPERATION_INIT();

    JAVA_ARG_CSTRING(1, path);
    JAVA_ARG_CSTRING(2, name);
    JAVA_ARG_BYTE_ARRAY(3, value, value_len);

    JFUSE_FS_PROVIDER_MID_OK(OPS_SETXATTR_BSD_NAME, OPS_SETXATTR_BSD_SIGNATURE) {

        JFUSE_FS_PROVIDER_CALL(JAVA_ARG(1), JAVA_ARG(2), JAVA_ARG(3), flags, position);

        JFUSE_SET_RETVAL();
    }

    JAVA_ARG_CLEANUP(3);
    JAVA_ARG_CLEANUP(2);
    JAVA_ARG_CLEANUP(1);

    JAVA_EXCEPTION_CHECK("jfuse_setxattr (BSD version)");

    CSLogTraceLeave("int jfuse_setxattr(%p, %p, %p, %zu, %d, %" PRId32 "): %d",
                path, name, value, value_len, flags, position, retval);
    return retval;
}
#else

int jfuse_setxattr(const char *path, const char *name, const char *value,
        size_t value_len, int flags) {
    CSLogTraceEnter("int jfuse_setxattr(%p, %p, %p, %zu, %d)", path, name, value, value_len, flags);
    CSLogTrace("  path=\"%s\"", path);
    CSLogTrace("  name=\"%s\"", name);

    int retval = -EIO;
    JFUSE_OPERATION_INIT();

    JAVA_ARG_CSTRING(1, path);
    JAVA_ARG_CSTRING(2, name);
    JAVA_ARG_BYTE_ARRAY(3, value, value_len);

    JFUSE_FS_PROVIDER_MID_OK(OPS_SETXATTR_NAME, OPS_SETXATTR_SIGNATURE) {

        JFUSE_FS_PROVIDER_CALL(JAVA_ARG(1), JAVA_ARG(2), JAVA_ARG(3), flags);

        JFUSE_SET_RETVAL();
    }

    JAVA_ARG_CLEANUP(3);
    JAVA_ARG_CLEANUP(2);
    JAVA_ARG_CLEANUP(1);

    JAVA_EXCEPTION_CHECK("jfuse_setxattr");

    CSLogTraceLeave("int jfuse_setxattr(%p, %p, %p, %zu, %d): %d",
                path, name, value, value_len, flags, retval);
    return retval;
}
#endif /* __FreeBSD__ >= 10 */

#if (__FreeBSD__ >= 10)

int jfuse_getxattr(const char *path, const char *name, char *value,
        size_t value_len, uint32_t position) {
    CSLogTraceEnter("int jfuse_getxattr(%p, %p, %p, %zu, %" PRId32 ")", path,
            name, value, value_len, position);
    CSLogTrace("  path=\"%s\"", path);
    CSLogTrace("  name=\"%s\"", name);

    int retval = -EIO;
    JFUSE_OPERATION_INIT();

    JAVA_ARG_CSTRING(1, path);
    JAVA_ARG_CSTRING(2, name);
    JAVA_ARG_BYTE_ARRAY(3, value, value_len);

    JFUSE_FS_PROVIDER_MID_OK(OPS_GETXATTR_BSD_NAME, OPS_GETXATTR_BSD_SIGNATURE) {

        JFUSE_FS_PROVIDER_CALL(JAVA_ARG(1), JAVA_ARG(2), JAVA_ARG(3), position);

        JFUSE_MERGE_BYTE_ARRAY(JAVA_ARG(3), value, value_len)

        JFUSE_SET_RETVAL();
    }

    JAVA_ARG_CLEANUP(3);
    JAVA_ARG_CLEANUP(2);
    JAVA_ARG_CLEANUP(1);

    JAVA_EXCEPTION_CHECK("jfuse_getxattr (BSD version)");

    CSLogTraceLeave("int jfuse_getxattr(%p, %p, %p, %zu, %" PRId32 "): %d",
                path, name, value, value_len, position, retval);
    return retval;
}
#else

int jfuse_getxattr(const char *path, const char *name, char *value,
        size_t value_len) {
    CSLogTraceEnter("int jfuse_getxattr(%p, %p, %p, %zu)", path,
            name, value, value_len);
    CSLogTrace("  path=\"%s\"", path);
    CSLogTrace("  name=\"%s\"", name);

    int retval = -EIO;
    JFUSE_OPERATION_INIT();

    JAVA_ARG_CSTRING(1, path);
    JAVA_ARG_CSTRING(2, name);
    JAVA_ARG_BYTE_ARRAY(3, value, value_len);

    JFUSE_FS_PROVIDER_MID_OK(OPS_GETXATTR_NAME, OPS_GETXATTR_SIGNATURE) {

        JFUSE_FS_PROVIDER_CALL(JAVA_ARG(1), JAVA_ARG(2), JAVA_ARG(3));

        JFUSE_MERGE_BYTE_ARRAY(JAVA_ARG(3), value, value_len)

        JFUSE_SET_RETVAL();
    }

    JAVA_ARG_CLEANUP(3);
    JAVA_ARG_CLEANUP(2);
    JAVA_ARG_CLEANUP(1);

    JAVA_EXCEPTION_CHECK("jfuse_getxattr");

    CSLogTraceLeave("int jfuse_getxattr(%p, %p, %p, %zu): %d",
                path, name, value, value_len, retval);
    return retval;
}
#endif /* __FreeBSD__ >= 10 */

int jfuse_listxattr(const char *path, char *namebuf, size_t namebuf_len) {
    CSLogTraceEnter("int jfuse_listxattr(%p, %p, %zu)", path, namebuf, namebuf_len);
    CSLogTrace("  path=\"%s\"", path);

    int retval = -EIO;
    JFUSE_OPERATION_INIT();

    JAVA_ARG_CSTRING(1, path);
    JAVA_ARG_BYTE_ARRAY(2, namebuf, namebuf_len);

    JFUSE_FS_PROVIDER_MID_OK(OPS_LISTXATTR_NAME, OPS_LISTXATTR_SIGNATURE) {

        JFUSE_FS_PROVIDER_CALL(JAVA_ARG(1), JAVA_ARG(2));

        JFUSE_MERGE_BYTE_ARRAY(JAVA_ARG(2), namebuf, namebuf_len)

        JFUSE_SET_RETVAL();
    }

    JAVA_ARG_CLEANUP(2);
    JAVA_ARG_CLEANUP(1);

    JAVA_EXCEPTION_CHECK("jfuse_removexattr");

    CSLogTraceLeave("int jfuse_listxattr(%p, %p, %zu): %d",
                path, namebuf, namebuf_len, retval);
    return retval;
}

int jfuse_removexattr(const char *path, const char *name) {
    CSLogTraceEnter("int jfuse_removexattr(%p, %p)", path, name);
    CSLogTrace("  path=\"%s\"", path);
    CSLogTrace("  name=\"%s\"", name);

    int retval = -EIO;
    JFUSE_OPERATION_INIT();

    JAVA_ARG_CSTRING(1, path);
    JAVA_ARG_CSTRING(2, name);

    JFUSE_FS_PROVIDER_MID_OK(OPS_REMOVEXATTR_NAME, OPS_REMOVEXATTR_SIGNATURE) {

        JFUSE_FS_PROVIDER_CALL(JAVA_ARG(1), JAVA_ARG(2));

        JFUSE_SET_RETVAL();
    }

    JAVA_ARG_CLEANUP(2);
    JAVA_ARG_CLEANUP(1);

    JAVA_EXCEPTION_CHECK("jfuse_removexattr");

    CSLogTraceLeave("int jfuse_removexattr(%p, %p): %d",
                path, name, retval);
    return retval;
}

int jfuse_opendir(const char *path, struct fuse_file_info *fi) {
    CSLogTraceEnter("int jfuse_opendir(%p, %p)", path, fi);
    CSLogTrace("  path=\"%s\"", path);

    int retval = -EIO;
    JFUSE_OPERATION_INIT();

    JAVA_ARG_CSTRING(1, path);
    JAVA_ARG_FUSE_FILE_INFO(2, fi);

    JFUSE_FS_PROVIDER_MID_OK(OPS_OPENDIR_NAME, OPS_OPENDIR_SIGNATURE) {

        JFUSE_FS_PROVIDER_CALL(JAVA_ARG(1), JAVA_ARG(2));

        JFUSE_MERGE_FUSE_FILE_INFO(JAVA_ARG(2), fi);

        JFUSE_SET_RETVAL();
    }

    JAVA_ARG_CLEANUP(2);
    JAVA_ARG_CLEANUP(1);

    JAVA_EXCEPTION_CHECK("jfuse_opendir");

    CSLogTraceLeave("int jfuse_opendir(%p, %p): %d",
                path, fi, retval);
    return retval;
}

int jfuse_readdir(const char *path, void *buf, fuse_fill_dir_t filler,
        off_t offset, struct fuse_file_info *fi) {
    
    CSLogTraceEnter("int jfuse_readdir(%p, %p, %p, %" PRId64 ", %p)",
            path, buf, filler, offset, fi);
    CSLogTrace("  path=\"%s\"", path);

    int retval = -EIO;
    JFUSE_OPERATION_INIT();

    JAVA_ARG_CSTRING(1, path);
    JAVA_ARG_FUSE_FILL_DIR(2, filler, buf);
    JAVA_ARG_FUSE_FILE_INFO(4, fi);

    JFUSE_FS_PROVIDER_MID_OK(OPS_READDIR_NAME, OPS_READDIR_SIGNATURE) {

        JFUSE_FS_PROVIDER_CALL(JAVA_ARG(1), JAVA_ARG(2), offset, JAVA_ARG(4));

        JFUSE_MERGE_FUSE_FILE_INFO(JAVA_ARG(4), fi);

        JFUSE_SET_RETVAL();
    }

    JAVA_ARG_CLEANUP(4);
    JAVA_ARG_CLEANUP(2);
    JAVA_ARG_CLEANUP(1);

    JAVA_EXCEPTION_CHECK("jfuse_readdir");

    CSLogTraceLeave("int jfuse_readdir(%p, %p, %p, %" PRId64 ", %p): %d",
            path, buf, filler, offset, fi, retval);
    return retval;
}

int jfuse_releasedir(const char *path, struct fuse_file_info *fi) {
    CSLogTraceEnter("int jfuse_releasedir(%p, %p)", path, fi);
    CSLogTrace("  path=\"%s\"", path);

    int retval = -EIO;
    JFUSE_OPERATION_INIT();

    JAVA_ARG_CSTRING(1, path);
    JAVA_ARG_FUSE_FILE_INFO(2, fi);

    JFUSE_FS_PROVIDER_MID_OK(OPS_RELEASEDIR_NAME, OPS_RELEASEDIR_SIGNATURE) {
        JFUSE_FS_PROVIDER_CALL(JAVA_ARG(1), JAVA_ARG(2));

        JFUSE_MERGE_FUSE_FILE_INFO(JAVA_ARG(2), fi);

        JFUSE_SET_RETVAL();
    }

    JAVA_ARG_CLEANUP(2);
    JAVA_ARG_CLEANUP(1);

    JAVA_EXCEPTION_CHECK("jfuse_releasedir");

    CSLogTraceLeave("int jfuse_releasedir(%p, %p): %d",
                path, fi, retval);
    return retval;
}

int jfuse_fsyncdir(const char *path, int datasync, struct fuse_file_info *fi) {
    CSLogTraceEnter("int jfuse_fsyncdir(%p, %d, %p)", path, datasync, fi);
    CSLogTrace("  path=\"%s\"", path);

    int retval = -EIO;
    JFUSE_OPERATION_INIT();

    JAVA_ARG_CSTRING(1, path);
    JAVA_ARG_FUSE_FILE_INFO(3, fi);

    JFUSE_FS_PROVIDER_MID_OK(OPS_FSYNCDIR_NAME, OPS_FSYNCDIR_SIGNATURE) {
        JFUSE_FS_PROVIDER_CALL(JAVA_ARG(1), (datasync != 0 ? JNI_TRUE : JNI_FALSE), JAVA_ARG(3));

        JFUSE_MERGE_FUSE_FILE_INFO(JAVA_ARG(3), fi);

        JFUSE_SET_RETVAL();
    }

    JAVA_ARG_CLEANUP(3);
    JAVA_ARG_CLEANUP(1);

    JAVA_EXCEPTION_CHECK("jfuse_fsyncdir");

    CSLogTraceLeave("int jfuse_fsyncdir(%p, %d, %p): %d",
                path, datasync, fi, retval);
    return retval;
}

void* jfuse_init(struct fuse_conn_info *conn) {
    CSLogTraceEnter("int jfuse_init(%p)", conn);

    JFUSE_OPERATION_INIT();
    void *retval = context;

    JAVA_ARG_FUSE_CONN_INFO(1, conn);

    JFUSE_FS_PROVIDER_MID_OK(OPS_INIT_NAME, OPS_INIT_SIGNATURE) {
        JFUSE_FS_INIT_CALL(JAVA_ARG(1));

        JFUSE_HANDLE_INIT_RETVAL();
    }

    JAVA_ARG_CLEANUP(1);

    JAVA_EXCEPTION_CHECK("jfuse_init");

    CSLogTraceLeave("int jfuse_init(%p): %p",
                conn, retval);
    return retval;
}

void jfuse_destroy(void *private_data) {
    CSLogTraceEnter("int jfuse_destroy(%p)", private_data);

    JFUSE_OPERATION_INIT();

    if(private_data != fuse_get_context()->private_data)
        CSLogPrint("jfuse_destroy: private_data assertion failed. %p != %p",
                private_data, fuse_get_context()->private_data);

    JFUSE_FS_PROVIDER_MID_OK(OPS_DESTROY_NAME, OPS_DESTROY_SIGNATURE) {
        JFUSE_FS_DESTROY_CALL(context->getPrivateData());
    }

    JAVA_EXCEPTION_CHECK("jfuse_destroy");

    CSLogTraceLeave("int jfuse_destroy(%p)", private_data);
}

int jfuse_access(const char *path, int amode) {
    CSLogTraceEnter("int jfuse_access(%p, %d)", path, amode);
    CSLogTrace("  path=\"%s\"", path);

    int retval = -EIO;
    JFUSE_OPERATION_INIT();

    JAVA_ARG_CSTRING(1, path);

    JFUSE_FS_PROVIDER_MID_OK(OPS_ACCESS_NAME, OPS_ACCESS_SIGNATURE) {
        JFUSE_FS_PROVIDER_CALL(JAVA_ARG(1), amode);

        JFUSE_SET_RETVAL();
    }

    JAVA_ARG_CLEANUP(1);

    JAVA_EXCEPTION_CHECK("jfuse_access");

    CSLogTraceLeave("int jfuse_access(%p, %d): %d",
                path, amode, retval);
    return retval;
}

int jfuse_create(const char *path, mode_t crmode, struct fuse_file_info *fi) {
    CSLogTraceEnter("int jfuse_create(%p, %d, %p)", path, crmode, fi);
    CSLogTrace("  path=\"%s\"", path);

    int retval = -EIO;
    JFUSE_OPERATION_INIT();

    JAVA_ARG_CSTRING(1, path);
    JAVA_ARG_FUSE_FILE_INFO(3, fi);

    JFUSE_FS_PROVIDER_MID_OK(OPS_CREATE_NAME, OPS_CREATE_SIGNATURE) {
        JFUSE_FS_PROVIDER_CALL(JAVA_ARG(1), crmode, JAVA_ARG(3));

        JFUSE_MERGE_FUSE_FILE_INFO(JAVA_ARG(3), fi);

        JFUSE_SET_RETVAL();
    }

    JAVA_ARG_CLEANUP(3);
    JAVA_ARG_CLEANUP(1);

    JAVA_EXCEPTION_CHECK("jfuse_create");

    CSLogTraceLeave("int jfuse_create(%p, %d, %p): %d",
                path, crmode, fi, retval);
    return retval;
}

int jfuse_ftruncate(const char *path, off_t size, struct fuse_file_info *fi) {
    CSLogTraceEnter("int jfuse_ftruncate(%p, %" PRId64 ", %p)", path, size, fi);
    CSLogTrace("  path=\"%s\"", path);

    int retval = -EIO;
    JFUSE_OPERATION_INIT();

    JAVA_ARG_CSTRING(1, path);
    JAVA_ARG_FUSE_FILE_INFO(3, fi);

    JFUSE_FS_PROVIDER_MID_OK(OPS_FTRUNCATE_NAME, OPS_FTRUNCATE_SIGNATURE) {
        JFUSE_FS_PROVIDER_CALL(JAVA_ARG(1), size, JAVA_ARG(3));

        JFUSE_MERGE_FUSE_FILE_INFO(JAVA_ARG(3), fi);

        JFUSE_SET_RETVAL();
    }

    JAVA_ARG_CLEANUP(3);
    JAVA_ARG_CLEANUP(1);

    JAVA_EXCEPTION_CHECK("jfuse_ftruncate");

    CSLogTraceLeave("int jfuse_ftruncate(%p, %" PRId64 ", %p): %d",
                path, size, fi, retval);
    return retval;
}

int jfuse_fgetattr(const char *path, struct stat *stbuf, struct fuse_file_info *fi) {
    CSLogTraceEnter("int jfuse_fgetattr(%p, %p, %p)", path, stbuf, fi);
    CSLogTrace("  path=\"%s\"", path);

    int retval = -EIO;
    JFUSE_OPERATION_INIT();

    JAVA_ARG_CSTRING(1, path);
    JAVA_ARG_STAT(2, stbuf);
    JAVA_ARG_FUSE_FILE_INFO(3, fi);

    JFUSE_FS_PROVIDER_MID_OK(OPS_FGETATTR_NAME, OPS_FGETATTR_SIGNATURE) {
        JFUSE_FS_PROVIDER_CALL(JAVA_ARG(1), JAVA_ARG(2), JAVA_ARG(3));

        JFUSE_MERGE_STAT(JAVA_ARG(2), stbuf);
        JFUSE_MERGE_FUSE_FILE_INFO(JAVA_ARG(3), fi);

        JFUSE_SET_RETVAL();
    }

    JAVA_ARG_CLEANUP(3);
    JAVA_ARG_CLEANUP(2);
    JAVA_ARG_CLEANUP(1);

    JAVA_EXCEPTION_CHECK("jfuse_fgetattr");

    CSLogTraceLeave("int jfuse_fgetattr(%p, %p, %p): %d",
                path, stbuf, fi, retval);
    return retval;
}

int jfuse_lock(const char *path, struct fuse_file_info *fi, int cmd,
        struct flock *flk) {
    CSLogTraceEnter("int jfuse_lock(%p, %p, %d, %p)", path, fi, cmd, flk);
    CSLogTrace("  path=\"%s\"", path);

    int retval = -EIO;
    JFUSE_OPERATION_INIT();

    JAVA_ARG_CSTRING(1, path);
    JAVA_ARG_FUSE_FILE_INFO(2, fi);
    JAVA_ARG_FLOCK(4, flk);

    JFUSE_FS_PROVIDER_MID_OK(OPS_LOCK_NAME, OPS_LOCK_SIGNATURE) {
        JFUSE_FS_PROVIDER_CALL(JAVA_ARG(1), JAVA_ARG(2), cmd, JAVA_ARG(4));

        JFUSE_MERGE_FUSE_FILE_INFO(JAVA_ARG(2), fi);
        JFUSE_MERGE_FLOCK(JAVA_ARG(4), flk);

        JFUSE_SET_RETVAL();
    }

    JAVA_ARG_CLEANUP(4);
    JAVA_ARG_CLEANUP(2);
    JAVA_ARG_CLEANUP(1);

    JAVA_EXCEPTION_CHECK("jfuse_lock");

    CSLogTraceLeave("int jfuse_lock(%p, %p, %d, %p): %d",
                path, fi, cmd, flk, retval);
    return retval;
}

int jfuse_utimens(const char *path, const struct timespec tv[2]) {
    CSLogTraceEnter("int jfuse_utimens(%p, %p)", path, tv);
    CSLogTrace("  path=\"%s\"", path);

    int retval = -EIO;
    JFUSE_OPERATION_INIT();

    JAVA_ARG_CSTRING(1, path);
    JAVA_ARG_TIMESPEC(2, &tv[0]);
    JAVA_ARG_TIMESPEC(3, &tv[1]);

    JFUSE_FS_PROVIDER_MID_OK(OPS_UTIMENS_NAME, OPS_UTIMENS_SIGNATURE) {
        JFUSE_FS_PROVIDER_CALL(JAVA_ARG(1), JAVA_ARG(2), JAVA_ARG(3));
        
        JFUSE_SET_RETVAL();
    }

    JAVA_ARG_CLEANUP(3);
    JAVA_ARG_CLEANUP(2);
    JAVA_ARG_CLEANUP(1);

    JAVA_EXCEPTION_CHECK("jfuse_utimens");

    CSLogTraceLeave("int jfuse_utimens(%p, %p): %d",
                path, tv, retval);
    return retval;
}

int jfuse_bmap(const char *path, size_t blocksize, uint64_t *idx) {
    CSLogTraceEnter("int jfuse_bmap(%p, %zu, %p)", path, blocksize, idx);
    CSLogTrace("  path=\"%s\"", path);

    int retval = -EIO;
    JFUSE_OPERATION_INIT();

    JAVA_ARG_CSTRING(1, path);
    JAVA_ARG_LONGREF(3, idx);

    JFUSE_FS_PROVIDER_MID_OK(OPS_BMAP_NAME, OPS_BMAP_SIGNATURE) {
        JFUSE_FS_PROVIDER_CALL(JAVA_ARG(1), blocksize, JAVA_ARG(3));

        JFUSE_MERGE_LONGREF(JAVA_ARG(3), idx);

        JFUSE_SET_RETVAL();
    }

    JAVA_ARG_CLEANUP(3);
    JAVA_ARG_CLEANUP(1);

    JAVA_EXCEPTION_CHECK("jfuse_bmap");

    CSLogTraceLeave("int jfuse_bmap(%p, %zu, %p): %d",
                path, blocksize, idx, retval);
    return retval;
}

#if (__FreeBSD__ >= 10)

// Implement these MacFUSE callbacks some time in the future.
/*
int jfuse_setvolname(const char *name) {
    CSLogTraceEnter("int jfuse_(%p, )", path, );
    CSLogTrace("  path=\"%s\"", path);

    int retval = -ENOTSUP;

    CSLogTraceLeave("int jfuse_(%p, ): %d",
                path, , retval);
    return retval;
}

int jfuse_exchange(const char *, const char *, unsigned long) {
    CSLogTraceEnter("int jfuse_(%p, )", path, );
    CSLogTrace("  path=\"%s\"", path);

    int retval = -ENOTSUP;

    CSLogTraceLeave("int jfuse_(%p, ): %d",
                path, , retval);
    return retval;
}

int jfuse_getxtimes(const char *, struct timespec *bkuptime,
        struct timespec *crtime) {
    CSLogTraceEnter("int jfuse_(%p, )", path, );
    CSLogTrace("  path=\"%s\"", path);

    int retval = -ENOTSUP;

    CSLogTraceLeave("int jfuse_(%p, ): %d",
                path, , retval);
    return retval;
}

int jfuse_setbkuptime(const char *, const struct timespec *tv) {
    CSLogTraceEnter("int jfuse_(%p, )", path, );
    CSLogTrace("  path=\"%s\"", path);

    int retval = -ENOTSUP;

    CSLogTraceLeave("int jfuse_(%p, ): %d",
                path, , retval);
    return retval;
}

int jfuse_setchgtime(const char *, const struct timespec *tv) {
    CSLogTraceEnter("int jfuse_(%p, )", path, );
    CSLogTrace("  path=\"%s\"", path);

    int retval = -ENOTSUP;

    CSLogTraceLeave("int jfuse_(%p, ): %d",
                path, , retval);
    return retval;
}

int jfuse_setcrtime(const char *, const struct timespec *tv) {
    CSLogTraceEnter("int jfuse_(%p, )", path, );
    CSLogTrace("  path=\"%s\"", path);

    int retval = -ENOTSUP;

    CSLogTraceLeave("int jfuse_(%p, ): %d",
                path, , retval);
    return retval;
}

int jfuse_chflags(const char *, uint32_t) {
    CSLogTraceEnter("int jfuse_(%p, )", path, );
    CSLogTrace("  path=\"%s\"", path);

    int retval = -ENOTSUP;

    CSLogTraceLeave("int jfuse_(%p, ): %d",
                path, , retval);
    return retval;
}

int jfuse_setattr_x(const char *, struct setattr_x *) {
    CSLogTraceEnter("int jfuse_(%p, )", path, );
    CSLogTrace("  path=\"%s\"", path);

    int retval = -ENOTSUP;

    CSLogTraceLeave("int jfuse_(%p, ): %d",
                path, , retval);
    return retval;
}

int jfuse_fsetattr_x(const char *, struct setattr_x *,
        struct fuse_file_info *fi) {
    CSLogTraceEnter("int jfuse_(%p, )", path, );
    CSLogTrace("  path=\"%s\"", path);

    int retval = -ENOTSUP;

    CSLogTraceLeave("int jfuse_(%p, ): %d",
                path, , retval);
    return retval;
}
*/

#endif /* __FreeBSD__ >= 10 */
