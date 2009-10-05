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

#if (defined(__APPLE__) || defined(__DARWIN__)) && !defined(O_SYMLINK)
// This constant is missing from Mac OS X 10.4 headers.
#define O_SYMLINK	0x200000
#endif

/* Testing macros for each platform that jFUSE supports. */
#define T_DARWIN  (defined(__APPLE__) || defined(__DARWIN__))
#define T_LINUX   (defined(__linux__))
#define T_FREEBSD ((__FreeBSD__ > 0) && !T_DARWIN)
#define T_SOLARIS (defined(__sun__))
#define T_NETBSD  (defined(__NetBSD__))

/* Safeguard against multiple platform detection. */

#if T_DARWIN
#ifndef T_PLATFORM
#define T_PLATFORM "Darwin"
#else
#error Multiple platforms detected.
#endif
#endif

#if T_LINUX
#ifndef T_PLATFORM
#define T_PLATFORM "Linux"
#else
#error Multiple platforms detected.
#endif
#endif

#if T_FREEBSD
#ifndef T_PLATFORM
#define T_PLATFORM "FreeBSD"
#else
#error Multiple platforms detected.
#endif
#endif

#if T_SOLARIS
#ifndef T_PLATFORM
#define T_PLATFORM "Solaris"
#else
#error Multiple platforms detected.
#endif
#endif

#if T_NETBSD
#ifndef T_PLATFORM
#define T_PLATFORM "NetBSD"
#else
#error Multiple platforms detected.
#endif
#endif

#if !defined(T_PLATFORM)
#error No known platform detected!
#endif

#if T_LINUX || T_DARWIN
#include <sys/xattr.h>
/*
#elif T_FREEBSD || T_NETBSD
#include <sys/extattr.h>
*/
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
    else_if_constant(O_ACCMODE);
    else_if_constant(O_RDONLY);
    else_if_constant(O_WRONLY);
    else_if_constant(O_RDWR);
    else_if_constant(O_NONBLOCK);
    else_if_constant(O_APPEND);
    else_if_constant(O_CREAT);
    else_if_constant(O_TRUNC);
    else_if_constant(O_EXCL);
    else_if_constant(O_NOFOLLOW);
    else_if_constant(O_SYNC);
    else_if_constant(O_NOCTTY);
    else_if_constant(O_NDELAY);

    // OS conditional constants

#if !T_FREEBSD && !T_LINUX && !T_SOLARIS && !T_NETBSD
    /* Confirmed on: Darwin */
    /* Unavailable on: FreeBSD, Linux, NetBSD, Solaris */
    else_if_constant(O_SYMLINK);
    else_if_constant(O_EVTONLY);
#endif

#if !T_FREEBSD && !T_NETBSD && !T_SOLARIS
    /* Confirmed on: Darwin, Linux */
    /* Unavailable on: FreeBSD, NetBSD, Solaris */
    else_if_constant(O_DIRECTORY);
#endif

#if !T_SOLARIS
    /* Confirmed on: Darwin, FreeBSD, Linux, NetBSD */
    /* Unavailable on: Solaris */
    else_if_constant(O_ASYNC);
#endif

#if !T_LINUX && !T_SOLARIS
    /* Confirmed on: Darwin, FreeBSD, NetBSD */
    /* Unavailable on: Linux, Solaris */
    else_if_constant(O_SHLOCK);
    else_if_constant(O_EXLOCK);
#endif

#if !T_DARWIN
    /* Confirmed on: Linux, FreeBSD */
    /* Unavailable on: Darwin */
    else_if_constant(O_FSYNC);
    else_if_constant(O_DIRECT);
#endif

#if !T_DARWIN && !T_FREEBSD
    /* Confirmed on: Linux, NetBSD, Solaris */
    /* Unavailable on: Darwin, FreeBSD */
    else_if_constant(O_DSYNC);
    else_if_constant(O_RSYNC);
#endif

#if !T_DARWIN && !T_FREEBSD && !T_NETBSD
    /* Confirmed on: Linux */
    /* Unavailable on: Darwin, FreeBSD, NetBSD */
    else_if_constant(O_NOATIME);
    else_if_constant(O_CLOEXEC);
#endif

#if !T_DARWIN && !T_FREEBSD && !T_NETBSD
    /* Confirmed on: Linux, Solaris */
    /* Unavailable on: Darwin, FreeBSD, NetBSD */
    else_if_constant(O_LARGEFILE);
#endif

#if !T_DARWIN && !T_FREEBSD && !T_LINUX && !T_NETBSD
    /* Confirmed on: Solaris */
    /* Unavailable on: Darwin, FreeBSD, Linux, NetBSD */
    else_if_constant(O_NOLINKS);
    else_if_constant(O_XATTR);
#endif

    // Constants from sys/xattr.h

#if !T_LINUX && !T_FREEBSD && !T_SOLARIS && !T_NETBSD
    /* Confirmed on: Darwin */
    /* Unavailable on: Linux, FreeBSD, Solaris, NetBSD */
    else_if_constant(XATTR_MAXNAMELEN);
#elif T_FREEBSD || T_NETBSD
    /* *BSD has a constant called EXTATTR_MAXNAMELEN, but it's kernel-private
     * (#ifdef _KERNEL) so I don't think it makes sense to export it. */
    /*
    else_if_constant2(XATTR_MAXNAMELEN, EXTATTR_MAXNAMELEN);
    */
#endif

#if !T_SOLARIS && !T_FREEBSD && !T_NETBSD
    /* Confirmed on: Darwin, Linux */
    /* Unavailable on: FreeBSD, NetBSD, Solaris */
    /* Not applicable for Solaris and *BSD, whose xattr APIs are fundamentally
     * different from the ones in Linux/Mac OS X. */
    else_if_constant(XATTR_CREATE);
    else_if_constant(XATTR_REPLACE);
#endif

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

