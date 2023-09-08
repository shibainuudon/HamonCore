/**
 *	@file	advance.hpp
 *
 *	@brief	advance 関数の定義
 */

#ifndef HAMON_ITERATOR_ADVANCE_HPP
#define HAMON_ITERATOR_ADVANCE_HPP

#include <hamon/iterator/config.hpp>

#if defined(HAMON_USE_STD_ITERATOR)

namespace hamon
{

using std::advance;

}	// namespace hamon

#else

#include <hamon/iterator/bidirectional_iterator_tag.hpp>
#include <hamon/iterator/input_iterator_tag.hpp>
#include <hamon/iterator/iter_difference_t.hpp>
#include <hamon/iterator/iterator_category.hpp>
#include <hamon/iterator/random_access_iterator_tag.hpp>
#include <hamon/assert.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

template <typename InputIterator, typename Distance>
inline HAMON_CXX14_CONSTEXPR void
advance_impl(InputIterator& it, Distance n, hamon::input_iterator_tag*)
{
	HAMON_ASSERT(n >= 0);
	for (; 0 < n; --n)
	{
		++it;
	}
}

template <typename BidirectionalIterator, typename Distance>
inline HAMON_CXX14_CONSTEXPR void
advance_impl(BidirectionalIterator& it, Distance n, hamon::bidirectional_iterator_tag*)
{
	if (n > 0)
	{
		for (; 0 < n; --n)
		{
			++it;
		}
	}
	else
	{
		for (; n < 0; ++n)
		{
			--it;
		}
	}
}

template <typename RandomAccessIterator, typename Distance>
inline HAMON_CXX14_CONSTEXPR void
advance_impl(RandomAccessIterator& it, Distance n, hamon::random_access_iterator_tag*)
{
	it += n;
}

}	// namespace detail

/**
 *	@brief	
 */
template <
	typename InputIterator,
	typename Distance = hamon::iter_difference_t<InputIterator>
>
inline HAMON_CXX14_CONSTEXPR void
advance(InputIterator& it, Distance n)
{
	using Category = hamon::iterator_category<InputIterator>*;
	hamon::detail::advance_impl(it, n, Category());
}

}	// namespace hamon

#endif

#endif // HAMON_ITERATOR_ADVANCE_HPP
