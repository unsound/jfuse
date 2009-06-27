/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package org.catacombae.jfuse;

import java.util.Date;

/**
 *
 * @author erik
 */
public class Stat {
    /** type of file */
    public static final int S_IFMT = StatConstant.S_IFMT.getNativeValue();
    /** named pipe (fifo) */
    public static final int S_IFIFO = StatConstant.S_IFIFO.getNativeValue();
    /** character special */
    public static final int S_IFCHR = StatConstant.S_IFCHR.getNativeValue();
    /** directory */
    public static final int S_IFDIR = StatConstant.S_IFDIR.getNativeValue();
    /** block special */
    public static final int S_IFBLK = StatConstant.S_IFBLK.getNativeValue();
    /** regular */
    public static final int S_IFREG = StatConstant.S_IFREG.getNativeValue();
    /** symbolic link */
    public static final int S_IFLNK = StatConstant.S_IFLNK.getNativeValue();
    /** socket */
    public static final int S_IFSOCK = StatConstant.S_IFSOCK.getNativeValue();
    /** whiteout */
    public static final int S_IFWHT = StatConstant.S_IFWHT.getNativeValue();
    /** set user id on execution */
    public static final int S_ISUID = StatConstant.S_ISUID.getNativeValue();
    /** set group id on execution */
    public static final int S_ISGID = StatConstant.S_ISGID.getNativeValue();
    /** save swapped text even after use */
    public static final int S_ISVTX = StatConstant.S_ISVTX.getNativeValue();
    /** read permission, owner */
    public static final int S_IRUSR = StatConstant.S_IRUSR.getNativeValue();
    /** write permission, owner */
    public static final int S_IWUSR = StatConstant.S_IWUSR.getNativeValue();
    /** execute/search permission, owner */
    public static final int S_IXUSR = StatConstant.S_IXUSR.getNativeValue();

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

    /* TODO: st_?timespec should be of class Timespec. */

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

    public void setAccessTimeToDate(Date d) {
        long millis = d.getTime();
        st_atimespec_sec = millis / 1000;
        st_atimespec_nsec = (millis % 1000) * 1000000;
    }

    public void setModifyTimeToDate(Date d) {
        long millis = d.getTime();
        st_mtimespec_sec = millis / 1000;
        st_mtimespec_nsec = (millis % 1000) * 1000000;
    }

    public void setStatusChangeTimeToDate(Date d) {
        long millis = d.getTime();
        st_ctimespec_sec = millis / 1000;
        st_ctimespec_nsec = (millis % 1000) * 1000000;
    }

    public Date getAccessTimeAsDate() {
        return new Date(st_atimespec_sec*1000 + st_atimespec_nsec/1000000);
    }

    public Date getModifyTimeAsDate() {
        return new Date(st_mtimespec_sec*1000 + st_mtimespec_nsec/1000000);
    }

    public Date getStatusChangeTimeAsDate() {
        return new Date(st_ctimespec_sec*1000 + st_ctimespec_nsec/1000000);
    }
}
