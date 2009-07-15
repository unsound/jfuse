# configure.ac - Source file to generate "./configure" to prepare package for
#		 compilation.
#
# Copyright (c) 2009 Erik Larsson
#
# Derived from NTFS-3G's autoconf script:
#   Copyright (c) 2000-2006 Anton Altaparmakov
#   Copyright (c) 2005-2008 Szabolcs Szakacsits
#   Copyright (C) 2007-2008 Alon Bar-Lev
#
# This autoconf script is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# as published by the Free Software Foundation; either version 2
# of the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

# Autoconf
AC_PREREQ(2.59)
AC_INIT([libjfuse],[0.1],[erik82@kth.se])
LIBJFUSE_VERSION="0"
AC_CONFIG_SRCDIR([src/fuse26_module.cpp])

# Environment
AC_CANONICAL_HOST
AC_CANONICAL_TARGET

# Automake
AC_CONFIG_AUX_DIR([.])
#AM_INIT_AUTOMAKE([${PACKAGE_NAME}], [${PACKAGE_VERSION}])
AM_INIT_AUTOMAKE(no-dependencies no-dist-gzip dist-bzip2)
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIR([m4])
AM_MAINTAINER_MODE

# Static options (no modify)
enable_library="yes"

# Options
AC_ARG_ENABLE(
	[debug],
	[AS_HELP_STRING([--enable-debug],[enable debugging code and output])],
	,
	[enable_debug="no"]
)

AC_ARG_ENABLE(
	[warnings],
	[AS_HELP_STRING([--enable-warnings],[enable lots of compiler warnings])],
	,
	[enable_warnings="no"]
)

AC_ARG_ENABLE(
	[pedantic],
	[AS_HELP_STRING([--enable-pedantic],[enable compile pedantic mode])],
	,
	[enable_pedantic="no"]
)

AC_ARG_ENABLE(
	[really-static],
	[AS_HELP_STRING([--enable-really-static],[create fully static binaries])],
	,
	[enable_really_static="no"]
)

AC_ARG_ENABLE(
	[ldscript],
	[AS_HELP_STRING([--enable-ldscript],[use ldscript instead of .so symlink])],
	,
	[enable_ldscript="no"]
)

AC_ARG_ENABLE(
	[ldconfig],
	[AS_HELP_STRING([--disable-ldconfig],[do not update dynamic linker cache using ldconfig])],
	,
	[enable_ldconfig="yes"]
)

case "${target_os}" in
darwin*)
	AC_ARG_ENABLE(
		[ub],
		[AS_HELP_STRING([--enable-ub],[compile a Universal Binary with i386, x86_64, ppc and ppc64 code @<:@default=enabled for Mac OS X@:>@])],
		[ fatbinary_type="all" ],
		
	)
	
	AC_ARG_ENABLE(
		[tigersdk],
		[AS_HELP_STRING([--enable-tigersdk],[use Mac OS X 10.4 (Tiger) SDK when compiling])],
		[
			macosx_sdk="10.4"
		],
		
	)
	;;
esac

# pthread_rwlock_t requires _GNU_SOURCE
AC_GNU_SOURCE

# Programs
AC_PROG_CC(gcc cc)
AC_PROG_CXX
AC_PROG_LN_S
AM_PROG_CC_C_O

ifdef(
	[LT_INIT],
	[LT_INIT],
	[
		AC_PROG_LIBTOOL
		AC_ENABLE_STATIC
		AC_ENABLE_SHARED
	]
)

AC_PATH_PROG([MV], [mv])
AC_PATH_PROG([RM], [rm])
AC_PATH_PROG([SED], [sed])
AC_ARG_VAR([LDCONFIG], [ldconfig utility])
AC_PATH_PROG([LDCONFIG], [ldconfig], [true], [/sbin /usr/sbin $PATH])

# Environment
if test "${enable_ldscript}" = "yes"; then
	AC_MSG_CHECKING([Output format])
	OUTPUT_FORMAT="$(${CC} ${CFLAGS} ${LDFLAGS} -Wl,--verbose 2>&1 | ${SED} -n 's/^OUTPUT_FORMAT("\([[^"]]*\)",.*/\1/p')"
	if test -z "${OUTPUT_FORMAT}"; then
		AC_MSG_RESULT([None])
	else
		AC_MSG_RESULT([${OUTPUT_FORMAT}])
		OUTPUT_FORMAT="OUTPUT_FORMAT ( ${OUTPUT_FORMAT} )"
	fi
fi

# Checks for header files.
AC_HEADER_STDC

AC_CHECK_HEADERS(
	[ \
		fcntl.h \
		inttypes.h \
		sys/mount.h \
		sys/stat.h \
		sys/time.h \
		sys/types.h \
		unistd.h
	],
	,
	AC_MSG_ERROR([[Could not find one of the required headers!]])
)

# FUSE check, using pkg-config
if test -z "$PKG_CONFIG"; then
	AC_PATH_PROG(PKG_CONFIG, pkg-config, no)
fi
test "x${PKG_CONFIG}" = "xno" && AC_MSG_ERROR([pkg-config wasn't found! Please install from your vendor, or see http://pkg-config.freedesktop.org/wiki/])
# Libraries often install their metadata .pc files in directories
# not searched by pkg-config. Let's workaround this. 
export PKG_CONFIG_PATH=${PKG_CONFIG_PATH}:/lib/pkgconfig:/usr/lib/pkgconfig:/opt/gnome/lib/pkgconfig:/usr/share/pkgconfig:/usr/local/lib/pkgconfig:$prefix/lib/pkgconfig:/opt/gnome/share/pkgconfig:/usr/local/share/pkgconfig
PKG_CHECK_MODULES(
	[FUSE_MODULE],
	[fuse >= 2.6.0],
	,
	[
		AC_MSG_ERROR([FUSE >= 2.6.0 was not found. Either older FUSE is still present, or FUSE is not fully installed (e.g. fuse, libfuse, libfuse2, libfuse-dev, etc packages). Source code: http://fuse.sf.net])
	]
)
FUSE_LIB_PATH=`$PKG_CONFIG --libs-only-L fuse | sed -e 's,/[/]*,/,g' -e 's,[ ]*$,,'`

# Attempt to locate JNI headers
if test -z "${JAVAC}"; then
   JAVAC=javac
fi

case "$host_os" in
freebsd*)
	# Attempt to work around FreeBSD's dirty tricks. See javavm(1).
	JAVA_HOME=`env JAVAVM_DRYRUN=yes /usr/local/bin/java | grep '^JAVA_HOME' | cut -c11-`
	PATH=$JAVA_HOME/bin:$PATH
	;;
esac


AC_JNI_INCLUDE_DIR
for JNI_INCLUDE_DIR in $JNI_INCLUDE_DIRS
do
	CPPFLAGS="$CPPFLAGS -I$JNI_INCLUDE_DIR"
done

# Checks for typedefs, structures, and compiler characteristics.
AC_C_CONST
AC_C_INLINE
AC_TYPE_OFF_T
AC_TYPE_SIZE_T

# Checks for library functions.
AC_FUNC_MEMCMP
AC_FUNC_STAT
AC_CHECK_FUNCS([ \
	fdatasync memset strerror utime fork \
])
AC_SYS_LARGEFILE

if test "$GCC" = "yes" ; then
	# We add -Wall to enable some compiler warnings.
	CFLAGS="${CFLAGS} -Wall"
fi

if test "${enable_pedantic}" = "yes"; then
	enable_warnings="yes"
	CFLAGS="${CFLAGS} -pedantic"
fi

if test "${enable_warnings}" = "yes"; then
	CFLAGS="${CFLAGS} -W -Wall -Waggregate-return -Wbad-function-cast -Wcast-align -Wcast-qual -Wdisabled-optimization -Wdiv-by-zero -Wfloat-equal -Winline -Wmissing-declarations -Wmissing-format-attribute -Wmissing-noreturn -Wmissing-prototypes -Wmultichar -Wnested-externs -Wpointer-arith -Wredundant-decls -Wshadow -Wsign-compare -Wstrict-prototypes -Wundef -Wwrite-strings -Wformat -Wformat-security"
fi

if test "${enable_debug}" = "yes"; then
	CFLAGS="${CFLAGS} -g -DDEBUG"
	AC_DEFINE(
		[ENABLE_DEBUG],
		[1],
		[Define to 1 if debug should be enabled]
	)
fi

case "${fatbinary_type}" in
all)
	ARCH_FLAGS="-arch i386 -arch x86_64 -arch ppc -arch ppc64" ;;
universal32)
	ARCH_FLAGS="-arch i386 -arch ppc" ;;
universal64)
	ARCH_FLAGS="-arch x86_64 -arch ppc64" ;;
fatppc)
	ARCH_FLAGS="-arch ppc -arch ppc64" ;;
fatintel)
	ARCH_FLAGS="-arch i386 -arch x86_64" ;;
esac

if test ! -z "${ARCH_FLAGS}"; then
   CFLAGS="${ARCH_FLAGS} ${CFLAGS}"
   CPPFLAGS="${ARCH_FLAGS} ${CPPFLAGS}"
   LDFLAGS="${ARCH_FLAGS} ${LDFLAGS}"
fi

case "${macosx_sdk}" in
10.4)
	SDK=/Developer/SDKs/MacOSX10.4u.sdk
	CFLAGS="${CFLAGS} -mmacosx-version-min=10.4 -isysroot ${SDK}"
	CPPFLAGS="${CPPFLAGS} -mmacosx-version-min=10.4 -isysroot ${SDK}"
	LDFLAGS="${LDFLAGS} -mmacosx-version-min=10.4 -isysroot ${SDK} -Wl,-syslibroot,${SDK}"
	;;
esac

if test "x${DISTCHECK_HACK}" != "x"; then
   	# I have no idea what this does.
	enable_ldconfig="no"
fi

# Settings
pkgconfigdir="\$(libdir)/pkgconfig"
jfuseincludedir="\$(includedir)"

AC_SUBST([pkgconfigdir])
AC_SUBST([jfuseincludedir])
AC_SUBST([LIBJFUSE_VERSION])
AC_SUBST([OUTPUT_FORMAT])
AM_CONDITIONAL([GENERATE_LDSCRIPT], [test "${enable_ldscript}" = "yes"])
AM_CONDITIONAL([WINDOWS], [test "${WINDOWS}" = "yes"])
AM_CONDITIONAL([RUN_LDCONFIG], [test "${enable_ldconfig}" = "yes"])
AM_CONDITIONAL([REALLYSTATIC], [test "${enable_really_static}" = "yes"])
AM_CONDITIONAL([INSTALL_LIBRARY], [test "${enable_library}" = "yes"])

# workaround for <autoconf-2.60
if test -z "${docdir}"; then
	docdir="\$(datarootdir)/doc/\$(PACKAGE_NAME)"
	AC_SUBST([docdir])
fi
# workaround for <automake-1.10
if test -z "${MKDIR_P}"; then
	MKDIR_P="\$(mkdir_p)"
	AC_SUBST([MKDIR_P])
fi

# generate files
AC_CONFIG_FILES([
	Makefile
	include/Makefile
	src/Makefile
	src/libjfuse.pc
])
AC_OUTPUT

echo "You can type now 'make' to build libjfuse."

