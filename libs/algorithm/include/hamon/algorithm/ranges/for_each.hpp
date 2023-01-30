/**
 *	@file	for_each.hpp
 *
 *	@brief	ranges::for_each の定義
 */

#ifndef HAMON_ALGORITHM_RANGES_FOR_EACH_HPP
#define HAMON_ALGORITHM_RANGES_FOR_EACH_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_RANGES_ALGORITHM)

#include <algorithm>

namespace hamon
{

namespace ranges
{

using std::ranges::for_each;

}	// namespace ranges

}	// namespace hamon

#else

#include <hamon/algorithm/ranges/in_fun_result.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/functional/identity.hpp>
#include <hamon/functional/invoke.hpp>
#include <hamon/iterator/concepts/input_iterator.hpp>
#include <hamon/iterator/concepts/sentinel_for.hpp>
#include <hamon/iterator/concepts/indirectly_unary_invocable.hpp>
#include <hamon/iterator/projected.hpp>
#include <hamon/ranges/concepts/input_range.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/ranges/borrowed_iterator_t.hpp>
#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/end.hpp>
#include <hamon/config.hpp>
#include <utility>

namespace hamon
{

namespace ranges
{

template <typename Iter, typename F>
using for_each_result = in_fun_result<Iter, F>;

struct for_each_fn
{
	template <
		HAMON_CONSTRAINED_PARAM(hamon::input_iterator, Iter),
		HAMON_CONSTRAINED_PARAM(hamon::sentinel_for, Iter, Sent),
		typename Proj = hamon::identity,
		typename ProjectedIter = hamon::projected<Iter, Proj>,
		HAMON_CONSTRAINED_PARAM(
			hamon::indirectly_unary_invocable,
			ProjectedIter,
			Fun)
	>
	HAMON_CXX14_CONSTEXPR for_each_result<Iter, Fun>
	operator()(Iter first, Sent last, Fun f, Proj proj ={}) const
	{
		for (; first != last; ++first)
		{
			hamon::invoke(f, hamon::invoke(proj, *first));
		}

		return { std::move(first), std::move(f) };
	}

	template <
		HAMON_CONSTRAINED_PARAM(hamon::ranges::input_range, Range),
		typename Proj = hamon::identity,
		typename ProjectedIter = hamon::projected<ranges::iterator_t<Range>, Proj>,
		HAMON_CONSTRAINED_PARAM(
			hamon::indirectly_unary_invocable,
			ProjectedIter,
			Fun)
	>
	HAMON_CXX14_CONSTEXPR for_each_result<ranges::borrowed_iterator_t<Range>, Fun>
	operator()(Range&& r, Fun f, Proj proj ={}) const
	{
		return (*this)(
			ranges::begin(r), ranges::end(r),
			std::move(f), std::move(proj));
	}
};

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR for_each_fn for_each{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_RANGES_FOR_EACH_HPP
