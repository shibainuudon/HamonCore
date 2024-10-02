/**
 *	@file	count.hpp
 *
 *	@brief	ranges::count の定義
 */

#ifndef HAMON_ALGORITHM_RANGES_COUNT_HPP
#define HAMON_ALGORITHM_RANGES_COUNT_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_RANGES_ALGORITHM) && \
	defined(__cpp_lib_algorithm_default_value_type) && (__cpp_lib_algorithm_default_value_type >= 202403L)

#include <algorithm>

namespace hamon
{

namespace ranges
{

using std::ranges::count;

}	// namespace ranges

}	// namespace hamon

#else

#include <hamon/algorithm/ranges/detail/return_type_requires_clauses.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/functional/ranges/equal_to.hpp>
#include <hamon/functional/identity.hpp>
#include <hamon/functional/invoke.hpp>
#include <hamon/iterator/concepts/input_iterator.hpp>
#include <hamon/iterator/concepts/sentinel_for.hpp>
#include <hamon/iterator/concepts/indirect_binary_predicate.hpp>
#include <hamon/iterator/projected.hpp>
#include <hamon/iterator/projected_value_t.hpp>
#include <hamon/iterator/iter_difference_t.hpp>
#include <hamon/ranges/concepts/input_range.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/ranges/range_difference_t.hpp>
#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/end.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace ranges
{

// 27.6.11 Count[alg.count]

struct count_fn
{
	template<
		HAMON_CONSTRAINED_PARAM(hamon::input_iterator, I),
		HAMON_CONSTRAINED_PARAM(hamon::sentinel_for, I, S),
		typename Proj = hamon::identity,
		typename T = hamon::projected_value_t<I, Proj>
	>
	HAMON_CXX14_CONSTEXPR auto operator()(
		I first, S last, T const& value, Proj proj = {}) const
	HAMON_RETURN_TYPE_REQUIRES_CLAUSES(
		hamon::iter_difference_t<I>,
		hamon::indirect_binary_predicate<
			ranges::equal_to,
			hamon::projected<I, Proj>,
			T const*>)
	{
		hamon::iter_difference_t<I> n = 0;
		for (; first != last; ++first)
		{
			if (hamon::invoke(proj, *first) == value)
			{
				++n;
			}
		}

		return n;
	}

	template<
		HAMON_CONSTRAINED_PARAM(hamon::ranges::input_range, R),
		typename Proj = hamon::identity,
		typename T = hamon::projected_value_t<ranges::iterator_t<R>, Proj>
	>
	HAMON_CXX14_CONSTEXPR auto operator()(
		R&& r, T const& value, Proj proj = {}) const
	HAMON_RETURN_TYPE_REQUIRES_CLAUSES(
		ranges::range_difference_t<R>,
		hamon::indirect_binary_predicate<
			ranges::equal_to,
			hamon::projected<ranges::iterator_t<R>, Proj>,
			T const*>)
	{
		return (*this)(
			ranges::begin(r), ranges::end(r), value, hamon::move(proj));
	}
};

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR count_fn count{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_RANGES_COUNT_HPP
