/**
 *	@file	in_out_result.hpp
 *
 *	@brief	ranges::in_out_result の定義
 */

#ifndef HAMON_ALGORITHM_RANGES_IN_OUT_RESULT_HPP
#define HAMON_ALGORITHM_RANGES_IN_OUT_RESULT_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_RANGES_ALGORITHM)

#include <algorithm>

namespace hamon
{

namespace ranges
{

using std::ranges::in_out_result;

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

template <typename I, typename O>
struct in_out_result
{
	HAMON_NO_UNIQUE_ADDRESS I in;
	HAMON_NO_UNIQUE_ADDRESS O out;

#if defined(HAMON_HAS_CXX20_CONCEPTS)
	template <typename I2, typename O2>
	requires
		hamon::convertible_to<I const&, I2> &&
		hamon::convertible_to<O const&, O2>
#else
	template <typename I2, typename O2,
		typename = hamon::enable_if_t<hamon::conjunction<
			hamon::convertible_to<I const&, I2>,
			hamon::convertible_to<O const&, O2>
		>::value>
	>
#endif
	HAMON_CXX14_CONSTEXPR
	operator in_out_result<I2, O2>() const&
	{
		return { in, out };
	}

#if defined(HAMON_HAS_CXX20_CONCEPTS)
	template <typename I2, typename O2>
	requires
		hamon::convertible_to<I, I2> &&
		hamon::convertible_to<O, O2>
#else
	template <typename I2, typename O2,
		typename = hamon::enable_if_t<hamon::conjunction<
			hamon::convertible_to<I, I2>,
			hamon::convertible_to<O, O2>
		>::value>
	>
#endif
	HAMON_CXX14_CONSTEXPR
	operator in_out_result<I2, O2>() &&
	{
		return { hamon::move(in), hamon::move(out) };
	}
};

}	// namespace ranges

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_RANGES_IN_OUT_RESULT_HPP
