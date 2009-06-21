#include "jFUSEContext.h"

#include "CSLog.h"
#include "common.h"

jFUSEContext::jFUSEContext(JNIEnv* env, jobject fsProvider) {
    if(env == NULL)
        throw "env == NULL";
    if(fsProvider == NULL)
        throw "fsProvider == NULL";
    
    this->env = env;
    this->fsProvider = fsProvider;
}

jFUSEContext::~jFUSEContext() {

}

JNIEnv* jFUSEContext::getJNIEnv() {
    return env;
}

jobject jFUSEContext::getFSProvider() {
    return fsProvider;
}

jmethodID jFUSEContext::getFSProviderMethod(const char *name, const char *signature) {
    jmethodID result = NULL;
    jclass cls = NULL;
    
    do {
        cls = env->GetObjectClass(fsProvider);
        if(cls == NULL || env->ExceptionCheck() == JNI_TRUE) {
            CSLogError("Could not get class of fsProvider!");
            if(env->ExceptionCheck() == JNI_FALSE)
                throwByName(env, "java/lang/RuntimeException", "Could not get Class of fsProvider");
            break;
        }

        result = env->GetMethodID(cls, name, signature);
    } while(0);

    if(cls != NULL)
        env->DeleteLocalRef(cls);

    return result;
}