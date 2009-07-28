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

package org.catacombae.jfuse.types.macfuse20;

import org.catacombae.jfuse.types.system.Stat;
import org.catacombae.jfuse.types.system.Timespec;

/**
 * MacFUSE structure which is used in the setattr_x and fsetattr_x operations to
 * return a lot of different attributes at one time, reducing kernel/userspace
 * communication.
 *
 * @author Erik Larsson
 */
public class Setattr_x {
    ///** What is this? Whether or not the struct is valid? TODO: check this. <b>(int32_t)</b> */
    //public int valid; // Not needed.

    /** File mode. <b>(mode_t)</b> */
    public short mode;

    /** User ID of the entry. <b>(uid_t)</b> */
    public long uid;

    /** Group ID of the entry. <b>(gid_t)</b> */
    public long gid;

    /** Size of the entry. <b>(off_t)</b> */
    public long size;

    /** Last accessed time. <b>(struct timespec)</b> */
    public final Timespec acctime = new Timespec();

    /** Last data modification time. <b>(struct timespec)</b> */
    public final Timespec modtime = new Timespec();

    /** Create time. <b>(struct timespec)</b> */
    public final Timespec crtime = new Timespec();

    /** Last file status change time. <b>(struct timespec)</b> */
    public final Timespec chgtime = new Timespec();

    /** Last backup time. <b>(struct timespec)</b> */
    public final Timespec bkuptime = new Timespec();

    /** Flags (probably equivalent to {@link Stat#st_flags}). <b>(uint32_t)</b> */
    public int flags;

    private boolean wantsMode = false;
    private boolean wantsUid = false;
    private boolean wantsGid = false;
    private boolean wantsSize = false;
    private boolean wantsAcctime = false;
    private boolean wantsModtime = false;
    private boolean wantsCrtime = false;
    private boolean wantsChgtime = false;
    private boolean wantsBkuptime = false;
    private boolean wantsFlags = false;

    /**
     * Whether or not this setattr_x session wants the file system to set the
     * variable 'mode'.
     */
    public boolean wantsMode() {
        return wantsMode;
    }

    /**
     * Whether or not this setattr_x session wants the file system to set the
     * variable 'uid'.
     */
    public boolean wantsUid() {
        return wantsUid;
    }

    /**
     * Whether or not this setattr_x session wants the file system to set the
     * variable 'gid'.
     */
    public boolean wantsGid() {
        return wantsGid;
    }

    /**
     * Whether or not this setattr_x session wants the file system to set the
     * variable 'size'.
     */
    public boolean wantsSize() {
        return wantsSize;
    }

    /**
     * Whether or not this setattr_x session wants the file system to set the
     * variable 'acctime'.
     */
    public boolean wantsAcctime() {
        return wantsAcctime;
    }

    /**
     * Whether or not this setattr_x session wants the file system to set the
     * variable 'modtime'.
     */
    public boolean wantsModtime() {
        return wantsModtime;
    }

    /**
     * Whether or not this setattr_x session wants the file system to set the
     * variable 'crtime'.
     */
    public boolean wantsCrtime() {
        return wantsCrtime;
    }

    /**
     * Whether or not this setattr_x session wants the file system to set the
     * variable 'chgtime'.
     */
    public boolean wantsChgtime() {
        return wantsChgtime;
    }

    /**
     * Whether or not this setattr_x session wants the file system to set the
     * variable 'bkuptime'.
     */
    public boolean wantsBkuptime() {
        return wantsBkuptime;
    }

    /**
     * Whether or not this setattr_x session wants the file system to set the
     * variable 'flags'.
     */
    public boolean wantsFlags() {
        return wantsFlags;
    }

    @Override
    public String toString() {
        return getClass().getName() +
                "[mode=0" + Integer.toOctalString(mode) +
                " uid=" + uid +
                " gid=" + gid +
                " size=" + size +
                " acctime=" + acctime +
                " modtime=" + modtime +
                " crtime=" + crtime +
                " chgtime=" + chgtime +
                " bkuptime=" + bkuptime +
                " flags=0x" + Integer.toHexString(flags) +
                " wantsMode=" + wantsMode +
                " wantsUid=" + wantsUid +
                " wantsGid=" + wantsGid +
                " wantsSize=" + wantsSize +
                " wantsAcctime=" + wantsAcctime +
                " wantsModtime=" + wantsModtime +
                " wantsCrtime=" + wantsCrtime +
                " wantsChgtime=" + wantsChgtime +
                " wantsBkuptime=" + wantsBkuptime +
                " wantsFlags=" + wantsFlags +
                "]";
    }

}
