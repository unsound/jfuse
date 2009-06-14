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
#define OPS_READ_SIGNATURE      "([B[BII" JFUSE_CLASS(FUSEFileInfo) ")I" // (byte[], byte[], int, int, FUSEFileInfo)->int
#define OPS_READDIR_NAME        "readdir"
#define OPS_READDIR_SIGNATURE   "([B" JFUSE_CLASS(FUSEFillDir) "J" JFUSE_CLASS(FUSEFileInfo) ")I" // (byte[], FUSEFillDir, long, FUSEFileInfo)->int

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

#define STAT_CLASS              JFUSE_PACKAGE "/Stat"
#define STAT_INIT_NAME          "<init>"
#define STAT_INIT_SIGNATURE     "()V"

#define FUSEFILLDIR_CLASS           JFUSE_PACKAGE "/FUSEFillDir"
#define FUSEFILLDIR_INIT_NAME       "<init>"
#define FUSEFILLDIR_INIT_SIGNATURE  "([B)V"

#define FUSEFILEINFO_CLASS          JFUSE_PACKAGE "/FUSEFileInfo"
#define FUSEFILEINFO_INIT_NAME      "<init>"
#define FUSEFILEINFO_INIT_SIGNATURE "()V"

#endif	/* _JAVASIGNATURES_H */

