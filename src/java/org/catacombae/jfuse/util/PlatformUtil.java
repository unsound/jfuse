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

package org.catacombae.jfuse.util;

/**
 * This class contains a few constants describing the current platform.
 *
 * @author Erik Larsson
 */
public class PlatformUtil {
    /** Set to true if the currently running platform is Mac OS X. */
    public static final boolean isMacOSX;
    /** Set to true if the currently running platform is Linux. */
    public static final boolean isLinux;
    /** Set to true if the currently running platform is Solaris. */
    public static final boolean isSolaris;
    /** Set to true if the currently running platform is FreeBSD. */
    public static final boolean isFreeBSD;
    /** Set to true if the currently running platform is NetBSD. */
    public static final boolean isNetBSD;

    static {
        boolean macosx = false;
        boolean linux = false;
        boolean solaris = false;
        boolean freebsd = false;
        boolean netbsd = false;

        String osName = System.getProperty("os.name");
        if(osName != null) {
            String osNameLowercase = osName.toLowerCase();

            if(osNameLowercase.startsWith("mac os x"))
                macosx = true;
            else if(osNameLowercase.startsWith("linux"))
                linux = true;
            else if(osNameLowercase.startsWith("sunos"))
                solaris = true;
            else if(osNameLowercase.startsWith("freebsd"))
                freebsd = true;
            else if(osNameLowercase.startsWith("netbsd"))
                netbsd = true;
        }

        isMacOSX = macosx;
        isLinux = linux;
        isSolaris = solaris;
        isFreeBSD = freebsd;
        isNetBSD = netbsd;
    }

    private PlatformUtil() {}
}
