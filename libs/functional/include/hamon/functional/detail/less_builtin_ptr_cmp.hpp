/**
 *	@file	less_builtin_ptr_cmp.hpp
 *
 *	@brief	less_builtin_ptr_cmp クラステンプレートの定義
 */

#ifndef HAMON_FUNCTIONAL_DETAIL_LESS_BUILTIN_PTR_CMP_HPP
#define HAMON_FUNCTIONAL_DETAIL_LESS_BUILTIN_PTR_CMP_HPP

#include <hamon/concepts/same_as.hpp>
#include <hamon/concepts/convertible_to.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/config.hpp>
#include <utility>

namespace hamon
{

namespace ranges
{

namespace detail
{

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T, typename U>
concept less_builtin_ptr_cmp =
	requires (T&& t, U&& u) { { t < u } -> hamon::same_as<bool>; } &&
	hamon::convertible_to<T, const volatile void*> &&
	hamon::convertible_to<U, const volatile void*> &&
	(
		!requires(T&& t, U&& u)
		{
			operator<(std::forward<T>(t), std::forward<U>(u));
		} &&
		!requires(T&& t, U&& u)
		{
			std::forward<T>(t).operator<(std::forward<U>(u));
		}
	);

#else

namespace less_builtin_ptr_cmp_detail
{

template <typename T, typename U, typename = void>
struct has_operator_less
	: public hamon::false_type {};

template <typename T, typename U>
struct has_operator_less<T, U, hamon::void_t<decltype(operator<(std::declval<T>(), std::declval<U>()))>>
	: public hamon::true_type {};

template <typename T, typename U, typename = void>
struct has_member_less
	: public hamon::false_type {};

template <typename T, typename U>
struct has_member_less<T, U, hamon::void_t<decltype(std::declval<T>().operator<(std::declval<U>()))>>
	: public hamon::true_type {};

template <typename T, typename U>
struct less_builtin_ptr_cmp_impl
{
private:
	template <typename T2, typename U2,
		typename = hamon::enable_if_t<
			hamon::same_as<decltype(std::declval<T2>() < std::declval<U2>()), bool>::value &&
			hamon::convertible_to<T2, const volatile void*>::value &&
			hamon::convertible_to<U2, const volatile void*>::value &&
			!has_operator_less<T2, U2>::value &&
			!has_member_less<T2, U2>::value
		>
	>
	static auto test(int) -> hamon::true_type;

	template <typename T2, typename U2>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<T, U>(0));
};

}	// namespace less_builtin_ptr_cmp_detail

template <typename T, typename U>
using less_builtin_ptr_cmp =
	typename less_builtin_ptr_cmp_detail::less_builtin_ptr_cmp_impl<T, U>::type;

#endif

}	// namespace detail

}	// namespace ranges

}	// namespace hamon

#endif // HAMON_FUNCTIONAL_DETAIL_LESS_BUILTIN_PTR_CMP_HPP
