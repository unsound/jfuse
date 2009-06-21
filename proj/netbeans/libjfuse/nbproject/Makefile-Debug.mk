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

# Macros
PLATFORM=GNU-MacOSX

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=build/Debug/${PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/Users/erik/devel/git/jfuse/proj/netbeans/libjfuse/../../../src/native/org_catacombae_jfuse_FUSE_26.o \
	${OBJECTDIR}/_ext/Users/erik/devel/git/jfuse/proj/netbeans/libjfuse/../../../src/native/FUSE26Util.o \
	${OBJECTDIR}/_ext/Users/erik/devel/git/jfuse/proj/netbeans/libjfuse/../../../src/native/org_catacombae_jfuse_StatConstant.o \
	${OBJECTDIR}/_ext/Users/erik/devel/git/jfuse/proj/netbeans/libjfuse/../../../src/native/fuse26_module.o \
	${OBJECTDIR}/_ext/Users/erik/devel/git/jfuse/proj/netbeans/libjfuse/../../../src/native/FUSEFillDirContext.o \
	${OBJECTDIR}/_ext/Users/erik/devel/git/jfuse/proj/netbeans/libjfuse/../../../src/native/JNIUtil.o \
	${OBJECTDIR}/_ext/Users/erik/devel/git/jfuse/proj/netbeans/libjfuse/../../../src/native/org_catacombae_jfuse_FUSEFillDir.o \
	${OBJECTDIR}/_ext/Users/erik/devel/git/jfuse/proj/netbeans/libjfuse/../../../src/native/jFUSEContext.o \
	${OBJECTDIR}/_ext/Users/erik/devel/git/jfuse/proj/netbeans/libjfuse/../../../src/native/org_catacombae_jfuse_Errno.o \
	${OBJECTDIR}/_ext/Users/erik/devel/git/jfuse/proj/netbeans/libjfuse/../../../src/native/common.o

# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-mmacosx-version-min=10.4 -arch i386 -arch ppc -arch x86_64 -arch ppc64
CXXFLAGS=-mmacosx-version-min=10.4 -arch i386 -arch ppc -arch x86_64 -arch ppc64

# Fortran Compiler Flags
FFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-lfuse -framework JavaVM

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	${MAKE}  -f nbproject/Makefile-Debug.mk dist/Debug/${PLATFORM}/libjfuse.dylib

dist/Debug/${PLATFORM}/libjfuse.dylib: ${OBJECTFILES}
	${MKDIR} -p dist/Debug/${PLATFORM}
	${LINK.cc} -dynamiclib -install_name libjfuse.dylib -o dist/Debug/${PLATFORM}/libjfuse.dylib -fPIC ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/_ext/Users/erik/devel/git/jfuse/proj/netbeans/libjfuse/../../../src/native/org_catacombae_jfuse_FUSE_26.o: ../../../src/native/org_catacombae_jfuse_FUSE_26.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/Users/erik/devel/git/jfuse/proj/netbeans/libjfuse/../../../src/native
	$(COMPILE.cc) -g -Wall -D_FILE_OFFSET_BITS=64 -I/System/Library/Frameworks/JavaVM.framework/Headers -fPIC  -o ${OBJECTDIR}/_ext/Users/erik/devel/git/jfuse/proj/netbeans/libjfuse/../../../src/native/org_catacombae_jfuse_FUSE_26.o ../../../src/native/org_catacombae_jfuse_FUSE_26.cpp

${OBJECTDIR}/_ext/Users/erik/devel/git/jfuse/proj/netbeans/libjfuse/../../../src/native/FUSE26Util.o: ../../../src/native/FUSE26Util.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/Users/erik/devel/git/jfuse/proj/netbeans/libjfuse/../../../src/native
	$(COMPILE.cc) -g -Wall -D_FILE_OFFSET_BITS=64 -I/System/Library/Frameworks/JavaVM.framework/Headers -fPIC  -o ${OBJECTDIR}/_ext/Users/erik/devel/git/jfuse/proj/netbeans/libjfuse/../../../src/native/FUSE26Util.o ../../../src/native/FUSE26Util.cpp

${OBJECTDIR}/_ext/Users/erik/devel/git/jfuse/proj/netbeans/libjfuse/../../../src/native/org_catacombae_jfuse_StatConstant.o: ../../../src/native/org_catacombae_jfuse_StatConstant.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/Users/erik/devel/git/jfuse/proj/netbeans/libjfuse/../../../src/native
	$(COMPILE.cc) -g -Wall -D_FILE_OFFSET_BITS=64 -I/System/Library/Frameworks/JavaVM.framework/Headers -fPIC  -o ${OBJECTDIR}/_ext/Users/erik/devel/git/jfuse/proj/netbeans/libjfuse/../../../src/native/org_catacombae_jfuse_StatConstant.o ../../../src/native/org_catacombae_jfuse_StatConstant.cpp

${OBJECTDIR}/_ext/Users/erik/devel/git/jfuse/proj/netbeans/libjfuse/../../../src/native/fuse26_module.o: ../../../src/native/fuse26_module.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/Users/erik/devel/git/jfuse/proj/netbeans/libjfuse/../../../src/native
	$(COMPILE.cc) -g -Wall -D_FILE_OFFSET_BITS=64 -I/System/Library/Frameworks/JavaVM.framework/Headers -fPIC  -o ${OBJECTDIR}/_ext/Users/erik/devel/git/jfuse/proj/netbeans/libjfuse/../../../src/native/fuse26_module.o ../../../src/native/fuse26_module.cpp

${OBJECTDIR}/_ext/Users/erik/devel/git/jfuse/proj/netbeans/libjfuse/../../../src/native/FUSEFillDirContext.o: ../../../src/native/FUSEFillDirContext.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/Users/erik/devel/git/jfuse/proj/netbeans/libjfuse/../../../src/native
	$(COMPILE.cc) -g -Wall -D_FILE_OFFSET_BITS=64 -I/System/Library/Frameworks/JavaVM.framework/Headers -fPIC  -o ${OBJECTDIR}/_ext/Users/erik/devel/git/jfuse/proj/netbeans/libjfuse/../../../src/native/FUSEFillDirContext.o ../../../src/native/FUSEFillDirContext.cpp

${OBJECTDIR}/_ext/Users/erik/devel/git/jfuse/proj/netbeans/libjfuse/../../../src/native/JNIUtil.o: ../../../src/native/JNIUtil.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/Users/erik/devel/git/jfuse/proj/netbeans/libjfuse/../../../src/native
	$(COMPILE.cc) -g -Wall -D_FILE_OFFSET_BITS=64 -I/System/Library/Frameworks/JavaVM.framework/Headers -fPIC  -o ${OBJECTDIR}/_ext/Users/erik/devel/git/jfuse/proj/netbeans/libjfuse/../../../src/native/JNIUtil.o ../../../src/native/JNIUtil.cpp

${OBJECTDIR}/_ext/Users/erik/devel/git/jfuse/proj/netbeans/libjfuse/../../../src/native/org_catacombae_jfuse_FUSEFillDir.o: ../../../src/native/org_catacombae_jfuse_FUSEFillDir.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/Users/erik/devel/git/jfuse/proj/netbeans/libjfuse/../../../src/native
	$(COMPILE.cc) -g -Wall -D_FILE_OFFSET_BITS=64 -I/System/Library/Frameworks/JavaVM.framework/Headers -fPIC  -o ${OBJECTDIR}/_ext/Users/erik/devel/git/jfuse/proj/netbeans/libjfuse/../../../src/native/org_catacombae_jfuse_FUSEFillDir.o ../../../src/native/org_catacombae_jfuse_FUSEFillDir.cpp

${OBJECTDIR}/_ext/Users/erik/devel/git/jfuse/proj/netbeans/libjfuse/../../../src/native/jFUSEContext.o: ../../../src/native/jFUSEContext.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/Users/erik/devel/git/jfuse/proj/netbeans/libjfuse/../../../src/native
	$(COMPILE.cc) -g -Wall -D_FILE_OFFSET_BITS=64 -I/System/Library/Frameworks/JavaVM.framework/Headers -fPIC  -o ${OBJECTDIR}/_ext/Users/erik/devel/git/jfuse/proj/netbeans/libjfuse/../../../src/native/jFUSEContext.o ../../../src/native/jFUSEContext.cpp

${OBJECTDIR}/_ext/Users/erik/devel/git/jfuse/proj/netbeans/libjfuse/../../../src/native/org_catacombae_jfuse_Errno.o: ../../../src/native/org_catacombae_jfuse_Errno.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/Users/erik/devel/git/jfuse/proj/netbeans/libjfuse/../../../src/native
	$(COMPILE.cc) -g -Wall -D_FILE_OFFSET_BITS=64 -I/System/Library/Frameworks/JavaVM.framework/Headers -fPIC  -o ${OBJECTDIR}/_ext/Users/erik/devel/git/jfuse/proj/netbeans/libjfuse/../../../src/native/org_catacombae_jfuse_Errno.o ../../../src/native/org_catacombae_jfuse_Errno.cpp

${OBJECTDIR}/_ext/Users/erik/devel/git/jfuse/proj/netbeans/libjfuse/../../../src/native/common.o: ../../../src/native/common.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/Users/erik/devel/git/jfuse/proj/netbeans/libjfuse/../../../src/native
	$(COMPILE.cc) -g -Wall -D_FILE_OFFSET_BITS=64 -I/System/Library/Frameworks/JavaVM.framework/Headers -fPIC  -o ${OBJECTDIR}/_ext/Users/erik/devel/git/jfuse/proj/netbeans/libjfuse/../../../src/native/common.o ../../../src/native/common.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf:
	${RM} -r build/Debug
	${RM} dist/Debug/${PLATFORM}/libjfuse.dylib

# Subprojects
.clean-subprojects:
