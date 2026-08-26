/**
 *	@file	make_reverse_iterator.hpp
 *
 *	@brief	make_reverse_iterator の定義
 */

#ifndef HAMON_ITERATOR_MAKE_REVERSE_ITERATOR_HPP
#define HAMON_ITERATOR_MAKE_REVERSE_ITERATOR_HPP

#include <hamon/iterator/reverse_iterator.hpp>
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

#endif // HAMON_ITERATOR_MAKE_REVERSE_ITERATOR_HPP
