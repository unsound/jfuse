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
	${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/src/native/FUSEDirFilContext.o \
	${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/src/native/MacFUSE20Util.o \
	${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/src/native/org_catacombae_jfuse_FUSE_26.o \
	${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/src/native/FUSE26Util.o \
	${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/src/native/org_catacombae_jfuse_types_fuse26_FUSEFillDir.o \
	${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/src/native/macfuse20_module.o \
	${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/src/native/FUSEFillDirContext.o \
	${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/src/native/org_catacombae_jfuse_types_fuse26_FUSEDirFil.o \
	${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/src/native/jFUSEContext.o \
	${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/src/native/common.o \
	${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/src/native/org_catacombae_jfuse_types_system_StatConstant.o \
	${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/src/native/fuse26_module.o \
	${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/src/native/JNIUtil.o \
	${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/src/native/org_catacombae_jfuse_types_system_Errno.o \
	${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/src/native/org_catacombae_jfuse_util_FUSEUtil.o

# C Compiler Flags
CFLAGS=-mmacosx-version-min=10.4 -arch i386 -arch ppc -arch x86_64 -arch ppc64

# CC Compiler Flags
CCFLAGS=-mmacosx-version-min=10.4 -arch i386 -arch ppc -arch x86_64 -arch ppc64
CXXFLAGS=-mmacosx-version-min=10.4 -arch i386 -arch ppc -arch x86_64 -arch ppc64

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-lfuse -framework JavaVM

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	${MAKE}  -f nbproject/Makefile-darwin-Debug.mk dist/darwin-Debug/libjfuse.dylib

dist/darwin-Debug/libjfuse.dylib: ${OBJECTFILES}
	${MKDIR} -p dist/darwin-Debug
	${LINK.cc} -dynamiclib -install_name libjfuse.dylib -o dist/darwin-Debug/libjfuse.dylib -fPIC ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/src/native/FUSEDirFilContext.o: nbproject/Makefile-${CND_CONF}.mk ../../../src/native/FUSEDirFilContext.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/src/native
	$(COMPILE.cc) -g -Wall -D_FILE_OFFSET_BITS=64 -D__FreeBSD__=10 -I/System/Library/Frameworks/JavaVM.framework/Headers -fPIC  -o ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/src/native/FUSEDirFilContext.o ../../../src/native/FUSEDirFilContext.cpp

${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/src/native/MacFUSE20Util.o: nbproject/Makefile-${CND_CONF}.mk ../../../src/native/MacFUSE20Util.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/src/native
	$(COMPILE.cc) -g -Wall -D_FILE_OFFSET_BITS=64 -D__FreeBSD__=10 -I/System/Library/Frameworks/JavaVM.framework/Headers -fPIC  -o ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/src/native/MacFUSE20Util.o ../../../src/native/MacFUSE20Util.cpp

${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/src/native/org_catacombae_jfuse_FUSE_26.o: nbproject/Makefile-${CND_CONF}.mk ../../../src/native/org_catacombae_jfuse_FUSE_26.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/src/native
	$(COMPILE.cc) -g -Wall -D_FILE_OFFSET_BITS=64 -D__FreeBSD__=10 -I/System/Library/Frameworks/JavaVM.framework/Headers -fPIC  -o ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/src/native/org_catacombae_jfuse_FUSE_26.o ../../../src/native/org_catacombae_jfuse_FUSE_26.cpp

${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/src/native/FUSE26Util.o: nbproject/Makefile-${CND_CONF}.mk ../../../src/native/FUSE26Util.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/src/native
	$(COMPILE.cc) -g -Wall -D_FILE_OFFSET_BITS=64 -D__FreeBSD__=10 -I/System/Library/Frameworks/JavaVM.framework/Headers -fPIC  -o ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/src/native/FUSE26Util.o ../../../src/native/FUSE26Util.cpp

${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/src/native/org_catacombae_jfuse_types_fuse26_FUSEFillDir.o: nbproject/Makefile-${CND_CONF}.mk ../../../src/native/org_catacombae_jfuse_types_fuse26_FUSEFillDir.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/src/native
	$(COMPILE.cc) -g -Wall -D_FILE_OFFSET_BITS=64 -D__FreeBSD__=10 -I/System/Library/Frameworks/JavaVM.framework/Headers -fPIC  -o ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/src/native/org_catacombae_jfuse_types_fuse26_FUSEFillDir.o ../../../src/native/org_catacombae_jfuse_types_fuse26_FUSEFillDir.cpp

${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/src/native/macfuse20_module.o: nbproject/Makefile-${CND_CONF}.mk ../../../src/native/macfuse20_module.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/src/native
	$(COMPILE.cc) -g -Wall -D_FILE_OFFSET_BITS=64 -D__FreeBSD__=10 -I/System/Library/Frameworks/JavaVM.framework/Headers -fPIC  -o ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/src/native/macfuse20_module.o ../../../src/native/macfuse20_module.cpp

${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/src/native/FUSEFillDirContext.o: nbproject/Makefile-${CND_CONF}.mk ../../../src/native/FUSEFillDirContext.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/src/native
	$(COMPILE.cc) -g -Wall -D_FILE_OFFSET_BITS=64 -D__FreeBSD__=10 -I/System/Library/Frameworks/JavaVM.framework/Headers -fPIC  -o ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/src/native/FUSEFillDirContext.o ../../../src/native/FUSEFillDirContext.cpp

${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/src/native/org_catacombae_jfuse_types_fuse26_FUSEDirFil.o: nbproject/Makefile-${CND_CONF}.mk ../../../src/native/org_catacombae_jfuse_types_fuse26_FUSEDirFil.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/src/native
	$(COMPILE.cc) -g -Wall -D_FILE_OFFSET_BITS=64 -D__FreeBSD__=10 -I/System/Library/Frameworks/JavaVM.framework/Headers -fPIC  -o ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/src/native/org_catacombae_jfuse_types_fuse26_FUSEDirFil.o ../../../src/native/org_catacombae_jfuse_types_fuse26_FUSEDirFil.cpp

${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/src/native/jFUSEContext.o: nbproject/Makefile-${CND_CONF}.mk ../../../src/native/jFUSEContext.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/src/native
	$(COMPILE.cc) -g -Wall -D_FILE_OFFSET_BITS=64 -D__FreeBSD__=10 -I/System/Library/Frameworks/JavaVM.framework/Headers -fPIC  -o ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/src/native/jFUSEContext.o ../../../src/native/jFUSEContext.cpp

${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/src/native/common.o: nbproject/Makefile-${CND_CONF}.mk ../../../src/native/common.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/src/native
	$(COMPILE.cc) -g -Wall -D_FILE_OFFSET_BITS=64 -D__FreeBSD__=10 -I/System/Library/Frameworks/JavaVM.framework/Headers -fPIC  -o ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/src/native/common.o ../../../src/native/common.cpp

${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/src/native/org_catacombae_jfuse_types_system_StatConstant.o: nbproject/Makefile-${CND_CONF}.mk ../../../src/native/org_catacombae_jfuse_types_system_StatConstant.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/src/native
	$(COMPILE.cc) -g -Wall -D_FILE_OFFSET_BITS=64 -D__FreeBSD__=10 -I/System/Library/Frameworks/JavaVM.framework/Headers -fPIC  -o ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/src/native/org_catacombae_jfuse_types_system_StatConstant.o ../../../src/native/org_catacombae_jfuse_types_system_StatConstant.cpp

${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/src/native/fuse26_module.o: nbproject/Makefile-${CND_CONF}.mk ../../../src/native/fuse26_module.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/src/native
	$(COMPILE.cc) -g -Wall -D_FILE_OFFSET_BITS=64 -D__FreeBSD__=10 -I/System/Library/Frameworks/JavaVM.framework/Headers -fPIC  -o ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/src/native/fuse26_module.o ../../../src/native/fuse26_module.cpp

${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/src/native/JNIUtil.o: nbproject/Makefile-${CND_CONF}.mk ../../../src/native/JNIUtil.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/src/native
	$(COMPILE.cc) -g -Wall -D_FILE_OFFSET_BITS=64 -D__FreeBSD__=10 -I/System/Library/Frameworks/JavaVM.framework/Headers -fPIC  -o ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/src/native/JNIUtil.o ../../../src/native/JNIUtil.cpp

${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/src/native/org_catacombae_jfuse_types_system_Errno.o: nbproject/Makefile-${CND_CONF}.mk ../../../src/native/org_catacombae_jfuse_types_system_Errno.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/src/native
	$(COMPILE.cc) -g -Wall -D_FILE_OFFSET_BITS=64 -D__FreeBSD__=10 -I/System/Library/Frameworks/JavaVM.framework/Headers -fPIC  -o ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/src/native/org_catacombae_jfuse_types_system_Errno.o ../../../src/native/org_catacombae_jfuse_types_system_Errno.cpp

${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/src/native/org_catacombae_jfuse_util_FUSEUtil.o: nbproject/Makefile-${CND_CONF}.mk ../../../src/native/org_catacombae_jfuse_util_FUSEUtil.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/src/native
	$(COMPILE.cc) -g -Wall -D_FILE_OFFSET_BITS=64 -D__FreeBSD__=10 -I/System/Library/Frameworks/JavaVM.framework/Headers -fPIC  -o ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/src/native/org_catacombae_jfuse_util_FUSEUtil.o ../../../src/native/org_catacombae_jfuse_util_FUSEUtil.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf:
	${RM} -r build/darwin-Debug
	${RM} dist/darwin-Debug/libjfuse.dylib

# Subprojects
.clean-subprojects:
