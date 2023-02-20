/**
 *	@file	get_if.hpp
 *
 *	@brief	get_if の定義
 */

#ifndef HAMON_VARIANT_GET_IF_HPP
#define HAMON_VARIANT_GET_IF_HPP

#include <hamon/variant/config.hpp>

#if defined(HAMON_USE_STD_VARIANT)

namespace hamon
{

using std::get_if;

}	// namespace hamon

#else

#include <hamon/variant/detail/access.hpp>
#include <hamon/variant/detail/exactly_once.hpp>
#include <hamon/variant/detail/find_index.hpp>
#include <hamon/variant/variant_alternative.hpp>
#include <hamon/variant/variant.hpp>
#include <hamon/memory/addressof.hpp>
#include <hamon/type_traits/add_pointer.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// [variant.get], value access
template <hamon::size_t I, typename... Types>
HAMON_NODISCARD
inline HAMON_CXX11_CONSTEXPR
hamon::add_pointer_t<variant_alternative_t<I, variant<Types...>>>
get_if(variant<Types...>* v) HAMON_NOEXCEPT
{
	// [variant.get]/7
	static_assert(I < sizeof...(Types), "variant index out of bounds");
	// [variant.get]/8
	return v && v->index() == I ?
		hamon::addressof(variant_detail::access::get<I>(*v)) :
		nullptr;
}

template <hamon::size_t I, typename... Types>
HAMON_NODISCARD
inline HAMON_CXX11_CONSTEXPR
hamon::add_pointer_t<variant_alternative_t<I, variant<Types...>> const>
get_if(variant<Types...> const* v) HAMON_NOEXCEPT
{
	// [variant.get]/7
	static_assert(I < sizeof...(Types), "variant index out of bounds");
	// [variant.get]/8
	return v && v->index() == I ?
		hamon::addressof(variant_detail::access::get<I>(*v)) :
		nullptr;
}

template <typename T, typename... Types>
HAMON_NODISCARD
inline HAMON_CXX11_CONSTEXPR hamon::add_pointer_t<T>
get_if(variant<Types...>* v) HAMON_NOEXCEPT
{
	// [variant.get]/9
	static_assert(variant_detail::exactly_once<T, Types...>::value, "");
	// [variant.get]/10
	return hamon::get_if<variant_detail::find_index<T, Types...>::value>(v);
}

template <typename T, typename... Types>
HAMON_NODISCARD
inline HAMON_CXX11_CONSTEXPR hamon::add_pointer_t<T const>
get_if(variant<Types...> const* v) HAMON_NOEXCEPT
{
	// [variant.get]/9
	static_assert(variant_detail::exactly_once<T, Types...>::value, "");
	// [variant.get]/10
	return hamon::get_if<variant_detail::find_index<T, Types...>::value>(v);
}

}	// namespace hamon

#endif

#endif // HAMON_VARIANT_GET_IF_HPP
