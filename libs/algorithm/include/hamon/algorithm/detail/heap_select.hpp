/**
 *	@file	heap_select.hpp
 *
 *	@brief	heap_select の実装
 */

#ifndef HAMON_ALGORITHM_DETAIL_HEAP_SELECT_HPP
#define HAMON_ALGORITHM_DETAIL_HEAP_SELECT_HPP

#include <hamon/algorithm/make_heap.hpp>
#include <hamon/algorithm/pop_heap.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

template <typename RandomAccessIterator, typename Compare>
inline HAMON_CXX14_CONSTEXPR void
heap_select(
	RandomAccessIterator first,
	RandomAccessIterator middle,
	RandomAccessIterator last,
	Compare comp)
{
	hamon::make_heap(first, middle, comp);
	for (auto i = middle; i < last; ++i)
	{
		if (comp(*i, *first))
		{
			hamon::detail::pop_heap_impl(first, middle, i, comp);
		}
	}
}

}	// namespace detail

}	// namespace hamon

#endif // HAMON_ALGORITHM_DETAIL_HEAP_SELECT_HPP
