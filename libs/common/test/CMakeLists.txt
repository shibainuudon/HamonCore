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

find_package(GTest)
if (NOT ${GTest_FOUND})
  include(FetchContent)
  FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/hogletgames/googletest.git
    GIT_TAG 5376968f6948923e2411081fd9372e71a59d8e77 # release-1.12.0
  )
  FetchContent_MakeAvailable(googletest)
endif()

target_link_libraries(${TARGET_NAME}
  INTERFACE
    GTest::gtest
    GTest::gtest_main)
