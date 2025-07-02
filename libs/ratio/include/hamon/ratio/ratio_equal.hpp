/**
 *	@file	ratio_equal.hpp
 *
 *	@brief	ratio_equal の定義
 */

#ifndef HAMON_RATIO_RATIO_EQUAL_HPP
#define HAMON_RATIO_RATIO_EQUAL_HPP

#include <hamon/ratio/config.hpp>
#include <hamon/config.hpp>

#if defined(HAMON_USE_STD_RATIO)

#include <ratio>

namespace hamon
{

using std::ratio_equal;

}	// namespace hamon

#else

#include <hamon/type_traits/bool_constant.hpp>

namespace hamon
{

// 21.4.5 Comparison of ratios[ratio.comparison]

template <typename R1, typename R2>
struct ratio_equal
	: public hamon::bool_constant<R1::num == R2::num && R1::den == R2::den>
{};

}	// namespace hamon

#endif

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

namespace hamon
{

template <typename R1, typename R2>
HAMON_INLINE_VAR HAMON_CXX11_CONSTEXPR
bool ratio_equal_v = hamon::ratio_equal<R1, R2>::value;

}	// namespace hamon

#endif

#endif // HAMON_RATIO_RATIO_EQUAL_HPP
