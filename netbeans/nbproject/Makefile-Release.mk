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
CND_PLATFORM=GNU-Linux-x86
CND_DLIB_EXT=so
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/1360923845/evolution_assert.o \
	${OBJECTDIR}/_ext/1360923845/evolution_crypto.o \
	${OBJECTDIR}/_ext/1360923845/evolution_debug.o \
	${OBJECTDIR}/_ext/1360923845/evolution_log_file.o \
	${OBJECTDIR}/_ext/761014165/evolution_directory.o \
	${OBJECTDIR}/_ext/761014165/evolution_file.o \
	${OBJECTDIR}/_ext/761014165/evolution_file_function.o \
	${OBJECTDIR}/_ext/761014165/evolution_file_read.o \
	${OBJECTDIR}/_ext/761014165/evolution_file_write.o \
	${OBJECTDIR}/_ext/824854343/evolution_function_base64.o \
	${OBJECTDIR}/_ext/824854343/evolution_function_bit_count.o \
	${OBJECTDIR}/_ext/824854343/evolution_function_bit_swap.o \
	${OBJECTDIR}/_ext/824854343/evolution_function_bit_to_char.o \
	${OBJECTDIR}/_ext/824854343/evolution_function_char_to_wchar.o \
	${OBJECTDIR}/_ext/824854343/evolution_function_string.o \
	${OBJECTDIR}/_ext/824854343/evolution_function_wchar_to_char.o \
	${OBJECTDIR}/_ext/993419216/evolution_memory_dynamic_memory_correction.o \
	${OBJECTDIR}/_ext/993419216/evolution_memory_tlsf_allocator.o \
	${OBJECTDIR}/_ext/993419216/evolution_stack_memory_manager.o \
	${OBJECTDIR}/_ext/1485229518/tlsf.o \
	${OBJECTDIR}/_ext/790105799/evolution_mutex.o \
	${OBJECTDIR}/_ext/790105799/evolution_parameter.o \
	${OBJECTDIR}/_ext/790105799/evolution_result.o \
	${OBJECTDIR}/_ext/790105799/evolution_thread.o \
	${OBJECTDIR}/_ext/790105799/evolution_thread_function.o \
	${OBJECTDIR}/_ext/790105799/evolution_thread_pool.o \
	${OBJECTDIR}/_ext/760597060/evolution_application_counter.o \
	${OBJECTDIR}/_ext/760597060/evolution_stop_watch.o \
	${OBJECTDIR}/_ext/760597060/evolution_timer_factory.o


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
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libevolution-core.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libevolution-core.a: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libevolution-core.a
	${AR} -rv ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libevolution-core.a ${OBJECTFILES} 
	$(RANLIB) ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libevolution-core.a

${OBJECTDIR}/_ext/1360923845/evolution_assert.o: ../etc/evolution_assert.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360923845
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DNODEBUG=1 -D_LINUX=1 -D_X64=1 -Dnullptr=0 -I../.. -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1360923845/evolution_assert.o ../etc/evolution_assert.cpp

${OBJECTDIR}/_ext/1360923845/evolution_crypto.o: ../etc/evolution_crypto.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360923845
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DNODEBUG=1 -D_LINUX=1 -D_X64=1 -Dnullptr=0 -I../.. -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1360923845/evolution_crypto.o ../etc/evolution_crypto.cpp

${OBJECTDIR}/_ext/1360923845/evolution_debug.o: ../etc/evolution_debug.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360923845
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DNODEBUG=1 -D_LINUX=1 -D_X64=1 -Dnullptr=0 -I../.. -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1360923845/evolution_debug.o ../etc/evolution_debug.cpp

${OBJECTDIR}/_ext/1360923845/evolution_log_file.o: ../etc/evolution_log_file.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360923845
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DNODEBUG=1 -D_LINUX=1 -D_X64=1 -Dnullptr=0 -I../.. -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1360923845/evolution_log_file.o ../etc/evolution_log_file.cpp

${OBJECTDIR}/_ext/761014165/evolution_directory.o: ../file/evolution_directory.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/761014165
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DNODEBUG=1 -D_LINUX=1 -D_X64=1 -Dnullptr=0 -I../.. -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/761014165/evolution_directory.o ../file/evolution_directory.cpp

${OBJECTDIR}/_ext/761014165/evolution_file.o: ../file/evolution_file.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/761014165
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DNODEBUG=1 -D_LINUX=1 -D_X64=1 -Dnullptr=0 -I../.. -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/761014165/evolution_file.o ../file/evolution_file.cpp

${OBJECTDIR}/_ext/761014165/evolution_file_function.o: ../file/evolution_file_function.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/761014165
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DNODEBUG=1 -D_LINUX=1 -D_X64=1 -Dnullptr=0 -I../.. -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/761014165/evolution_file_function.o ../file/evolution_file_function.cpp

${OBJECTDIR}/_ext/761014165/evolution_file_read.o: ../file/evolution_file_read.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/761014165
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DNODEBUG=1 -D_LINUX=1 -D_X64=1 -Dnullptr=0 -I../.. -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/761014165/evolution_file_read.o ../file/evolution_file_read.cpp

${OBJECTDIR}/_ext/761014165/evolution_file_write.o: ../file/evolution_file_write.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/761014165
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DNODEBUG=1 -D_LINUX=1 -D_X64=1 -Dnullptr=0 -I../.. -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/761014165/evolution_file_write.o ../file/evolution_file_write.cpp

${OBJECTDIR}/_ext/824854343/evolution_function_base64.o: ../function/evolution_function_base64.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/824854343
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DNODEBUG=1 -D_LINUX=1 -D_X64=1 -Dnullptr=0 -I../.. -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/824854343/evolution_function_base64.o ../function/evolution_function_base64.cpp

${OBJECTDIR}/_ext/824854343/evolution_function_bit_count.o: ../function/evolution_function_bit_count.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/824854343
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DNODEBUG=1 -D_LINUX=1 -D_X64=1 -Dnullptr=0 -I../.. -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/824854343/evolution_function_bit_count.o ../function/evolution_function_bit_count.cpp

${OBJECTDIR}/_ext/824854343/evolution_function_bit_swap.o: ../function/evolution_function_bit_swap.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/824854343
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DNODEBUG=1 -D_LINUX=1 -D_X64=1 -Dnullptr=0 -I../.. -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/824854343/evolution_function_bit_swap.o ../function/evolution_function_bit_swap.cpp

${OBJECTDIR}/_ext/824854343/evolution_function_bit_to_char.o: ../function/evolution_function_bit_to_char.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/824854343
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DNODEBUG=1 -D_LINUX=1 -D_X64=1 -Dnullptr=0 -I../.. -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/824854343/evolution_function_bit_to_char.o ../function/evolution_function_bit_to_char.cpp

${OBJECTDIR}/_ext/824854343/evolution_function_char_to_wchar.o: ../function/evolution_function_char_to_wchar.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/824854343
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DNODEBUG=1 -D_LINUX=1 -D_X64=1 -Dnullptr=0 -I../.. -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/824854343/evolution_function_char_to_wchar.o ../function/evolution_function_char_to_wchar.cpp

${OBJECTDIR}/_ext/824854343/evolution_function_string.o: ../function/evolution_function_string.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/824854343
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DNODEBUG=1 -D_LINUX=1 -D_X64=1 -Dnullptr=0 -I../.. -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/824854343/evolution_function_string.o ../function/evolution_function_string.cpp

${OBJECTDIR}/_ext/824854343/evolution_function_wchar_to_char.o: ../function/evolution_function_wchar_to_char.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/824854343
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DNODEBUG=1 -D_LINUX=1 -D_X64=1 -Dnullptr=0 -I../.. -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/824854343/evolution_function_wchar_to_char.o ../function/evolution_function_wchar_to_char.cpp

${OBJECTDIR}/_ext/993419216/evolution_memory_dynamic_memory_correction.o: ../memory/evolution_memory_dynamic_memory_correction.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/993419216
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DNODEBUG=1 -D_LINUX=1 -D_X64=1 -Dnullptr=0 -I../.. -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/993419216/evolution_memory_dynamic_memory_correction.o ../memory/evolution_memory_dynamic_memory_correction.cpp

${OBJECTDIR}/_ext/993419216/evolution_memory_tlsf_allocator.o: ../memory/evolution_memory_tlsf_allocator.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/993419216
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DNODEBUG=1 -D_LINUX=1 -D_X64=1 -Dnullptr=0 -I../.. -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/993419216/evolution_memory_tlsf_allocator.o ../memory/evolution_memory_tlsf_allocator.cpp

${OBJECTDIR}/_ext/993419216/evolution_stack_memory_manager.o: ../memory/evolution_stack_memory_manager.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/993419216
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DNODEBUG=1 -D_LINUX=1 -D_X64=1 -Dnullptr=0 -I../.. -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/993419216/evolution_stack_memory_manager.o ../memory/evolution_stack_memory_manager.cpp

${OBJECTDIR}/_ext/1485229518/tlsf.o: ../memory/tlsf-3.0/tlsf.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/1485229518
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1485229518/tlsf.o ../memory/tlsf-3.0/tlsf.c

${OBJECTDIR}/_ext/790105799/evolution_mutex.o: ../thread/evolution_mutex.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/790105799
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DNODEBUG=1 -D_LINUX=1 -D_X64=1 -Dnullptr=0 -I../.. -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/790105799/evolution_mutex.o ../thread/evolution_mutex.cpp

${OBJECTDIR}/_ext/790105799/evolution_parameter.o: ../thread/evolution_parameter.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/790105799
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DNODEBUG=1 -D_LINUX=1 -D_X64=1 -Dnullptr=0 -I../.. -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/790105799/evolution_parameter.o ../thread/evolution_parameter.cpp

${OBJECTDIR}/_ext/790105799/evolution_result.o: ../thread/evolution_result.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/790105799
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DNODEBUG=1 -D_LINUX=1 -D_X64=1 -Dnullptr=0 -I../.. -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/790105799/evolution_result.o ../thread/evolution_result.cpp

${OBJECTDIR}/_ext/790105799/evolution_thread.o: ../thread/evolution_thread.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/790105799
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DNODEBUG=1 -D_LINUX=1 -D_X64=1 -Dnullptr=0 -I../.. -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/790105799/evolution_thread.o ../thread/evolution_thread.cpp

${OBJECTDIR}/_ext/790105799/evolution_thread_function.o: ../thread/evolution_thread_function.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/790105799
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DNODEBUG=1 -D_LINUX=1 -D_X64=1 -Dnullptr=0 -I../.. -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/790105799/evolution_thread_function.o ../thread/evolution_thread_function.cpp

${OBJECTDIR}/_ext/790105799/evolution_thread_pool.o: ../thread/evolution_thread_pool.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/790105799
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DNODEBUG=1 -D_LINUX=1 -D_X64=1 -Dnullptr=0 -I../.. -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/790105799/evolution_thread_pool.o ../thread/evolution_thread_pool.cpp

${OBJECTDIR}/_ext/760597060/evolution_application_counter.o: ../time/evolution_application_counter.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/760597060
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DNODEBUG=1 -D_LINUX=1 -D_X64=1 -Dnullptr=0 -I../.. -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/760597060/evolution_application_counter.o ../time/evolution_application_counter.cpp

${OBJECTDIR}/_ext/760597060/evolution_stop_watch.o: ../time/evolution_stop_watch.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/760597060
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DNODEBUG=1 -D_LINUX=1 -D_X64=1 -Dnullptr=0 -I../.. -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/760597060/evolution_stop_watch.o ../time/evolution_stop_watch.cpp

${OBJECTDIR}/_ext/760597060/evolution_timer_factory.o: ../time/evolution_timer_factory.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/760597060
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DNODEBUG=1 -D_LINUX=1 -D_X64=1 -Dnullptr=0 -I../.. -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/760597060/evolution_timer_factory.o ../time/evolution_timer_factory.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libevolution-core.a

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
