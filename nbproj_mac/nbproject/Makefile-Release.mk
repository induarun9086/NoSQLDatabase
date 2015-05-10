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
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-MacOSX
CND_DLIB_EXT=dylib
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/1939253193/Connection.o \
	${OBJECTDIR}/_ext/395932884/Item.o \
	${OBJECTDIR}/_ext/315475475/NoSQLStore.o \
	${OBJECTDIR}/_ext/1095637251/ipc.o \
	${OBJECTDIR}/_ext/252661366/main.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/nbproj_mac

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/nbproj_mac: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/nbproj_mac ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/_ext/1939253193/Connection.o: /Users/indudinesh/Documents/indu/c++\ workspace/NoSQLDataBase/src/Connection/Connection.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1939253193
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1939253193/Connection.o /Users/indudinesh/Documents/indu/c++\ workspace/NoSQLDataBase/src/Connection/Connection.cpp

${OBJECTDIR}/_ext/395932884/Item.o: /Users/indudinesh/Documents/indu/c++\ workspace/NoSQLDataBase/src/Item/Item.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/395932884
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/395932884/Item.o /Users/indudinesh/Documents/indu/c++\ workspace/NoSQLDataBase/src/Item/Item.cpp

${OBJECTDIR}/_ext/315475475/NoSQLStore.o: /Users/indudinesh/Documents/indu/c++\ workspace/NoSQLDataBase/src/NoSQLStore/NoSQLStore.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/315475475
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/315475475/NoSQLStore.o /Users/indudinesh/Documents/indu/c++\ workspace/NoSQLDataBase/src/NoSQLStore/NoSQLStore.cpp

${OBJECTDIR}/_ext/1095637251/ipc.o: /Users/indudinesh/Documents/indu/c++\ workspace/NoSQLDataBase/src/ipc/ipc.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1095637251
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1095637251/ipc.o /Users/indudinesh/Documents/indu/c++\ workspace/NoSQLDataBase/src/ipc/ipc.cpp

${OBJECTDIR}/_ext/252661366/main.o: /Users/indudinesh/Documents/indu/c++\ workspace/NoSQLDataBase/src/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/252661366
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/252661366/main.o /Users/indudinesh/Documents/indu/c++\ workspace/NoSQLDataBase/src/main.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/nbproj_mac

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
