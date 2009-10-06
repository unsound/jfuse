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

#include "macfuse20_module.h"

#include "fuse26_module.h"
#include "CSLog.h"
#include "JavaSignatures.h"

#include <errno.h>
#define __STDC_FORMAT_MACROS
#include <inttypes.h>

#if defined(__APPLE__) || defined(__DARWIN__)
#if (__FreeBSD__ >= 10)

#define OP_NAME(a) OPS_##a##_NAME
#define OP_SIGNATURE(a) OPS_##a##_NAME

/*
int jfuse_setvolname(const char *path) {
#define _FNAME_ "jfuse_setvolname"
    CSLogTraceEnter("int " _FNAME_ "(%p)", path);
    CSLogTrace("  path=\"%s\"", path);

    int retval = -EIO;
    JFUSE_OPERATION_INIT();
    JAVA_ARG_CSTRING_BYTEBUFFER(1, path);

    JFUSE_FS_PROVIDER_METHOD_OK(SETVOLNAME) {
        JFUSE_FS_PROVIDER_CALL(JAVA_ARG(1));

        JFUSE_SET_RETVAL();
    }

    JAVA_ARG_CLEANUP(1);

    JAVA_EXCEPTION_CHECK(_FNAME_);

    CSLogTraceLeave("int " _FNAME_ "(%p): %d", path, retval);

    return retval;
#undef _FNAME_
}
*/

int jfuse_exchange(const char *path1, const char *path2, unsigned long options) {
#define _FNAME_ "jfuse_exchange"
    CSLogTraceEnter("int " _FNAME_ "(%p, %p, %lu)", path1, path2, options);
    CSLogTrace("  path1=\"%s\"", path1);
    CSLogTrace("  path2=\"%s\"", path2);

    int retval = -EIO;
    JFUSE_OPERATION_INIT();

    JAVA_ARG_CSTRING_BYTEBUFFER(1, path1);
    JAVA_ARG_CSTRING_BYTEBUFFER(2, path2);

    JFUSE_FS_PROVIDER_METHOD_OK(EXCHANGE) {
        JFUSE_FS_PROVIDER_CALL(JAVA_ARG(1), JAVA_ARG(2), (jlong)options);

        JFUSE_SET_RETVAL();
    }

    JAVA_ARG_CLEANUP(2);
    JAVA_ARG_CLEANUP(1);

    JAVA_EXCEPTION_CHECK(_FNAME_);

    CSLogTraceLeave("int " _FNAME_ "(%p, %p, %lu): %d", path1, path2, options, retval);

    return retval;
#undef _FNAME_
}

int jfuse_getxtimes(const char *path, struct timespec *bkuptime,
        struct timespec *crtime) {
#define _FNAME_ "jfuse_getxtimes"
    CSLogTraceEnter("int " _FNAME_ "(%p, %p, %p)", path, bkuptime, crtime);
    CSLogTrace("  path=\"%s\"", path);

    int retval = -EIO;
    JFUSE_OPERATION_INIT();

    JAVA_ARG_CSTRING_BYTEBUFFER(1, path);
    JAVA_ARG_TIMESPEC(2, bkuptime);
    JAVA_ARG_TIMESPEC(3, crtime);

    JFUSE_FS_PROVIDER_METHOD_OK(GETXTIMES) {
        JFUSE_FS_PROVIDER_CALL(JAVA_ARG(1), JAVA_ARG(2), JAVA_ARG(3));

        JFUSE_MERGE_TIMESPEC(JAVA_ARG(2), bkuptime);
        JFUSE_MERGE_TIMESPEC(JAVA_ARG(3), crtime);

        JFUSE_SET_RETVAL();
    }

    JAVA_ARG_CLEANUP(3);
    JAVA_ARG_CLEANUP(2);
    JAVA_ARG_CLEANUP(1);

    JAVA_EXCEPTION_CHECK(_FNAME_);

    CSLogTraceLeave("int " _FNAME_ "(%p, %p, %p): %d", path, bkuptime, crtime,
            retval);

    return retval;
#undef _FNAME_
}

int jfuse_setbkuptime(const char *path, const struct timespec *tv) {
#define _FNAME_ "jfuse_setbkuptime"
    CSLogTraceEnter("int " _FNAME_ "(%p, %p)", path, tv);
    CSLogTrace("  path=\"%s\"", path);

    int retval = -EIO;
    JFUSE_OPERATION_INIT();

    JAVA_ARG_CSTRING_BYTEBUFFER(1, path);
    JAVA_ARG_TIMESPEC(2, tv);

    JFUSE_FS_PROVIDER_METHOD_OK(SETBKUPTIME) {
        JFUSE_FS_PROVIDER_CALL(JAVA_ARG(1), JAVA_ARG(2));

        JFUSE_SET_RETVAL();
    }

    JAVA_ARG_CLEANUP(2);
    JAVA_ARG_CLEANUP(1);

    JAVA_EXCEPTION_CHECK(_FNAME_);

    CSLogTraceLeave("int " _FNAME_ "(%p, %p): %d", path, tv, retval);

    return retval;
#undef _FNAME_
}

int jfuse_setchgtime(const char *path, const struct timespec *tv) {
#define _FNAME_ "jfuse_setchgtime"
    CSLogTraceEnter("int " _FNAME_ "(%p, %p)", path, tv);
    CSLogTrace("  path=\"%s\"", path);

    int retval = -EIO;
    JFUSE_OPERATION_INIT();

    JAVA_ARG_CSTRING_BYTEBUFFER(1, path);
    JAVA_ARG_TIMESPEC(2, tv);

    JFUSE_FS_PROVIDER_METHOD_OK(SETCHGTIME) {
        JFUSE_FS_PROVIDER_CALL(JAVA_ARG(1), JAVA_ARG(2));

        JFUSE_SET_RETVAL();
    }

    JAVA_ARG_CLEANUP(2);
    JAVA_ARG_CLEANUP(1);

    JAVA_EXCEPTION_CHECK(_FNAME_);

    CSLogTraceLeave("int " _FNAME_ "(%p, %p): %d", path, tv, retval);

    return retval;
#undef _FNAME_
}

int jfuse_setcrtime(const char *path, const struct timespec *tv) {
#define _FNAME_ "jfuse_setcrtime"
    CSLogTraceEnter("int " _FNAME_ "(%p, %p)", path, tv);
    CSLogTrace("  path=\"%s\"", path);

    int retval = -EIO;
    JFUSE_OPERATION_INIT();

    JAVA_ARG_CSTRING_BYTEBUFFER(1, path);
    JAVA_ARG_TIMESPEC(2, tv);

    JFUSE_FS_PROVIDER_METHOD_OK(SETCRTIME) {
        JFUSE_FS_PROVIDER_CALL(JAVA_ARG(1), JAVA_ARG(2));

        JFUSE_SET_RETVAL();
    }

    JAVA_ARG_CLEANUP(2);
    JAVA_ARG_CLEANUP(1);

    JAVA_EXCEPTION_CHECK(_FNAME_);

    CSLogTraceLeave("int " _FNAME_ "(%p, %p): %d", path, tv, retval);

    return retval;
#undef _FNAME_
}

int jfuse_chflags(const char *path, uint32_t flags) {
#define _FNAME_ "jfuse_chflags"
    CSLogTraceEnter("int " _FNAME_ "(%p, %" PRIu32 ")", path, flags);
    CSLogTrace("  path=\"%s\"", path);

    int retval = -EIO;
    JFUSE_OPERATION_INIT();

    JAVA_ARG_CSTRING_BYTEBUFFER(1, path);

    JFUSE_FS_PROVIDER_METHOD_OK(CHFLAGS) {
        JFUSE_FS_PROVIDER_CALL(JAVA_ARG(1), (jint)flags);

        JFUSE_SET_RETVAL();
    }

    JAVA_ARG_CLEANUP(1);

    JAVA_EXCEPTION_CHECK(_FNAME_);

    CSLogTraceLeave("int " _FNAME_ "(%p, %" PRIu32 "): %d", path, flags,
            retval);

    return retval;
#undef _FNAME_
}

int jfuse_setattr_x(const char *path, struct setattr_x *attr) {
#define _FNAME_ "jfuse_setattr_x"
    CSLogTraceEnter("int " _FNAME_ "(%p, %p)", path, attr);
    CSLogTrace("  path=\"%s\"", path);

    int retval = -EIO;
    JFUSE_OPERATION_INIT();

    JAVA_ARG_CSTRING_BYTEBUFFER(1, path);
    JAVA_ARG_SETATTR_X(2, attr);

    JFUSE_FS_PROVIDER_METHOD_OK(SETATTR_X) {
        JFUSE_FS_PROVIDER_CALL(JAVA_ARG(1), JAVA_ARG(2));

        JFUSE_MERGE_SETATTR_X(JAVA_ARG(2), attr);

        JFUSE_SET_RETVAL();
    }

    JAVA_ARG_CLEANUP(2);
    JAVA_ARG_CLEANUP(1);

    JAVA_EXCEPTION_CHECK(_FNAME_);

    CSLogTraceLeave("int " _FNAME_ "(%p, %p): %d", path, attr, retval);

    return retval;
#undef _FNAME_
}

int jfuse_fsetattr_x(const char *path, struct setattr_x *attr,
        struct fuse_file_info *fi) {
#define _FNAME_ "jfuse_fsetattr_x"
    CSLogTraceEnter("int " _FNAME_ "(%p, %p, %p)", path, attr, fi);
    CSLogTrace("  path=\"%s\"", path);

    int retval = -EIO;
    JFUSE_OPERATION_INIT();

    JAVA_ARG_CSTRING_BYTEBUFFER(1, path);
    JAVA_ARG_SETATTR_X(2, attr);
    JAVA_ARG_FUSE_FILE_INFO(3, fi);

    JFUSE_FS_PROVIDER_METHOD_OK(FSETATTR_X) {
        JFUSE_FS_PROVIDER_CALL(JAVA_ARG(1), JAVA_ARG(2), JAVA_ARG(3));

        JFUSE_MERGE_SETATTR_X(JAVA_ARG(2), attr);
        JFUSE_MERGE_FUSE_FILE_INFO(JAVA_ARG(3), fi);

        JFUSE_SET_RETVAL();
    }

    JAVA_ARG_CLEANUP(3);
    JAVA_ARG_CLEANUP(2);
    JAVA_ARG_CLEANUP(1);

    JAVA_EXCEPTION_CHECK(_FNAME_);

    CSLogTraceLeave("int " _FNAME_ "(%p, %p, %p): %d", path, attr, fi, retval);

    return retval;
#undef _FNAME_
}

#endif /* __FreeBSD__ >= 10 */
#endif /* defined(__APPLE__) || defined(__DARWIN__) */
