/*-
 * TestFS - A testing file system for jFUSE.
 * Copyright (C) 2008-2009  Erik Larsson <erik82@kth.se>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

package org.catacombae.jfuse.test;

import java.nio.ByteBuffer;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.Hashtable;
import java.util.TreeSet;
import org.catacombae.jfuse.FUSE;
import org.catacombae.jfuse.types.fuse26.FUSEConnInfo;
import org.catacombae.jfuse.types.fuse26.FUSEFileInfo;
import org.catacombae.jfuse.FUSEFileSystemAdapter;
import org.catacombae.jfuse.types.fuse26.FUSEFillDir;
import org.catacombae.jfuse.util.FUSEUtil;
import org.catacombae.jfuse.types.fuse26.FUSEContext;
import org.catacombae.jfuse.types.system.Stat;
import org.catacombae.jfuse.util.Log;

/**
 * In-memory file system for testing jFUSE.<br>
 * This file system will be used for testing jFUSE. All or most of the
 * FUSEOperations will be implemented in this file system eventually.
 * (Current status is work-in-progress.)
 *
 * @author Erik Larsson
 */
public class TestFS extends FUSEFileSystemAdapter {

    private static final String CLASS_NAME = "TestFS";

    private final int blockSize = 65535;
    private final byte[] zeroBlock;

    /**
     * A filesystem entry.
     */
    private static class Entry {

        public String name;
        public Inode node;
    }

    private static abstract class Inode {

        public long uid;
        public long gid;
        public short mode;
        public int nlink;
    }

    private static class Directory extends Inode {

        public final TreeSet<Entry> children = new TreeSet<Entry>();
    }

    private static class File extends Inode {
        public final ArrayList<byte[]> blocks = new ArrayList<byte[]>();
        public long length;
    }

    private static class Symlink extends Inode {
        public String target;
    }

    private static class Block {
        byte[] data;
        int ptr = 0;
    }

/*    private static class BlockAllocator {
        public Block
    }*/

    private Hashtable<String, Inode> fileTable = new Hashtable<String, Inode>();

    public TestFS() {
        zeroBlock = new byte[blockSize];
        for(int i = 0; i < zeroBlock.length; ++i)
            zeroBlock[i] = 0;
    }

    private Inode resolveSymlink(Symlink l) {
        HashSet<String> visited = new HashSet<String>();

        while(!visited.contains(l.target)) {
            Inode curNode = lookupInode(l.target);
            if(curNode == null)
                break;
            else if(curNode instanceof Symlink)
                l = (Symlink) curNode;
            else
                return curNode;
        }

        return null;
    }

    private int createFile(String path, FUSEFileInfo fi) {
        String parentPath = FUSEUtil.dirname(path);
        String childName = FUSEUtil.basename(path);

        Inode parent = lookupInode(parentPath);
        if(parent instanceof Symlink)
            parent = resolveSymlink((Symlink) parent);

        if(parent == null)
            return -ENOENT; // A component of the path name that must exist does not exist.
        else if(!(parent instanceof Directory)) {
            return -ENOTDIR; // A component of the path prefix is not a directory.
        }
        else {
            Directory parentDir = (Directory) parent;
            File f = new File();
            f.uid = parent.uid;
            f.gid = parent.gid;
            f.mode = (short) (Stat.S_IFREG |
                    ((Stat.S_IRWXU | Stat.S_IRWXG | Stat.S_IRWXO) &
                    parent.mode));
            f.blocks.clear();
            f.blocks.add(new byte[blockSize]);
            f.length = 0;
            f.nlink = 1;

            Entry entry = new Entry();
            entry.name = childName;
            entry.node = f;

            parentDir.children.add(entry);
            fileTable.put(path, f);
            return 0;
        }
    }

    private Inode lookupInode(String path) {
        return fileTable.get(path);
    }

    @Override
    public Object init(FUSEConnInfo conn) {
        final String METHOD_NAME = "init";
        Log.traceEnter(CLASS_NAME + "." + METHOD_NAME, conn);

        Log.trace("conn.proto_major = " + conn.proto_major);
        Log.trace("conn.proto_minor = " + conn.proto_minor);
        Log.trace("conn.async_read = " + conn.async_read);
        Log.trace("conn.max_readahead = " + conn.max_readahead);
        Log.trace("conn.max_write = " + conn.max_write);

        Log.debug("process pid=" + FUSEUtil.getProcessPid());
        //FUSEContext ctx = FUSE.getContext();

        Directory rootNode = new Directory();
        rootNode.uid = FUSEUtil.getProcessUid();
        Log.debug("root directory uid set to: " + rootNode.uid +
                " (0x" + Long.toHexString(rootNode.uid) + ")");
        rootNode.gid = FUSEUtil.getProcessGid();
        Log.debug("root directory gid set to: " + rootNode.gid +
                " (0x" + Long.toHexString(rootNode.gid) + ")");
        rootNode.nlink = 2;
        rootNode.mode = (short)(S_IFDIR | 0777);
        fileTable.put("/", rootNode);

        Log.debug("fileTable result for '/': " + lookupInode("/"));

        Object retval = "Laban1235";

        Log.traceLeave(CLASS_NAME + "." + METHOD_NAME, retval, conn);
        return retval;
    }

    @Override
    public void destroy(Object o) {
        final String METHOD_NAME = "destroy";
        Log.traceEnter(CLASS_NAME + "." + METHOD_NAME, o);

        Log.trace("Java method destroy got object: " + o);

        Log.traceLeaveVoid(CLASS_NAME + "." + METHOD_NAME, o);
    }

    @Override
    public int getattr(byte[] path, Stat stbuf) {
        final String METHOD_NAME = "getattr";
        Log.traceEnter(CLASS_NAME + "." + METHOD_NAME, path, stbuf);

        int res = 0;
        String pathString = FUSEUtil.decodeUTF8(path);
        Log.trace("  pathString = \"" + pathString + "\"");
        if(pathString == null) // Invalid UTF-8 sequence.
            res = -ENOENT;
        else {
            Inode e = lookupInode(pathString);
            if(e != null) {
                stbuf.st_uid = e.uid;
                stbuf.st_gid = e.gid;
                stbuf.st_mode = e.mode;
                stbuf.st_nlink = e.nlink;
                if(e instanceof File)
                    stbuf.st_size = ((File) e).length;
                else
                    stbuf.st_size = 0;
            }
            else
                res = -ENOENT;
        }

        Log.traceLeave(CLASS_NAME + "." + METHOD_NAME, res, path, stbuf);
        return res;
    }

    @Override
    public int readdir(byte[] path, FUSEFillDir filler, long offset,
            FUSEFileInfo fi) {
        final String METHOD_NAME = "readdir";
        Log.traceEnter(CLASS_NAME + "." + METHOD_NAME, path, filler, offset,
                fi);

        int res = 0;
        String pathString = FUSEUtil.decodeUTF8(path);
        Log.trace("  pathString = \"" + pathString + "\"");
        if(pathString == null) // Invalid UTF-8 sequence.
            res = -ENOENT;
        else {
            Inode e = lookupInode(pathString);
            if(e != null && e instanceof Directory) {
                Directory dir = (Directory) e;

                filler.fill(FUSEUtil.encodeUTF8("."), null, 0);
                filler.fill(FUSEUtil.encodeUTF8(".."), null, 0);
                for(Entry child : dir.children)
                    filler.fill(FUSEUtil.encodeUTF8(child.name), null, 0);
            }
            else
                res = -ENOENT;
        }

        Log.traceLeave(CLASS_NAME + "." + METHOD_NAME, res, path, filler,
                offset, fi);
        return res;
    }

    @Override
    public int readlink(byte[] path, byte[] buffer) {
        final String METHOD_NAME = "readlink";
        Log.traceEnter(CLASS_NAME + "." + METHOD_NAME, path, buffer);

        int res;
        String pathString = FUSEUtil.decodeUTF8(path);
        Log.trace("  pathString = \"" + pathString + "\"");
        if(pathString == null) // Invalid UTF-8 sequence.
            res = -ENOENT;
        else {
            Inode e = lookupInode(pathString);
            if(e != null) {
                if(e instanceof Symlink) {
                    if(buffer.length > 0) {
                        Symlink link = (Symlink) e;
                        byte[] encodedTarget = FUSEUtil.encodeUTF8(link.target);
                        int copySize = Math.min(buffer.length - 1, encodedTarget.length);
                        System.arraycopy(encodedTarget, 0, buffer, 0, copySize);
                        buffer[copySize] = '\0';
                    }

                    res = 0; // ?
                }
                else
                    res = -EINVAL;
            }
            else
                res = -ENOENT;
        }

        Log.traceLeave(CLASS_NAME + "." + METHOD_NAME, res, path, buffer);
        return res;
    }

    @Override
    public int open(byte[] path, FUSEFileInfo fi) {
        final String METHOD_NAME = "open";
        Log.traceEnter(CLASS_NAME + "." + METHOD_NAME, path, fi);

        int res;
        String pathString = FUSEUtil.decodeUTF8(path);
        Log.trace("  pathString = \"" + pathString + "\"");
        if(pathString == null) // Invalid UTF-8 sequence.
            res = -ENOENT;
        else {

            Inode e = lookupInode(pathString);
            if(e != null) {
                if(e instanceof Directory)
                    res = -EISDIR;
                else {
                    File f = (File) e;

                    if(fi.getFlagCreate() && fi.getFlagExcl())
                        res = -EEXIST;
                    else if(fi.getFlagNofollow() && e instanceof Symlink)
                        res = -ELOOP;
                    else if(fi.getFlagSymlink() && e instanceof Symlink)
                        res = -ENOENT; // Open a symlink? ahem... later?
                    else if(fi.getFlagSharedLock() || fi.getFlagExclusiveLock())
                        res = -EOPNOTSUPP;
                    else {
                        if(fi.getFlagTruncate()) {
                            f.length = 0;
                            f.blocks.clear();
                            f.blocks.add(new byte[blockSize]);
                        }

                        res = 0;
                    }
                }
                /* Do I really need to worry so much about this? Won't FUSE
                 * take care of it for me? */
            }
            else {
                if(!fi.getFlagCreate())
                    res = -ENOENT;
                else
                    res = createFile(pathString, fi);
            }
        }

        Log.traceLeave(CLASS_NAME + "." + METHOD_NAME, res, path, fi);
        return res;
    }

    @Override
    public int read(byte[] path, ByteBuffer buf, long offset, FUSEFileInfo fi) {
        final String METHOD_NAME = "read";
        Log.traceEnter(CLASS_NAME + "." + METHOD_NAME, path, buf, offset, fi);

        final int res;
        String pathString = FUSEUtil.decodeUTF8(path);
        Log.trace("  pathString = \"" + pathString + "\"");
        if(pathString == null) { // Invalid UTF-8 sequence.
            Log.warning("Recieved byte sequence that could not be decoded.");
            res = -ENOENT;
        }
        else if(offset < 0 || offset > Integer.MAX_VALUE) {
            Log.warning("'offset' out of range: " + offset);
            res = -EINVAL;
        }
        else {
            Inode e = lookupInode(pathString);
            if(e == null)
                res = -ENOENT;
            else if(!(e instanceof File))
                res = -EACCES; // ?
            else {
                File f = (File) e;
                long bytesLeftInFile = f.length - offset;
                if(bytesLeftInFile > 0) {
                    int len = (int)Math.min(bytesLeftInFile, buf.remaining());

                    int totalBytesRead = 0;
                    while(totalBytesRead < len) {
                        long curOffset = offset+totalBytesRead;
                        int currentBlock = (int) (curOffset / blockSize);
                        int offsetInBlock = (int) (curOffset - (currentBlock * blockSize));
                        int bytesToRead = Math.min(len - totalBytesRead,
                                blockSize - offsetInBlock);

                        byte[] block = f.blocks.get(currentBlock);
                        if(block != null)
                            buf.put(block, offsetInBlock, bytesToRead);
                        else
                            buf.put(zeroBlock, offsetInBlock, bytesToRead);

                        totalBytesRead += bytesToRead;
                        ++currentBlock;
                    }
                    
                    if(totalBytesRead != len)
                        throw new RuntimeException("totalBytesRead != len (" +
                                totalBytesRead + " != " + len);

                    res = len;
                }
                else
                    res = 0;
            }
        }

        Log.traceLeave(CLASS_NAME + "." + METHOD_NAME, res, path, buf, offset,
                fi);
        return res;
    }

    @Override
    public int write(byte[] path, ByteBuffer buf, long offset, FUSEFileInfo fi) {
        final String METHOD_NAME = "write";
        Log.traceEnter(CLASS_NAME + "." + METHOD_NAME, path, buf, offset, fi);

        final int res;
        String pathString = FUSEUtil.decodeUTF8(path);
        Log.trace("  pathString = \"" + pathString + "\"");
        if(pathString == null) { // Invalid UTF-8 sequence.
            Log.warning("Recieved byte sequence that could not be decoded.");
            res = -ENOENT;
        }
        else if(offset < 0 || offset > Integer.MAX_VALUE) {
            Log.warning("'offset' out of range: " + offset);
            res = -EINVAL;
        }
        else {
            Inode e = lookupInode(pathString);
            if(e == null)
                res = -ENOENT;
            else if(!(e instanceof File))
                res = -EACCES; // ?
            else {
                File f = (File) e;
                long bytesLeftInFile = f.length - offset;
                if(bytesLeftInFile > 0) {
                    int len = buf.remaining();

                    int totalBytesWritten = 0;
                    while(totalBytesWritten < len) {
                        long curOffset = offset+totalBytesWritten;
                        int currentBlock = (int) (curOffset / blockSize);
                        int offsetInBlock = (int) (curOffset - (currentBlock * blockSize));
                        int bytesToWrite = Math.min(len - totalBytesWritten,
                                blockSize - offsetInBlock);
                        Log.debug("write: copying " + bytesToWrite + " bytes " +
                                "to block " + currentBlock + " starting at" +
                                offsetInBlock);

                        while(f.blocks.size() < currentBlock)
                            f.blocks.add(null);

                        byte[] curBlock = f.blocks.get(currentBlock);

                        if(curBlock == null) {
                            curBlock = new byte[blockSize];
                            f.blocks.set(currentBlock, curBlock);
                        }

                        buf.get(curBlock, offsetInBlock,
                                bytesToWrite);

                        if(f.length < curOffset+bytesToWrite)
                            f.length = curOffset+bytesToWrite;

                        totalBytesWritten += bytesToWrite;
                        ++currentBlock;
                    }

                    if(totalBytesWritten != len)
                        throw new RuntimeException("totalBytesWritten != len (" +
                                totalBytesWritten + " != " + len);

                    res = len;
                }
                else
                    res = 0;
            }
        }

        Log.traceLeave(CLASS_NAME + "." + METHOD_NAME, res, path, buf, offset,
                fi);
        return res;
    }

    public static void main(String[] args) {
        System.err.print(CLASS_NAME + ".main(");
        for(String s : args)
            System.err.print("\"" + s + "\" ");
        System.err.println("\b)");
        FUSE.main(args, new TestFS());
    }
}
