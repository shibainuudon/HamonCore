/**
 *	@file	const_iterator.hpp
 *
 *	@brief	const_iterator の定義
 */

#ifndef HAMON_ITERATOR_CONST_ITERATOR_HPP
#define HAMON_ITERATOR_CONST_ITERATOR_HPP

#include <hamon/iterator/basic_const_iterator.hpp>

#if defined(HAMON_USE_STD_BASIC_CONST_ITERATOR)

namespace hamon
{

using std::const_iterator;

}	// namespace hamon

#else

#include <hamon/iterator/detail/constant_iterator.hpp>
#include <hamon/iterator/concepts/input_iterator.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/type_traits/conditional.hpp>

namespace hamon
{

// [const.iterators.alias]

template <HAMON_CONSTRAINED_PARAM(hamon::input_iterator, I)>
using const_iterator =
	hamon::conditional_t<
		detail::constant_iterator_t<I>::value,
		I,
		hamon::basic_const_iterator<I>
	>;

}	// namespace hamon

#endif

#endif // HAMON_ITERATOR_CONST_ITERATOR_HPP
