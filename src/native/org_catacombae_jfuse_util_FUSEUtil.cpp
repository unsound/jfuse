#include <unistd.h>

#include "org_catacombae_jfuse_util_FUSEUtil.h"

/*
 * Class:     org_catacombae_jfuse_util_FUSEUtil
 * Method:    getProcessUidNative
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_org_catacombae_jfuse_util_FUSEUtil_getProcessUidNative
  (JNIEnv *env, jclass clazz) {
    return (jlong) getuid();
}

/*
 * Class:     org_catacombae_jfuse_util_FUSEUtil
 * Method:    getProcessGidNative
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_org_catacombae_jfuse_util_FUSEUtil_getProcessGidNative
  (JNIEnv *env, jclass clazz) {
    return (jlong) getgid();
}

/*
 * Class:     org_catacombae_jfuse_util_FUSEUtil
 * Method:    getProcessPidNative
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_org_catacombae_jfuse_util_FUSEUtil_getProcessPidNative
  (JNIEnv *env, jclass clazz) {
    return (jlong) getpid();
}

