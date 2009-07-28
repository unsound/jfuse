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

#if defined(__APPLE__) || defined(__DARWIN__)
#if (__FreeBSD__ >= 10)

#include "MacFUSE20Util.h"
#include "JavaSignatures.h"
#include "FUSE26Util.h"
#include "CSLog.h"

/**
 * Merges the contents of attrObject into the struct setattr_x target.
 */
bool MacFUSE20Util::mergeSetattr_x(JNIEnv *env, jobject source,
        struct setattr_x *target) {
#define _FNAME_ "MacFUSE20Util::mergeSetattr_x"
    CSLogTraceEnter("bool " _FNAME_ "(%p, %p, %p)", env, source, target);
    bool res = false;
    do {
        jclass clazz = env->GetObjectClass(source);
        if(clazz == NULL || env->ExceptionCheck() == JNI_TRUE) {
            CSLogError("Could not get object class!");
            if(env->ExceptionCheck())
                env->ExceptionDescribe();
            break;
        }

        //jint valid;
        jshort mode;
        jlong uid;
        jlong gid;
        jlong size;
        jobject acctime;
        jobject modtime;
        jobject crtime;
        jobject chgtime;
        jobject bkuptime;
        jint flags;

        //if(!getIntField(env, clazz, source, "valid", &valid))
        //    break;
        if(!getShortField(env, clazz, source, "mode", &mode))
            break;
        if(!getLongField(env, clazz, source, "uid", &uid))
            break;
        if(!getLongField(env, clazz, source, "gid", &gid))
            break;
        if(!getLongField(env, clazz, source, "size", &size))
            break;
        if(!getObjectField(env, clazz, source, "acctime",
                JAVA_CLASS(TIMESPEC_CLASS), &acctime))
            break;
        if(!getObjectField(env, clazz, source, "modtime",
                JAVA_CLASS(TIMESPEC_CLASS), &modtime))
            break;
        if(!getObjectField(env, clazz, source, "crtime",
                JAVA_CLASS(TIMESPEC_CLASS), &crtime))
            break;
        if(!getObjectField(env, clazz, source, "chgtime",
                JAVA_CLASS(TIMESPEC_CLASS), &chgtime))
            break;
        if(!getObjectField(env, clazz, source, "bkuptime",
                JAVA_CLASS(TIMESPEC_CLASS), &bkuptime))
            break;
        if(!getIntField(env, clazz, source, "flags", &flags))
            break;

        struct timespec tmp_acctime, tmp_modtime, tmp_crtime, tmp_chgtime, tmp_bkuptime;
        if(!FUSE26Util::mergeTimespec(env, acctime, &tmp_acctime))
            break;
        if(!FUSE26Util::mergeTimespec(env, modtime, &tmp_modtime))
            break;
        if(!FUSE26Util::mergeTimespec(env, crtime, &tmp_crtime))
            break;
        if(!FUSE26Util::mergeTimespec(env, chgtime, &tmp_chgtime))
            break;
        if(!FUSE26Util::mergeTimespec(env, bkuptime, &tmp_bkuptime))
            break;

        env->DeleteLocalRef(acctime);
        env->DeleteLocalRef(modtime);
        env->DeleteLocalRef(crtime);
        env->DeleteLocalRef(chgtime);
        env->DeleteLocalRef(bkuptime);

        //target->valid = valid;
        target->mode = mode;
        target->uid = uid;
        target->gid = gid;
        target->size = size;
        target->acctime = tmp_acctime;
        target->modtime = tmp_modtime;
        target->crtime = tmp_crtime;
        target->chgtime = tmp_chgtime;
        target->bkuptime = tmp_bkuptime;
        target->flags = flags;

        res = true;
    }
    while(0);

    CSLogTraceLeave("bool " _FNAME_ "(%p, %p, %p): %d", env, source, target, res);
    return res;
#undef _FNAME_
}

/**
 * Fills in the fields of attrObject (Java class Setattr_x) from the fields
 * of attr (struct setattr_x).
 */
bool MacFUSE20Util::fillSetattr_x(JNIEnv *env,
        const struct setattr_x *source, jobject target) {
#define _FNAME_ "MacFUSE20Util::fillSetattr_x"
    CSLogTraceEnter("bool " _FNAME_ "(%p, %p, %p)", env, source, target);

    bool ret = false;
    do {
        jclass clazz = env->GetObjectClass(target);
        if(clazz == NULL || env->ExceptionCheck() == JNI_TRUE) {
            CSLogError("Could not get object class!");
            if(env->ExceptionCheck())
                env->ExceptionDescribe();
            break;
        }

        jobject acctime;
        jobject modtime;
        jobject crtime;
        jobject chgtime;
        jobject bkuptime;

        if(!getObjectField(env, clazz, target, "acctime",
                JAVA_CLASS(TIMESPEC_CLASS), &acctime))
            break;
        if(!getObjectField(env, clazz, target, "modtime",
                JAVA_CLASS(TIMESPEC_CLASS), &modtime))
            break;
        if(!getObjectField(env, clazz, target, "crtime",
                JAVA_CLASS(TIMESPEC_CLASS), &crtime))
            break;
        if(!getObjectField(env, clazz, target, "chgtime",
                JAVA_CLASS(TIMESPEC_CLASS), &chgtime))
            break;
        if(!getObjectField(env, clazz, target, "bkuptime",
                JAVA_CLASS(TIMESPEC_CLASS), &bkuptime))
            break;

        //if(!setIntField(env, clazz, target, "valid", source->valid))
        //    break;
        if(!setShortField(env, clazz, target, "mode", source->mode))
            break;
        if(!setLongField(env, clazz, target, "uid", source->uid))
            break;
        if(!setLongField(env, clazz, target, "gid", source->gid))
            break;
        if(!setLongField(env, clazz, target, "size", source->size))
            break;
        if(!FUSE26Util::fillTimespec(env, &(source->acctime), acctime))
            break;
        if(!FUSE26Util::fillTimespec(env, &(source->modtime), modtime))
            break;
        if(!FUSE26Util::fillTimespec(env, &(source->crtime), crtime))
            break;
        if(!FUSE26Util::fillTimespec(env, &(source->chgtime), chgtime))
            break;
        if(!FUSE26Util::fillTimespec(env, &(source->bkuptime), bkuptime))
            break;
        if(!setIntField(env, clazz, target, "flags", source->flags))
            break;

        if(!setBooleanField(env, clazz, target, "wantsMode",
                (SETATTR_WANTS_MODE(source) ? JNI_TRUE : JNI_FALSE)))
            break;
        if(!setBooleanField(env, clazz, target, "wantsUid",
                (SETATTR_WANTS_UID(source) ? JNI_TRUE : JNI_FALSE)))
            break;
        if(!setBooleanField(env, clazz, target, "wantsGid",
                (SETATTR_WANTS_GID(source) ? JNI_TRUE : JNI_FALSE)))
            break;
        if(!setBooleanField(env, clazz, target, "wantsSize",
                (SETATTR_WANTS_SIZE(source) ? JNI_TRUE : JNI_FALSE)))
            break;
        if(!setBooleanField(env, clazz, target, "wantsAcctime",
                (SETATTR_WANTS_ACCTIME(source) ? JNI_TRUE : JNI_FALSE)))
            break;
        if(!setBooleanField(env, clazz, target, "wantsModtime",
                (SETATTR_WANTS_MODTIME(source) ? JNI_TRUE : JNI_FALSE)))
            break;
        if(!setBooleanField(env, clazz, target, "wantsCrtime",
                (SETATTR_WANTS_CRTIME(source) ? JNI_TRUE : JNI_FALSE)))
            break;
        if(!setBooleanField(env, clazz, target, "wantsChgtime",
                (SETATTR_WANTS_CHGTIME(source) ? JNI_TRUE : JNI_FALSE)))
            break;
        if(!setBooleanField(env, clazz, target, "wantsBkuptime",
                (SETATTR_WANTS_BKUPTIME(source) ? JNI_TRUE : JNI_FALSE)))
            break;
        if(!setBooleanField(env, clazz, target, "wantsFlags",
                (SETATTR_WANTS_FLAGS(source) ? JNI_TRUE : JNI_FALSE)))
            break;

        env->DeleteLocalRef(acctime);
        env->DeleteLocalRef(modtime);
        env->DeleteLocalRef(crtime);
        env->DeleteLocalRef(chgtime);
        env->DeleteLocalRef(bkuptime);

        ret = true;
    } while(0);

    CSLogTraceLeave("bool " _FNAME_ "(%p, %p, %p): %d", env, source, target, ret);
    return ret;
#undef _FNAME_
}

/**
 * Creates a new Setattr_x object and fills it using the fields in
 * <code>attr</code>.
 */
jobject MacFUSE20Util::newSetattr_x(JNIEnv *env,
        const struct setattr_x *source) {
#define _FNAME_ "MacFUSE20Util::newSetattr_x"
    CSLogTraceEnter("jobject " _FNAME_ "(%p, %p)", env, source);

    jobject res = NULL;

    jobject obj = newObject(env, SETATTR_X_CLASS, SETATTR_X_INIT_NAME, SETATTR_X_INIT_SIGNATURE);
    if (obj == NULL || env->ExceptionCheck() == JNI_TRUE)
        CSLogError("Could not create new Setattr_x instance.");
    else {
        if (!fillSetattr_x(env, source, obj))
            CSLogError("fillSetattr_x failed!");
        else
            res = obj;
    }

    if(env->ExceptionCheck() == JNI_TRUE)
        env->ExceptionDescribe();

    CSLogTraceLeave("jobject " _FNAME_ "(%p, %p): %p", env, source, res);
    return res;
#undef _FNAME_
}

#endif /* __FreeBSD__ >= 10 */
#endif /* defined(__APPLE__) || defined(__DARWIN__) */
