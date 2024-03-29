﻿/**
 *	@file	replace_copy_if.hpp
 *
 *	@brief	ranges::replace_copy_if の定義
 */

#ifndef HAMON_ALGORITHM_RANGES_REPLACE_COPY_IF_HPP
#define HAMON_ALGORITHM_RANGES_REPLACE_COPY_IF_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_RANGES_ALGORITHM)

#include <algorithm>

namespace hamon
{

namespace ranges
{

using std::ranges::replace_copy_if;

}	// namespace ranges

}	// namespace hamon

#else

#include <hamon/algorithm/ranges/in_out_result.hpp>
#include <hamon/algorithm/ranges/detail/return_type_requires_clauses.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/functional/identity.hpp>
#include <hamon/functional/invoke.hpp>
#include <hamon/iterator/concepts/input_iterator.hpp>
#include <hamon/iterator/concepts/sentinel_for.hpp>
#include <hamon/iterator/concepts/output_iterator.hpp>
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

template <typename Iter, typename Out>
using replace_copy_if_result = in_out_result<Iter, Out>;

struct replace_copy_if_fn
{
	template <
		HAMON_CONSTRAINED_PARAM(hamon::input_iterator, Iter),
		HAMON_CONSTRAINED_PARAM(hamon::sentinel_for, Iter, Sent),
		typename T,
		HAMON_CONSTRAINED_PARAM(hamon::output_iterator, T const&, Out),
		typename Proj = hamon::identity,
		typename ProjectedIter = hamon::projected<Iter, Proj>,
		HAMON_CONSTRAINED_PARAM(
			hamon::indirect_unary_predicate,
			ProjectedIter,
			Pred)
	>
	HAMON_CXX14_CONSTEXPR auto operator()(
		Iter first, Sent last, Out result,
		Pred pred, T const& new_value, Proj proj = {}) const
	HAMON_RETURN_TYPE_REQUIRES_CLAUSES(
		replace_copy_if_result<Iter HAMON_PP_COMMA() Out>,
		hamon::indirectly_copyable<Iter, Out>)
	{
		for (; first != last; ++first, (void)++result)
		{
			if (hamon::invoke(pred, hamon::invoke(proj, *first)))
			{
				*result = new_value;
			}
			else
			{
				*result = *first;
			}
		}

		return { hamon::move(first), hamon::move(result) };
	}

	template <
		HAMON_CONSTRAINED_PARAM(hamon::ranges::input_range, Range),
		typename T,
		HAMON_CONSTRAINED_PARAM(hamon::output_iterator, T const&, Out),
		typename Proj = hamon::identity,
		typename ProjectedIter = hamon::projected<ranges::iterator_t<Range>, Proj>,
		HAMON_CONSTRAINED_PARAM(
			hamon::indirect_unary_predicate,
			ProjectedIter,
			Pred)
	>
	HAMON_CXX14_CONSTEXPR auto operator()(
		Range&& r, Out result,
		Pred pred, T const& new_value, Proj proj = {}) const
	HAMON_RETURN_TYPE_REQUIRES_CLAUSES(
		replace_copy_if_result<
			ranges::borrowed_iterator_t<Range> HAMON_PP_COMMA() Out>,
		hamon::indirectly_copyable<ranges::iterator_t<Range>, Out>)
	{
		return (*this)(
			ranges::begin(r), ranges::end(r),
			hamon::move(result),
			hamon::move(pred),
			new_value,
			hamon::move(proj));
	}
};

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR replace_copy_if_fn replace_copy_if{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_RANGES_REPLACE_COPY_IF_HPP
