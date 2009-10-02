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
    bool getInitEnabled();
    void setInitEnabled(bool b);
#if defined(__APPLE__) || defined(__DARWIN__)
#if __FreeBSD__ >= 10
    bool getXtimesEnabled();
    void setXtimesEnabled(bool b);
#endif /* __FreeBSD__ >= 10 */
#endif /* defined(__APPLE__) || defined(__DARWIN__) */
protected:
    JNIEnv *env;
    jobject fsProvider;
    jobject privateData;
    bool initEnabled;
#if defined(__APPLE__) || defined(__DARWIN__)
#if __FreeBSD__ >= 10
    bool xtimesEnabled;
#endif /* __FreeBSD__ >= 10 */
#endif /* defined(__APPLE__) || defined(__DARWIN__) */
};

#endif	/* _JFUSECONTEXT_H */

