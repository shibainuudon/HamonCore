/**
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
#include <hamon/iterator/bidirectional_iterator_tag.hpp>
#include <hamon/iterator/iterator_traits.hpp>
#include <hamon/iterator/iterator_category.hpp>
#include <hamon/iterator/forward_iterator_tag.hpp>
#include <hamon/iterator/ranges/iter_swap.hpp>
#include <hamon/iterator/ranges/next.hpp>
#include <hamon/utility/move.hpp>

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
	hamon::bidirectional_iterator_tag const*)
{
	auto mid = ranges::next(last, -n, first);
	if (mid == first)
	{
		return last;
	}

	return hamon::move_backward(hamon::move(first), hamon::move(mid), hamon::move(last));
}

template <typename ForwardIterator, typename Difference>
inline HAMON_CXX14_CONSTEXPR ForwardIterator
shift_right_impl(
	ForwardIterator first,
	ForwardIterator last,
	Difference n,
	hamon::forward_iterator_tag const*)
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
			hamon::move(hamon::move(first), hamon::move(dest_head), hamon::move(result));
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
				dest_head = hamon::move(cursor, result, hamon::move(dest_head));
				hamon::move(hamon::move(first), hamon::move(cursor), hamon::move(dest_head));
				return result;
			}
			hamon::ranges::iter_swap(cursor, dest_head);
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
		hamon::move(first),
		hamon::move(last),
		n,
		Category{});
}

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_SHIFT_RIGHT_HPP
