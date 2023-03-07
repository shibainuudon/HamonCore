/**
 *	@file	common_type.hpp
 *
 *	@brief	common_type の定義
 */

#ifndef HAMON_TYPE_TRAITS_COMMON_TYPE_HPP
#define HAMON_TYPE_TRAITS_COMMON_TYPE_HPP

#include <hamon/config.hpp>
#include <type_traits>

#if defined(HAMON_HAS_CXX20_CONCEPTS) && HAMON_HAS_INCLUDE(<concepts>)
#include <concepts>
#endif

#if defined(__cpp_lib_concepts) && (__cpp_lib_concepts >= 202002)

namespace hamon
{

#define HAMON_COMMON_TYPE_NAMESPACE std

using std::common_type;

}	// namespace hamon

#else

#include <hamon/type_traits/type_identity.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/type_traits/detail/common_type_fold.hpp>
#include <hamon/type_traits/detail/common_type_pack.hpp>
#include <hamon/utility/declval.hpp>

namespace hamon
{

#define HAMON_COMMON_TYPE_NAMESPACE hamon

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

namespace detail
{

// If sizeof...(T) is two, ...
template <
	typename T1, typename T2,
	typename D1 = typename std::decay<T1>::type,
	typename D2 = typename std::decay<T2>::type
>
struct common_type_impl
{
	// If is_same_v<T1, D1> is false or is_same_v<T2, D2> is false,
	// let C denote the same type, if any, as common_type_t<D1, D2>.
	using type = hamon::common_type<D1, D2>;
};

template <typename T1, typename T2>
struct common_type_impl<T1, T2, T1, T2>
{
private:
	struct failure_type
	{};

	template <typename T, typename U>
	using cond_t = decltype(false ? hamon::declval<T>() : hamon::declval<U>());

	// Otherwise, if decay_t<decltype(false ? declval<D1>() : declval<D2>())>
	// denotes a valid type, let C denote that type.
	template <typename T, typename U>
	static auto test(int) -> hamon::type_identity<typename std::decay<cond_t<T, U>>::type>;

	// Otherwise, if COND-RES(CREF(D1), CREF(D2)) denotes a type,
	// let C denote the type decay_t<COND-RES(CREF(D1), CREF(D2))>.
	template <typename T, typename U>
	static auto test_2(int) -> hamon::type_identity<typename std::decay<cond_t<const T&, const U&>>::type>;

	template <typename, typename>
	static auto test_2(...) -> failure_type;

	template <typename T, typename U>
	static auto test(...) -> decltype(test_2<T, U>(0));

public:
	using type = decltype(test<T1, T2>(0));
};

template <typename T1, typename T2, typename... Rest>
struct common_type_fold<
	hamon::common_type<T1, T2>,
	detail::common_type_pack<Rest...>,
	hamon::void_t<typename hamon::common_type<T1, T2>::type>
>
	: public hamon::common_type<typename hamon::common_type<T1, T2>::type, Rest...>
{};

}	// namespace detail

// If sizeof...(T) is zero, there shall be no member type.
template <>
struct common_type<>
{};

// If sizeof...(T) is one, the same type, if any, as common_type_t<T0, T0>.
template <typename T0>
struct common_type<T0>
	: public common_type<T0, T0>
{};

// If sizeof...(T) is two, ...
template <typename T1, typename T2>
struct common_type<T1, T2>
	: public detail::common_type_impl<T1, T2>::type
{};

// If sizeof...(T) is greater than two, ...
template <typename T1, typename T2, typename... Rest>
struct common_type<T1, T2, Rest...>
	: public detail::common_type_fold<
		hamon::common_type<T1, T2>,
		detail::common_type_pack<Rest...>
	>
{};

}	// namespace hamon

#endif

namespace hamon
{

template <typename... Types>
using common_type_t = typename common_type<Types...>::type;

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_COMMON_TYPE_HPP
