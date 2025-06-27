cmake_minimum_required(VERSION 3.20)

set(TARGET_NAME_BASE common_test)

set(TARGET_NAME hamon_${TARGET_NAME_BASE})
set(TARGET_ALIAS_NAME Hamon::${TARGET_NAME_BASE})

if (TARGET ${TARGET_NAME})
	RETURN()
endif()

add_library(${TARGET_NAME} INTERFACE)
add_library(${TARGET_ALIAS_NAME} ALIAS ${TARGET_NAME})

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# /MT[d]
set_property(GLOBAL PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

if (MSVC)
	# /W4 (Warning Level)
	target_compile_options(${TARGET_NAME} INTERFACE /W4)

	# /WX (Treat all warnings as errors)
	target_compile_options(${TARGET_NAME} INTERFACE /WX)

	# /GR- (Disable Run-Time Type Information)
	target_compile_options(${TARGET_NAME} INTERFACE /GR-)

	# /Zi
	target_compile_options(${TARGET_NAME} INTERFACE /Zi)

	# /guard:cf (Enable Control Flow Guard)
	target_compile_options(${TARGET_NAME} INTERFACE /guard:cf)

	# /permissive- (Standards conformance)
	target_compile_options(${TARGET_NAME} INTERFACE /permissive-)

	# /bigobj (Increase Number of Sections in .obj file)
	target_compile_options(${TARGET_NAME} INTERFACE /bigobj)

	# /MP (Build with Multiple Processes)
	if (NOT CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
		target_compile_options(${TARGET_NAME} INTERFACE /MP)
	endif()

elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
	target_compile_options(${TARGET_NAME} INTERFACE -fno-rtti -Wall -Wextra -Wshadow -Wconversion -Wpedantic -Werror)
	target_compile_options(${TARGET_NAME} INTERFACE -Wno-gnu-zero-variadic-macro-arguments)

elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
	target_compile_options(${TARGET_NAME} INTERFACE -fno-rtti -Wall -Wextra -Wshadow -Wconversion -Wpedantic -Werror)
	target_compile_options(${TARGET_NAME} INTERFACE "$<$<CONFIG:Release>:-Wno-aggressive-loop-optimizations>")
	target_compile_options(${TARGET_NAME} INTERFACE "$<$<CONFIG:Release>:-Wno-array-bounds>")
	target_compile_options(${TARGET_NAME} INTERFACE "$<$<CONFIG:Release>:-Wno-maybe-uninitialized>")
	target_compile_options(${TARGET_NAME} INTERFACE "$<$<CONFIG:Release>:-Wno-stringop-overflow>")
	target_compile_options(${TARGET_NAME} INTERFACE "$<$<CONFIG:Release>:-Wno-stringop-overread>")
	target_compile_options(${TARGET_NAME} INTERFACE "$<$<CONFIG:Release>:-Wno-uninitialized>")
endif()

# emscriptenビルドのときは例外を無効にする
if (EMSCRIPTEN)
    if (MSVC)
        # /EHs-c-
        target_compile_options(${TARGET_NAME} INTERFACE /EHs-)
        target_compile_options(${TARGET_NAME} INTERFACE /EHc-)

        # _HAS_EXCEPTIONS
        target_compile_options(${TARGET_NAME} INTERFACE /D_HAS_EXCEPTIONS=0)

    elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
        target_compile_options(${TARGET_NAME} INTERFACE -fno-exceptions)

    elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        target_compile_options(${TARGET_NAME} INTERFACE -fno-exceptions)

    endif()
endif()

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
    set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)
endif()

target_link_libraries(${TARGET_NAME}
    INTERFACE
        GTest::gtest
        GTest::gtest_main)
