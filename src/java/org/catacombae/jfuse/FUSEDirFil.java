/*-
 * jFUSE - FUSE bindings for Java
 * Copyright (C) 2008  Erik Larsson <erik82@kth.se>
 *
 * Derived from:
 *   FUSE: Filesystem in Userspace
 *   Copyright (C) 2001-2007  Miklos Szeredi <miklos@szeredi.hu>
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

package org.catacombae.jfuse;

/** Used by deprecated getdir() method */
public interface FUSEDirFil {
    public long fill(byte[] struct_fuse_dirhandlep_h,
		     byte[] const_charp_name,
		     int int_type,
		     byte[] ino_t_ino);
}

// /* Used by deprecated getdir() method */
// typedef struct fuse_dirhandle *fuse_dirh_t;
// typedef int (*fuse_dirfil_t) (fuse_dirh_t h, const char *name, int type,
//                               ino_t ino);