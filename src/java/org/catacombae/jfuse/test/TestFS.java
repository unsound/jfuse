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
import java.util.HashSet;
import java.util.Hashtable;
import java.util.TreeSet;
import org.catacombae.jfuse.FUSE;
import org.catacombae.jfuse.types.fuse26.FUSEConnInfo;
import org.catacombae.jfuse.types.fuse26.FUSEFileInfo;
import org.catacombae.jfuse.FUSEFileSystemAdapter;
import org.catacombae.jfuse.types.fuse26.FUSEFillDir;
import org.catacombae.jfuse.FUSEUtil;
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

        public TreeSet<Entry> children;
    }

    private static class File extends Inode {

        public byte[] data;
    }

    private static class Symlink extends Inode {

        public String target;
    }
    private Hashtable<String, Inode> fileTable = new Hashtable<String, Inode>();

    public TestFS() {
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

    private int createInode(String path, FUSEFileInfo fi) {
        String parentPath = path.substring(0, path.lastIndexOf('/'));
        String childName = path.substring(parentPath.length() + 1);

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
            f.data = new byte[0];
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

        FUSEContext ctx = FUSE.getContext();

        Directory rootNode = new Directory();
        rootNode.uid = ctx.uid;
        rootNode.gid = ctx.gid;
        fileTable.put("/", rootNode);

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
                stbuf.st_mode = e.mode;
                stbuf.st_nlink = e.nlink;
                if(e instanceof File)
                    stbuf.st_size = ((File) e).data.length;
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
                        if(fi.getFlagTruncate())
                            f.data = new byte[0];

                        res = 0;
                    }
                }
                /* Do I really need to worry so much about this? Won't MacFUSE
                 * take care of it for me? */
            }
            else {
                if(!fi.getFlagCreate())
                    res = -ENOENT;
                else
                    res = createInode(pathString, fi);
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
                int bytesLeftInFile = f.data.length - (int) (offset);
                if(bytesLeftInFile > 0) {
                    int len = Math.min(bytesLeftInFile, buf.remaining());
                    buf.put(f.data, (int)offset, len);
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
