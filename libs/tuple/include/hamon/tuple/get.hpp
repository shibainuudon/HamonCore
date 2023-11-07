/**
 *	@file	get.hpp
 *
 *	@brief	get の定義
 */

#ifndef HAMON_TUPLE_GET_HPP
#define HAMON_TUPLE_GET_HPP

#include <hamon/tuple/config.hpp>

#if defined(HAMON_USE_STD_TUPLE)

namespace hamon
{

using std::get;

}	// namespace hamon

#else

#include <hamon/tuple/tuple_fwd.hpp>
#include <hamon/tuple/tuple_element.hpp>
#include <hamon/tuple/detail/access.hpp>
#include <hamon/tuple/detail/exactly_once.hpp>
#include <hamon/tuple/detail/find_index.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// Element access	[tuple.elem]
template <hamon::size_t I, typename... Types>
HAMON_NODISCARD	// extension
inline HAMON_CXX11_CONSTEXPR tuple_element_t<I, tuple<Types...>>&
get(tuple<Types...>& t) HAMON_NOEXCEPT
{
	static_assert(I < sizeof...(Types), "[tuple.elem]/1");
	return tuple_detail::access::get<I>(t);
}

template <hamon::size_t I, typename... Types>
HAMON_NODISCARD	// extension
inline HAMON_CXX11_CONSTEXPR tuple_element_t<I, tuple<Types...>>&&
get(tuple<Types...>&& t) HAMON_NOEXCEPT
{
	static_assert(I < sizeof...(Types), "[tuple.elem]/1");
	return tuple_detail::access::get<I>(hamon::move(t));
}

template <hamon::size_t I, typename... Types>
HAMON_NODISCARD	// extension
inline HAMON_CXX11_CONSTEXPR tuple_element_t<I, tuple<Types...>> const&
get(tuple<Types...> const& t) HAMON_NOEXCEPT
{
	static_assert(I < sizeof...(Types), "[tuple.elem]/1");
	return tuple_detail::access::get<I>(t);
}

template <hamon::size_t I, typename... Types>
HAMON_NODISCARD	// extension
inline HAMON_CXX11_CONSTEXPR tuple_element_t<I, tuple<Types...>> const&&
get(tuple<Types...> const&& t) HAMON_NOEXCEPT
{
	static_assert(I < sizeof...(Types), "[tuple.elem]/1");
	return tuple_detail::access::get<I>(hamon::move(t));
}

template <typename T, typename... Types>
HAMON_NODISCARD	// extension
inline HAMON_CXX11_CONSTEXPR T&
get(tuple<Types...>& t) HAMON_NOEXCEPT
{
	static_assert(tuple_detail::exactly_once<T, Types...>::value, "[tuple.elem]/5");
	return hamon::get<tuple_detail::find_index<T, Types...>::value>(t);
}

template <typename T, typename... Types>
HAMON_NODISCARD	// extension
inline HAMON_CXX11_CONSTEXPR T&&
get(tuple<Types...>&& t) HAMON_NOEXCEPT
{
	static_assert(tuple_detail::exactly_once<T, Types...>::value, "[tuple.elem]/5");
	return hamon::get<tuple_detail::find_index<T, Types...>::value>(hamon::move(t));
}

template <typename T, typename... Types>
HAMON_NODISCARD	// extension
inline HAMON_CXX11_CONSTEXPR T const&
get(tuple<Types...> const& t) HAMON_NOEXCEPT
{
	static_assert(tuple_detail::exactly_once<T, Types...>::value, "[tuple.elem]/5");
	return hamon::get<tuple_detail::find_index<T, Types...>::value>(t);
}

template <typename T, typename... Types>
HAMON_NODISCARD	// extension
inline HAMON_CXX11_CONSTEXPR T const&&
get(tuple<Types...> const&& t) HAMON_NOEXCEPT
{
	static_assert(tuple_detail::exactly_once<T, Types...>::value, "[tuple.elem]/5");
	return hamon::get<tuple_detail::find_index<T, Types...>::value>(hamon::move(t));
}

}	// namespace hamon

#endif

#endif // HAMON_TUPLE_GET_HPP
