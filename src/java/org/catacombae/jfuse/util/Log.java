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
    public static boolean noticeEnabled = true;
    public static boolean traceEnabled = true;
    public static boolean debugEnabled = true;
    public static boolean warningEnabled = true;
    public static boolean errorEnabled = true;

    public static void traceEnter(String methodName, Object... args) {
        if(traceEnabled) {
            StringBuilder sb = new StringBuilder("ENTER: ");
            sb.append(methodName).append("(");
            for(int i = 0; i < args.length; ++i) {
                if(i != 0) {
                    sb.append(", ");
                }
                sb.append(args[i]);
            }
            sb.append(")");

            System.err.println(sb.toString());
        }
    }

    public static void traceLeave(String methodName, Object retval, Object... args) {
        if(traceEnabled) {
            StringBuilder sb = new StringBuilder("LEAVE: ");
            sb.append(methodName).append("(");
            for(int i = 0; i < args.length; ++i) {
                if(i != 0) {
                    sb.append(", ");
                }
                sb.append(args[i]);
            }
            sb.append("): ").append(retval);

            System.err.println(sb.toString());
        }
    }

    public static void traceLeaveVoid(String methodName, Object... args) {
        if(traceEnabled) {
            StringBuilder sb = new StringBuilder("LEAVE: ");
            sb.append(methodName).append("(");
            for(int i = 0; i < args.length; ++i) {
                if(i != 0) {
                    sb.append(", ");
                }
                sb.append(args[i]);
            }
            sb.append(")");

            System.err.println(sb.toString());
        }
    }

    /**
     * 'notice' is the least urgent log level. Messages printed at this level
     * are relatively unimportant for debugging, but might be interesting when
     * following the behaviour of the program.
     *
     * @param msg the log message.
     */
    public static void notice(String msg) {
        if(noticeEnabled)
            System.err.println("NOTICE: " + msg);
    }

    /**
     * Free form TRACE level log message.
     * @param msg
     */
    public static void trace(String msg) {
        if(traceEnabled)
            System.err.println("TRACE: " + msg);
    }

    public static void debug(String msg) {
        if(debugEnabled)
            System.err.println("DEBUG: " + msg);
    }

    public static void warning(String msg) {
        if(warningEnabled)
            System.err.println("WARNING: " + msg);
    }

    public static void error(String msg) {
        if(errorEnabled)
            System.err.println("ERROR: " + msg);
    }

    /**
     * The 'info' log level represents messages that should always be printed,
     * for instance for runtime diagnostic purposes. Use this log level
     * sparsely.
     *
     * @param msg the log message.
     */
    public static void info(String msg) {
        System.err.println("INFO: " + msg);
    }

}
