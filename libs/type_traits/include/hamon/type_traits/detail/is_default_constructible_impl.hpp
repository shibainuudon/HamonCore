/**
 *	@file	is_default_constructible_impl.hpp
 *
 *	@brief	is_default_constructible_impl の定義
 */

#ifndef HAMON_TYPE_TRAITS_DETAIL_IS_DEFAULT_CONSTRUCTIBLE_IMPL_HPP
#define HAMON_TYPE_TRAITS_DETAIL_IS_DEFAULT_CONSTRUCTIBLE_IMPL_HPP

#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/is_function.hpp>
#include <hamon/type_traits/is_unbounded_array.hpp>
#include <hamon/type_traits/is_void.hpp>
#include <hamon/cstddef/size_t.hpp>

namespace hamon
{
namespace detail
{

template <typename T>
struct do_is_default_constructible_impl
{
	template <typename T1, typename = decltype(T1())>
	static auto test(int) -> hamon::true_type;

	template <typename T1>
	static auto test(...) -> hamon::false_type;

	using type = decltype(test<T>(0));
};

template <typename T>
struct is_default_constructible_impl
	: public hamon::bool_constant<
		!hamon::is_void_v<T> &&
		!hamon::is_function_v<T> &&
		!hamon::is_unbounded_array_v<T> &&
		do_is_default_constructible_impl<T>::type::value
	>
{};

template <typename T, hamon::size_t N>
struct is_default_constructible_impl<T[N]>
	: public hamon::detail::is_default_constructible_impl<T>
{};

}	// namespace detail
}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_DETAIL_IS_DEFAULT_CONSTRUCTIBLE_IMPL_HPP
