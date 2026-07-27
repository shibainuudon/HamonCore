/**
 *	@file	config.hpp
 *
 *	@brief
 */

#ifndef HAMON_RANGES_CONFIG_HPP
#define HAMON_RANGES_CONFIG_HPP

#include <hamon/config.hpp>
#include <hamon/tuple/config.hpp>

#if (HAMON_CXX_STANDARD >= 20) && HAMON_HAS_INCLUDE(<ranges>)
#  include <ranges>
#endif

#if (defined(__cpp_lib_ranges)              && (__cpp_lib_ranges              >= 202302L)) && \
	(defined(__cpp_lib_ranges_as_const)     && (__cpp_lib_ranges_as_const     >= 202207L)) && \
	(defined(__cpp_lib_ranges_concat)       && (__cpp_lib_ranges_concat       >= 202403L)) && \
	(defined(__cpp_lib_ranges_cache_latest) && (__cpp_lib_ranges_cache_latest >= 202411L)) && \
	(defined(__cpp_lib_ranges_as_input)     && (__cpp_lib_ranges_as_input     >= 202502L)) && \
	(defined(__cpp_lib_ranges_reserve_hint) && (__cpp_lib_ranges_reserve_hint >= 202502L)) && \
	(defined(__cpp_lib_ranges_indices)      && (__cpp_lib_ranges_indices      >= 202506L)) && \
	defined(HAMON_USE_STD_TUPLE) && \
	!(defined(_GLIBCXX_RELEASE) && (_GLIBCXX_RELEASE <= 13))    /* libcstdc++ の enable_view は参照型でもtrueになってしまう */

#  define HAMON_USE_STD_RANGES

#endif

#if defined(HAMON_USE_STD_RANGES)
#define HAMON_RANGES_START_NAMESPACE namespace std { namespace ranges {
#else
#define HAMON_RANGES_START_NAMESPACE namespace hamon { namespace ranges {
#endif

#define HAMON_RANGES_END_NAMESPACE   }}

namespace hamon {
namespace ranges {
namespace views {
}	// namespace views
}	// namespace ranges

namespace views = ranges::views;

}	// namespace hamon

#endif // HAMON_RANGES_CONFIG_HPP
