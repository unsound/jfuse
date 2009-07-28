#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=
AS=

# Macros
CND_PLATFORM=GNU-MacOSX
CND_CONF=darwin-Debug
CND_DISTDIR=dist

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=build/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/libjfuse/src/org_catacombae_jfuse_util_FUSEUtil.o \
	${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/libjfuse/src/org_catacombae_jfuse_JNILoader.o \
	${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/libjfuse/src/org_catacombae_jfuse_types_system_StatConstant.o \
	${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/libjfuse/src/org_catacombae_jfuse_FUSE_26.o \
	${OBJECTDIR}/_ext/Users/erik/devel/git/jfuse/libjfuse/src/org_catacombae_jfuse_types_system_StringConstant.o \
	${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/libjfuse/src/org_catacombae_jfuse_types_fuse26_FUSEFillDir.o \
	${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/libjfuse/src/JNIUtil.o \
	${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/libjfuse/src/MacFUSE20Util.o \
	${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/libjfuse/src/fuse26_module.o \
	${OBJECTDIR}/_ext/Users/erik/devel/git/jfuse/libjfuse/src/org_catacombae_jfuse_types_system_NumericalConstant.o \
	${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/libjfuse/src/common.o \
	${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/libjfuse/src/FUSEFillDirContext.o \
	${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/libjfuse/src/FUSEDirFilContext.o \
	${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/libjfuse/src/FUSE26Util.o \
	${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/libjfuse/src/macfuse20_module.o \
	${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/libjfuse/src/org_catacombae_jfuse_types_fuse26_FUSEDirFil.o \
	${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/libjfuse/src/org_catacombae_jfuse_types_system_Errno.o \
	${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/libjfuse/src/jFUSEContext.o

# C Compiler Flags
CFLAGS=-mmacosx-version-min=10.4 -arch i386 -arch ppc -arch x86_64 -arch ppc64

# CC Compiler Flags
CCFLAGS=-mmacosx-version-min=10.4 -arch i386 -arch ppc -arch x86_64 -arch ppc64 -gstabs3
CXXFLAGS=-mmacosx-version-min=10.4 -arch i386 -arch ppc -arch x86_64 -arch ppc64 -gstabs3

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-lfuse

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	${MAKE}  -f nbproject/Makefile-darwin-Debug.mk dist/darwin-Debug/libjfuse.dylib

dist/darwin-Debug/libjfuse.dylib: ${OBJECTFILES}
	${MKDIR} -p dist/darwin-Debug
	${LINK.cc} -dynamiclib -install_name libjfuse.dylib -o dist/darwin-Debug/libjfuse.dylib -fPIC ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/libjfuse/src/org_catacombae_jfuse_util_FUSEUtil.o: nbproject/Makefile-${CND_CONF}.mk ../../../libjfuse/src/org_catacombae_jfuse_util_FUSEUtil.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/libjfuse/src
	$(COMPILE.cc) -Wall -D_FILE_OFFSET_BITS=64 -D__FreeBSD__=10 -I/System/Library/Frameworks/JavaVM.framework/Headers -I/usr/local/include/fuse -I../../../libjfuse/include -fPIC  -o ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/libjfuse/src/org_catacombae_jfuse_util_FUSEUtil.o ../../../libjfuse/src/org_catacombae_jfuse_util_FUSEUtil.cpp

${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/libjfuse/src/org_catacombae_jfuse_JNILoader.o: nbproject/Makefile-${CND_CONF}.mk ../../../libjfuse/src/org_catacombae_jfuse_JNILoader.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/libjfuse/src
	$(COMPILE.cc) -Wall -D_FILE_OFFSET_BITS=64 -D__FreeBSD__=10 -I/System/Library/Frameworks/JavaVM.framework/Headers -I/usr/local/include/fuse -I../../../libjfuse/include -fPIC  -o ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/libjfuse/src/org_catacombae_jfuse_JNILoader.o ../../../libjfuse/src/org_catacombae_jfuse_JNILoader.cpp

${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/libjfuse/src/org_catacombae_jfuse_types_system_StatConstant.o: nbproject/Makefile-${CND_CONF}.mk ../../../libjfuse/src/org_catacombae_jfuse_types_system_StatConstant.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/libjfuse/src
	$(COMPILE.cc) -Wall -D_FILE_OFFSET_BITS=64 -D__FreeBSD__=10 -I/System/Library/Frameworks/JavaVM.framework/Headers -I/usr/local/include/fuse -I../../../libjfuse/include -fPIC  -o ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/libjfuse/src/org_catacombae_jfuse_types_system_StatConstant.o ../../../libjfuse/src/org_catacombae_jfuse_types_system_StatConstant.cpp

${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/libjfuse/src/org_catacombae_jfuse_FUSE_26.o: nbproject/Makefile-${CND_CONF}.mk ../../../libjfuse/src/org_catacombae_jfuse_FUSE_26.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/libjfuse/src
	$(COMPILE.cc) -Wall -D_FILE_OFFSET_BITS=64 -D__FreeBSD__=10 -I/System/Library/Frameworks/JavaVM.framework/Headers -I/usr/local/include/fuse -I../../../libjfuse/include -fPIC  -o ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/libjfuse/src/org_catacombae_jfuse_FUSE_26.o ../../../libjfuse/src/org_catacombae_jfuse_FUSE_26.cpp

${OBJECTDIR}/_ext/Users/erik/devel/git/jfuse/libjfuse/src/org_catacombae_jfuse_types_system_StringConstant.o: nbproject/Makefile-${CND_CONF}.mk /Users/erik/devel/git/jfuse/libjfuse/src/org_catacombae_jfuse_types_system_StringConstant.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/Users/erik/devel/git/jfuse/libjfuse/src
	$(COMPILE.cc) -Wall -D_FILE_OFFSET_BITS=64 -D__FreeBSD__=10 -I/System/Library/Frameworks/JavaVM.framework/Headers -I/usr/local/include/fuse -I../../../libjfuse/include -fPIC  -o ${OBJECTDIR}/_ext/Users/erik/devel/git/jfuse/libjfuse/src/org_catacombae_jfuse_types_system_StringConstant.o /Users/erik/devel/git/jfuse/libjfuse/src/org_catacombae_jfuse_types_system_StringConstant.cpp

${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/libjfuse/src/org_catacombae_jfuse_types_fuse26_FUSEFillDir.o: nbproject/Makefile-${CND_CONF}.mk ../../../libjfuse/src/org_catacombae_jfuse_types_fuse26_FUSEFillDir.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/libjfuse/src
	$(COMPILE.cc) -Wall -D_FILE_OFFSET_BITS=64 -D__FreeBSD__=10 -I/System/Library/Frameworks/JavaVM.framework/Headers -I/usr/local/include/fuse -I../../../libjfuse/include -fPIC  -o ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/libjfuse/src/org_catacombae_jfuse_types_fuse26_FUSEFillDir.o ../../../libjfuse/src/org_catacombae_jfuse_types_fuse26_FUSEFillDir.cpp

${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/libjfuse/src/JNIUtil.o: nbproject/Makefile-${CND_CONF}.mk ../../../libjfuse/src/JNIUtil.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/libjfuse/src
	$(COMPILE.cc) -Wall -D_FILE_OFFSET_BITS=64 -D__FreeBSD__=10 -I/System/Library/Frameworks/JavaVM.framework/Headers -I/usr/local/include/fuse -I../../../libjfuse/include -fPIC  -o ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/libjfuse/src/JNIUtil.o ../../../libjfuse/src/JNIUtil.cpp

${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/libjfuse/src/MacFUSE20Util.o: nbproject/Makefile-${CND_CONF}.mk ../../../libjfuse/src/MacFUSE20Util.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/libjfuse/src
	$(COMPILE.cc) -Wall -D_FILE_OFFSET_BITS=64 -D__FreeBSD__=10 -I/System/Library/Frameworks/JavaVM.framework/Headers -I/usr/local/include/fuse -I../../../libjfuse/include -fPIC  -o ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/libjfuse/src/MacFUSE20Util.o ../../../libjfuse/src/MacFUSE20Util.cpp

${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/libjfuse/src/fuse26_module.o: nbproject/Makefile-${CND_CONF}.mk ../../../libjfuse/src/fuse26_module.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/libjfuse/src
	$(COMPILE.cc) -Wall -D_FILE_OFFSET_BITS=64 -D__FreeBSD__=10 -I/System/Library/Frameworks/JavaVM.framework/Headers -I/usr/local/include/fuse -I../../../libjfuse/include -fPIC  -o ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/libjfuse/src/fuse26_module.o ../../../libjfuse/src/fuse26_module.cpp

${OBJECTDIR}/_ext/Users/erik/devel/git/jfuse/libjfuse/src/org_catacombae_jfuse_types_system_NumericalConstant.o: nbproject/Makefile-${CND_CONF}.mk /Users/erik/devel/git/jfuse/libjfuse/src/org_catacombae_jfuse_types_system_NumericalConstant.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/Users/erik/devel/git/jfuse/libjfuse/src
	$(COMPILE.cc) -Wall -D_FILE_OFFSET_BITS=64 -D__FreeBSD__=10 -I/System/Library/Frameworks/JavaVM.framework/Headers -I/usr/local/include/fuse -I../../../libjfuse/include -fPIC  -o ${OBJECTDIR}/_ext/Users/erik/devel/git/jfuse/libjfuse/src/org_catacombae_jfuse_types_system_NumericalConstant.o /Users/erik/devel/git/jfuse/libjfuse/src/org_catacombae_jfuse_types_system_NumericalConstant.cpp

${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/libjfuse/src/common.o: nbproject/Makefile-${CND_CONF}.mk ../../../libjfuse/src/common.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/libjfuse/src
	$(COMPILE.cc) -Wall -D_FILE_OFFSET_BITS=64 -D__FreeBSD__=10 -I/System/Library/Frameworks/JavaVM.framework/Headers -I/usr/local/include/fuse -I../../../libjfuse/include -fPIC  -o ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/libjfuse/src/common.o ../../../libjfuse/src/common.cpp

${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/libjfuse/src/FUSEFillDirContext.o: nbproject/Makefile-${CND_CONF}.mk ../../../libjfuse/src/FUSEFillDirContext.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/libjfuse/src
	$(COMPILE.cc) -Wall -D_FILE_OFFSET_BITS=64 -D__FreeBSD__=10 -I/System/Library/Frameworks/JavaVM.framework/Headers -I/usr/local/include/fuse -I../../../libjfuse/include -fPIC  -o ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/libjfuse/src/FUSEFillDirContext.o ../../../libjfuse/src/FUSEFillDirContext.cpp

${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/libjfuse/src/FUSEDirFilContext.o: nbproject/Makefile-${CND_CONF}.mk ../../../libjfuse/src/FUSEDirFilContext.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/libjfuse/src
	$(COMPILE.cc) -Wall -D_FILE_OFFSET_BITS=64 -D__FreeBSD__=10 -I/System/Library/Frameworks/JavaVM.framework/Headers -I/usr/local/include/fuse -I../../../libjfuse/include -fPIC  -o ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/libjfuse/src/FUSEDirFilContext.o ../../../libjfuse/src/FUSEDirFilContext.cpp

${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/libjfuse/src/FUSE26Util.o: nbproject/Makefile-${CND_CONF}.mk ../../../libjfuse/src/FUSE26Util.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/libjfuse/src
	$(COMPILE.cc) -Wall -D_FILE_OFFSET_BITS=64 -D__FreeBSD__=10 -I/System/Library/Frameworks/JavaVM.framework/Headers -I/usr/local/include/fuse -I../../../libjfuse/include -fPIC  -o ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/libjfuse/src/FUSE26Util.o ../../../libjfuse/src/FUSE26Util.cpp

${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/libjfuse/src/macfuse20_module.o: nbproject/Makefile-${CND_CONF}.mk ../../../libjfuse/src/macfuse20_module.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/libjfuse/src
	$(COMPILE.cc) -Wall -D_FILE_OFFSET_BITS=64 -D__FreeBSD__=10 -I/System/Library/Frameworks/JavaVM.framework/Headers -I/usr/local/include/fuse -I../../../libjfuse/include -fPIC  -o ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/libjfuse/src/macfuse20_module.o ../../../libjfuse/src/macfuse20_module.cpp

${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/libjfuse/src/org_catacombae_jfuse_types_fuse26_FUSEDirFil.o: nbproject/Makefile-${CND_CONF}.mk ../../../libjfuse/src/org_catacombae_jfuse_types_fuse26_FUSEDirFil.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/libjfuse/src
	$(COMPILE.cc) -Wall -D_FILE_OFFSET_BITS=64 -D__FreeBSD__=10 -I/System/Library/Frameworks/JavaVM.framework/Headers -I/usr/local/include/fuse -I../../../libjfuse/include -fPIC  -o ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/libjfuse/src/org_catacombae_jfuse_types_fuse26_FUSEDirFil.o ../../../libjfuse/src/org_catacombae_jfuse_types_fuse26_FUSEDirFil.cpp

${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/libjfuse/src/org_catacombae_jfuse_types_system_Errno.o: nbproject/Makefile-${CND_CONF}.mk ../../../libjfuse/src/org_catacombae_jfuse_types_system_Errno.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/libjfuse/src
	$(COMPILE.cc) -Wall -D_FILE_OFFSET_BITS=64 -D__FreeBSD__=10 -I/System/Library/Frameworks/JavaVM.framework/Headers -I/usr/local/include/fuse -I../../../libjfuse/include -fPIC  -o ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/libjfuse/src/org_catacombae_jfuse_types_system_Errno.o ../../../libjfuse/src/org_catacombae_jfuse_types_system_Errno.cpp

${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/libjfuse/src/jFUSEContext.o: nbproject/Makefile-${CND_CONF}.mk ../../../libjfuse/src/jFUSEContext.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/libjfuse/src
	$(COMPILE.cc) -Wall -D_FILE_OFFSET_BITS=64 -D__FreeBSD__=10 -I/System/Library/Frameworks/JavaVM.framework/Headers -I/usr/local/include/fuse -I../../../libjfuse/include -fPIC  -o ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/libjfuse/src/jFUSEContext.o ../../../libjfuse/src/jFUSEContext.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf:
	${RM} -r build/darwin-Debug
	${RM} dist/darwin-Debug/libjfuse.dylib

# Subprojects
.clean-subprojects:
