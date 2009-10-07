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
import org.catacombae.jfuse.util.Log;

/**
 * This enum enumerates some important system constants that may be useful when
 * developing jFUSE file systems. Not all constans are guaranteed to be defined
 * on the host system, in which case <code>getValue()</code> will return
 * <code>null</code>.
 * The interface SystemConstants contains all constants that are guaranteed to
 * be available on all systems that jFUSE supports.
 *
 * @author Erik Larsson
 */
public enum NumericalConstant {

    /* Begin: Constants from sys/fcntl.h */

    /** sys/fcntl.h: Mask for open modes (O_RDONLY, O_WRONLY and O_RDWR). */
    O_ACCMODE,

    /** sys/fcntl.h: Open for reading only. */
    O_RDONLY,

    /** sys/fcntl.h: Open for writing only */
    O_WRONLY,

    /** sys/fcntl.h: Open for reading and writing. */
    O_RDWR,

    /** sys/fcntl.h: Do not block on open or for data to become available. */
    O_NONBLOCK,

    /** sys/fcntl.h: Set append mode (append on each write). */
    O_APPEND,

    /** sys/fcntl.h: Create file if it does not exist. */
    O_CREAT,

    /** sys/fcntl.h: Truncate size to 0. */
    O_TRUNC,

    /** sys/fcntl.h: Error if O_CREAT and the file exists. */
    O_EXCL,

    /** sys/fcntl.h: Don't follow symlinks. */
    O_NOFOLLOW,

    /** sys/fcntl.h: Synchronous writes. */
    O_SYNC,

    /** sys/fcntl.h: Don't assign controlling terminal. */
    O_NOCTTY,

    /** sys/fcntl.h: Non-blocking I/O. */
    O_NDELAY,

    /* The following constants are not present on all systems that jFUSE
     * supports. Thus their value may be null. */

    /** sys/fcntl.h: <b>(Mac OS X)</b> Descriptor requested for event notifications only. */
    O_EVTONLY,

    /** sys/fcntl.h: <b>(Mac OS X)</b> Allow open of a symlink. */
    O_SYMLINK,

    /** sys/fcntl.h: <b>(Mac OS X, Linux)</b> Must be a directory. */
    O_DIRECTORY,

    /**
     * sys/fcntl.h: <b>(Mac OS X, Linux, NetBSD)</b> Signal pgrp when data
     * ready.
     */
    O_ASYNC,

    /**
     * sys/fcntl.h: <b>(Mac OS X, NetBSD)</b> Atomically obtain an exclusive
     * lock.
     */
    O_EXLOCK,

    /**
     * sys/fcntl.h: <b>(Mac OS X, NetBSD)</b> Atomically obtain a shared lock.
     */
    O_SHLOCK,

    /** sys/fcntl.h: <b>(Linux)</b> ? */
    O_FSYNC,

    /** sys/fcntl.h: <b>(Linux)</b> Set close_on_exec. */
    O_CLOEXEC,

    /** sys/fcntl.h: <b>(Linux)</b> Direct disk access. */
    O_DIRECT,

    /** sys/fcntl.h: <b>(Linux)</b> Do not set atime. */
    O_NOATIME,

    /**
     * sys/fcntl.h: <b>(Linux, NetBSD, Solaris)</b> Synchronized update of file
     * data.
     */
    O_DSYNC,

    /**
     * sys/fcntl.h: <b>(Linux, NetBSD, Solaris)</b> Synchronized update of file
     * (read/write file integrity).
     */
    O_RSYNC,

    /**
     * sys/fcntl.h: <b>(Linux, Solaris)</b>  Maximum offset limit is the largest
     * value of off64_t.
     */
    O_LARGEFILE,

    /**
     * sys/fcntl.h: <b>(Solaris)</b> Don't allow multiple hard links.
     */
    O_NOLINKS,

    /**
     * sys/fcntl.h: <b>(Solaris)</b> openat(2) request is for an extended
     * attribute.
     */
    O_XATTR,

    /* End: Constants from sys/fcntl.h */


    /* Begin: Constants from sys/xattr.h */

    /**
     * sys/xattr.h: <b>(Mac OS X)</b> Maximum length of an xattr name.
     */
    XATTR_MAXNAMELEN,

    /**
     * sys/xattr.h: <b>(Mac OS X, Linux)</b> Set the value, fail if attr already
     * exists.
     */
    XATTR_CREATE,

    /**
     * sys/xattr.h: <b>(Mac OS X, Linux)</b> Set the value, fail if attr does
     * not exist.
     */
    XATTR_REPLACE,

    /* End: Constants from sys/xattr.h */

    ;

    private final Integer value;

    private NumericalConstant() {
        JNILoader.ensureLoaded();

        Integer nativeValue;
        try {
            nativeValue = getNativeValue(name());
        } catch(NoSuchConstantException e) {
            Log.notice("No native numerical constant value found for " +
                    name() + ". Message: " + e.getMessage());
            nativeValue = null;
        }

        this.value = nativeValue;
    }

    /**
     * Returns the value of the constant, if the constant exists in the host's
     * execution environment, or <code>null</code> if it isn't available on the
     * currently running system.
     *
     * @return the value of the constant, or <code>null</code> if not available.
     */
    public Integer getValue() {
        return value;
    }

    private static native int getNativeValue(String constantName) throws NoSuchConstantException;

    /**
     * Testcode.
     */
    public static void main(String[] args) {
        for(NumericalConstant v : NumericalConstant.values())
            System.out.println(v.name() + ": " + v.getValue());
    }

}
