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
#include <hamon/type_traits/remove_cvref.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

#define HAMON_NOEXCEPT_DECLTYPE_RETURN(...) \
	HAMON_NOEXCEPT_IF_EXPR(__VA_ARGS__)     \
	-> decltype((__VA_ARGS__))              \
	{ return __VA_ARGS__; }

template <typename Compare>
struct heterogeneous_compare
{
public:
	Compare comp;

private:
	template <typename T, typename = hamon::enable_if_t<
		hamon::pair_like_t<hamon::remove_cvref_t<T>>::value>>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto
	get_key_impl(T const& t, hamon::detail::overload_priority<1>) const
	HAMON_NOEXCEPT_DECLTYPE_RETURN(
		hamon::adl_get<0>(t))

	template <typename T>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR T const&
	get_key_impl(T const& t, hamon::detail::overload_priority<0>) const noexcept
	{
		return t;
	}

	template <typename T>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto
	get_key(T const& t) const
	HAMON_NOEXCEPT_DECLTYPE_RETURN(
		get_key_impl(t, hamon::detail::overload_priority<1>{}))

public:
	HAMON_CXX11_CONSTEXPR
	heterogeneous_compare()
		: comp() {}

	HAMON_CXX11_CONSTEXPR
	heterogeneous_compare(Compare const& c)
		: comp(c) {}

	template <typename Lhs, typename Rhs>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto
	operator()(Lhs const& x, Rhs const& y) const
	HAMON_NOEXCEPT_DECLTYPE_RETURN(
		comp(get_key(x), get_key(y)))
};

#undef HAMON_NOEXCEPT_DECLTYPE_RETURN

}	// namespace detail

}	// namespace hamon

#endif // HAMON_MAP_DETAIL_HETEROGENEOUS_COMPARE_HPP
