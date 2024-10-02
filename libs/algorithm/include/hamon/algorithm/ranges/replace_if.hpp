/**
 *	@file	replace_if.hpp
 *
 *	@brief	ranges::replace_if の定義
 */

#ifndef HAMON_ALGORITHM_RANGES_REPLACE_IF_HPP
#define HAMON_ALGORITHM_RANGES_REPLACE_IF_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_RANGES_ALGORITHM) && \
	defined(__cpp_lib_algorithm_default_value_type) && (__cpp_lib_algorithm_default_value_type >= 202403L)

#include <algorithm>

namespace hamon
{

namespace ranges
{

using std::ranges::replace_if;

}	// namespace ranges

}	// namespace hamon

#else

#include <hamon/algorithm/ranges/detail/return_type_requires_clauses.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/functional/identity.hpp>
#include <hamon/functional/invoke.hpp>
#include <hamon/iterator/concepts/input_iterator.hpp>
#include <hamon/iterator/concepts/sentinel_for.hpp>
#include <hamon/iterator/concepts/indirect_unary_predicate.hpp>
#include <hamon/iterator/concepts/indirectly_writable.hpp>
#include <hamon/iterator/projected.hpp>
#include <hamon/iterator/projected_value_t.hpp>
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

// 27.7.5 Replace[alg.replace]

struct replace_if_fn
{
	template <
		HAMON_CONSTRAINED_PARAM(hamon::input_iterator, I),
		HAMON_CONSTRAINED_PARAM(hamon::sentinel_for, I, S),
		typename Proj = hamon::identity,
		typename T = hamon::projected_value_t<I, Proj>,
		typename ProjectedIter = hamon::projected<I, Proj>,
		HAMON_CONSTRAINED_PARAM(hamon::indirect_unary_predicate, ProjectedIter, Pred)
	>
	HAMON_CXX14_CONSTEXPR auto operator()(
		I first, S last,
		Pred pred, T const& new_value, Proj proj = {}) const
	HAMON_RETURN_TYPE_REQUIRES_CLAUSES(
		I,
		hamon::indirectly_writable<I, T const&>)
	{
		for (; first != last; ++first)
		{
			if (hamon::invoke(pred, hamon::invoke(proj, *first)))
			{
				*first = new_value;
			}
		}

		return first;
	}

	template <
		HAMON_CONSTRAINED_PARAM(hamon::ranges::input_range, R),
		typename Proj = hamon::identity,
		typename T = hamon::projected_value_t<ranges::iterator_t<R>, Proj>,
		typename ProjectedIter = hamon::projected<ranges::iterator_t<R>, Proj>,
		HAMON_CONSTRAINED_PARAM(hamon::indirect_unary_predicate, ProjectedIter, Pred)
	>
	HAMON_CXX14_CONSTEXPR auto
	operator()(R&& r, Pred pred, T const& new_value, Proj proj = {}) const
	HAMON_RETURN_TYPE_REQUIRES_CLAUSES(
		ranges::borrowed_iterator_t<R>,
		hamon::indirectly_writable<ranges::iterator_t<R>, T const&>)
	{
		return (*this)(
			ranges::begin(r), ranges::end(r),
			hamon::move(pred), new_value, hamon::move(proj));
	}
};

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR replace_if_fn replace_if{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_RANGES_REPLACE_IF_HPP
