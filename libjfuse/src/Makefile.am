
MAINTAINERCLEANFILES  = $(srcdir)/Makefile.in

if INSTALL_LIBRARY
#rootlib_LTLIBRARIES=#Create directory
lib_LTLIBRARIES       = libjfuse.la
pkgconfig_DATA        = libjfuse.pc
else
noinst_LTLIBRARIES    = libjfuse.la
endif

libjfuse_la_CPPFLAGS  = $(AM_CPPFLAGS) $(FUSE_MODULE_CFLAGS) -I$(top_srcdir)/include

libjfuse_la_LIBADD    = $(FUSE_MODULE_LIBS)
libjfuse_la_LDFLAGS   = -version-info $(LIBJFUSE_VERSION) -no-undefined

libjfuse_la_SOURCES   = \
	FUSE26Util.cpp \
	FUSEDirFilContext.cpp \
	FUSEFillDirContext.cpp \
	JNIUtil.cpp \
	MacFUSE20Util.cpp \
	common.cpp \
	fuse26_module.cpp \
	jFUSEContext.cpp \
	macfuse20_module.cpp \
	org_catacombae_jfuse_FUSE_26.cpp \
	org_catacombae_jfuse_JNILoader.cpp \
	org_catacombae_jfuse_types_fuse26_FUSEDirFil.cpp \
	org_catacombae_jfuse_types_fuse26_FUSEFillDir.cpp \
	org_catacombae_jfuse_types_system_Errno.cpp \
	org_catacombae_jfuse_types_system_StatConstant.cpp \
	org_catacombae_jfuse_util_FUSEUtil.cpp
