/**
 *	@file	starts_with.hpp
 *
 *	@brief	ranges::starts_with の定義
 */

#ifndef HAMON_ALGORITHM_RANGES_STARTS_WITH_HPP
#define HAMON_ALGORITHM_RANGES_STARTS_WITH_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_RANGES_ALGORITHM) &&	\
	defined(__cpp_lib_ranges_starts_ends_with) && (__cpp_lib_ranges_starts_ends_with >= 202106L)

#include <algorithm>

namespace hamon
{

namespace ranges
{

using std::ranges::starts_with;

}	// namespace ranges

}	// namespace hamon

#else

#include <hamon/algorithm/ranges/mismatch.hpp>
#include <hamon/algorithm/ranges/detail/return_type_requires_clauses.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/functional/ranges/equal_to.hpp>
#include <hamon/functional/identity.hpp>
#include <hamon/iterator/concepts/input_iterator.hpp>
#include <hamon/iterator/concepts/sentinel_for.hpp>
#include <hamon/iterator/concepts/indirectly_comparable.hpp>
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

struct starts_with_fn
{
	template <
		HAMON_CONSTRAINED_PARAM(hamon::input_iterator, I1),
		HAMON_CONSTRAINED_PARAM(hamon::sentinel_for, I1, S1),
		HAMON_CONSTRAINED_PARAM(hamon::input_iterator, I2),
		HAMON_CONSTRAINED_PARAM(hamon::sentinel_for, I2, S2),
		typename Pred = ranges::equal_to,
		typename Proj1 = hamon::identity,
		typename Proj2 = hamon::identity
	>
	HAMON_CXX14_CONSTEXPR auto operator()(
		I1 first1, S1 last1,
		I2 first2, S2 last2,
		Pred pred = {},
		Proj1 proj1 = {},
		Proj2 proj2 = {}) const
	HAMON_RETURN_TYPE_REQUIRES_CLAUSES(
		bool,
		hamon::indirectly_comparable<I1, I2, Pred, Proj1, Proj2>)
	{
		return ranges::mismatch(
			hamon::move(first1), last1,
			hamon::move(first2), last2,
			hamon::move(pred), hamon::move(proj1), hamon::move(proj2)
		).in2 == last2;
	}

	template <
		HAMON_CONSTRAINED_PARAM(ranges::input_range, R1),
		HAMON_CONSTRAINED_PARAM(ranges::input_range, R2),
		typename Pred = ranges::equal_to,
		typename Proj1 = hamon::identity,
		typename Proj2 = hamon::identity
	>
	HAMON_CXX14_CONSTEXPR auto operator()(
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
			hamon::move(pred), hamon::move(proj1), hamon::move(proj2));
	}
};

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR starts_with_fn starts_with{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_RANGES_STARTS_WITH_HPP
