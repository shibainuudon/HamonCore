/**
 *	@file	ratio_greater.hpp
 *
 *	@brief	ratio_greater の定義
 */

#ifndef HAMON_RATIO_RATIO_GREATER_HPP
#define HAMON_RATIO_RATIO_GREATER_HPP

#include <hamon/ratio/ratio_less.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 21.4.5 Comparison of ratios[ratio.comparison]

template <typename R1, typename R2>
struct ratio_greater
	: public hamon::bool_constant<hamon::ratio_less<R2, R1>::value>
{};

template <typename R1, typename R2>
HAMON_INLINE_VAR HAMON_CXX11_CONSTEXPR
bool ratio_greater_v = hamon::ratio_greater<R1, R2>::value;

}	// namespace hamon

#endif // HAMON_RATIO_RATIO_GREATER_HPP
