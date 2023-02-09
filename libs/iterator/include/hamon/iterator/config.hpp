/**
 *	@file	config.hpp
 *
 *	@brief
 */

#ifndef HAMON_ITERATOR_CONFIG_HPP
#define HAMON_ITERATOR_CONFIG_HPP

#include <hamon/config.hpp>
#include <hamon/ranges/config.hpp>
#include <iterator>

#if defined(__cpp_lib_constexpr_iterator) && (__cpp_lib_constexpr_iterator >= 201811)
#  define HAMON_USE_STD_ITERATOR
#endif

#if defined(HAMON_USE_STD_ITERATOR) && defined(HAMON_USE_STD_RANGES)
#  define HAMON_USE_STD_RANGES_ITERATOR
#endif

#endif // HAMON_ITERATOR_CONFIG_HPP
