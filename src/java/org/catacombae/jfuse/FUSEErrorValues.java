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

/**
 * <p>This interface contains constants taken from errno.h that can be used as
 * return values for jFUSE methods.</p>
 *
 * <p>The values of these constants are not hard coded, but fetched from native
 * code so they match the platform that the native library was compiled on.</p>
 *
 * @author Erik Larsson
 */
public interface FUSEErrorValues {

    /** Operation not permitted */
    public static final int EPERM = Errno.EPERM.getNativeErrnoValue();
    /** No such file or directory */
    public static final int ENOENT = Errno.ENOENT.getNativeErrnoValue();
    /** No such process */
    public static final int ESRCH = Errno.ESRCH.getNativeErrnoValue();
    /** Interrupted system call */
    public static final int EINTR = Errno.EINTR.getNativeErrnoValue();
    /** Input/output error */
    public static final int EIO = Errno.EIO.getNativeErrnoValue();
    /** Device not configured */
    public static final int ENXIO = Errno.ENXIO.getNativeErrnoValue();
    /** Argument list too long */
    public static final int E2BIG = Errno.E2BIG.getNativeErrnoValue();
    /** Exec format error */
    public static final int ENOEXEC = Errno.ENOEXEC.getNativeErrnoValue();
    /** Bad file descriptor */
    public static final int EBADF = Errno.EBADF.getNativeErrnoValue();
    /** No child processes */
    public static final int ECHILD = Errno.ECHILD.getNativeErrnoValue();
    /** Resource deadlock avoided */
    public static final int EDEADLK = Errno.EDEADLK.getNativeErrnoValue();
    /** Cannot allocate memory */
    public static final int ENOMEM = Errno.ENOMEM.getNativeErrnoValue();
    /** Permission denied */
    public static final int EACCES = Errno.EACCES.getNativeErrnoValue();
    /** Bad address */
    public static final int EFAULT = Errno.EFAULT.getNativeErrnoValue();
    /** Block device required */
    public static final int ENOTBLK = Errno.ENOTBLK.getNativeErrnoValue();
    /** Device busy */
    public static final int EBUSY = Errno.EBUSY.getNativeErrnoValue();
    /** File exists */
    public static final int EEXIST = Errno.EEXIST.getNativeErrnoValue();
    /** Cross-device link */
    public static final int EXDEV = Errno.EXDEV.getNativeErrnoValue();
    /** Operation not supported by device */
    public static final int ENODEV = Errno.ENODEV.getNativeErrnoValue();
    /** Not a directory */
    public static final int ENOTDIR = Errno.ENOTDIR.getNativeErrnoValue();
    /** Is a directory */
    public static final int EISDIR = Errno.EISDIR.getNativeErrnoValue();
    /** Invalid argument */
    public static final int EINVAL = Errno.EINVAL.getNativeErrnoValue();
    /** Too many open files in system */
    public static final int ENFILE = Errno.ENFILE.getNativeErrnoValue();
    /** Too many open files */
    public static final int EMFILE = Errno.EMFILE.getNativeErrnoValue();
    /** Inappropriate ioctl for device */
    public static final int ENOTTY = Errno.ENOTTY.getNativeErrnoValue();
    /** Text file busy */
    public static final int ETXTBSY = Errno.ETXTBSY.getNativeErrnoValue();
    /** File too large */
    public static final int EFBIG = Errno.EFBIG.getNativeErrnoValue();
    /** No space left on device */
    public static final int ENOSPC = Errno.ENOSPC.getNativeErrnoValue();
    /** Illegal seek */
    public static final int ESPIPE = Errno.ESPIPE.getNativeErrnoValue();
    /** Read-only file system */
    public static final int EROFS = Errno.EROFS.getNativeErrnoValue();
    /** Too many links */
    public static final int EMLINK = Errno.EMLINK.getNativeErrnoValue();
    /** Broken pipe */
    public static final int EPIPE = Errno.EPIPE.getNativeErrnoValue();

    /* math software */
    /** Numerical argument out of domain */
    public static final int EDOM = Errno.EDOM.getNativeErrnoValue();
    /** Result too large */
    public static final int ERANGE = Errno.ERANGE.getNativeErrnoValue();

    /* non-blocking and interrupt i/o */
    /** Resource temporarily unavailable */
    public static final int EAGAIN = Errno.EAGAIN.getNativeErrnoValue();
    /** Operation would block */
    public static final int EWOULDBLOCK = Errno.EWOULDBLOCK.getNativeErrnoValue();
    /** Operation now in progress */
    public static final int EINPROGRESS = Errno.EINPROGRESS.getNativeErrnoValue();
    /** Operation already in progress */
    public static final int EALREADY = Errno.EALREADY.getNativeErrnoValue();

    /* ipc/network software -- argument errors */
    /** Socket operation on non-socket */
    public static final int ENOTSOCK = Errno.ENOTSOCK.getNativeErrnoValue();
    /** Destination address required */
    public static final int EDESTADDRREQ = Errno.EDESTADDRREQ.getNativeErrnoValue();
    /** Message too long */
    public static final int EMSGSIZE = Errno.EMSGSIZE.getNativeErrnoValue();
    /** Protocol wrong type for socket */
    public static final int EPROTOTYPE = Errno.EPROTOTYPE.getNativeErrnoValue();
    /** Protocol not available */
    public static final int ENOPROTOOPT = Errno.ENOPROTOOPT.getNativeErrnoValue();
    /** Protocol not supported */
    public static final int EPROTONOSUPPORT = Errno.EPROTONOSUPPORT.getNativeErrnoValue();
    /** Socket type not supported */
    public static final int ESOCKTNOSUPPORT = Errno.ESOCKTNOSUPPORT.getNativeErrnoValue();
    /** Operation not supported */
    public static final int ENOTSUP = Errno.ENOTSUP.getNativeErrnoValue();
    /** Operation not supported on socket (all other systems) */
    public static final int EOPNOTSUPP = Errno.EOPNOTSUPP.getNativeErrnoValue();
    /** Protocol family not supported */
    public static final int EPFNOSUPPORT = Errno.EPFNOSUPPORT.getNativeErrnoValue();
    /** Address family not supported by protocol family */
    public static final int EAFNOSUPPORT = Errno.EAFNOSUPPORT.getNativeErrnoValue();
    /** Address already in use */
    public static final int EADDRINUSE = Errno.EADDRINUSE.getNativeErrnoValue();
    /** Can't assign requested address */
    public static final int EADDRNOTAVAIL = Errno.EADDRNOTAVAIL.getNativeErrnoValue();

    /* ipc/network software -- operational errors */
    /** Network is down */
    public static final int ENETDOWN = Errno.ENETDOWN.getNativeErrnoValue();
    /** Network is unreachable */
    public static final int ENETUNREACH = Errno.ENETUNREACH.getNativeErrnoValue();
    /** Network dropped connection on reset */
    public static final int ENETRESET = Errno.ENETRESET.getNativeErrnoValue();
    /** Software caused connection abort */
    public static final int ECONNABORTED = Errno.ECONNABORTED.getNativeErrnoValue();
    /** Connection reset by peer */
    public static final int ECONNRESET = Errno.ECONNRESET.getNativeErrnoValue();
    /** No buffer space available */
    public static final int ENOBUFS = Errno.ENOBUFS.getNativeErrnoValue();
    /** Socket is already connected */
    public static final int EISCONN = Errno.EISCONN.getNativeErrnoValue();
    /** Socket is not connected */
    public static final int ENOTCONN = Errno.ENOTCONN.getNativeErrnoValue();
    /** Can't send after socket shutdown */
    public static final int ESHUTDOWN = Errno.ESHUTDOWN.getNativeErrnoValue();
    /** Too many references: can't splice */
    public static final int ETOOMANYREFS = Errno.ETOOMANYREFS.getNativeErrnoValue();
    /** Operation timed out */
    public static final int ETIMEDOUT = Errno.ETIMEDOUT.getNativeErrnoValue();
    /** Connection refused */
    public static final int ECONNREFUSED = Errno.ECONNREFUSED.getNativeErrnoValue();
    /** Too many levels of symbolic links */
    public static final int ELOOP = Errno.ELOOP.getNativeErrnoValue();
    /** File name too long */
    public static final int ENAMETOOLONG = Errno.ENAMETOOLONG.getNativeErrnoValue();

    /* should be rearranged */
    /** Host is down */
    public static final int EHOSTDOWN = Errno.EHOSTDOWN.getNativeErrnoValue();
    /** No route to host */
    public static final int EHOSTUNREACH = Errno.EHOSTUNREACH.getNativeErrnoValue();
    /** Directory not empty */
    public static final int ENOTEMPTY = Errno.ENOTEMPTY.getNativeErrnoValue();

    /* quotas & mush */
    /** Too many processes */
    //public static final int EPROCLIM = Errno.EPROCLIM.getNativeErrnoValue();
    /** Too many users */
    public static final int EUSERS = Errno.EUSERS.getNativeErrnoValue();
    /** Disc quota exceeded */
    public static final int EDQUOT = Errno.EDQUOT.getNativeErrnoValue();

    /* Network File System */
    /** Stale NFS file handle */
    public static final int ESTALE = Errno.ESTALE.getNativeErrnoValue();
    /** Too many levels of remote in path */
    public static final int EREMOTE = Errno.EREMOTE.getNativeErrnoValue();
    /** RPC struct is bad */
    //public static final int EBADRPC = Errno.EBADRPC.getNativeErrnoValue();
    /** RPC version wrong */
    //public static final int ERPCMISMATCH = Errno.ERPCMISMATCH.getNativeErrnoValue();
    /** RPC prog. not avail */
    //public static final int EPROGUNAVAIL = Errno.EPROGUNAVAIL.getNativeErrnoValue();
    /** Program version wrong */
    //public static final int EPROGMISMATCH = Errno.EPROGMISMATCH.getNativeErrnoValue();
    /** Bad procedure for program */
    //public static final int EPROCUNAVAIL = Errno.EPROCUNAVAIL.getNativeErrnoValue();
    
    /** No locks available */
    public static final int ENOLCK = Errno.ENOLCK.getNativeErrnoValue();
    /** Function not implemented */
    public static final int ENOSYS = Errno.ENOSYS.getNativeErrnoValue();

    /** Inappropriate file type or format */
    //public static final int EFTYPE = Errno.EFTYPE.getNativeErrnoValue();
    /** Authentication error */
    //public static final int EAUTH = Errno.EAUTH.getNativeErrnoValue();
    /** Need authenticator */
    //public static final int ENEEDAUTH = Errno.ENEEDAUTH.getNativeErrnoValue();

/* Intelligent device errors */
    /** Device power is off */
    //public static final int EPWROFF = Errno.EPWROFF.getNativeErrnoValue();
    /** Device error, e.g. paper out */
    //public static final int EDEVERR = Errno.EDEVERR.getNativeErrnoValue();

    /** Value too large to be stored in data type */
    public static final int EOVERFLOW = Errno.EOVERFLOW.getNativeErrnoValue();

/* Program loading errors */

    /** Bad executable */
    //public static final int EBADEXEC = Errno.EBADEXEC.getNativeErrnoValue();
    /** Bad CPU type in executable */
    //public static final int EBADARCH = Errno.EBADARCH.getNativeErrnoValue();
    /** Shared library version mismatch */
    //public static final int ESHLIBVERS = Errno.ESHLIBVERS.getNativeErrnoValue();
    /** Malformed Macho file */
    //public static final int EBADMACHO = Errno.EBADMACHO.getNativeErrnoValue();
    /** Operation canceled */
    public static final int ECANCELED = Errno.ECANCELED.getNativeErrnoValue();
    /** Identifier removed */
    public static final int EIDRM = Errno.EIDRM.getNativeErrnoValue();
    /** No message of desired type */
    public static final int ENOMSG = Errno.ENOMSG.getNativeErrnoValue();
    /** Illegal byte sequence */
    public static final int EILSEQ = Errno.EILSEQ.getNativeErrnoValue();
    /** Attribute not found */
    //public static final int ENOATTR = Errno.ENOATTR.getNativeErrnoValue();
    /** Bad message */
    public static final int EBADMSG = Errno.EBADMSG.getNativeErrnoValue();
    /** Reserved */
    public static final int EMULTIHOP = Errno.EMULTIHOP.getNativeErrnoValue();
    /** No message available on STREAM */
    public static final int ENODATA = Errno.ENODATA.getNativeErrnoValue();
    /** Reserved */
    public static final int ENOLINK = Errno.ENOLINK.getNativeErrnoValue();
    /** No STREAM resources */
    public static final int ENOSR = Errno.ENOSR.getNativeErrnoValue();
    /** Not a STREAM */
    public static final int ENOSTR = Errno.ENOSTR.getNativeErrnoValue();
    /** Protocol error */
    public static final int EPROTO = Errno.EPROTO.getNativeErrnoValue();
    /** STREAM ioctl timeout */
    public static final int ETIME = Errno.ETIME.getNativeErrnoValue();
    /** Must be equal largest errno */
    public static final int ELAST = Errno.ELAST.getNativeErrnoValue();
     /** Must be equal largest errno */
    //public static final int ELAST = Errno.ELAST.getNativeErrnoValue();
}
