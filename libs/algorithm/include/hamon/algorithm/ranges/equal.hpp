/**
 *	@file	equal.hpp
 *
 *	@brief	ranges::equal の定義
 */

#ifndef HAMON_ALGORITHM_RANGES_EQUAL_HPP
#define HAMON_ALGORITHM_RANGES_EQUAL_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_RANGES_ALGORITHM)

#include <algorithm>

namespace hamon
{

namespace ranges
{

using std::ranges::equal;

}	// namespace ranges

}	// namespace hamon

#else

#include <hamon/algorithm/ranges/detail/return_type_requires_clauses.hpp>
#include <hamon/concepts/same_as.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/cstring/memcmp.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/functional/ranges/equal_to.hpp>
#include <hamon/functional/identity.hpp>
#include <hamon/functional/invoke.hpp>
#include <hamon/iterator/concepts/input_iterator.hpp>
#include <hamon/iterator/concepts/indirectly_comparable.hpp>
#include <hamon/iterator/concepts/sentinel_for.hpp>
#include <hamon/iterator/concepts/sized_sentinel_for.hpp>
#include <hamon/iterator/ranges/distance.hpp>
#include <hamon/iterator/iter_value_t.hpp>
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

struct equal_fn
{
private:
	template <
		typename Iter1, typename Iter2,
		typename Pred, typename Proj1, typename Proj2,
		HAMON_CONSTRAINED_PARAM(hamon::sized_sentinel_for, Iter1, Sent1),
		HAMON_CONSTRAINED_PARAM(hamon::sized_sentinel_for, Iter2, Sent2)
	>
	static HAMON_CXX14_CONSTEXPR bool impl(
		hamon::detail::overload_priority<1>,
		Iter1 first1, Sent1 last1,
		Iter2 first2, Sent2 last2,
		Pred pred, Proj1 proj1, Proj2 proj2)
	{
		auto d1 = ranges::distance(first1, last1);
		auto d2 = ranges::distance(first2, last2);
		if (d1 != d2)
		{
			return false;
		}

		/*
		using ValueType1 = hamon::iter_value_t<Iter1>;
		using ValueType2 = hamon::iter_value_t<Iter2>;
		constexpr bool use_memcmp
			= ((hamon::is_integral<ValueType1>::value || hamon::is_pointer<ValueType1>::value)
			//&& __memcmpable<Iter1, Iter2>::__value
			&& hamon::is_same<Pred, ranges::equal_to>::value
			&& hamon::is_same<Proj1, hamon::identity>::value
			&& hamon::is_same<Proj2, hamon::identity>::value);
		if constexpr (use_memcmp)
		{
			if (const hamon::size_t len = (last1 - first1))
			{
				return !hamon::memcmp(first1, first2, len);
			}
			return true;
		}
		else
		*/
		{
			for (; first1 != last1; ++first1, (void)++first2)
			{
				if (!(bool)hamon::invoke(pred,
					hamon::invoke(proj1, *first1),
					hamon::invoke(proj2, *first2)))
				{
					return false;
				}
			}
			return true;
		}
	}

	template <
		typename Iter1, typename Sent1,
		typename Iter2, typename Sent2,
		typename Pred, typename Proj1, typename Proj2
	>
	static HAMON_CXX14_CONSTEXPR bool impl(
		hamon::detail::overload_priority<0>,
		Iter1 first1, Sent1 last1,
		Iter2 first2, Sent2 last2,
		Pred pred, Proj1 proj1, Proj2 proj2)
	{
		for (; first1 != last1 && first2 != last2; ++first1, (void)++first2)
		{
			if (!(bool)hamon::invoke(pred,
				hamon::invoke(proj1, *first1),
				hamon::invoke(proj2, *first2)))
			{
				return false;
			}
		}
		return first1 == last1 && first2 == last2;
	}

public:
	template <
		HAMON_CONSTRAINED_PARAM(hamon::input_iterator, Iter1),
		HAMON_CONSTRAINED_PARAM(hamon::sentinel_for, Iter1, Sent1),
		HAMON_CONSTRAINED_PARAM(hamon::input_iterator, Iter2),
		HAMON_CONSTRAINED_PARAM(hamon::sentinel_for, Iter2, Sent2),
		typename Pred = ranges::equal_to,
		typename Proj1 = hamon::identity,
		typename Proj2 = hamon::identity
	>
	HAMON_CXX14_CONSTEXPR auto operator()(
		Iter1 first1, Sent1 last1,
		Iter2 first2, Sent2 last2,
		Pred pred = {},
		Proj1 proj1 = {},
		Proj2 proj2 = {}) const
	HAMON_RETURN_TYPE_REQUIRES_CLAUSES(
		bool,
		hamon::indirectly_comparable<Iter1, Iter2, Pred, Proj1, Proj2>)
	{
		return impl(hamon::detail::overload_priority<1>{},
			first1, last1,
			first2, last2,
			pred, proj1, proj2);
	}

	template <
		HAMON_CONSTRAINED_PARAM(ranges::input_range, Range1),
		HAMON_CONSTRAINED_PARAM(ranges::input_range, Range2),
		typename Pred = ranges::equal_to,
		typename Proj1 = hamon::identity,
		typename Proj2 = hamon::identity,
		typename Iter1 = ranges::iterator_t<Range1>,
		typename Iter2 = ranges::iterator_t<Range2>
	>
	HAMON_CXX14_CONSTEXPR auto operator()(
		Range1&& r1,
		Range2&& r2,
		Pred pred = {},
		Proj1 proj1 = {},
		Proj2 proj2 = {}) const
	HAMON_RETURN_TYPE_REQUIRES_CLAUSES(
		bool,
		hamon::indirectly_comparable<Iter1, Iter2, Pred, Proj1, Proj2>)
	{
		return (*this)(
			ranges::begin(r1), ranges::end(r1),
			ranges::begin(r2), ranges::end(r2),
			hamon::move(pred),
			hamon::move(proj1),
			hamon::move(proj2));
	}
};

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR equal_fn equal{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_RANGES_EQUAL_HPP
