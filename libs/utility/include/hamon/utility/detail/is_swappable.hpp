/**
 *	@file	is_swappable.hpp
 *
 *	@brief	is_swappable の定義
 */

#ifndef HAMON_UTILITY_DETAIL_IS_SWAPPABLE_HPP
#define HAMON_UTILITY_DETAIL_IS_SWAPPABLE_HPP

#include <hamon/utility/declval.hpp>
#include <hamon/utility/swap.hpp>
#include <hamon/type_traits/add_lvalue_reference.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/conditional.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_void.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

template <typename T, typename U>
struct is_swappable_with_impl
{
private:
	template <
		typename T2,
		typename U2,
		typename = decltype(
			swap(hamon::declval<T2>(), hamon::declval<U2>()),
			swap(hamon::declval<U2>(), hamon::declval<T2>()))
	>
	static hamon::true_type test(int);

	template <typename, typename>
	static hamon::false_type test(...);

public:
	using type = decltype(test<T, U>(0));
};

template <typename T, typename U>
struct is_swappable_with
	: public hamon::detail::is_swappable_with_impl<T, U>::type
{};

template <typename T>
struct is_swappable
	: public hamon::conditional_t<
		hamon::is_void<T>::value,	// TODO is_referenceable
		hamon::false_type,
		hamon::detail::is_swappable_with<
			hamon::add_lvalue_reference_t<T>,
			hamon::add_lvalue_reference_t<T>
		>
	>
{};

template <typename T, typename U>
struct is_nothrow_swappable_with_impl
{
private:
	template <typename T2, typename U2,
		typename = hamon::enable_if_t<
			hamon::detail::is_swappable_with<T2, U2>::value
		>
	>
	static hamon::bool_constant<
		HAMON_NOEXCEPT_EXPR(swap(hamon::declval<T2>(), hamon::declval<U2>())) &&
		HAMON_NOEXCEPT_EXPR(swap(hamon::declval<U2>(), hamon::declval<T2>()))
	>
	test(int);

	template <typename, typename>
	static hamon::false_type test(...);

public:
	using type = decltype(test<T, U>(0));
};

template <typename T, typename U>
struct is_nothrow_swappable_with
	: public hamon::detail::is_nothrow_swappable_with_impl<T, U>::type
{};

template <typename T>
struct is_nothrow_swappable
	: public hamon::conditional_t<
		hamon::is_void<T>::value,	// TODO is_referenceable
		hamon::false_type,
		hamon::detail::is_nothrow_swappable_with<
			hamon::add_lvalue_reference_t<T>,
			hamon::add_lvalue_reference_t<T>
		>
	>
{};

}	// namespace detail

}	// namespace hamon

#endif // HAMON_UTILITY_DETAIL_IS_SWAPPABLE_HPP
