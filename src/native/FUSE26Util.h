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
    static bool fillStat(JNIEnv *env, const struct stat *st, jobject statObject);
    
    /**
     * Creates a new Stat object and fills it using the fields in
     * <code>st</code>.
     */
    static jobject newStat(JNIEnv *env, const struct stat *st);

    /**
     * Merges the contents of ffiObject (Java class FUSEFileInfo) with the supplied
     * struct fuse_file_info.
     */
    static bool mergeFUSEFileInfo(JNIEnv *env, jobject ffiObject, struct fuse_file_info *target);

    /**
     * Fills in the fields of ffiObject (Java class FUSEFileInfo) from the fields of fi
     * (struct fuse_file_info).
     */
    static bool fillFUSEFileInfo(JNIEnv *env, const struct fuse_file_info *fi, jobject ffiObject);

    /**
     * Creates a new FUSEFileInfo object and fills it using the fields in
     * <code>fi</code>.
     */
    static jobject newFUSEFileInfo(JNIEnv *env, const struct fuse_file_info *fi);

    /**
     * Merges the contents of source (Java class Flock) with the supplied
     * struct flock.
     */
    static bool mergeFlock(JNIEnv *env, jobject source, struct flock *target);

    /**
     * Fills in the fields of target (Java class Flock) from the fields of source
     * (struct flock).
     */
    static bool fillFlock(JNIEnv *env, const struct flock *source, jobject target);

    /**
     * Creates a new Flock object and fills it using the fields in
     * <code>source</code>.
     */
    static jobject newFlock(JNIEnv *env, const struct flock *source);

    /**
     * Fills in the fields of target (Java class Timespec) from the fields of source
     * (struct timespec).
     */
    static bool fillTimespec(JNIEnv *env, const struct timespec *source, jobject target);

    /**
     * Creates a new Timespec object and fills it using the fields in
     * <code>source</code>.
     */
    static jobject newTimespec(JNIEnv *env, const struct timespec *source);

    /**
     * Merges the contents of source (Java class LongRef) with the supplied
     * uint64_t.
     */
    static bool mergeLongRef(JNIEnv *env, jobject source, uint64_t *target);

    /**
     * Fills in the fields of target (Java class LongRef) from the fields of source
     * (uint64_t).
     */
    static bool fillLongRef(JNIEnv *env, const uint64_t *source, jobject target);

    /**
     * Creates a new LongRef object and fills it using the fields in
     * <code>source</code>.
     */
    static jobject newLongRef(JNIEnv *env, const uint64_t *source);

    /**
     * Merges the contents of source (Java class FUSEConnInfo) with the supplied
     * fuse_conn_info.
     */
    static bool mergeFUSEConnInfo(JNIEnv *env, jobject source, struct fuse_conn_info *target);

    /**
     * Fills in the fields of target (Java class FUSEConnInfo) from the fields
     * of source (fuse_conn_info).
     */
    static bool fillFUSEConnInfo(JNIEnv *env, const struct fuse_conn_info *source, jobject target);

    /**
     * Creates a new FUSEConnInfo object and fills it using the fields in
     * <code>source</code>.
     */
    static jobject newFUSEConnInfo(JNIEnv *env, const struct fuse_conn_info *source);
};


#endif	/* _FUSE26UTIL_H */

