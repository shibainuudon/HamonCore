/**
 *	@file	heterogeneous_compare.hpp
 *
 *	@brief
 */

#ifndef HAMON_MAP_DETAIL_HETEROGENEOUS_COMPARE_HPP
#define HAMON_MAP_DETAIL_HETEROGENEOUS_COMPARE_HPP

#include <hamon/detail/overload_priority.hpp>
#include <hamon/tuple/adl_get.hpp>
#include <hamon/tuple/concepts/pair_like.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

template <typename Compare>
struct heterogeneous_compare
{
private:
	Compare& comp;

	template <typename T, typename = hamon::enable_if_t<hamon::pair_like_t<hamon::remove_cvref_t<T>>::value>>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto
	get_key_impl(T const& t, hamon::detail::overload_priority<1>) const noexcept
	->decltype(hamon::adl_get<0>(t))
	{
		return hamon::adl_get<0>(t);
	}

	template <typename T>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR T const&
	get_key_impl(T const& t, hamon::detail::overload_priority<0>) const noexcept
	{
		return t;
	}

	template <typename T>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto
	get_key(T const& t) const noexcept
	->decltype(get_key_impl(t, hamon::detail::overload_priority<1>{}))
	{
		return get_key_impl(t, hamon::detail::overload_priority<1>{});
	}

public:
	HAMON_CXX11_CONSTEXPR
	heterogeneous_compare(Compare& c) : comp(c) {}

	template <typename Lhs, typename Rhs>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bool
	operator()(Lhs const& x, Rhs const& y) const
	{
		return comp(get_key(x), get_key(y));
	}
};

}	// namespace detail

}	// namespace hamon

#endif // HAMON_MAP_DETAIL_HETEROGENEOUS_COMPARE_HPP
