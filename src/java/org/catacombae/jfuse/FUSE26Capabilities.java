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
public class FUSE26Capabilities {
    public boolean getattr = false;
    public boolean readlink = false;
    public boolean getdir = false;
    public boolean mknod = false;
    public boolean mkdir = false;
    public boolean unlink = false;
    public boolean rmdir = false;
    public boolean symlink = false;
    public boolean rename = false;
    public boolean link = false;
    public boolean chmod = false;
    public boolean chown = false;
    public boolean truncate = false;
    public boolean utime = false;
    public boolean open = false;
    public boolean read = false;
    public boolean write = false;
    public boolean statfs = false;
    public boolean flush = false;
    public boolean release = false;
    public boolean fsync = false;
    public boolean setxattr_BSD = false;
    public boolean setxattr = false;
    public boolean getxattr_BSD = false;
    public boolean getxattr = false;
    public boolean listxattr = false;
    public boolean removexattr = false;
    public boolean opendir = false;
    public boolean readdir = false;
    public boolean releasedir = false;
    public boolean fsyncdir = false;
    public boolean init = false;
    public boolean destroy = false;
    public boolean access = false;
    public boolean create = false;
    public boolean ftruncate = false;
    public boolean fgetattr = false;
    public boolean lock = false;
    public boolean utimens = false;
    public boolean bmap = false;

    public void printFields(PrintStream ps, String prefix) {
        try {
            for(Field f : getClass().getDeclaredFields())
                ps.println(prefix + f.getName() + ": " + f.getBoolean(this));
        } catch(IllegalAccessException ex) {
            throw new RuntimeException(ex);
        }
    }

    public void print(PrintStream ps, String prefix) {
        ps.println(prefix + FUSE26Capabilities.class.getSimpleName() + ":");
        printFields(ps, prefix + "  ");
    }
}
