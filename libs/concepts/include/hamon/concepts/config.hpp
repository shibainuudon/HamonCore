/**
 *	@file	config.hpp
 *
 *	@brief
 */

#ifndef HAMON_CONCEPTS_CONFIG_HPP
#define HAMON_CONCEPTS_CONFIG_HPP

#include <hamon/config.hpp>

#if defined(HAMON_HAS_CXX20_CONCEPTS) && HAMON_HAS_INCLUDE(<concepts>)
#  include <concepts>
#endif

#if defined(__cpp_lib_concepts) && (__cpp_lib_concepts >= 202002)
#  define HAMON_USE_STD_CONCEPTS
#endif

#endif // HAMON_CONCEPTS_CONFIG_HPP
