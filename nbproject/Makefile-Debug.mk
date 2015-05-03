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
CND_PLATFORM=Cygwin_4.x-Windows
CND_DLIB_EXT=dll
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/src/Connection/Connection.o \
	${OBJECTDIR}/src/Item/Item.o \
	${OBJECTDIR}/src/NoSQLStore/NoSQLStore.o \
	${OBJECTDIR}/src/main.o


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
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/nosqldatabase.exe

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/nosqldatabase.exe: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/nosqldatabase ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/src/Connection/Connection.o: src/Connection/Connection.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/Connection
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/cygdrive/C/Program\ Files/boost_1_58_0 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Connection/Connection.o src/Connection/Connection.cpp

${OBJECTDIR}/src/Item/Item.o: src/Item/Item.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/Item
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/cygdrive/C/Program\ Files/boost_1_58_0 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Item/Item.o src/Item/Item.cpp

${OBJECTDIR}/src/NoSQLStore/NoSQLStore.o: src/NoSQLStore/NoSQLStore.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/NoSQLStore
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/cygdrive/C/Program\ Files/boost_1_58_0 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/NoSQLStore/NoSQLStore.o src/NoSQLStore/NoSQLStore.cpp

${OBJECTDIR}/src/main.o: src/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/cygdrive/C/Program\ Files/boost_1_58_0 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/main.o src/main.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/nosqldatabase.exe

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
