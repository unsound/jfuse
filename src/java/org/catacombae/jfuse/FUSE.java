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
    private static final Object mountSync = new Object();

    public static void main(String[] args, FUSE26FileSystem fs) {
        
    }

    public static void mount(FUSE26FileSystem fileSystem, String mountPoint, FUSEOptions options) {
        // Never allow more than one mount at the same time.
        synchronized(mountSync) {
            mountNative26(fileSystem, mountPoint, options);
        }
    }

    private static native boolean mountNative26(FUSE26FileSystem fileSystem,
            String mountPoint, FUSEOptions options);
}
