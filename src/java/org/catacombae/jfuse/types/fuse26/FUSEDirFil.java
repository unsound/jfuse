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

import org.catacombae.jfuse.JNILoader;

/** Used by deprecated getdir() method */
public class FUSEDirFil {
    static {
        JNILoader.ensureLoaded();
    }

    public final byte[] nativeContextPointer;

    public FUSEDirFil(byte[] nativeContextPointer) {
        if(nativeContextPointer == null)
            throw new IllegalArgumentException("null nativeContextPointer not allowed.");

        this.nativeContextPointer = new byte[nativeContextPointer.length];
        System.arraycopy(nativeContextPointer, 0, this.nativeContextPointer, 0,
                this.nativeContextPointer.length);
    }

    @Override
    public void finalize() throws Throwable {
        freeNative(nativeContextPointer);
    }

    /**
     * Fills a directory entry in a getdir operation.
     *
     * @param name  the name of the directory entry.
     * @param type  file type. See sys/dirent.h. Valid values are the DT_
     *              constants. (Set this to DT_UNKNOWN (0) if you're lazy.)
     * @param ino   inode number. This is limited to 32 bits on most systems,
     *              but 64-bit inode numbers do exist. As such, we use the long
     *              data type. (Set this to 0 if you're lazy.)
     * @return      1 if the buffer is full (?), 0 otherwise (?). (I'm unsure
     *              about this... it's undocumented in fuse.h.)
     */
    public int fill(byte[] name,
		     int type,
		     long ino) {
        return fillNative(nativeContextPointer, name, type, ino);
    }

    public static native int fillNative(byte[] nativeContextPointer,
            byte[] name, int type, long ino);

    /**
     * Frees a native pointer value, stored in the byte array
     * <code>nativeContextPointer</code>.<br>
     * TODO: Move this to a general utility class.
     *
     * @param nativeContextPointer a byte array containing the pointer value.
     */
    public static native void freeNative(byte[] nativeContextPointer);
}

// /* Used by deprecated getdir() method */
// typedef struct fuse_dirhandle *fuse_dirh_t;
// typedef int (*fuse_dirfil_t) (fuse_dirh_t h, const char *name, int type,
//                               ino_t ino);