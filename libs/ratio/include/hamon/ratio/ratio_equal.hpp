/**
 *	@file	ratio_equal.hpp
 *
 *	@brief	ratio_equal の定義
 */

#ifndef HAMON_RATIO_RATIO_EQUAL_HPP
#define HAMON_RATIO_RATIO_EQUAL_HPP

#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 21.4.5 Comparison of ratios[ratio.comparison]

template <typename R1, typename R2>
struct ratio_equal
	: public hamon::bool_constant<R1::num == R2::num && R1::den == R2::den>
{};

template <typename R1, typename R2>
HAMON_INLINE_VAR HAMON_CXX11_CONSTEXPR
bool ratio_equal_v = hamon::ratio_equal<R1, R2>::value;

}	// namespace hamon

#endif // HAMON_RATIO_RATIO_EQUAL_HPP
