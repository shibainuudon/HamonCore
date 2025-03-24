/**
 *	@file	map_get_key.hpp
 *
 *	@brief	map_get_key の定義
 */

#ifndef HAMON_CONTAINER_DETAIL_MAP_GET_KEY_HPP
#define HAMON_CONTAINER_DETAIL_MAP_GET_KEY_HPP

#include <hamon/detail/overload_priority.hpp>
#include <hamon/tuple/adl_get.hpp>
#include <hamon/tuple/concepts/pair_like.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/remove_cvref.hpp>
#include <hamon/config.hpp>

namespace hamon {
namespace detail {

#define HAMON_NOEXCEPT_DECLTYPE_RETURN(...) \
	HAMON_NOEXCEPT_IF_EXPR(__VA_ARGS__)     \
	-> decltype((__VA_ARGS__))              \
	{ return __VA_ARGS__; }

template <typename T, typename = hamon::enable_if_t<
	hamon::pair_like_t<hamon::remove_cvref_t<T>>::value>>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto
map_get_key_impl(T const& t, hamon::detail::overload_priority<1>)
HAMON_NOEXCEPT_DECLTYPE_RETURN(
	hamon::adl_get<0>(t))

template <typename T>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR T const&
map_get_key_impl(T const& t, hamon::detail::overload_priority<0>) noexcept
{
	return t;
}

template <typename T>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto
map_get_key(T const& t)
HAMON_NOEXCEPT_DECLTYPE_RETURN(
	map_get_key_impl(t, hamon::detail::overload_priority<1>{}))

#undef HAMON_NOEXCEPT_DECLTYPE_RETURN

}	// namespace detail
}	// namespace hamon

#endif // HAMON_CONTAINER_DETAIL_MAP_GET_KEY_HPP
