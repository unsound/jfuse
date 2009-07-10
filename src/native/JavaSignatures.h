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

#ifndef _JAVASIGNATURES_H
#define	_JAVASIGNATURES_H

#define JFUSE_PACKAGE               "org/catacombae/jfuse"

#define JAVA_CLASS(a)               "L" a ";"
#define JFUSE_CLASS(a)              "L" JFUSE_PACKAGE "/" #a ";"

// Class signatures for certain built in Java classes

#define OBJECT_CLASS                "java/lang/Object"
#define BYTEBUFFER_CLASS            "java/nio/ByteBuffer"

// Class / method signatures for certain classes

#define FUSECONTEXT_CLASS           JFUSE_PACKAGE "/types/fuse26/FUSEContext"
#define FUSECONTEXT_INIT_NAME       "<init>"
#define FUSECONTEXT_INIT_SIGNATURE  "(JJJ" JAVA_CLASS(OBJECT_CLASS) ")V"

#define FUSECONNINFO_CLASS          JFUSE_PACKAGE "/types/fuse26/FUSEConnInfo"
#define FUSECONNINFO_INIT_NAME      "<init>"
#define FUSECONNINFO_INIT_SIGNATURE "()V"

#define FUSEDIRFIL_CLASS            JFUSE_PACKAGE "/types/fuse26/FUSEDirFil"
#define FUSEDIRFIL_INIT_NAME        "<init>"
#define FUSEDIRFIL_INIT_SIGNATURE   "([B)V"

#define FUSEFILEINFO_CLASS          JFUSE_PACKAGE "/types/fuse26/FUSEFileInfo"
#define FUSEFILEINFO_INIT_NAME      "<init>"
#define FUSEFILEINFO_INIT_SIGNATURE "()V"

#define FUSEFILLDIR_CLASS           JFUSE_PACKAGE "/types/fuse26/FUSEFillDir"
#define FUSEFILLDIR_INIT_NAME       "<init>"
#define FUSEFILLDIR_INIT_SIGNATURE  "([B)V"

#define FLOCK_CLASS                 JFUSE_PACKAGE "/types/system/Flock"
#define FLOCK_INIT_NAME              "<init>"
#define FLOCK_INIT_SIGNATURE        "()V"

#define LONGREF_CLASS               JFUSE_PACKAGE "/types/system/LongRef"
#define LONGREF_INIT_NAME           "<init>"
#define LONGREF_INIT_SIGNATURE      "()V"

#define STAT_CLASS                  JFUSE_PACKAGE "/types/system/Stat"
#define STAT_INIT_NAME              "<init>"
#define STAT_INIT_SIGNATURE         "()V"

#define STATVFS_CLASS               JFUSE_PACKAGE "/types/system/StatVFS"
#define STATVFS_INIT_NAME           "<init>"
#define STATVFS_INIT_SIGNATURE      "()V"

#define TIMESPEC_CLASS              JFUSE_PACKAGE "/types/system/Timespec"
#define TIMESPEC_INIT_NAME          "<init>"
#define TIMESPEC_INIT_SIGNATURE     "()V"

#define UTIMBUF_CLASS               JFUSE_PACKAGE "/types/system/Utimbuf"
#define UTIMBUF_INIT_NAME           "<init>"
#define UTIMBUF_INIT_SIGNATURE      "()V"

// FUSE26Operations signatures

#define OPS_GETATTR_NAME            "getattr"
#define OPS_GETATTR_SIGNATURE       "(" JAVA_CLASS(BYTEBUFFER_CLASS) JAVA_CLASS(STAT_CLASS) ")I"
#define OPS_READLINK_NAME           "readlink"
#define OPS_READLINK_SIGNATURE      "(" JAVA_CLASS(BYTEBUFFER_CLASS) JAVA_CLASS(BYTEBUFFER_CLASS) ")I"
#define OPS_GETDIR_NAME             "getdir"
#define OPS_GETDIR_SIGNATURE        "(" JAVA_CLASS(BYTEBUFFER_CLASS) JAVA_CLASS(FUSEDIRFIL_CLASS) ")I"
#define OPS_MKNOD_NAME              "mknod"
#define OPS_MKNOD_SIGNATURE         "(" JAVA_CLASS(BYTEBUFFER_CLASS) "SJ)I"
#define OPS_MKDIR_NAME              "mkdir"
#define OPS_MKDIR_SIGNATURE         "(" JAVA_CLASS(BYTEBUFFER_CLASS) "S)I"
#define OPS_UNLINK_NAME             "unlink"
#define OPS_UNLINK_SIGNATURE        "(" JAVA_CLASS(BYTEBUFFER_CLASS) ")I"
#define OPS_RMDIR_NAME              "rmdir"
#define OPS_RMDIR_SIGNATURE         "(" JAVA_CLASS(BYTEBUFFER_CLASS) ")I"
#define OPS_SYMLINK_NAME            "symlink"
#define OPS_SYMLINK_SIGNATURE       "(" JAVA_CLASS(BYTEBUFFER_CLASS) JAVA_CLASS(BYTEBUFFER_CLASS) ")I"
#define OPS_RENAME_NAME             "rename"
#define OPS_RENAME_SIGNATURE        "(" JAVA_CLASS(BYTEBUFFER_CLASS) JAVA_CLASS(BYTEBUFFER_CLASS) ")I"
#define OPS_LINK_NAME               "link"
#define OPS_LINK_SIGNATURE          "(" JAVA_CLASS(BYTEBUFFER_CLASS) JAVA_CLASS(BYTEBUFFER_CLASS) ")I"
#define OPS_CHMOD_NAME              "chmod"
#define OPS_CHMOD_SIGNATURE         "(" JAVA_CLASS(BYTEBUFFER_CLASS) "S)I"
#define OPS_CHOWN_NAME              "chown"
#define OPS_CHOWN_SIGNATURE         "(" JAVA_CLASS(BYTEBUFFER_CLASS) "JJ)I"
#define OPS_TRUNCATE_NAME           "truncate"
#define OPS_TRUNCATE_SIGNATURE      "(" JAVA_CLASS(BYTEBUFFER_CLASS) "J)I"
#define OPS_UTIME_NAME              "utime"
#define OPS_UTIME_SIGNATURE         "(" JAVA_CLASS(BYTEBUFFER_CLASS) JAVA_CLASS(UTIMBUF_CLASS) ")I"
#define OPS_OPEN_NAME               "open"
#define OPS_OPEN_SIGNATURE          "(" JAVA_CLASS(BYTEBUFFER_CLASS) JAVA_CLASS(FUSEFILEINFO_CLASS) ")I"
#define OPS_READ_NAME               "read"
#define OPS_READ_SIGNATURE          "(" JAVA_CLASS(BYTEBUFFER_CLASS) JAVA_CLASS(BYTEBUFFER_CLASS) "J" JAVA_CLASS(FUSEFILEINFO_CLASS) ")I"
#define OPS_WRITE_NAME              "write"
#define OPS_WRITE_SIGNATURE         "(" JAVA_CLASS(BYTEBUFFER_CLASS) JAVA_CLASS(BYTEBUFFER_CLASS) "J" JAVA_CLASS(FUSEFILEINFO_CLASS) ")I"
#define OPS_STATFS_NAME             "statfs"
#define OPS_STATFS_SIGNATURE        "(" JAVA_CLASS(BYTEBUFFER_CLASS) JAVA_CLASS(STATVFS_CLASS) ")I"
#define OPS_FLUSH_NAME              "flush"
#define OPS_FLUSH_SIGNATURE         "(" JAVA_CLASS(BYTEBUFFER_CLASS) JAVA_CLASS(FUSEFILEINFO_CLASS) ")I"
#define OPS_RELEASE_NAME            "release"
#define OPS_RELEASE_SIGNATURE       "(" JAVA_CLASS(BYTEBUFFER_CLASS) JAVA_CLASS(FUSEFILEINFO_CLASS) ")I"
#define OPS_FSYNC_NAME              "fsync"
#define OPS_FSYNC_SIGNATURE         "(" JAVA_CLASS(BYTEBUFFER_CLASS) "Z" JAVA_CLASS(FUSEFILEINFO_CLASS) ")I"
#define OPS_SETXATTR_BSD_NAME       "setxattr_BSD"
#define OPS_SETXATTR_BSD_SIGNATURE  "(" JAVA_CLASS(BYTEBUFFER_CLASS) JAVA_CLASS(BYTEBUFFER_CLASS) JAVA_CLASS(BYTEBUFFER_CLASS) "II)I"
#define OPS_SETXATTR_NAME           "setxattr"
#define OPS_SETXATTR_SIGNATURE      "(" JAVA_CLASS(BYTEBUFFER_CLASS) JAVA_CLASS(BYTEBUFFER_CLASS) JAVA_CLASS(BYTEBUFFER_CLASS) "I)I"
#define OPS_GETXATTR_BSD_NAME       "getxattr_BSD"
#define OPS_GETXATTR_BSD_SIGNATURE  "(" JAVA_CLASS(BYTEBUFFER_CLASS) JAVA_CLASS(BYTEBUFFER_CLASS) JAVA_CLASS(BYTEBUFFER_CLASS) "I)I"
#define OPS_GETXATTR_NAME           "getxattr"
#define OPS_GETXATTR_SIGNATURE      "(" JAVA_CLASS(BYTEBUFFER_CLASS) JAVA_CLASS(BYTEBUFFER_CLASS) JAVA_CLASS(BYTEBUFFER_CLASS) ")I"
#define OPS_LISTXATTR_NAME          "listxattr"
#define OPS_LISTXATTR_SIGNATURE     "(" JAVA_CLASS(BYTEBUFFER_CLASS) JAVA_CLASS(BYTEBUFFER_CLASS) ")I"
#define OPS_REMOVEXATTR_NAME        "removexattr"
#define OPS_REMOVEXATTR_SIGNATURE   "(" JAVA_CLASS(BYTEBUFFER_CLASS) JAVA_CLASS(BYTEBUFFER_CLASS) ")I"
#define OPS_OPENDIR_NAME            "opendir"
#define OPS_OPENDIR_SIGNATURE       "(" JAVA_CLASS(BYTEBUFFER_CLASS) JAVA_CLASS(FUSEFILEINFO_CLASS) ")I"
#define OPS_READDIR_NAME            "readdir"
#define OPS_READDIR_SIGNATURE       "(" JAVA_CLASS(BYTEBUFFER_CLASS) JAVA_CLASS(FUSEFILLDIR_CLASS) "J" JAVA_CLASS(FUSEFILEINFO_CLASS) ")I"
#define OPS_RELEASEDIR_NAME         "releasedir"
#define OPS_RELEASEDIR_SIGNATURE    "(" JAVA_CLASS(BYTEBUFFER_CLASS) JAVA_CLASS(FUSEFILEINFO_CLASS) ")I"
#define OPS_FSYNCDIR_NAME           "fsyncdir"
#define OPS_FSYNCDIR_SIGNATURE      "(" JAVA_CLASS(BYTEBUFFER_CLASS) "Z" JAVA_CLASS(FUSEFILEINFO_CLASS) ")I"
#define OPS_INIT_NAME               "init"
#define OPS_INIT_SIGNATURE          "(" JAVA_CLASS(FUSECONNINFO_CLASS) ")" JAVA_CLASS(OBJECT_CLASS)
#define OPS_DESTROY_NAME            "destroy"
#define OPS_DESTROY_SIGNATURE       "(" JAVA_CLASS(OBJECT_CLASS) ")V"
#define OPS_ACCESS_NAME             "access"
#define OPS_ACCESS_SIGNATURE        "(" JAVA_CLASS(BYTEBUFFER_CLASS) "I)I"
#define OPS_CREATE_NAME             "create"
#define OPS_CREATE_SIGNATURE        "(" JAVA_CLASS(BYTEBUFFER_CLASS) "S" JAVA_CLASS(FUSEFILEINFO_CLASS) ")I"
#define OPS_FTRUNCATE_NAME          "ftruncate"
#define OPS_FTRUNCATE_SIGNATURE     "(" JAVA_CLASS(BYTEBUFFER_CLASS) "J" JAVA_CLASS(FUSEFILEINFO_CLASS) ")I"
#define OPS_FGETATTR_NAME           "fgetattr"
#define OPS_FGETATTR_SIGNATURE      "(" JAVA_CLASS(BYTEBUFFER_CLASS) JAVA_CLASS(STAT_CLASS) JAVA_CLASS(FUSEFILEINFO_CLASS) ")I"
#define OPS_LOCK_NAME               "lock"
#define OPS_LOCK_SIGNATURE          "(" JAVA_CLASS(BYTEBUFFER_CLASS) JAVA_CLASS(FUSEFILEINFO_CLASS) "I" JAVA_CLASS(FLOCK_CLASS) ")I"
#define OPS_UTIMENS_NAME            "utimens"
#define OPS_UTIMENS_SIGNATURE       "(" JAVA_CLASS(BYTEBUFFER_CLASS) JAVA_CLASS(TIMESPEC_CLASS) JAVA_CLASS(TIMESPEC_CLASS) ")I"
#define OPS_BMAP_NAME               "bmap"
#define OPS_BMAP_SIGNATURE          "(" JAVA_CLASS(BYTEBUFFER_CLASS) "J" JAVA_CLASS(LONGREF_CLASS) ")I"

// MacFUSE20Operations signatures

#if defined(__APPLE__) || defined(__DARWIN__)
#if (__FreeBSD__ >= 10)

#define SETATTR_X_CLASS             JFUSE_PACKAGE "/types/macfuse20/Setattr_x"
#define SETATTR_X_INIT_NAME         "<init>"
#define SETATTR_X_INIT_SIGNATURE    "()V"

#define OPS_EXCHANGE_NAME           "exchange"
#define OPS_EXCHANGE_SIGNATURE      "(" JAVA_CLASS(BYTEBUFFER_CLASS) JAVA_CLASS(BYTEBUFFER_CLASS) "J)I"

#define OPS_GETXTIMES_NAME          "getxtimes"
#define OPS_GETXTIMES_SIGNATURE     "(" JAVA_CLASS(BYTEBUFFER_CLASS) JAVA_CLASS(TIMESPEC_CLASS) JAVA_CLASS(TIMESPEC_CLASS) ")I"

#define OPS_SETBKUPTIME_NAME        "setbkuptime"
#define OPS_SETBKUPTIME_SIGNATURE   "(" JAVA_CLASS(BYTEBUFFER_CLASS) JAVA_CLASS(TIMESPEC_CLASS) ")I"

#define OPS_SETCRTIME_NAME          "setcrtime"
#define OPS_SETCRTIME_SIGNATURE     "(" JAVA_CLASS(BYTEBUFFER_CLASS) JAVA_CLASS(TIMESPEC_CLASS) ")I"

#define OPS_CHFLAGS_NAME            "chflags"
#define OPS_CHFLAGS_SIGNATURE       "(" JAVA_CLASS(BYTEBUFFER_CLASS) "I)I"

#define OPS_SETATTR_X_NAME          "setattr_x"
#define OPS_SETATTR_X_SIGNATURE     "(" JAVA_CLASS(BYTEBUFFER_CLASS) JAVA_CLASS(SETATTR_X_CLASS) ")I"

#define OPS_FSETATTR_X_NAME         "fsetattr_x"
#define OPS_FSETATTR_X_SIGNATURE    "(" JAVA_CLASS(BYTEBUFFER_CLASS) JAVA_CLASS(SETATTR_X_CLASS) JAVA_CLASS(FUSEFILEINFO_CLASS) ")I"

#endif /* __FreeBSD__ >= 10 */
#endif /* defined(__APPLE__) || defined(__DARWIN__) */


/*
#define OPS__NAME                   ""
#define OPS__SIGNATURE              "(" JAVA_CLASS(BYTEBUFFER_CLASS) ")I"
*/

#endif	/* _JAVASIGNATURES_H */

