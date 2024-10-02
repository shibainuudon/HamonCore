/**
 *	@file	in_in_out_result.hpp
 *
 *	@brief	ranges::in_in_out_result の定義
 */

#ifndef HAMON_ALGORITHM_RANGES_IN_IN_OUT_RESULT_HPP
#define HAMON_ALGORITHM_RANGES_IN_IN_OUT_RESULT_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_RANGES_ALGORITHM)

#include <algorithm>

namespace hamon
{

namespace ranges
{

using std::ranges::in_in_out_result;

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

template <typename I1, typename I2, typename O>
struct in_in_out_result
{
	HAMON_NO_UNIQUE_ADDRESS I1 in1;
	HAMON_NO_UNIQUE_ADDRESS I2 in2;
	HAMON_NO_UNIQUE_ADDRESS O  out;

#if defined(HAMON_HAS_CXX20_CONCEPTS)
	template <typename II1, typename II2, typename OO>
	requires
		hamon::convertible_to<I1 const&, II1> &&
		hamon::convertible_to<I2 const&, II2> &&
		hamon::convertible_to<O const&, OO>
#else
	template <
		typename II1, typename II2, typename OO,
		typename = hamon::enable_if_t<hamon::conjunction<
			hamon::convertible_to<I1 const&, II1>,
			hamon::convertible_to<I2 const&, II2>,
			hamon::convertible_to<O const&, OO>
		>::value>
	>
#endif
	HAMON_CXX14_CONSTEXPR
	operator in_in_out_result<II1, II2, OO>() const&
	{
		return { in1, in2, out };
	}

#if defined(HAMON_HAS_CXX20_CONCEPTS)
	template <typename II1, typename II2, typename OO>
	requires
		hamon::convertible_to<I1, II1> &&
		hamon::convertible_to<I2, II2> &&
		hamon::convertible_to<O, OO>
#else
	template <
		typename II1, typename II2, typename OO,
		typename = hamon::enable_if_t<hamon::conjunction<
			hamon::convertible_to<I1, II1>,
			hamon::convertible_to<I2, II2>,
			hamon::convertible_to<O, OO>
		>::value>
	>
#endif
	HAMON_CXX14_CONSTEXPR
	operator in_in_out_result<II1, II2, OO>() &&
	{
		return { hamon::move(in1), hamon::move(in2), hamon::move(out) };
	}
};

}	// namespace ranges

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_RANGES_IN_IN_OUT_RESULT_HPP
