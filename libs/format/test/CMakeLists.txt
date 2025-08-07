cmake_minimum_required(VERSION 3.20)

set(TARGET_NAME_BASE format)
set(TARGET_NAME hamon_${TARGET_NAME_BASE}_test)
set(TARGET_ALIAS_NAME Hamon::${TARGET_NAME_BASE}_test)

add_library(${TARGET_NAME} INTERFACE)
add_library(${TARGET_ALIAS_NAME} ALIAS ${TARGET_NAME})

file(GLOB_RECURSE test_sources CONFIGURE_DEPENDS src/*)
target_sources(${TARGET_NAME} INTERFACE ${test_sources})
target_include_directories(${TARGET_NAME} INTERFACE src)
target_link_libraries(${TARGET_NAME}
	INTERFACE
		Hamon::${TARGET_NAME_BASE})

add_sublibraries(${TARGET_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/../..
	INTERFACE
		algorithm
		array
		bitset
		chrono
		complex
		concepts
		cstddef
		cstdint
		deque
		detail
		flat_map
		flat_set
		forward_list
		iterator
		limits
		list
		map
		memory
		optional
		pair
		queue
		set
		span
		stack
		string
		string_view
		system_error
		tuple
		unordered_map
		unordered_set
		utility
		valarray
		variant
		vector
		common_test)
