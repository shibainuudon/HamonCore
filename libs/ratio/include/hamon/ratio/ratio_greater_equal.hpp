﻿/**
 *	@file	ratio_greater_equal.hpp
 *
 *	@brief	ratio_greater_equal の定義
 */

#ifndef HAMON_RATIO_RATIO_GREATER_EQUAL_HPP
#define HAMON_RATIO_RATIO_GREATER_EQUAL_HPP

#include <hamon/ratio/config.hpp>
#include <hamon/config.hpp>

#if defined(HAMON_USE_STD_RATIO)

#include <ratio>

namespace hamon
{

using std::ratio_greater_equal;

}	// namespace hamon

#else

#include <hamon/ratio/ratio_less.hpp>
#include <hamon/type_traits/bool_constant.hpp>

namespace hamon
{

// 21.4.5 Comparison of ratios[ratio.comparison]

template <typename R1, typename R2>
struct ratio_greater_equal
	: public hamon::bool_constant<!hamon::ratio_less<R1, R2>::value>
{};

}	// namespace hamon

#endif

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

namespace hamon
{

template <typename R1, typename R2>
HAMON_INLINE_VAR HAMON_CXX11_CONSTEXPR
bool ratio_greater_equal_v = hamon::ratio_greater_equal<R1, R2>::value;

}	// namespace hamon

#endif

#endif // HAMON_RATIO_RATIO_GREATER_EQUAL_HPP
