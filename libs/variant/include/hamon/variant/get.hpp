/**
 *	@file	get.hpp
 *
 *	@brief	get の定義
 */

#ifndef HAMON_VARIANT_GET_HPP
#define HAMON_VARIANT_GET_HPP

#include <hamon/variant/config.hpp>

#if defined(HAMON_USE_STD_VARIANT)

namespace hamon
{

using std::get;

}	// namespace hamon

#else

#include <hamon/variant/detail/access.hpp>
#include <hamon/variant/detail/exactly_once.hpp>
#include <hamon/variant/detail/find_index.hpp>
#include <hamon/variant/variant_alternative.hpp>
#include <hamon/variant/variant.hpp>
#include <hamon/variant/bad_variant_access.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/config.hpp>

namespace hamon
{

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4702)	// unreachable code

// [variant.get], value access
template <hamon::size_t I, typename... Types>
HAMON_NODISCARD
inline HAMON_CXX11_CONSTEXPR variant_alternative_t<I, variant<Types...>>&
get(variant<Types...>& v)
{
	// [variant.get]/3
	static_assert(I < sizeof...(Types), "variant index out of bounds");
	// [variant.get]/4
	return
		(v.index() != I ? (throw_bad_variant_access(), 0) : 0),
		variant_detail::access::get<I>(v);
}

template <hamon::size_t I, typename... Types>
HAMON_NODISCARD
inline HAMON_CXX11_CONSTEXPR variant_alternative_t<I, variant<Types...>>&&
get(variant<Types...>&& v)
{
	// [variant.get]/3
	static_assert(I < sizeof...(Types), "variant index out of bounds");
	// [variant.get]/4
	return
		(v.index() != I ? (throw_bad_variant_access(), 0) : 0),
		variant_detail::access::get<I>(hamon::move(v));
}

template <hamon::size_t I, typename... Types>
HAMON_NODISCARD
inline HAMON_CXX11_CONSTEXPR variant_alternative_t<I, variant<Types...>> const&
get(variant<Types...> const& v)
{
	// [variant.get]/3
	static_assert(I < sizeof...(Types), "variant index out of bounds");
	// [variant.get]/4
	return
		(v.index() != I ? (throw_bad_variant_access(), 0) : 0),
		variant_detail::access::get<I>(v);
}

template <hamon::size_t I, typename... Types>
HAMON_NODISCARD
inline HAMON_CXX11_CONSTEXPR variant_alternative_t<I, variant<Types...>> const&&
get(variant<Types...> const&& v)
{
	// [variant.get]/3
	static_assert(I < sizeof...(Types), "variant index out of bounds");
	// [variant.get]/4
	return
		(v.index() != I ? (throw_bad_variant_access(), 0) : 0),
		variant_detail::access::get<I>(hamon::move(v));
}

HAMON_WARNING_POP()

template <typename T, typename... Types>
HAMON_NODISCARD
inline HAMON_CXX11_CONSTEXPR T&
get(variant<Types...>& v)
{
	// [variant.get]/5
	static_assert(variant_detail::exactly_once<T, Types...>::value, "");
	// [variant.get]/6
	return hamon::get<variant_detail::find_index<T, Types...>::value>(v);
}

template <typename T, typename... Types>
HAMON_NODISCARD
inline HAMON_CXX11_CONSTEXPR T&&
get(variant<Types...>&& v)
{
	// [variant.get]/5
	static_assert(variant_detail::exactly_once<T, Types...>::value, "");
	// [variant.get]/6
	return hamon::get<variant_detail::find_index<T, Types...>::value>(hamon::move(v));
}

template <typename T, typename... Types>
HAMON_NODISCARD
inline HAMON_CXX11_CONSTEXPR T const&
get(variant<Types...> const& v)
{
	// [variant.get]/5
	static_assert(variant_detail::exactly_once<T, Types...>::value, "");
	// [variant.get]/6
	return hamon::get<variant_detail::find_index<T, Types...>::value>(v);
}

template <typename T, typename... Types>
HAMON_NODISCARD
inline HAMON_CXX11_CONSTEXPR T const&&
get(variant<Types...> const&& v)
{
	// [variant.get]/5
	static_assert(variant_detail::exactly_once<T, Types...>::value, "");
	// [variant.get]/6
	return hamon::get<variant_detail::find_index<T, Types...>::value>(hamon::move(v));
}

}	// namespace hamon

#endif

#endif // HAMON_VARIANT_GET_HPP
