/**
 *	@file	iter_mapped_type.hpp
 *
 *	@brief	iter_mapped_type の定義
 */

#ifndef HAMON_CONTAINER_DETAIL_ITER_MAPPED_TYPE_HPP
#define HAMON_CONTAINER_DETAIL_ITER_MAPPED_TYPE_HPP

#include <hamon/container/detail/iter_value_type.hpp>
#include <hamon/tuple/tuple_element.hpp>

namespace hamon
{

namespace detail
{

// 23.4.1 General[associative.general]

template <typename InputIterator>
using iter_mapped_type =
	hamon::tuple_element_t<1, hamon::detail::iter_value_type<InputIterator>>;

}	// namespace detail

}	// namespace hamon

#endif // HAMON_CONTAINER_DETAIL_ITER_MAPPED_TYPE_HPP
