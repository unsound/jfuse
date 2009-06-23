/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package org.catacombae.jfuse;

/**
 * Java representation of <code>struct statvfs</code>.
 *
 * @author erik
 */
public class StatVFS {
    /** File system block size */
    long f_bsize;
    /** Fundamental file system block size */
    long f_frsize;
    /** Blocks on FS in units of f_frsize */
    long f_blocks;
    /** Free blocks */
    long f_bfree;
    /** Blocks available to non-root */
    long f_bavail;
    /** Total inodes */
    long f_files;
    /** Free inodes */
    long f_ffree;
    /** Free inodes for non-root */
    long f_favail;
    /** Filesystem ID */
    long f_fsid;
    /** Bit mask of values */
    long f_flag;
    /** Max file name length */
    long f_namemax;
}
