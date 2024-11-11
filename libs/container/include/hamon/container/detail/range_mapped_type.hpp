/**
 *	@file	range_mapped_type.hpp
 *
 *	@brief	range_mapped_type の定義
 */

#ifndef HAMON_CONTAINER_DETAIL_RANGE_MAPPED_TYPE_HPP
#define HAMON_CONTAINER_DETAIL_RANGE_MAPPED_TYPE_HPP

#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/ranges/concepts/input_range.hpp>
#include <hamon/ranges/range_value_t.hpp>

namespace hamon
{

namespace detail
{

// 23.4.1 General[associative.general]

template <HAMON_CONSTRAINED_PARAM(hamon::ranges::input_range, Range)>
using range_mapped_type =
	typename hamon::ranges::range_value_t<Range>::second_type;

}	// namespace detail

}	// namespace hamon

#endif // HAMON_CONTAINER_DETAIL_RANGE_MAPPED_TYPE_HPP
