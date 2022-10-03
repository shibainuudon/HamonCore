/**
 *	@file	prev.hpp
 *
 *	@brief	prev 関数の定義
 */

#ifndef HAMON_ITERATOR_PREV_HPP
#define HAMON_ITERATOR_PREV_HPP

#include <hamon/iterator/config.hpp>

#if defined(HAMON_USE_STD_ITERATOR)

namespace hamon
{

using std::prev;

}	// namespace hamon

#else

#include <hamon/iterator/advance.hpp>
#include <hamon/iterator/iter_difference_t.hpp>
#include <hamon/iterator/iterator_category.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

template <typename BidirectionalIterator, typename Distance>
inline HAMON_CXX14_CONSTEXPR BidirectionalIterator
prev_impl(BidirectionalIterator it, Distance n, std::bidirectional_iterator_tag*)
{
	hamon::advance(it, -n);
	return it;
}

template <typename RandomAccessIterator, typename Distance>
inline HAMON_CONSTEXPR RandomAccessIterator
prev_impl(RandomAccessIterator const& it, Distance n, std::random_access_iterator_tag*)
{
	return it - n;
}

}	// namespace detail

/**
 *	@brief	
 */
template <
	typename BidirectionalIterator,
	typename Distance = hamon::iter_difference_t<BidirectionalIterator>
>
inline HAMON_CONSTEXPR BidirectionalIterator
prev(BidirectionalIterator const& it, Distance n = 1)
{
	using Category = hamon::iterator_category<BidirectionalIterator>*;
	return detail::prev_impl(it, n, Category());
}

}	// namespace hamon

#endif

#endif // HAMON_ITERATOR_PREV_HPP
