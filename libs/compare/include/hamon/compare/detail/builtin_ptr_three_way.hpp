/**
 *	@file	builtin_ptr_three_way.hpp
 *
 *	@brief	builtin_ptr_three_way の定義
 */

#ifndef HAMON_COMPARE_DETAIL_BUILTIN_PTR_THREE_WAY_HPP
#define HAMON_COMPARE_DETAIL_BUILTIN_PTR_THREE_WAY_HPP

#include <hamon/config.hpp>

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)

#include <hamon/concepts/convertible_to.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/utility/declval.hpp>

namespace hamon
{

namespace detail
{

#if defined(HAMON_HAS_CXX20_CONCEPTS)

// BUILTIN-PTR-THREE-WAY(T, U)
template <typename T, typename U>
HAMON_CONCEPT_OR_BOOL builtin_ptr_three_way =
	requires(T&& t, U&& u)
	{
		static_cast<T&&>(t) <=> static_cast<U&&>(u);
	} &&
	hamon::convertible_to<T, void const volatile*> &&
	hamon::convertible_to<U, void const volatile*> &&
	!requires(T&& t, U&& u)
	{
		operator<=>(static_cast<T&&>(t), static_cast<U&&>(u));
	} &&
	!requires(T&& t, U&& u)
	{
		static_cast<T&&>(t).operator<=>(static_cast<U&&>(u));
	};

#else

template <typename T, typename U>
struct builtin_ptr_three_way_impl
{
private:
	template <typename T2, typename U2,
		typename = decltype(operator<=>(hamon::declval<T2&&>(), hamon::declval<U2&&>()))
	>
	static auto user_defined_three_way1(int) -> hamon::true_type;

	template <typename T2, typename U2>
	static auto user_defined_three_way1(...) -> hamon::false_type;

	template <typename T2, typename U2,
		typename = decltype(hamon::declval<T2&&>().operator<=>(hamon::declval<U2&&>()))
	>
	static auto user_defined_three_way2(int) -> hamon::true_type;

	template <typename T2, typename U2>
	static auto user_defined_three_way2(...) -> hamon::false_type;

	template <typename T2, typename U2,
		typename = decltype(hamon::declval<T2&&>() <=> hamon::declval<U2&&>()),
		typename = hamon::enable_if_t<hamon::convertible_to<T2, void const volatile*>>,
		typename = hamon::enable_if_t<hamon::convertible_to<U2, void const volatile*>>,
		typename = hamon::enable_if_t<!decltype(user_defined_three_way1<T2, U2>(0))::value>,
		typename = hamon::enable_if_t<!decltype(user_defined_three_way2<T2, U2>(0))::value>
	>
	static auto test(int) -> hamon::true_type;

	template <typename T2, typename U2>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<T, U>(0));
};

template <typename T, typename U>
HAMON_CONCEPT_OR_BOOL builtin_ptr_three_way =
	builtin_ptr_three_way_impl<T, U>::type::value;

#endif

}	// namespace detail

}	// namespace hamon

#endif

#endif // HAMON_COMPARE_DETAIL_BUILTIN_PTR_THREE_WAY_HPP
