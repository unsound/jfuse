
MAINTAINERCLEANFILES = $(srcdir)/Makefile.in

publicheaders = 

privateheaders = \
	CSLog.h \
	FUSE26Util.h \
	FUSEDirFilContext.h \
	FUSEFillDirContext.h \
	JNIUtil.h \
	JavaSignatures.h \
	MacFUSE20Util.h \
	common.h \
	fuse26_module.h \
	jFUSEContext.h \
	macfuse20_module.h \
	org_catacombae_jfuse_FUSE.h \
	org_catacombae_jfuse_JNILoader.h \
	org_catacombae_jfuse_types_fuse26_FUSEDirFil.h \
	org_catacombae_jfuse_types_fuse26_FUSEFillDir.h \
	org_catacombae_jfuse_types_system_Errno.h \
	org_catacombae_jfuse_types_system_StatConstant.h \
	org_catacombae_jfuse_util_FUSEUtil.h

if INSTALL_LIBRARY
include_HEADERS = $(publicheaders)
else
noinst_HEADERS = $(publicheaders) $(privateheaders)
endif

