/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package org.catacombae.jfuse.examples;

import org.catacombae.jfuse.FUSE;
import org.catacombae.jfuse.FUSEFileInfo;
import org.catacombae.jfuse.FUSEFileSystemAdapter;
import org.catacombae.jfuse.FUSEFillDir;
import org.catacombae.jfuse.FUSEUtil;
import org.catacombae.jfuse.Stat;

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
    public int getattr(byte[] path, Stat stbuf) {
        String pathString = FUSEUtil.decodeUTF8(path);
        if(pathString == null) // Invalid UTF-8 sequence.
            return -ENOENT;

        int res = 0;

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

        return res;
    }

    @Override
    public int readdir(byte[] path, FUSEFillDir filler, long offset, FUSEFileInfo fi) {
        String pathString = FUSEUtil.decodeUTF8(path);
        if(pathString == null) // Invalid UTF-8 sequence.
            return -ENOENT;

        if(!pathString.equals("/"))
            return -ENOENT;

        filler.fill(FUSEUtil.encodeUTF8("."), null, 0);
        filler.fill(FUSEUtil.encodeUTF8(".."), null, 0);
        filler.fill(FUSEUtil.encodeUTF8(hello_path.substring(1)), null, 0);

        return 0;
    }

    @Override
    public int open(byte[] path, FUSEFileInfo fi) {
        String pathString = FUSEUtil.decodeUTF8(path);
        if(pathString == null) // Invalid UTF-8 sequence.
            return -ENOENT;

        if(!pathString.equals(hello_path))
            return -ENOENT;

        if((fi.flags & 3) != FUSEFileInfo.O_RDONLY)
            return -EACCES;

        return 0;
    }

    @Override
    public int read(byte[] path, byte[] buf, int size, int offset, FUSEFileInfo fi) {
        String pathString = FUSEUtil.decodeUTF8(path);
        if(pathString == null) // Invalid UTF-8 sequence.
            return -ENOENT;

        if(!pathString.equals(hello_path))
            return -ENOENT;
        
        int len = hello_str.length;
        if(offset < len) {
           if (offset + size > len)
               size = len - offset;
           System.arraycopy(hello_str, offset, buf, 0, size);
        }
        else
            size = 0;

        return size;
    }

    public static void main(String[] args) {
        FUSE.main(args, new HelloFS());
    }
}
