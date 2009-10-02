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

import java.io.PrintStream;

/**
 *
 * @author erik
 */
public class Stat implements FileModeFlags {
    /** Device inode resides on. Type: dev_t (4 bytes) */
    public long st_dev = 0;
    /** Inode's number. Type: ino_t (4 bytes) */
    public long st_ino = 0;
    /** Inode protection mode. Type: mode_t (2 bytes) */
    public long st_mode = 0;
    /** Number of hard links to the file. Type: nlink_t (2 bytes) */
    public long st_nlink = 0;
    /** User-id of owner. Type: uid_t (4 bytes) */
    public long st_uid = 0;
    /** Group-id of owner. Type: gid_t (4 bytes) */
    public long st_gid = 0;
    /** Device type, for special file inode. Type: dev_t (4 bytes) */
    public long st_rdev = 0;
    /** Time of last access. */
    public final Timespec st_atimespec = new Timespec();
    /** Time of last data modification. */
    public final Timespec st_mtimespec = new Timespec();
    /** Time of last file status change. */
    public final Timespec st_ctimespec = new Timespec();
    /** File size, in bytes. Type: off_t (8 bytes) */
    public long st_size = 0;
    /** Blocks allocated for file. Type: quad_t (8 bytes) */
    public long st_blocks = 0;
    /** Optimal file sys I/O ops blocksize. Type: u_long (4 bytes) */
    public long st_blocksize = 0;
    /** User defined flags for file. Type: u_long (4 bytes) */
    public long st_flags = 0;
    /** File generation number. Type: u_long (4 bytes) */
    public long st_gen = 0;

    /**
     * Zeroes all instance fields in the object.
     */
    public void zero() {
        st_dev = 0;
        st_ino = 0;
        st_mode = 0;
        st_nlink = 0;
        st_uid = 0;
        st_gid = 0;
        st_rdev = 0;
        st_atimespec.zero();
        st_mtimespec.zero();
        st_ctimespec.zero();
        st_size = 0;
        st_blocks = 0;
        st_blocksize = 0;
        st_flags = 0;
        st_gen = 0;
    }

    public void printFields(String prefix, PrintStream ps) {
        ps.println(prefix + "st_dev = " + st_dev);
        ps.println(prefix + "st_ino = " + st_ino);
        ps.println(prefix + "st_mode = 0x" + Long.toHexString(st_mode));
        ps.println(prefix + "st_nlink = " + st_nlink);
        ps.println(prefix + "st_uid = " + st_uid);
        ps.println(prefix + "st_gid = " + st_gid);
        ps.println(prefix + "st_rdev = " + st_rdev);
        ps.println(prefix + "st_atimespec:");
        st_atimespec.print(prefix + " ", ps);
        st_mtimespec.print(prefix + " ", ps);
        st_ctimespec.print(prefix + " ", ps);
        ps.println(prefix + "st_size = " + st_size);
        ps.println(prefix + "st_blocks = " + st_blocks);
        ps.println(prefix + "st_blocksize = " + st_blocksize);
        ps.println(prefix + "st_flags = " + st_flags);
        ps.println(prefix + "st_gen = " + st_gen);
    }
}
