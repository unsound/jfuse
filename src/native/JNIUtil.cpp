/*-
 * jFUSE - FUSE bindings for Java
 * Copyright (C) 2008-2009  Erik Larsson <erik82@kth.se>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include "JNIUtil.h"
#include "CSLog.h"
#include "JavaSignatures.h"

#include <stdlib.h>
#include <string.h>
#include <errno.h>
#define __STDC_FORMAT_MACROS
#include <inttypes.h>

jbyteArray JNIUtil::cstringToJByteArray(JNIEnv *env, const char *cstr) {
    CSLogTraceEnter("jbyteArray JNIUtil::cstringToJByteArray(%p, \"%s\")", env, cstr);

    jbyteArray res = bytesToJByteArray(env, cstr, strlen(cstr));

    CSLogTraceLeave("jbyteArray JNIUtil::cstringToJByteArray(%p, \"%s\"): %p", env, cstr, res);
    return res;
}

jobject JNIUtil::cstringToReadonlyByteBuffer(JNIEnv *env, const char *cstr) {
    CSLogTraceEnter("jbyteArray JNIUtil::cstringToByteBuffer(%p, \"%s\")", env, cstr);

    jobject res = bytesToReadonlyByteBuffer(env, cstr, strlen(cstr));

    CSLogTraceLeave("jbyteArray JNIUtil::cstringToByteBuffer(%p, \"%s\"): %p", env, cstr, res);
    return res;
}

jobject JNIUtil::newByteBuffer(JNIEnv* env, jsize length) {
    CSLogTraceEnter("jbyteArray JNIUtil::newByteBuffer(%p, %" PRId32 ")",
            env, (int32_t)length);

    jobject res = NULL;
    int finalErrno = 0;

    void *backingBuffer = malloc(length);
    if(backingBuffer == NULL) {
        finalErrno = errno;
        CSLogError("Memory error! Could not allocate %" PRId32 " bytes with "
                "malloc: %d (%s)", (int32_t)length, errno, strerror(errno));
    }
    else {
        memset(backingBuffer, 0, length);
        res = bytesToByteBuffer(env, backingBuffer, length);
        finalErrno = errno;
    }

    CSLogTraceLeave("jbyteArray JNIUtil::cstringToByteBuffer(%p, %" PRId32 "): "
            "%p", env, (int32_t)length, res);
    errno = finalErrno;
    return res;

}

jbyteArray JNIUtil::bytesToJByteArray(JNIEnv *env, const void *data,
        jsize dataLength) {
    CSLogTraceEnter("jbyteArray JNIUtil::bytesToJByteArray(%p, %p, %" PRId32
            ")", env, data, (int32_t)dataLength);

    jbyteArray res = NULL;
    jbyteArray dataArray = env->NewByteArray(dataLength); // <alloc>
    if(dataArray == NULL || env->ExceptionCheck() == JNI_TRUE)
        CSLogError("Could not create new byte array with length %" PRId32,
                (int32_t)dataLength);
    else {
        env->SetByteArrayRegion(dataArray, 0, dataLength,
                (const signed char*) data);
        if(env->ExceptionCheck() == JNI_TRUE)
            CSLogError("Could not set byte array region with length %" PRId32,
                    (int32_t)dataLength);
        else
            res = dataArray;
    }

    if(res == NULL && dataArray != NULL)
        env->DeleteLocalRef(dataArray);

    CSLogTraceLeave("jbyteArray JNIUtil::bytesToJByteArray(%p, %p, %" PRId32
            "): %p", env, data, (int32_t)dataLength, res);
    return res;
}

jobject JNIUtil::bytesToByteBuffer(JNIEnv *env, void *data, jsize dataLength) {
    CSLogTraceEnter("jbyteArray JNIUtil::bytesToByteBuffer(%p, %p, %" PRId32
            ")", env, data, (int32_t)dataLength);

    jobject res = NULL;
    jobject dataBuffer = env->NewDirectByteBuffer(data, dataLength); // <alloc>
    if(dataBuffer == NULL || env->ExceptionCheck() == JNI_TRUE) {
        // TODO: Fallback to a byte array backed byte buffer?
        CSLogError("Could not create new direct byte buffer from %p with "
                "length %" PRId32, data, (int32_t)dataLength);
    }
    else {
        res = dataBuffer;
    }

    if(res == NULL && dataBuffer != NULL)
        env->DeleteLocalRef(dataBuffer);

    CSLogTraceLeave("jbyteArray JNIUtil::bytesToByteBuffer(%p, %p, %" PRId32 
            "): %p", env, data, (int32_t)dataLength, res);
    return res;
}

jobject JNIUtil::bytesToReadonlyByteBuffer(JNIEnv *env, const void *data,
        jsize dataLength) {
    CSLogTraceEnter("jbyteArray JNIUtil::bytesToReadonlyByteBuffer(%p, %p, %"
            PRId32 ")", env, data, (int32_t)dataLength);

    jobject res = NULL;
    jobject buf = bytesToByteBuffer(env, (void*)data, dataLength);
    if(buf != NULL && env->ExceptionCheck() == JNI_FALSE) {
        jclass clazz = env->GetObjectClass(buf);
        if(clazz != NULL && env->ExceptionCheck() == JNI_FALSE) {
            const char *name = "asReadOnlyBuffer";
            const char *sig = "()Ljava/nio/ByteBuffer;";
            jmethodID mid = env->GetMethodID(clazz, name, sig);
            if(mid != NULL) {
                jobject callres = env->CallObjectMethod(buf, mid);
                if(callres != NULL && env->ExceptionCheck() == JNI_FALSE) {
                    env->DeleteLocalRef(buf);
                    res = callres;
                }
                else
                    CSLogError("Calling ByteBuffer.asReadOnlyBuffer failed. "
                            "callRes=%p", callres);
            }
            else
                CSLogError("Could not get method id for "
                        "ByteBuffer.asReadOnlyBuffer. mid=%p", mid);
        }
        else
            CSLogError("Could not get class for object %p.", buf);
    }
    else
        CSLogError("bytesToByteBuffer returned with an error.");

    CSLogTraceLeave("jbyteArray JNIUtil::bytesToReadonlyByteBuffer(%p, %p, %"
            PRId32 "): %p", env, data, (int32_t)dataLength, res);
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
}

bool JNIUtil::setShortField(JNIEnv *env, jclass fieldClass, jobject fieldObject,
        const char *fieldName, jshort value2) {
    uint16_t value = value2;
    setField(Short, PRId16, "S");
}

bool JNIUtil::setIntField(JNIEnv *env, jclass fieldClass, jobject fieldObject,
        const char *fieldName, jint value2) {
    uint32_t value = value2;
    setField(Int, PRId32, "I");
}

bool JNIUtil::setLongField(JNIEnv *env, jclass fieldClass, jobject fieldObject,
        const char *fieldName, jlong value) {
    setField(Long, PRId64, "J");
}

bool JNIUtil::getBooleanField(JNIEnv *env, jclass fieldClass, jobject fieldObject,
        const char *fieldName, jboolean *target) {
    getField(Boolean, "Z");
}

bool JNIUtil::getShortField(JNIEnv *env, jclass fieldClass, jobject fieldObject,
        const char *fieldName, jshort *target) {
    getField(Short, "S");
}

bool JNIUtil::getIntField(JNIEnv *env, jclass fieldClass, jobject fieldObject,
        const char *fieldName, jint *target) {
    getField(Int, "I");
}

bool JNIUtil::getLongField(JNIEnv *env, jclass fieldClass, jobject fieldObject,
        const char *fieldName, jlong *target) {
    getField(Long, "J");
}

#undef getField
#undef setField

