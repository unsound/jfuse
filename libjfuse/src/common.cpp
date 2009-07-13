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
