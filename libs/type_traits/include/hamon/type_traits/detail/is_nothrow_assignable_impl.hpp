/**
 *	@file	is_nothrow_assignable_impl.hpp
 *
 *	@brief	is_nothrow_assignable_impl の定義
 */

#ifndef HAMON_TYPE_TRAITS_DETAIL_IS_NOTHROW_ASSIGNABLE_IMPL_HPP
#define HAMON_TYPE_TRAITS_DETAIL_IS_NOTHROW_ASSIGNABLE_IMPL_HPP

#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/conditional.hpp>
#include <hamon/type_traits/is_assignable.hpp>
#include <hamon/utility/declval.hpp>

namespace hamon
{
namespace detail
{

template <typename T, typename U>
struct do_is_nothrow_assignable_impl
	: public hamon::bool_constant<noexcept(hamon::declval<T>() = hamon::declval<U>())>
{};

template <typename T, typename U>
struct is_nothrow_assignable_impl
	: public hamon::conditional_t<
		!hamon::is_assignable<T, U>::value,
		hamon::false_type,
		do_is_nothrow_assignable_impl<T, U>
	>
{};

}	// namespace detail
}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_DETAIL_IS_NOTHROW_ASSIGNABLE_IMPL_HPP
