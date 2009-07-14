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

#include <unistd.h>

#include "org_catacombae_jfuse_util_FUSEUtil.h"

/*
 * Class:     org_catacombae_jfuse_util_FUSEUtil
 * Method:    getProcessUidNative
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_org_catacombae_jfuse_util_FUSEUtil_getProcessUidNative
  (JNIEnv *env, jclass clazz) {
    return (jlong) getuid();
}

/*
 * Class:     org_catacombae_jfuse_util_FUSEUtil
 * Method:    getProcessGidNative
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_org_catacombae_jfuse_util_FUSEUtil_getProcessGidNative
  (JNIEnv *env, jclass clazz) {
    return (jlong) getgid();
}

/*
 * Class:     org_catacombae_jfuse_util_FUSEUtil
 * Method:    getProcessPidNative
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_org_catacombae_jfuse_util_FUSEUtil_getProcessPidNative
  (JNIEnv *env, jclass clazz) {
    return (jlong) getpid();
}

