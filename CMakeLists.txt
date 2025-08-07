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

set(SUBDIRECTORIES
	algorithm
	any
	array
	atomic
	base64
	bigint
	bit
	bitflags
	bitset
	charconv
	chrono
	cmath
	compare
	complex
	concepts
	config
	container
	cstddef
	cstdint
	cstdlib
	cstring
	debug
	deque
	expected
	flat_map
	flat_set
	format
	forward_list
	functional
	inplace_vector
	iomanip
	ios
	iterator
	limits
	list
	map
	memory
	memory_resource
	mutex
	new
	numbers
	numeric
	optional
	pair
	preprocessor
	queue
	qvm
	random
	ranges
	ratio
	scoped_allocator
	serialization
	set
	shared_mutex
	span
	stack
	static_typeinfo
	stdexcept
	string
	string_view
	system_error
	tuple
	type_traits
	units
	unordered_map
	unordered_set
	utility
	valarray
	variant
	vector)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
include(AddSubLibrary)

add_sublibraries(${TARGET_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/libs
	INTERFACE ${SUBDIRECTORIES})

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
	if(HAMON_BUILD_TESTING)
		add_library(${TARGET_NAME}_test INTERFACE)
		add_library(${TARGET_ALIAS_NAME}_test ALIAS ${TARGET_NAME}_test)

		foreach(SUBDIRECTORY ${SUBDIRECTORIES})
			add_subdirectory(libs/${SUBDIRECTORY}/test)
			target_link_libraries(${TARGET_NAME}_test INTERFACE Hamon::${SUBDIRECTORY}_test)
		endforeach()

		enable_testing()
		add_executable(unit_test)
		target_link_libraries(unit_test PRIVATE ${TARGET_NAME}_test)
		include(GoogleTest)
		gtest_discover_tests(unit_test
			DISCOVERY_TIMEOUT 30
			DISCOVERY_MODE PRE_TEST)
	endif()
endif()
