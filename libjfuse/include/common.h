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

#ifndef _COMMON_H
#define	_COMMON_H

#include <jni.h>

/**
 * Throws a Java exception using the exception class referenced to by
 * <code>name</code>, with an exception message set to the UTF-string
 * <code>msg</code>.
 * Example: throwByName(env, "java/lang/RuntimeException", "My Message");
 */
bool throwByName(JNIEnv *env, const char *name, const char *msg);

static inline bool throwRuntimeException(JNIEnv *env, const char *msg){
    return throwByName(env, "java/lang/RuntimeException", msg);
}

#endif	/* _COMMON_H */

