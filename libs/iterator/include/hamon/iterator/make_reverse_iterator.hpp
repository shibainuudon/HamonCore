/**
 *	@file	make_reverse_iterator.hpp
 *
 *	@brief	make_reverse_iterator の定義
 */

#ifndef HAMON_ITERATOR_MAKE_REVERSE_ITERATOR_HPP
#define HAMON_ITERATOR_MAKE_REVERSE_ITERATOR_HPP

#include <hamon/iterator/reverse_iterator.hpp>
#include <iterator>

#if defined(HAMON_USE_STD_REVERSE_ITERATOR) && \
    defined(__cpp_lib_make_reverse_iterator) && (__cpp_lib_make_reverse_iterator >= 201402)

namespace hamon
{

using std::make_reverse_iterator;

}	// namespace hamon

#else

#include <hamon/config.hpp>

namespace hamon
{

// make_reverse_iterator
template <typename Iterator>
inline HAMON_CONSTEXPR hamon::reverse_iterator<Iterator>
make_reverse_iterator(Iterator it)
{
	return hamon::reverse_iterator<Iterator>(it);
}

}	// namespace hamon

#endif

#endif // HAMON_ITERATOR_MAKE_REVERSE_ITERATOR_HPP
