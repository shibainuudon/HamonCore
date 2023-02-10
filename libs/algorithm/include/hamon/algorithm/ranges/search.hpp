/**
 *	@file	search.hpp
 *
 *	@brief	ranges::search の定義
 */

#ifndef HAMON_ALGORITHM_RANGES_SEARCH_HPP
#define HAMON_ALGORITHM_RANGES_SEARCH_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_RANGES_ALGORITHM)

#include <algorithm>

namespace hamon
{

namespace ranges
{

using std::ranges::search;

}	// namespace ranges

}	// namespace hamon

#else

#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/functional/ranges/equal_to.hpp>
#include <hamon/functional/identity.hpp>
#include <hamon/functional/invoke.hpp>
#include <hamon/iterator/concepts/forward_iterator.hpp>
#include <hamon/iterator/concepts/sentinel_for.hpp>
#include <hamon/iterator/concepts/indirectly_comparable.hpp>
#include <hamon/ranges/views/subrange.hpp>
#include <hamon/ranges/concepts/forward_range.hpp>
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

struct search_fn
{
	template<
		HAMON_CONSTRAINED_PARAM(hamon::forward_iterator, Iter1),
		HAMON_CONSTRAINED_PARAM(hamon::sentinel_for, Iter1, Sent1),
		HAMON_CONSTRAINED_PARAM(hamon::forward_iterator, Iter2),
		HAMON_CONSTRAINED_PARAM(hamon::sentinel_for, Iter2, Sent2),
		typename Pred = ranges::equal_to,
		typename Proj1 = hamon::identity,
		typename Proj2 = hamon::identity
	>
	HAMON_CXX14_CONSTEXPR auto
	operator()(
		Iter1 first1, Sent1 last1,
		Iter2 first2, Sent2 last2,
		Pred pred = {},
		Proj1 proj1 = {},
		Proj2 proj2 = {}) const
	HAMON_RETURN_TYPE_REQUIRES_CLAUSES(
		ranges::subrange<Iter1>,
		hamon::indirectly_comparable<Iter1, Iter2, Pred, Proj1, Proj2>)
	{
		if (first1 == last1 || first2 == last2)
		{
			return { first1, first1 };
		}

		for (;;)
		{
			for (;;)
			{
				if (first1 == last1)
				{
					return { first1, first1 };
				}

				if (hamon::invoke(pred,
					hamon::invoke(proj1, *first1),
					hamon::invoke(proj2, *first2)))
				{
					break;
				}

				++first1;
			}

			auto cur1 = first1;
			auto cur2 = first2;

			for (;;)
			{
				if (++cur2 == last2)
				{
					return { first1, ++cur1 };
				}

				if (++cur1 == last1)
				{
					return { cur1, cur1 };
				}

				if (!(bool)hamon::invoke(pred,
					hamon::invoke(proj1, *cur1),
					hamon::invoke(proj2, *cur2)))
				{
					++first1;
					break;
				}
			}
		}
	}

	template<
		HAMON_CONSTRAINED_PARAM(hamon::ranges::forward_range, Range1),
		HAMON_CONSTRAINED_PARAM(hamon::ranges::forward_range, Range2),
		typename Pred = ranges::equal_to,
		typename Proj1 = hamon::identity,
		typename Proj2 = hamon::identity
	>
	HAMON_CXX14_CONSTEXPR auto
	operator()(
		Range1&& r1,
		Range2&& r2,
		Pred pred = {},
		Proj1 proj1 = {},
		Proj2 proj2 = {}) const
	HAMON_RETURN_TYPE_REQUIRES_CLAUSES(
		ranges::borrowed_subrange_t<Range1>,
		hamon::indirectly_comparable<
			ranges::iterator_t<Range1>,
			ranges::iterator_t<Range2>,
			Pred, Proj1, Proj2>)
	{
		return (*this)(
			ranges::begin(r1), ranges::end(r1),
			ranges::begin(r2), ranges::end(r2),
			std::move(pred),
			std::move(proj1),
			std::move(proj2));
	}
};

#undef HAMON_RETURN_TYPE_REQUIRES_CLAUSES

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR search_fn search{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_RANGES_SEARCH_HPP
