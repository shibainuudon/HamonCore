/**
 *	@file	ratio_less_equal.hpp
 *
 *	@brief	ratio_less_equal の定義
 */

#ifndef HAMON_RATIO_RATIO_LESS_EQUAL_HPP
#define HAMON_RATIO_RATIO_LESS_EQUAL_HPP

#include <hamon/ratio/config.hpp>
#include <hamon/config.hpp>

#if defined(HAMON_USE_STD_RATIO)

#include <ratio>

namespace hamon
{

using std::ratio_less_equal;

}	// namespace hamon

#else

namespace hamon
{

// TODO

}	// namespace hamon

#endif

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

namespace hamon
{

template <typename R1, typename R2>
HAMON_INLINE_VAR HAMON_CXX11_CONSTEXPR
bool ratio_less_equal_v = hamon::ratio_less_equal<R1, R2>::value;

}	// namespace hamon

#endif

#endif // HAMON_RATIO_RATIO_LESS_EQUAL_HPP
