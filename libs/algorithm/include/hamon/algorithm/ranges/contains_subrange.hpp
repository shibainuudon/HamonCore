/**
 *	@file	contains_subrange.hpp
 *
 *	@brief	ranges::contains_subrange の定義
 */

#ifndef HAMON_ALGORITHM_RANGES_CONTAINS_SUBRANGE_HPP
#define HAMON_ALGORITHM_RANGES_CONTAINS_SUBRANGE_HPP

#include <algorithm>

#if defined(__cpp_lib_ranges_contains) && (__cpp_lib_ranges_contains >= 202207L)

namespace hamon
{

namespace ranges
{

using std::ranges::contains_subrange;

}	// namespace ranges

}	// namespace hamon

#else

#include <hamon/algorithm/ranges/search.hpp>
#include <hamon/algorithm/ranges/detail/return_type_requires_clauses.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/functional/ranges/equal_to.hpp>
#include <hamon/functional/identity.hpp>
#include <hamon/iterator/concepts/forward_iterator.hpp>
#include <hamon/iterator/concepts/sentinel_for.hpp>
#include <hamon/iterator/concepts/indirectly_comparable.hpp>
#include <hamon/ranges/concepts/forward_range.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/end.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace ranges
{

namespace detail
{

// 27.6.4 Contains[alg.contains]

struct contains_subrange_fn
{
	template <
		HAMON_CONSTRAINED_PARAM(hamon::forward_iterator, I1),
		HAMON_CONSTRAINED_PARAM(hamon::sentinel_for, I1, S1),
		HAMON_CONSTRAINED_PARAM(hamon::forward_iterator, I2),
		HAMON_CONSTRAINED_PARAM(hamon::sentinel_for, I2, S2),
		typename Pred = ranges::equal_to,
		typename Proj1 = hamon::identity,
		typename Proj2 = hamon::identity
	>
	HAMON_CXX14_CONSTEXPR auto
	operator()(
		I1 first1, S1 last1,
		I2 first2, S2 last2,
		Pred pred = {},
		Proj1 proj1 = {},
		Proj2 proj2 = {}) const
	HAMON_RETURN_TYPE_REQUIRES_CLAUSES(
		bool,
		hamon::indirectly_comparable<
			I1, I2, Pred, Proj1, Proj2>)
	{
		// [alg.contains]/2
		return (first2 == last2) ||
			!ranges::search(
				first1, last1,
				first2, last2,
				pred, proj1, proj2).empty();
	}

	template <
		HAMON_CONSTRAINED_PARAM(ranges::forward_range, R1),
		HAMON_CONSTRAINED_PARAM(ranges::forward_range, R2),
		typename Pred = ranges::equal_to,
		typename Proj1 = hamon::identity,
		typename Proj2 = hamon::identity
	>
	HAMON_CXX14_CONSTEXPR auto
	operator()(
		R1&& r1, R2&& r2,
		Pred pred = {},
		Proj1 proj1 = {},
		Proj2 proj2 = {}) const
	HAMON_RETURN_TYPE_REQUIRES_CLAUSES(
		bool,
		hamon::indirectly_comparable<
			ranges::iterator_t<R1>,
			ranges::iterator_t<R2>,
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

}	// namespace detail

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR detail::contains_subrange_fn contains_subrange{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_RANGES_CONTAINS_SUBRANGE_HPP
