/**
 *	@file	common_reference.hpp
 *
 *	@brief	common_reference の定義
 */

#ifndef HAMON_TYPE_TRAITS_COMMON_REFERENCE_HPP
#define HAMON_TYPE_TRAITS_COMMON_REFERENCE_HPP

#include <hamon/type_traits/detail/common_type_helper.hpp>
#include <hamon/type_traits/add_pointer.hpp>
#include <hamon/type_traits/basic_common_reference.hpp>
#include <hamon/type_traits/common_type.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_convertible.hpp>
#include <hamon/type_traits/is_reference.hpp>
#include <hamon/type_traits/remove_cvref.hpp>
#include <hamon/type_traits/void_t.hpp>

namespace hamon
{

// [meta.trans.other], other transformations
template <typename... T>
struct common_reference;

template <typename... T>
using common_reference_t = typename common_reference<T...>::type;

// [meta.trans.other]/6.1
// If sizeof...(T) is zero, there shall be no member type.
template <>
struct common_reference<>
{};

// [meta.trans.other]/6.2
// Otherwise, if sizeof...(T) is one, let T0 denote the sole type in the pack T.
// The member typedef type shall denote the same type as T0.
template <typename T0>
struct common_reference<T0>
{
	using type = T0;
};

// [meta.trans.other]/6.3
// Otherwise, if sizeof...(T) is two, let T1 and T2 denote the two types in the pack T. Then
namespace detail
{

template <
	typename T1, typename T2,
	int Bullet = 1,
	typename = void>
struct common_reference_impl
	: public common_reference_impl<T1, T2, Bullet + 1>
{};

// [meta.trans.other]/6.3.1
// Let R be COMMON-REF(T1, T2).
// If T1 and T2 are reference types, R is well-formed, and
// is_convertible_v<add_pointer_t<T1>, add_pointer_t<R>> &&
// is_convertible_v<add_pointer_t<T2>, add_pointer_t<R>> is true,
// then the member typedef type denotes R.
template <typename T1, typename T2>
struct common_reference_impl<T1, T2, 1,
	hamon::enable_if_t<
		hamon::is_reference_v<T1> &&
		hamon::is_reference_v<T2> &&
		hamon::is_convertible_v<hamon::add_pointer_t<T1>, hamon::add_pointer_t<COMMON_REF<T1, T2>>> &&
		hamon::is_convertible_v<hamon::add_pointer_t<T2>, hamon::add_pointer_t<COMMON_REF<T1, T2>>>
	>
>
{
	using type = COMMON_REF<T1, T2>;
};

// [meta.trans.other]/6.3.2
// Otherwise, if basic_common_reference<remove_cvref_t<T1>, remove_cvref_t<T2>,​ XREF(​T1), XREF(T2)>​::​type
// is well-formed, then the member typedef type denotes that type.
template <typename T1, typename T2>
using basic_common_ref =
	typename hamon::basic_common_reference<
		hamon::remove_cvref_t<T1>,
		hamon::remove_cvref_t<T2>,
		XREF<T1>::template type,
		XREF<T2>::template type
	>::type;

template <typename T1, typename T2>
struct common_reference_impl<T1, T2, 2,
	hamon::void_t<basic_common_ref<T1, T2>>>
{
	using type = basic_common_ref<T1, T2>;
};

// [meta.trans.other]/6.3.3
// Otherwise, if COND-RES(T1, T2) is well-formed, then the member typedef type denotes that type.
template <typename T1, typename T2>
struct common_reference_impl<T1, T2, 3,
	hamon::void_t<COND_RES<T1, T2>>>
{
	using type = COND_RES<T1, T2>;
};

// [meta.trans.other]/6.3.4
// Otherwise, if common_type_t<T1, T2> is well-formed, then the member typedef type denotes that type.
template <typename T1, typename T2>
struct common_reference_impl<T1, T2, 4,
	hamon::void_t<hamon::common_type_t<T1, T2>>>
{
	using type = hamon::common_type_t<T1, T2>;
};

// [meta.trans.other]/6.3.5
// Otherwise, there shall be no member type.
template <typename T1, typename T2>
struct common_reference_impl<T1, T2, 5, void>
{};

}	// namespace detail

template <typename T1, typename T2>
struct common_reference<T1, T2>
	: public detail::common_reference_impl<T1, T2>
{};

// [meta.trans.other]/6.4
// Otherwise, if sizeof...(T) is greater than two, let T1, T2, and Rest, respectively,
// denote the first, second, and (pack of) remaining types comprising T.
// Let C be the type common_reference_t<T1, T2>. Then:
namespace detail
{

// [meta.trans.other]/6.4.2
// Otherwise, there shall be no member type.
template <typename...>
struct common_reference_fold
{};

// [meta.trans.other]/6.4.1
// If there is such a type C, the member typedef type shall denote the same type,
// if any, as common_reference_t<C, Rest...>.
template <typename T1, typename T2, typename... Rest>
struct common_reference_fold<hamon::void_t<hamon::common_reference_t<T1, T2>>, T1, T2, Rest...>
	: public common_reference<hamon::common_reference_t<T1, T2>, Rest...>
{};

}	// namespace detail

template <typename T1, typename T2, typename... Rest>
struct common_reference<T1, T2, Rest...>
	: public detail::common_reference_fold<void, T1, T2, Rest...>
{};

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_COMMON_REFERENCE_HPP
