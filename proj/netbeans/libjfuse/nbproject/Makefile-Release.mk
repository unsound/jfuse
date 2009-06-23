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
OBJECTDIR=build/Release/${PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/Users/erik/devel/git/jfuse/proj/netbeans/libjfuse/../../../src/native/FUSEDirFilContext.o \
	${OBJECTDIR}/_ext/Users/erik/devel/git/jfuse/proj/netbeans/libjfuse/../../../src/native/org_catacombae_jfuse_FUSE_26.o \
	${OBJECTDIR}/_ext/Users/erik/devel/git/jfuse/proj/netbeans/libjfuse/../../../src/native/FUSE26Util.o \
	${OBJECTDIR}/_ext/Users/erik/devel/git/jfuse/proj/netbeans/libjfuse/../../../src/native/FUSEFillDirContext.o \
	${OBJECTDIR}/_ext/Users/erik/devel/git/jfuse/proj/netbeans/libjfuse/../../../src/native/jFUSEContext.o \
	${OBJECTDIR}/_ext/Users/erik/devel/git/jfuse/proj/netbeans/libjfuse/../../../src/native/org_catacombae_jfuse_Errno.o \
	${OBJECTDIR}/_ext/Users/erik/devel/git/jfuse/proj/netbeans/libjfuse/../../../src/native/common.o \
	${OBJECTDIR}/_ext/Users/erik/devel/git/jfuse/proj/netbeans/libjfuse/../../../src/native/org_catacombae_jfuse_StatConstant.o \
	${OBJECTDIR}/_ext/Users/erik/devel/git/jfuse/proj/netbeans/libjfuse/../../../src/native/fuse26_module.o \
	${OBJECTDIR}/_ext/Users/erik/devel/git/jfuse/proj/netbeans/libjfuse/../../../src/native/JNIUtil.o \
	${OBJECTDIR}/_ext/Users/erik/devel/git/jfuse/proj/netbeans/libjfuse/../../../src/native/org_catacombae_jfuse_FUSEDirFil.o \
	${OBJECTDIR}/_ext/Users/erik/devel/git/jfuse/proj/netbeans/libjfuse/../../../src/native/org_catacombae_jfuse_FUSEFillDir.o

# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	${MAKE}  -f nbproject/Makefile-Release.mk dist/Release/${PLATFORM}/liblibjfuse.dylib

dist/Release/${PLATFORM}/liblibjfuse.dylib: ${OBJECTFILES}
	${MKDIR} -p dist/Release/${PLATFORM}
	${LINK.cc} -dynamiclib -install_name liblibjfuse.dylib -o dist/Release/${PLATFORM}/liblibjfuse.dylib -fPIC ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/_ext/Users/erik/devel/git/jfuse/proj/netbeans/libjfuse/../../../src/native/FUSEDirFilContext.o: ../../../src/native/FUSEDirFilContext.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/Users/erik/devel/git/jfuse/proj/netbeans/libjfuse/../../../src/native
	${RM} $@.d
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/Users/erik/devel/git/jfuse/proj/netbeans/libjfuse/../../../src/native/FUSEDirFilContext.o ../../../src/native/FUSEDirFilContext.cpp

${OBJECTDIR}/_ext/Users/erik/devel/git/jfuse/proj/netbeans/libjfuse/../../../src/native/org_catacombae_jfuse_FUSE_26.o: ../../../src/native/org_catacombae_jfuse_FUSE_26.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/Users/erik/devel/git/jfuse/proj/netbeans/libjfuse/../../../src/native
	${RM} $@.d
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/Users/erik/devel/git/jfuse/proj/netbeans/libjfuse/../../../src/native/org_catacombae_jfuse_FUSE_26.o ../../../src/native/org_catacombae_jfuse_FUSE_26.cpp

${OBJECTDIR}/_ext/Users/erik/devel/git/jfuse/proj/netbeans/libjfuse/../../../src/native/FUSE26Util.o: ../../../src/native/FUSE26Util.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/Users/erik/devel/git/jfuse/proj/netbeans/libjfuse/../../../src/native
	${RM} $@.d
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/Users/erik/devel/git/jfuse/proj/netbeans/libjfuse/../../../src/native/FUSE26Util.o ../../../src/native/FUSE26Util.cpp

${OBJECTDIR}/_ext/Users/erik/devel/git/jfuse/proj/netbeans/libjfuse/../../../src/native/FUSEFillDirContext.o: ../../../src/native/FUSEFillDirContext.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/Users/erik/devel/git/jfuse/proj/netbeans/libjfuse/../../../src/native
	${RM} $@.d
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/Users/erik/devel/git/jfuse/proj/netbeans/libjfuse/../../../src/native/FUSEFillDirContext.o ../../../src/native/FUSEFillDirContext.cpp

${OBJECTDIR}/_ext/Users/erik/devel/git/jfuse/proj/netbeans/libjfuse/../../../src/native/jFUSEContext.o: ../../../src/native/jFUSEContext.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/Users/erik/devel/git/jfuse/proj/netbeans/libjfuse/../../../src/native
	${RM} $@.d
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/Users/erik/devel/git/jfuse/proj/netbeans/libjfuse/../../../src/native/jFUSEContext.o ../../../src/native/jFUSEContext.cpp

${OBJECTDIR}/_ext/Users/erik/devel/git/jfuse/proj/netbeans/libjfuse/../../../src/native/org_catacombae_jfuse_Errno.o: ../../../src/native/org_catacombae_jfuse_Errno.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/Users/erik/devel/git/jfuse/proj/netbeans/libjfuse/../../../src/native
	${RM} $@.d
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/Users/erik/devel/git/jfuse/proj/netbeans/libjfuse/../../../src/native/org_catacombae_jfuse_Errno.o ../../../src/native/org_catacombae_jfuse_Errno.cpp

${OBJECTDIR}/_ext/Users/erik/devel/git/jfuse/proj/netbeans/libjfuse/../../../src/native/common.o: ../../../src/native/common.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/Users/erik/devel/git/jfuse/proj/netbeans/libjfuse/../../../src/native
	${RM} $@.d
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/Users/erik/devel/git/jfuse/proj/netbeans/libjfuse/../../../src/native/common.o ../../../src/native/common.cpp

${OBJECTDIR}/_ext/Users/erik/devel/git/jfuse/proj/netbeans/libjfuse/../../../src/native/org_catacombae_jfuse_StatConstant.o: ../../../src/native/org_catacombae_jfuse_StatConstant.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/Users/erik/devel/git/jfuse/proj/netbeans/libjfuse/../../../src/native
	${RM} $@.d
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/Users/erik/devel/git/jfuse/proj/netbeans/libjfuse/../../../src/native/org_catacombae_jfuse_StatConstant.o ../../../src/native/org_catacombae_jfuse_StatConstant.cpp

${OBJECTDIR}/_ext/Users/erik/devel/git/jfuse/proj/netbeans/libjfuse/../../../src/native/fuse26_module.o: ../../../src/native/fuse26_module.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/Users/erik/devel/git/jfuse/proj/netbeans/libjfuse/../../../src/native
	${RM} $@.d
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/Users/erik/devel/git/jfuse/proj/netbeans/libjfuse/../../../src/native/fuse26_module.o ../../../src/native/fuse26_module.cpp

${OBJECTDIR}/_ext/Users/erik/devel/git/jfuse/proj/netbeans/libjfuse/../../../src/native/JNIUtil.o: ../../../src/native/JNIUtil.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/Users/erik/devel/git/jfuse/proj/netbeans/libjfuse/../../../src/native
	${RM} $@.d
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/Users/erik/devel/git/jfuse/proj/netbeans/libjfuse/../../../src/native/JNIUtil.o ../../../src/native/JNIUtil.cpp

${OBJECTDIR}/_ext/Users/erik/devel/git/jfuse/proj/netbeans/libjfuse/../../../src/native/org_catacombae_jfuse_FUSEDirFil.o: ../../../src/native/org_catacombae_jfuse_FUSEDirFil.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/Users/erik/devel/git/jfuse/proj/netbeans/libjfuse/../../../src/native
	${RM} $@.d
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/Users/erik/devel/git/jfuse/proj/netbeans/libjfuse/../../../src/native/org_catacombae_jfuse_FUSEDirFil.o ../../../src/native/org_catacombae_jfuse_FUSEDirFil.cpp

${OBJECTDIR}/_ext/Users/erik/devel/git/jfuse/proj/netbeans/libjfuse/../../../src/native/org_catacombae_jfuse_FUSEFillDir.o: ../../../src/native/org_catacombae_jfuse_FUSEFillDir.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/Users/erik/devel/git/jfuse/proj/netbeans/libjfuse/../../../src/native
	${RM} $@.d
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/Users/erik/devel/git/jfuse/proj/netbeans/libjfuse/../../../src/native/org_catacombae_jfuse_FUSEFillDir.o ../../../src/native/org_catacombae_jfuse_FUSEFillDir.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf:
	${RM} -r build/Release
	${RM} dist/Release/${PLATFORM}/liblibjfuse.dylib

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
