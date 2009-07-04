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
 * @author erik
 */
public interface FileStatusFlags {
    /*
     * File status flags: these are used by open(2), fcntl(2).
     * They are also used (indirectly) in the kernel file structure f_flags,
     * which is a superset of the open/fcntl flags.  Open flags and f_flags
     * are inter-convertible using OFLAGS(fflags) and FFLAGS(oflags).
     * Open/fcntl flags begin with O_; kernel-internal flags begin with F.
     */

    /** Mask for open modes (O_RDONLY, O_WRONLY and O_RDWR). */
    public static final int O_ACCMODE = 0x0003;

    /* flags present in the read(2) manpage.. */

    /** Open for reading only. */
    public static final int O_RDONLY = 0x0000;
    /** Open for writing only */
    public static final int O_WRONLY = 0x0001;
    /** Open for reading and writing. */
    public static final int O_RDWR = 0x0002;
    /** Do not block on open or for data to become available. */
    public static final int O_NONBLOCK = 0x0004;
    /** Set append mode (append on each write). */
    public static final int O_APPEND = 0x0008;
    /** Create file if it does not exist. */
    public static final int O_CREAT = 0x0200;
    /** Truncate size to 0. */
    public static final int O_TRUNC = 0x0400;
    /** Error if O_CREAT and the file exists. */
    public static final int O_EXCL = 0x0800;
    /** Atomically obtain a shared lock. */
    public static final int O_SHLOCK = 0x0010;
    /** Atomically obtain an exclusive lock. */
    public static final int O_EXLOCK = 0x0020;
    /** Don't follow symlinks. */
    public static final int O_NOFOLLOW = 0x0100;
    /** Allow open of a symlink. */
    public static final int O_SYMLINK = 0x200000;

    /* additional #defines found in fcntl.h. */

    /** Synchronous writes. */
    public static final int O_SYNC = 0x0080;
    /** Signal pgrp when data ready. */
    public static final int O_ASYNC = 0x0040;
    /** Descriptor requested for event notifications only. */
    public static final int O_EVTONLY = 0x8000;
    /** Don't assign controlling terminal. */
    public static final int O_NOCTTY = 0x20000;
    public static final int O_DIRECTORY = 0x100000;
}
