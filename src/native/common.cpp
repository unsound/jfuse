#include "common.h"

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
