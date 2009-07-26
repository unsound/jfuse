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
 * An exception that gets thrown by the native code when the requested constant could not be found
 * in the headers of the current system.
 *
 * @author Erik Larsson
 */
public class NoSuchConstantException extends Exception {
    /** @see Exception#Exception() */
    public NoSuchConstantException() {
        super();
    }

    /** @see Exception#Exception(java.lang.String)  */
    public NoSuchConstantException(String message) {
        super(message);
    }

    /** @see Exception#Exception(java.lang.Throwable) */
    public NoSuchConstantException(Throwable cause) {
        super(cause);
    }

    /** @see Exception#Exception(java.lang.String, java.lang.Throwable) */
    public NoSuchConstantException(String message, Throwable cause) {
        super(message, cause);
    }
}
