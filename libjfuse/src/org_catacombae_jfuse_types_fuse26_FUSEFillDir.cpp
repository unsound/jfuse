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

#include "org_catacombae_jfuse_types_fuse26_FUSEFillDir.h"

#include "common.h"
#include "fuse26_module.h"
#include "FUSEFillDirContext.h"
#include "CSLog.h"
#include "FUSE26Util.h"
#include "JavaSignatures.h"

#include <stdlib.h>
#include <inttypes.h>
#include <fuse.h>

/*
 * Class:     org_catacombae_jfuse_types_fuse26_FUSEFillDir
 * Method:    fillNative
 * Signature: ([B[BLorg/catacombae/jfuse/types/system/Stat;J)Z
 */
JNIEXPORT jboolean JNICALL Java_org_catacombae_jfuse_types_fuse26_FUSEFillDir_fillNative
  (JNIEnv *env, jclass cls, jbyteArray nativeContextPointer, jbyteArray name,
        jobject statObject, jlong off) {
#define _FNAME_ "Java_org_catacombae_jfuse_types_fuse26_FUSEFillDir_fillNative"

    CSLogTraceEnter("jboolean %s(%p, %p, %p, %p, %p, %" PRId64 ")", _FNAME_,
            env, cls, nativeContextPointer, name, statObject, (int64_t)off);

#define CheckForErrors(a, b, ...) \
    if((a) || env->ExceptionCheck() == JNI_TRUE) { \
        CSLogError(b, ##__VA_ARGS__); \
        if(env->ExceptionCheck() == JNI_FALSE) \
            throwException = true; \
        break; \
    }

    jboolean res = JNI_FALSE;
    bool throwException = false;
    char *nameBuf = NULL;

    do {
        jbyteArray ba = nativeContextPointer;

        jsize baLength = env->GetArrayLength(ba);
        CheckForErrors(baLength != sizeof(FUSEFillDirContext*),
                "baLength: %" PRId32 " != sizeof(fuse_fill_dir_t): %zu",
                (int32_t)baLength, sizeof(fuse_fill_dir_t));

        FUSEFillDirContext *fill_ctx = NULL;
        env->GetByteArrayRegion(ba, 0, baLength, (jbyte*) (&fill_ctx));
        CheckForErrors(fill_ctx == NULL, "Could not get FUSEFillDirContext "
                "pointer.");

        jsize nameStrlen = env->GetArrayLength(name);
        CheckForErrors(nameStrlen < 0, "Could not get array length "
                "(nameStrlen=%" PRId32 ")", (int32_t)nameStrlen);

        nameBuf = (char*) calloc(1, sizeof(char)*(nameStrlen + 1));
        CheckForErrors(nameBuf == NULL, "calloc failed for nameBuf");

        env->GetByteArrayRegion(name, 0, nameStrlen, (signed char*) nameBuf);
        CheckForErrors(0, "Could not get byte array region for 'name'.");

        struct stat stbuf;
        struct stat *stp = NULL;
        if(statObject != NULL) {
            CheckForErrors(FUSE26Util::mergeStat(env, statObject, &stbuf),
                    "Could not merge stat object");
            stp = &stbuf;
        }

        fuse_fill_dir_t filler = fill_ctx->getFiller();
        CSLogDebug("getFiller() = %p", filler);
        void *buf = fill_ctx->getBuf();
        CSLogDebug("getBuf() = %p", buf);
        CSLogDebug("invoking filler(%p, \"%s\", %p, %" PRId64 ")", buf, nameBuf,
                stp, (off_t) off);
        int fillRes = filler(buf, nameBuf, stp, (off_t) off);
        CSLogDebug("fillRes = %d", fillRes);
        if(fillRes == 0)
            res = JNI_FALSE;
        else if(fillRes == 1)
            res = JNI_TRUE;
        else {
            CSLogError("Unexpected return value from filler: %d", fillRes);
            throwException = true;
        }
    }
    while(0);

    if(nameBuf != NULL)
        free(nameBuf);

    if(throwException) {
        throwByName(env, "java/lang/RuntimeException", "Exception in native "
                "method " _FNAME_ ".");
    }

#undef CheckForErrors

    CSLogTraceLeave("jboolean %s(%p, %p, %p, %p, %p, %" PRId64 "): %d",
            _FNAME_, env, cls, nativeContextPointer, name, statObject,
            (int64_t)off, res);
    return res;

#undef _FNAME_
}

