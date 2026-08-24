/**
 *	@file	common_type_helper.hpp
 *
 *	@brief	common_type と common_reference の実装で使われるものの定義
 */

#ifndef HAMON_TYPE_TRAITS_DETAIL_COMMON_TYPE_HELPER_HPP
#define HAMON_TYPE_TRAITS_DETAIL_COMMON_TYPE_HELPER_HPP

#include <hamon/type_traits/add_lvalue_reference.hpp>
#include <hamon/type_traits/conditional.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/type_traits/copy_cv.hpp>
#include <hamon/type_traits/decay.hpp>
#include <hamon/type_traits/disjunction.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_array.hpp>
#include <hamon/type_traits/is_convertible.hpp>
#include <hamon/type_traits/is_lvalue_reference.hpp>
#include <hamon/type_traits/is_reference.hpp>
#include <hamon/type_traits/is_rvalue_reference.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/is_scalar.hpp>
#include <hamon/type_traits/remove_reference.hpp>
#include <hamon/type_traits/remove_cvref.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/config.hpp>

namespace hamon {
namespace detail {

// [meta.trans.other]/3.1	CREF(A)
template <typename A>
using CREF = hamon::add_lvalue_reference_t<const hamon::remove_reference_t<A>>;

// [meta.trans.other]/3.2	XREF(A)
template <typename T>
struct XREF
{
	template <typename U> using type = hamon::copy_cv_t<U, T>;
};

template <typename T>
struct XREF<T&>
{
	template <typename U> using type = hamon::copy_cv_t<U, T>&;
};

template <typename T>
struct XREF<T&&>
{
	template <typename U> using type = hamon::copy_cv_t<U, T>&&;
};

// [meta.trans.other]/3.3	COPYCV(FROM, TO)
template <typename From, typename To>
using COPYCV = hamon::copy_cv_t<To, From>;

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_CLANG("-Wdeprecated-volatile")
HAMON_WARNING_DISABLE_MSVC(4244)	// '引数': 'T' から 'const T' への変換です。データが失われる可能性があります。

// [meta.trans.other]/3.4	COND-RES(X, Y)
#if !(defined(HAMON_MSVC) && (HAMON_MSVC < 1930))

template <typename X, typename Y>
using COND_RES = decltype(false ? hamon::declval<X(&)()>()() : hamon::declval<Y(&)()>()());

#else

template <typename X, typename Y, typename = void>
struct COND_RES_workaround {};

template <typename X, typename Y>
struct COND_RES_workaround<X, Y, hamon::void_t<decltype(false ? hamon::declval<X(&)()>()() : hamon::declval<Y(&)()>()())>>
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
        hamon::decay_t<COPYCV<hamon::remove_reference_t<X>, hamon::remove_reference_t<Y>>>,
		decltype(false ? hamon::declval<X(&)()>()() : hamon::declval<Y(&)()>()())
	>;
};

template <typename X, typename Y>
using COND_RES = typename COND_RES_workaround<X, Y>::type;

#endif

HAMON_WARNING_POP()

template <typename A, typename B, typename = void>
struct common_ref_impl
{};

// [meta.trans.other], COMMON-REF(A, B)
template <typename A, typename B>
using COMMON_REF = typename common_ref_impl<A, B>::type;

// [meta.trans.other]/3.5
// If A and B are both lvalue reference types,
// COMMON-REF(A, B) is COND-RES(COPYCV(X, Y) &, COPYCV(​Y, X) &)
// if that type exists and is a reference type.
template <typename X, typename Y>
struct common_ref_impl<X&, Y&,
	hamon::enable_if_t<
		hamon::is_reference_v<COND_RES<COPYCV<X, Y>&, COPYCV<Y, X>&>>
	>
>
{
	using type = COND_RES<COPYCV<X, Y>&, COPYCV<Y, X>&>;
};

// [meta.trans.other]/3.6
// Otherwise, let C be remove_reference_t<COMMON-REF(X&, Y&)>&&.
// If A and B are both rvalue reference types, C is well-formed, and
// is_convertible_v<A, C> && is_convertible_v<B, C> is true,
// then COMMON-REF(A, B) is C.
template <typename X, typename Y>
using common_ref_C = hamon::remove_reference_t<COMMON_REF<X&, Y&>>&&;

template <typename X, typename Y>
struct common_ref_impl<X&&, Y&&,
	hamon::enable_if_t<
		hamon::is_convertible_v<X&&, common_ref_C<X, Y>> &&
		hamon::is_convertible_v<Y&&, common_ref_C<X, Y>>
	>
>
{
	using type = common_ref_C<X, Y>;
};

// [meta.trans.other]/3.7
// Otherwise, let D be COMMON-REF(const X&, Y&).
// If A is an rvalue reference and B is an lvalue reference and
// D is well-formed and is_convertible_v<A, D> is true,
// then COMMON-REF(A, B) is D.
template <typename X, typename Y>
using common_ref_D = COMMON_REF<const X&, Y&>;

template <typename X, typename Y>
struct common_ref_impl<X&&, Y&,
	hamon::enable_if_t<
		hamon::is_convertible_v<X&&, common_ref_D<X, Y>>
	>
>
{
	using type = common_ref_D<X, Y>;
};

// [meta.trans.other]/3.8
// Otherwise, if A is an lvalue reference and B is an rvalue reference,
// then COMMON-REF(A, B) is COMMON-REF(B, A).
template <typename X, typename Y>
struct common_ref_impl<X&, Y&&>
	: public common_ref_impl<Y&&, X&>
{};

}	// namespace detail
}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_DETAIL_COMMON_TYPE_HELPER_HPP
