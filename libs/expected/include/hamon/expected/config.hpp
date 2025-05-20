/**
 *	@file	config.hpp
 *
 *	@brief
 */

#ifndef HAMON_EXPECTED_CONFIG_HPP
#define HAMON_EXPECTED_CONFIG_HPP

#include <hamon/config.hpp>

#if (HAMON_CXX_STANDARD >= 23)

#if HAMON_HAS_INCLUDE(<expected>)
#  include <expected>
#endif

#if defined(__cpp_lib_expected)             && (__cpp_lib_expected             >= 202211L) && \
	defined(__cpp_lib_constrained_equality) && (__cpp_lib_constrained_equality >= 202411L) && \
	defined(__cpp_lib_constexpr_exceptions) && (__cpp_lib_constexpr_exceptions >= 202502L)
#  define HAMON_USE_STD_EXPECTED
#endif

#endif

#endif // HAMON_EXPECTED_CONFIG_HPP
