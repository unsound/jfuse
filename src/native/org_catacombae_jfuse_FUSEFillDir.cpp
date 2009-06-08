#include <fuse.h>
#include "fuse_module.h"
#include "org_catacombae_jfuse_FUSEFillDir.h"
#include "fusefilldircontext.h"

#define FUSEFILLDIR_CLASS "org/catacombae/jfuse/FUSEFillDir"
#define LOG_ERROR(...)

/*
 * Class:     org_catacombae_jfuse_FUSEFillDir
 * Method:    fill
 * Signature: ([BLorg/catacombae/jfuse/Stat;J)Z
 */
JNIEXPORT jboolean JNICALL Java_org_catacombae_jfuse_FUSEFillDir_fill
  (JNIEnv *env, jobject thisObject, jbyteArray name, jobject statObject, jlong off) {
    jclass fuseFillDirClass = env->FindClass(FUSEFILLDIR_CLASS)
    jfieldID pointerFieldID = env->GetFieldID(fuseFillDirClass, "nativeFunctionPointer", "[B");

    jbyteArray ba = env->GetObjectField(thisObject, pointerFieldID);

    jsize baLength = env->GetArrayLength(ba);
    FUSEFillDirContext *fill_ctx = NULL;
    if(baLength == sizeof(FUSEFillDirContext*)) {
        env->GetByteArrayRegion(ba, 0, baLength, &fill_ctx);
        if(fill_ctx != NULL) {
            int nameStrlen = env->GetArrayLength(name);
            char *nameBuf = calloc(1, sizeof(char)*(nameStrlen+1));
            env->GetByteArrayRegion(name, 0, nameLen, nameBuf)
            struct stat stbuf;
            if(mergeStat(env, statObject, &stbuf)) {
                fuse_fill_dir_t filler = fill_ctx->getFiller();
                void *buf = fill_ctx->getBuf();
                filler(buf, nameBuf, stbuf, (off_t)off);
            }
        }
    }
    else
        LOG_ERROR("baLength: %d != sizeof(fuse_fill_dir_t): %d", baLength, sizeof(fuse_fill_dir_t));
}

