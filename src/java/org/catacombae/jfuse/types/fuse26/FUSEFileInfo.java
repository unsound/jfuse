/*-
 * jFUSE - FUSE bindings for Java
 * Copyright (C) 2008-2009  Erik Larsson <erik82@kth.se>
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
package org.catacombae.jfuse.types.fuse26;

import org.catacombae.jfuse.types.system.FileStatusFlags;

/**
 *
 * @author erik
 */
public class FUSEFileInfo implements FileStatusFlags {

    /** Open flags. Available in open() and release() */
    public int flags;

    /** Old file handle, don't use */
    public long fh_old;
    
    /**
     * In case of a write operation indicates if this was caused by a
     * writepage
     */
    public int writepage;

    /**
     * Can be filled in by open, to use direct I/O on this file.
     * Introduced in version 2.4
     */
    public boolean direct_io;

    /**
     * Can be filled in by open, to indicate, that cached file data
     * need not be invalidated.
     * Introduced in version 2.4
     */
    public boolean keep_cache;

    /**
     * Indicates a flush operation.  Set in flush operation, also
     * maybe set in highlevel lock operation and lowlevel release
     * operation.
     * Introduced in version 2.6
     */
    public boolean flush;

    /** Padding. Do not use*/
    //unsigned int padding : 29;

    /**
     * File handle. May be filled in by filesystem in open().
     * Available in all other file operations
     */
    public long fh;

    /** Lock owner id. Available in locking operations and flush */
    public long lock_owner;

    /** Convenience method that checks if O_RDONLY is set. */
    public boolean getFlagReadOnly() {
        return (flags & O_WRONLY) == 0;
    }

    /** Convenience method that checks if O_WRONLY is set. */
    public boolean getFlagWriteOnly() {
        return (flags & O_WRONLY) != 0;
    }

    /** Convenience method that checks if O_RDWR is set. */
    public boolean getFlagReadWrite() {
        return (flags & O_RDWR) != 0;
    }

    /** Convenience method that checks if O_NONBLOCK is set. */
    public boolean getFlagNonblock() {
        return (flags & O_NONBLOCK) != 0;
    }

    /** Convenience method that checks if O_APPEND is set. */
    public boolean getFlagAppend() {
        return (flags & O_APPEND) != 0;
    }

    /** Convenience method that checks if O_CREAT is set. */
    public boolean getFlagCreate() {
        return (flags & O_CREAT) != 0;
    }

    /** Convenience method that checks if O_TRUNC is set. */
    public boolean getFlagTruncate() {
        return (flags & O_TRUNC) != 0;
    }

    /** Convenience method that checks if O_EXCL is set. */
    public boolean getFlagExcl() {
        return (flags & O_EXCL) != 0;
    }

    /** Convenience method that checks if O_SHLOCK is set. */
    public boolean getFlagSharedLock() {
        return (flags & O_SHLOCK) != 0;
    }

    /** Convenience method that checks if O_EXLOCK is set. */
    public boolean getFlagExclusiveLock() {
        return (flags & O_EXLOCK) != 0;
    }

    /** Convenience method that checks if O_NOFOLLOW is set. */
    public boolean getFlagNofollow() {
        return (flags & O_NOFOLLOW) != 0;
    }

    /** Convenience method that checks if O_SYMLINK is set. */
    public boolean getFlagSymlink() {
        return (flags & O_SYMLINK) != 0;
    }
}
