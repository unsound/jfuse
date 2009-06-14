/*-
 * Copyright (C) 2007 Erik Larsson
 * 
 * All rights reserved.
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA
 */

#ifndef RARFS_FUSE_H
#define RARFS_FUSE_H

#define FUSE_USE_VERSION 26

#include <fuse.h>

int rarfs_getattr(const char *path, struct stat *stbuf);
int rarfs_readdir(const char *path, void *buf, fuse_fill_dir_t filler,
                         off_t offset, struct fuse_file_info *fi);
int rarfs_open(const char *path, struct fuse_file_info *fi);
int rarfs_read(const char *path, char *buf, size_t size, off_t offset,
                      struct fuse_file_info *fi);

int rarfs_main(int argc, char *argv[]);

#endif

