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

import org.catacombae.jfuse.types.macfuse20.Setattr_x;
import org.catacombae.jfuse.types.system.Timespec;
import org.catacombae.jfuse.types.fuse26.FUSEFileInfo;

/**
 * MacFUSE 2.0 extensions to FUSE 2.6 operations.
 *
 * @author Erik Larsson
 */
public interface MacFUSE20Operations extends FUSE26Operations {
    /**
     * See exchange(2) for more info.
     *
     * @param path1 <b>(const char*)</b>
     * @param path2 <b>(const char*)</b>
     * @param options <b>(uint32_t)</b>
     * @return 0 if successful and a negated error value from FUSEErrorValues
     * otherwise.
     */
	int exchange(String path1, String path2, long options);

    /**
     * Get the Mac OS X extended time values "backup time" and "create time".
     *
     * @param path <b>(const char*)</b>
     * @param bkuptime <b>(struct timespec*)</b>
     * @param crtime <b>(struct timespec*)</b>
     * @return 0 if successful or a negated error value from FUSEErrorValues
     * otherwise.
     */
    public int getxtimes(String path, Timespec bkuptime, Timespec crtime);

    /**
     * Set the Mac OS X extended time value "backup time".
     *
     * @param path <b>(const char*)</b>
     * @param tv <b>(const struct timespec*)</b>
     * @return 0 if successful or a negated error value from FUSEErrorValues
     * otherwise.
     */
    public int setbkuptime(String path, Timespec tv);

    /**
     * Set the Mac OS X extended time value "create time".
     *
     * @param path <b>(const char*)</b>
     * @param tv <b>(const struct timespec*)</b>
     * @return 0 if successful and a negated error value from FUSEErrorValues
     * otherwise.
     */
    public int setcrtime(String path, Timespec tv);

    /**
     * 
     * @param path <b>(const char*)</b>
     * @param flags <b>(uint32_t)</b>
     * @return 0 if successful and a negated error value from FUSEErrorValues
     * otherwise.
     */
	public int chflags(String path, int flags);

    /**
     *
     * @param path <b>(const char*)</b>
     * @param attr <b>(struct setattr_x*)</b>
     * @return 0 if successful and a negated error value from FUSEErrorValues
     * otherwise.
     */
	public int setattr_x(String path, Setattr_x attr);

    /**
     *
     * @param path <b>(const char*)</b>
     * @param attr <b>(struct setattr_x*)</b>
     * @param fi <b>(struct fuse_file_info*)</b>
     * @return 0 if successful and a negated error value from FUSEErrorValues
     * otherwise.
     */
	public int fsetattr_x(String path, Setattr_x attr, FUSEFileInfo fi);
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