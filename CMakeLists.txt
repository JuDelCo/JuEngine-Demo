
# Copyright (c) 2016 Juan Delgado (JuDelCo)
# License: GPLv3 License
# GPLv3 License web page: http://www.gnu.org/licenses/gpl.txt

# ----------------------------------------------------------------------------------------------

cmake_minimum_required(VERSION 3.0)

if(NOT CONFIGURED_ONCE)
	set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Debug Release RelWithDebInfo MinSizeRel" FORCE)
	set(BUILD_CPU_ARCH   "x64"   CACHE STRING "x86 x64") # x64 by default UNIX, x86 by default in WIN32 !
endif()

if( NOT ${CMAKE_BUILD_TYPE} STREQUAL "Debug" AND
	NOT ${CMAKE_BUILD_TYPE} STREQUAL "Release" AND
	NOT ${CMAKE_BUILD_TYPE} STREQUAL "RelWithDebInfo" AND
	NOT ${CMAKE_BUILD_TYPE} STREQUAL "MinSizeRel")
	message(FATAL_ERROR "Bad CMAKE_BUILD_TYPE variable value (Debug Release RelWithDebInfo MinSizeRel)")
endif()

if( NOT ${BUILD_CPU_ARCH} STREQUAL "x86" AND
	NOT ${BUILD_CPU_ARCH} STREQUAL "x64")
	message(FATAL_ERROR "Bad BUILD_CPU_ARCH variable value (x86 x64)")
endif()

message(STATUS "CMAKE_BUILD_CONFIG: ${CMAKE_BUILD_TYPE} (${BUILD_CPU_ARCH})")

# -------------------------------------------------------------------------------------------------

set(CMAKE_CXX_FLAGS         "-Wall -Werror -fmax-errors=5 -std=c++11")
set(CMAKE_CXX_FLAGS_DEBUG   "-gdwarf-2 -Og -DDEBUG_ON") # -g
set(CMAKE_CXX_FLAGS_RELEASE "-s -O2")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR})

set(EXECUTABLE_NAME Game_${CMAKE_BUILD_TYPE}_${BUILD_CPU_ARCH})
file(GLOB_RECURSE GAME_SRC Game/*.*pp)
file(GLOB_RECURSE TEST_SRC Tests/*.*pp)

if(${BUILD_CPU_ARCH} STREQUAL "x64")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m64")
else()
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m32")
endif()

if(UNIX)
	set(LINK_FLAGS "-Wl,-rpath,./Libraries")

	set(GLM_PATH "/home/judelco/Projects/Libraries/glm-0.9.7.1")
	set(JUENGINE_PATH "/home/judelco/Projects/JuEngine/bin/${CMAKE_BUILD_TYPE}_${BUILD_CPU_ARCH}")
	set(JUENGINE_DLL "${JUENGINE_PATH}/lib/libJuEngine.so")
elseif(WIN32)
	set(LINK_FLAGS
		"-lopengl32"
		"-lwinmm"
	)

	if(${BUILD_CPU_ARCH} STREQUAL "x64")
		set(LINK_FLAGS ${LINK_FLAGS}
			"-lmingw32"
		)
	endif()

	set(LINK_FLAGS ${LINK_FLAGS}
		"-static-libgcc"
		"-static-libstdc++"
	)

	if(CMAKE_BUILD_TYPE STREQUAL "Release")
		set(LINK_FLAGS ${LINK_FLAGS}
			"-mwindows" # hide console
		)
	endif()

	set(GLM_PATH "C:/Programacion/CppLibs/GLM-0.9.6.1")
	set(JUENGINE_PATH "C:/Programacion/JuEngine/bin/${CMAKE_BUILD_TYPE}_${BUILD_CPU_ARCH}")
	set(JUENGINE_DLL "${JUENGINE_PATH}/lib/libJuEngine.dll")
endif()

# -------------------------------------------------------------------------------------------------

project(JuEngine_Game CXX)

include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}
	${GLM_PATH}/include
	${JUENGINE_PATH}/include
)

link_directories(
	${JUENGINE_PATH}/lib
)

add_executable(${EXECUTABLE_NAME}
	main.cpp
	${GAME_SRC}
	${TEST_SRC}
)

target_link_libraries(${EXECUTABLE_NAME}
	${LINK_FLAGS}
	JuEngine
)

# -------------------------------------------------------------------------------------------------

install(FILES ${JUENGINE_DLL} DESTINATION ${CMAKE_SOURCE_DIR}/bin/Libraries)

#add_custom_command(TARGET JuEngine_Game POST_BUILD
#	COMMAND "echo."
#	COMMAND "${EXECUTABLE_NAME}"
#	COMMAND "echo."
#	WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
#	COMMENT "Running ${EXECUTABLE_NAME}" VERBATIM)

# -------------------------------------------------------------------------------------------------

set(CONFIGURED_ONCE TRUE CACHE INTERNAL "Flag - CMake has configured at least once")
