/* 
 * File:   jFUSEContext.h
 * Author: erik
 *
 * Created on den 13 juni 2009, 08:50
 */

#ifndef _JFUSECONTEXT_H
#define	_JFUSECONTEXT_H

#include <jni.h>

class jFUSEContext {
public:
    jFUSEContext(JNIEnv *env, jobject fsProvider);
    virtual ~jFUSEContext();

    JNIEnv* getJNIEnv();
    jobject getFSProvider();
    jmethodID getFSProviderMethod(const char *name, const char *descriptor);
    jobject getPrivateData();
    void setPrivateData(jobject obj);
protected:
    JNIEnv *env;
    jobject fsProvider;
    jobject privateData;
};

#endif	/* _JFUSECONTEXT_H */

