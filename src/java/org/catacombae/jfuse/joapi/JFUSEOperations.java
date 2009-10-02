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

package org.catacombae.jfuse.joapi;

import java.nio.ByteBuffer;
import org.catacombae.jfuse.types.fuse26.FUSEConnInfo;
import org.catacombae.jfuse.types.fuse26.FUSEDirFil;
import org.catacombae.jfuse.types.fuse26.FUSEFileInfo;
import org.catacombae.jfuse.types.fuse26.FUSEFillDir;
import org.catacombae.jfuse.types.system.Flock;
import org.catacombae.jfuse.types.system.LongRef;
import org.catacombae.jfuse.types.system.Stat;
import org.catacombae.jfuse.types.system.StatVFS;
import org.catacombae.jfuse.types.system.Timespec;
import org.catacombae.jfuse.types.system.Utimbuf;

/**
 *
 * @author erik
 */
public interface JFUSEOperations {
    /**
     * <pre>
     * Get file attributes.
     *
     * Similar to stat().  The 'st_dev' and 'st_blksize' fields are
     * ignored.  The 'st_ino' field is ignored except if the 'use_ino'
     * mount option is given.
     * </pre>
     *
     * @param path <b>(const char*)</b>
     * @param stat <b>(struct stat*)</b>
     */
    public void getattr(String path,
			Stat stat) throws JFUSEException;

    /**
     * <pre>
     * Read the target of a symbolic link.
     *
     * The buffer should be filled with a null terminated string.  The
     * buffer size argument includes the space for the terminating
     * null character.  If the linkname is too long to fit in the
     * buffer, it should be truncated.  The return value should be 0
     * for success.
     * </pre>
     * In jFUSE the buffer size argument has already been parsed when this
     * method gets the buffer. The byte array passed to readlink has a size
     * equal to the size of the native buffer.
     *
     * @param path <b>(const char*)</b>
     * @param buffer <b>(char*)</b>
     */
    public void readlink(String path,
			 ByteBuffer buffer) throws JFUSEException;

    /**
     * <pre>
     * Deprecated, use readdir() instead.
     * </pre>
     *
     * @param path <b>(const char*)</b>
     * @param filler <b>(fuse_dirfil_t)</b>
     * @deprecated
     */
    @Deprecated
    public void getdir(String path,
		       FUSEDirFil filler) throws JFUSEException;

    /**
     * <pre>
     * Create a file node.
     *
     * This is called for creation of all non-directory, non-symlink
     * nodes.  If the filesystem defines a create() method, then for
     * regular files that will be called instead.
     * </pre>
     *
     * @param path <b>(const char*)</b>
     * @param fileMode <b>(mode_t)</b>
     * @param deviceNumber <b>(dev_t)</b>
     */
    public void mknod(String path,
		      short fileMode,
		      long deviceNumber) throws JFUSEException;

    /**
     * <pre>
     * Create a directory.
     * </pre>
     *
     * @param path <b>(const char*)</b> the path to the file system node on
     * which the operation is to be applied.
     * @param createMode <b>(mode_t)</b>
     */
    public void mkdir(String path,
		      short createMode) throws JFUSEException;

    /**
     * <pre>
     * Remove a file.
     * </pre>
     *
     * @param path <b>(const char*)</b> the path to the file system node on
     * which the operation is to be applied.
     */
    public void unlink(String path) throws JFUSEException;

    /**
     * <pre>
     * Remove a directory.
     * </pre>
     *
     * @param path <b>(const char*)</b> the path to the file system node on
     * which the operation is to be applied.
     */
    public void rmdir(String path) throws JFUSEException;

    /**
     * <pre>
     * Create a symbolic link.
     * </pre>
     *
     * @param sourcePath <b>(const char*)</b>
     * @param destPath <b>(const char*)</b>
     */
    public void symlink(String sourcePath,
			String destPath) throws JFUSEException;

    /**
     * <pre>
     * Rename a file.
     * </pre>
     *
     * @param oldPath <b>(const char*)</b>
     * @param newPath <b>(const char*)</b>
     */
    public void rename(String oldPath,
		       String newPath) throws JFUSEException;

    /**
     * <pre>
     * Create a hard link to a file.
     * </pre>
     *
     * @param sourcePath <b>(const char*)</b>
     * @param destPath <b>(const char*)</b>
     */
    public void link(String sourcePath,
		     String destPath) throws JFUSEException;

    /**
     * <pre>
     * Change the permission bits of a file.
     * </pre>
     *
     * @param path <b>(const char*)</b> the path to the file system node on
     * which the operation is to be applied.
     * @param newMode <b>(mode_t)</b>
     */
    public void chmod(String path,
		      short newMode) throws JFUSEException;

    /**
     * <pre>
     * Change the owner and group of a file
     * </pre>
     *
     * @param path <b>(const char*)</b> the path to the file system node on
     * which the operation is to be applied.
     * @param userId <b>(uid_t)</b>
     * @param groupId <b>(uid_t)</b>
     */
    public void chown(String path,
		      long userId,
		      long groupId) throws JFUSEException;

    /**
     * <pre>
     * Change the size of a file.
     * </pre>
     *
     * @param path <b>(const char*)</b> the path to the file system node on
     * which the operation is to be applied.
     * @param newSize <b>(off_t)</b>
     */
    public void truncate(String path,
			 long newSize) throws JFUSEException;

    /**
     * <pre>
     * Change the access and/or modification times of a file.
     *
     * Deprecated, use utimens() instead.
     * </pre>
     *
     * @param path <b>(const char*)</b> the path to the file system node on
     * which the operation is to be applied.
     * @param time <b>(struct utimbuf*)</b>
     * @deprecated
     */
    @Deprecated
    public void utime(String path,
		      Utimbuf time) throws JFUSEException;

    /**
     * <pre>
     * File open operation.
     *
     * No creation, or truncation flags (O_CREAT, O_EXCL, O_TRUNC)
     * will be passed to open().  Open should check if the operation
     * is permitted for the given flags.  Optionally open may also
     * return an arbitrary filehandle in the fuse_file_info structure,
     * which will be passed to all file operations.
     *
     * Changed in version 2.2
     * </pre>
     *
     * @param path <b>(const char*)</b> the path to the file system node on
     * which the operation is to be applied.
     * @param fi <b>(struct fuse_file_info*)</b>
     */
    public void open(String path,
		     FUSEFileInfo fi) throws JFUSEException;

    /**
     * <pre>
     * Read data from an open file.
     *
     * Read should return exactly the number of bytes requested except
     * on EOF or error, otherwise the rest of the data will be
     * substituted with zeroes.  An exception to this is when the
     * 'direct_io' mount option is specified, in which case the return
     * value of the read system call will reflect the return value of
     * this operation.
     *
     * Changed in version 2.2
     * </pre>
     *
     * @param path <b>(const char*)</b> a path to the file to read from.
     * @param dest <b>(char*)</b> the destination buffer.
     * @param off <b>(off_t)</b> offset in file to start reading.
     * @param fi <b>(struct fuse_file_info*)</b> file info.
     */
    public int read(String path,
		     ByteBuffer dest,
		     long off,
		     FUSEFileInfo fi) throws JFUSEException;

    /**
     * <pre>
     * Write data to an open file.
     *
     * Write should return exactly the number of bytes requested
     * except on error.  An exception to this is when the 'direct_io'
     * mount option is specified (see read operation).
     *
     * Changed in version 2.2
     * </pre>
     *
     * @param path <b>(const char*)</b> the path to the file system node on
     * which the operation is to be applied.
     * @param src <b>(const char*)</b> the data to write.
     * @param off <b>(off_t)</b> offset in file where data should be written.
     * @param fi <b>(struct fuse_file_info*)</b>
     */
    public int write(String path,
		      ByteBuffer src,
		      long off,
		      FUSEFileInfo fi) throws JFUSEException;

    /**
     * <pre>
     * Get file system statistics.
     *
     * The 'f_frsize', 'f_favail', 'f_fsid' and 'f_flag' fields are ignored
     *
     * Replaced 'struct statfs' parameter with 'struct statvfs' in
     * version 2.5
     * </pre>
     *
     * @param path <b>(const char*)</b> the path to the file system node on
     * which the operation is to be applied.
     * @param stat <b>(struct statvfs*)</b>
     */
    public void statfs(String path,
		       StatVFS stat) throws JFUSEException;

    /**
     * <pre>
     * Possibly flush cached data.
     *
     * BIG NOTE: This is not equivalent to fsync().  It's not a
     * request to sync dirty data.
     *
     * Flush is called on each close() of a file descriptor.  So if a
     * filesystem wants to return write errors in close() and the file
     * has cached dirty data, this is a good place to write back data
     * and return any errors.  Since many applications ignore close()
     * errors this is not always useful.
     *
     * NOTE: The flush() method may be called more than once for each
     * open().  This happens if more than one file descriptor refers
     * to an opened file due to dup(), dup2() or fork() calls.  It is
     * not possible to determine if a flush is final, so each flush
     * should be treated equally.  Multiple write-flush sequences are
     * relatively rare, so this shouldn't be a problem.
     *
     * Filesystems shouldn't assume that flush will always be called
     * after some writes, or that if will be called at all.
     *
     * Changed in version 2.2
     * </pre>
     *
     * @param path <b>(const char*)</b> the path to the file system node on
     * which the operation is to be applied.
     * @param fi <b>(struct fuse_file_info*)</b>
     */
    public void flush(String path,
		      FUSEFileInfo fi) throws JFUSEException;

    /**
     * <pre>
     * Release an open file.
     *
     * Release is called when there are no more references to an open
     * file: all file descriptors are closed and all memory mappings
     * are unmapped.
     *
     * For every open() call there will be exactly one release() call
     * with the same flags and file descriptor.  It is possible to
     * have a file opened more than once, in which case only the last
     * release will mean, that no more reads/writes will happen on the
     * file.  The return value of release is ignored.
     *
     * Changed in version 2.2
     * </pre>
     *
     * @param path <b>(const char*)</b> the path to the file system node on
     * which the operation is to be applied.
     * @param fi <b>(struct fuse_file_info*)</b>
     */
    public void release(String path,
			FUSEFileInfo fi) throws JFUSEException;

    /**
     * <pre>
     * Synchronize file contents.
     *
     * If the datasync parameter is non-zero, then only the user data
     * should be flushed, not the meta data.
     *
     * Changed in version 2.2
     * </pre>
     *
     * @param path <b>(const char*)</b> the path to the file system node on
     * which the operation is to be applied.
     * @param datasync <b>(int)</b> set to <code>true</code> if only the user data should be
     * flushed, and not the meta-data.
     * @param fi <b>(struct fuse_file_info*)</b>
     */
    public void fsync(String path, boolean datasync, FUSEFileInfo fi) throws JFUSEException;

    /**
     * <pre>
     * Set extended attributes.
     * </pre>
     *
     * This is the FreeBSD version of the callback. If you want your application
     * to respond properly to the setxattr call on all platforms, you need to
     * implement both setxattr callbacks.
     *
     * @param path <b>(const char*)</b>
     * @param name <b>(const char*)</b>
     * @param value <b>(const char*)</b>
     * @param flags <b>(int)</b>
     * @param position <b>(uint32_t)</b>
     * @throws JFUSEException if the operation could not complete successfully.
     */
    public void setxattr(String path,
			 String name,
			 ByteBuffer value,
			 int flags,
			 int position) throws JFUSEException;

    /**
     * <pre>
     * Set extended attributes.
     * </pre>
     *
     * This is the non-BSD version of the callback. If you want your application
     * to respond properly to the setxattr call on all platforms, you need to
     * implement both setxattr and setxattr_BSD.
     *
     * @param path <b>(const char*)</b>
     * @param name <b>(const char*)</b>
     * @param value <b>(const char*)</b>
     * @param flags <b>(int)</b>
     * @throws JFUSEException if the operation could not complete successfully.
     */
    public void setxattr(String path,
            String name,
            ByteBuffer value,
            int flags) throws JFUSEException;

    /**
     * <pre>
     * Get extended attributes.
     * </pre>
     *
     * This is the FreeBSD version of the callback. If you want your application
     * to respond properly to the getxattr call on all platforms, you need to
     * implement both getxattr callbacks.
     *
     * @param path <b>(const char*)</b>
     * @param name <b>(const char*)</b>
     * @param value <b>(char*)</b> (out)
     * @param position <b>(uint32_t)</b>
     * @return the size of the retrieved extended attribute data.
     * @throws JFUSEException if the operation could not complete successfully.
     */
    public int getxattr(String path,
			 String name,
			 ByteBuffer value,
			 int position) throws JFUSEException;

    /**
     * <pre>
     * Get extended attributes.
     * </pre>
     *
     * This is the non-BSD version of the callback. If you want your application
     * to respond properly to the getxattr call on all platforms, you need to
     * implement both getxattr and getxattr_BSD.
     *
     * @param path <b>(const char*)</b>
     * @param name <b>(const char*)</b>
     * @param value <b>(char*)</b> (out)
     * @return the size of the retrieved extended attribute data.
     * @throws JFUSEException if the operation could not complete successfully.
     */
    public int getxattr(String path,
            String name,
            ByteBuffer value) throws JFUSEException;

    /**
     * <pre>
     * List extended attributes.
     * </pre>
     *
     * @param path <b>(const char*)</b>
     * @param namebuf <b>(char*)</b> the buffer where we store the result.
     * @return the size of the extended attributes list.
     * @throws JFUSEException if the operation could not complete successfully.
     */
    public int listxattr(String path,
			  ByteBuffer namebuf) throws JFUSEException;

    /**
     * <pre>
     * Remove extended attributes.
     * </pre>
     *
     * @param path <b>(const char*)</b>
     * @param name <b>(const char*)</b>
     * @throws JFUSEException if the operation could not complete successfully.
     */
    public void removexattr(String path,
			    String name) throws JFUSEException;

    /**
     * <pre>
     * Open directory.
     *
     * This method should check if the open operation is permitted for
     * this  directory
     *
     * Introduced in version 2.3
     * </pre>
     *
     * @param path <b>(const char*)</b>
     * @param fi <b>(struct fuse_file_info*)</b>
     */
    public void opendir(String path,
			FUSEFileInfo fi) throws JFUSEException;

    /**
     * <pre>
     * Read directory.
     *
     * This supersedes the old getdir() interface.  New applications
     * should use this.
     *
     * The filesystem may choose between two modes of operation:
     *
     * 1) The readdir implementation ignores the offset parameter, and
     * passes zero to the filler function's offset.  The filler
     * function will not return '1' (unless an error happens), so the
     * whole directory is read in a single readdir operation.  This
     * works just like the old getdir() method.
     *
     * 2) The readdir implementation keeps track of the offsets of the
     * directory entries.  It uses the offset parameter and always
     * passes non-zero offset to the filler function.  When the buffer
     * is full (or an error happens) the filler function will return
     * '1'.
     *
     * Introduced in version 2.3
     * </pre>
     *
     * @param path <b>(const char*)</b>
     * @param filler <b>(fuse_fill_dir_t)</b>
     * @param offset <b>(off_t)</b>
     * @param fi <b>(struct fuse_file_info*)</b>
     */
    public void readdir(String path,
			FUSEFillDir filler,
			long offset,
			FUSEFileInfo fi) throws JFUSEException;

    /**
     * <pre>
     * Release directory.
     *
     * Introduced in version 2.3
     * </pre>
     *
     * @param path <b>(const char*)</b>
     * @param fi <b>(struct fuse_file_info*)</b>
     */
    public void releasedir(String path,
			   FUSEFileInfo fi) throws JFUSEException;

    /**
     * <pre>
     * Synchronize directory contents.
     *
     * If the datasync parameter is non-zero, then only the user data
     * should be flushed, not the meta data
     *
     * Introduced in version 2.3
     * </pre>
     *
     * @param path <b>(const char*)</b>
     * @param datasync <b>(int)</b>
     * @param fi <b>(struct fuse_file_info*)</b>
     */
    public void fsyncdir(String path,
			 boolean datasync,
			 FUSEFileInfo fi) throws JFUSEException;

    /**
     * <pre>
     * Initialize filesystem.
     *
     * The return value will passed in the private_data field of
     * fuse_context to all file operations and as a parameter to the
     * destroy() method.
     *
     * Introduced in version 2.3
     * Changed in version 2.6
     * </pre>
     *
     * @param conn <b>(struct fuse_conn_info*)</b>
     * @return (optional) a return value that will be passed in the private_data
     * field of fuse_context to all file operations and as a parameter to the
     * destroy() method.
     */
    public Object init(FUSEConnInfo conn);

    /**
     * <pre>
     * Clean up filesystem.
     *
     * Called on filesystem exit.
     *
     * Introduced in version 2.3
     * </pre>
     */
    public void destroy(Object o);

    /**
     * <pre>
     * Check file access permissions.
     *
     * This will be called for the access() system call.  If the
     * 'default_permissions' mount option is given, this method is not
     * called.
     *
     * This method is not called under Linux kernel versions 2.4.x
     *
     * Introduced in version 2.5
     * </pre>
     *
     * @param path <b>(const char*)</b>
     * @param mode <b>(int)</b>
     */
    public void access(String path,
		       int mode) throws JFUSEException;

    /**
     * <pre>
     * Create and open a file.
     *
     * If the file does not exist, first create it with the specified
     * mode, and then open it.
     *
     * If this method is not implemented or under Linux kernel
     * versions earlier than 2.6.15, the mknod() and open() methods
     * will be called instead.
     *
     * Introduced in version 2.5
     * </pre>
     *
     * @param path <b>(const char*)</b> path to the newly created file.
     * @param mode <b>(mode_t)</b> the mode flags for the created file.
     * @param fi <b>(struct fuse_file_info*)</b>
     */
    public void create(String path,
		       short mode,
		       FUSEFileInfo fi) throws JFUSEException;

    /**
     * <pre>
     * Change the size of an open file.
     *
     * This method is called instead of the truncate() method if the
     * truncation was invoked from an ftruncate() system call.
     *
     * If this method is not implemented or under Linux kernel
     * versions earlier than 2.6.15, the truncate() method will be
     * called instead.
     *
     * Introduced in version 2.5
     * </pre>
     *
     * @param path <b>(const char*)</b>
     * @param length <b>(off_t)</b>
     * @param fi <b>(struct fuse_file_info*)</b>
     */
    public void ftruncate(String path,
			  long length,
			  FUSEFileInfo fi) throws JFUSEException;

    /**
     * <pre>
     * Get attributes from an open file.
     *
     * This method is called instead of the getattr() method if the
     * file information is available.
     *
     * Currently this is only called after the create() method if that
     * is implemented (see above).  Later it may be called for
     * invocations of fstat() too.
     *
     * Introduced in version 2.5
     * </pre>
     *
     * @param path <b>(const char*)</b>
     * @param stat <b>(struct stat*)</b>
     * @param fi <b>(struct fuse_file_info*)</b>
     */
    public void fgetattr(String path,
			 Stat stat,
			 FUSEFileInfo fi) throws JFUSEException;

    /**
     * <pre>
     * Perform POSIX file locking operation.
     *
     * The cmd argument will be either F_GETLK, F_SETLK or F_SETLKW.
     *
     * For the meaning of fields in 'struct flock' see the man page
     * for fcntl(2).  The l_whence field will always be set to
     * SEEK_SET.
     *
     * For checking lock ownership, the 'fuse_file_info->owner'
     * argument must be used.
     *
     * For F_GETLK operation, the library will first check currently
     * held locks, and if a conflicting lock is found it will return
     * information without calling this method.  This ensures, that
     * for local locks the l_pid field is correctly filled in.  The
     * results may not be accurate in case of race conditions and in
     * the presence of hard links, but it's unlikly that an
     * application would rely on accurate GETLK results in these
     * cases.  If a conflicting lock is not found, this method will be
     * called, and the filesystem may fill out l_pid by a meaningful
     * value, or it may leave this field zero.
     *
     * For F_SETLK and F_SETLKW the l_pid field will be set to the pid
     * of the process performing the locking operation.
     *
     * Note: if this method is not implemented, the kernel will still
     * allow file locking to work locally.  Hence it is only
     * interesting for network filesystems and similar.
     *
     * Introduced in version 2.6
     * </pre>
     *
     * @param path <b>(const char*)</b>
     * @param fi <b>(struct fuse_file_info*)</b>
     * @param cmd <b>(int)</b>
     * @param flock <b>(struct flock*)</b>
     */
    public void lock(String path,
		     FUSEFileInfo fi,
		     int cmd,
		     Flock flock) throws JFUSEException;

    /**
     * <pre>
     * Change the access and modification times of a file with
     * nanosecond resolution.
     *
     * Introduced in version 2.6
     * </pre>
     *
     * @param path <b>(const char*)</b>
     * @param accessTime <b>(const struct timespec)</b>
     * @param modificationTime <b>(const struct timespec)</b>
     */
    public void utimens(String path,
			Timespec accessTime,
                        Timespec modificationTime) throws JFUSEException;

    /**
     * <pre>
     * Map block index within file to block index within device.
     *
     * Note: This makes sense only for block device backed filesystems
     * mounted with the 'blkdev' option
     *
     * Introduced in version 2.6
     * </pre>
     *
     * @param path <b>(const char*)</b>
     * @param blocksize <b>(size_t)</b>
     * @param idx <b>(uint64_t*)</b>
     */
    public void bmap(String path,
		     long blocksize,
		     LongRef idx) throws JFUSEException;

}
