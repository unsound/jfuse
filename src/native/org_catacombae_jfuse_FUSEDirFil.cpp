#include "org_catacombae_jfuse_FUSEDirFil.h"

#include "CSLog.h"
#include "common.h"
#include "FUSEDirFilContext.h"

#include <stdlib.h>
#define __STDC_FORMAT_MACROS
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
 * Class:     org_catacombae_jfuse_FUSEDirFil
 * Method:    fillNative
 * Signature: ([B[BIJ)I
 */
JNIEXPORT jint JNICALL Java_org_catacombae_jfuse_FUSEDirFil_fillNative
  (JNIEnv *env, jclass cls, jbyteArray nativeContextPointer, jbyteArray name,
        jint type, jlong ino) {
    CSLogTraceEnter("jint Java_org_catacombae_jfuse_FUSEDirFil_fillNative(%p, "
            "%p, %p, %d, %lld)", env, nativeContextPointer, name, type, ino);

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
                getPointerFromByteArray(env, nativeContextPointer, &fill_ctx);
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

        CSLogDebug("invoking filler(%p, \"%s\", %d, %" PRId64 ")", handle,
                nameBuf, type, ino);
        int fillRes = filler(buf, nameBuf, type, ino);
        CSLogDebug("fillRes = %d", fillRes);

        res = fillRes;
    } while(0);

    if(nameBuf != NULL)
        free(nameBuf);

    if(throwException) {
        throwByName(env, "java/lang/RuntimeException", "Exception in native "
                "method Java_org_catacombae_jfuse_FUSEDirFil_fillNative.");
    }

#undef CheckForErrors

    CSLogTraceLeave("jint Java_org_catacombae_jfuse_FUSEDirFil_fillNative(%p, "
            "%p, %p, %d, %lld): %d", env, nativeFunctionPointer, name, type,
            ino, res);
    return res;
}

/*
 * Class:     org_catacombae_jfuse_FUSEDirFil
 * Method:    freeNative
 * Signature: ([B)V
 */
JNIEXPORT void JNICALL Java_org_catacombae_jfuse_FUSEDirFil_freeNative
  (JNIEnv *env, jclass cls, jbyteArray nativePointer) {

    void *ptr = getPointerFromByteArray(env, nativePointer);
    if(ptr != NULL && env->ExceptionCheck() != JNI_TRUE)
        free(ptr);
    
}

