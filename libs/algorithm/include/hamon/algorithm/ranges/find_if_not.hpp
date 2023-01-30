/**
 *	@file	find_if_not.hpp
 *
 *	@brief	ranges::find_if_not の定義
 */

#ifndef HAMON_ALGORITHM_RANGES_FIND_IF_NOT_HPP
#define HAMON_ALGORITHM_RANGES_FIND_IF_NOT_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_RANGES_ALGORITHM)

#include <algorithm>

namespace hamon
{

namespace ranges
{

using std::ranges::find_if_not;

}	// namespace ranges

}	// namespace hamon

#else

#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/functional/identity.hpp>
#include <hamon/functional/invoke.hpp>
#include <hamon/iterator/concepts/input_iterator.hpp>
#include <hamon/iterator/concepts/sentinel_for.hpp>
#include <hamon/iterator/concepts/indirect_unary_predicate.hpp>
#include <hamon/iterator/projected.hpp>
#include <hamon/ranges/concepts/input_range.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/ranges/borrowed_iterator_t.hpp>
#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/end.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/config.hpp>
#include <utility>

namespace hamon
{

namespace ranges
{

struct find_if_not_fn
{
	template <
		HAMON_CONSTRAINED_PARAM(hamon::input_iterator, Iter),
		HAMON_CONSTRAINED_PARAM(hamon::sentinel_for, Iter, Sent),
		typename Proj = hamon::identity,
		typename ProjectedIter = hamon::projected<Iter, Proj>,
		HAMON_CONSTRAINED_PARAM(
			hamon::indirect_unary_predicate,
			ProjectedIter,
			Pred)
	>
	HAMON_CXX14_CONSTEXPR Iter operator()(
		Iter first, Sent last, Pred pred, Proj proj = {}) const
	{
		while (first != last &&
			(bool)hamon::invoke(pred, hamon::invoke(proj, *first)))
		{
			++first;
		}

		return first;
	}

	template <
		HAMON_CONSTRAINED_PARAM(hamon::ranges::input_range, Range),
		typename Proj = hamon::identity,
		typename ProjectedIter = hamon::projected<ranges::iterator_t<Range>, Proj>,
		HAMON_CONSTRAINED_PARAM(
			hamon::indirect_unary_predicate,
			ProjectedIter,
			Pred)
	>
	HAMON_CXX14_CONSTEXPR ranges::borrowed_iterator_t<Range>
		operator()(Range&& r, Pred pred, Proj proj = {}) const
	{
		return (*this)(
			ranges::begin(r), ranges::end(r), std::move(pred), std::move(proj));
	}
};

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR find_if_not_fn find_if_not{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_RANGES_FIND_IF_NOT_HPP
