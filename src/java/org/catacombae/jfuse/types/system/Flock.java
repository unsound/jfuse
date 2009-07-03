/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package org.catacombae.jfuse.types.system;

/**
 *
 * @author erik
 */
public class Flock {
    /** starting offset */
    public long l_start;

    /** len = 0 means until end of file */
    public long l_len;

    /** lock owner */
    public long l_pid;

    /** lock type: read/write, etc. */
    public short l_type;

    /* type of l_start */
    public short l_whence;
}
