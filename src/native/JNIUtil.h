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

#ifndef _JNIUTIL_H
#define	_JNIUTIL_H

#include <jni.h>

class JNIUtil {
public:
    static jbyteArray cstringToJByteArray(JNIEnv *env, const char *cstr);
    static jbyteArray bytesToJByteArray(JNIEnv *env, const void *data, jsize dataLength);

    static jobject newByteBuffer(JNIEnv *env, jsize length);
    static jobject cstringToReadonlyByteBuffer(JNIEnv *env, const char *cstr);
    static jobject bytesToByteBuffer(JNIEnv *env, void *data, jsize dataLength);
    static jobject bytesToReadonlyByteBuffer(JNIEnv *env, const void *data, jsize dataLength);
    
    static bool setBooleanField(JNIEnv *env, jclass fieldClass, jobject fieldObject,
            const char *fieldName, jboolean value);

    static bool setShortField(JNIEnv *env, jclass fieldClass, jobject fieldObject,
            const char *fieldName, jshort value);

    static bool setIntField(JNIEnv *env, jclass fieldClass, jobject fieldObject,
            const char *fieldName, jint value);

    static bool setLongField(JNIEnv *env, jclass fieldClass, jobject fieldObject,
            const char *fieldName, jlong value);

    static bool getBooleanField(JNIEnv *env, jclass fieldClass, jobject fieldObject,
            const char *fieldName, jboolean *target);

    static bool getShortField(JNIEnv *env, jclass fieldClass, jobject fieldObject,
                const char *fieldName, jshort *target);

    static bool getIntField(JNIEnv *env, jclass fieldClass, jobject fieldObject,
            const char *fieldName, jint *target);

    static bool getLongField(JNIEnv *env, jclass fieldClass, jobject fieldObject,
            const char *fieldName, jlong *target);
};

#endif	/* _JNIUTIL_H */

