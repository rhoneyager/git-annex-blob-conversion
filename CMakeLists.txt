cmake_minimum_required (VERSION 3.1)
# This project needs at least CMake 3.1. If your system
# does not provide this version, you can get it from
# https://cmake.org/download/

# This project requires a C++11 compiler.
project(git-annex-blob-conversion C CXX)

# Global definitions
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS OFF)
SET(CMAKE_POSITION_INDEPENDENT_CODE ON)
include(TestBigEndian)
TEST_BIG_ENDIAN(TEST_ENDIANNESS_RESULT)



add_executable(git-annex-blob-conversion main.cpp sha1.cpp sha1.h README.md LICENSE)

if(TEST_ENDIANNESS_RESULT)
	#set(ENDIAN_PLATFORM "big")
else()
	target_compile_definitions(git-annex-blob-conversion PRIVATE LITTLE_ENDIAN)
	#set(ENDIAN_PLATFORM "little")
endif()
