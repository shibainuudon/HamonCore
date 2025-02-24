﻿/**
 *	@file	in_fun_result.hpp
 *
 *	@brief	ranges::in_fun_result の定義
 */

#ifndef HAMON_ALGORITHM_RANGES_IN_FUN_RESULT_HPP
#define HAMON_ALGORITHM_RANGES_IN_FUN_RESULT_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_RANGES_ALGORITHM)

#include <algorithm>

namespace hamon
{

namespace ranges
{

using std::ranges::in_fun_result;

}	// namespace ranges

}	// namespace hamon

#else

#include <hamon/concepts/convertible_to.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace ranges
{

// 27.5 Algorithm result types[algorithms.results]

template <typename I, typename F>
struct in_fun_result
{
	HAMON_NO_UNIQUE_ADDRESS I in;
	HAMON_NO_UNIQUE_ADDRESS F fun;

#if defined(HAMON_HAS_CXX20_CONCEPTS)
	template <typename I2, typename F2>
	requires
		hamon::convertible_to<I const&, I2> &&
		hamon::convertible_to<F const&, F2>
#else
	template <typename I2, typename F2,
		typename = hamon::enable_if_t<hamon::conjunction<
			hamon::convertible_to<I const&, I2>,
			hamon::convertible_to<F const&, F2>
		>::value>
	>
#endif
	HAMON_CXX14_CONSTEXPR
	operator in_fun_result<I2, F2>() const&
	{
		return { in, fun };
	}

#if defined(HAMON_HAS_CXX20_CONCEPTS)
	template <typename I2, typename F2>
	requires
		hamon::convertible_to<I, I2> &&
		hamon::convertible_to<F, F2>
#else
	template <typename I2, typename F2,
		typename = hamon::enable_if_t<hamon::conjunction<
			hamon::convertible_to<I, I2>,
			hamon::convertible_to<F, F2>
		>::value>
	>
#endif
	HAMON_CXX14_CONSTEXPR
	operator in_fun_result<I2, F2>() &&
	{
		return { hamon::move(in), hamon::move(fun) };
	}
};

}	// namespace ranges

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_RANGES_IN_FUN_RESULT_HPP
