#include "common.h"
#include "CSLog.h"

/**
 * Throws a Java exception using the exception class referenced to by
 * <code>name</code>, with an exception message set to the UTF-string
 * <code>msg</code>.
 * Example: throwByName(env, "java/lang/RuntimeException", "My Message");
 */
bool throwByName(JNIEnv *env, const char *name, const char *msg) {
    jclass cls = env->FindClass(name);
    if (cls != NULL) {
        if (env->ThrowNew(cls, msg) == 0) {
            env->DeleteLocalRef(cls);
            return true;
        }
    }

    return false;
}

/**
 * This function must be defined and return the proper JNI version, or we're
 * stuck with version 1.1 of JNI.
 */
JNIEXPORT jint JNI_OnLoad(JavaVM *vm, void *reserved) {
    CSLogTraceEnter("JNI_OnLoad(%p, %p)", vm, reserved);
    jint res = JNI_VERSION_1_4;
    CSLogTraceLeave("JNI_OnLoad(%p, %p): %ld", vm, reserved,
            (long)res);
    return res;
}