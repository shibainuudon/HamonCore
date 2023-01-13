/**
 *	@file	config.hpp
 *
 *	@brief
 */

#ifndef HAMON_STRING_VIEW_CONFIG_HPP
#define HAMON_STRING_VIEW_CONFIG_HPP

#include <hamon/config.hpp>

#if (HAMON_CXX_STANDARD >= 17) && HAMON_HAS_INCLUDE(<string_view>)
#  include <string_view>
#endif

#if (HAMON_CXX_STANDARD >= 17) && \
	defined(__cpp_lib_starts_ends_with)      && (__cpp_lib_starts_ends_with      >= 201711) &&	\
	defined(__cpp_lib_string_view)           && (__cpp_lib_string_view           >= 201803) &&	\
	defined(__cpp_lib_constexpr_string_view) && (__cpp_lib_constexpr_string_view >= 201811) &&	\
	defined(__cpp_lib_three_way_comparison)  && (__cpp_lib_three_way_comparison  >= 201907) &&	\
	defined(__cpp_lib_char8_t)               && (__cpp_lib_char8_t               >= 201907) &&	\
	defined(__cpp_lib_string_contains)       && (__cpp_lib_string_contains       >= 202011)
#  define HAMON_USE_STD_STRING_VIEW
#endif

#endif // HAMON_STRING_VIEW_CONFIG_HPP
