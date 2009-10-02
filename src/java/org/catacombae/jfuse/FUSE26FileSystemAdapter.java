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

import org.catacombae.jfuse.types.fuse26.FUSEConnInfo;
import org.catacombae.jfuse.types.system.Flock;
import org.catacombae.jfuse.types.system.Stat;
import org.catacombae.jfuse.types.system.Utimbuf;
import org.catacombae.jfuse.types.system.StatVFS;
import org.catacombae.jfuse.types.system.Timespec;
import org.catacombae.jfuse.types.system.LongRef;
import org.catacombae.jfuse.types.fuse26.FUSEFillDir;
import org.catacombae.jfuse.types.fuse26.FUSEFileInfo;
import org.catacombae.jfuse.types.fuse26.FUSEDirFil;
import java.lang.reflect.Field;
import java.lang.reflect.Method;
import java.nio.ByteBuffer;

@SuppressWarnings("deprecation") // utime and getdir
public abstract class FUSE26FileSystemAdapter implements FUSEFileSystem {

    //@Override
    public int getattr(ByteBuffer path, Stat stat) {
        throw new UnsupportedOperationException("Not supposed to call this method.");
    }

    //@Override
    public int readlink(ByteBuffer path, ByteBuffer buffer) {
        throw new UnsupportedOperationException("Not supposed to call this method.");
    }

    //@Override
    public int getdir(ByteBuffer path, FUSEDirFil filler) {
        throw new UnsupportedOperationException("Not supposed to call this method.");
    }

    //@Override
    public int mknod(ByteBuffer path, short fileMode, long deviceNumber) {
        throw new UnsupportedOperationException("Not supposed to call this method.");
    }

    //@Override
    public int mkdir(ByteBuffer path, short createMode) {
        throw new UnsupportedOperationException("Not supposed to call this method.");
    }

    //@Override
    public int unlink(ByteBuffer path) {
        throw new UnsupportedOperationException("Not supposed to call this method.");
    }

    //@Override
    public int rmdir(ByteBuffer path) {
        throw new UnsupportedOperationException("Not supposed to call this method.");
    }

    //@Override
    public int symlink(ByteBuffer sourcePath, ByteBuffer destPath) {
        throw new UnsupportedOperationException("Not supposed to call this method.");
    }

    //@Override
    public int rename(ByteBuffer oldPath, ByteBuffer newPath) {
        throw new UnsupportedOperationException("Not supposed to call this method.");
    }

    //@Override
    public int link(ByteBuffer sourcePath, ByteBuffer destPath) {
        throw new UnsupportedOperationException("Not supposed to call this method.");
    }

    //@Override
    public int chmod(ByteBuffer path, short mode_t_newMode) {
        throw new UnsupportedOperationException("Not supposed to call this method.");
    }

    //@Override
    public int chown(ByteBuffer path, long userId, long groupId) {
        throw new UnsupportedOperationException("Not supposed to call this method.");
    }

    //@Override
    public int truncate(ByteBuffer path, long newSize) {
        throw new UnsupportedOperationException("Not supposed to call this method.");
    }

    //@Override
    public int utime(ByteBuffer path, Utimbuf time) {
        throw new UnsupportedOperationException("Not supposed to call this method.");
    }

    //@Override
    public int open(ByteBuffer path, FUSEFileInfo fi) {
        throw new UnsupportedOperationException("Not supposed to call this method.");
    }

    //@Override
    public int read(ByteBuffer path, ByteBuffer dest, long offset, FUSEFileInfo fi) {
        throw new UnsupportedOperationException("Not supposed to call this method.");
    }

    //@Override
    public int write(ByteBuffer path, ByteBuffer src, long off, FUSEFileInfo fi) {
        throw new UnsupportedOperationException("Not supposed to call this method.");
    }

    //@Override
    public int statfs(ByteBuffer path, StatVFS stat) {
        throw new UnsupportedOperationException("Not supposed to call this method.");
    }

    //@Override
    public int flush(ByteBuffer path, FUSEFileInfo fi) {
        throw new UnsupportedOperationException("Not supposed to call this method.");
    }

    //@Override
    public int release(ByteBuffer path, FUSEFileInfo fi) {
        throw new UnsupportedOperationException("Not supposed to call this method.");
    }

    //@Override
    public int fsync(ByteBuffer path, boolean datasync, FUSEFileInfo fi) {
        throw new UnsupportedOperationException("Not supposed to call this method.");
    }

    //@Override
    public int setxattr(ByteBuffer path, ByteBuffer name, ByteBuffer value, int flags, long position) {
        throw new UnsupportedOperationException("Not supposed to call this method.");
    }

    //@Override
    public int getxattr(ByteBuffer path, ByteBuffer name, ByteBuffer value, long position) {
        throw new UnsupportedOperationException("Not supposed to call this method.");
    }

    //@Override
    public int listxattr(ByteBuffer path, ByteBuffer namebuf) {
        throw new UnsupportedOperationException("Not supposed to call this method.");
    }

    //@Override
    public int removexattr(ByteBuffer path, ByteBuffer name) {
        throw new UnsupportedOperationException("Not supposed to call this method.");
    }

    //@Override
    public int opendir(ByteBuffer path, FUSEFileInfo fi) {
        throw new UnsupportedOperationException("Not supposed to call this method.");
    }

    //@Override
    public int readdir(ByteBuffer path, FUSEFillDir filler, long offset, FUSEFileInfo fi) {
        throw new UnsupportedOperationException("Not supposed to call this method.");
    }

    //@Override
    public int releasedir(ByteBuffer path, FUSEFileInfo fi) {
        throw new UnsupportedOperationException("Not supposed to call this method.");
    }

    //@Override
    public int fsyncdir(ByteBuffer path, boolean datasync, FUSEFileInfo fi) {
        throw new UnsupportedOperationException("Not supposed to call this method.");
    }

    //@Override
    public Object init(FUSEConnInfo conn) {
        throw new UnsupportedOperationException("Not supposed to call this method.");
    }

    //@Override
    public void destroy(Object o) {
        throw new UnsupportedOperationException("Not supposed to call this method.");
    }

    //@Override
    public int access(ByteBuffer path, int mode) {
        throw new UnsupportedOperationException("Not supposed to call this method.");
    }

    //@Override
    public int create(ByteBuffer path, short mode, FUSEFileInfo fi) {
        throw new UnsupportedOperationException("Not supposed to call this method.");
    }

    //@Override
    public int ftruncate(ByteBuffer path, long length, FUSEFileInfo fi) {
        throw new UnsupportedOperationException("Not supposed to call this method.");
    }

    //@Override
    public int fgetattr(ByteBuffer path, Stat stat, FUSEFileInfo fi) {
        throw new UnsupportedOperationException("Not supposed to call this method.");
    }

    //@Override
    public int lock(ByteBuffer path, FUSEFileInfo fi, int cmd, Flock flock) {
        throw new UnsupportedOperationException("Not supposed to call this method.");
    }

    //@Override
    public int utimens(ByteBuffer path, Timespec accessTime, Timespec modificationTime) {
        throw new UnsupportedOperationException("Not supposed to call this method.");
    }

    //@Override
    public int bmap(ByteBuffer path, long blocksize, LongRef idx) {
        throw new UnsupportedOperationException("Not supposed to call this method.");
    }

    //@Override
    public final FUSE26Capabilities getFUSECapabilities() {
        FUSE26Capabilities c = new FUSE26Capabilities();

        // Find out our capabilities through reflection.
        Class<FUSE26Operations> baseClass = FUSE26Operations.class;
        Class<?> subClass = this.getClass();

        while(!subClass.equals(FUSE26FileSystemAdapter.class)) {
            for(Method m : baseClass.getDeclaredMethods()) {
                try {
                    Field f = c.getClass().getField(m.getName());

                    try {
                        try {
                            subClass.getDeclaredMethod(m.getName(), m.getParameterTypes());
                            f.setBoolean(c, true);
                        } catch(NoSuchMethodException e) {
                            //f.setBoolean(c, false);
                        }
                    } catch(IllegalAccessException iae) {
                        throw new RuntimeException(iae);
                    }
                } catch(NoSuchFieldException e) {
                    throw new RuntimeException("No field \"" + m.getName() +
                            "\" in FUSE26Capabilities.", e);
                }
            }

            subClass = subClass.getSuperclass();
        }

        return c;
    }
}
