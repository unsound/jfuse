
#include "common.h"

#include "org_catacombae_jfuse_FUSEFillDir.h"
#include "fuse26_module.h"
#include "fusefilldircontext.h"
#include "CSLog.h"
#include "FUSE26Util.h"

#include <stdlib.h>
#define __STDC_FORMAT_MACROS
#include <inttypes.h>
#include <fuse.h>

#define FUSEFILLDIR_CLASS "org/catacombae/jfuse/FUSEFillDir"


/*
 * Class:     org_catacombae_jfuse_FUSEFillDir
 * Method:    fill
 * Signature: ([BLorg/catacombae/jfuse/Stat;J)Z
 */
JNIEXPORT jboolean JNICALL Java_org_catacombae_jfuse_FUSEFillDir_fillNative(JNIEnv *env,
        jobject thisObject, jbyteArray name, jobject statObject, jlong off) {
    
#define CheckForErrors(a, b, ...) \
    if((a) || env->ExceptionCheck() == JNI_TRUE) { \
        CSLogError(b, ##__VA_ARGS__); \
        if(env->ExceptionCheck() == JNI_FALSE) \
            throwException = true; \
        break; \
    }

    CSLogTraceEnter("jboolean Java_org_catacombae_jfuse_FUSEFillDir_fill(%p, "
            "%p, %p, %p, %lld)", env, thisObject, name, statObject, off);
    jboolean res = JNI_FALSE;
    bool throwException = false;

    do {
        jclass fuseFillDirClass = env->FindClass(FUSEFILLDIR_CLASS);
        CheckForErrors(fuseFillDirClass == NULL, "Could not find FUSEFillDir class! (%s)", FUSEFILLDIR_CLASS);

        jfieldID pointerFieldID = env->GetFieldID(fuseFillDirClass, "nativeFunctionPointer", "[B");
        CheckForErrors(pointerFieldID == NULL, "Could not find field FUSEFillDir.nativeFunctionPointer!");

        // TODO: Check how to ensure valid jbyteArray cast.
        jbyteArray ba = (jbyteArray) env->GetObjectField(thisObject, pointerFieldID);
        CheckForErrors(false, "Could not get field FUSEFillDir.nativeFunctionPointer!");

        jsize baLength = env->GetArrayLength(ba);
        CheckForErrors(baLength != sizeof(FUSEFillDirContext*),
                "baLength: %" PRId32 " != sizeof(fuse_fill_dir_t): %zu", baLength,
                sizeof(fuse_fill_dir_t));

        FUSEFillDirContext *fill_ctx = NULL;
        env->GetByteArrayRegion(ba, 0, baLength, (jbyte*) (&fill_ctx));
        CheckForErrors(fill_ctx == NULL, "Could not get FUSEFillDirContext pointer.");

        jsize nameStrlen = env->GetArrayLength(name);
        CheckForErrors(nameStrlen < 0, "Could not get array length (nameStrlen=%" PRId32 ")", nameStrlen);

        char *nameBuf = (char*) calloc(1, sizeof(char)*(nameStrlen + 1));
        CheckForErrors(nameBuf == NULL, "calloc failed for nameBuf");

        env->GetByteArrayRegion(name, 0, nameStrlen, (signed char*) nameBuf);
        CheckForErrors(0, "Could not get byte array region for 'name'.");

        struct stat stbuf;
        struct stat *stp = NULL;
        if(statObject != NULL) {
            CheckForErrors(FUSE26Util::mergeStat(env, statObject, &stbuf), "Could not merge stat object");
            stp = &stbuf;
        }

        fuse_fill_dir_t filler = fill_ctx->getFiller();
        CSLogDebug("getFiller() = %p", filler);
        void *buf = fill_ctx->getBuf();
        CSLogDebug("getBuf() = %p", buf);
        CSLogDebug("invoking filler(%p, \"%s\", %p, %" PRId64 ")", buf, nameBuf, stp, (off_t) off);
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

    if(throwException) {
        throwByName(env, "java/lang/RuntimeException", "Exception in native "
                "method Java_org_catacombae_jfuse_FUSEFillDir_fill.");
    }

    CSLogTraceLeave("jboolean Java_org_catacombae_jfuse_FUSEFillDir_fill(%p, "
            "%p, %p, %p, %lld): %d", env, thisObject, name, statObject, off, res);
    return res;

#undef CheckForErrors
}

