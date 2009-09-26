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

import java.io.File;
import org.catacombae.jfuse.types.fuse26.FUSEContext;
import org.catacombae.jfuse.util.Log;

/**
 * Hooks to some of the FUSE library functions.
 *
 * @author Erik Larsson
 */
public class FUSE {
    
    static {
        JNILoader.ensureLoaded();
    }

    private static final Object mountSync = new Object();

    /**
     * Convenience 'main' method to mount a FUSE file system. The argument
     * array <code>args</code> is assumed to be in the form { "mountpoint",
     * "-ooption1", "-ooption2", ... }.
     * @param args          the argument array, i.e. the mountpoint followed by
     *                      zero or more options.
     * @param fileSystem    the file system to mount.
     */
    public static void main(String[] args, FUSE26FileSystem fileSystem) {
        System.err.println("FUSE.main(...)");
        if(args.length < 1)
            throw new IllegalArgumentException("You need to specify the " +
                    "mountpoint as the first argument.");

        String mountPoint = args[0];
        String[] adjustedArgs = new String[args.length - 1];
        if(adjustedArgs.length > 0)
            System.arraycopy(args, 1, adjustedArgs, 0, adjustedArgs.length);
        
        // Get absolute path to mountPoint (safest)
        Log.debug("Getting absolute path for \"" + mountPoint + "\":");
        mountPoint = new File(mountPoint).getAbsolutePath();
        Log.debug("    \"" + mountPoint + "\"");

        synchronized(mountSync) {
            System.err.println("Calling mountNative26 with args:");
            for(int i = 0; i < adjustedArgs.length; ++i)
                System.err.println("  adjustedArgs[" + i + "] = \"" +
                        adjustedArgs[i] + "\"");
            System.err.println("  ...");
            boolean res = mount26(fileSystem, mountPoint, adjustedArgs);
            System.err.println("  mountNative26 returned " + res + ".");
        }
    }

    public static void mount(FUSE26FileSystem fileSystem, String mountPoint,
            FUSEOptions options) {
        // Never allow more than one mount at the same time.
        synchronized(mountSync) {
            System.err.println("Calling mountNative26");
            boolean res = mount26(fileSystem, mountPoint,
                    options.generateOptionStrings());
            System.err.println("  mountNative26 returned " + res + ".");
        }
    }

    private static boolean mount26(FUSE26FileSystem fileSystem,
            final String mountPoint, String[] optionStrings) {
        FUSE26Capabilities fuseCapabilities = fileSystem.getFUSECapabilities();
        MacFUSE20Capabilities macFuseCapabilities;
        if(fileSystem instanceof MacFUSE20FileSystem)
            macFuseCapabilities = ((MacFUSE20FileSystem)fileSystem).getMacFUSECapabilities();
        else
            macFuseCapabilities = null;

        Thread shutdownHook = new Thread() {
            @Override
            public void run() {
                Log.debug("Shutdown hook invoked... trying to unmount \"" +
                        mountPoint + "\"");
                boolean res = unmount(mountPoint, true);
                if(res)
                    Log.debug("Successfully unmounted \"" + mountPoint + "\"");
                else
                    Log.error("Shutdown hook could not unmount \"" +
                            mountPoint + "\"!");
            }
        };

        Runtime.getRuntime().addShutdownHook(shutdownHook);

        boolean res = mountNative26(fileSystem, mountPoint, optionStrings,
                fuseCapabilities, macFuseCapabilities);

        try {
            if(!Runtime.getRuntime().removeShutdownHook(shutdownHook))
                Log.error("FUSE.mount26: Could not remove shutdown hook!");
        } catch(IllegalStateException e) {
            // No worries. This happens when the user presses "Ctrl-C".
            Log.debug("Shutdown hook was not removed since we are in the " +
                    "process of shutting down the JVM.");
        }

        return res;
    }

    private static native boolean mountNative26(FUSE26FileSystem fileSystem,
            String mountPoint, String[] optionStrings,
            FUSE26Capabilities fuseCapabilities,
            MacFUSE20Capabilities macFuseCapabilities);

    /**
     * Get the current context
     *
     * The context is only valid for the duration of a filesystem
     * operation, and thus must not be stored and used later.
     *
     * @return the context
     */
    public static FUSEContext getContext() {
        return getContextNative();
    }

    private static native FUSEContext getContextNative();

    private static boolean unmount(String mountPoint, boolean force) {
        return unmountNative(mountPoint, force);
    }

    private static native boolean unmountNative(String mountPoint, boolean force);
}
