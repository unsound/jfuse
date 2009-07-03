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

package org.catacombae.jfuse.types.system;

/**
 * Java representation of <code>struct statvfs</code>.
 *
 * @author erik
 */
public class StatVFS {
    /** File system block size */
    long f_bsize;
    /** Fundamental file system block size */
    long f_frsize;
    /** Blocks on FS in units of f_frsize */
    long f_blocks;
    /** Free blocks */
    long f_bfree;
    /** Blocks available to non-root */
    long f_bavail;
    /** Total inodes */
    long f_files;
    /** Free inodes */
    long f_ffree;
    /** Free inodes for non-root */
    long f_favail;
    /** Filesystem ID */
    long f_fsid;
    /** Bit mask of values */
    long f_flag;
    /** Max file name length */
    long f_namemax;
}
