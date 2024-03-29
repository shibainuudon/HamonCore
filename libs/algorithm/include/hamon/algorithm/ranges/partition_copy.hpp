﻿/**
 *	@file	partition_copy.hpp
 *
 *	@brief	ranges::partition_copy の定義
 */

#ifndef HAMON_ALGORITHM_RANGES_PARTITION_COPY_HPP
#define HAMON_ALGORITHM_RANGES_PARTITION_COPY_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_RANGES_ALGORITHM)

#include <algorithm>

namespace hamon
{

namespace ranges
{

using std::ranges::partition_copy;

}	// namespace ranges

}	// namespace hamon

#else

#include <hamon/algorithm/ranges/in_out_out_result.hpp>
#include <hamon/algorithm/ranges/detail/return_type_requires_clauses.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/concepts/detail/and.hpp>
#include <hamon/functional/identity.hpp>
#include <hamon/functional/invoke.hpp>
#include <hamon/iterator/concepts/input_iterator.hpp>
#include <hamon/iterator/concepts/sentinel_for.hpp>
#include <hamon/iterator/concepts/weakly_incrementable.hpp>
#include <hamon/iterator/concepts/indirect_unary_predicate.hpp>
#include <hamon/iterator/concepts/indirectly_copyable.hpp>
#include <hamon/iterator/projected.hpp>
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

template <typename Iter, typename Out1, typename Out2>
using partition_copy_result = in_out_out_result<Iter, Out1, Out2>;

struct partition_copy_fn
{
	template <
		HAMON_CONSTRAINED_PARAM(hamon::input_iterator, Iter),
		HAMON_CONSTRAINED_PARAM(hamon::sentinel_for, Iter, Sent),
		HAMON_CONSTRAINED_PARAM(hamon::weakly_incrementable, Out1),
		HAMON_CONSTRAINED_PARAM(hamon::weakly_incrementable, Out2),
		typename Proj = hamon::identity,
		typename ProjectedIter = hamon::projected<Iter, Proj>,
		HAMON_CONSTRAINED_PARAM(
			hamon::indirect_unary_predicate,
			ProjectedIter,
			Pred)
	>
	HAMON_CXX14_CONSTEXPR auto operator()(
		Iter first, Sent last,
		Out1 out_true, Out2 out_false,
		Pred pred, Proj proj = {}) const
	HAMON_RETURN_TYPE_REQUIRES_CLAUSES(
		partition_copy_result<Iter HAMON_PP_COMMA() Out1 HAMON_PP_COMMA() Out2>,
		HAMON_CONCEPTS_AND(
			hamon::indirectly_copyable<Iter HAMON_PP_COMMA() Out1>,
			hamon::indirectly_copyable<Iter HAMON_PP_COMMA() Out2>))
	{
		for (; first != last; ++first)
		{
			if (hamon::invoke(pred, hamon::invoke(proj, *first)))
			{
				*out_true = *first;
				++out_true;
			}
			else
			{
				*out_false = *first;
				++out_false;
			}
		}

		return { hamon::move(first), hamon::move(out_true), hamon::move(out_false) };
	}

	template <
		HAMON_CONSTRAINED_PARAM(ranges::input_range, Range),
		HAMON_CONSTRAINED_PARAM(hamon::weakly_incrementable, Out1),
		HAMON_CONSTRAINED_PARAM(hamon::weakly_incrementable, Out2),
		typename Proj = hamon::identity,
		typename ProjectedIter = hamon::projected<ranges::iterator_t<Range>, Proj>,
		HAMON_CONSTRAINED_PARAM(
			hamon::indirect_unary_predicate,
			ProjectedIter,
			Pred)
	>
	HAMON_CXX14_CONSTEXPR auto operator()(
		Range&& r, Out1 out_true, Out2 out_false,
		Pred pred, Proj proj = {}) const
	HAMON_RETURN_TYPE_REQUIRES_CLAUSES(
		partition_copy_result<ranges::borrowed_iterator_t<Range> HAMON_PP_COMMA() Out1 HAMON_PP_COMMA() Out2>,
		HAMON_CONCEPTS_AND(
			hamon::indirectly_copyable<ranges::iterator_t<Range> HAMON_PP_COMMA() Out1>,
			hamon::indirectly_copyable<ranges::iterator_t<Range> HAMON_PP_COMMA() Out2>))
	{
		return (*this)(
			ranges::begin(r), ranges::end(r),
			hamon::move(out_true), hamon::move(out_false),
			hamon::move(pred), hamon::move(proj));
	}
};

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR partition_copy_fn partition_copy{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_RANGES_PARTITION_COPY_HPP
