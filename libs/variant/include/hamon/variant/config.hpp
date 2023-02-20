/**
 *	@file	config.hpp
 *
 *	@brief
 */

#ifndef HAMON_VARIANT_CONFIG_HPP
#define HAMON_VARIANT_CONFIG_HPP

#include <hamon/config.hpp>

#if (HAMON_CXX_STANDARD >= 17) && HAMON_HAS_INCLUDE(<variant>)
#  include <variant>
#endif

#if defined(__cpp_lib_variant) && (__cpp_lib_variant >= 202106)
#  define HAMON_USE_STD_VARIANT
#endif

#endif // HAMON_VARIANT_CONFIG_HPP
