/**
 *	@file	access.hpp
 *
 *	@brief	access の定義
 */

#ifndef HAMON_TUPLE_DETAIL_ACCESS_HPP
#define HAMON_TUPLE_DETAIL_ACCESS_HPP

#include <hamon/tuple/tuple_element.hpp>
#include <hamon/tuple/tuple.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/config.hpp>

namespace hamon {
namespace tuple_detail {

struct access
{
	template <hamon::size_t I, typename... Types>
	static HAMON_CXX11_CONSTEXPR hamon::tuple_element_t<I, hamon::tuple<Types...>>&
	get(hamon::tuple<Types...>& t) HAMON_NOEXCEPT
	{
		using type = hamon::tuple_element_t<I, hamon::tuple<Types...>>;
		return static_cast<hamon::tuple_detail::tuple_leaf<I, type>&>(t.m_impl).m_value;
	}

	template <hamon::size_t I, typename... Types>
	static HAMON_CXX11_CONSTEXPR hamon::tuple_element_t<I, hamon::tuple<Types...>>&&
	get(hamon::tuple<Types...>&& t) HAMON_NOEXCEPT
	{
		using type = hamon::tuple_element_t<I, hamon::tuple<Types...>>;
		return hamon::forward<type>(
			static_cast<hamon::tuple_detail::tuple_leaf<I, type>&&>(t.m_impl).m_value);
	}

	template <hamon::size_t I, typename... Types>
	static HAMON_CXX11_CONSTEXPR hamon::tuple_element_t<I, hamon::tuple<Types...>> const&
	get(hamon::tuple<Types...> const& t) HAMON_NOEXCEPT
	{
		using type = hamon::tuple_element_t<I, hamon::tuple<Types...>>;
		return static_cast<hamon::tuple_detail::tuple_leaf<I, type> const&>(t.m_impl).m_value;
	}

	template <hamon::size_t I, typename... Types>
	static HAMON_CXX11_CONSTEXPR hamon::tuple_element_t<I, hamon::tuple<Types...>> const&&
	get(hamon::tuple<Types...> const&& t) HAMON_NOEXCEPT
	{
		using type = hamon::tuple_element_t<I, hamon::tuple<Types...>>;
		return hamon::forward<type const>(
			static_cast<hamon::tuple_detail::tuple_leaf<I, type> const&&>(t.m_impl).m_value);
	}
};

}	// namespace tuple_detail
}	// namespace hamon

#endif // HAMON_TUPLE_DETAIL_ACCESS_HPP
