/**
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
#include <hamon/concepts/detail/and.hpp>
#include <hamon/functional/identity.hpp>
#include <hamon/functional/invoke.hpp>
#include <hamon/iterator/concepts/input_iterator.hpp>
#include <hamon/iterator/concepts/sentinel_for.hpp>
#include <hamon/iterator/concepts/output_iterator.hpp>
#include <hamon/iterator/concepts/indirect_unary_predicate.hpp>
#include <hamon/iterator/concepts/indirectly_copyable.hpp>
#include <hamon/iterator/iter_value_t.hpp>
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

template <typename I, typename O>
using replace_copy_if_result = in_out_result<I, O>;

struct replace_copy_if_fn
{
	template <
		HAMON_CONSTRAINED_PARAM(hamon::input_iterator, I),
		HAMON_CONSTRAINED_PARAM(hamon::sentinel_for, I, S),
		typename O,
		typename T = hamon::iter_value_t<O>,
		typename Proj = hamon::identity,
		typename ProjectedIter = hamon::projected<I, Proj>,
		HAMON_CONSTRAINED_PARAM(hamon::indirect_unary_predicate, ProjectedIter, Pred)
	>
	HAMON_CXX14_CONSTEXPR auto operator()(
		I first, S last, O result,
		Pred pred, T const& new_value, Proj proj = {}) const
	HAMON_RETURN_TYPE_REQUIRES_CLAUSES(
		replace_copy_if_result<I HAMON_PP_COMMA() O>,
		HAMON_CONCEPTS_AND(
			hamon::indirectly_copyable<I HAMON_PP_COMMA() O>,
			hamon::output_iterator<O HAMON_PP_COMMA() T const&>))
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
		HAMON_CONSTRAINED_PARAM(hamon::ranges::input_range, R),
		typename O,
		typename T = hamon::iter_value_t<O>,
		typename Proj = hamon::identity,
		typename ProjectedIter = hamon::projected<ranges::iterator_t<R>, Proj>,
		HAMON_CONSTRAINED_PARAM(hamon::indirect_unary_predicate, ProjectedIter, Pred)
	>
	HAMON_CXX14_CONSTEXPR auto operator()(
		R&& r, O result,
		Pred pred, T const& new_value, Proj proj = {}) const
	HAMON_RETURN_TYPE_REQUIRES_CLAUSES(
		replace_copy_if_result<
			ranges::borrowed_iterator_t<R> HAMON_PP_COMMA() O>,
		HAMON_CONCEPTS_AND(
			hamon::indirectly_copyable<ranges::iterator_t<R> HAMON_PP_COMMA() O>,
			hamon::output_iterator<O HAMON_PP_COMMA() T const&>))
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
