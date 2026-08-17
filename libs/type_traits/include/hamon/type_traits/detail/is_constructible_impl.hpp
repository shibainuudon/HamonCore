/**
 *	@file	is_constructible_impl.hpp
 *
 *	@brief	is_constructible_impl の定義
 */

#ifndef HAMON_TYPE_TRAITS_DETAIL_IS_CONSTRUCTIBLE_IMPL_HPP
#define HAMON_TYPE_TRAITS_DETAIL_IS_CONSTRUCTIBLE_IMPL_HPP

#include <hamon/type_traits/detail/is_default_constructible_impl.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/conditional.hpp>
#include <hamon/type_traits/is_function.hpp>
#include <hamon/type_traits/is_reference.hpp>
#include <hamon/type_traits/is_unbounded_array.hpp>
#include <hamon/type_traits/is_void.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/config.hpp>

namespace hamon
{
namespace detail
{

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4244)	// '_Ty' から '_Ty' への変換です。データが失われる可能性があります。

template <typename T, typename... Args>
struct do_is_constructible_impl_ref
{
	template <typename T1>
	static auto test(T1) -> hamon::true_type;

	template <typename T1>
	static auto test(...) -> hamon::false_type;

	using type = decltype(test<T>(hamon::declval<Args>()...));
};

template <typename T, typename... Args>
struct do_is_constructible_impl_1
{
	template <typename T1, typename... Args1,
		typename = decltype(::new T1(hamon::declval<Args1>()...))
	>
	static auto test(int) -> hamon::true_type;

	template <typename T1, typename... Args1>
	static auto test(...) -> hamon::false_type;

	using type = decltype(test<T, Args...>(0));
};

#if defined(HAMON_HAS_CXX20_AGGREGATE_PAREN_INIT)
// P0960R3 によってint n[2](1, 2); のような形での初期化が可能になった

template <typename T, hamon::size_t N>
struct TArray
{
	T arr[N];
};

template <typename T, hamon::size_t N, typename... Args>
struct do_is_constructible_impl_1<T[N], Args...>
{
	template <typename T1, typename... Args1,
		typename = decltype(TArray<T1, N>{hamon::declval<Args1>()...})
	>
	static auto test(int) -> hamon::true_type;

	template <typename T1, typename... Args1>
	static auto test(...) -> hamon::false_type;

	using type = decltype(test<T, Args...>(0));
};
#endif

template <typename T, typename... Args>
using do_is_constructible_impl = typename hamon::conditional_t<
	hamon::is_reference_v<T>,
	do_is_constructible_impl_ref<T, Args...>,
	do_is_constructible_impl_1<T, Args...>
>::type;

template <typename T, typename... Args>
struct is_constructible_impl
	: public hamon::bool_constant<
		!hamon::is_void_v<T> &&
		!hamon::is_function_v<T> &&
		!hamon::is_unbounded_array_v<T> &&
		do_is_constructible_impl<T, Args...>::value
	>
{};

template <typename T>
struct is_constructible_impl<T>
	: public hamon::detail::is_default_constructible_impl<T>
{};

HAMON_WARNING_POP()

}	// namespace detail
}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_DETAIL_IS_CONSTRUCTIBLE_IMPL_HPP
