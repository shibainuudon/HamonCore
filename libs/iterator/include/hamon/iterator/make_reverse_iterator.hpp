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

#include <hamon/type_traits/is_nothrow_move_constructible.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// [reverse.iter.nonmember]/7
template <typename Iterator>
HAMON_CXX11_CONSTEXPR hamon::reverse_iterator<Iterator>
make_reverse_iterator(Iterator i)
HAMON_NOEXCEPT_IF(hamon::is_nothrow_move_constructible<Iterator>::value)
{
	return hamon::reverse_iterator<Iterator>(i);
}

}	// namespace hamon

#endif

#endif // HAMON_ITERATOR_MAKE_REVERSE_ITERATOR_HPP
