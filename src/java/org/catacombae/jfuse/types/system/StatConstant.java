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

import org.catacombae.jfuse.JNILoader;

/**
 *
 * @author erik
 */
enum StatConstant {
    /** mask: type of file */
    S_IFMT,
    /** named pipe (fifo) */
    S_IFIFO,
    /** character special */
    S_IFCHR,
    /** directory */
    S_IFDIR,
    /** block special */
    S_IFBLK,
    /** regular */
    S_IFREG,
    /** symbolic link */
    S_IFLNK,
    /** socket */
    S_IFSOCK,
    /** whiteout */
    //S_IFWHT, // Not portable.
    /** RWX mask for owner. */
    S_IRWXU,
    /** read permission, owner */
    S_IRUSR,
    /** write permission, owner */
    S_IWUSR,
    /** execute/search permission, owner */
    S_IXUSR,
    /** RWX mask for group. */
    S_IRWXG,
    /** read permission, group */
    S_IRGRP,
    /** write permission, group */
    S_IWGRP,
    /** execute/search permission, group */
    S_IXGRP,
    /** RWX mask for other. */
    S_IRWXO,
    /** read permission, other */
    S_IROTH,
    /** write permission, other */
    S_IWOTH,
    /** execute/search permission, other */
    S_IXOTH,
    /** set user id on execution */
    S_ISUID,
    /** set group id on execution */
    S_ISGID,
    /** save swapped text even after use */
    S_ISVTX,
    ;

    private final int nativeValue;

    private StatConstant() {
        JNILoader.ensureLoaded();

        this.nativeValue = getNativeValue(name());
    }

    public int getNativeValue() {
        return nativeValue;
    }

    private static native int getNativeValue(String constantName);

    public static void main(String[] args) {
        for(StatConstant v : StatConstant.values())
            System.out.println(v.name() + ": " + v.nativeValue);
    }
}