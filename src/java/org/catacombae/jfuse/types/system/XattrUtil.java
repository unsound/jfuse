/*-
 * jFUSE - FUSE bindings for Java
 * Copyright (C) 2009  Erik Larsson <erik82@kth.se>
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
 *
 * @author erik
 */
public class XattrUtil {
    /**
     * Tests whether the flag XATTR_CREATE is set in <code>flags</code>.
     * If XATTR_CREATE isn't defined on this system, the method returns
     * <code>false</code>.
     *
     * @param flags the xattr flags.
     * @return whether the flag XATTR_CREATE is set in <code>flags</code>.
     */
    public static boolean isCreateFlagSet(int flags) {
        Integer xattr_create = NumericalConstant.XATTR_CREATE.getValue();
        if(xattr_create != null)
            return (flags & xattr_create) != 0;
        else
            return false;
    }

    /**
     * Tests whether the flag XATTR_REPLACE is set in <code>flags</code>.
     * If XATTR_REPLACE isn't defined on this system, the method returns
     * <code>false</code>.
     *
     * @param flags the xattr flags.
     * @return whether the flag XATTR_REPLACE is set in <code>flags</code>.
     */
    public static boolean isReplaceFlagSet(int flags) {
        Integer xattr_replace = NumericalConstant.XATTR_REPLACE.getValue();
        if(xattr_replace != null)
            return (flags & xattr_replace) != 0;
        else
            return false;
    }
}
