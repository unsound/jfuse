#include "org_catacombae_jfuse_FUSE.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <jni.h>

#define FUSE_USE_VERSION 26
#include <fuse.h>
#include <fuse/fuse_common.h>

#include "fuse26_module.h"
#include "CSLog.h"

#define errorHandling(...) \
    do { \
        fprintf(stderr, "Panic!\n"); \
        char *ptr = NULL; \
        ptr[0] = '\0'; \
        exit(1); \
    } while(0)

/*
struct fuse_capability {
    char *name;
    void *jfuse_function;
    void **fuse_operation;
};
*/

static bool getCapability(JNIEnv *env, jclass capabilitiesClass,
        jobject capabilities, char *name, jboolean *out) {
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

static bool fillFUSE26Operations(JNIEnv *env, jclass capabilitiesClass,
        jobject capabilities, struct fuse_operations *ops) {
    CSLogTraceEnter("fillFUSE26Operations(%p, %p, %p, %p)",
            env, capabilitiesClass, capabilities, ops);

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
#if (__FreeBSD__ >= 10)
    AddOperationIfSupported2(setxattr, setxattr_BSD);
    AddOperationIfSupported2(getxattr, getxattr_BSD);
#else
    AddOperationIfSupported(setxattr);
    AddOperationIfSupported(getxattr);
#endif
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

    /*
    if(getCapability(env, capabilitiesClass, capabilities, "getattr") == JNI_TRUE)
        ops.getattr = jfuse_getattr;
    if(getCapability(env, capabilitiesClass, capabilities, "readlink") == JNI_TRUE)
        ops.readlink = jfuse_readlink;
    if(getCapability(env, capabilitiesClass, capabilities, "getdir") == JNI_TRUE)
        ops.getdir = jfuse_getdir;
    if(getCapability(env, capabilitiesClass, capabilities, "mknod") == JNI_TRUE)
        ops.mknod = jfuse_mknod;
    if(getCapability(env, capabilitiesClass, capabilities, "mkdir") == JNI_TRUE)
        ops.mkdir = jfuse_mkdir;
    if(getCapability(env, capabilitiesClass, capabilities, "unlink") == JNI_TRUE)
        ops.unlink = jfuse_unlink;
    if(getCapability(env, capabilitiesClass, capabilities, "rmdir") == JNI_TRUE)
        ops.rmdir = jfuse_rmdir;
    if(getCapability(env, capabilitiesClass, capabilities, "symlink") == JNI_TRUE)
        ops.symlink = jfuse_symlink;
    if(getCapability(env, capabilitiesClass, capabilities, "rename") == JNI_TRUE)
        ops.rename = jfuse_rename;
    if(getCapability(env, capabilitiesClass, capabilities, "link") == JNI_TRUE)
        ops.link = jfuse_link;
    if(getCapability(env, capabilitiesClass, capabilities, "chmod") == JNI_TRUE)
        ops.chmod = jfuse_chmod;
    if(getCapability(env, capabilitiesClass, capabilities, "chown") == JNI_TRUE)
        ops.chown = jfuse_chown;
    if(getCapability(env, capabilitiesClass, capabilities, "truncate") == JNI_TRUE)
        ops.truncate = jfuse_truncate;
    if(getCapability(env, capabilitiesClass, capabilities, "utime") == JNI_TRUE)
        ops.utime = jfuse_utime;
    if(getCapability(env, capabilitiesClass, capabilities, "open") == JNI_TRUE)
        ops.open = jfuse_open;
    if(getCapability(env, capabilitiesClass, capabilities, "read") == JNI_TRUE)
        ops.read = jfuse_read;
    if(getCapability(env, capabilitiesClass, capabilities, "write") == JNI_TRUE)
        ops.write = jfuse_write;
    if(getCapability(env, capabilitiesClass, capabilities, "statfs") == JNI_TRUE)
        ops.statfs = jfuse_statfs;
    if(getCapability(env, capabilitiesClass, capabilities, "flush") == JNI_TRUE)
        ops.flush = jfuse_flush;
    if(getCapability(env, capabilitiesClass, capabilities, "release") == JNI_TRUE)
        ops.release = jfuse_release;
    if(getCapability(env, capabilitiesClass, capabilities, "fsync") == JNI_TRUE)
        ops.fsync = jfuse_fsync;
#if (__FreeBSD__ >= 10)
    if(getCapability(env, capabilitiesClass, capabilities, "setxattr_BSD") == JNI_TRUE)
        ops.setxattr = jfuse_setxattr;
    if(getCapability(env, capabilitiesClass, capabilities, "getxattr_BSD") == JNI_TRUE)
        ops.getxattr = jfuse_getxattr;
#else
    if(getCapability(env, capabilitiesClass, capabilities, "setxattr") == JNI_TRUE)
        ops.setxattr = jfuse_setxattr;
    if(getCapability(env, capabilitiesClass, capabilities, "getxattr") == JNI_TRUE)
        ops.getxattr = jfuse_getxattr;
#endif
    if(getCapability(env, capabilitiesClass, capabilities, "listxattr") == JNI_TRUE)
        ops.listxattr = jfuse_listxattr;
    if(getCapability(env, capabilitiesClass, capabilities, "removexattr") == JNI_TRUE)
        ops.removexattr = jfuse_removexattr;
    if(getCapability(env, capabilitiesClass, capabilities, "opendir") == JNI_TRUE)
        ops.opendir = jfuse_opendir;
    if(getCapability(env, capabilitiesClass, capabilities, "readdir") == JNI_TRUE)
        ops.readdir = jfuse_readdir;
    if(getCapability(env, capabilitiesClass, capabilities, "releasedir") == JNI_TRUE)
        ops.releasedir = jfuse_releasedir;
    if(getCapability(env, capabilitiesClass, capabilities, "fsyncdir") == JNI_TRUE)
        ops.fsyncdir = jfuse_fsyncdir;
    if(getCapability(env, capabilitiesClass, capabilities, "init") == JNI_TRUE)
        ops.init = jfuse_init;
    if(getCapability(env, capabilitiesClass, capabilities, "destroy") == JNI_TRUE)
        ops.destroy = jfuse_destroy;
    if(getCapability(env, capabilitiesClass, capabilities, "access") == JNI_TRUE)
        ops.access = jfuse_access;
    if(getCapability(env, capabilitiesClass, capabilities, "create") == JNI_TRUE)
        ops.create = jfuse_create;
    if(getCapability(env, capabilitiesClass, capabilities, "ftruncate") == JNI_TRUE)
        ops.ftruncate = jfuse_ftruncate;
    if(getCapability(env, capabilitiesClass, capabilities, "fgetattr") == JNI_TRUE)
        ops.fgetattr = jfuse_fgetattr;
    if(getCapability(env, capabilitiesClass, capabilities, "lock") == JNI_TRUE)
        ops.lock = jfuse_lock;
    if(getCapability(env, capabilitiesClass, capabilities, "utimens") == JNI_TRUE)
        ops.utimens = jfuse_utimens;
    if(getCapability(env, capabilitiesClass, capabilities, "bmap") == JNI_TRUE)
        ops.bmap = jfuse_bmap;
    */
    /*
    if(getCapability(env, capabilitiesClass, capabilities, "") == JNI_TRUE)
        ops. = jfuse_;
    */

    CSLogTraceLeave("fillFUSE26Operations(%p, %p, %p, %p): %d",
            env, capabilitiesClass, capabilities, ops, true);
    
    return true;
}

static struct fuse_operations jfuse_operations;

/*
 * Class:     org_catacombae_jfuse_FUSE
 * Method:    mountNative26
 * Signature: (Lorg/catacombae/jfuse/FUSE26FileSystem;Ljava/lang/String;Lorg/catacombae/jfuse/FUSEOptions;)Z
 */
JNIEXPORT jboolean JNICALL Java_org_catacombae_jfuse_FUSE_mountNative26(
        JNIEnv *env, jclass cls, jobject fileSystem, jstring mountPoint,
        jobjectArray optionStrings) {
    CSLogTraceEnter("Java_org_catacombae_jfuse_FUSE_mountNative26(%p, %p, %p, %p, %p)",
            env, cls, fileSystem, mountPoint, optionStrings);

    jclass fileSystemClass = env->GetObjectClass(fileSystem);
    if(fileSystemClass == NULL)
        errorHandling();
    else
        CSLogDebug("Got file system class: %p", fileSystemClass);

    jmethodID getCapabilitiesMid = env->GetMethodID(fileSystemClass,
            "getCapabilities", "()Lorg/catacombae/jfuse/FUSE26Capabilities;");
    if(getCapabilitiesMid == NULL)
        CSPanicWithMessage("Could not get method ID for getCapabilities!");
    else
        CSLogDebug("Got method ID for getCapabilities(): %p", getCapabilitiesMid);

    jobject capabilities = env->CallObjectMethod(fileSystem, getCapabilitiesMid);
    if(capabilities == NULL)
        CSPanicWithMessage("Could not call object method getCapabilities.");
    else
        CSLogDebug("Called method getCapabilities() with result: %p", capabilities);

    jclass capabilitiesClass = env->GetObjectClass(capabilities);
    if(capabilitiesClass == NULL)
        CSPanicWithMessage("Could not get capabilities class!");
    else
        CSLogDebug("Got capabilities class: %p", capabilitiesClass);

    if(!fillFUSE26Operations(env, capabilitiesClass, capabilities, &jfuse_operations))
        CSPanicWithMessage("Could not fill FUSE 2.6 operations!");
    else
        CSLogDebug("Filled FUSE 2.6 operations.");

    /* Read mountpoint. */
    jboolean isCopy;
    const char *utf8MountPoint = env->GetStringUTFChars(mountPoint, &isCopy);

    /* Read options. */
    struct fuse_args args = FUSE_ARGS_INIT(0, NULL);
    jsize optionStringsLength = env->GetArrayLength(optionStrings);
    for(int i = 0; i < optionStringsLength; ++i) {
        jstring cur = (jstring)env->GetObjectArrayElement(optionStrings, i);
        const char *utfChars = env->GetStringUTFChars(cur, NULL);

        fuse_opt_add_arg(&args, utfChars);

        env->ReleaseStringUTFChars(cur, utfChars);
        env->DeleteLocalRef(cur);
    }
    
    jFUSEContext *context = new jFUSEContext(env, fileSystem);
    
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
    fuse_chan *chan = fuse_mount(utf8MountPoint, &args);
    if(chan == NULL)
        errorHandling();

    fuse *fh = fuse_new(chan, &args, &jfuse_operations,
            sizeof(jfuse_operations), context);
    if(fh == NULL)
        errorHandling();

    fuse_loop(fh);

    fuse_opt_free_args(&args);
    fuse_unmount(utf8MountPoint, chan);
    fuse_destroy(fh);

    delete context;

    CSLogTraceLeave("Java_org_catacombae_jfuse_FUSE_mountNative26(%p, %p, %p, %p, %p): %d",
            env, cls, fileSystem, mountPoint, optionStrings, JNI_TRUE);
    return JNI_TRUE;
}
