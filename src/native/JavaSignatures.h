/* 
 * File:   JavaSignatures.h
 * Author: erik
 *
 * Created on den 13 juni 2009, 15:53
 */

#ifndef _JAVASIGNATURES_H
#define	_JAVASIGNATURES_H

#define JFUSE_PACKAGE           "org/catacombae/jfuse"

#define JFUSE_CLASS(a)          "L" JFUSE_PACKAGE "/" #a ";"

#define OPS_GETATTR_NAME        "getattr"
#define OPS_GETATTR_SIGNATURE   "([B" JFUSE_CLASS(Stat) ")I" // (byte[], Stat)->int
#define OPS_OPEN_NAME           "open"
#define OPS_OPEN_SIGNATURE      "([B" JFUSE_CLASS(FUSEFileInfo) ")I" // (byte[], FUSEFileInfo)->int
#define OPS_READ_NAME           "read"
#define OPS_READ_SIGNATURE      "([B[BIJ" JFUSE_CLASS(FUSEFileInfo) ")I" // (byte[], byte[], int, long, FUSEFileInfo)->int
#define OPS_READDIR_NAME        "readdir"
#define OPS_READDIR_SIGNATURE   "([B" JFUSE_CLASS(FUSEFillDir) "J" JFUSE_CLASS(FUSEFileInfo) ")I" // (byte[], FUSEFillDir, long, FUSEFileInfo)->int
#define OPS_INIT_NAME           "init"
#define OPS_INIT_SIGNATURE      "(" JFUSE_CLASS(FUSEConnInfo) ")Ljava/lang/Object;"
#define OPS_DESTROY_NAME        "destroy"
#define OPS_DESTROY_SIGNATURE   "(Ljava/lang/Object;)V"
#define OPS_ACCESS_NAME         "access"
#define OPS_ACCESS_SIGNATURE    "([BI)I"
#define OPS_CREATE_NAME         "create"
#define OPS_CREATE_SIGNATURE    "([BS" JFUSE_CLASS(FUSEFileInfo) ")I"
#define OPS_FTRUNCATE_NAME      "ftruncate"
#define OPS_FTRUNCATE_SIGNATURE "([BJ" JFUSE_CLASS(FUSEFileInfo) ")I"
#define OPS_FGETATTR_NAME       "fgetattr"
#define OPS_FGETATTR_SIGNATURE  "([B" JFUSE_CLASS(Stat) JFUSE_CLASS(FUSEFileInfo) ")I"
#define OPS_LOCK_NAME           "lock"
#define OPS_LOCK_SIGNATURE      "([B" JFUSE_CLASS(FUSEFileInfo) "I" JFUSE_CLASS(Flock) ")I"
#define OPS_UTIMENS_NAME        "utimens"
#define OPS_UTIMENS_SIGNATURE   "([B" JFUSE_CLASS(Timespec) JFUSE_CLASS(Timespec) ")I"
#define OPS_BMAP_NAME           "bmap"
#define OPS_BMAP_SIGNATURE      "([BJ" JFUSE_CLASS(LongRef) ")I"


/*
#define OPS_READLINK_NAME       "readlink"
#define OPS_READLINK_SIGNATURE  "([BJ)I" // (byte[], long)->int
#define OPS_GETDIR_NAME         "getdir"
#define OPS_GETDIR_SIGNATURE    "([B[B" JFUSE_CLASS(FUSEDirFil) ")I"

#define OPS_ACCESS_NAME         "access"
#define OPS_ACCESS_SIGNATURE    "([BI)I"
#define OPS_BMAP_NAME           "bmap"
#define OPS_BMAP_SIGNATURE      "([BJ" JFUSE_CLASS(LongRef) ")I"
#define OPS_CHMOD_NAME          "chmod"
#define OPS_CHMOD_SIGNATURE     "([BS)I"
*/

#define STAT_CLASS                  JFUSE_PACKAGE "/Stat"
#define STAT_INIT_NAME              "<init>"
#define STAT_INIT_SIGNATURE         "()V"

#define FUSEFILLDIR_CLASS           JFUSE_PACKAGE "/FUSEFillDir"
#define FUSEFILLDIR_INIT_NAME       "<init>"
#define FUSEFILLDIR_INIT_SIGNATURE  "([B)V"

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

#endif	/* _JAVASIGNATURES_H */

