/**
 *	@file	is_nothrow_convertible_impl.hpp
 *
 *	@brief	is_nothrow_convertible_impl の定義
 */

#ifndef HAMON_TYPE_TRAITS_DETAIL_IS_NOTHROW_CONVERTIBLE_IMPL_HPP
#define HAMON_TYPE_TRAITS_DETAIL_IS_NOTHROW_CONVERTIBLE_IMPL_HPP

#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/is_convertible.hpp>
#include <hamon/type_traits/is_void.hpp>
#include <hamon/utility/declval.hpp>

namespace hamon
{
namespace detail
{

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4244)	// '引数': '_Ty1' から 'To' への変換です。データが失われる可能性があります。
HAMON_WARNING_DISABLE_CLANG("-Wimplicit-int-conversion")
HAMON_WARNING_DISABLE_CLANG("-Wimplicit-int-float-conversion")

template <typename To>
static void is_nothrow_convertible_impl_helper(To) noexcept;

template <typename From, typename To,
	bool = hamon::is_convertible_v<From, To>,
	bool = hamon::is_void_v<From> && hamon::is_void_v<To>
>
struct is_nothrow_convertible_impl
	: public hamon::false_type
{};

template <typename From, typename To>
struct is_nothrow_convertible_impl<From, To, true, true>
	: public hamon::true_type
{};

template <typename From, typename To>
struct is_nothrow_convertible_impl<From, To, true, false>
	: public hamon::bool_constant<
		noexcept(is_nothrow_convertible_impl_helper<To>(hamon::declval<From>()))>
{};

HAMON_WARNING_POP()

}	// namespace detail
}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_DETAIL_IS_NOTHROW_CONVERTIBLE_IMPL_HPP
