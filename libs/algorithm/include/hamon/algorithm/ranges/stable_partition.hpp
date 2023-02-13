/**
 *	@file	stable_partition.hpp
 *
 *	@brief	ranges::stable_partition の定義
 */

#ifndef HAMON_ALGORITHM_RANGES_STABLE_PARTITION_HPP
#define HAMON_ALGORITHM_RANGES_STABLE_PARTITION_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_RANGES_ALGORITHM)

#include <algorithm>

namespace hamon
{

namespace ranges
{

using std::ranges::stable_partition;

}	// namespace ranges

}	// namespace hamon

#else

#include <hamon/algorithm/stable_partition.hpp>
#include <hamon/algorithm/ranges/detail/make_pred_proj.hpp>
#include <hamon/algorithm/ranges/detail/return_type_requires_clauses.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/functional/identity.hpp>
#include <hamon/iterator/concepts/bidirectional_iterator.hpp>
#include <hamon/iterator/concepts/sentinel_for.hpp>
#include <hamon/iterator/concepts/indirect_unary_predicate.hpp>
#include <hamon/iterator/concepts/permutable.hpp>
#include <hamon/iterator/ranges/next.hpp>
#include <hamon/iterator/projected.hpp>
#include <hamon/ranges/concepts/bidirectional_range.hpp>
#include <hamon/ranges/views/subrange.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/ranges/borrowed_subrange_t.hpp>
#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/end.hpp>
#include <hamon/config.hpp>
#include <utility>

namespace hamon
{

namespace ranges
{

struct stable_partition_fn
{
	template <
		HAMON_CONSTRAINED_PARAM(hamon::bidirectional_iterator, Iter),
		HAMON_CONSTRAINED_PARAM(hamon::sentinel_for, Iter, Sent),
		typename Proj = hamon::identity,
		typename ProjectedIter = hamon::projected<Iter, Proj>,
		HAMON_CONSTRAINED_PARAM(
			hamon::indirect_unary_predicate, ProjectedIter, Pred)
	>
	auto operator()(
		Iter first, Sent last,
		Pred pred, Proj proj = {}) const
	HAMON_RETURN_TYPE_REQUIRES_CLAUSES(
		ranges::subrange<Iter>,
		hamon::permutable<Iter>)
	{
		auto lasti = ranges::next(first, last);
		auto middle = hamon::stable_partition(
			std::move(first), lasti, detail::make_pred_proj(pred, proj));
		return { std::move(middle), std::move(lasti) };
	}

	template <
		HAMON_CONSTRAINED_PARAM(ranges::bidirectional_range, Range),
		typename Proj = hamon::identity,
		HAMON_CONSTRAINED_PARAM(
			hamon::indirect_unary_predicate,
			hamon::projected<ranges::iterator_t<Range>, Proj>,
			Pred)
	>
	auto operator()(Range&& r, Pred pred, Proj proj = {}) const
	HAMON_RETURN_TYPE_REQUIRES_CLAUSES(
		ranges::borrowed_subrange_t<Range>,
		hamon::permutable<ranges::iterator_t<Range>>)
	{
		return (*this)(
			ranges::begin(r), ranges::end(r),
			std::move(pred), std::move(proj));
	}
};

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR stable_partition_fn stable_partition{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_RANGES_STABLE_PARTITION_HPP
