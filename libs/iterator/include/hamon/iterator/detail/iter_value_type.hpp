/**
 *	@file	iter_value_type.hpp
 *
 *	@brief	iter_value_type の定義
 */

#ifndef HAMON_ITERATOR_DETAIL_ITER_VALUE_TYPE_HPP
#define HAMON_ITERATOR_DETAIL_ITER_VALUE_TYPE_HPP

#include <hamon/iterator/iterator_traits.hpp>

namespace hamon
{

namespace detail
{

// [sequences.general]/2
template <typename InputIterator>
using iter_value_type =
	typename hamon::iterator_traits<InputIterator>::value_type;

}	// namespace detail

}	// namespace hamon

#endif // HAMON_ITERATOR_DETAIL_ITER_VALUE_TYPE_HPP
