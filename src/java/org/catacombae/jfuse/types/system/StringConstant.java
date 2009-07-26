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
enum StringConstant {
    /**
     * The extended attribute name reserved for the Mac OS "Finder info".
     * The value of this constant will be <code>null</code> on non-Mac OS X systems.
     */
    XATTR_FINDERINFO_NAME,
    /**
     * The extended attribute name reserved for the Mac OS "resource fork".
     * The value of this constant will be <code>null</code> on non-Mac OS X systems.
     */
    XATTR_RESOURCEFORK_NAME,
    ;

    private final String value;

    private StringConstant() {
        JNILoader.ensureLoaded();

        String nativeValue;
        try {
            nativeValue = getNativeValue(name());
        } catch(NoSuchConstantException e) {
            nativeValue = null;
        }

        this.value = nativeValue;
    }

    public String getValue() {
        return value;
    }

    private static native String getNativeValue(String constantName) throws NoSuchConstantException;

    public static void main(String[] args) {
        for(StringConstant v : StringConstant.values())
            System.out.println(v.name() + ": " + v.getValue());
    }
}
