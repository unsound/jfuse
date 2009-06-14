/* 
 * File:   FUSE26Util.h
 * Author: erik
 *
 * Created on den 13 juni 2009, 18:28
 */

#ifndef _FUSE26UTIL_H
#define	_FUSE26UTIL_H

#include <jni.h>
#if FUSE_USE_VERSION != 26
#define FUSE_USE_VERSION 26
#endif
#include <fuse.h>

#include "JNIUtil.h"

class FUSE26Util : JNIUtil {
public:
    static jobject createFUSEFillDir(JNIEnv *env, fuse_fill_dir_t filler, void *buf);

    /**
     * Merges the contents of statObject into the struct stat target.
     */
    static bool mergeStat(JNIEnv *env, jobject statObject, struct stat *target);

    /**
     * Fills in the fields of statObject (Java class Stat) from the fields of st
     * (struct stat).
     */
    static bool fillStat(JNIEnv *env, struct stat *st, jobject statObject);
    
    /**
     * Creates a new Stat object and fills it using the fields in
     * <code>st</code>.
     */
    static jobject newStat(JNIEnv *env, struct stat *st);

    /**
     * Merges the contents of ffiObject (Java class FUSEFileInfo) with the supplied
     * struct fuse_file_info.
     */
    static bool mergeFUSEFileInfo(JNIEnv *env, jobject ffiObject, struct fuse_file_info *target);

    /**
     * Fills in the fields of ffiObject (Java class FUSEFileInfo) from the fields of fi
     * (struct fuse_file_info).
     */
    static bool fillFUSEFileInfo(JNIEnv *env, struct fuse_file_info *fi, jobject ffiObject);

    /**
     * Creates a new FUSEFileInfo object and fills it using the fields in
     * <code>fi</code>.
     */
    static jobject newFUSEFileInfo(JNIEnv *env, struct fuse_file_info *fi);
};


#endif	/* _FUSE26UTIL_H */

