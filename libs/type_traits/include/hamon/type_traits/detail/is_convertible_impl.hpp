/**
 *	@file	is_convertible_impl.hpp
 *
 *	@brief	is_convertible_impl の定義
 */

#ifndef HAMON_TYPE_TRAITS_DETAIL_IS_CONVERTIBLE_IMPL_HPP
#define HAMON_TYPE_TRAITS_DETAIL_IS_CONVERTIBLE_IMPL_HPP

#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/conditional.hpp>
#include <hamon/type_traits/is_array.hpp>
#include <hamon/type_traits/is_function.hpp>
#include <hamon/type_traits/is_void.hpp>
#include <hamon/utility/declval.hpp>

namespace hamon
{
namespace detail
{

template <typename From, typename To>
struct do_is_convertible_impl
{
	template <typename To1>
	static void test_helper(To1);

	template <typename From1, typename To1,
		typename = decltype(test_helper<To1>(hamon::declval<From1>()))
	>
	static auto test(int) -> hamon::true_type;

	template <typename From1, typename To1>
	static auto test(...) -> hamon::false_type;

	using type = decltype(test<From, To>(0));
};

template <typename From, typename To>
struct is_convertible_impl : public
	hamon::conditional_t<
		hamon::is_void_v<From> && hamon::is_void_v<To>,
		hamon::true_type,
		hamon::conditional_t<
			hamon::is_function_v<To> || hamon::is_array_v<To>,
			hamon::false_type,
			typename do_is_convertible_impl<From, To>::type
		>
	>
{};

}	// namespace detail
}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_DETAIL_IS_CONVERTIBLE_IMPL_HPP
