﻿/**
 *	@file	partial_sort_copy.hpp
 *
 *	@brief	ranges::partial_sort_copy の定義
 */

#ifndef HAMON_ALGORITHM_RANGES_PARTIAL_SORT_COPY_HPP
#define HAMON_ALGORITHM_RANGES_PARTIAL_SORT_COPY_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_RANGES_ALGORITHM)

#include <algorithm>

namespace hamon
{

namespace ranges
{

using std::ranges::partial_sort_copy;

}	// namespace ranges

}	// namespace hamon

#else

#include <hamon/algorithm/ranges/in_out_result.hpp>
#include <hamon/algorithm/ranges/make_heap.hpp>
#include <hamon/algorithm/ranges/pop_heap.hpp>
#include <hamon/algorithm/ranges/push_heap.hpp>
#include <hamon/algorithm/ranges/sort_heap.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/functional/ranges/less.hpp>
#include <hamon/functional/identity.hpp>
#include <hamon/functional/invoke.hpp>
#include <hamon/iterator/concepts/input_iterator.hpp>
#include <hamon/iterator/concepts/sentinel_for.hpp>
#include <hamon/iterator/concepts/random_access_iterator.hpp>
#include <hamon/iterator/concepts/indirectly_copyable.hpp>
#include <hamon/iterator/concepts/sortable.hpp>
#include <hamon/iterator/concepts/indirect_strict_weak_order.hpp>
#include <hamon/iterator/projected.hpp>
#include <hamon/iterator/ranges/next.hpp>
#include <hamon/preprocessor/punctuation/comma.hpp>
#include <hamon/ranges/concepts/input_range.hpp>
#include <hamon/ranges/concepts/random_access_range.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/ranges/borrowed_iterator_t.hpp>
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

template <typename Iter, typename Out>
using partial_sort_copy_result = in_out_result<Iter, Out>;

namespace detail
{

template <typename Iter1, typename Iter2, typename Comp, typename Proj1, typename Proj2>
#if defined(HAMON_HAS_CXX20_CONCEPTS)
concept partial_sort_copyable =
	hamon::indirectly_copyable<Iter1, Iter2> &&
	hamon::sortable<Iter2, Comp, Proj2> &&
	hamon::indirect_strict_weak_order<Comp,
		hamon::projected<Iter1, Proj1>,
		hamon::projected<Iter2, Proj2>>;
#else
using partial_sort_copyable = hamon::conjunction<
	hamon::indirectly_copyable<Iter1, Iter2>,
	hamon::sortable<Iter2, Comp, Proj2>,
	hamon::indirect_strict_weak_order<Comp,
		hamon::projected<Iter1, Proj1>,
		hamon::projected<Iter2, Proj2>>
>;
#endif

}	// namespace detail

struct partial_sort_copy_fn
{
	template <
		HAMON_CONSTRAINED_PARAM(hamon::input_iterator, Iter1),
		HAMON_CONSTRAINED_PARAM(hamon::sentinel_for, Iter1, Sent1),
		HAMON_CONSTRAINED_PARAM(hamon::random_access_iterator, Iter2),
		HAMON_CONSTRAINED_PARAM(hamon::sentinel_for, Iter2, Sent2),
		typename Comp = ranges::less,
		typename Proj1 = hamon::identity,
		typename Proj2 = hamon::identity
	>
	HAMON_CXX14_CONSTEXPR auto
	operator()(
		Iter1 first,        Sent1 last,
		Iter2 result_first, Sent2 result_last,
		Comp  comp  = {},
		Proj1 proj1 = {},
		Proj2 proj2 = {}) const
	HAMON_RETURN_TYPE_REQUIRES_CLAUSES(
		partial_sort_copy_result<Iter1 HAMON_PP_COMMA() Iter2>,
		detail::partial_sort_copyable<Iter1, Iter2, Comp, Proj1, Proj2>)
	{
		if (result_first == result_last)
		{
			// TODO: Eliminating the variable lasti triggers an ICE.
			auto lasti = ranges::next(std::move(first), std::move(last));
			return { std::move(lasti), std::move(result_first) };
		}

		auto result_real_last = result_first;
		while (first != last && result_real_last != result_last)
		{
			*result_real_last = *first;
			++result_real_last;
			++first;
		}

		ranges::make_heap(result_first, result_real_last, comp, proj2);
		for (; first != last; ++first)
		{
			if (hamon::invoke(comp,
				hamon::invoke(proj1, *first),
				hamon::invoke(proj2, *result_first)))
			{
				ranges::pop_heap(result_first, result_real_last, comp, proj2);
				*(result_real_last-1) = *first;
				ranges::push_heap(result_first, result_real_last, comp, proj2);
			}
		}

		ranges::sort_heap(result_first, result_real_last, comp, proj2);

		return { std::move(first), std::move(result_real_last) };
	}

	template <
		HAMON_CONSTRAINED_PARAM(ranges::input_range, Range1),
		HAMON_CONSTRAINED_PARAM(ranges::random_access_range, Range2),
		typename Comp = ranges::less,
		typename Proj1 = hamon::identity,
		typename Proj2 = hamon::identity
	>
	HAMON_CXX14_CONSTEXPR auto
	operator()(
		Range1&& r, Range2&& out,
		Comp  comp  = {},
		Proj1 proj1 = {},
		Proj2 proj2 = {}) const
	HAMON_RETURN_TYPE_REQUIRES_CLAUSES(
		partial_sort_copy_result<
			ranges::borrowed_iterator_t<Range1> HAMON_PP_COMMA()
			ranges::borrowed_iterator_t<Range2>>,
		detail::partial_sort_copyable<
			ranges::iterator_t<Range1>,
			ranges::iterator_t<Range2>,
			Comp, Proj1, Proj2>)
	{
		return (*this)(
			ranges::begin(r), ranges::end(r),
			ranges::begin(out), ranges::end(out),
			std::move(comp),
			std::move(proj1),
			std::move(proj2));
	}
};

#undef HAMON_RETURN_TYPE_REQUIRES_CLAUSES

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR partial_sort_copy_fn partial_sort_copy{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_RANGES_PARTIAL_SORT_COPY_HPP