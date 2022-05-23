/**
 *	@file	common_reference.hpp
 *
 *	@brief	common_reference の定義
 */

#ifndef HAMON_TYPE_TRAITS_COMMON_REFERENCE_HPP
#define HAMON_TYPE_TRAITS_COMMON_REFERENCE_HPP

#include <hamon/type_traits/basic_common_reference.hpp>
#include <hamon/config.hpp>

#if defined(HAMON_HAS_CXX20_CONCEPTS) && HAMON_HAS_INCLUDE(<concepts>)
#include <concepts>
#endif

#if defined(__cpp_lib_concepts) && (__cpp_lib_concepts >= 202002)

#include <type_traits>

namespace hamon
{

using std::common_reference;
using std::common_reference_t;

}	// namespace hamon

#else

#include <hamon/type_traits/common_type.hpp>
#include <hamon/type_traits/copy_cv.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/remove_cvref.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/type_traits/detail/common_type_fold.hpp>
#include <hamon/type_traits/detail/common_type_pack.hpp>
#include <hamon/type_traits/detail/cond_res.hpp>
#include <type_traits>

namespace hamon
{

template <typename... T>
struct common_reference;

template <typename... T>
using common_reference_t = typename common_reference<T...>::type;

namespace detail
{

template <
	typename A,
	typename B,
	typename X = typename std::remove_reference<A>::type,
	typename Y = typename std::remove_reference<B>::type,
	bool = std::is_lvalue_reference<A>::value,
	bool = std::is_lvalue_reference<B>::value,
	typename = hamon::void_t<>
>
struct common_ref_impl
{};

// [meta.trans.other], COMMON-REF(A, B)
template <typename A, typename B>
using common_ref = typename detail::common_ref_impl<A, B>::type;

// If A and B are both lvalue reference types, ...
template <typename A, typename B, typename X, typename Y>
struct common_ref_impl<A, B, X, Y, true, true,
	hamon::void_t<detail::cond_res<hamon::copy_cv_t<X, Y>&, hamon::copy_cv_t<Y, X>&>>
>
{
	using type = detail::cond_res<hamon::copy_cv_t<X, Y>&, hamon::copy_cv_t<Y, X>&>;
};

// let C be remove_reference_t<COMMON-REF(X&, Y&)>&&
template <typename X, typename Y>
using common_ref_C = typename std::remove_reference<detail::common_ref<X&, Y&>>::type&&;

// If A and B are both rvalue reference types, ...
template <typename A, typename B, typename X, typename Y>
struct common_ref_impl<A, B, X, Y, false, false,
	hamon::enable_if_t<
		std::is_convertible<A, detail::common_ref_C<X, Y>>::value &&
		std::is_convertible<B, detail::common_ref_C<X, Y>>::value
	>
>
{
	using type = detail::common_ref_C<X, Y>;
};

// let D be COMMON-REF(const X&, Y&)
template <typename X, typename Y>
using common_ref_D = detail::common_ref<const X&, Y&>;

// If A is an rvalue reference and B is an lvalue reference, ...
template <typename A, typename B, typename X, typename Y>
struct common_ref_impl<A, B, X, Y, false, true,
	hamon::enable_if_t<
		std::is_convertible<A, detail::common_ref_D<X, Y>>::value
	>
>
{
	using type = detail::common_ref_D<X, Y>;
};

// If A is an lvalue reference and B is an rvalue reference, ...
template <typename A, typename B, typename X, typename Y>
struct common_ref_impl<A, B, X, Y, true, false>
	: public common_ref_impl<B, A>
{};

template <typename T>
struct xref
{
	template <typename U> using type = hamon::copy_cv_t<U, T>;
};

template <typename T>
struct xref<T&>
{
	template <typename U> using type = hamon::copy_cv_t<U, T>&;
};

template <typename T>
struct xref<T&&>
{
	template <typename U> using type = hamon::copy_cv_t<U, T>&&;
};

template <typename T1, typename T2>
using basic_common_ref =
	typename hamon::basic_common_reference<
		hamon::remove_cvref_t<T1>,
		hamon::remove_cvref_t<T2>,
		detail::xref<T1>::template type,
		detail::xref<T2>::template type
	>::type;

template <typename T1, typename T2, int Bullet = 1, bool = std::is_reference<T1>::value && std::is_reference<T2>::value, typename = hamon::void_t<>>
struct common_reference_impl
	: public common_reference_impl<T1, T2, Bullet + 1>
{};

// If T1 and T2 are reference types and COMMON-REF(T1, T2) is well-formed, ...
template <typename T1, typename T2>
struct common_reference_impl<T1, T2, 1, true,
	hamon::void_t<detail::common_ref<T1, T2>>>
{
	using type = detail::common_ref<T1, T2>;
};

// Otherwise, if basic_common_reference<...>::type is well-formed, ...
template <typename T1, typename T2, bool B>
struct common_reference_impl<T1, T2, 2, B,
	hamon::void_t<detail::basic_common_ref<T1, T2>>>
{
	using type = detail::basic_common_ref<T1, T2>;
};

// Otherwise, if COND-RES(T1, T2) is well-formed, ...
template <typename T1, typename T2, bool B>
struct common_reference_impl<T1, T2, 3, B,
	hamon::void_t<detail::cond_res<T1, T2>>>
{
	using type = detail::cond_res<T1, T2>;
};

// Otherwise, if hamon::common_type_t<T1, T2> is well-formed, ...
template <typename T1, typename T2, bool B>
struct common_reference_impl<T1, T2, 4, B,
	hamon::void_t<hamon::common_type_t<T1, T2>>>
{
	using type = hamon::common_type_t<T1, T2>;
};

// Otherwise, there shall be no member type.
template <typename T1, typename T2, bool B>
struct common_reference_impl<T1, T2, 5, B, hamon::void_t<>>
{};

template <typename T1, typename T2, typename... Rest>
struct common_type_fold<
	common_reference<T1, T2>,
	detail::common_type_pack<Rest...>,
	hamon::void_t<hamon::common_reference_t<T1, T2>>
>
	: public hamon::common_reference<hamon::common_reference_t<T1, T2>, Rest...>
{};

}	// namespace detail

// If sizeof...(T) is zero, there shall be no member type.
template <>
struct common_reference<>
{};

// If sizeof...(T) is one ...
template <typename T0>
struct common_reference<T0>
{
	using type = T0;
};

// If sizeof...(T) is two ...
template <typename T1, typename T2>
struct common_reference<T1, T2>
	: public detail::common_reference_impl<T1, T2>
{};

// Otherwise, if sizeof...(T) is greater than two, ...
template <typename T1, typename T2, typename... Rest>
struct common_reference<T1, T2, Rest...>
	: public detail::common_type_fold<
		common_reference<T1, T2>,
		detail::common_type_pack<Rest...>
	>
{};

}	// namespace hamon

#endif

#endif // HAMON_TYPE_TRAITS_COMMON_REFERENCE_HPP
