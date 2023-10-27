/**
 *	@file	noexcept.hpp
 *
 *	@brief	HAMON_NOEXCEPT の定義
 */

#ifndef HAMON_CONFIG_SUFFIX_NOEXCEPT_HPP
#define HAMON_CONFIG_SUFFIX_NOEXCEPT_HPP

//
// noexcept workarounds
//
#if !defined(HAMON_NOEXCEPT)
#	if defined(HAMON_HAS_CXX11_NOEXCEPT)
#	  define HAMON_NOEXCEPT noexcept
#	else
#	  define HAMON_NOEXCEPT
#	endif
#endif

#if !defined(HAMON_NOEXCEPT_OR_NOTHROW)
#	if defined(HAMON_HAS_CXX11_NOEXCEPT)
#	  define HAMON_NOEXCEPT_OR_NOTHROW noexcept
#	else
#	  define HAMON_NOEXCEPT_OR_NOTHROW throw()
#	endif
#endif

#if !defined(HAMON_NOEXCEPT_IF)
#	if defined(HAMON_HAS_CXX11_NOEXCEPT)
#	  define HAMON_NOEXCEPT_IF(...) noexcept((__VA_ARGS__))
#	else
#	  define HAMON_NOEXCEPT_IF(...)
#	endif
#endif

#if !defined(HAMON_NOEXCEPT_EXPR)
#	if defined(HAMON_HAS_CXX11_NOEXCEPT)
#	  define HAMON_NOEXCEPT_EXPR(...) noexcept((__VA_ARGS__))
#	else
#	  define HAMON_NOEXCEPT_EXPR(...) false
#	endif
#endif

#if !defined(HAMON_NOEXCEPT_IF_EXPR)
#	define HAMON_NOEXCEPT_IF_EXPR(...)	HAMON_NOEXCEPT_IF(HAMON_NOEXCEPT_EXPR((__VA_ARGS__)))
#endif

#endif // HAMON_CONFIG_SUFFIX_NOEXCEPT_HPP
