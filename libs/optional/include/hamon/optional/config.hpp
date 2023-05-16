/**
 *	@file	config.hpp
 *
 *	@brief
 */

#ifndef HAMON_OPTIONAL_CONFIG_HPP
#define HAMON_OPTIONAL_CONFIG_HPP

#include <hamon/config.hpp>

#if (HAMON_CXX_STANDARD >= 17)

#  if HAMON_HAS_INCLUDE(<optional>)
#    include <optional>
#  endif

#  if defined(__cpp_lib_optional) && (__cpp_lib_optional >= 202110L) &&	\
      defined(__cpp_lib_three_way_comparison) && (__cpp_lib_three_way_comparison >= 201907L)
#    define	HAMON_USE_STD_OPTIONAL
#  endif

#endif

#endif // HAMON_OPTIONAL_CONFIG_HPP
