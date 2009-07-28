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

import java.nio.ByteBuffer;
import org.catacombae.jfuse.types.macfuse20.Setattr_x;
import org.catacombae.jfuse.types.system.Timespec;
import org.catacombae.jfuse.types.fuse26.FUSEFileInfo;

/**
 * MacFUSE 2.0 extensions to FUSE operations. These operations will only be
 * called if jFUSE is running in a MacFUSE 2.0 (or later) environment.
 *
 * @author Erik Larsson
 */
public interface MacFUSE20Operations {

    /**
     * Atomically exchange data between two files. See exchangedata(2) for more
     * info.
     *
     * @param path1 path to the first file. <b>(const char*)</b>
     * @param path2 path to the second file. <b>(const char*)</b>
     * @param options options to the exchange operation. <b>(uint32_t)</b>
     * @return 0 if successful and a negated error value from FUSEErrorValues
     * otherwise.
     */
    public int exchange(ByteBuffer path1, ByteBuffer path2, long options);

    /**
     * Get the Mac OS X extended time values "backup time" and "create time".
     * <br/>
     * Note: For things to work as smoothly as possible in Mac OS X, you should
     * implement all of the extended time callbacks (getxtimes, setcrtime,
     * setbkuptime and setcrtim), or none at all. (For a read-only file system,
     * the set-callbacks don't need to be implemented.)
     *
     * @param path <b>(const char*)</b>
     * @param bkuptime <b>(struct timespec*)</b>
     * @param crtime <b>(struct timespec*)</b>
     * @return 0 if successful or a negated error value from FUSEErrorValues
     * otherwise.
     */
    public int getxtimes(ByteBuffer path, Timespec bkuptime, Timespec crtime);

    /**
     * Set the Mac OS X extended time value "backup time".<br/>
     * Note: For things to work as smoothly as possible in Mac OS X, you should
     * implement all of the extended time callbacks (getxtimes, setcrtime,
     * setbkuptime and setcrtim), or none at all. (For a read-only file system,
     * the set-callbacks don't need to be implemented.)
     *
     * @param path <b>(const char*)</b>
     * @param tv <b>(const struct timespec*)</b>
     * @return 0 if successful or a negated error value from FUSEErrorValues
     * otherwise.
     */
    public int setbkuptime(ByteBuffer path, Timespec tv);

    /**
     * Set the Mac OS X extended time value "create time".<br/>
     * Note: For things to work as smoothly as possible in Mac OS X, you should
     * implement all of the extended time callbacks (getxtimes, setcrtime,
     * setbkuptime and setcrtim), or none at all. (For a read-only file system,
     * the set-callbacks don't need to be implemented.)
     *
     * @param path <b>(const char*)</b>
     * @param tv <b>(const struct timespec*)</b>
     * @return 0 if successful and a negated error value from FUSEErrorValues
     * otherwise.
     */
    public int setcrtime(ByteBuffer path, Timespec tv);

    /**
     * Set the UNIX time value ctime ("Time when file status was last changed").
     * This time value can not normally be set explicitly, but Mac OS X allows
     * it.<br/>
     * Note: For things to work as smoothly as possible in Mac OS X, you should
     * implement all of the extended time callbacks (getxtimes, setcrtime,
     * setbkuptime and setcrtim), or none at all. (For a read-only file system,
     * the set-callbacks don't need to be implemented.)
     *
     * @param path <b>(const char*)</b>
     * @param tv <b>(const struct timespec*)</b>
     * @return 0 if successful and a negated error value from FUSEErrorValues
     * otherwise.
     */
    public int setchgtime(ByteBuffer path, Timespec tv);

    /**
     * Change file flags. See chflags(2) for more info.
     * 
     * @param path <b>(const char*)</b>
     * @param flags <b>(uint32_t)</b>
     * @return 0 if successful and a negated error value from FUSEErrorValues
     * otherwise.
     */
    public int chflags(ByteBuffer path, int flags);

    /**
     * Set many attributes in a single call. If you implement setattr_x and
     * fsetattr_x, they together replace the operations chmod, chown, utimens,
     * truncate, ftruncate, chflags, setcrtime, and setbkuptime. None of these
     * replaced operations will be called if setattr_x and fsetattr_x are
     * implemented. (Note that this only applies if MacFUSE is available. They
     * are ignored in regular FUSE.)
     *
     * @param path <b>(const char*)</b>
     * @param attr <b>(struct setattr_x*)</b>
     * @return 0 if successful and a negated error value from FUSEErrorValues
     * otherwise.
     */
    public int setattr_x(ByteBuffer path, Setattr_x attr);

    /**
     * Set many attributes in a single call. If you implement setattr_x and
     * fsetattr_x, they together replace the operations chmod, chown, utimens,
     * truncate, ftruncate, chflags, setcrtime, and setbkuptime. None of these
     * replaced operations will be called if setattr_x and fsetattr_x are
     * implemented. (Note that this only applies if MacFUSE is available. They
     * are ignored in regular FUSE.)
     *
     * @param path <b>(const char*)</b>
     * @param attr <b>(struct setattr_x*)</b>
     * @param fi <b>(struct fuse_file_info*)</b>
     * @return 0 if successful and a negated error value from FUSEErrorValues
     * otherwise.
     */
    public int fsetattr_x(ByteBuffer path, Setattr_x attr, FUSEFileInfo fi);
}

/* From fuse/fuse.h, MacFUSE 2.0.2/2.0.3:
        int (*reserved00)(void *, void *, void *, void *, void *, void *,
                          void *, void *);
        int (*reserved01)(void *, void *, void *, void *, void *, void *,
                          void *, void *);
        int (*reserved02)(void *, void *, void *, void *, void *, void *,
                          void *, void *);
        int (*reserved03)(void *, void *, void *, void *, void *, void *,
                          void *, void *);
        int (*reserved04)(void *, void *, void *, void *, void *, void *,
                          void *, void *);
        int (*reserved05)(void *, void *, void *, void *, void *, void *,
                          void *, void *);
        int (*reserved06)(void *, void *, void *, void *, void *, void *,
                          void *, void *);
        int (*reserved07)(void *, void *, void *, void *, void *, void *,
                          void *, void *);
        int (*reserved08)(void *, void *, void *, void *, void *, void *,
                          void *, void *);
        int (*reserved09)(void *, void *, void *, void *, void *, void *,
                          void *, void *);
        int (*reserved10)(void *, void *, void *, void *, void *, void *,
                          void *, void *);

        int (*setvolname) (const char *);

	int (*exchange) (const char *, const char *, unsigned long);

        int (*getxtimes) (const char *, struct timespec *bkuptime,
			  struct timespec *crtime);

        int (*setbkuptime) (const char *, const struct timespec *tv);

        int (*setchgtime) (const char *, const struct timespec *tv);

        int (*setcrtime) (const char *, const struct timespec *tv);

	int (*chflags) (const char *, uint32_t);

	int (*setattr_x) (const char *, struct setattr_x *);

	int (*fsetattr_x) (const char *, struct setattr_x *,
			   struct fuse_file_info *);
*/
