/* 
 * File:   JNIUtil.h
 * Author: erik
 *
 * Created on den 13 juni 2009, 13:27
 */

#ifndef _JNIUTIL_H
#define	_JNIUTIL_H

#include <jni.h>

class JNIUtil {
public:
    static jbyteArray cstringToJByteArray(JNIEnv *env, const char *cstr);
    static jbyteArray bytesToJByteArray(JNIEnv *env, const void *cstr, size_t cstrLength);
    static bool setBooleanField(JNIEnv *env, jclass fieldClass, jobject fieldObject,
            const char *fieldName, jboolean value);

    static bool setIntField(JNIEnv *env, jclass fieldClass, jobject fieldObject,
            const char *fieldName, jint value);

    static bool setLongField(JNIEnv *env, jclass fieldClass, jobject fieldObject,
            const char *fieldName, jlong value);

    static bool getBooleanField(JNIEnv *env, jclass fieldClass, jobject fieldObject,
            const char *fieldName, jboolean *target);

    static bool getIntField(JNIEnv *env, jclass fieldClass, jobject fieldObject,
            const char *fieldName, jint *target);

    static bool getLongField(JNIEnv *env, jclass fieldClass, jobject fieldObject,
            const char *fieldName, jlong *target);
};

#endif	/* _JNIUTIL_H */

