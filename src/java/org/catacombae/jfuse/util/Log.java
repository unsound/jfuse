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

package org.catacombae.jfuse.util;

/**
 *
 * @author erik
 */
public class Log {
    public static void traceEnter(String methodName, Object... args) {
        StringBuilder sb = new StringBuilder("ENTER: ");
        sb.append(methodName).append("(");
        for(int i = 0; i < args.length; ++i) {
            if(i != 0)
                sb.append(", ");
            sb.append(args[i]);
        }
        sb.append(")");
        
        System.err.println(sb.toString());
    }

    public static void traceLeave(String methodName, Object retval, Object... args) {
        StringBuilder sb = new StringBuilder("LEAVE: ");
        sb.append(methodName).append("(");
        for(int i = 0; i < args.length; ++i) {
            if(i != 0)
                sb.append(", ");
            sb.append(args[i]);
        }
        sb.append("): ").append(retval);

        System.err.println(sb.toString());
    }

    public static void traceLeaveVoid(String methodName, Object... args) {
        StringBuilder sb = new StringBuilder("LEAVE: ");
        sb.append(methodName).append("(");
        for(int i = 0; i < args.length; ++i) {
            if(i != 0)
                sb.append(", ");
            sb.append(args[i]);
        }
        sb.append(")");

        System.err.println(sb.toString());
    }

    /**
     * Free form TRACE level log message.
     * @param msg
     */
    public static void trace(String msg) {
        System.err.println("TRACE: " + msg);
    }

    public static void debug(String msg) {
        System.err.println("DEBUG: " + msg);
    }

    public static void warning(String msg) {
        System.err.println("WARNING: " + msg);
    }

    public static void error(String msg) {
        System.err.println("ERROR: " + msg);
    }

    public static void info(String msg) {
        System.err.println("INFO: " + msg);
    }

    public static void notice(String msg) {
        System.err.println("NOTICE: " + msg);
    }
}
