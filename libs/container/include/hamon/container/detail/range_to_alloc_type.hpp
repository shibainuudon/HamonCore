/**
 *	@file	range_to_alloc_type.hpp
 *
 *	@brief	range_to_alloc_type の定義
 */

#ifndef HAMON_CONTAINER_DETAIL_RANGE_TO_ALLOC_TYPE_HPP
#define HAMON_CONTAINER_DETAIL_RANGE_TO_ALLOC_TYPE_HPP

#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/pair/pair.hpp>
#include <hamon/ranges/concepts/input_range.hpp>
#include <hamon/ranges/range_value_t.hpp>
#include <hamon/type_traits/add_const.hpp>

namespace hamon
{

namespace detail
{

// 23.4.1 General[associative.general]

template <HAMON_CONSTRAINED_PARAM(hamon::ranges::input_range, Range)>
using range_to_alloc_type =
	hamon::pair<
		hamon::add_const_t<typename hamon::ranges::range_value_t<Range>::first_type>,
		typename hamon::ranges::range_value_t<Range>::second_type
	>;

}	// namespace detail

}	// namespace hamon

#endif // HAMON_CONTAINER_DETAIL_RANGE_TO_ALLOC_TYPE_HPP
