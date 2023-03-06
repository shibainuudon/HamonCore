/**
 *	@file	rotate.hpp
 *
 *	@brief	rotate の定義
 */

#ifndef HAMON_ALGORITHM_ROTATE_HPP
#define HAMON_ALGORITHM_ROTATE_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_ALGORITHM)

#include <algorithm>

namespace hamon
{

using std::rotate;

}	// namespace hamon

#else

#include <hamon/algorithm/move.hpp>
#include <hamon/algorithm/move_backward.hpp>
#include <hamon/algorithm/swap_ranges.hpp>
#include <hamon/iterator/iterator_category.hpp>
#include <hamon/iterator/iter_value_t.hpp>
#include <hamon/iterator/next.hpp>
#include <hamon/iterator/prev.hpp>
#include <hamon/numeric/gcd.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_trivially_move_assignable.hpp>
#include <hamon/config.hpp>
#include <iterator>
#include <utility>

namespace hamon
{

namespace detail
{

template <typename ForwardIterator>
inline HAMON_CXX14_CONSTEXPR ForwardIterator
rotate_left(
	ForwardIterator first,
	ForwardIterator last)
{
	auto tmp = std::move(*first);
	auto lm1 = hamon::move(hamon::next(first), last, first);
	*lm1 = std::move(tmp);
	return lm1;
}

template <typename BidirectionalIterator>
inline HAMON_CXX14_CONSTEXPR BidirectionalIterator
rotate_right(
	BidirectionalIterator first,
	BidirectionalIterator last)
{
	auto lm1 = hamon::prev(last);
	auto tmp = std::move(*lm1);
	auto fp1 = hamon::move_backward(first, lm1, last);
	*first = std::move(tmp);
	return fp1;
}

template <typename ForwardIterator>
inline HAMON_CXX14_CONSTEXPR ForwardIterator
rotate_forward(
	ForwardIterator first,
	ForwardIterator middle,
	ForwardIterator last)
{
	using std::swap;

	auto i = middle;

	for (;;)
	{
		swap(*first, *i);
		++first;

		if (++i == last)
		{
			break;
		}

		if (first == middle)
		{
			middle = i;
		}
	}

	auto const r = first;
	
	if (first != middle)
	{
		i = middle;

		for (;;)
		{
			swap(*first, *i);
			++first;

			if (++i == last)
			{
				if (first == middle)
				{
					break;
				}

				i = middle;
			}
			else if (first == middle)
			{
				middle = i;
			}
		}
	}

	return r;
}

template <typename RandomAccessIterator>
inline HAMON_CXX14_CONSTEXPR RandomAccessIterator
rotate_gcd(
	RandomAccessIterator first,
	RandomAccessIterator middle,
	RandomAccessIterator last)
{
	auto const m1 = middle - first;
	auto const m2 = last - middle;

	if (m1 == m2)
	{
		hamon::swap_ranges(first, middle, middle);
		return middle;
	}

	auto const g = hamon::gcd(m1, m2);

	for (auto p = first + g; p != first;)
	{
		auto t = std::move(*--p);
		auto p1 = p;
		auto p2 = p1 + m1;

		do
		{
			*p1 = std::move(*p2);
			p1 = p2;
			auto const d = last - p2;

			if (m1 < d)
			{
				p2 += m1;
			}
			else
			{
				p2 = first + (m1 - d);
			}
		}
		while (p2 != p);
		
		*p1 = std::move(t);
	}

	return first + m2;
}

template <typename ForwardIterator>
inline HAMON_CXX14_CONSTEXPR ForwardIterator
rotate_impl_2(
	ForwardIterator first,
	ForwardIterator middle,
	ForwardIterator last,
	std::forward_iterator_tag*)
{
	if (hamon::next(first) == middle)
	{
		return rotate_left(first, last);
	}

	return rotate_forward(first, middle, last);
}

template <typename BidirectionalIterator>
inline HAMON_CXX14_CONSTEXPR BidirectionalIterator
rotate_impl_2(
	BidirectionalIterator first,
	BidirectionalIterator middle,
	BidirectionalIterator last,
	std::bidirectional_iterator_tag*)
{
	if (hamon::next(first) == middle)
	{
		return rotate_left(first, last);
	}

	if (hamon::next(middle) == last)
	{
		return rotate_right(first, last);
	}

	return rotate_forward(first, middle, last);
}

template <typename RandomAccessIterator>
inline HAMON_CXX14_CONSTEXPR RandomAccessIterator
rotate_impl_2(
	RandomAccessIterator first,
	RandomAccessIterator middle,
	RandomAccessIterator last,
	std::random_access_iterator_tag*)
{
	if (hamon::next(first) == middle)
	{
		return rotate_left(first, last);
	}

	if (hamon::next(middle) == last)
	{
		return rotate_right(first, last);
	}

	return rotate_gcd(first, middle, last);
}

template <typename ForwardIterator,
	typename ValueType = hamon::iter_value_t<ForwardIterator>,
	typename = hamon::enable_if_t<
		!hamon::is_trivially_move_assignable<ValueType>::value
	>
>
inline HAMON_CXX14_CONSTEXPR ForwardIterator
rotate_impl(
	ForwardIterator first,
	ForwardIterator middle,
	ForwardIterator last,
	hamon::detail::overload_priority<1>)
{
	return rotate_forward(first, middle, last);
}

template <typename ForwardIterator>
inline HAMON_CXX14_CONSTEXPR ForwardIterator
rotate_impl(
	ForwardIterator first,
	ForwardIterator middle,
	ForwardIterator last,
	hamon::detail::overload_priority<0>)
{
	using Category = hamon::iterator_category<ForwardIterator>*;
	return rotate_impl_2(first, middle, last, Category{});
}

}	// namespace detail

/**
 *	@brief		要素の並びを回転させる。
 *
 *	@tparam		ForwardIterator
 *
 *	@param		first
 *	@param		middle
 *	@param		last
 *
 *	@require	[first,middle) と [middle,last) は有効な範囲である必要がある。
 *				ForwardIterator は ValueSwappable の要件を満たしている必要がある。
 *				*first の型は MoveConstructible と MoveAssignable の要件を満たしている必要がある。
 *
 *	@effect		0 以上 last - first 未満の整数 i について、
 *				first + i の要素を first + (i + (last - middle)) % (last - first) の位置へ移動させる。
 *
 *	@return		first + (last - middle)
 *
 *	@complexity	最大で last - first 回 swap する。
 *
 *	@note		これは左への回転である
 */
template <typename ForwardIterator>
inline HAMON_CXX14_CONSTEXPR ForwardIterator
rotate(ForwardIterator first, ForwardIterator middle, ForwardIterator last)
{
	if (first == middle)
	{
		return last;
	}

	if (middle == last)
	{
		return first;
	}

	return hamon::detail::rotate_impl(first, middle, last,
		hamon::detail::overload_priority<1>{});
}

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_ROTATE_HPP
