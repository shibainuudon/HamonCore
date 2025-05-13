/**
 *	@file	has_append_range.hpp
 *
 *	@brief	has_append_range の定義
 */

#ifndef HAMON_CONTAINER_DETAIL_HAS_APPEND_RANGE_HPP
#define HAMON_CONTAINER_DETAIL_HAS_APPEND_RANGE_HPP

#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>

namespace hamon
{

namespace detail
{

template <typename Container, typename R, typename = void>
struct has_append_range
	: public hamon::false_type {};

template <typename Container, typename R>
struct has_append_range<Container, R,
	hamon::void_t<decltype(hamon::declval<Container&>().append_range(hamon::declval<R>()))>>
	: public hamon::true_type {};

}	// namespace detail

}	// namespace hamon

#endif // HAMON_CONTAINER_DETAIL_HAS_APPEND_RANGE_HPP
