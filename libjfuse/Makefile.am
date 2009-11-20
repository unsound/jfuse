
AUTOMAKE_OPTIONS = gnu
ACLOCAL_AMFLAGS = -I m4

EXTRA_DIST = BUILD_INSTRUCTIONS autogen.sh m4/ac_jni_include_dir.m4

MAINTAINERCLEANFILES=\
	$(srcdir)/configure \
	$(srcdir)/Makefile.in \
	$(srcdir)/aclocal.m4 \
	$(srcdir)/compile \
	$(srcdir)/depcomp \
	$(srcdir)/install-sh \
	$(srcdir)/ltmain.sh \
	$(srcdir)/missing \
	$(srcdir)/config.guess \
	$(srcdir)/config.sub \
	$(srcdir)/config.h.in \
	$(srcdir)/config.h.in~ \
	$(srcdir)/INSTALL \
	$(srcdir)/m4/ltsugar.m4 \
	$(srcdir)/m4/libtool.m4 \
	$(srcdir)/m4/ltversion.m4 \
	$(srcdir)/m4/lt~obsolete.m4 \
	$(srcdir)/m4/ltoptions.m4

SUBDIRS = include src

doc_DATA = AUTHORS COPYING ChangeLog NEWS README

dist-hook:
	$(MKDIR_P) "$(distdir)/m4"
