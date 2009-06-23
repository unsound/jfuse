/* 
 * File:   common.h
 * Author: erik
 *
 * Created on den 10 juni 2009, 07:22
 */

#ifndef _COMMON_H
#define	_COMMON_H

#include <jni.h>

/**
 * Throws a Java exception using the exception class referenced to by
 * <code>name</code>, with an exception message set to the UTF-string
 * <code>msg</code>.
 * Example: throwByName(env, "java/lang/RuntimeException", "My Message");
 */
bool throwByName(JNIEnv *env, const char *name, const char *msg);

static inline bool throwRuntimeException(JNIEnv *env, const char *msg){
    return throwByName(env, "java/lang/RuntimeException", msg);
}

#endif	/* _COMMON_H */

