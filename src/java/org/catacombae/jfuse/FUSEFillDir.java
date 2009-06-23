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

public class FUSEFillDir {
    static {
        JNILoader.ensureLoaded();
    }

    private final byte[] nativeContextPointer;

    public FUSEFillDir(byte[] nativeContextPointer) {
        if(nativeContextPointer == null)
            throw new IllegalArgumentException("null nativeContextPointer not allowed.");

        this.nativeContextPointer = new byte[nativeContextPointer.length];
        System.arraycopy(nativeContextPointer, 0, this.nativeContextPointer, 0,
                this.nativeContextPointer.length);
    }


    @Override
    public void finalize() throws Throwable {
        FUSEDirFil.freeNative(nativeContextPointer);
    }

    //* @param voidp_buf the buffer passed to the readdir() operation
    /**
     * Function to add an entry in a readdir() operation
     *
     * @param name <b>(const char*)</b> the file name of the directory entry
     * @param stat <b>(const struct stat*)</b> file attributes, can be NULL
     * @param off <b>(off_t)</b> offset of the next entry or zero
     * @return true if buffer is full, false otherwise
     */
    public boolean fill(byte[] name, Stat stat, long off) {
        return fillNative(name, stat, off);
    }

    private native boolean fillNative(byte[] name, Stat stat, long off);
}

// /** Function to add an entry in a readdir() operation
//  *
//  * @param buf the buffer passed to the readdir() operation
//  * @param name the file name of the directory entry
//  * @param stat file attributes, can be NULL
//  * @param off offset of the next entry or zero
//  * @return 1 if buffer is full, zero otherwise
//  */
// typedef int (*fuse_fill_dir_t) (void *buf, const char *name,
//                                 const struct stat *stbuf, off_t off);