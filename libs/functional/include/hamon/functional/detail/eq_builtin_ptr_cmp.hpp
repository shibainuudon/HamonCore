/**
 *	@file	eq_builtin_ptr_cmp.hpp
 *
 *	@brief	eq_builtin_ptr_cmp クラステンプレートの定義
 */

#ifndef HAMON_FUNCTIONAL_DETAIL_EQ_BUILTIN_PTR_CMP_HPP
#define HAMON_FUNCTIONAL_DETAIL_EQ_BUILTIN_PTR_CMP_HPP

#include <hamon/concepts/same_as.hpp>
#include <hamon/concepts/convertible_to.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace ranges
{

namespace detail
{

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T, typename U>
concept eq_builtin_ptr_cmp =
	requires (T&& t, U&& u) { { t == u } -> hamon::same_as<bool>; } &&
	hamon::convertible_to<T, const volatile void*> &&
	hamon::convertible_to<U, const volatile void*> &&
	(
		!requires(T&& t, U&& u)
		{
			operator==(hamon::forward<T>(t), hamon::forward<U>(u));
		} &&
		!requires(T&& t, U&& u)
		{
			hamon::forward<T>(t).operator==(hamon::forward<U>(u));
		}
	);

#else

namespace eq_builtin_ptr_cmp_detail
{

template <typename T, typename U, typename = void>
struct has_operator_eq
	: public hamon::false_type {};

template <typename T, typename U>
struct has_operator_eq<T, U, hamon::void_t<decltype(operator==(hamon::declval<T>(), hamon::declval<U>()))>>
	: public hamon::true_type {};

template <typename T, typename U, typename = void>
struct has_member_eq
	: public hamon::false_type {};

template <typename T, typename U>
struct has_member_eq<T, U, hamon::void_t<decltype(hamon::declval<T>().operator==(hamon::declval<U>()))>>
	: public hamon::true_type {};

template <typename T, typename U>
struct eq_builtin_ptr_cmp_impl
{
private:
	template <typename T2, typename U2,
		typename = hamon::enable_if_t<
			hamon::same_as<decltype(hamon::declval<T2>() == hamon::declval<U2>()), bool>::value &&
			hamon::convertible_to<T2, const volatile void*>::value &&
			hamon::convertible_to<U2, const volatile void*>::value &&
			!has_operator_eq<T2, U2>::value &&
			!has_member_eq<T2, U2>::value
		>
	>
	static auto test(int) -> hamon::true_type;

	template <typename T2, typename U2>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<T, U>(0));
};

}	// namespace eq_builtin_ptr_cmp_detail

template <typename T, typename U>
using eq_builtin_ptr_cmp =
	typename eq_builtin_ptr_cmp_detail::eq_builtin_ptr_cmp_impl<T, U>::type;

#endif

}	// namespace detail

}	// namespace ranges

}	// namespace hamon

#endif // HAMON_FUNCTIONAL_DETAIL_EQ_BUILTIN_PTR_CMP_HPP
