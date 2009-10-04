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

#define __STDC_FORMAT_MACROS

#define LOG_ENABLE_TRACE 0

#include "org_catacombae_jfuse_types_system_StringConstant.h"

#include "common.h"
#include "CSLog.h"
#include "JavaSignatures.h"

#include <string.h>
#include <inttypes.h>

#if !defined(__sun__) && !defined(__NetBSD__)
#include <sys/xattr.h>
#endif

/*
 * Class:     org_catacombae_jfuse_types_system_StringConstant
 * Method:    getNativeValue
 * Signature: (Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_catacombae_jfuse_types_system_StringConstant_getNativeValue
  (JNIEnv *env, jclass cls, jstring constantName) {
#define _FNAME_ "Java_org_catacombae_jfuse_types_system_StringConstant_getNativeValue"

    CSLogTraceEnter("jstring %s(%p, %p, %p)", _FNAME_, env, cls, constantName);
    jstring result = NULL;
    const char *constantNameChars = env->GetStringUTFChars(constantName, NULL);

    // One truth.
#define else_if_constant(a) \
    else if(strcmp(#a, constantNameChars) == 0) \
        result = env->NewStringUTF(a)

    if(0);

#if defined(__linux__) || defined(__sun__) || defined(__NetBSD__)
    // Getting these variables dynamically from headers is just madness.
    #define XATTR_FINDERINFO_NAME	  "com.apple.FinderInfo"
    #define XATTR_RESOURCEFORK_NAME	  "com.apple.ResourceFork"
#endif

    // Constants from sys/xattr.h
    else_if_constant(XATTR_FINDERINFO_NAME);
    else_if_constant(XATTR_RESOURCEFORK_NAME);
    
    else {
        // If we got here, the constant is unrecognized.
        CSLogError("Could not find a matching constant value for \"%s\"", constantNameChars);
        throwByName(env, NOSUCHCONSTANTEXCEPTION_CLASS, "Unrecognized constant value!");
    }

#undef else_if_constant

    env->ReleaseStringUTFChars(constantName, constantNameChars);

    CSLogTraceLeave("jstring %s(%p, %p, %p): %p", _FNAME_, env, cls,
            constantName, result);
    return result;
}
