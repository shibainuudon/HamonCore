/**
 *	@file	iter_to_alloc_type.hpp
 *
 *	@brief	iter_to_alloc_type の定義
 */

#ifndef HAMON_CONTAINER_DETAIL_ITER_TO_ALLOC_TYPE_HPP
#define HAMON_CONTAINER_DETAIL_ITER_TO_ALLOC_TYPE_HPP

#include <hamon/container/detail/iter_value_type.hpp>
#include <hamon/pair/pair.hpp>
#include <hamon/type_traits/add_const.hpp>
#include <hamon/tuple/tuple_element.hpp>

namespace hamon
{

namespace detail
{

// 23.4.1 General[associative.general]

template <typename InputIterator>
using iter_to_alloc_type =
	hamon::pair<
		hamon::add_const_t<hamon::tuple_element_t<0, hamon::detail::iter_value_type<InputIterator>>>,
		hamon::tuple_element_t<1, hamon::detail::iter_value_type<InputIterator>>
	>;

}	// namespace detail

}	// namespace hamon

#endif // HAMON_CONTAINER_DETAIL_ITER_TO_ALLOC_TYPE_HPP
