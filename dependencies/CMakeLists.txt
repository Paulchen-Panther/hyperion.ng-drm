add_subdirectory(build/hidapi)

if ( ENABLE_TINKERFORGE )
	add_subdirectory(build/tinkerforge)
endif()

if(ENABLE_WS281XPWM)
	add_library(ws281x
		external/rpi_ws281x/mailbox.c external/rpi_ws281x/ws2811.c
		external/rpi_ws281x/pwm.c external/rpi_ws281x/dma.c
		external/rpi_ws281x/pcm.c
		external/rpi_ws281x/rpihw.c)
endif()

#=============================================================================
# FLATBUFFER
#=============================================================================

set(USE_SYSTEM_FLATBUFFERS_LIBS ${DEFAULT_USE_SYSTEM_FLATBUFFERS_LIBS} CACHE BOOL "use flatbuffers library from system")

if (USE_SYSTEM_FLATBUFFERS_LIBS)
	find_program(FLATBUFFERS_FLATC_EXECUTABLE NAMES flatc REQUIRED)
	find_package(Flatbuffers REQUIRED)
else ()
	set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build shared flatbuffers library")
	set(FLATBUFFERS_BUILD_TESTS OFF CACHE BOOL "Build Flatbuffers with tests")
	add_subdirectory(external/flatbuffers)

	if(CMAKE_CROSSCOMPILING)
		# when crosscompiling import the flatc executable targets from a file generated by a native build
		option(IMPORT_FLATC "flatc export file (flatc_export.cmake) from a native build" "IMPORT_FLATC-FILE_NOT_FOUND")
		include(${IMPORT_FLATC})
	else()
		# export the flatc compiler so it can be used when cross compiling
		export(TARGETS flatc FILE "${CMAKE_BINARY_DIR}/flatc_export.cmake")
	endif()

	# define the include for the flatbuffers library at the parent scope
	set(FLATBUFFERS_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/external/flatbuffers/include")

	IF (NOT CMAKE_CROSSCOMPILING)
		# define the flatc executable at the parent scope
		get_property(FLATBUFFERS_FLATC_EXECUTABLE TARGET flatc PROPERTY LOCATION)
	else()
		#Workaround, set flatc comiplier directory hard, as cmake definitions of flatc do not cater for crosscompile correctly.
		#Includ of flatc_export.cmake detects that flatc target is defined aand returns before using the definitions written by export
		set ( FLATBUFFERS_FLATC_EXECUTABLE "${CMAKE_BINARY_DIR}/../build-x86x64/bin/flatc")
	endif()
endif()
set(FLATBUFFERS_FLATC_EXECUTABLE ${FLATBUFFERS_FLATC_EXECUTABLE} PARENT_SCOPE)
set(FLATBUFFERS_INCLUDE_DIRS ${FLATBUFFERS_INCLUDE_DIRS} PARENT_SCOPE)
include_directories(${FLATBUFFERS_INCLUDE_DIRS})


message(STATUS "Using flatbuffers compiler: " ${FLATBUFFERS_FLATC_EXECUTABLE})

function(compile_flattbuffer_schema SRC_FBS OUTPUT_DIR)
	string(REGEX REPLACE "\\.fbs$" "_generated.h" GEN_HEADER ${SRC_FBS})
	set_property(SOURCE ${GEN_HEADER} PROPERTY SKIP_AUTOMOC ON)

	add_custom_command(
		OUTPUT ${GEN_HEADER}
		COMMAND "${FLATBUFFERS_FLATC_EXECUTABLE}" -c --no-includes --gen-mutable
				--gen-object-api
				-o "${OUTPUT_DIR}"
				"${SRC_FBS}"
		DEPENDS "${FLATBUFFERS_FLATC_EXECUTABLE}" ${SRC_FBS})
endfunction()

#=============================================================================
# PROTOBUFFER
#=============================================================================

set(USE_SYSTEM_PROTO_LIBS ${DEFAULT_USE_SYSTEM_PROTO_LIBS} CACHE BOOL "use protobuf library from system")

if (USE_SYSTEM_PROTO_LIBS)
	find_package(Protobuf REQUIRED)
else ()
	set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build shared protobuf library")
	set(protobuf_BUILD_SHARED_LIBS OFF CACHE BOOL "Build protobuf shared")

	if (WIN32)
		set(protobuf_MSVC_STATIC_RUNTIME OFF CACHE BOOL "Build protobuf static")
	endif()

	add_subdirectory(external/protobuf)

	if(CMAKE_CROSSCOMPILING)
		# when crosscompiling import the protoc executable targets from a file generated by a native build
		option(IMPORT_PROTOC "Protoc export file (protoc_export.cmake) from a native build" "IMPORT_PROTOC-FILE_NOT_FOUND")
		include(${IMPORT_PROTOC})
	else()
		# export the protoc compiler so it can be used when cross compiling
		export(TARGETS protoc_compiler FILE "${CMAKE_BINARY_DIR}/protoc_export.cmake")
	endif()

	# define the include for the protobuf library at the parent scope
	set(PROTOBUF_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/external/protobuf/src")

	# define the protoc executable at the parent scope
	get_property(PROTOBUF_PROTOC_EXECUTABLE TARGET protoc_compiler PROPERTY LOCATION)
endif()
option(protobuf_BUILD_TESTS "" OFF)

set(PROTOBUF_PROTOC_EXECUTABLE ${PROTOBUF_PROTOC_EXECUTABLE} PARENT_SCOPE)
set(PROTOBUF_INCLUDE_DIRS ${PROTOBUF_INCLUDE_DIRS} PARENT_SCOPE)
include_directories(${PROTOBUF_INCLUDE_DIRS})

message(STATUS "Using protobuf compiler: " ${PROTOBUF_PROTOC_EXECUTABLE})

#=============================================================================
# Copyright 2009 Kitware, Inc.
# Copyright 2009-2011 Philip Lowman <philip@yhbt.com>
# Copyright 2008 Esben Mose Hansen, Ange Optimization ApS
#
# Distributed under the OSI-approved BSD License (the "License");
# see accompanying file Copyright.txt for details.
#
# This software is distributed WITHOUT ANY WARRANTY; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# See the License for more information.
#=============================================================================
# (To distribute this file outside of CMake, substitute the full
#  License text for the above reference.)
function(PROTOBUF_GENERATE_CPP SRCS HDRS)
	if(NOT ARGN)
		message(SEND_ERROR "Error: PROTOBUF_GENERATE_CPP() called without any proto files")
		return()
	endif()

	if(PROTOBUF_GENERATE_CPP_APPEND_PATH)
		# Create an include path for each file specified
		foreach(FIL ${ARGN})
			get_filename_component(ABS_FIL ${FIL} ABSOLUTE)
			get_filename_component(ABS_PATH ${ABS_FIL} PATH)
			list(FIND _protobuf_include_path ${ABS_PATH} _contains_already)
			if(${_contains_already} EQUAL -1)
				list(APPEND _protobuf_include_path -I ${ABS_PATH})
			endif()
		endforeach()
	else()
		set(_protobuf_include_path -I ${CMAKE_CURRENT_SOURCE_DIR})
	endif()

	if(DEFINED PROTOBUF_IMPORT_DIRS)
		foreach(DIR ${PROTOBUF_IMPORT_DIRS})
			get_filename_component(ABS_PATH ${DIR} ABSOLUTE)
			list(FIND _protobuf_include_path ${ABS_PATH} _contains_already)
			if(${_contains_already} EQUAL -1)
				list(APPEND _protobuf_include_path -I ${ABS_PATH})
			endif()
		endforeach()
	endif()

	if(CMAKE_CROSSCOMPILING OR USE_SYSTEM_PROTO_LIBS)
		set(PROTOC_DEPENDENCY ${PROTOBUF_PROTOC_EXECUTABLE})
	else()
		set(PROTOC_DEPENDENCY protoc_compiler)
	endif()

	set(${SRCS})
	set(${HDRS})
	foreach(FIL ${ARGN})
		get_filename_component(ABS_FIL ${FIL} ABSOLUTE)
		get_filename_component(FIL_WE ${FIL} NAME_WE)

		list(APPEND ${SRCS} "${CMAKE_CURRENT_BINARY_DIR}/${FIL_WE}.pb.cc")
		list(APPEND ${HDRS} "${CMAKE_CURRENT_BINARY_DIR}/${FIL_WE}.pb.h")

		add_custom_command(
			OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/${FIL_WE}.pb.cc"
				   "${CMAKE_CURRENT_BINARY_DIR}/${FIL_WE}.pb.h"
			COMMAND ${PROTOBUF_PROTOC_EXECUTABLE}
			ARGS --cpp_out ${CMAKE_CURRENT_BINARY_DIR} ${_protobuf_include_path} ${ABS_FIL}
			DEPENDS ${ABS_FIL} ${PROTOC_DEPENDENCY}
			COMMENT "Running C++ protocol buffer compiler on ${FIL}"
			VERBATIM
		)
		set_property(SOURCE "${CMAKE_CURRENT_BINARY_DIR}/${FIL_WE}.pb.cc" PROPERTY SKIP_AUTOMOC ON)
		set_property(SOURCE "${CMAKE_CURRENT_BINARY_DIR}/${FIL_WE}.pb.h" PROPERTY SKIP_AUTOMOC ON)
	endforeach()

	set_source_files_properties(${${SRCS}} ${${HDRS}} PROPERTIES GENERATED TRUE)
	set(${SRCS} ${${SRCS}} PARENT_SCOPE)
	set(${HDRS} ${${HDRS}} PARENT_SCOPE)
endfunction()

#=============================================================================
# MBEDTLS
#=============================================================================

set(USE_SYSTEM_MBEDTLS_LIBS ${DEFAULT_USE_SYSTEM_MBEDTLS_LIBS} CACHE BOOL "use mbedtls library from system")

if (USE_SYSTEM_MBEDTLS_LIBS)
	find_package(mbedtls REQUIRED)
	if (NOT MBEDTLS_FOUND)
		message(STATUS "Could NOT find mbedtls system libraries, build static mbedtls libraries")
		#Fallback: build mbedtls static libray inside project
		set(DEFAULT_USE_SYSTEM_MBEDTLS_LIBS OFF PARENT_SCOPE)
		set(USE_SYSTEM_MBEDTLS_LIBS OFF)
	endif (NOT MBEDTLS_FOUND)
endif (USE_SYSTEM_MBEDTLS_LIBS)

if (NOT USE_SYSTEM_MBEDTLS_LIBS)
	set(DEFAULT_USE_SYSTEM_MBEDTLS_LIBS OFF CACHE BOOL "system mbedtls libraries not found, disable use system mbedtls libraries")
	set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build shared mbedtls libraries")

	set(ENABLE_TESTING OFF CACHE BOOL "Disable mbedTLS tests")
	set(ENABLE_PROGRAMS OFF CACHE BOOL "Disable mbedTLS programs")
	set(USE_SHARED_MBEDTLS_LIBRARY OFF CACHE BOOL "Disable mbedTLS shared libraries")
	set(USE_STATIC_MBEDTLS_LIBRARY ON CACHE BOOL "Enable mbedTLS static libraries")

	set(MBEDTLS_DOWNLOAD_DIR "${CMAKE_BINARY_DIR}/dependencies/external/mbedtls/download")
	set(MBEDTLS_SOURCE_DIR "${CMAKE_BINARY_DIR}/dependencies/external/mbedtls/src")
	set(MBEDTLS_BINARY_DIR "${CMAKE_BINARY_DIR}/dependencies/external/mbedtls/build")
	set(MBEDTLS_INSTALL_DIR "${CMAKE_BINARY_DIR}")
	if(${CMAKE_BUILD_TYPE} AND ${CMAKE_BUILD_TYPE} EQUAL "Debug")
		set(MBEDTLS_LOGGING 1)
	else ()
		set(MBEDTLS_LOGGING 0)
	endif ()

	set(MBEDTLS_CMAKE_ARGS
		-DCMAKE_INSTALL_PREFIX:PATH=${MBEDTLS_INSTALL_DIR}
		-DCMAKE_BUILD_TYPE:STRING=${CMAKE_BUILD_TYPE}
		-DUSE_SHARED_MBEDTLS_LIBRARY:BOOL=OFF
		-DUSE_STATIC_MBEDTLS_LIBRARY:BOOL=ON
		-DENABLE_TESTING:BOOL=OFF
		-DENABLE_PROGRAMS:BOOL=OFF
		-DLINK_WITH_PTHREAD:BOOL=ON
		-Wno-dev
		#-DCMAKE_POSITION_INDEPENDENT_CODE:BOOL=TRUE
	)

		if(NOT DEFINED BUILD_MBEDTLS_ONCE)
	 		set(BUILD_MBEDTLS_ONCE CACHE INTERNAL "Done")
			configure_file(${CMAKE_SOURCE_DIR}/dependencies/CMakeLists-mbedtls.txt.in ${MBEDTLS_DOWNLOAD_DIR}/CMakeLists.txt @ONLY)
			execute_process(COMMAND ${CMAKE_COMMAND} -DCMAKE_INSTALL_PREFIX:PATH=${MBEDTLS_INSTALL_DIR} -DCMAKE_BUILD_TYPE:STRING=${CMAKE_BUILD_TYPE} -G "${CMAKE_GENERATOR}" . WORKING_DIRECTORY ${MBEDTLS_DOWNLOAD_DIR})
			execute_process(COMMAND ${CMAKE_COMMAND} --build . WORKING_DIRECTORY ${MBEDTLS_DOWNLOAD_DIR})
			add_subdirectory(${MBEDTLS_SOURCE_DIR} ${MBEDTLS_BINARY_DIR})
	 	endif()

	set (MBEDTLS_INCLUDE_DIR "${MBEDTLS_SOURCE_DIR}/include")
	set (MBEDTLS_INCLUDE_DIR ${MBEDTLS_INCLUDE_DIR} PARENT_SCOPE)
	if (MBEDTLS_INCLUDE_DIR)
		if (EXISTS "${MBEDTLS_INCLUDE_DIR}/mbedtls/build_info.h")
			file(STRINGS ${MBEDTLS_INCLUDE_DIR}/mbedtls/build_info.h _MBEDTLS_VERSION_LINE REGEX "^#define[ \t]+MBEDTLS_VERSION_STRING[\t ].*")
			string(REGEX REPLACE ".*MBEDTLS_VERSION_STRING[\t ]+\"(.*)\"" "\\1" MBEDTLS_VERSION ${_MBEDTLS_VERSION_LINE})
			set (MBEDTLS_VERSION ${MBEDTLS_VERSION} PARENT_SCOPE)
			message(STATUS "Using static mbedtls libraries (build version \"${MBEDTLS_VERSION}\")")
		elseif(EXISTS "${MBEDTLS_INCLUDE_DIR}/mbedtls/version.h")
			file(STRINGS "${MBEDTLS_INCLUDE_DIR}/mbedtls/version.h" _MBEDTLS_VERSION_STRING REGEX "^#[\t ]*define[\t ]+MBEDTLS_VERSION_STRING[\t ]+\"[0-9]+.[0-9]+.[0-9]+\"")
			string(REGEX REPLACE "^.*MBEDTLS_VERSION_STRING.*([0-9]+.[0-9]+.[0-9]+).*" "\\1" MBEDTLS_VERSION "${_MBEDTLS_VERSION_STRING}")
			set (MBEDTLS_VERSION ${MBEDTLS_VERSION} PARENT_SCOPE)
			message(STATUS "Using static mbedtls libraries (build version \"${MBEDTLS_VERSION}\")")
		endif()
	endif ()

	include_directories(${MBEDTLS_INCLUDE_DIR})

	if(WIN32)
		set (MBEDTLS_LIB_INSTALL_DIR_WITH_LIB_PREFIX "${MBEDTLS_INSTALL_DIR}/lib/${CMAKE_CFG_INTDIR}/")
	else()
		set (MBEDTLS_LIB_INSTALL_DIR_WITH_LIB_PREFIX "${MBEDTLS_INSTALL_DIR}/lib/${CMAKE_STATIC_LIBRARY_PREFIX}")
	endif ()

	set (MBEDTLS_SSL_LIBRARY "${MBEDTLS_LIB_INSTALL_DIR_WITH_LIB_PREFIX}mbedtls${CMAKE_STATIC_LIBRARY_SUFFIX}")
	set (MBEDTLS_X509_LIBRARY "${MBEDTLS_LIB_INSTALL_DIR_WITH_LIB_PREFIX}mbedx509${CMAKE_STATIC_LIBRARY_SUFFIX}")
	set (MBEDTLS_CRYPTO_LIBRARY "${MBEDTLS_LIB_INSTALL_DIR_WITH_LIB_PREFIX}mbedcrypto${CMAKE_STATIC_LIBRARY_SUFFIX}")
	set (MBEDTLS_LIBRARIES ${MBEDTLS_SSL_LIBRARY} ${MBEDTLS_X509_LIBRARY} ${MBEDTLS_CRYPTO_LIBRARY})
	set (MBEDTLS_LIBRARIES ${MBEDTLS_LIBRARIES} PARENT_SCOPE)

	if(${CMAKE_BUILD_TYPE} AND ${CMAKE_BUILD_TYPE} EQUAL "Debug")
		message(STATUS "mbedtls libraries: ${MBEDTLS_LIBRARIES}")
	endif ()

	mark_as_advanced (MBEDTLS_INCLUDE_DIR MBEDTLS_LIBRARIES MBEDTLS_SSL_LIBRARY MBEDTLS_X509_LIBRARY MBEDTLS_CRYPTO_LIBRARY)

endif (NOT USE_SYSTEM_MBEDTLS_LIBS)

#=============================================================================
# LIBYUV
#=============================================================================

add_subdirectory(external/libyuv)
set(LibYUV_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/external/libyuv/include")
set(LibYUV_INCLUDE_DIRS ${LibYUV_INCLUDE_DIRS} PARENT_SCOPE)
set(LibYUV_LIBRARIES "${CMAKE_BINARY_DIR}/lib/${CMAKE_STATIC_LIBRARY_PREFIX}yuv${CMAKE_STATIC_LIBRARY_SUFFIX}" PARENT_SCOPE)
include_directories(${LibYUV_INCLUDE_DIRS})
