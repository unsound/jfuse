/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package org.catacombae.jfuse.examples;

import org.catacombae.jfuse.FUSE;
import org.catacombae.jfuse.FUSEConnInfo;
import org.catacombae.jfuse.FUSEFileInfo;
import org.catacombae.jfuse.FUSEFileSystemAdapter;
import org.catacombae.jfuse.FUSEFillDir;
import org.catacombae.jfuse.FUSEUtil;
import org.catacombae.jfuse.Stat;
import org.catacombae.jfuse.util.Log;

/**
 *
 * @author erik
 */
public class HelloFS extends FUSEFileSystemAdapter {
    private final byte[] hello_str;
    private final String hello_path = "/hello";

    public HelloFS() {
        String hello = "Hello!\n";
        this.hello_str = FUSEUtil.encodeUTF8(hello);
        if(hello_str == null)
            throw new RuntimeException("Couldn't UTF-8 encode the following string: " + hello_str);
    }

    @Override
    public Object init(FUSEConnInfo conn) {
        Log.traceEnter("HelloFS.init", conn);

        Log.trace("conn.proto_major = " + conn.proto_major);
        Log.trace("conn.proto_minor = " + conn.proto_minor);
        Log.trace("conn.async_read = " + conn.async_read);
        Log.trace("conn.max_readahead = " + conn.max_readahead);
        Log.trace("conn.max_write = " + conn.max_write);
        Object retval = "Laban1235";

        Log.traceLeave("HelloFS.init", retval, conn);
        return retval;
    }

    @Override
    public void destroy(Object o) {
        Log.traceEnter("HelloFS.destroy", o);

        Log.trace("Java method destroy got object: " + o);

        Log.traceLeaveVoid("HelloFS.destroy", o);
    }

    @Override
    public int getattr(byte[] path, Stat stbuf) {
        Log.traceEnter("HelloFS.gettattr", path, stbuf);

        int res = 0;
        String pathString = FUSEUtil.decodeUTF8(path);
        Log.trace("  pathString = \"" + pathString + "\"");
        if(pathString == null) // Invalid UTF-8 sequence.
            res = -ENOENT;
        else {
            stbuf.zero();
            if(pathString.equals("/")) {
                stbuf.st_mode = Stat.S_IFDIR | 0755;
                stbuf.st_nlink = 2;
            }
            else if(pathString.equals(hello_path)) {
                stbuf.st_mode = Stat.S_IFREG | 0444;
                stbuf.st_nlink = 1;
                stbuf.st_size = hello_str.length;
            }
            else
                res = -ENOENT;
        }

        Log.traceLeave("HelloFS.gettattr", res, path, stbuf);
        return res;
    }

    @Override
    public int readdir(byte[] path, FUSEFillDir filler, long offset, FUSEFileInfo fi) {
        Log.traceEnter("HelloFS.readdir", path, filler, offset, fi);

        int res = 0;
        String pathString = FUSEUtil.decodeUTF8(path);
        Log.trace("  pathString = \"" + pathString + "\"");
        if(pathString == null) // Invalid UTF-8 sequence.
            res = -ENOENT;
        else if(!pathString.equals("/"))
            res = -ENOENT;
        else {
            filler.fill(FUSEUtil.encodeUTF8("."), null, 0);
            filler.fill(FUSEUtil.encodeUTF8(".."), null, 0);
            filler.fill(FUSEUtil.encodeUTF8(hello_path.substring(1)), null, 0);
        }

        Log.traceLeave("HelloFS.readdir", res, path, filler, offset, fi);
        return res;
    }

    @Override
    public int open(byte[] path, FUSEFileInfo fi) {
        Log.traceEnter("HelloFS.open", path, fi);

        int res = 0;
        String pathString = FUSEUtil.decodeUTF8(path);
        Log.trace("  pathString = \"" + pathString + "\"");
        if(pathString == null) // Invalid UTF-8 sequence.
            return -ENOENT;

        if(!pathString.equals(hello_path))
            return -ENOENT;

        if((fi.flags & 3) != FUSEFileInfo.O_RDONLY)
            return -EACCES;

        Log.traceLeave("HelloFS.open", res, path, fi);
        return 0;
    }

    @Override
    public int read(byte[] path, byte[] buf, int size, long offset, FUSEFileInfo fi) {
        Log.traceEnter("int HelloFS.read", path, buf, size, offset, fi);

        int res = 0;
        String pathString = FUSEUtil.decodeUTF8(path);
        Log.trace("  pathString = \"" + pathString + "\"");
        if(pathString == null) {// Invalid UTF-8 sequence.
            Log.warning("Recieved byte sequence that could not be decoded.");
            res = -ENOENT;
        }
        else if(offset < 0 || offset > Integer.MAX_VALUE) {
            Log.warning("'offset' out of range.");
            res = -EINVAL;
        }
        else if(!pathString.equals(hello_path))
            res = -ENOENT;
        else {
            int bytesLeftInFile = hello_str.length - (int)(offset);
            if(bytesLeftInFile > 0) {
                res = Math.min(bytesLeftInFile, size);
                System.arraycopy(hello_str, (int)offset, buf, 0, res);
            }
            else
                res = 0;
        }

        Log.traceLeave("int HelloFS.read", res, path, buf, size, offset, fi);
        return res;
    }

    public static void main(String[] args) {
        System.err.print("HelloFS.main(");
        for(String s : args)
            System.err.print("\"" + s + "\" ");
        System.err.println("\b)");
        FUSE.main(args, new HelloFS());
    }
}
