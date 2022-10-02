/**
 *	@file	config.hpp
 *
 *	@brief
 */

#ifndef HAMON_COMPARE_CONFIG_HPP
#define HAMON_COMPARE_CONFIG_HPP

#include <hamon/config.hpp>

#if HAMON_HAS_INCLUDE(<compare>) && (HAMON_CXX_STANDARD >= 20)

#include <compare>

#define HAMON_HAS_STD_COMPARE

#if defined(__cpp_lib_three_way_comparison) && (__cpp_lib_three_way_comparison >= 201907L)

#define HAMON_USE_STD_COMPARE

#endif

#endif

// Visual Studio 2017 はinline変数に対応しているのに変数の多重定義でリンクエラーになる
#if defined(HAMON_HAS_CXX17_INLINE_VARIABLES)
#if !(defined(HAMON_MSVC) && (HAMON_MSVC < 1920))
#define HAMON_COMPARE_USE_INLINE_VARIABLES
#endif
#endif

#endif // HAMON_COMPARE_CONFIG_HPP
