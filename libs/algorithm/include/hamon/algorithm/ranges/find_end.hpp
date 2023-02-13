/**
 *	@file	find_end.hpp
 *
 *	@brief	ranges::find_end の定義
 */

#ifndef HAMON_ALGORITHM_RANGES_FIND_END_HPP
#define HAMON_ALGORITHM_RANGES_FIND_END_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_RANGES_ALGORITHM)

#include <algorithm>

namespace hamon
{

namespace ranges
{

using std::ranges::find_end;

}	// namespace ranges

}	// namespace hamon

#else

#include <hamon/algorithm/ranges/search.hpp>
#include <hamon/algorithm/ranges/detail/return_type_requires_clauses.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/functional/ranges/equal_to.hpp>
#include <hamon/functional/identity.hpp>
#include <hamon/iterator/concepts/forward_iterator.hpp>
#include <hamon/iterator/concepts/bidirectional_iterator.hpp>
#include <hamon/iterator/concepts/sentinel_for.hpp>
#include <hamon/iterator/concepts/indirectly_comparable.hpp>
#include <hamon/iterator/ranges/next.hpp>
#include <hamon/iterator/reverse_iterator.hpp>
#include <hamon/ranges/concepts/forward_range.hpp>
#include <hamon/ranges/views/subrange.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/ranges/borrowed_subrange_t.hpp>
#include <hamon/ranges/end.hpp>
#include <hamon/ranges/begin.hpp>
#include <hamon/config.hpp>
#include <utility>

namespace hamon
{

namespace ranges
{

struct find_end_fn
{
private:
	template <
		HAMON_CONSTRAINED_PARAM(hamon::bidirectional_iterator, Iter1),
		typename Sent1,
		HAMON_CONSTRAINED_PARAM(hamon::bidirectional_iterator, Iter2),
		typename Sent2,
		typename Pred,
		typename Proj1,
		typename Proj2
	>
	static HAMON_CXX14_CONSTEXPR ranges::subrange<Iter1>
	impl(
		Iter1 first1, Sent1 last1,
		Iter2 first2, Sent2 last2,
		Pred pred, Proj1 proj1, Proj2 proj2,
		hamon::detail::overload_priority<1>)
	{
		auto i1 = ranges::next(first1, last1);
		auto i2 = ranges::next(first2, last2);
		auto rresult = ranges::search(
			hamon::reverse_iterator<Iter1>{i1},
			hamon::reverse_iterator<Iter1>{first1},
			hamon::reverse_iterator<Iter2>{i2},
			hamon::reverse_iterator<Iter2>{first2},
			std::move(pred),
			std::move(proj1),
			std::move(proj2));
		auto result_first = ranges::end(rresult).base();
		auto result_last  = ranges::begin(rresult).base();
		if (result_last == first1)
		{
			return { i1, i1 };
		}
		else
		{
			return { result_first, result_last };
		}
	}

	template <
		typename Iter1, typename Sent1,
		typename Iter2, typename Sent2,
		typename Pred,
		typename Proj1,
		typename Proj2
	>
	static HAMON_CXX14_CONSTEXPR ranges::subrange<Iter1>
	impl(
		Iter1 first1, Sent1 last1,
		Iter2 first2, Sent2 last2,
		Pred pred, Proj1 proj1, Proj2 proj2,
		hamon::detail::overload_priority<0>)
	{
		auto i = ranges::next(first1, last1);
		if (first2 == last2)
		{
			return { i, i };
		}

		auto result_begin = i;
		auto result_end   = i;

		for (;;)
		{
			auto new_range = ranges::search(
				first1, last1,
				first2, last2,
				pred, proj1, proj2);
			auto new_result_begin = ranges::begin(new_range);
			auto new_result_end   = ranges::end(new_range);
			if (new_result_begin == last1)
			{
				return { result_begin, result_end };
			}
			else
			{
				result_begin = new_result_begin;
				result_end   = new_result_end;
				first1 = result_begin;
				++first1;
			}
		}
	}

public:
	template <
		HAMON_CONSTRAINED_PARAM(hamon::forward_iterator, Iter1),
		HAMON_CONSTRAINED_PARAM(hamon::sentinel_for, Iter1, Sent1),
		HAMON_CONSTRAINED_PARAM(hamon::forward_iterator, Iter2),
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
		ranges::subrange<Iter1>,
		hamon::indirectly_comparable<
			Iter1, Iter2, Pred, Proj1, Proj2>)
	{
		return impl(
			std::move(first1), std::move(last1),
			std::move(first2), std::move(last2),
			std::move(pred),
			std::move(proj1),
			std::move(proj2),
			hamon::detail::overload_priority<1>{});
	}

	template <
		HAMON_CONSTRAINED_PARAM(ranges::forward_range, Range1),
		HAMON_CONSTRAINED_PARAM(ranges::forward_range, Range2),
		typename Pred = ranges::equal_to,
		typename Proj1 = hamon::identity,
		typename Proj2 = hamon::identity
	>
	HAMON_CXX14_CONSTEXPR auto operator()(
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

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR find_end_fn find_end{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_RANGES_FIND_END_HPP
