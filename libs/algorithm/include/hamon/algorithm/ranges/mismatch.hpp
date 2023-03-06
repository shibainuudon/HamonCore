/**
 *	@file	mismatch.hpp
 *
 *	@brief	ranges::mismatch の定義
 */

#ifndef HAMON_ALGORITHM_RANGES_MISMATCH_HPP
#define HAMON_ALGORITHM_RANGES_MISMATCH_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_RANGES_ALGORITHM)

#include <algorithm>

namespace hamon
{

namespace ranges
{

using std::ranges::mismatch;

}	// namespace ranges

}	// namespace hamon

#else

#include <hamon/algorithm/ranges/in_in_result.hpp>
#include <hamon/algorithm/ranges/detail/return_type_requires_clauses.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/functional/ranges/equal_to.hpp>
#include <hamon/functional/identity.hpp>
#include <hamon/functional/invoke.hpp>
#include <hamon/iterator/concepts/input_iterator.hpp>
#include <hamon/iterator/concepts/sentinel_for.hpp>
#include <hamon/iterator/concepts/indirectly_comparable.hpp>
#include <hamon/preprocessor/punctuation/comma.hpp>
#include <hamon/ranges/concepts/input_range.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/end.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace ranges
{

template <typename Iter1, typename Iter2>
using mismatch_result = in_in_result<Iter1, Iter2>;

struct mismatch_fn
{
	template <
		HAMON_CONSTRAINED_PARAM(hamon::input_iterator, Iter1),
		HAMON_CONSTRAINED_PARAM(hamon::sentinel_for, Iter1, Sent1),
		HAMON_CONSTRAINED_PARAM(hamon::input_iterator, Iter2),
		HAMON_CONSTRAINED_PARAM(hamon::sentinel_for, Iter2, Sent2),
		typename Pred = ranges::equal_to,
		typename Proj1 = hamon::identity,
		typename Proj2 = hamon::identity
	>
	HAMON_CXX14_CONSTEXPR auto operator()(
		Iter1 first1, Sent1 last1,
		Iter2 first2, Sent2 last2,
		Pred pred = {},
		Proj1 proj1 = {},
		Proj2 proj2 = {}) const
	HAMON_RETURN_TYPE_REQUIRES_CLAUSES(
		mismatch_result<Iter1 HAMON_PP_COMMA() Iter2>,
		hamon::indirectly_comparable<
			Iter1, Iter2, Pred, Proj1, Proj2>)
	{
		while (first1 != last1 && first2 != last2 &&
			(bool)hamon::invoke(pred,
				hamon::invoke(proj1, *first1),
				hamon::invoke(proj2, *first2)))
		{
			++first1;
			++first2;
		}

		return { hamon::move(first1), hamon::move(first2) };
	}

	template <
		HAMON_CONSTRAINED_PARAM(hamon::ranges::input_range, Range1),
		HAMON_CONSTRAINED_PARAM(hamon::ranges::input_range, Range2),
		typename Pred = ranges::equal_to,
		typename Proj1 = hamon::identity,
		typename Proj2 = hamon::identity
	>
	HAMON_CXX14_CONSTEXPR auto operator()(
		Range1&& r1,
		Range2&& r2,
		Pred pred = {},
		Proj1 proj1 = {},
		Proj2 proj2 = {}) const
	HAMON_RETURN_TYPE_REQUIRES_CLAUSES(
		mismatch_result<
			ranges::iterator_t<Range1> HAMON_PP_COMMA()
			ranges::iterator_t<Range2>>,
		hamon::indirectly_comparable<
			ranges::iterator_t<Range1>,
			ranges::iterator_t<Range2>,
			Pred, Proj1, Proj2>)
	{
		return (*this)(
			ranges::begin(r1), ranges::end(r1),
			ranges::begin(r2), ranges::end(r2),
			hamon::move(pred),
			hamon::move(proj1),
			hamon::move(proj2));
	}
};

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR mismatch_fn mismatch{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_RANGES_MISMATCH_HPP
