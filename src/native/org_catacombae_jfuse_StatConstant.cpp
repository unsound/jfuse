#include "org_catacombae_jfuse_StatConstant.h"

#include "common.h"
#include "CSLog.h"

#include <string.h>
#define __STDC_FORMAT_MACROS
#include <inttypes.h>
#include <sys/stat.h>

/*
 * Class:     org_catacombae_jfuse_StatConstant
 * Method:    getNativeValue
 * Signature: (Ljava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_org_catacombae_jfuse_StatConstant_getNativeValue
  (JNIEnv *env, jclass cls, jstring constantName) {

    CSLogTraceEnter("jint Java_org_catacombae_jfuse_StatConstant_getNativeValue"
            "(%p, %p, %p)", env, cls, constantName);
    jint result = -1;
    const char *constantNameChars = env->GetStringUTFChars(constantName, NULL);

    // One truth.
#define ifconstant(a) else if(strcmp(#a, constantNameChars) == 0) result = a

    if(0);
    ifconstant(S_IFMT);
    ifconstant(S_IFIFO);
    ifconstant(S_IFCHR);
    ifconstant(S_IFDIR);
    ifconstant(S_IFBLK);
    ifconstant(S_IFREG);
    ifconstant(S_IFLNK);
    ifconstant(S_IFSOCK);
    ifconstant(S_IFWHT);
    ifconstant(S_ISUID);
    ifconstant(S_ISGID);
    ifconstant(S_ISVTX);
    ifconstant(S_IRUSR);
    ifconstant(S_IWUSR);
    ifconstant(S_IXUSR);

#undef ifconstant
    else {
        // If we got here, the constant is unrecognized.
        CSLogError("Could not find a matching constant value for \"%s\"", constantNameChars);
        throwByName(env, "java/lang/RuntimeException", "Unrecognized constant value!");
    }

    env->ReleaseStringUTFChars(constantName, constantNameChars);

    CSLogTraceLeave("jint Java_org_catacombae_jfuse_StatConstant_getNativeValue"
            "(%p, %p, %p): %" PRId32 "", env, cls, constantName, result);
    return result;

}

