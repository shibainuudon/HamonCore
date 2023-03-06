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

template <typename Iter1, typename Iter2, typename Out>
struct in_in_out_result
{
	HAMON_NO_UNIQUE_ADDRESS Iter1 in1;
	HAMON_NO_UNIQUE_ADDRESS Iter2 in2;
	HAMON_NO_UNIQUE_ADDRESS Out   out;

#if defined(HAMON_HAS_CXX20_CONCEPTS)
	template <typename IIter1, typename IIter2, typename OOut>
	requires
		hamon::convertible_to<Iter1 const&, IIter1> &&
		hamon::convertible_to<Iter2 const&, IIter2> &&
		hamon::convertible_to<Out const&, OOut>
#else
	template <
		typename IIter1, typename IIter2, typename OOut,
		typename = hamon::enable_if_t<hamon::conjunction<
			hamon::convertible_to<Iter1 const&, IIter1>,
			hamon::convertible_to<Iter2 const&, IIter2>,
			hamon::convertible_to<Out const&, OOut>
		>::value>
	>
#endif
	HAMON_CXX14_CONSTEXPR
	operator in_in_out_result<IIter1, IIter2, OOut>() const&
	{
		return { in1, in2, out };
	}

#if defined(HAMON_HAS_CXX20_CONCEPTS)
	template <typename IIter1, typename IIter2, typename OOut>
	requires
		hamon::convertible_to<Iter1, IIter1> &&
		hamon::convertible_to<Iter2, IIter2> &&
		hamon::convertible_to<Out, OOut>
#else
	template <
		typename IIter1, typename IIter2, typename OOut,
		typename = hamon::enable_if_t<hamon::conjunction<
			hamon::convertible_to<Iter1, IIter1>,
			hamon::convertible_to<Iter2, IIter2>,
			hamon::convertible_to<Out, OOut>
		>::value>
	>
#endif
	HAMON_CXX14_CONSTEXPR
	operator in_in_out_result<IIter1, IIter2, OOut>() &&
	{
		return { hamon::move(in1), hamon::move(in2), hamon::move(out) };
	}
};

}	// namespace ranges

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_RANGES_IN_IN_OUT_RESULT_HPP
