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

#include "org_catacombae_jfuse_types_system_Errno.h"
#include "common.h"
#include "CSLog.h"

#include <errno.h>
#include <string.h>
#define __STDC_FORMAT_MACROS
#include <inttypes.h>

/*
 * Class:     org_catacombae_jfuse_types_system_Errno
 * Method:    getNativeErrnoValue
 * Signature: (Ljava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_org_catacombae_jfuse_types_system_Errno_getNativeErrnoValue
  (JNIEnv *env, jclass cls, jstring errnoName) {
#define _FNAME_ \
    "Java_org_catacombae_jfuse_types_system_Errno_getNativeErrnoValue"

    CSLogTraceEnter("jint %s(%p, %p, %p)", _FNAME_, env, cls, errnoName);
    jint result = -1;
    const char *errnoNameChars = env->GetStringUTFChars(errnoName, NULL);

    // One truth.
#define iferrno(a) else if(strcmp(#a, errnoNameChars) == 0) result = a

    if(0);
    iferrno(EPERM);
    iferrno(ENOENT);
    iferrno(ESRCH);
    iferrno(EINTR);
    iferrno(EIO);
    iferrno(ENXIO);
    iferrno(E2BIG);
    iferrno(ENOEXEC);
    iferrno(EBADF);
    iferrno(ECHILD);
    iferrno(EDEADLK);
    iferrno(ENOMEM);
    iferrno(EACCES);
    iferrno(EFAULT);
    iferrno(ENOTBLK);
    iferrno(EBUSY);
    iferrno(EEXIST);
    iferrno(EXDEV);
    iferrno(ENODEV);
    iferrno(ENOTDIR);
    iferrno(EISDIR);
    iferrno(EINVAL);
    iferrno(ENFILE);
    iferrno(EMFILE);
    iferrno(ENOTTY);
    iferrno(ETXTBSY);
    iferrno(EFBIG);
    iferrno(ENOSPC);
    iferrno(ESPIPE);
    iferrno(EROFS);
    iferrno(EMLINK);
    iferrno(EPIPE);
    iferrno(EDOM);
    iferrno(ERANGE);
    iferrno(EAGAIN);
    iferrno(EWOULDBLOCK);
    iferrno(EINPROGRESS);
    iferrno(EALREADY);
    iferrno(ENOTSOCK);
    iferrno(EDESTADDRREQ);
    iferrno(EMSGSIZE);
    iferrno(EPROTOTYPE);
    iferrno(ENOPROTOOPT);
    iferrno(EPROTONOSUPPORT);
    iferrno(ESOCKTNOSUPPORT);
    iferrno(ENOTSUP);
    iferrno(EOPNOTSUPP);
    iferrno(EPFNOSUPPORT);
    iferrno(EAFNOSUPPORT);
    iferrno(EADDRINUSE);
    iferrno(EADDRNOTAVAIL);
    iferrno(ENETDOWN);
    iferrno(ENETUNREACH);
    iferrno(ENETRESET);
    iferrno(ECONNABORTED);
    iferrno(ECONNRESET);
    iferrno(ENOBUFS);
    iferrno(EISCONN);
    iferrno(ENOTCONN);
    iferrno(ESHUTDOWN);
    iferrno(ETOOMANYREFS);
    iferrno(ETIMEDOUT);
    iferrno(ECONNREFUSED);
    iferrno(ELOOP);
    iferrno(ENAMETOOLONG);
    iferrno(EHOSTDOWN);
    iferrno(EHOSTUNREACH);
    iferrno(ENOTEMPTY);
    //iferrno(EPROCLIM);
    iferrno(EUSERS);
    iferrno(EDQUOT);
    iferrno(ESTALE);
    iferrno(EREMOTE);
    //iferrno(EBADRPC);
    //iferrno(ERPCMISMATCH);
    //iferrno(EPROGUNAVAIL);
    //iferrno(EPROGMISMATCH);
    //iferrno(EPROCUNAVAIL);
    iferrno(ENOLCK);
    iferrno(ENOSYS);
    //iferrno(EFTYPE);
    //iferrno(EAUTH);
    //iferrno(ENEEDAUTH);
    //iferrno(EPWROFF);
    //iferrno(EDEVERR);
    iferrno(EOVERFLOW);
    //iferrno(EBADEXEC);
    //iferrno(EBADARCH);
    //iferrno(ESHLIBVERS);
    //iferrno(EBADMACHO);
    iferrno(ECANCELED);
    iferrno(EIDRM);
    iferrno(ENOMSG);
    iferrno(EILSEQ);
    //iferrno(ENOATTR);
    iferrno(EBADMSG);
    iferrno(EMULTIHOP);
    iferrno(ENODATA);
    iferrno(ENOLINK);
    iferrno(ENOSR);
    iferrno(ENOSTR);
    iferrno(EPROTO);
    iferrno(ETIME);
    //iferrno(ELAST);

#undef iferrno
    else {
        // If we got here, the ERRNO is unrecognized.
        CSLogError("Could not find a matching ERRNO value for \"%s\"", errnoNameChars);
        throwByName(env, "java/lang/RuntimeException", "Unrecognized Errno value!");
    }

    env->ReleaseStringUTFChars(errnoName, errnoNameChars);

    CSLogTraceLeave("jint %s(%p, %p, %p): %" PRId32 "", _FNAME_, env, cls,
            errnoName, (int32_t)result);
    return result;
}
