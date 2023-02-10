/**
 *	@file	minmax.hpp
 *
 *	@brief	ranges::minmax の定義
 */

#ifndef HAMON_ALGORITHM_RANGES_MINMAX_HPP
#define HAMON_ALGORITHM_RANGES_MINMAX_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_RANGES_ALGORITHM)

#include <algorithm>

namespace hamon
{

namespace ranges
{

using std::ranges::minmax;

}	// namespace ranges

}	// namespace hamon

#else

#include <hamon/algorithm/ranges/min_max_result.hpp>
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
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/config.hpp>
#include <hamon/assert.hpp>
#include <initializer_list>
#include <utility>

namespace hamon
{

namespace ranges
{

#if defined(HAMON_HAS_CXX20_CONCEPTS)
#define HAMON_RETURN_TYPE_REQUIRES_CLAUSES(T, ...)	\
	-> T requires __VA_ARGS__
#else
#define HAMON_RETURN_TYPE_REQUIRES_CLAUSES(T, ...)	\
	-> hamon::enable_if_t<__VA_ARGS__::value, T>
#endif

template <typename T>
using minmax_result = min_max_result<T>;

struct minmax_fn
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
	HAMON_CXX14_CONSTEXPR minmax_result<T const&>
	operator()(T const& a, T const& b,
		Comp comp = {}, Proj proj = {}) const
	{
		if (hamon::invoke(std::move(comp),
			hamon::invoke(proj, b),
			hamon::invoke(proj, a)))
		{
			return { b, a };
		}
		else
		{
			return { a, b };
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
		minmax_result<ranges::range_value_t<Range>>,
		hamon::indirectly_copyable_storable<
			ranges::iterator_t<Range>,
			ranges::range_value_t<Range>*>)
	{
		auto first = ranges::begin(r);
		auto last = ranges::end(r);
		HAMON_ASSERT(bool(first != last));
		minmax_result<ranges::range_value_t<Range>> result = { *first, *first };
		while (++first != last)
		{
			auto tmp = *first;
			if (hamon::invoke(comp,
				hamon::invoke(proj, tmp),
				hamon::invoke(proj, result.min)))
			{
				result.min = std::move(tmp);
			}

			if (!(bool)hamon::invoke(comp,
				hamon::invoke(proj, tmp),
				hamon::invoke(proj, result.max)))
			{
				result.max = std::move(tmp);
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
	HAMON_CXX14_CONSTEXPR minmax_result<T>
	operator()(std::initializer_list<T> r,
		Comp comp = {}, Proj proj = {}) const
	{
		return (*this)(ranges::subrange<T const*>(r),
			std::move(comp), std::move(proj));
	}
};

#undef HAMON_RETURN_TYPE_REQUIRES_CLAUSES

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR minmax_fn minmax{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_RANGES_MINMAX_HPP
