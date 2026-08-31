/**
 *	@file	ratio_less_equal.hpp
 *
 *	@brief	ratio_less_equal の定義
 */

#ifndef HAMON_RATIO_RATIO_LESS_EQUAL_HPP
#define HAMON_RATIO_RATIO_LESS_EQUAL_HPP

#include <hamon/ratio/ratio_less.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 21.4.5 Comparison of ratios[ratio.comparison]

template <typename R1, typename R2>
struct ratio_less_equal
	: public hamon::bool_constant<!hamon::ratio_less<R2, R1>::value>
{};

template <typename R1, typename R2>
HAMON_INLINE_VAR HAMON_CXX11_CONSTEXPR
bool ratio_less_equal_v = hamon::ratio_less_equal<R1, R2>::value;

}	// namespace hamon

#endif // HAMON_RATIO_RATIO_LESS_EQUAL_HPP
