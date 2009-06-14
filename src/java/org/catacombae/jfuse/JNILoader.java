/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package org.catacombae.jfuse;

/**
 *
 * @author erik
 */
class JNILoader {
    private static final Object loadSync = new Object();
    private static boolean loaded = false;

    private JNILoader() { throw new RuntimeException(); }

    public static void ensureLoaded() {
        synchronized(loadSync) {
            if(!loaded) {
                System.err.println("Loading library 'jfuse'...");
                System.loadLibrary("jfuse");
                loaded = true;
                System.err.println("   done.");
            }
        }
    }
}
