/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package org.catacombae.jfuse;

/**
 *
 * @author erik
 */
public class FUSE {
    static {
        JNILoader.ensureLoaded();
    }

    private static final Object mountSync = new Object();

    public static void main(String[] args, FUSE26FileSystem fileSystem) {
        System.err.println("FUSE.main(...)");
        if(args.length < 1)
            throw new IllegalArgumentException("You need to specify the mount point as first argument.");
        String mountPoint = args[0];
        String[] adjustedArgs = new String[args.length-1];
        if(adjustedArgs.length > 0)
            System.arraycopy(args, 1, adjustedArgs, 0, adjustedArgs.length);

        synchronized(mountSync) {
            System.err.println("Calling mountNative26");
            mountNative26(fileSystem, mountPoint, adjustedArgs);
            System.err.println("  done calling mountNative26.");
        }
    }

    public static void mount(FUSE26FileSystem fileSystem, String mountPoint, FUSEOptions options) {
        // Never allow more than one mount at the same time.
        synchronized(mountSync) {
            System.err.println("Calling mountNative26");
            mountNative26(fileSystem, mountPoint, options.generateOptionStrings());
            System.err.println("  done calling mountNative26.");
        }
    }

    private static native boolean mountNative26(FUSE26FileSystem fileSystem,
            String mountPoint, String[] optionStrings);
}
