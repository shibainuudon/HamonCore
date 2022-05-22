/**
 *	@file	config.hpp
 *
 *	@brief
 */

#ifndef HAMON_RANGES_CONFIG_HPP
#define HAMON_RANGES_CONFIG_HPP

#include <hamon/config.hpp>

#if (HAMON_CXX_STANDARD >= 20) && HAMON_HAS_INCLUDE(<ranges>)
#  include <ranges>
#endif

//#if defined(__cpp_lib_ranges) && (__cpp_lib_ranges >= 201911)
#if defined(__cpp_lib_ranges) && (__cpp_lib_ranges >= 202106)
#  define HAMON_USE_STD_RANGES
#endif

#if defined(HAMON_USE_STD_RANGES)
#define HAMON_RANGES_START_NAMESPACE namespace std { namespace ranges {
#else
#define HAMON_RANGES_START_NAMESPACE namespace hamon { namespace ranges {
#endif

#define HAMON_RANGES_END_NAMESPACE   }}

#endif // HAMON_RANGES_CONFIG_HPP
