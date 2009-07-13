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

#ifndef _FUSE26UTIL_H
#define	_FUSE26UTIL_H

#if FUSE_USE_VERSION != 26
#define FUSE_USE_VERSION 26
#endif

#include "JNIUtil.h"

#include <fuse.h>

class FUSE26Util : JNIUtil {
public:
    /**
     * Creates a new FUSEFillDir object using <code>filler</code> and
     * <code>buf</code> internally.
     */
    static jobject newFUSEFillDir(JNIEnv *env, fuse_fill_dir_t filler, void *buf);

    /**
     * Creates a new FUSEDirFil object using <code>dirfil</code> and
     * <code>dirh</code> internally.
     */
    static jobject newFUSEDirFil(JNIEnv *env, fuse_dirfil_t dirfil, fuse_dirh_t dirh);

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
     * Merges the contents of source (Java class Timespec) into the supplied
     * struct timespec.
     */
    static bool mergeTimespec(JNIEnv *env, jobject source, struct timespec *target);

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

    /**
     * Merges the contents of source (Java class Utimbuf) with the supplied
     * struct utimbuf.
     */
    static bool mergeUtimbuf(JNIEnv *env, jobject source, struct utimbuf *target);

    /**
     * Fills in the fields of target (Java class Utimbuf) from the fields
     * of source (struct utimbuf).
     */
    static bool fillUtimbuf(JNIEnv *env, const struct utimbuf *source, jobject target);

    /**
     * Creates a new Utimbuf object and fills it using the fields in
     * <code>source</code>.
     */
    static jobject newUtimbuf(JNIEnv *env, const struct utimbuf *source);

    /**
     * Merges the contents of source (Java class StatVFS) with the supplied
     * struct statvfs.
     */
    static bool mergeStatVFS(JNIEnv *env, jobject source, struct statvfs *target);

    /**
     * Fills in the fields of target (Java class StatVFS) from the fields
     * of source (struct statvfs).
     */
    static bool fillStatVFS(JNIEnv *env, const struct statvfs *source, jobject target);

    /**
     * Creates a new StatVFS object and fills it using the fields in
     * <code>source</code>.
     */
    static jobject newStatVFS(JNIEnv *env, const struct statvfs *source);
};


#endif	/* _FUSE26UTIL_H */

