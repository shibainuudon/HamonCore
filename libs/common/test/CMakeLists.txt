cmake_minimum_required(VERSION 3.20)

set(TARGET_NAME_BASE common)
set(TARGET_NAME hamon_${TARGET_NAME_BASE}_test)
set(TARGET_ALIAS_NAME Hamon::${TARGET_NAME_BASE}_test)

if (TARGET ${TARGET_NAME})
	RETURN()
endif()

add_library(${TARGET_NAME} INTERFACE)
add_library(${TARGET_ALIAS_NAME} ALIAS ${TARGET_NAME})

target_include_directories(${TARGET_NAME} INTERFACE include)

target_precompile_headers(${TARGET_NAME} INTERFACE include/pch.hpp)

option(BUILD_GMOCK "Builds the googlemock subproject" OFF)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../../../externals/googletest ${CMAKE_CURRENT_BINARY_DIR}/googletest)
target_link_libraries(${TARGET_NAME}
  INTERFACE
    GTest::gtest
    GTest::gtest_main)
