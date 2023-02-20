/**
 *	@file	variadic_union.hpp
 *
 *	@brief	variadic_union の定義
 */

#ifndef HAMON_VARIANT_DETAIL_VARIADIC_UNION_HPP
#define HAMON_VARIANT_DETAIL_VARIADIC_UNION_HPP

#include <hamon/cstddef/size_t.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/type_traits/is_trivially_destructible.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/utility/in_place_index.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace variant_detail
{

template <bool TriviallyDestructible, typename... Types>
union variadic_union_impl
{
};

template <typename Head, typename... Tail>
union variadic_union_impl<true, Head, Tail...>
{
	//~variadic_union_impl() = default;

	HAMON_CXX11_CONSTEXPR variadic_union_impl() : m_tail() {}

	template <typename... Args>
	HAMON_CXX11_CONSTEXPR explicit
	variadic_union_impl(hamon::in_place_index_t<0>, Args&&... args)
		: m_head(hamon::forward<Args>(args)...)
	{}

	template <hamon::size_t I, typename... Args>
	HAMON_CXX11_CONSTEXPR explicit
	variadic_union_impl(hamon::in_place_index_t<I>, Args&&... args)
		: m_tail(hamon::in_place_index_t<I-1>{}, hamon::forward<Args>(args)...)
	{}

	Head m_head;
	variadic_union_impl<true, Tail...> m_tail;
};

template <typename Head, typename... Tail>
union variadic_union_impl<false, Head, Tail...>
{
	HAMON_CXX20_CONSTEXPR ~variadic_union_impl() {}

	HAMON_CXX11_CONSTEXPR variadic_union_impl() : m_tail() {}

	template <typename... Args>
	HAMON_CXX11_CONSTEXPR explicit
	variadic_union_impl(hamon::in_place_index_t<0>, Args&&... args)
		: m_head(hamon::forward<Args>(args)...)
	{}

	template <hamon::size_t I, typename... Args>
	HAMON_CXX11_CONSTEXPR explicit
	variadic_union_impl(hamon::in_place_index_t<I>, Args&&... args)
		: m_tail(hamon::in_place_index_t<I-1>{}, hamon::forward<Args>(args)...)
	{}

	Head m_head;
	variadic_union_impl<false, Tail...> m_tail;
};

template <typename... Types>
using variadic_union =
	variadic_union_impl<
		hamon::conjunction<hamon::is_trivially_destructible<Types>...>::value,
		Types...
	>;

}	// namespace variant_detail

}	// namespace hamon

#endif // HAMON_VARIANT_DETAIL_VARIADIC_UNION_HPP
