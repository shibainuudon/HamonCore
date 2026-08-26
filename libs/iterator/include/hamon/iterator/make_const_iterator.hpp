/**
 *	@file	make_const_iterator.hpp
 *
 *	@brief	make_const_iterator の定義
 */

#ifndef HAMON_ITERATOR_MAKE_CONST_ITERATOR_HPP
#define HAMON_ITERATOR_MAKE_CONST_ITERATOR_HPP

#include <hamon/iterator/concepts/input_iterator.hpp>
#include <hamon/iterator/const_iterator.hpp>
#include <hamon/concepts/detail/constraint.hpp>
#include <hamon/type_traits/is_nothrow_convertible.hpp>
#include <hamon/config.hpp>

namespace hamon
{

template <HAMON_CONSTRAINT(hamon::input_iterator, I)>
HAMON_CXX11_CONSTEXPR hamon::const_iterator<I>
make_const_iterator(I it)
HAMON_NOEXCEPT_IF(hamon::is_nothrow_convertible<I, hamon::const_iterator<I>>::value)	// noexcept as an extension
{
	return it;
}

}	// namespace hamon

#endif // HAMON_ITERATOR_MAKE_CONST_ITERATOR_HPP
