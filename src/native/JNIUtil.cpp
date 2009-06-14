#include "JNIUtil.h"
#include "CSLog.h"
#include "JavaSignatures.h"

#include <string.h>
#define __STDC_FORMAT_MACROS
#include <inttypes.h>

jbyteArray JNIUtil::cstringToJByteArray(JNIEnv *env, const char *cstr) {
    CSLogTraceEnter("jbyteArray JNIUtil::cstringToJByteArray(%p, \"%s\")", env, cstr);

    jbyteArray res = bytesToJByteArray(env, cstr, strlen(cstr));

    CSLogTraceLeave("jbyteArray JNIUtil::cstringToJByteArray(%p, \"%s\"): %p", env, cstr, res);
    return res;
}

jbyteArray JNIUtil::bytesToJByteArray(JNIEnv *env, const void *data, size_t dataLength) {
    CSLogTraceEnter("jbyteArray JNIUtil::bytesToJByteArray(%p, %p, %zu)", env, data, dataLength);

    jbyteArray res = NULL;
    jbyteArray dataArray = env->NewByteArray(dataLength); // <alloc>
    if(dataArray == NULL || env->ExceptionCheck() == JNI_TRUE)
        CSLogError("Could not create new byte array with length %zu", dataLength);
    else {
        env->SetByteArrayRegion(dataArray, 0, dataLength, (const signed char*) data);
        if(env->ExceptionCheck() == JNI_TRUE)
            CSLogError("Could not set byte array region with length %zu", dataLength);
        else
            res = dataArray;
    }

    if(res == NULL && dataArray != NULL)
        env->DeleteLocalRef(dataArray);

    CSLogTraceLeave("jbyteArray JNIUtil::bytesToJByteArray(%p, %p, %zu): %p", env, data, dataLength, res);
    return res;
}

#define setField(a, b, c) \
    CSLogTraceEnter("bool JNIUtil::set" #a "Field(%p, %p, %p, \"%s\", %" b ")", env, fieldClass, \
            fieldObject, fieldName, value); \
    \
    bool res = false; \
    jfieldID fieldID = env->GetFieldID(fieldClass, fieldName, c); \
    if(fieldID != NULL) { \
        env->Set##a##Field(fieldObject, fieldID, value); \
        res = true; \
    } \
    \
    CSLogTraceLeave("bool JNIUtil::set" #a "Field(%p, %p, %p, \"%s\", %" b "): %d", env, fieldClass, \
            fieldObject, fieldName, value, res); \
    return res;


#define getField(a, c) \
    CSLogTraceEnter("bool JNIUtil::get" #a "Field(%p, %p, %p, \"%s\", %p)", env, fieldClass, \
            fieldObject, fieldName, target); \
    \
    bool res = false; \
    jfieldID fieldID = env->GetFieldID(fieldClass, fieldName, c); \
    if(fieldID != NULL) { \
        *target = env->Get##a##Field(fieldObject, fieldID); \
        res = true; \
    } \
    \
    CSLogTraceLeave("bool JNIUtil::get" #a "Field(%p, %p, %p, \"%s\", %p): %d", env, fieldClass, \
            fieldObject, fieldName, target, res); \
    return res;

bool JNIUtil::setBooleanField(JNIEnv *env, jclass fieldClass, jobject fieldObject,
        const char *fieldName, jboolean value) {
    setField(Boolean, "d", "Z");
    /*CSLogTraceEnter("bool setBooleanField(%p, %p, %p, \"%s\", %d)", env, fieldClass, fieldObject,
            fieldName, value);
    jfieldID fieldID = env->GetFieldID(fieldClass, fieldName, "Z");
    if(fieldID == NULL)
        return false;

    env->SetBooleanField(fieldObject, fieldID, value);

    return true;*/
}

bool JNIUtil::setIntField(JNIEnv *env, jclass fieldClass, jobject fieldObject,
        const char *fieldName, jint value) {
    setField(Int, PRId32, "I");
    /*CSLogTraceEnter("bool setIntField(%p, %p, %p, \"%s\", %" PRId32 ")", env, fieldClass,
            fieldObject, fieldName, value);
    jfieldID fieldID = env->GetFieldID(fieldClass, fieldName, "I");
    if(fieldID == NULL)
        return false;

    env->SetIntField(fieldObject, fieldID, value);

    return true;*/
}

bool JNIUtil::setLongField(JNIEnv *env, jclass fieldClass, jobject fieldObject,
        const char *fieldName, jlong value) {
    setField(Long, PRId64, "J");
    /*CSLogTraceEnter("bool setLongField(%p, %p, %p, \"%s\", %" PRId64 ")", env, fieldClass,
            fieldObject, fieldName, value);

    bool res = false;
    jfieldID fieldID = env->GetFieldID(fieldClass, fieldName, "J");
    if(fieldID != NULL) {
        env->SetLongField(fieldObject, fieldID, value);
        res = true;
    }

    CSLogTraceLeave("bool setLongField(%p, %p, %p, \"%s\", %" PRId64 "): %d", env, fieldClass,
            fieldObject, fieldName, value, res);
    return res;*/
}

bool JNIUtil::getBooleanField(JNIEnv *env, jclass fieldClass, jobject fieldObject,
        const char *fieldName, jboolean *target) {
    getField(Boolean, "Z");
    /*jfieldID fieldID = env->GetFieldID(fieldClass, fieldName, "Z");
    if(fieldID == NULL)
        return false;

    *target = env->GetBooleanField(fieldObject, fieldID);
    return true;*/
}

bool JNIUtil::getIntField(JNIEnv *env, jclass fieldClass, jobject fieldObject,
        const char *fieldName, jint *target) {
    getField(Int, "I");
    /*jfieldID fieldID = env->GetFieldID(fieldClass, fieldName, "I");
    if(fieldID == NULL)
        return false;

    *target = env->GetIntField(fieldObject, fieldID);
    return true;*/
}

bool JNIUtil::getLongField(JNIEnv *env, jclass fieldClass, jobject fieldObject,
        const char *fieldName, jlong *target) {
    getField(Long, "J");
    /*jfieldID fieldID = env->GetFieldID(fieldClass, fieldName, "J");
    if(fieldID == NULL)
        return false;

    *target = env->GetLongField(fieldObject, fieldID);
    return true;*/
}

#undef getField
#undef setField

