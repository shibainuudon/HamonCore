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
#include <hamon/config.hpp>
#include <utility>

namespace hamon
{

namespace ranges
{

template <typename Iter, typename Out1, typename Out2>
struct in_out_out_result
{
	HAMON_NO_UNIQUE_ADDRESS Iter in;
	HAMON_NO_UNIQUE_ADDRESS Out1 out1;
	HAMON_NO_UNIQUE_ADDRESS Out2 out2;

#if defined(HAMON_HAS_CXX20_CONCEPTS)
	template <typename IIter, typename OOut1, typename OOut2>
	requires
		hamon::convertible_to<const Iter&, IIter> &&
		hamon::convertible_to<const Out1&, OOut1> &&
		hamon::convertible_to<const Out2&, OOut2>
#else
	template <
		typename IIter, typename OOut1, typename OOut2,
		typename = hamon::enable_if_t<hamon::conjunction<
			hamon::convertible_to<const Iter&, IIter>,
			hamon::convertible_to<const Out1&, OOut1>,
			hamon::convertible_to<const Out2&, OOut2>
		>::value>
	>
#endif
	HAMON_CXX14_CONSTEXPR
	operator in_out_out_result<IIter, OOut1, OOut2>() const&
	{
		return { in, out1, out2 };
	}

#if defined(HAMON_HAS_CXX20_CONCEPTS)
	template <typename IIter, typename OOut1, typename OOut2>
	requires
		hamon::convertible_to<Iter, IIter> &&
		hamon::convertible_to<Out1, OOut1> &&
		hamon::convertible_to<Out2, OOut2>
#else
	template <
		typename IIter, typename OOut1, typename OOut2,
		typename = hamon::enable_if_t<hamon::conjunction<
			hamon::convertible_to<Iter, IIter>,
			hamon::convertible_to<Out1, OOut1>,
			hamon::convertible_to<Out2, OOut2>
		>::value>
	>
#endif
	HAMON_CXX14_CONSTEXPR
	operator in_out_out_result<IIter, OOut1, OOut2>() &&
	{
		return { std::move(in), std::move(out1), std::move(out2) };
	}
};

}	// namespace ranges

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_RANGES_IN_OUT_OUT_RESULT_HPP
