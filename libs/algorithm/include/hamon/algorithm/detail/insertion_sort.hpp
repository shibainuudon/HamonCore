﻿/**
 *	@file	insertion_sort.hpp
 *
 *	@brief	insertion_sort の実装
 */

#ifndef HAMON_ALGORITHM_DETAIL_INSERTION_SORT_HPP
#define HAMON_ALGORITHM_DETAIL_INSERTION_SORT_HPP

#include <hamon/algorithm/move_backward.hpp>
#include <hamon/algorithm/detail/unguarded_linear_insert.hpp>
#include <hamon/iterator/iter_value_t.hpp>
#include <hamon/config.hpp>
#include <utility>

namespace hamon
{

namespace detail
{

template <typename RandomAccessIterator, typename Compare>
inline HAMON_CXX14_CONSTEXPR void
insertion_sort(RandomAccessIterator first, RandomAccessIterator last, Compare comp)
{
	if (first == last)
	{
		return;
	}

	for (auto i = first + 1; i != last; ++i)
	{
		if (comp(*i, *first))
		{
			hamon::iter_value_t<RandomAccessIterator> val = std::move(*i);
			hamon::move_backward(first, i, i + 1);
			*first = std::move(val);
		}
		else
		{
			hamon::detail::unguarded_linear_insert(i, comp);
		}
	}
}

}	// namespace detail

}	// namespace hamon

#endif // HAMON_ALGORITHM_DETAIL_INSERTION_SORT_HPP
