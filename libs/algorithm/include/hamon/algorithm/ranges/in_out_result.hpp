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

template <typename Iter, typename Out>
struct in_out_result
{
	HAMON_NO_UNIQUE_ADDRESS Iter in;
	HAMON_NO_UNIQUE_ADDRESS Out  out;

#if defined(HAMON_HAS_CXX20_CONCEPTS)
	template <typename Iter2, typename Out2>
	requires
		hamon::convertible_to<Iter const&, Iter2> &&
		hamon::convertible_to<Out const&, Out2>
#else
	template <typename Iter2, typename Out2,
		typename = hamon::enable_if_t<hamon::conjunction<
			hamon::convertible_to<Iter const&, Iter2>,
			hamon::convertible_to<Out const&, Out2>
		>::value>
	>
#endif
	HAMON_CXX14_CONSTEXPR operator in_out_result<Iter2, Out2>() const&
	{
		return { in, out };
	}

#if defined(HAMON_HAS_CXX20_CONCEPTS)
	template <typename Iter2, typename Out2>
	requires
		hamon::convertible_to<Iter, Iter2> &&
		hamon::convertible_to<Out, Out2>
#else
	template <typename Iter2, typename Out2,
		typename = hamon::enable_if_t<hamon::conjunction<
			hamon::convertible_to<Iter, Iter2>,
			hamon::convertible_to<Out, Out2>
		>::value>
	>
#endif
	HAMON_CXX14_CONSTEXPR operator in_out_result<Iter2, Out2>() &&
	{
		return { hamon::move(in), hamon::move(out) };
	}
};

}	// namespace ranges

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_RANGES_IN_OUT_RESULT_HPP
