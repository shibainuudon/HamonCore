﻿/**
 *	@file	shift_right.hpp
 *
 *	@brief	shift_right の定義
 */

#ifndef HAMON_ALGORITHM_SHIFT_RIGHT_HPP
#define HAMON_ALGORITHM_SHIFT_RIGHT_HPP

#include <hamon/config.hpp>
#include <algorithm>

#if defined(__cpp_lib_shift) && (__cpp_lib_shift >= 201806) &&	\
	!(defined(HAMON_APPLE_CLANG) && (HAMON_APPLE_CLANG <= 130000))

namespace hamon
{

using std::shift_right;

}	// namespace hamon

#else

#include <hamon/algorithm/move.hpp>
#include <hamon/algorithm/move_backward.hpp>
#include <hamon/algorithm/iter_swap.hpp>
#include <hamon/iterator/iterator_traits.hpp>
#include <hamon/iterator/iterator_category.hpp>
#include <hamon/iterator/ranges/next.hpp>
#include <iterator>
#include <utility>

namespace hamon
{

namespace detail
{

template <typename BidirectionalIterator, typename Difference>
inline HAMON_CXX14_CONSTEXPR BidirectionalIterator
shift_right_impl(
	BidirectionalIterator first,
	BidirectionalIterator last,
	Difference n,
	std::bidirectional_iterator_tag*)
{
	auto mid = ranges::next(last, -n, first);
	if (mid == first)
	{
		return last;
	}

	return hamon::move_backward(std::move(first), std::move(mid), std::move(last));
}

template <typename ForwardIterator, typename Difference>
inline HAMON_CXX14_CONSTEXPR ForwardIterator
shift_right_impl(
	ForwardIterator first,
	ForwardIterator last,
	Difference n,
	std::forward_iterator_tag*)
{
	auto result = ranges::next(first, n, last);
	if (result == last)
	{
		return last;
	}

	auto dest_head = first;
	auto dest_tail = result;
	while (dest_head != result)
	{
		if (dest_tail == last)
		{
			hamon::move(std::move(first), std::move(dest_head), std::move(result));
			return result;
		}
		++dest_head;
		++dest_tail;
	}

	for (;;)
	{
		auto cursor = first;
		while (cursor != result)
		{
			if (dest_tail == last)
			{
				dest_head = hamon::move(cursor, result, std::move(dest_head));
				hamon::move(std::move(first), std::move(cursor), std::move(dest_head));
				return result;
			}
			hamon::iter_swap(cursor, dest_head);
			++dest_head;
			++dest_tail;
			++cursor;
		}
	}
}

}	// namespace detail

template <typename ForwardIterator>
inline HAMON_CXX14_CONSTEXPR ForwardIterator
shift_right(ForwardIterator first, ForwardIterator last,
	typename hamon::iterator_traits<ForwardIterator>::difference_type n)
{
	using Category = hamon::iterator_category<ForwardIterator>*;

	if (n <= 0)
	{
		return first;
	}

	return detail::shift_right_impl(
		std::move(first),
		std::move(last),
		n,
		Category{});
}

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_SHIFT_RIGHT_HPP