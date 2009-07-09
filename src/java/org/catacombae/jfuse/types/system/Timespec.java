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

import java.util.Date;

/**
 * A Java mapping of <code>struct timespec</code>.
 *
 * @author Erik Larsson
 */
public class Timespec {
    /** Seconds. */
    public int sec;
    /** Nanoseconds. */
    public int nsec;

    /**
     * Sets the fields of this Timespec object to the specified time value,
     * expressed in milliseconds since January 1, 1970, 00:00:00 GMT.
     *
     * @param millis the new time value, in milliseconds since January 1, 1970,
     * 00:00:00 GMT.
     */
    public void setToMillis(long millis) {
        sec = (int)(millis / 1000);
        nsec = (int)(millis-sec*1000)*1000000;
    }

    /**
     * Sets the fields of this Timespec object to the specified time value,
     * expressed as a Java date.
     *
     * @param d the new time value.
     */
    public void setToDate(Date d) {
        setToMillis(d.getTime());
    }
}
