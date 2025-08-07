/**
 *	@file	is_standard_floating_point.hpp
 *
 *	@brief	is_standard_floating_point の定義
 */

#ifndef HAMON_FORMAT_DETAIL_IS_STANDARD_FLOATING_POINT_HPP
#define HAMON_FORMAT_DETAIL_IS_STANDARD_FLOATING_POINT_HPP

#include <hamon/type_traits/disjunction.hpp>
#include <hamon/type_traits/is_same.hpp>

namespace hamon
{

namespace detail
{

// TODO: 別の場所で定義してもいいかも

// 6.9.2 Fundamental types[basic.fundamental]

// [basic.fundamental]/12
template <typename T>
using is_standard_floating_point = hamon::disjunction<
	hamon::is_same<T, float>,
	hamon::is_same<T, double>,
	hamon::is_same<T, long double>>;

}	// namespace detail

}	// namespace hamon

#endif // HAMON_FORMAT_DETAIL_IS_STANDARD_FLOATING_POINT_HPP
