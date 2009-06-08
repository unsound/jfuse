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
	${OBJECTDIR}/_ext/Users/erik/devel/jFUSE/proj/netbeans/libjfuse/../../../src/native/fuse_module.o \
	${OBJECTDIR}/_ext/Users/erik/devel/jFUSE/proj/netbeans/libjfuse/../../../src/native/org_catacombae_jfuse_FUSEFillDir.o \
	${OBJECTDIR}/_ext/Users/erik/devel/jFUSE/proj/netbeans/libjfuse/../../../src/native/libjfuse/jfuse.o \
	${OBJECTDIR}/_ext/Users/erik/devel/jFUSE/proj/netbeans/libjfuse/../../../src/native/FUSEFillDirContext.o \
	${OBJECTDIR}/_ext/Users/erik/devel/jFUSE/proj/netbeans/libjfuse/../../../src/native/JNIModule.o

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
	${MAKE}  -f nbproject/Makefile-Debug.mk dist/Debug/${PLATFORM}/liblibjfuse.dylib

dist/Debug/${PLATFORM}/liblibjfuse.dylib: ${OBJECTFILES}
	${MKDIR} -p dist/Debug/${PLATFORM}
	${LINK.cc} -dynamiclib -install_name liblibjfuse.dylib -o dist/Debug/${PLATFORM}/liblibjfuse.dylib -fPIC ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/_ext/Users/erik/devel/jFUSE/proj/netbeans/libjfuse/../../../src/native/fuse_module.o: ../../../src/native/fuse_module.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/Users/erik/devel/jFUSE/proj/netbeans/libjfuse/../../../src/native
	${RM} $@.d
	$(COMPILE.cc) -g -I/System/Library/Frameworks/JavaVM.framework/Headers -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/Users/erik/devel/jFUSE/proj/netbeans/libjfuse/../../../src/native/fuse_module.o ../../../src/native/fuse_module.cpp

${OBJECTDIR}/_ext/Users/erik/devel/jFUSE/proj/netbeans/libjfuse/../../../src/native/org_catacombae_jfuse_FUSEFillDir.o: ../../../src/native/org_catacombae_jfuse_FUSEFillDir.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/Users/erik/devel/jFUSE/proj/netbeans/libjfuse/../../../src/native
	${RM} $@.d
	$(COMPILE.cc) -g -I/System/Library/Frameworks/JavaVM.framework/Headers -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/Users/erik/devel/jFUSE/proj/netbeans/libjfuse/../../../src/native/org_catacombae_jfuse_FUSEFillDir.o ../../../src/native/org_catacombae_jfuse_FUSEFillDir.cpp

${OBJECTDIR}/_ext/Users/erik/devel/jFUSE/proj/netbeans/libjfuse/../../../src/native/libjfuse/jfuse.o: ../../../src/native/libjfuse/jfuse.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/Users/erik/devel/jFUSE/proj/netbeans/libjfuse/../../../src/native/libjfuse
	${RM} $@.d
	$(COMPILE.c) -g -I/System/Library/Frameworks/JavaVM.framework/Headers -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/Users/erik/devel/jFUSE/proj/netbeans/libjfuse/../../../src/native/libjfuse/jfuse.o ../../../src/native/libjfuse/jfuse.c

${OBJECTDIR}/_ext/Users/erik/devel/jFUSE/proj/netbeans/libjfuse/../../../src/native/FUSEFillDirContext.o: ../../../src/native/FUSEFillDirContext.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/Users/erik/devel/jFUSE/proj/netbeans/libjfuse/../../../src/native
	${RM} $@.d
	$(COMPILE.cc) -g -I/System/Library/Frameworks/JavaVM.framework/Headers -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/Users/erik/devel/jFUSE/proj/netbeans/libjfuse/../../../src/native/FUSEFillDirContext.o ../../../src/native/FUSEFillDirContext.cpp

${OBJECTDIR}/_ext/Users/erik/devel/jFUSE/proj/netbeans/libjfuse/../../../src/native/JNIModule.o: ../../../src/native/JNIModule.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/Users/erik/devel/jFUSE/proj/netbeans/libjfuse/../../../src/native
	${RM} $@.d
	$(COMPILE.cc) -g -I/System/Library/Frameworks/JavaVM.framework/Headers -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/Users/erik/devel/jFUSE/proj/netbeans/libjfuse/../../../src/native/JNIModule.o ../../../src/native/JNIModule.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf:
	${RM} -r build/Debug
	${RM} dist/Debug/${PLATFORM}/liblibjfuse.dylib

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
