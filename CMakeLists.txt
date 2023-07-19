cmake_minimum_required(VERSION 3.20)

set(TARGET_NAME_BASE core)

set(TARGET_NAME hamon_${TARGET_NAME_BASE})
set(TARGET_ALIAS_NAME Hamon::${TARGET_NAME_BASE})

if (TARGET ${TARGET_NAME})
	RETURN()
endif()

project(${TARGET_NAME} LANGUAGES C CXX)

add_library(${TARGET_NAME} INTERFACE)
add_library(${TARGET_ALIAS_NAME} ALIAS ${TARGET_NAME})

add_library(${TARGET_NAME}_test INTERFACE)
add_library(${TARGET_ALIAS_NAME}_test ALIAS ${TARGET_NAME}_test)

set(SUBDIRECTORIES
	algorithm
	any
	array
	base64
	bit
	bitflags
	bitset
	charconv
	cmath
	compare
	complex
	concepts
	config
	cstddef
	cstdint
	cstring
	debug
	functional
	ios
	iterator
	memory
	numbers
	numeric
	optional
	pair
	preprocessor
	qvm
	random
	ranges
	ratio
	serialization
	span
	string
	string_view
	tuple
	type_info
	type_traits
	units
	utility
	variant)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
include(AddSubLibrary)

add_sublibraries(${TARGET_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/libs
	INTERFACE ${SUBDIRECTORIES})

foreach(SUBDIRECTORY ${SUBDIRECTORIES})
	target_link_libraries(${TARGET_NAME}_test INTERFACE Hamon::${SUBDIRECTORY}_test)
endforeach()

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
	if(HAMON_BUILD_TESTING)
		enable_testing()
		add_executable(unit_test)
		target_link_libraries(unit_test PRIVATE ${TARGET_NAME}_test)
		include(GoogleTest)
		gtest_discover_tests(unit_test
			DISCOVERY_TIMEOUT 30
			DISCOVERY_MODE PRE_TEST)
	endif()
endif()
