cmake_minimum_required(VERSION 3.20)

set(TARGET_NAME_BASE common)

set(TARGET_NAME hamon_${TARGET_NAME_BASE})
set(TARGET_ALIAS_NAME Hamon::${TARGET_NAME_BASE})

if (TARGET ${TARGET_NAME})
	RETURN()
endif()

project(${TARGET_NAME} LANGUAGES C CXX)

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
endif()

add_subdirectory(test)
