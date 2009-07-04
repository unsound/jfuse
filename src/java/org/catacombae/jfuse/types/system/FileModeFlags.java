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
 *
 * @author Erik Larsson
 */
public interface FileModeFlags {
    /* File type */

    /** type of file */
    public static final int S_IFMT = StatConstant.S_IFMT.getNativeValue();
    /** named pipe (fifo) */
    public static final int S_IFIFO = StatConstant.S_IFIFO.getNativeValue();
    /** character special */
    public static final int S_IFCHR = StatConstant.S_IFCHR.getNativeValue();
    /** directory */
    public static final int S_IFDIR = StatConstant.S_IFDIR.getNativeValue();
    /** block special */
    public static final int S_IFBLK = StatConstant.S_IFBLK.getNativeValue();
    /** regular */
    public static final int S_IFREG = StatConstant.S_IFREG.getNativeValue();
    /** symbolic link */
    public static final int S_IFLNK = StatConstant.S_IFLNK.getNativeValue();
    /** socket */
    public static final int S_IFSOCK = StatConstant.S_IFSOCK.getNativeValue();
    /** whiteout */
    //public static final int S_IFWHT = StatConstant.S_IFWHT.getNativeValue(); // Not portable

    /* Permissions */

    /** RWX mask for owner. */
    public static final int S_IRWXU = StatConstant.S_IRWXU.getNativeValue();
    /** read permission, owner */
    public static final int S_IRUSR = StatConstant.S_IRUSR.getNativeValue();
    /** write permission, owner */
    public static final int S_IWUSR = StatConstant.S_IWUSR.getNativeValue();
    /** execute/search permission, owner */
    public static final int S_IXUSR = StatConstant.S_IXUSR.getNativeValue();

    /** RWX mask for group. */
    public static final int S_IRWXG = StatConstant.S_IRWXG.getNativeValue();
    /** read permission, group */
    public static final int S_IRGRP = StatConstant.S_IRGRP.getNativeValue();
    /** write permission, group */
    public static final int S_IWGRP = StatConstant.S_IWGRP.getNativeValue();
    /** execute/search permission, group */
    public static final int S_IXGRP = StatConstant.S_IXGRP.getNativeValue();

    /** RWX mask for other. */
    public static final int S_IRWXO = StatConstant.S_IRWXO.getNativeValue();
    /** read permission, other */
    public static final int S_IROTH = StatConstant.S_IROTH.getNativeValue();
    /** write permission, other */
    public static final int S_IWOTH = StatConstant.S_IWOTH.getNativeValue();
    /** execute/search permission, other */
    public static final int S_IXOTH = StatConstant.S_IXOTH.getNativeValue();

    /** set user id on execution */
    public static final int S_ISUID = StatConstant.S_ISUID.getNativeValue();
    /** set group id on execution */
    public static final int S_ISGID = StatConstant.S_ISGID.getNativeValue();
    /** save swapped text even after use */
    public static final int S_ISVTX = StatConstant.S_ISVTX.getNativeValue();
}
