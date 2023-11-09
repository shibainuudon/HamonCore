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

#if (_MSC_VER >= 1937)
#  define HAMON_HAS_CXX23_LIB_EXTENDED_FLOATING_POINT_TYPES			// P1467R9	Extended floating-point types and standard names
#endif

#endif // HAMON_CONFIG_STDLIB_DINKUMWARE_HPP
