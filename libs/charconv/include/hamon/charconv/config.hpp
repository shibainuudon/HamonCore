/**
 *	@file	config.hpp
 *
 *	@brief
 */

#ifndef HAMON_CHARCONV_CONFIG_HPP
#define HAMON_CHARCONV_CONFIG_HPP

#include <hamon/config.hpp>

#if (HAMON_CXX_STANDARD >= 17)

#  if HAMON_HAS_INCLUDE(<charconv>)
#    include <charconv>
#  endif

#  if defined(__cpp_lib_to_chars) && (__cpp_lib_to_chars >= 201611L) &&	\
      defined(__cpp_lib_constexpr_charconv) && (__cpp_lib_constexpr_charconv >= 202207L)
#    define	HAMON_USE_STD_CHARCONV
#  endif

#endif

#endif // HAMON_CHARCONV_CONFIG_HPP
