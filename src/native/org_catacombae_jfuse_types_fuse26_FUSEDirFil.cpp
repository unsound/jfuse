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

#include "org_catacombae_jfuse_types_fuse26_FUSEDirFil.h"

#include "CSLog.h"
#include "common.h"
#include "FUSEDirFilContext.h"

#include <stdlib.h>
#define __STDC_FORMAT_MACROS
#include <inttypes.h>
#include <fuse.h>

static bool getPointerFromByteArray(JNIEnv *env,
        jbyteArray contextPointerArray, void **dest) {
    bool result = false;

    jbyteArray ba = contextPointerArray;
    jsize baLength = env->GetArrayLength(ba);
    if(baLength != sizeof(void*) || env->ExceptionCheck() == JNI_TRUE) {
        CSLogError("baLength: %" PRId32 " != sizeof(void*): %zu",
                (int32_t) baLength, sizeof(void*));
        throwByName(env, "java/lang/RuntimeException", "Invalid pointer size.");
    }
    else {
        void *ptr = NULL;
        env->GetByteArrayRegion(ba, 0, baLength, (jbyte*) (&ptr));
        if(env->ExceptionCheck() != JNI_TRUE) {
            *dest = ptr;
            result = true;
        }
    }
    
    return result;
}

/*
 * Class:     org_catacombae_jfuse_types_fuse26_FUSEDirFil
 * Method:    fillNative
 * Signature: ([B[BIJ)I
 */
JNIEXPORT jint JNICALL Java_org_catacombae_jfuse_types_fuse26_FUSEDirFil_fillNative
  (JNIEnv *env, jclass cls, jbyteArray nativeContextPointer, jbyteArray name,
        jint type, jlong ino) {
#define _FNAME_ "Java_org_catacombae_jfuse_types_fuse26_FUSEDirFil_fillNative"
    CSLogTraceEnter("jint " _FNAME_ "(%p, "
            "%p, %p, %p, %" PRId32 ", %" PRId64 ")", env, cls,
            nativeContextPointer, name, (int32_t)type, (int64_t)ino);

#define CheckForErrors(a, b, ...) \
    if((a) || env->ExceptionCheck() == JNI_TRUE) { \
        CSLogError(b, ##__VA_ARGS__); \
        if(env->ExceptionCheck() == JNI_FALSE) \
            throwException = true; \
        break; \
    }

    jint res = -1;
    bool throwException = false;

    char *nameBuf = NULL;
    do {
        // Get the native context pointer from the supplied jbyteArray.
        FUSEDirFilContext *fill_ctx;

        bool gpres =
                getPointerFromByteArray(env, nativeContextPointer, (void**)(&fill_ctx));
        CheckForErrors(gpres == false || fill_ctx == NULL,
                "getPointerFromByteArray failed! gpres=%d fill_ctx=%p",
                gpres, fill_ctx);

        // Copy data from the jbyteArray containing the name to a C string.
        jsize nameStrlen = env->GetArrayLength(name);
        CheckForErrors(nameStrlen < 0, "Could not get array length (nameStrlen=%"
                PRId32 ")", (int32_t)nameStrlen);

        nameBuf = (char*) calloc(1, sizeof(char)*(nameStrlen + 1));
        CheckForErrors(nameBuf == NULL, "calloc failed for nameBuf");

        env->GetByteArrayRegion(name, 0, nameStrlen, (signed char*) nameBuf);
        CheckForErrors(0, "Could not get byte array region for 'name'.");

        // Invoke the associated fuse_dirfil_t.
        fuse_dirfil_t filler = fill_ctx->getDirFil();
        CSLogDebug("getDirFil() = %p", filler);
        fuse_dirh_t handle = fill_ctx->getHandle();
        CSLogDebug("getHandle() = %p", handle);

        CSLogDebug("invoking filler(%p, \"%s\", %" PRId32 ", %" PRId64 ")",
                handle, nameBuf, (uint32_t)type, ino);
        int fillRes = filler(handle, nameBuf, type, ino);
        CSLogDebug("fillRes = %d", fillRes);

        res = fillRes;
    } while(0);

    if(nameBuf != NULL)
        free(nameBuf);

    if(throwException) {
        throwByName(env, "java/lang/RuntimeException", "Exception in native "
                "method " _FNAME_ ".");
    }

#undef CheckForErrors

    CSLogTraceLeave("jint " _FNAME_ "(%p, "
            "%p, %p, %p, %" PRId32 ", %" PRId64 "): %" PRId32, env, cls,
            nativeContextPointer, name, (int32_t)type, (int64_t)ino,
            (int32_t)res);
    return res;
#undef _FNAME_
}

/*
 * Class:     org_catacombae_jfuse_types_fuse26_FUSEDirFil
 * Method:    freeNative
 * Signature: ([B)V
 */
JNIEXPORT void JNICALL Java_org_catacombae_jfuse_types_fuse26_FUSEDirFil_freeNative
  (JNIEnv *env, jclass cls, jbyteArray nativePointer) {
#define _FNAME_ "Java_org_catacombae_jfuse_types_fuse26_FUSEDirFil_freeNative"
    CSLogTraceEnter("void " _FNAME_ "(%p, "
            "%p, %p)", env, cls, nativePointer);

    void *ptr = NULL;
    if(getPointerFromByteArray(env, nativePointer, &ptr)) {
        if(ptr != NULL && env->ExceptionCheck() != JNI_TRUE)
            free(ptr);
    }
    else {
        CSLogError("Could not get pointer from byte array.");
        throwRuntimeException(env, _FNAME_ ": Could not get pointer from "
                "byte array.");
    }
    
    CSLogTraceLeave("void " _FNAME_ "(%p, "
            "%p, %p)", env, cls, nativePointer);
#undef _FNAME_
}

