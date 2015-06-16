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
CND_CONF=Debug
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
	${OBJECTDIR}/_ext/7405130/KeyValueStore.o \
	${OBJECTDIR}/_ext/315475475/NoSQLStore.o \
	${OBJECTDIR}/_ext/1095637251/ipc.o \
	${OBJECTDIR}/_ext/252661366/main.o

# Test Directory
TESTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}/tests

# Test Files
TESTFILES= \
	${TESTDIR}/TestFiles/f1

# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-lboost_unit_test_framework
CXXFLAGS=-lboost_unit_test_framework

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-lboost_system -lboost_timer-mt -lboost_thread-mt -lboost_unit_test_framework

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/nbproj_mac

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/nbproj_mac: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/nbproj_mac ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/_ext/1939253193/Connection.o: /Users/indudinesh/Documents/indu/c++\ workspace/NoSQLDataBase/src/Connection/Connection.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1939253193
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/local/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1939253193/Connection.o /Users/indudinesh/Documents/indu/c++\ workspace/NoSQLDataBase/src/Connection/Connection.cpp

${OBJECTDIR}/_ext/395932884/Item.o: /Users/indudinesh/Documents/indu/c++\ workspace/NoSQLDataBase/src/Item/Item.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/395932884
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/local/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/395932884/Item.o /Users/indudinesh/Documents/indu/c++\ workspace/NoSQLDataBase/src/Item/Item.cpp

${OBJECTDIR}/_ext/7405130/KeyValueStore.o: /Users/indudinesh/Documents/indu/c++\ workspace/NoSQLDataBase/src/KeyValueStore/KeyValueStore.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/7405130
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/local/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/7405130/KeyValueStore.o /Users/indudinesh/Documents/indu/c++\ workspace/NoSQLDataBase/src/KeyValueStore/KeyValueStore.cpp

${OBJECTDIR}/_ext/315475475/NoSQLStore.o: /Users/indudinesh/Documents/indu/c++\ workspace/NoSQLDataBase/src/NoSQLStore/NoSQLStore.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/315475475
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/local/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/315475475/NoSQLStore.o /Users/indudinesh/Documents/indu/c++\ workspace/NoSQLDataBase/src/NoSQLStore/NoSQLStore.cpp

${OBJECTDIR}/_ext/1095637251/ipc.o: /Users/indudinesh/Documents/indu/c++\ workspace/NoSQLDataBase/src/ipc/ipc.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1095637251
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/local/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1095637251/ipc.o /Users/indudinesh/Documents/indu/c++\ workspace/NoSQLDataBase/src/ipc/ipc.cpp

${OBJECTDIR}/_ext/252661366/main.o: /Users/indudinesh/Documents/indu/c++\ workspace/NoSQLDataBase/src/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/252661366
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/local/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/252661366/main.o /Users/indudinesh/Documents/indu/c++\ workspace/NoSQLDataBase/src/main.cpp

# Subprojects
.build-subprojects:

# Build Test Targets
.build-tests-conf: .build-conf ${TESTFILES}
${TESTDIR}/TestFiles/f1: ${TESTDIR}/_ext/650260808/NoSQLDataBaseTest.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc}   -o ${TESTDIR}/TestFiles/f1 $^ ${LDLIBSOPTIONS} -lcunit 


${TESTDIR}/_ext/650260808/NoSQLDataBaseTest.o: /Users/indudinesh/Documents/indu/c++\ workspace/NoSQLDataBase/src/tests/NoSQLDataBaseTest.cpp 
	${MKDIR} -p ${TESTDIR}/_ext/650260808
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/local/include -I. -I. -MMD -MP -MF "$@.d" -o ${TESTDIR}/_ext/650260808/NoSQLDataBaseTest.o /Users/indudinesh/Documents/indu/c++\ workspace/NoSQLDataBase/src/tests/NoSQLDataBaseTest.cpp


${OBJECTDIR}/_ext/1939253193/Connection_nomain.o: ${OBJECTDIR}/_ext/1939253193/Connection.o /Users/indudinesh/Documents/indu/c++\ workspace/NoSQLDataBase/src/Connection/Connection.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1939253193
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/1939253193/Connection.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -I/usr/local/include -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1939253193/Connection_nomain.o /Users/indudinesh/Documents/indu/c++\ workspace/NoSQLDataBase/src/Connection/Connection.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/1939253193/Connection.o ${OBJECTDIR}/_ext/1939253193/Connection_nomain.o;\
	fi

${OBJECTDIR}/_ext/395932884/Item_nomain.o: ${OBJECTDIR}/_ext/395932884/Item.o /Users/indudinesh/Documents/indu/c++\ workspace/NoSQLDataBase/src/Item/Item.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/395932884
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/395932884/Item.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -I/usr/local/include -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/395932884/Item_nomain.o /Users/indudinesh/Documents/indu/c++\ workspace/NoSQLDataBase/src/Item/Item.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/395932884/Item.o ${OBJECTDIR}/_ext/395932884/Item_nomain.o;\
	fi

${OBJECTDIR}/_ext/7405130/KeyValueStore_nomain.o: ${OBJECTDIR}/_ext/7405130/KeyValueStore.o /Users/indudinesh/Documents/indu/c++\ workspace/NoSQLDataBase/src/KeyValueStore/KeyValueStore.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/7405130
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/7405130/KeyValueStore.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -I/usr/local/include -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/7405130/KeyValueStore_nomain.o /Users/indudinesh/Documents/indu/c++\ workspace/NoSQLDataBase/src/KeyValueStore/KeyValueStore.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/7405130/KeyValueStore.o ${OBJECTDIR}/_ext/7405130/KeyValueStore_nomain.o;\
	fi

${OBJECTDIR}/_ext/315475475/NoSQLStore_nomain.o: ${OBJECTDIR}/_ext/315475475/NoSQLStore.o /Users/indudinesh/Documents/indu/c++\ workspace/NoSQLDataBase/src/NoSQLStore/NoSQLStore.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/315475475
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/315475475/NoSQLStore.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -I/usr/local/include -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/315475475/NoSQLStore_nomain.o /Users/indudinesh/Documents/indu/c++\ workspace/NoSQLDataBase/src/NoSQLStore/NoSQLStore.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/315475475/NoSQLStore.o ${OBJECTDIR}/_ext/315475475/NoSQLStore_nomain.o;\
	fi

${OBJECTDIR}/_ext/1095637251/ipc_nomain.o: ${OBJECTDIR}/_ext/1095637251/ipc.o /Users/indudinesh/Documents/indu/c++\ workspace/NoSQLDataBase/src/ipc/ipc.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1095637251
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/1095637251/ipc.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -I/usr/local/include -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1095637251/ipc_nomain.o /Users/indudinesh/Documents/indu/c++\ workspace/NoSQLDataBase/src/ipc/ipc.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/1095637251/ipc.o ${OBJECTDIR}/_ext/1095637251/ipc_nomain.o;\
	fi

${OBJECTDIR}/_ext/252661366/main_nomain.o: ${OBJECTDIR}/_ext/252661366/main.o /Users/indudinesh/Documents/indu/c++\ workspace/NoSQLDataBase/src/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/252661366
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/252661366/main.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -I/usr/local/include -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/252661366/main_nomain.o /Users/indudinesh/Documents/indu/c++\ workspace/NoSQLDataBase/src/main.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/252661366/main.o ${OBJECTDIR}/_ext/252661366/main_nomain.o;\
	fi

# Run Test Targets
.test-conf:
	@if [ "${TEST}" = "" ]; \
	then  \
	    ${TESTDIR}/TestFiles/f1 || true; \
	else  \
	    ./${TEST} || true; \
	fi

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/nbproj_mac

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
