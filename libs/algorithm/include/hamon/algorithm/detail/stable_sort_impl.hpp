/**
 *	@file	stable_sort_impl.hpp
 *
 *	@brief	stable_sort_impl の実装
 */

#ifndef HAMON_ALGORITHM_DETAIL_STABLE_SORT_IMPL_HPP
#define HAMON_ALGORITHM_DETAIL_STABLE_SORT_IMPL_HPP

#include <hamon/algorithm/inplace_merge.hpp>
#include <hamon/algorithm/detail/insertion_sort.hpp>
#include <hamon/iterator/iterator_traits.hpp>
#include <hamon/iterator/ranges/iter_swap.hpp>
#include <hamon/type_traits/is_trivially_copy_assignable.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

template <typename RandomAccessIterator, typename Compare>
HAMON_CXX14_CONSTEXPR void
stable_sort_impl(RandomAccessIterator first, RandomAccessIterator last, Compare comp)
{
	auto const len = last - first;
	switch (len)
	{
	case 0:
	case 1:
		return;
	case 2:
		if (comp(*--last, *first))
		{
			hamon::ranges::iter_swap(first, last);
		}
		return;
	}

	using value_type = typename hamon::iterator_traits<RandomAccessIterator>::value_type;
	if (hamon::is_trivially_copy_assignable<value_type>::value)
	{
		if (len <= 128)
		{
			hamon::detail::insertion_sort(first, last, comp);
			return;
		}
	}

	RandomAccessIterator m = first + len / 2;
	hamon::detail::stable_sort_impl(first, m, comp);
	hamon::detail::stable_sort_impl(m, last, comp);
	hamon::inplace_merge(first, m, last, comp);
}

}	// namespace detail

}	// namespace hamon

#endif // HAMON_ALGORITHM_DETAIL_STABLE_SORT_IMPL_HPP
