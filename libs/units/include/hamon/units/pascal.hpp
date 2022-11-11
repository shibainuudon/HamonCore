/**
 *	@file	pascal.hpp
 *
 *	@brief	pascal の定義
 */

#ifndef HAMON_UNITS_PASCAL_HPP
#define HAMON_UNITS_PASCAL_HPP

#include <hamon/units/detail/si_prefix.hpp>
#include <hamon/units/newton.hpp>
#include <hamon/units/area.hpp>

namespace hamon
{

namespace units
{

// パスカル
template <typename T> using pascals = decltype(newton<T>() / square_metre<T>());
HAMON_UNITS_SI_PREFIX(pascals);

// "pascal"がキーワードになっている環境では"pascal"は定義しない("pascals"を使う)
#if defined(HAMON_MSVC)
	#define HAMON_UNITS_NO_PASCAL
#elif defined(pascal)
	#define HAMON_UNITS_NO_PASCAL
#endif

#if !defined(HAMON_UNITS_NO_PASCAL)
template <typename T> using pascal = pascals<T>;
HAMON_UNITS_SI_PREFIX(pascal);
#endif

}	// namespace units

}	// namespace hamon

#endif // HAMON_UNITS_PASCAL_HPP
