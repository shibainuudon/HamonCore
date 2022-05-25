/**
 *	@file	arithmetic_promote.hpp
 *
 *	@brief	arithmetic_promote
 */

#ifndef HAMON_TYPE_TRAITS_ARITHMETIC_PROMOTE_HPP
#define HAMON_TYPE_TRAITS_ARITHMETIC_PROMOTE_HPP

#include <hamon/type_traits/type_identity.hpp>
#include <hamon/type_traits/remove_cv.hpp>
#include <type_traits>

namespace hamon
{

/**
 *	@brief	通常の算術型変換によって昇格した型を得る
 * 
 *	@tparam	T...	算術型
 * 
 *	@require	全てのTにおいて is_arithmetic<T>::value == true
 * 
 *	T1 + T2 + ... + Ti のような演算のときに変換される型を得る。
 *	詳細な規則は https://en.cppreference.com/w/c/language/conversion の
 *	「Usual arithmetic conversions」を参照。
 */
template <typename... T>
struct arithmetic_promote;

/**
 *	@brief	arithmetic_promoteのエイリアステンプレート
 */
template <typename... T>
using arithmetic_promote_t = typename arithmetic_promote<T...>::type;

namespace detail
{

template <typename... T>
struct arithmetic_promote_impl;

template <typename T>
struct arithmetic_promote_impl<T>
	: public hamon::type_identity<T>
{
	static_assert(std::is_arithmetic<T>::value, "");
};

template <typename T, typename U>
struct arithmetic_promote_impl<T, U>
	: public std::decay<decltype(std::declval<T>() + std::declval<U>())>
{
	static_assert(std::is_arithmetic<T>::value, "");
	static_assert(std::is_arithmetic<U>::value, "");
};

template <typename T, typename U, typename... Tail>
struct arithmetic_promote_impl<T, U, Tail...>
	: public arithmetic_promote_impl<typename arithmetic_promote_impl<T, U>::type, Tail...>
{};

}	// namespace detail

template <typename... T>
struct arithmetic_promote
	: public detail::arithmetic_promote_impl<
		hamon::remove_cv_t<T>...
	>
{};

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_ARITHMETIC_PROMOTE_HPP
