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

#define LOG_ENABLE_TRACE 0

#include "org_catacombae_jfuse_types_system_StatConstant.h"

#include "common.h"
#include "CSLog.h"

#include <string.h>
#define __STDC_FORMAT_MACROS
#include <inttypes.h>
#include <sys/stat.h>

/*
 * Class:     org_catacombae_jfuse_types_system_StatConstant
 * Method:    getNativeValue
 * Signature: (Ljava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_org_catacombae_jfuse_types_system_StatConstant_getNativeValue
  (JNIEnv *env, jclass cls, jstring constantName) {
#define _FNAME_ "Java_org_catacombae_jfuse_types_system_StatConstant_getNativeValue"

    CSLogTraceEnter("jint %s(%p, %p, %p)", _FNAME_, env, cls, constantName);
    jint result = -1;
    const char *constantNameChars = env->GetStringUTFChars(constantName, NULL);

    // One truth.
#define ifconstant(a) else if(strcmp(#a, constantNameChars) == 0) result = a

    if(0);
    ifconstant(S_IFMT);
    ifconstant(S_IFIFO);
    ifconstant(S_IFCHR);
    ifconstant(S_IFDIR);
    ifconstant(S_IFBLK);
    ifconstant(S_IFREG);
    ifconstant(S_IFLNK);
    ifconstant(S_IFSOCK);
    //ifconstant(S_IFWHT);
    ifconstant(S_ISUID);
    ifconstant(S_ISGID);
    ifconstant(S_ISVTX);
    ifconstant(S_IRUSR);
    ifconstant(S_IWUSR);
    ifconstant(S_IXUSR);

#undef ifconstant
    else {
        // If we got here, the constant is unrecognized.
        CSLogError("Could not find a matching constant value for \"%s\"", constantNameChars);
        throwByName(env, "java/lang/RuntimeException", "Unrecognized constant value!");
    }

    env->ReleaseStringUTFChars(constantName, constantNameChars);

    CSLogTraceLeave("jint %s(%p, %p, %p): %" PRId32, _FNAME_, env, cls,
            constantName, (int32_t)result);
    return result;

}

