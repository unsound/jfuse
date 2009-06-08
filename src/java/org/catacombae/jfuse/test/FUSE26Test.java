/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package org.catacombae.jfuse.test;

import org.catacombae.jfuse.FUSE26Capabilities;
import org.catacombae.jfuse.FUSE26FileSystemAdapter;
import org.catacombae.jfuse.LongRef;
import org.catacombae.jfuse.Stat;

/**
 *
 * @author erik
 */
public class FUSE26Test {
    public static void main(String[] args) {
        FUSE26Capabilities c = new FUSE26Capabilities();

        //c.print(System.out, "");

        FUSE26FileSystemAdapter fs = new Yada() {
            @Override
            public int getattr(byte[] path, Stat stat) {
                return -ENOENT;
            }
        };

        fs.getCapabilities().print(System.out, "");
    }

    private static class Yada extends FUSE26FileSystemAdapter {
        @Override
        public int bmap(byte[] path,
		     long blocksize,
		     LongRef idx) {
            return -ENOENT;
        }
    }
}
