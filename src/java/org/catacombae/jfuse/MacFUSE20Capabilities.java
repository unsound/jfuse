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

import java.io.PrintStream;
import java.lang.reflect.Field;

/**
 *
 * @author erik
 */
public class MacFUSE20Capabilities {
    public boolean exchange = false;
    public boolean getxtimes = false;
    public boolean setbkuptime = false;
    public boolean setcrtime = false;
    public boolean chflags = false;
    public boolean setattr_x = false;
    public boolean fsetattr_x = false;

    public void printFields(PrintStream ps, String prefix) {
        try {
            for(Field f : getClass().getDeclaredFields())
                ps.println(prefix + f.getName() + ": " + f.getBoolean(this));
        } catch(IllegalAccessException ex) {
            throw new RuntimeException(ex);
        }
    }

    public void print(PrintStream ps, String prefix) {
        ps.println(prefix + MacFUSE20Capabilities.class.getSimpleName() + ":");
        printFields(ps, prefix + "  ");
    }
}
