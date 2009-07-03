/*-
 * jFUSE - FUSE bindings for Java
 * Copyright (C) 2008-2009  Erik Larsson <erik82@kth.se>
 *
 * Derived from:
 *   FUSE: Filesystem in Userspace
 *   Copyright (C) 2001-2007  Miklos Szeredi <miklos@szeredi.hu>
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

// Class / method signatures for certain classes

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

#define JAVA_CLASS(a)               "L" a ";"
#define JFUSE_CLASS(a)              "L" JFUSE_PACKAGE "/" #a ";"

#define OPS_GETATTR_NAME            "getattr"
#define OPS_GETATTR_SIGNATURE       "([B" JAVA_CLASS(STAT_CLASS) ")I"
#define OPS_READLINK_NAME           "readlink"
#define OPS_READLINK_SIGNATURE      "([B[B)I"
#define OPS_GETDIR_NAME             "getdir"
#define OPS_GETDIR_SIGNATURE        "([B" JAVA_CLASS(FUSEDIRFIL_CLASS) ")I"
#define OPS_MKNOD_NAME              "mknod"
#define OPS_MKNOD_SIGNATURE         "([BSJ)I"
#define OPS_MKDIR_NAME              "mkdir"
#define OPS_MKDIR_SIGNATURE         "([BS)I"
#define OPS_UNLINK_NAME             "unlink"
#define OPS_UNLINK_SIGNATURE        "([B)I"
#define OPS_RMDIR_NAME              "rmdir"
#define OPS_RMDIR_SIGNATURE         "([B)I"
#define OPS_SYMLINK_NAME            "symlink"
#define OPS_SYMLINK_SIGNATURE       "([B[B)I"
#define OPS_RENAME_NAME             "rename"
#define OPS_RENAME_SIGNATURE        "([B[B)I"
#define OPS_LINK_NAME               "link"
#define OPS_LINK_SIGNATURE          "([B[B)I"
#define OPS_CHMOD_NAME              "chmod"
#define OPS_CHMOD_SIGNATURE         "([BS)I"
#define OPS_CHOWN_NAME              "chown"
#define OPS_CHOWN_SIGNATURE         "([BJJ)I"
#define OPS_TRUNCATE_NAME           "truncate"
#define OPS_TRUNCATE_SIGNATURE      "([BJ)I"
#define OPS_UTIME_NAME              "utime"
#define OPS_UTIME_SIGNATURE         "([B" JAVA_CLASS(UTIMBUF_CLASS) ")I"
#define OPS_OPEN_NAME               "open"
#define OPS_OPEN_SIGNATURE          "([B" JAVA_CLASS(FUSEFILEINFO_CLASS) ")I"
#define OPS_READ_NAME               "read"
#define OPS_READ_SIGNATURE          "([B" JAVA_CLASS("java/nio/ByteBuffer") "J" JAVA_CLASS(FUSEFILEINFO_CLASS) ")I"
#define OPS_WRITE_NAME              "write"
#define OPS_WRITE_SIGNATURE         "([B" JAVA_CLASS("java/nio/ByteBuffer") "J" JAVA_CLASS(FUSEFILEINFO_CLASS) ")I"
#define OPS_STATFS_NAME             "statfs"
#define OPS_STATFS_SIGNATURE        "([B" JAVA_CLASS(STATVFS_CLASS) ")I"
#define OPS_FLUSH_NAME              "flush"
#define OPS_FLUSH_SIGNATURE         "([B" JAVA_CLASS(FUSEFILEINFO_CLASS) ")I"
#define OPS_RELEASE_NAME            "release"
#define OPS_RELEASE_SIGNATURE       "([B" JAVA_CLASS(FUSEFILEINFO_CLASS) ")I"
#define OPS_FSYNC_NAME              "fsync"
#define OPS_FSYNC_SIGNATURE         "([BZ" JAVA_CLASS(FUSEFILEINFO_CLASS) ")I"
#define OPS_SETXATTR_BSD_NAME       "setxattr_BSD"
#define OPS_SETXATTR_BSD_SIGNATURE  "([B[B[BII)I"
#define OPS_SETXATTR_NAME           "setxattr"
#define OPS_SETXATTR_SIGNATURE      "([B[B[BI)I"
#define OPS_GETXATTR_BSD_NAME       "getxattr_BSD"
#define OPS_GETXATTR_BSD_SIGNATURE  "([B[B[BI)I"
#define OPS_GETXATTR_NAME           "getxattr"
#define OPS_GETXATTR_SIGNATURE      "([B[B[B)I"
#define OPS_LISTXATTR_NAME          "listxattr"
#define OPS_LISTXATTR_SIGNATURE     "([B[B)I"
#define OPS_REMOVEXATTR_NAME        "removexattr"
#define OPS_REMOVEXATTR_SIGNATURE   "([B[B)I"
#define OPS_OPENDIR_NAME            "opendir"
#define OPS_OPENDIR_SIGNATURE       "([B" JAVA_CLASS(FUSEFILEINFO_CLASS) ")I"
#define OPS_READDIR_NAME            "readdir"
#define OPS_READDIR_SIGNATURE       "([B" JAVA_CLASS(FUSEFILLDIR_CLASS) "J" JAVA_CLASS(FUSEFILEINFO_CLASS) ")I"
#define OPS_RELEASEDIR_NAME         "releasedir"
#define OPS_RELEASEDIR_SIGNATURE    "([B" JAVA_CLASS(FUSEFILEINFO_CLASS) ")I"
#define OPS_FSYNCDIR_NAME           "fsyncdir"
#define OPS_FSYNCDIR_SIGNATURE      "([BZ" JAVA_CLASS(FUSEFILEINFO_CLASS) ")I"
#define OPS_INIT_NAME               "init"
#define OPS_INIT_SIGNATURE          "(" JAVA_CLASS(FUSECONNINFO_CLASS) ")" JAVA_CLASS("java/lang/Object")
#define OPS_DESTROY_NAME            "destroy"
#define OPS_DESTROY_SIGNATURE       "(" JAVA_CLASS("java/lang/Object") ")V"
#define OPS_ACCESS_NAME             "access"
#define OPS_ACCESS_SIGNATURE        "([BI)I"
#define OPS_CREATE_NAME             "create"
#define OPS_CREATE_SIGNATURE        "([BS" JAVA_CLASS(FUSEFILEINFO_CLASS) ")I"
#define OPS_FTRUNCATE_NAME          "ftruncate"
#define OPS_FTRUNCATE_SIGNATURE     "([BJ" JAVA_CLASS(FUSEFILEINFO_CLASS) ")I"
#define OPS_FGETATTR_NAME           "fgetattr"
#define OPS_FGETATTR_SIGNATURE      "([B" JAVA_CLASS(STAT_CLASS) JAVA_CLASS(FUSEFILEINFO_CLASS) ")I"
#define OPS_LOCK_NAME               "lock"
#define OPS_LOCK_SIGNATURE          "([B" JAVA_CLASS(FUSEFILEINFO_CLASS) "I" JAVA_CLASS(FLOCK_CLASS) ")I"
#define OPS_UTIMENS_NAME            "utimens"
#define OPS_UTIMENS_SIGNATURE       "([B" JAVA_CLASS(TIMESPEC_CLASS) JAVA_CLASS(TIMESPEC_CLASS) ")I"
#define OPS_BMAP_NAME               "bmap"
#define OPS_BMAP_SIGNATURE          "([BJ" JAVA_CLASS(LONGREF_CLASS) ")I"

/*
#define OPS__NAME                   ""
#define OPS__SIGNATURE              "([B)I"
*/

#endif	/* _JAVASIGNATURES_H */

