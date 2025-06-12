/**
 *	@file	sort_impl.hpp
 *
 *	@brief	sort_impl の実装
 */

#ifndef HAMON_ALGORITHM_DETAIL_SORT_IMPL_HPP
#define HAMON_ALGORITHM_DETAIL_SORT_IMPL_HPP

#include <hamon/algorithm/partial_sort.hpp>

namespace hamon
{

namespace detail
{

template <typename RandomAccessIterator, typename Compare>
HAMON_CXX14_CONSTEXPR void
sort_impl(RandomAccessIterator first, RandomAccessIterator last, Compare comp)
{
	// TODO: intro_sort
	hamon::partial_sort(first, last, last, comp);
}

}	// namespace detail

}	// namespace hamon

#endif // HAMON_ALGORITHM_DETAIL_SORT_IMPL_HPP
