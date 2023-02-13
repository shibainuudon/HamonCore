/**
 *	@file	max.hpp
 *
 *	@brief	ranges::max の定義
 */

#ifndef HAMON_ALGORITHM_RANGES_MAX_HPP
#define HAMON_ALGORITHM_RANGES_MAX_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_RANGES_ALGORITHM)

#include <algorithm>

namespace hamon
{

namespace ranges
{

using std::ranges::max;

}	// namespace ranges

}	// namespace hamon

#else

#include <hamon/algorithm/ranges/detail/return_type_requires_clauses.hpp>
#include <hamon/concepts/copyable.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/functional/ranges/less.hpp>
#include <hamon/functional/identity.hpp>
#include <hamon/functional/invoke.hpp>
#include <hamon/iterator/concepts/indirect_strict_weak_order.hpp>
#include <hamon/iterator/concepts/indirectly_copyable_storable.hpp>
#include <hamon/iterator/projected.hpp>
#include <hamon/ranges/concepts/input_range.hpp>
#include <hamon/ranges/views/subrange.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/ranges/range_value_t.hpp>
#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/end.hpp>
#include <hamon/config.hpp>
#include <hamon/assert.hpp>
#include <initializer_list>
#include <utility>

namespace hamon
{

namespace ranges
{

struct max_fn
{
	template <
		typename T,
		typename Proj = hamon::identity,
		typename ProjectedIter = hamon::projected<T const*, Proj>,
		HAMON_CONSTRAINED_PARAM_D(
			hamon::indirect_strict_weak_order,
			ProjectedIter,
			Comp,
			ranges::less)
	>
	HAMON_CXX14_CONSTEXPR T const& operator()(
		T const& a, T const& b, Comp comp = {}, Proj proj = {}) const
	{
		if (hamon::invoke(std::move(comp),
			hamon::invoke(proj, a),
			hamon::invoke(proj, b)))
		{
			return b;
		}
		else
		{
			return a;
		}
	}

	template <
		HAMON_CONSTRAINED_PARAM(ranges::input_range, Range),
		typename Proj = hamon::identity,
		typename ProjectedIter = hamon::projected<ranges::iterator_t<Range>, Proj>,
		HAMON_CONSTRAINED_PARAM_D(
			hamon::indirect_strict_weak_order,
			ProjectedIter,
			Comp,
			ranges::less)
	>
	HAMON_CXX14_CONSTEXPR auto
	operator()(Range&& r, Comp comp = {}, Proj proj = {}) const
	HAMON_RETURN_TYPE_REQUIRES_CLAUSES(
		ranges::range_value_t<Range>,
		hamon::indirectly_copyable_storable<
			ranges::iterator_t<Range>,
			ranges::range_value_t<Range>*>)
	{
		auto first = ranges::begin(r);
		auto last = ranges::end(r);
		HAMON_ASSERT(bool(first != last));
		auto result = *first;
		while (++first != last)
		{
			auto tmp = *first;
			if (hamon::invoke(comp,
				hamon::invoke(proj, result),
				hamon::invoke(proj, tmp)))
			{
				result = std::move(tmp);
			}
		}

		return result;
	}

	template <
		HAMON_CONSTRAINED_PARAM(hamon::copyable, T),
		typename Proj = hamon::identity,
		typename ProjectedIter = hamon::projected<T const*, Proj>,
		HAMON_CONSTRAINED_PARAM_D(
			hamon::indirect_strict_weak_order,
			ProjectedIter,
			Comp,
			ranges::less)
	>
	HAMON_CXX14_CONSTEXPR T
	operator()(std::initializer_list<T> r, Comp comp = {}, Proj proj = {}) const
	{
		return (*this)(
			ranges::subrange<T const*>(r),
			std::move(comp), std::move(proj));
	}
};

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR max_fn max{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_RANGES_MAX_HPP
