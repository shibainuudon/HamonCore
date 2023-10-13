/**
 *	@file	config.hpp
 *
 *	@brief
 */

#ifndef HAMON_STRING_CONFIG_HPP
#define HAMON_STRING_CONFIG_HPP

#include <hamon/config.hpp>
#include <string>

// char_traits は、P0426R1 や P1032R1 で constexpr対応されたが、
// Feature-testing macro は追加されなかった。(GCC は __cpp_lib_constexpr_char_traits を定義していたりする)
// そのため、C++バージョンで判定するしかない。
#if HAMON_CXX_STANDARD >= 20
#  define HAMON_USE_STD_CHAR_TRAITS
#endif

#if	defined(__cpp_lib_string_udls)           && (__cpp_lib_string_udls           >= 201304) &&	\
	defined(__cpp_lib_starts_ends_with)      && (__cpp_lib_starts_ends_with      >= 201711) &&	\
	defined(__cpp_lib_string_view)           && (__cpp_lib_string_view           >= 201803) &&	\
	defined(__cpp_lib_constexpr_string)      && (__cpp_lib_constexpr_string      >= 201907) &&	\
	defined(__cpp_lib_three_way_comparison)  && (__cpp_lib_three_way_comparison  >= 201907) &&	\
	defined(__cpp_lib_char8_t)               && (__cpp_lib_char8_t               >= 201907) &&	\
	defined(__cpp_lib_erase_if)              && (__cpp_lib_erase_if              >= 202002) &&	\
	defined(__cpp_lib_string_contains)       && (__cpp_lib_string_contains       >= 202011)
#  define HAMON_USE_STD_STRING
#endif

#endif // HAMON_STRING_CONFIG_HPP
