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

/**
 *
 * @author erik
 */
public class JNILoader {
    private static final String LIBRARY_BASE_NAME = "jfuse";

    /**
     * Set this variable to true if you want some messages printed to stderr when the library is
     * loaded.
     */
    public static boolean verboseLoadLibrary = true;

    private enum CPUArchitecture {

        I386("i386"), AMD64("amd64"), IA64("ia64"),
        POWERPC("ppc32"), POWERPC64("ppc64"),
        SPARC("sparc32"), SPARC64("sparc64"),
        MIPS("mips32"), MIPS64("mips64"), ALPHA("alpha"),
        UNKNOWN;

        private final String idString;

        private CPUArchitecture() {
            this.idString = null;
        }

        private CPUArchitecture(String idString) {
            this.idString = idString;
        }

        public String getArchitectureString() {
            return idString;
        }
    };

    private enum ExecutionEnvironment {

        WINDOWS("windows"), DARWIN("darwin"), GNU_LINUX("linux"),
        SOLARIS("solaris"), GNU_SOLARIS("gnu-solaris"), FREEBSD("freebsd"),
        GNU_FREEBSD("gnu-freebsd"), NETBSD("netbsd"), GNU_NETBSD("gnu-netbsd"),
        OPENBSD("openbsd"), DRAGONFLYBSD("dflybsd"), HP_UX("hpux"),
        IRIX("irix"), UNKNOWN;

        private final String idString;

        private ExecutionEnvironment() {
            this.idString = null;
        }

        private ExecutionEnvironment(String idString) {
            if(idString == null)
                throw new RuntimeException("Do not pass null.");
            this.idString = idString;
        }

        public String getIdentifierString() {
            return idString;
        }
    };

    private static CPUArchitecture getJVMArchitecture() {
        // Trying to cover all thinkable cases here...
        // Got some hints from http://lopica.sourceforge.net/os.html
        final String osArch = System.getProperty("os.arch");
        if(osArch == null)
            return CPUArchitecture.UNKNOWN;
        else if(osArch.equalsIgnoreCase("x86") ||
                osArch.equalsIgnoreCase("i386") ||
                osArch.equalsIgnoreCase("i486") ||
                osArch.equalsIgnoreCase("i586") ||
                osArch.equalsIgnoreCase("i686"))
            return CPUArchitecture.I386;
        else if(osArch.equalsIgnoreCase("amd64") ||
                osArch.equalsIgnoreCase("x86_64") ||
                osArch.equalsIgnoreCase("x64"))
            return CPUArchitecture.AMD64;
        else if(osArch.equalsIgnoreCase("ia64") ||
                osArch.equalsIgnoreCase("ia64n"))
            return CPUArchitecture.IA64;
        else
            return CPUArchitecture.UNKNOWN;
    }

    private static ExecutionEnvironment getExecutionEnvironment() {
        final String osName = System.getProperty("os.name").toLowerCase();
        final String osVersion = System.getProperty("os.version").toLowerCase();

        if(osName == null)
            return ExecutionEnvironment.UNKNOWN;
        else if(osName.startsWith("windows"))
            return ExecutionEnvironment.WINDOWS;
        else if(osName.startsWith("mac os x") ||
                osName.startsWith("darwin"))
            return ExecutionEnvironment.DARWIN;
        else if(osName.toLowerCase().startsWith("linux"))
            return ExecutionEnvironment.GNU_LINUX;
        else
            return ExecutionEnvironment.UNKNOWN;
    }

    public static String getSystemSpecifier() {
        CPUArchitecture archId = getJVMArchitecture();
        ExecutionEnvironment reId = getExecutionEnvironment();

        switch(reId) {
            case DARWIN:
                // Darwin has fat binaries, so we don't suffix any specific arch
                return reId.getIdentifierString();
            default:
                return reId.getIdentifierString() + "-" +
                        archId.getArchitectureString();
        }
    }

    /**
     * Does not check if the system is supported, and just tries to load the approprate library
     * from the architecture string specified in this system's ArchitectureIdentifier.
     */
    private static void loadLibrary() {
        final CPUArchitecture archId = getJVMArchitecture();
        final ExecutionEnvironment exId = getExecutionEnvironment();
        if(archId == CPUArchitecture.UNKNOWN) {
            System.err.println(System.getProperty("os.arch") + ": " +
                    "Architecture unknown! Cannot locate corresponding " +
                    "native I/O library.");
            throw new RuntimeException("loadLibrary(): CPU architecture unknown!");
        }
        else if(exId == ExecutionEnvironment.UNKNOWN) {
            System.err.println(System.getProperty("os.name") + " / " +
                    System.getProperty("os.version") + ": " +
                    "Execution environment unknown! Cannot locate " +
                    "corresponding native I/O library.");
            throw new RuntimeException("loadLibrary(): Execution environment " +
                    "(operating system) unknown!");
        }
        else {
            final String libName = LIBRARY_BASE_NAME + "-" + getSystemSpecifier();
            try {
                if(verboseLoadLibrary) System.err.println("Trying to load native library \"" + libName + "\"...");
                System.loadLibrary(libName);
                if(verboseLoadLibrary) System.err.println("Native library \"" + libName + "\" successfully loaded.");
            } catch(UnsatisfiedLinkError e) {
                System.err.println("ERROR: Native library \"" + libName + "\" failed to load!");
                System.err.println("java.library.path=\"" + System.getProperty("java.library.path") + "\"");
                throw e;
            }
        }
    }

    private static final Object loadSync = new Object();
    private static boolean loaded = false;

    private JNILoader() { throw new RuntimeException(); }

    public static void ensureLoaded() {
        synchronized(loadSync) {
            if(!loaded) {
                System.err.println("Loading library 'jfuse'...");
                loadLibrary();
                loaded = true;
                System.err.println("   done.");
            }
        }
    }
}
