/**
 *	@file	make_const_iterator.hpp
 *
 *	@brief	make_const_iterator の定義
 */

#ifndef HAMON_ITERATOR_MAKE_CONST_ITERATOR_HPP
#define HAMON_ITERATOR_MAKE_CONST_ITERATOR_HPP

#include <hamon/iterator/basic_const_iterator.hpp>

#if defined(HAMON_USE_STD_BASIC_CONST_ITERATOR)

namespace hamon
{

using std::make_const_iterator;

}	// namespace hamon

#else

#include <hamon/iterator/concepts/input_iterator.hpp>
#include <hamon/iterator/const_iterator.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>

namespace hamon
{

template <HAMON_CONSTRAINED_PARAM(hamon::input_iterator, I)>
constexpr hamon::const_iterator<I>
make_const_iterator(I it)
{
	return it;
}

}	// namespace hamon

#endif

#endif // HAMON_ITERATOR_MAKE_CONST_ITERATOR_HPP
