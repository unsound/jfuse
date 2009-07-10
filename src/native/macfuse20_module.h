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

#ifndef _MACFUSE20_MODULE_H
#define	_MACFUSE20_MODULE_H

#define FUSE_USE_VERSION 26

#include "MacFUSE20Util.h"

#include <fuse.h>

/*
 * Function definitions for our MacFUSE specific jFUSE callbacks.
 */

#if defined(__APPLE__) || defined(__DARWIN__)
#if (__FreeBSD__ >= 10)

//int jfuse_setvolname(const char *path);

int jfuse_exchange(const char *path1, const char *path2, unsigned long options);

int jfuse_getxtimes(const char *path, struct timespec *bkuptime,
        struct timespec *crtime);

int jfuse_setbkuptime(const char *path, const struct timespec *tv);

//int jfuse_setchgtime(const char *path, const struct timespec *tv);

int jfuse_setcrtime(const char *path, const struct timespec *tv);

int jfuse_chflags(const char *path, uint32_t flags);

int jfuse_setattr_x(const char *path, struct setattr_x *attr);

int jfuse_fsetattr_x(const char *path, struct setattr_x *attr,
        struct fuse_file_info *fi);

#define JAVA_ARG_SETATTR_X(num, attr) \
    CSLogDebug("Processing argument %d (%s) of type struct setattr_x...", num, #attr); \
    jobject java_arg##num = MacFUSE20Util::newSetattr_x(env, attr); \
    if(java_arg##num == NULL) { \
        if(env->ExceptionCheck() == JNI_TRUE) \
            env->ExceptionDescribe(); \
        CSPanicWithMessage("Could not create new Java Setattr_x object from setattr_x buffer."); \
    }

#define JFUSE_MERGE_SETATTR_X(attr_object, attr) \
        if(env->ExceptionCheck() == JNI_FALSE) { \
            if(!MacFUSE20Util::mergeSetattr_x(env, attr_object, attr)) \
                CSPanicWithMessage("Could not merge Setattr_x -> struct setattr_x"); \
        }

#endif /* __FreeBSD__ >= 10 */
#endif /* defined(__APPLE__) || defined(__DARWIN__) */

#endif	/* _MACFUSE20_MODULE_H */

