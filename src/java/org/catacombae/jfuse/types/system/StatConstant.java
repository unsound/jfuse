/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package org.catacombae.jfuse.types.system;

import org.catacombae.jfuse.*;

/**
 *
 * @author erik
 */
public enum StatConstant {
    /** mask: type of file */
    S_IFMT,
    /** named pipe (fifo) */
    S_IFIFO,
    /** character special */
    S_IFCHR,
    /** directory */
    S_IFDIR,
    /** block special */
    S_IFBLK,
    /** regular */
    S_IFREG,
    /** symbolic link */
    S_IFLNK,
    /** socket */
    S_IFSOCK,
    /** whiteout */
    //S_IFWHT,
    /** set user id on execution */
    S_ISUID,
    /** set group id on execution */
    S_ISGID,
    /** save swapped text even after use */
    S_ISVTX,
    /** read permission, owner */
    S_IRUSR,
    /** write permission, owner */
    S_IWUSR,
    /** execute/search permission, owner */
    S_IXUSR;

    private final int nativeValue;

    private StatConstant() {
        JNILoader.ensureLoaded();

        this.nativeValue = getNativeValue(name());
    }

    public int getNativeValue() {
        return nativeValue;
    }

    private static native int getNativeValue(String constantName);

    public static void main(String[] args) {
        for(StatConstant v : StatConstant.values())
            System.out.println(v.name() + ": " + v.nativeValue);
    }
}