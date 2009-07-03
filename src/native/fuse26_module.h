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

#ifndef _FUSE_MODULE_H
#define	_FUSE_MODULE_H

#define FUSE_USE_VERSION 26

#include <jni.h>
#include <fuse.h>
#include "jFUSEContext.h"

void jfuse_set_context(jFUSEContext *ctx);

/*
 * Function definitions for our jFUSE callbacks.
 */

int jfuse_getattr(const char *, struct stat *);

int jfuse_readlink(const char *, char *, size_t);

int jfuse_getdir(const char *, fuse_dirh_t, fuse_dirfil_t);

int jfuse_mknod(const char *, mode_t, dev_t);

int jfuse_mkdir(const char *, mode_t);

int jfuse_unlink(const char *);

int jfuse_rmdir(const char *);

int jfuse_symlink(const char *, const char *);

int jfuse_rename(const char *, const char *);

int jfuse_link(const char *, const char *);

int jfuse_chmod(const char *, mode_t);

int jfuse_chown(const char *, uid_t, gid_t);

int jfuse_truncate(const char *, off_t);

int jfuse_utime(const char *, struct utimbuf *);

int jfuse_open(const char *, struct fuse_file_info *);

int jfuse_read(const char *, char *, size_t, off_t,
        struct fuse_file_info *);

int jfuse_write(const char *, const char *, size_t, off_t,
        struct fuse_file_info *);

int jfuse_statfs(const char *, struct statvfs *);

int jfuse_flush(const char *, struct fuse_file_info *);

int jfuse_release(const char *, struct fuse_file_info *);

int jfuse_fsync(const char *, int, struct fuse_file_info *);

#if (__FreeBSD__ >= 10)
int jfuse_setxattr(const char *, const char *, const char *, size_t, int, uint32_t);
#else
int jfuse_setxattr(const char *, const char *, const char *, size_t, int);
#endif /* __FreeBSD__ >= 10 */

#if (__FreeBSD__ >= 10)
int jfuse_getxattr(const char *, const char *, char *, size_t, uint32_t);
#else
int jfuse_getxattr(const char *, const char *, char *, size_t);
#endif /* __FreeBSD__ >= 10 */

int jfuse_listxattr(const char *, char *, size_t);

int jfuse_removexattr(const char *, const char *);

int jfuse_opendir(const char *, struct fuse_file_info *);

int jfuse_readdir(const char *, void *, fuse_fill_dir_t, off_t,
        struct fuse_file_info *);

int jfuse_releasedir(const char *, struct fuse_file_info *);

int jfuse_fsyncdir(const char *, int, struct fuse_file_info *);

void *jfuse_init(struct fuse_conn_info *conn);

void jfuse_destroy(void *);

int jfuse_access(const char *, int);

int jfuse_create(const char *, mode_t, struct fuse_file_info *);

int jfuse_ftruncate(const char *, off_t, struct fuse_file_info *);

int jfuse_fgetattr(const char *, struct stat *, struct fuse_file_info *);

int jfuse_lock(const char *, struct fuse_file_info *, int cmd,
        struct flock *);

int jfuse_utimens(const char *, const struct timespec tv[2]);

int jfuse_bmap(const char *, size_t blocksize, uint64_t *idx);

#if (__FreeBSD__ >= 10)
int jfuse_setvolname(const char *);

int jfuse_exchange(const char *, const char *, unsigned long);

int jfuse_getxtimes(const char *, struct timespec *bkuptime,
        struct timespec *crtime);

int jfuse_setbkuptime(const char *, const struct timespec *tv);

int jfuse_setchgtime(const char *, const struct timespec *tv);

int jfuse_setcrtime(const char *, const struct timespec *tv);

int jfuse_chflags(const char *, uint32_t);

int jfuse_setattr_x(const char *, struct setattr_x *);

int jfuse_fsetattr_x(const char *, struct setattr_x *,
        struct fuse_file_info *);

#endif /* __FreeBSD__ >= 10 */

#endif	/* _FUSE_MODULE_H */

