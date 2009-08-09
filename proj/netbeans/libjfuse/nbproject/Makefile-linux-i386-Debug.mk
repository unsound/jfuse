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
CND_PLATFORM=GNU-Linux-x86
CND_CONF=linux-i386-Debug
CND_DISTDIR=dist

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=build/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/libjfuse/src/org_catacombae_jfuse_types_system_StatConstant.o \
	${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/libjfuse/src/org_catacombae_jfuse_FUSE_26.o \
	${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/libjfuse/src/FUSEFillDirContext.o \
	${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/libjfuse/src/common.o \
	${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/libjfuse/src/MacFUSE20Util.o \
	${OBJECTDIR}/_ext/Users/erik/devel/git/jfuse/libjfuse/src/org_catacombae_jfuse_types_system_NumericalConstant.o \
	${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/libjfuse/src/org_catacombae_jfuse_types_fuse26_FUSEDirFil.o \
	${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/libjfuse/src/FUSE26Util.o \
	${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/libjfuse/src/org_catacombae_jfuse_util_FUSEUtil.o \
	${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/libjfuse/src/JNIUtil.o \
	${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/libjfuse/src/fuse26_module.o \
	${OBJECTDIR}/_ext/Users/erik/devel/git/jfuse/libjfuse/src/org_catacombae_jfuse_types_system_StringConstant.o \
	${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/libjfuse/src/org_catacombae_jfuse_types_fuse26_FUSEFillDir.o \
	${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/libjfuse/src/jFUSEContext.o \
	${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/libjfuse/src/FUSEDirFilContext.o \
	${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/libjfuse/src/macfuse20_module.o \
	${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/libjfuse/src/org_catacombae_jfuse_types_system_Errno.o \
	${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/libjfuse/src/org_catacombae_jfuse_JNILoader.o

# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-m32
CXXFLAGS=-m32

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-lfuse

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	${MAKE}  -f nbproject/Makefile-linux-i386-Debug.mk dist/linux-i386-Debug/libjfuse.so

dist/linux-i386-Debug/libjfuse.so: ${OBJECTFILES}
	${MKDIR} -p dist/linux-i386-Debug
	${LINK.cc} -shared -o dist/linux-i386-Debug/libjfuse.so -fPIC ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/libjfuse/src/org_catacombae_jfuse_types_system_StatConstant.o: nbproject/Makefile-${CND_CONF}.mk ../../../libjfuse/src/org_catacombae_jfuse_types_system_StatConstant.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/libjfuse/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -D_FILE_OFFSET_BITS=64 -I../../../libjfuse/include -I/usr/lib/jvm/default-java/include -I/usr/include/fuse -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/libjfuse/src/org_catacombae_jfuse_types_system_StatConstant.o ../../../libjfuse/src/org_catacombae_jfuse_types_system_StatConstant.cpp

${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/libjfuse/src/org_catacombae_jfuse_FUSE_26.o: nbproject/Makefile-${CND_CONF}.mk ../../../libjfuse/src/org_catacombae_jfuse_FUSE_26.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/libjfuse/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -D_FILE_OFFSET_BITS=64 -I../../../libjfuse/include -I/usr/lib/jvm/default-java/include -I/usr/include/fuse -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/libjfuse/src/org_catacombae_jfuse_FUSE_26.o ../../../libjfuse/src/org_catacombae_jfuse_FUSE_26.cpp

${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/libjfuse/src/FUSEFillDirContext.o: nbproject/Makefile-${CND_CONF}.mk ../../../libjfuse/src/FUSEFillDirContext.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/libjfuse/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -D_FILE_OFFSET_BITS=64 -I../../../libjfuse/include -I/usr/lib/jvm/default-java/include -I/usr/include/fuse -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/libjfuse/src/FUSEFillDirContext.o ../../../libjfuse/src/FUSEFillDirContext.cpp

${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/libjfuse/src/common.o: nbproject/Makefile-${CND_CONF}.mk ../../../libjfuse/src/common.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/libjfuse/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -D_FILE_OFFSET_BITS=64 -I../../../libjfuse/include -I/usr/lib/jvm/default-java/include -I/usr/include/fuse -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/libjfuse/src/common.o ../../../libjfuse/src/common.cpp

${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/libjfuse/src/MacFUSE20Util.o: nbproject/Makefile-${CND_CONF}.mk ../../../libjfuse/src/MacFUSE20Util.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/libjfuse/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -D_FILE_OFFSET_BITS=64 -I../../../libjfuse/include -I/usr/lib/jvm/default-java/include -I/usr/include/fuse -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/libjfuse/src/MacFUSE20Util.o ../../../libjfuse/src/MacFUSE20Util.cpp

${OBJECTDIR}/_ext/Users/erik/devel/git/jfuse/libjfuse/src/org_catacombae_jfuse_types_system_NumericalConstant.o: nbproject/Makefile-${CND_CONF}.mk /Users/erik/devel/git/jfuse/libjfuse/src/org_catacombae_jfuse_types_system_NumericalConstant.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/Users/erik/devel/git/jfuse/libjfuse/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -D_FILE_OFFSET_BITS=64 -I../../../libjfuse/include -I/usr/lib/jvm/default-java/include -I/usr/include/fuse -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/Users/erik/devel/git/jfuse/libjfuse/src/org_catacombae_jfuse_types_system_NumericalConstant.o /Users/erik/devel/git/jfuse/libjfuse/src/org_catacombae_jfuse_types_system_NumericalConstant.cpp

${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/libjfuse/src/org_catacombae_jfuse_types_fuse26_FUSEDirFil.o: nbproject/Makefile-${CND_CONF}.mk ../../../libjfuse/src/org_catacombae_jfuse_types_fuse26_FUSEDirFil.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/libjfuse/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -D_FILE_OFFSET_BITS=64 -I../../../libjfuse/include -I/usr/lib/jvm/default-java/include -I/usr/include/fuse -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/libjfuse/src/org_catacombae_jfuse_types_fuse26_FUSEDirFil.o ../../../libjfuse/src/org_catacombae_jfuse_types_fuse26_FUSEDirFil.cpp

${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/libjfuse/src/FUSE26Util.o: nbproject/Makefile-${CND_CONF}.mk ../../../libjfuse/src/FUSE26Util.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/libjfuse/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -D_FILE_OFFSET_BITS=64 -I../../../libjfuse/include -I/usr/lib/jvm/default-java/include -I/usr/include/fuse -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/libjfuse/src/FUSE26Util.o ../../../libjfuse/src/FUSE26Util.cpp

${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/libjfuse/src/org_catacombae_jfuse_util_FUSEUtil.o: nbproject/Makefile-${CND_CONF}.mk ../../../libjfuse/src/org_catacombae_jfuse_util_FUSEUtil.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/libjfuse/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -D_FILE_OFFSET_BITS=64 -I../../../libjfuse/include -I/usr/lib/jvm/default-java/include -I/usr/include/fuse -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/libjfuse/src/org_catacombae_jfuse_util_FUSEUtil.o ../../../libjfuse/src/org_catacombae_jfuse_util_FUSEUtil.cpp

${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/libjfuse/src/JNIUtil.o: nbproject/Makefile-${CND_CONF}.mk ../../../libjfuse/src/JNIUtil.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/libjfuse/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -D_FILE_OFFSET_BITS=64 -I../../../libjfuse/include -I/usr/lib/jvm/default-java/include -I/usr/include/fuse -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/libjfuse/src/JNIUtil.o ../../../libjfuse/src/JNIUtil.cpp

${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/libjfuse/src/fuse26_module.o: nbproject/Makefile-${CND_CONF}.mk ../../../libjfuse/src/fuse26_module.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/libjfuse/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -D_FILE_OFFSET_BITS=64 -I../../../libjfuse/include -I/usr/lib/jvm/default-java/include -I/usr/include/fuse -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/libjfuse/src/fuse26_module.o ../../../libjfuse/src/fuse26_module.cpp

${OBJECTDIR}/_ext/Users/erik/devel/git/jfuse/libjfuse/src/org_catacombae_jfuse_types_system_StringConstant.o: nbproject/Makefile-${CND_CONF}.mk /Users/erik/devel/git/jfuse/libjfuse/src/org_catacombae_jfuse_types_system_StringConstant.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/Users/erik/devel/git/jfuse/libjfuse/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -D_FILE_OFFSET_BITS=64 -I../../../libjfuse/include -I/usr/lib/jvm/default-java/include -I/usr/include/fuse -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/Users/erik/devel/git/jfuse/libjfuse/src/org_catacombae_jfuse_types_system_StringConstant.o /Users/erik/devel/git/jfuse/libjfuse/src/org_catacombae_jfuse_types_system_StringConstant.cpp

${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/libjfuse/src/org_catacombae_jfuse_types_fuse26_FUSEFillDir.o: nbproject/Makefile-${CND_CONF}.mk ../../../libjfuse/src/org_catacombae_jfuse_types_fuse26_FUSEFillDir.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/libjfuse/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -D_FILE_OFFSET_BITS=64 -I../../../libjfuse/include -I/usr/lib/jvm/default-java/include -I/usr/include/fuse -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/libjfuse/src/org_catacombae_jfuse_types_fuse26_FUSEFillDir.o ../../../libjfuse/src/org_catacombae_jfuse_types_fuse26_FUSEFillDir.cpp

${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/libjfuse/src/jFUSEContext.o: nbproject/Makefile-${CND_CONF}.mk ../../../libjfuse/src/jFUSEContext.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/libjfuse/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -D_FILE_OFFSET_BITS=64 -I../../../libjfuse/include -I/usr/lib/jvm/default-java/include -I/usr/include/fuse -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/libjfuse/src/jFUSEContext.o ../../../libjfuse/src/jFUSEContext.cpp

${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/libjfuse/src/FUSEDirFilContext.o: nbproject/Makefile-${CND_CONF}.mk ../../../libjfuse/src/FUSEDirFilContext.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/libjfuse/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -D_FILE_OFFSET_BITS=64 -I../../../libjfuse/include -I/usr/lib/jvm/default-java/include -I/usr/include/fuse -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/libjfuse/src/FUSEDirFilContext.o ../../../libjfuse/src/FUSEDirFilContext.cpp

${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/libjfuse/src/macfuse20_module.o: nbproject/Makefile-${CND_CONF}.mk ../../../libjfuse/src/macfuse20_module.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/libjfuse/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -D_FILE_OFFSET_BITS=64 -I../../../libjfuse/include -I/usr/lib/jvm/default-java/include -I/usr/include/fuse -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/libjfuse/src/macfuse20_module.o ../../../libjfuse/src/macfuse20_module.cpp

${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/libjfuse/src/org_catacombae_jfuse_types_system_Errno.o: nbproject/Makefile-${CND_CONF}.mk ../../../libjfuse/src/org_catacombae_jfuse_types_system_Errno.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/libjfuse/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -D_FILE_OFFSET_BITS=64 -I../../../libjfuse/include -I/usr/lib/jvm/default-java/include -I/usr/include/fuse -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/libjfuse/src/org_catacombae_jfuse_types_system_Errno.o ../../../libjfuse/src/org_catacombae_jfuse_types_system_Errno.cpp

${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/libjfuse/src/org_catacombae_jfuse_JNILoader.o: nbproject/Makefile-${CND_CONF}.mk ../../../libjfuse/src/org_catacombae_jfuse_JNILoader.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/libjfuse/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -D_FILE_OFFSET_BITS=64 -I../../../libjfuse/include -I/usr/lib/jvm/default-java/include -I/usr/include/fuse -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/_DOTDOT/_DOTDOT/_DOTDOT/libjfuse/src/org_catacombae_jfuse_JNILoader.o ../../../libjfuse/src/org_catacombae_jfuse_JNILoader.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf:
	${RM} -r build/linux-i386-Debug
	${RM} dist/linux-i386-Debug/libjfuse.so

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
