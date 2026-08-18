/**
 *	@file	is_nothrow_constructible_impl.hpp
 *
 *	@brief	is_nothrow_constructible_impl の定義
 */

#ifndef HAMON_TYPE_TRAITS_DETAIL_IS_NOTHROW_CONSTRUCTIBLE_IMPL_HPP
#define HAMON_TYPE_TRAITS_DETAIL_IS_NOTHROW_CONSTRUCTIBLE_IMPL_HPP

#include <hamon/type_traits/detail/is_constructible_impl.hpp>
#include <hamon/type_traits/detail/is_nothrow_default_constructible_impl.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/conditional.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/config.hpp>

namespace hamon
{
namespace detail
{

template <typename T, typename... Args>
struct do_is_nothrow_constructible_impl
	: public hamon::bool_constant<noexcept(T(hamon::declval<Args>()...))>
{};

#if defined(HAMON_HAS_CXX20_AGGREGATE_PAREN_INIT)
template <typename T, hamon::size_t N, typename... Args>
struct do_is_nothrow_constructible_impl<T[N], Args...>
	: public hamon::bool_constant<noexcept(TArray<T, N>{hamon::declval<Args>()...})>
{};
#endif

template <typename T, typename... Args>
struct is_nothrow_constructible_impl
	: public hamon::conditional_t<
		!hamon::detail::is_constructible_impl<T, Args...>::value,
		hamon::false_type,
		do_is_nothrow_constructible_impl<T, Args...>
	>
{};

template <typename T>
struct is_nothrow_constructible_impl<T>
	: public hamon::detail::is_nothrow_default_constructible_impl<T>
{};

}	// namespace detail
}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_DETAIL_IS_NOTHROW_CONSTRUCTIBLE_IMPL_HPP
