/**
 *	@file	common_reference.hpp
 *
 *	@brief	common_reference の定義
 */

#ifndef HAMON_TYPE_TRAITS_COMMON_REFERENCE_HPP
#define HAMON_TYPE_TRAITS_COMMON_REFERENCE_HPP

#include <hamon/type_traits/basic_common_reference.hpp>
#include <hamon/type_traits/config.hpp>

#if defined(HAMON_USE_STD_COMMON_REFERENCE)

#include <type_traits>

namespace hamon
{

using std::common_reference;
using std::common_reference_t;

}	// namespace hamon

#else

#include <hamon/type_traits/common_type.hpp>
#include <hamon/type_traits/conditional.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/type_traits/copy_cv.hpp>
#include <hamon/type_traits/decay.hpp>
#include <hamon/type_traits/disjunction.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/remove_cvref.hpp>
#include <hamon/type_traits/remove_reference.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/type_traits/is_reference.hpp>
#include <hamon/type_traits/is_convertible.hpp>
#include <hamon/type_traits/is_scalar.hpp>
#include <hamon/type_traits/is_array.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/is_lvalue_reference.hpp>
#include <hamon/type_traits/is_rvalue_reference.hpp>
#include <hamon/type_traits/add_pointer.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/config.hpp>

namespace hamon
{

template <typename... T>
struct common_reference;

template <typename... T>
using common_reference_t = typename common_reference<T...>::type;

namespace detail
{

// [meta.trans.other]/2.3	COPYCV(FROM, TO)
template <typename From, typename To>
using copycv = hamon::copy_cv_t<To, From>;

HAMON_WARNING_PUSH()
#if defined(HAMON_CLANG_VERSION) && (HAMON_CLANG_VERSION >= 100000)
HAMON_WARNING_DISABLE_CLANG("-Wdeprecated-volatile")
#endif

// [meta.trans.other]/2.4	COND-RES(X, Y)
#if !defined(_MSC_VER)

template <typename X, typename Y>
using cond_res = decltype(false ? hamon::declval<X(&)()>()() : hamon::declval<Y(&)()>()());

#else

template <typename X, typename Y, typename = void>
struct cond_res_workaround {};

template <typename X, typename Y>
struct cond_res_workaround<X, Y, hamon::void_t<decltype(false ? hamon::declval<X(&)()>()() : hamon::declval<Y(&)()>()())>>
{
    using U = hamon::remove_cvref_t<X>;
    using type = hamon::conditional_t<
		hamon::conjunction<
			hamon::is_same<U, hamon::remove_cvref_t<Y>>,
			hamon::disjunction<hamon::is_scalar<U>, hamon::is_array<U>>,
			hamon::disjunction<
				hamon::conjunction<hamon::is_lvalue_reference<X>, hamon::is_rvalue_reference<Y>>,
				hamon::conjunction<hamon::is_rvalue_reference<X>, hamon::is_lvalue_reference<Y>>
			>
		>::value,
        hamon::decay_t<copycv<hamon::remove_reference_t<X>, hamon::remove_reference_t<Y>>>,
		decltype(false ? hamon::declval<X(&)()>()() : hamon::declval<Y(&)()>()())
	>;
};

template <typename X, typename Y>
using cond_res = typename cond_res_workaround<X, Y>::type;

#endif

HAMON_WARNING_POP()

template <typename A, typename B, typename = void>
struct common_ref_impl
{};

// [meta.trans.other], COMMON-REF(A, B)
template <typename A, typename B>
using common_ref = typename common_ref_impl<A, B>::type;

// [meta.trans.other]/2.5
// COND-RES(COPYCV(X, Y) &, COPYCV(Y, X) &)
template <typename X, typename Y>
using condres_cvref = cond_res<copycv<X, Y>&, copycv<Y, X>&>;

// If A and B are both lvalue reference types, ...
template <typename X, typename Y>
struct common_ref_impl<X&, Y&,
	hamon::enable_if_t<
		hamon::is_reference<condres_cvref<X, Y>>::value>
>
{
	using type = condres_cvref<X, Y>;
};

// [meta.trans.other]/2.6
// let C be remove_reference_t<COMMON-REF(X&, Y&)>&&
template <typename X, typename Y>
using common_ref_C = hamon::remove_reference_t<common_ref<X&, Y&>>&&;

// If A and B are both rvalue reference types, ...
template <typename X, typename Y>
struct common_ref_impl<X&&, Y&&,
	hamon::enable_if_t<hamon::conjunction<
		hamon::is_convertible<X&&, common_ref_C<X, Y>>,
		hamon::is_convertible<Y&&, common_ref_C<X, Y>>
	>::value>
>
{
	using type = common_ref_C<X, Y>;
};

// [meta.trans.other]/2.7
// let D be COMMON-REF(const X&, Y&)
template <typename X, typename Y>
using common_ref_D = common_ref<const X&, Y&>;

// If A is an rvalue reference and B is an lvalue reference, ...
template <typename X, typename Y>
struct common_ref_impl<X&&, Y&,
	hamon::enable_if_t<
		hamon::is_convertible<X&&, common_ref_D<X, Y>>::value>
>
{
	using type = common_ref_D<X, Y>;
};

// [meta.trans.other]/2.8
// If A is an lvalue reference and B is an rvalue reference, ...
template <typename X, typename Y>
struct common_ref_impl<X&, Y&&>
	: public common_ref_impl<Y&&, X&>
{};

// [meta.trans.other]/2.2	XREF(A)
template <typename T>
struct xref
{
	template <typename U> using type = copycv<T, U>;
};

template <typename T>
struct xref<T&>
{
	template <typename U> using type = copycv<T, U>&;
};

template <typename T>
struct xref<T&&>
{
	template <typename U> using type = copycv<T, U>&&;
};

template <
	typename T1, typename T2,
	bool B = hamon::is_reference<T1>::value && hamon::is_reference<T2>::value,
	int Bullet = 1,
	typename = void>
struct common_reference_impl
	: public common_reference_impl<T1, T2, B, Bullet + 1>
{};

// [meta.trans.other]/5.3.1
// If T1 and T2 are reference types and COMMON-REF(T1, T2) is well-formed, ...
template <typename T1, typename T2>
struct common_reference_impl<T1, T2, true, 1,
	hamon::enable_if_t<hamon::conjunction<
		hamon::is_convertible<hamon::add_pointer_t<T1>, hamon::add_pointer_t<common_ref<T1, T2>>>,
		hamon::is_convertible<hamon::add_pointer_t<T2>, hamon::add_pointer_t<common_ref<T1, T2>>>
	>::value>
>
{
	using type = common_ref<T1, T2>;
};

// [meta.trans.other]/5.3.2
// Otherwise, if basic_common_reference<...>::type is well-formed, ...
template <typename T1, typename T2>
using basic_common_ref =
	typename hamon::basic_common_reference<
		hamon::remove_cvref_t<T1>,
		hamon::remove_cvref_t<T2>,
		xref<T1>::template type,
		xref<T2>::template type
	>::type;

template <typename T1, typename T2, bool B>
struct common_reference_impl<T1, T2, B, 2,
	hamon::void_t<basic_common_ref<T1, T2>>>
{
	using type = basic_common_ref<T1, T2>;
};

// [meta.trans.other]/5.3.3
// Otherwise, if COND-RES(T1, T2) is well-formed, ...
template <typename T1, typename T2, bool B>
struct common_reference_impl<T1, T2, B, 3,
	hamon::void_t<cond_res<T1, T2>>>
{
	using type = cond_res<T1, T2>;
};

// [meta.trans.other]/5.3.4
// Otherwise, if common_type_t<T1, T2> is well-formed, ...
template <typename T1, typename T2, bool B>
struct common_reference_impl<T1, T2, B, 4,
	hamon::void_t<hamon::common_type_t<T1, T2>>>
{
	using type = hamon::common_type_t<T1, T2>;
};

// [meta.trans.other]/5.3.5
// Otherwise, there shall be no member type.
template <typename T1, typename T2, bool B>
struct common_reference_impl<T1, T2, B, 5, void>
{};

// [meta.trans.other]/5.4.2
template <typename...>
struct common_reference_fold
{};

// [meta.trans.other]/5.4.1
template <typename T1, typename T2, typename... Rest>
struct common_reference_fold<
	hamon::void_t<hamon::common_reference_t<T1, T2>>, T1, T2, Rest...>
	: public common_reference<hamon::common_reference_t<T1, T2>, Rest...>
{};

}	// namespace detail

// [meta.trans.other]/5.1
// If sizeof...(T) is zero, there shall be no member type.
template <>
struct common_reference<>
{};

// [meta.trans.other]/5.2
// If sizeof...(T) is one ...
template <typename T0>
struct common_reference<T0>
{
	using type = T0;
};

// [meta.trans.other]/5.3
// If sizeof...(T) is two ...
template <typename T1, typename T2>
struct common_reference<T1, T2>
	: public detail::common_reference_impl<T1, T2>
{};

// [meta.trans.other]/5.4
// Otherwise, if sizeof...(T) is greater than two, ...
template <typename T1, typename T2, typename... Rest>
struct common_reference<T1, T2, Rest...>
	: public detail::common_reference_fold<void, T1, T2, Rest...>
{};

}	// namespace hamon

#endif

#endif // HAMON_TYPE_TRAITS_COMMON_REFERENCE_HPP
