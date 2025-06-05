/**
 *	@file	is_reservable.hpp
 *
 *	@brief	is_reservable の定義
 */

#ifndef HAMON_CONTAINER_DETAIL_IS_RESERVABLE_HPP
#define HAMON_CONTAINER_DETAIL_IS_RESERVABLE_HPP

#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/utility/declval.hpp>

namespace hamon
{

namespace detail
{

template <typename Container, typename = void>
struct is_reservable
	: public hamon::false_type
{};

template <typename Container>
struct is_reservable<Container,
	hamon::void_t<decltype(hamon::declval<Container&>().reserve(hamon::declval<typename Container::size_type>()))>>
	: public hamon::true_type
{};

}	// namespace detail

}	// namespace hamon

#endif // HAMON_CONTAINER_DETAIL_IS_RESERVABLE_HPP
