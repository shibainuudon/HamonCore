/**
 *	@file	is_nothrow_default_constructible_impl.hpp
 *
 *	@brief	is_nothrow_default_constructible_impl の定義
 */

#ifndef HAMON_TYPE_TRAITS_DETAIL_IS_NOTHROW_DEFAULT_CONSTRUCTIBLE_IMPL_HPP
#define HAMON_TYPE_TRAITS_DETAIL_IS_NOTHROW_DEFAULT_CONSTRUCTIBLE_IMPL_HPP

#include <hamon/type_traits/detail/is_default_constructible_impl.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/conditional.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/config.hpp>

namespace hamon
{
namespace detail
{

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4197)	// 'T': キャストの トップレベルの volatile は無視されます。

template <typename T>
struct do_is_nothrow_default_constructible_impl
	: public hamon::bool_constant<noexcept(T())>
{};

HAMON_WARNING_POP()

template <typename T>
struct is_nothrow_default_constructible_impl
	: public hamon::conditional_t<
		!hamon::detail::is_default_constructible_impl<T>::value,
		hamon::false_type,
		do_is_nothrow_default_constructible_impl<T>
	>
{};

template <typename T, hamon::size_t N>
struct is_nothrow_default_constructible_impl<T[N]>
	: public hamon::detail::is_nothrow_default_constructible_impl<T>
{};

}	// namespace detail
}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_DETAIL_IS_NOTHROW_DEFAULT_CONSTRUCTIBLE_IMPL_HPP
