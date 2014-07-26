cmake_minimum_required(VERSION 2.8)
project(microGL)
include(ExternalProject)

set(microGL_INSTALL_DIR "${microGL_SOURCE_DIR}/bin")
# Use modified FindSDL2 and FindGLEW that will work with my windows setup
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${microGL_SOURCE_DIR}/cmake")

# Bump up warning levels appropriately for each compiler
if (${CMAKE_C_COMPILER_ID} STREQUAL "GNU" OR ${CMAKE_C_COMPILER_ID} STREQUAL "Clang")
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -pedantic -ggdb -std=c99")
elseif (${CMAKE_C_COMPILER_ID} STREQUAL "MSVC")
	if(CMAKE_C_FLAGS MATCHES "/W[0-4]")
		string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /Zi")
	else()
		set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /W4 /Zi")
	endif()
endif()

find_package(SDL2 REQUIRED)

include_directories(include ${SDL2_INCLUDE_DIR})
add_subdirectory(src)

