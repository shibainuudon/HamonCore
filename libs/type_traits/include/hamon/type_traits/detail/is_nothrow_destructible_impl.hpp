/**
 *	@file	is_nothrow_destructible_impl.hpp
 *
 *	@brief	is_nothrow_destructible_impl の定義
 */

#ifndef HAMON_TYPE_TRAITS_DETAIL_IS_NOTHROW_DESTRUCTIBLE_IMPL_HPP
#define HAMON_TYPE_TRAITS_DETAIL_IS_NOTHROW_DESTRUCTIBLE_IMPL_HPP

#include <hamon/type_traits/detail/is_destructible_impl.hpp>
#include <hamon/type_traits/add_lvalue_reference.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/conditional.hpp>
#include <hamon/type_traits/is_reference.hpp>
#include <hamon/type_traits/remove_all_extents.hpp>
#include <hamon/utility/declval.hpp>

namespace hamon
{
namespace detail
{

template <typename U>
struct do_is_nothrow_destructible_impl
	: public hamon::bool_constant<noexcept(hamon::declval<hamon::add_lvalue_reference_t<U>>().~U())>
{};

template <typename T>
struct is_nothrow_destructible_impl : public
	hamon::conditional_t<
		hamon::is_reference_v<T>,
		hamon::true_type,
		hamon::conditional_t<
			!hamon::detail::is_destructible_impl<T>::value,
			hamon::false_type,
			do_is_nothrow_destructible_impl<hamon::remove_all_extents_t<T>>
		>
	>
{};

}	// namespace detail
}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_DETAIL_IS_NOTHROW_DESTRUCTIBLE_IMPL_HPP
