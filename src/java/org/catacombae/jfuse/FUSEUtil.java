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

package org.catacombae.jfuse;

import java.io.UnsupportedEncodingException;

/**
 *
 * @author erik
 */
public class FUSEUtil {
    public static byte[] encodeUTF8(String str) {
        try {
            // TODO: Encode properly and deal with errors.
            return str.getBytes("UTF-8");
        } catch(UnsupportedEncodingException e) {
            throw new RuntimeException("UTF-8 charset not found! This should not happen...", e);
        }
    }

    public static String decodeUTF8(byte[] utf8Data) {
        try {
            // TODO: Decode properly and deal with errors.
            return new String(utf8Data, 0, utf8Data.length, "UTF-8");
        } catch(UnsupportedEncodingException e) {
            throw new RuntimeException("UTF-8 charset not found! This should not happen...", e);
        }
    }
}
