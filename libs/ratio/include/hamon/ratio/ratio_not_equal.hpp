﻿/**
 *	@file	ratio_not_equal.hpp
 *
 *	@brief	ratio_not_equal の定義
 */

#ifndef HAMON_RATIO_RATIO_NOT_EQUAL_HPP
#define HAMON_RATIO_RATIO_NOT_EQUAL_HPP

#include <hamon/ratio/config.hpp>
#include <hamon/config.hpp>

#if defined(HAMON_USE_STD_RATIO)

#include <ratio>

namespace hamon
{

using std::ratio_not_equal;

}	// namespace hamon

#else

#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/ratio/ratio_equal.hpp>

namespace hamon
{

// 21.4.5 Comparison of ratios[ratio.comparison]

template <typename R1, typename R2>
struct ratio_not_equal
	: public hamon::bool_constant<!hamon::ratio_equal<R1, R2>::value>
{};

}	// namespace hamon

#endif

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

namespace hamon
{

template <typename R1, typename R2>
HAMON_INLINE_VAR HAMON_CXX11_CONSTEXPR
bool ratio_not_equal_v = hamon::ratio_not_equal<R1, R2>::value;

}	// namespace hamon

#endif

#endif // HAMON_RATIO_RATIO_NOT_EQUAL_HPP
