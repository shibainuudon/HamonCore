/**
 *	@file	in_out_out_result.hpp
 *
 *	@brief	ranges::in_out_out_result の定義
 */

#ifndef HAMON_ALGORITHM_RANGES_IN_OUT_OUT_RESULT_HPP
#define HAMON_ALGORITHM_RANGES_IN_OUT_OUT_RESULT_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_RANGES_ALGORITHM)

#include <algorithm>

namespace hamon
{

namespace ranges
{

using std::ranges::in_out_out_result;

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

template <typename I, typename O1, typename O2>
struct in_out_out_result
{
	HAMON_NO_UNIQUE_ADDRESS I  in;
	HAMON_NO_UNIQUE_ADDRESS O1 out1;
	HAMON_NO_UNIQUE_ADDRESS O2 out2;

#if defined(HAMON_HAS_CXX20_CONCEPTS)
	template <typename II, typename OO1, typename OO2>
	requires
		hamon::convertible_to<I const&, II> &&
		hamon::convertible_to<O1 const&, OO1> &&
		hamon::convertible_to<O2 const&, OO2>
#else
	template <
		typename II, typename OO1, typename OO2,
		typename = hamon::enable_if_t<hamon::conjunction<
			hamon::convertible_to<I const&, II>,
			hamon::convertible_to<O1 const&, OO1>,
			hamon::convertible_to<O2 const&, OO2>
		>::value>
	>
#endif
	HAMON_CXX14_CONSTEXPR
	operator in_out_out_result<II, OO1, OO2>() const&
	{
		return { in, out1, out2 };
	}

#if defined(HAMON_HAS_CXX20_CONCEPTS)
	template <typename II, typename OO1, typename OO2>
	requires
		hamon::convertible_to<I, II> &&
		hamon::convertible_to<O1, OO1> &&
		hamon::convertible_to<O2, OO2>
#else
	template <
		typename II, typename OO1, typename OO2,
		typename = hamon::enable_if_t<hamon::conjunction<
			hamon::convertible_to<I, II>,
			hamon::convertible_to<O1, OO1>,
			hamon::convertible_to<O2, OO2>
		>::value>
	>
#endif
	HAMON_CXX14_CONSTEXPR
	operator in_out_out_result<II, OO1, OO2>() &&
	{
		return { hamon::move(in), hamon::move(out1), hamon::move(out2) };
	}
};

}	// namespace ranges

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_RANGES_IN_OUT_OUT_RESULT_HPP
