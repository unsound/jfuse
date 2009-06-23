/* 
 * File:   JavaSignatures.h
 * Author: erik
 *
 * Created on den 13 juni 2009, 15:53
 */

#ifndef _JAVASIGNATURES_H
#define	_JAVASIGNATURES_H

#define JFUSE_PACKAGE               "org/catacombae/jfuse"

#define JFUSE_CLASS(a)              "L" JFUSE_PACKAGE "/" #a ";"

#define OPS_GETATTR_NAME            "getattr"
#define OPS_GETATTR_SIGNATURE       "([B" JFUSE_CLASS(Stat) ")I"
#define OPS_READLINK_NAME           "readlink"
#define OPS_READLINK_SIGNATURE      "([B[B)I"
#define OPS_GETDIR_NAME             "getdir"
#define OPS_GETDIR_SIGNATURE        "([B" JFUSE_CLASS(FUSEDirFil) ")I"
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
#define OPS_UTIME_SIGNATURE         "([B" JFUSE_CLASS(Utimbuf) ")I"
#define OPS_OPEN_NAME               "open"
#define OPS_OPEN_SIGNATURE          "([B" JFUSE_CLASS(FUSEFileInfo) ")I"
#define OPS_READ_NAME               "read"
#define OPS_READ_SIGNATURE          "([B[BIJ" JFUSE_CLASS(FUSEFileInfo) ")I"
#define OPS_WRITE_NAME              "write"
#define OPS_WRITE_SIGNATURE         "([B[BJJ" JFUSE_CLASS(FUSEFileInfo) ")I"
#define OPS_STATFS_NAME             "statfs"
#define OPS_STATFS_SIGNATURE        "([B" JFUSE_CLASS(StatVFS) ")I"
#define OPS_FLUSH_NAME              "flush"
#define OPS_FLUSH_SIGNATURE         "([B" JFUSE_CLASS(FUSEFileInfo) ")I"
#define OPS_RELEASE_NAME            "release"
#define OPS_RELEASE_SIGNATURE       "([B" JFUSE_CLASS(FUSEFileInfo) ")I"
#define OPS_FSYNC_NAME              "fsync"
#define OPS_FSYNC_SIGNATURE         "([BZ" JFUSE_CLASS(FUSEFileInfo) ")I"
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
#define OPS_OPENDIR_SIGNATURE       "([B" JFUSE_CLASS(FUSEFileInfo) ")I"
#define OPS_READDIR_NAME            "readdir"
#define OPS_READDIR_SIGNATURE       "([B" JFUSE_CLASS(FUSEFillDir) "J" JFUSE_CLASS(FUSEFileInfo) ")I"
#define OPS_RELEASEDIR_NAME         "releasedir"
#define OPS_RELEASEDIR_SIGNATURE    "([B" JFUSE_CLASS(FUSEFileInfo) ")I"
#define OPS_FSYNCDIR_NAME           "fsyncdir"
#define OPS_FSYNCDIR_SIGNATURE      "([BZ" JFUSE_CLASS(FUSEFileInfo) ")I"
#define OPS_INIT_NAME               "init"
#define OPS_INIT_SIGNATURE          "(" JFUSE_CLASS(FUSEConnInfo) ")Ljava/lang/Object;"
#define OPS_DESTROY_NAME            "destroy"
#define OPS_DESTROY_SIGNATURE       "(Ljava/lang/Object;)V"
#define OPS_ACCESS_NAME             "access"
#define OPS_ACCESS_SIGNATURE        "([BI)I"
#define OPS_CREATE_NAME             "create"
#define OPS_CREATE_SIGNATURE        "([BS" JFUSE_CLASS(FUSEFileInfo) ")I"
#define OPS_FTRUNCATE_NAME          "ftruncate"
#define OPS_FTRUNCATE_SIGNATURE     "([BJ" JFUSE_CLASS(FUSEFileInfo) ")I"
#define OPS_FGETATTR_NAME           "fgetattr"
#define OPS_FGETATTR_SIGNATURE      "([B" JFUSE_CLASS(Stat) JFUSE_CLASS(FUSEFileInfo) ")I"
#define OPS_LOCK_NAME               "lock"
#define OPS_LOCK_SIGNATURE          "([B" JFUSE_CLASS(FUSEFileInfo) "I" JFUSE_CLASS(Flock) ")I"
#define OPS_UTIMENS_NAME            "utimens"
#define OPS_UTIMENS_SIGNATURE       "([B" JFUSE_CLASS(Timespec) JFUSE_CLASS(Timespec) ")I"
#define OPS_BMAP_NAME               "bmap"
#define OPS_BMAP_SIGNATURE          "([BJ" JFUSE_CLASS(LongRef) ")I"

/*
#define OPS__NAME                   ""
#define OPS__SIGNATURE              "([B)I"
*/

#define STAT_CLASS                  JFUSE_PACKAGE "/Stat"
#define STAT_INIT_NAME              "<init>"
#define STAT_INIT_SIGNATURE         "()V"

#define FUSEFILLDIR_CLASS           JFUSE_PACKAGE "/FUSEFillDir"
#define FUSEFILLDIR_INIT_NAME       "<init>"
#define FUSEFILLDIR_INIT_SIGNATURE  "([B)V"


#define FUSEDIRFIL_CLASS            JFUSE_PACKAGE "/FUSEDirFil"
#define FUSEDIRFIL_INIT_NAME        "<init>"
#define FUSEDIRFIL_INIT_SIGNATURE   "([B)V"

#define FUSEFILEINFO_CLASS          JFUSE_PACKAGE "/FUSEFileInfo"
#define FUSEFILEINFO_INIT_NAME      "<init>"
#define FUSEFILEINFO_INIT_SIGNATURE "()V"

#define FLOCK_CLASS                 JFUSE_PACKAGE "/Flock"
#define FLOCK_INIT_NAME              "<init>"
#define FLOCK_INIT_SIGNATURE        "()V"

#define TIMESPEC_CLASS              JFUSE_PACKAGE "/Timespec"
#define TIMESPEC_INIT_NAME          "<init>"
#define TIMESPEC_INIT_SIGNATURE     "()V"

#define LONGREF_CLASS               JFUSE_PACKAGE "/LongRef"
#define LONGREF_INIT_NAME           "<init>"
#define LONGREF_INIT_SIGNATURE      "()V"

#define FUSECONNINFO_CLASS          JFUSE_PACKAGE "/FUSEConnInfo"
#define FUSECONNINFO_INIT_NAME      "<init>"
#define FUSECONNINFO_INIT_SIGNATURE "()V"

#define UTIMBUF_CLASS               JFUSE_PACKAGE "/Utimbuf"
#define UTIMBUF_INIT_NAME           "<init>"
#define UTIMBUF_INIT_SIGNATURE      "()V"

#define STATVFS_CLASS               JFUSE_PACKAGE "/StatVFS"
#define STATVFS_INIT_NAME           "<init>"
#define STATVFS_INIT_SIGNATURE      "()V"

#endif	/* _JAVASIGNATURES_H */

