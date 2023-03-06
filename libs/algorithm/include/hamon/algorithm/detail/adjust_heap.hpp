/**
 *	@file	adjust_heap.hpp
 *
 *	@brief	adjust_heap の実装
 */

#ifndef HAMON_ALGORITHM_DETAIL_ADJUST_HEAP_HPP
#define HAMON_ALGORITHM_DETAIL_ADJUST_HEAP_HPP

#include <hamon/algorithm/push_heap.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

template <
	typename RandomAccessIterator,
	typename Distance,
	typename T,
	typename Compare
>
inline HAMON_CXX14_CONSTEXPR void
adjust_heap(
	RandomAccessIterator first,
	Distance hole_index,
	Distance len,
	T value,
	Compare comp)
{
	const Distance top_index = hole_index;
	Distance second_child = hole_index;
	while (second_child < (len - 1) / 2)
	{
		second_child = 2 * (second_child + 1);
		if (comp(*(first + second_child), *(first + (second_child - 1))))
		{
			second_child--;
		}

		*(first + hole_index) = hamon::move(*(first + second_child));
		hole_index = second_child;
	}

	if ((len & 1) == 0 && second_child == (len - 2) / 2)
	{
		second_child = 2 * (second_child + 1);
		*(first + hole_index) = hamon::move(*(first + (second_child - 1)));
		hole_index = second_child - 1;
	}

	hamon::detail::push_heap_impl(first, hole_index, top_index, hamon::move(value), comp);
}

}	// namespace detail

}	// namespace hamon

#endif // HAMON_ALGORITHM_DETAIL_ADJUST_HEAP_HPP
