/**
 *	@file	common_type.hpp
 *
 *	@brief	common_type の定義
 */

#ifndef HAMON_TYPE_TRAITS_COMMON_TYPE_HPP
#define HAMON_TYPE_TRAITS_COMMON_TYPE_HPP

#include <hamon/type_traits/detail/common_type_helper.hpp>
#include <hamon/type_traits/decay.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/type_identity.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/utility/declval.hpp>

namespace hamon
{

/**
 *	@brief	変換可能な共通の型を取得する。
 *
 *	@tparam		Types...
 *
 *	@require	Types...の全ての型は完全型であるか、void(cv修飾を含む)でなければならない。
 *
 *	common_typeは、Types...に含まれる全ての型が暗黙変換可能な型を、メンバ型typeとして定義する。
 */
template <typename... Types>
struct common_type;

template <typename... Types>
using common_type_t = typename common_type<Types...>::type;

// [meta.trans.other]/4.1
// If sizeof...(T) is zero, there shall be no member type.
template <>
struct common_type<>
{};

// [meta.trans.other]/4.2
// If sizeof...(T) is one, let T0 denote the sole type constituting the pack T.
// The member typedef-name type shall denote the same type, if any,
// as common_type_t<T0, T0>; otherwise there shall be no member type.
template <typename T0>
struct common_type<T0>
	: public common_type<T0, T0>
{};

// [meta.trans.other]/4.3
// If sizeof...(T) is two, let the first and second types constituting T be denoted by T1 and T2, respectively,
// and let D1 and D2 denote the same types as decay_t<T1> and decay_t<T2>, respectively.
namespace detail
{

template <typename T1, typename T2>
struct common_type_impl
{
private:
	struct failure_type {};

	// [meta.trans.other]/4.3.1
	// If is_same_v<T1, D1> is false or is_same_v<T2, D2> is false,
	// let C denote the same type, if any, as common_type_t<D1, D2>.
	template <typename U1, typename U2, typename D1, typename D2,
		typename = hamon::enable_if_t<
			!hamon::is_same_v<U1, D1> || !hamon::is_same_v<U2, D2>
		>
	>
	static auto test(hamon::detail::overload_priority<3>)
		-> hamon::type_identity<typename hamon::common_type<D1, D2>::type>;

	// [meta.trans.other]/4.3.2
	// [Note 4: None of the following will apply if there is a specialization common_type<D1, D2>. — end note]

	// [meta.trans.other]/4.3.3
	// Otherwise, if decay_t<decltype(false ? declval<D1>() : declval<D2>())>
	// denotes a valid type, let C denote that type.
	template <typename U1, typename U2, typename D1, typename D2>
	static auto test(hamon::detail::overload_priority<2>)
		-> hamon::type_identity<hamon::decay_t<decltype(false ? hamon::declval<D1>() : hamon::declval<D2>())>>;

	// [meta.trans.other]/4.3.4
	// Otherwise, if COND-RES(CREF(D1), CREF(D2)) denotes a type,
	// let C denote the type decay_t<COND-RES(CREF(D1), CREF(D2))>.
	template <typename U1, typename U2, typename D1, typename D2>
	static auto test(hamon::detail::overload_priority<1>)
		-> hamon::type_identity<hamon::decay_t<COND_RES<CREF<D1>, CREF<D2>>>>;

	// Otherwise, there shall be no member type.
	template <typename U1, typename U2, typename D1, typename D2>
	static auto test(hamon::detail::overload_priority<0>)
		-> failure_type;

public:
	using type = decltype(test<T1, T2, hamon::decay_t<T1>, hamon::decay_t<T2>>(hamon::detail::overload_priority<3>{}));
};

}	// namespace detail

template <typename T1, typename T2>
struct common_type<T1, T2>
	: public detail::common_type_impl<T1, T2>::type
{};

// [meta.trans.other]/4.4
// If sizeof...(T) is greater than two, let T1, T2, and R, respectively,
// denote the first, second, and (pack of) remaining types constituting T.
// Let C denote the same type, if any, as common_type_t<T1, T2>.
// If there is such a type C, the member typedef-name type shall denote the same type,
// if any, as common_type_t<C, R...>. Otherwise, there shall be no member type.
namespace detail
{

template <typename...>
struct common_type_fold
{};

template <typename T1, typename T2, typename... R>
struct common_type_fold<hamon::void_t<typename hamon::common_type<T1, T2>::type>, T1, T2, R...>
	: public hamon::common_type<typename hamon::common_type<T1, T2>::type, R...>
{};

}	// namespace detail

template <typename T1, typename T2, typename... R>
struct common_type<T1, T2, R...>
	: public detail::common_type_fold<void, T1, T2, R...>
{};

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_COMMON_TYPE_HPP
