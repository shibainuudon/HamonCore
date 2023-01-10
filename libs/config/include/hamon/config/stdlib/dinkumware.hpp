/**
 *	@file	dinkumware.hpp
 *
 *	@brief
 */

#ifndef HAMON_CONFIG_STDLIB_DINKUMWARE_HPP
#define HAMON_CONFIG_STDLIB_DINKUMWARE_HPP

#if defined(_CPPLIB_VER)
#  define HAMON_STDLIB "Dinkumware standard library version " HAMON_STRINGIZE(_CPPLIB_VER)
#else
#  define HAMON_STDLIB "Dinkumware standard library version 1.x"
#endif

#define HAMON_STDLIB_DINKUMWARE

#endif // HAMON_CONFIG_STDLIB_DINKUMWARE_HPP
