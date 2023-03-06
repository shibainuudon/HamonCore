﻿/**
 *	@file	set_difference.hpp
 *
 *	@brief	ranges::set_difference の定義
 */

#ifndef HAMON_ALGORITHM_RANGES_SET_DIFFERENCE_HPP
#define HAMON_ALGORITHM_RANGES_SET_DIFFERENCE_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_RANGES_ALGORITHM)

#include <algorithm>

namespace hamon
{

namespace ranges
{

using std::ranges::set_difference;

}	// namespace ranges

}	// namespace hamon

#else

#include <hamon/algorithm/ranges/in_out_result.hpp>
#include <hamon/algorithm/ranges/copy.hpp>
#include <hamon/algorithm/ranges/detail/return_type_requires_clauses.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/functional/ranges/less.hpp>
#include <hamon/functional/identity.hpp>
#include <hamon/functional/invoke.hpp>
#include <hamon/iterator/concepts/input_iterator.hpp>
#include <hamon/iterator/concepts/sentinel_for.hpp>
#include <hamon/iterator/concepts/weakly_incrementable.hpp>
#include <hamon/iterator/concepts/mergeable.hpp>
#include <hamon/preprocessor/punctuation/comma.hpp>
#include <hamon/ranges/concepts/input_range.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/ranges/borrowed_iterator_t.hpp>
#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/end.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace ranges
{

template <typename Iter, typename Out>
using set_difference_result = in_out_result<Iter, Out>;

struct set_difference_fn
{
	template <
		HAMON_CONSTRAINED_PARAM(hamon::input_iterator, Iter1),
		HAMON_CONSTRAINED_PARAM(hamon::sentinel_for, Iter1, Sent1),
		HAMON_CONSTRAINED_PARAM(hamon::input_iterator, Iter2),
		HAMON_CONSTRAINED_PARAM(hamon::sentinel_for, Iter2, Sent2),
		HAMON_CONSTRAINED_PARAM(hamon::weakly_incrementable, Out),
		typename Comp = ranges::less,
		typename Proj1 = hamon::identity,
		typename Proj2 = hamon::identity
	>
	HAMON_CXX14_CONSTEXPR auto operator()(
		Iter1 first1, Sent1 last1,
		Iter2 first2, Sent2 last2,
		Out result,
		Comp comp = {},
		Proj1 proj1 = {}, Proj2 proj2 = {}) const
	HAMON_RETURN_TYPE_REQUIRES_CLAUSES(
		set_difference_result<Iter1 HAMON_PP_COMMA() Out>,
		hamon::mergeable<Iter1, Iter2, Out, Comp, Proj1, Proj2>)
	{
		while (first1 != last1 && first2 != last2)
		{
			if (hamon::invoke(comp,
				hamon::invoke(proj1, *first1),
				hamon::invoke(proj2, *first2)))
			{
				*result = *first1;
				++first1;
				++result;
			}
			else if (hamon::invoke(comp,
				hamon::invoke(proj2, *first2),
				hamon::invoke(proj1, *first1)))
			{
				++first2;
			}
			else
			{
				++first1;
				++first2;
			}
		}

		return ranges::copy(
			hamon::move(first1),
			hamon::move(last1),
			hamon::move(result));
	}

	template <
		HAMON_CONSTRAINED_PARAM(ranges::input_range, Range1),
		HAMON_CONSTRAINED_PARAM(ranges::input_range, Range2),
		HAMON_CONSTRAINED_PARAM(hamon::weakly_incrementable, Out),
		typename Comp = ranges::less,
		typename Proj1 = hamon::identity,
		typename Proj2 = hamon::identity
	>
	HAMON_CXX14_CONSTEXPR auto operator()(
		Range1&& r1, Range2&& r2,
		Out result,
		Comp comp = {},
		Proj1 proj1 = {},
		Proj2 proj2 = {}) const
	HAMON_RETURN_TYPE_REQUIRES_CLAUSES(
		set_difference_result<
			ranges::borrowed_iterator_t<Range1> HAMON_PP_COMMA() Out>,
		hamon::mergeable<
			ranges::iterator_t<Range1>,
			ranges::iterator_t<Range2>,
			Out, Comp, Proj1, Proj2>)
	{
		return (*this)(
			ranges::begin(r1), ranges::end(r1),
			ranges::begin(r2), ranges::end(r2),
			hamon::move(result), hamon::move(comp),
			hamon::move(proj1), hamon::move(proj2));
	}
};

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR set_difference_fn set_difference{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_RANGES_SET_DIFFERENCE_HPP
