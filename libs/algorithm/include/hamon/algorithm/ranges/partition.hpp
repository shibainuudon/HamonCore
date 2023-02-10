/**
 *	@file	partition.hpp
 *
 *	@brief	ranges::partition の定義
 */

#ifndef HAMON_ALGORITHM_RANGES_PARTITION_HPP
#define HAMON_ALGORITHM_RANGES_PARTITION_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_RANGES_ALGORITHM)

#include <algorithm>

namespace hamon
{

namespace ranges
{

using std::ranges::partition;

}	// namespace ranges

}	// namespace hamon

#else

#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/functional/identity.hpp>
#include <hamon/functional/invoke.hpp>
#include <hamon/iterator/concepts/permutable.hpp>
#include <hamon/iterator/concepts/sentinel_for.hpp>
#include <hamon/iterator/concepts/indirect_unary_predicate.hpp>
#include <hamon/iterator/concepts/bidirectional_iterator.hpp>
#include <hamon/iterator/ranges/next.hpp>
#include <hamon/iterator/ranges/iter_swap.hpp>
#include <hamon/iterator/projected.hpp>
#include <hamon/ranges/concepts/forward_range.hpp>
#include <hamon/ranges/views/subrange.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/ranges/borrowed_subrange_t.hpp>
#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/end.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/config.hpp>
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

struct partition_fn
{
private:
	template <
		HAMON_CONSTRAINED_PARAM(hamon::bidirectional_iterator, Iter),
		typename Sent,
		typename Proj,
		typename Pred
	>
	static HAMON_CXX14_CONSTEXPR ranges::subrange<Iter>
	impl(Iter first, Sent last, Pred pred, Proj proj,
		hamon::detail::overload_priority<1>)
	{
		auto lasti = ranges::next(first, last);
		auto tail = lasti;
		for (;;)
		{
			for (;;)
			{
				if (first == tail)
				{
					return { std::move(first), std::move(lasti) };
				}
				else if (hamon::invoke(pred, hamon::invoke(proj, *first)))
				{
					++first;
				}
				else
				{
					break;
				}
			}

			--tail;

			for (;;)
			{
				if (first == tail)
				{
					return { std::move(first), std::move(lasti) };
				}
				else if (!(bool)hamon::invoke(pred, hamon::invoke(proj, *tail)))
				{
					--tail;
				}
				else
				{
					break;
				}
			}

			ranges::iter_swap(first, tail);
			++first;
		}
	}

	template <
		typename Iter,
		typename Sent,
		typename Proj,
		typename Pred
	>
	static HAMON_CXX14_CONSTEXPR ranges::subrange<Iter>
	impl(Iter first, Sent last, Pred pred, Proj proj,
		hamon::detail::overload_priority<0>)
	{
		if (first == last)
		{
			return { std::move(first), std::move(first) };
		}

		while (hamon::invoke(pred, hamon::invoke(proj, *first)))
		{
			if (++first == last)
			{
				return { std::move(first), std::move(first) };
			}
		}

		auto next_it = first;
		while (++next_it != last)
		{
			if (hamon::invoke(pred, hamon::invoke(proj, *next_it)))
			{
				ranges::iter_swap(first, next_it);
				++first;
			}
		}

		return { std::move(first), std::move(next_it) };
	}

public:
	template <
		HAMON_CONSTRAINED_PARAM(hamon::permutable, Iter),
		HAMON_CONSTRAINED_PARAM(hamon::sentinel_for, Iter, Sent),
		typename Proj = hamon::identity,
		typename ProjectedIter = hamon::projected<Iter, Proj>,
		HAMON_CONSTRAINED_PARAM(
			hamon::indirect_unary_predicate,
			ProjectedIter,
			Pred)
	>
	HAMON_CXX14_CONSTEXPR ranges::subrange<Iter>
	operator()(
		Iter first, Sent last,
		Pred pred, Proj proj = {}) const
	{
		return impl(
			std::move(first),
			std::move(last),
			std::move(pred),
			std::move(proj),
			hamon::detail::overload_priority<1>{});
	}

	template <
		HAMON_CONSTRAINED_PARAM(ranges::forward_range, Range),
		typename Proj = hamon::identity,
		typename ProjectedIter = hamon::projected<ranges::iterator_t<Range>, Proj>,
		HAMON_CONSTRAINED_PARAM(
			hamon::indirect_unary_predicate,
			ProjectedIter,
			Pred)
	>
	HAMON_CXX14_CONSTEXPR auto
	operator()(Range&& r, Pred pred, Proj proj = {}) const
	HAMON_RETURN_TYPE_REQUIRES_CLAUSES(
		ranges::borrowed_subrange_t<Range>,
		hamon::permutable<ranges::iterator_t<Range>>)
	{
		return (*this)(
			ranges::begin(r), ranges::end(r),
			std::move(pred), std::move(proj));
	}
};

#undef HAMON_RETURN_TYPE_REQUIRES_CLAUSES

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR partition_fn partition{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_RANGES_PARTITION_HPP
