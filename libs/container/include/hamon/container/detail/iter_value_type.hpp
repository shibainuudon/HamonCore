/**
 *	@file	iter_value_type.hpp
 *
 *	@brief	iter_value_type の定義
 */

#ifndef HAMON_CONTAINER_DETAIL_ITER_VALUE_TYPE_HPP
#define HAMON_CONTAINER_DETAIL_ITER_VALUE_TYPE_HPP

#include <hamon/iterator/iterator_traits.hpp>

namespace hamon
{

namespace detail
{

// 23.4.1 General[associative.general]

template <typename InputIterator>
using iter_value_type =
	typename hamon::iterator_traits<InputIterator>::value_type;

}	// namespace detail

}	// namespace hamon

#endif // HAMON_CONTAINER_DETAIL_ITER_VALUE_TYPE_HPP
