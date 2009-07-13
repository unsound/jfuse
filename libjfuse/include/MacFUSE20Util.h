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

#ifndef _MACFUSE20UTIL_H
#define	_MACFUSE20UTIL_H

#if defined(__APPLE__) || defined(__DARWIN__)
#if (__FreeBSD__ >= 10)

#if FUSE_USE_VERSION != 26
#define FUSE_USE_VERSION 26
#endif

#include "JNIUtil.h"

#include <fuse.h>

class MacFUSE20Util : JNIUtil {
public:
    /**
     * Merges the contents of attrObject into the struct setattr_x target.
     */
    static bool mergeSetattr_x(JNIEnv *env, jobject attrObject,
            struct setattr_x *target);

    /**
     * Fills in the fields of attrObject (Java class Setattr_x) from the fields
     * of attr (struct setattr_x).
     */
    static bool fillSetattr_x(JNIEnv *env, const struct setattr_x *attr,
            jobject attrObject);

    /**
     * Creates a new Setattr_x object and fills it using the fields in
     * <code>attr</code>.
     */
    static jobject newSetattr_x(JNIEnv *env, const struct setattr_x *attr);
    
};

#endif /* __FreeBSD__ >= 10 */
#endif /* defined(__APPLE__) || defined(__DARWIN__) */

#endif	/* _MACFUSE20UTIL_H */

