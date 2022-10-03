/**
 *	@file	next.hpp
 *
 *	@brief	next 関数の定義
 */

#ifndef HAMON_ITERATOR_NEXT_HPP
#define HAMON_ITERATOR_NEXT_HPP

#include <hamon/iterator/config.hpp>

#if defined(HAMON_USE_STD_ITERATOR)

namespace hamon
{

using std::next;

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

template <typename InputIterator, typename Distance>
inline HAMON_CXX14_CONSTEXPR InputIterator
next_impl(InputIterator it, Distance n, std::input_iterator_tag*)
{
	hamon::advance(it, n);
	return it;
}

template <typename RandomAccessIterator, typename Distance>
inline HAMON_CONSTEXPR RandomAccessIterator
next_impl(RandomAccessIterator const& it, Distance n, std::random_access_iterator_tag*)
{
	return it + n;
}

}	// namespace detail

/**
 *	@brief	
 */
template <
	typename InputIterator,
	typename Distance = hamon::iter_difference_t<InputIterator>
>
inline HAMON_CONSTEXPR InputIterator
next(InputIterator const& it, Distance n = 1)
{
	using Category = hamon::iterator_category<InputIterator>*;
	return detail::next_impl(it, n, Category());
}

}	// namespace hamon

#endif

#endif // HAMON_ITERATOR_NEXT_HPP
