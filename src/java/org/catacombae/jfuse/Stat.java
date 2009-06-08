/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package org.catacombae.jfuse;

/**
 *
 * @author erik
 */
public class Stat {
    /** type of file */
    public static final int S_IFMT = 0170000;
    /** named pipe (fifo) */
    public static final int S_IFIFO = 0010000;
    /** character special */
    public static final int S_IFCHR = 0020000;
    /** directory */
    public static final int S_IFDIR = 0040000;
    /** block special */
    public static final int S_IFBLK = 0060000;
    /** regular */
    public static final int S_IFREG = 0100000;
    /** symbolic link */
    public static final int S_IFLNK = 0120000;
    /** socket */
    public static final int S_IFSOCK = 0140000;
    /** whiteout */
    public static final int S_IFWHT = 0160000;
    /** set user id on execution */
    public static final int S_ISUID = 0004000;
    /** set group id on execution */
    public static final int S_ISGID = 0002000;
    /** save swapped text even after use */
    public static final int S_ISVTX = 0001000;
    /** read permission, owner */
    public static final int S_IRUSR = 0000400;
    /** write permission, owner */
    public static final int S_IWUSR = 0000200;
    /** execute/search permission, owner */
    public static final int S_IXUSR = 0000100;

    /** Type: dev_t (4 bytes) */
    public long st_dev = 0;
    /** Type: ino_t (4 bytes) */
    public long st_ino = 0;
    /** Type: mode_t (2 bytes) */
    public long st_mode = 0;
    /** Type: nlink_t (2 bytes) */
    public long st_nlink = 0;
    /** Type: uid_t (4 bytes) */
    public long st_uid = 0;
    /** Type: gid_t (4 bytes) */
    public long st_gid = 0;
    /** Type: dev_t (4 bytes) */
    public long st_rdev = 0;
    /** Type: __darwin_time_t (4 bytes (32-bit platforms), 8 bytes (64-bit platforms)) */
    public long st_atimespec_sec = 0;
    /** Type: long (4 bytes (32-bit platforms), 8 bytes (64-bit platforms)) */
    public long st_atimespec_nsec = 0;
    /** Type: __darwin_time_t (4 bytes (32-bit platforms), 8 bytes (64-bit platforms)) */
    public long st_mtimespec_sec = 0;
    /** Type: long (4 bytes (32-bit platforms), 8 bytes (64-bit platforms)) */
    public long st_mtimespec_nsec = 0;
    /** Type: __darwin_time_t (4 bytes (32-bit platforms), 8 bytes (64-bit platforms)) */
    public long st_ctimespec_sec = 0;
    /** Type: long (4 bytes (32-bit platforms), 8 bytes (64-bit platforms)) */
    public long st_ctimespec_nsec = 0;
    /** Type: off_t (8 bytes) */
    public long st_size = 0;
    /** Type: quad_t (8 bytes) */
    public long st_blocks = 0;
    /** Type: u_long (4 bytes) */
    public long st_blocksize = 0;
    /** Type: u_long (4 bytes) */
    public long st_flags = 0;
    /** Type: u_long (4 bytes) */
    public long st_gen = 0;

    /**
     * Zeroes all instance fields in the object.
     */
    public void zero() {
        st_dev = 0;
        st_ino = 0;
        st_mode = 0;
        st_nlink = 0;
        st_uid = 0;
        st_gid = 0;
        st_rdev = 0;
        st_atimespec_sec = 0;
        st_atimespec_nsec = 0;
        st_mtimespec_sec = 0;
        st_mtimespec_nsec = 0;
        st_ctimespec_sec = 0;
        st_ctimespec_nsec = 0;
        st_size = 0;
        st_blocks = 0;
        st_blocksize = 0;
        st_flags = 0;
        st_gen = 0;
    }
}
