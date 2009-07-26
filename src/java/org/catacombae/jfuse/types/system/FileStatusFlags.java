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
    public static final int O_ACCMODE = NumericalConstant.O_ACCMODE.getValue();

    /* flags present in the read(2) manpage.. */

    /** Open for reading only. */
    public static final int O_RDONLY = NumericalConstant.O_RDONLY.getValue();
    /** Open for writing only */
    public static final int O_WRONLY = NumericalConstant.O_WRONLY.getValue();
    /** Open for reading and writing. */
    public static final int O_RDWR = NumericalConstant.O_RDWR.getValue();
    /** Do not block on open or for data to become available. */
    public static final int O_NONBLOCK = NumericalConstant.O_NONBLOCK.getValue();
    /** Set append mode (append on each write). */
    public static final int O_APPEND = NumericalConstant.O_APPEND.getValue();
    /** Create file if it does not exist. */
    public static final int O_CREAT = NumericalConstant.O_CREAT.getValue();
    /** Truncate size to 0. */
    public static final int O_TRUNC = NumericalConstant.O_TRUNC.getValue();
    /** Error if O_CREAT and the file exists. */
    public static final int O_EXCL = NumericalConstant.O_EXCL.getValue();
    /** Atomically obtain a shared lock. */
    public static final int O_SHLOCK = NumericalConstant.O_SHLOCK.getValue();
    /** Atomically obtain an exclusive lock. */
    public static final int O_EXLOCK = NumericalConstant.O_EXLOCK.getValue();
    /** Don't follow symlinks. */
    public static final int O_NOFOLLOW = NumericalConstant.O_NOFOLLOW.getValue();
    /** Allow open of a symlink. */
    public static final int O_SYMLINK = NumericalConstant.O_SYMLINK.getValue();

    /* additional #defines found in fcntl.h. */

    /** Synchronous writes. */
    public static final int O_SYNC = NumericalConstant.O_SYNC.getValue();
    /** Signal pgrp when data ready. */
    public static final int O_ASYNC = NumericalConstant.O_ASYNC.getValue();
    /** Descriptor requested for event notifications only. */
    public static final int O_EVTONLY = NumericalConstant.O_EVTONLY.getValue();
    /** Don't assign controlling terminal. */
    public static final int O_NOCTTY = NumericalConstant.O_NOCTTY.getValue();
    public static final int O_DIRECTORY = NumericalConstant.O_DIRECTORY.getValue();

    public static class Print {
        public static void main(String[] args) throws Exception {
            Class c = FileStatusFlags.class;
            for(java.lang.reflect.Field f : c.getFields()) {
                System.out.println(f.getName() + " = " + f.getInt(null));
            }
        }
    }
}
