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

package org.catacombae.jfuse.types.fuse26;

/**
 * The jFUSE version of fuse_context.
 *
 * @author Erik Larsson
 */
public class FUSEContext {

    /** User ID of the calling process */
    public final long uid;

    /** Group ID of the calling process */
    public final long gid;

    /** Thread ID of the calling process */
    public final long pid;

    /** Private filesystem data. */
    public final Object privateData;

    private FUSEContext(long uid, long gid, long pid, Object privateData) {
        this.uid = uid;
        this.gid = gid;
        this.pid = pid;
        this.privateData = privateData;
    }
}
