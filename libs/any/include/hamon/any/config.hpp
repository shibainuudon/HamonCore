/**
 *	@file	config.hpp
 *
 *	@brief
 */

#ifndef HAMON_ANY_CONFIG_HPP
#define HAMON_ANY_CONFIG_HPP

#include <hamon/config.hpp>

#if (HAMON_CXX_STANDARD >= 17) && HAMON_HAS_INCLUDE(<any>)
#  include <any>
#endif

#if defined(__cpp_lib_any) && (__cpp_lib_any >= 201606)
#  define HAMON_USE_STD_ANY
#endif

#endif // HAMON_ANY_CONFIG_HPP
