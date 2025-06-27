cmake_minimum_required(VERSION 3.20)

set(TARGET_NAME_BASE detail)

set(TARGET_NAME hamon_${TARGET_NAME_BASE})
set(TARGET_ALIAS_NAME Hamon::${TARGET_NAME_BASE})

if (TARGET ${TARGET_NAME})
	RETURN()
endif()

project(${TARGET_NAME} LANGUAGES C CXX)

add_library(${TARGET_NAME} INTERFACE)
add_library(${TARGET_ALIAS_NAME} ALIAS ${TARGET_NAME})

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../cmake)
include(AddSubLibrary)

add_sublibraries(${TARGET_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/..
	INTERFACE
		config)

option(HAMON_BUILD_TESTING "Build tests" ON)
option(HAMON_COVERAGE "Coverage" OFF)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(CopyFiles)
if (MSVC)
	copy_files(*.natvis ${CMAKE_BINARY_DIR})
endif()

target_include_directories(${TARGET_NAME} INTERFACE ${PROJECT_SOURCE_DIR}/include)
