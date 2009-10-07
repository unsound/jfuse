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

#ifdef __linux__
#define __STDC_LIMIT_MACROS
#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#endif

#define LOG_ENABLE_TRACE 0

#include "org_catacombae_jfuse_types_system_NumericalConstant.h"

#include "common.h"
#include "CSLog.h"
#include "JavaSignatures.h"

#include <string.h>
#include <inttypes.h>

#include <sys/fcntl.h>

//#if defined(__NetBSD__)
//#include <sys/extattr.h>
//#endif

#if !defined(__sun__) && !defined(__NetBSD__)
#include <sys/xattr.h>
#endif

#if (defined(__APPLE__) || defined(__DARWIN__)) && !defined(O_SYMLINK)
// This constant is missing from Mac OS X 10.4 headers.
#define O_SYMLINK	0x200000
#endif

/* Testing macros for each platform that jFUSE supports. */
#define T_DARWIN  (defined(__APPLE__) || defined(__DARWIN__))
#define T_LINUX   (defined(__linux__))
#define T_FREEBSD ((__FreeBSD__ >= 10) && !T_DARWIN)
#define T_SOLARIS (defined(__sun__))
#define T_NETBSD  (defined(__NetBSD__))

#if T_DARWIN
#define HEJ
#endif
#if T_LINUX
#define HEJ
#endif
#if T_FREEBSD
#define HEJ
#endif
#if T_SOLARIS
#define HEJ
#endif
#if T_NETBSD
#define HEJ
#endif

/*
 * Class:     org_catacombae_jfuse_types_system_NumericalConstant
 * Method:    getNativeValue
 * Signature: (Ljava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_org_catacombae_jfuse_types_system_NumericalConstant_getNativeValue
  (JNIEnv *env, jclass cls, jstring constantName) {
#define _FNAME_ "Java_org_catacombae_jfuse_types_system_NumericalConstant_getNativeValue"

    CSLogTraceEnter("jint %s(%p, %p, %p)", _FNAME_, env, cls, constantName);
    jint result = -1;
    const char *constantNameChars = env->GetStringUTFChars(constantName, NULL);

    // One truth.
#define else_if_constant2(a, b)			\
    else if(strcmp(#a, constantNameChars) == 0) \
        result = (jint)b
#define else_if_constant(a)	\
    else if(strcmp(#a, constantNameChars) == 0) \
        result = (jint)a

    if(0);

    // Constants from sys/fcntl.h
    else_if_constant(O_ACCMODE); // X
    else_if_constant(O_RDONLY); // X
    else_if_constant(O_WRONLY); // X
    else_if_constant(O_RDWR); // X
    else_if_constant(O_NONBLOCK); // X
    else_if_constant(O_APPEND); // X
    else_if_constant(O_CREAT); // X
    else_if_constant(O_TRUNC); // X
    else_if_constant(O_EXCL); // X
    else_if_constant(O_NOFOLLOW); // X
    else_if_constant(O_SYNC); // X
    else_if_constant(O_NOCTTY); // X
    else_if_constant(O_NDELAY); // X

    // OS conditional constants

#if !T_LINUX && !T_SOLARIS && !T_NETBSD
    /* Confirmed on: Darwin */
    /* Unavailable on: Linux, Solaris, NetBSD */
    else_if_constant(O_SYMLINK);
    else_if_constant(O_EVTONLY);
#endif

#if !T_NETBSD && !T_SOLARIS
    /* Confirmed on: Darwin, Linux */
    /* Unavailable on: NetBSD, Solaris */
    else_if_constant(O_DIRECTORY); // X
#endif

#if !T_SOLARIS
    /* Confirmed on: Darwin, Linux, NetBSD */
    /* Unavailable on: Solaris */
    else_if_constant(O_ASYNC); // X
#endif

#if !T_LINUX && !T_SOLARIS
    /* Confirmed on: Darwin, NetBSD */
    /* Unavailable on: Linux, Solaris */
    else_if_constant(O_SHLOCK);
    else_if_constant(O_EXLOCK);
#endif

#if !T_DARWIN
    /* Confirmed on: Linux */
    /* Unavailable on: Darwin */
    else_if_constant(O_FSYNC); // X
    else_if_constant(O_DIRECT); // X
    else_if_constant(O_NOATIME); // X
    else_if_constant(O_CLOEXEC); // X
#endif

#if !T_DARWIN
    /* Confirmed on: Linux, NetBSD, Solaris */
    /* Unavailable on: Darwin */
    else_if_constant(O_DSYNC); // X
    else_if_constant(O_RSYNC); // X
#endif

#if !T_DARWIN && !T_NETBSD
    /* Confirmed on: Linux, Solaris */
    /* Unavailable on: Darwin, NetBSD */
    else_if_constant(O_LARGEFILE); // X
#endif

#if !T_DARWIN && !T_LINUX && !T_FREEBSD && !T_NETBSD
    /* Confirmed on: Solaris */
    /* Unavailable on: Darwin, Linux, NetBSD */
    else_if_constant(O_NOLINKS);
    else_if_constant(O_XATTR);
#endif

    // Constants from sys/xattr.h

#if !T_LINUX && !T_SOLARIS && !T_NETBSD
    /* Confirmed on: Darwin */
    /* Unavailable on: Linux, Solaris, NetBSD */
    else_if_constant(XATTR_MAXNAMELEN);
#endif

#if !T_SOLARIS && !T_NETBSD
    /* Confirmed on: Darwin, Linux */
    /* Unavailable on: Solaris, NetBSD */
    /* Not applicable for Solaris and NetBSD, who are using another xattr
     * infrastructure. */
    else_if_constant(XATTR_CREATE);
    else_if_constant(XATTR_REPLACE);
#endif

/* NetBSD has a constant called EXATTR_MAXNAMELEN, but it's kernel-private so I
 * don't think it makes sense to export it. */
/*
#if T_NETBSD
    else_if_constant2(XATTR_MAXNAMELEN, EXTATTR_MAXNAMELEN);
#endif
*/

    //else_if_constant();

    else {
        // If we got here, the constant is unrecognized.
        CSLogDebug("Could not find a matching constant value for \"%s\".",
                constantNameChars);
        throwByName(env, NOSUCHCONSTANTEXCEPTION_CLASS,
                "Unrecognized constant value.");
    }

#undef else_if_constant2
#undef else_if_constant

    env->ReleaseStringUTFChars(constantName, constantNameChars);

    CSLogTraceLeave("jint %s(%p, %p, %p): %" PRId32, _FNAME_, env, cls,
            constantName, (int32_t)result);
    return result;
}

