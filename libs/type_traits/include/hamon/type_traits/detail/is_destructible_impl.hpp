/**
 *	@file	is_destructible_impl.hpp
 *
 *	@brief	is_destructible_impl の定義
 */

#ifndef HAMON_TYPE_TRAITS_DETAIL_IS_DESTRUCTIBLE_IMPL_HPP
#define HAMON_TYPE_TRAITS_DETAIL_IS_DESTRUCTIBLE_IMPL_HPP

#include <hamon/type_traits/add_lvalue_reference.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/is_function.hpp>
#include <hamon/type_traits/is_reference.hpp>
#include <hamon/type_traits/is_unbounded_array.hpp>
#include <hamon/type_traits/is_void.hpp>
#include <hamon/type_traits/remove_all_extents.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>

namespace hamon
{
namespace detail
{

template <typename U, typename = void>
struct do_is_destructible_impl
	: public hamon::false_type
{};

template <typename U>
struct do_is_destructible_impl<U,
	hamon::void_t<decltype(hamon::declval<hamon::add_lvalue_reference_t<U>>().~U())>>
	: public hamon::true_type
{};

template <typename T, bool = hamon::is_reference_v<T>>
struct is_destructible_impl
	: public hamon::true_type
{};

template <typename T>
struct is_destructible_impl<T, false>
	: public hamon::bool_constant<
		!hamon::is_void_v<T> &&
		!hamon::is_function_v<T> &&
		!hamon::is_unbounded_array_v<T> &&
		do_is_destructible_impl<hamon::remove_all_extents_t<T>>::value
	>
{};

}	// namespace detail
}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_DETAIL_IS_DESTRUCTIBLE_IMPL_HPP
