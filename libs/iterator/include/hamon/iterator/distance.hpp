/**
 *	@file	distance.hpp
 *
 *	@brief	distance 関数の定義
 */

#ifndef HAMON_ITERATOR_DISTANCE_HPP
#define HAMON_ITERATOR_DISTANCE_HPP

#include <hamon/iterator/config.hpp>

#if defined(HAMON_USE_STD_ITERATOR)

namespace hamon
{

using std::distance;

}	// namespace hamon

#else

#include <hamon/iterator/input_iterator_tag.hpp>
#include <hamon/iterator/iterator_category.hpp>
#include <hamon/iterator/iter_difference_t.hpp>
#include <hamon/config.hpp>
#include <iterator>

namespace hamon
{

namespace detail
{

template <typename Distance, typename InputIterator>
inline HAMON_CXX14_CONSTEXPR Distance
distance_impl(InputIterator first, InputIterator last, hamon::input_iterator_tag*)
{
	Distance n = 0;
	for (; first != last; ++first)
	{
		++n;
	}
	return n;
}

template <typename Distance, typename RandomAccessIterator>
inline HAMON_CONSTEXPR Distance
distance_impl(RandomAccessIterator first, RandomAccessIterator last, std::random_access_iterator_tag*)
{
	return last - first;
}

}	// namespace detail

template <typename InputIterator>
inline HAMON_CONSTEXPR hamon::iter_difference_t<InputIterator>
distance(InputIterator first, InputIterator last)
{
	using Distance = hamon::iter_difference_t<InputIterator>;
	using Category = hamon::iterator_category<InputIterator>*;
	return hamon::detail::distance_impl<Distance>(first, last, Category());
}

}	// namespace hamon

#endif

#endif // HAMON_ITERATOR_DISTANCE_HPP
