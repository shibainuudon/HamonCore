/**
 *	@file	float_promote.hpp
 *
 *	@brief	float_promote
 */

#ifndef HAMON_TYPE_TRAITS_FLOAT_PROMOTE_HPP
#define HAMON_TYPE_TRAITS_FLOAT_PROMOTE_HPP

#include <hamon/type_traits/remove_cv.hpp>
#include <type_traits>

namespace hamon
{

/**
 *	@brief	浮動小数点数への昇格
 *
 *	Types のどれか1つでも long double だったとき、type は long double
 *	Types が全て float だったとき、type は float
 *	それ以外のとき、type は double
 */
template <typename... Types>
struct float_promote;

/**
 *	@brief	float_promoteのエイリアステンプレート
 */
template <typename... Types>
using float_promote_t = typename float_promote<Types...>::type;

namespace detail
{

template <typename... Types>
struct float_promote_impl;

template <typename T>
struct float_promote_impl<T>
	: public std::conditional<
		std::is_floating_point<T>::value,
		T,
		double
	>
{};

template <typename T, typename U>
struct float_promote_impl<T, U>
	: public std::conditional<
		std::is_same<T, long double>::value ||
		std::is_same<U, long double>::value,
		long double,
		typename std::conditional<
			std::is_same<T, float>::value &&
			std::is_same<U, float>::value,
			float,
			double
		>::type
	>
{};

template <typename T, typename U, typename... Tail>
struct float_promote_impl<T, U, Tail...>
	: public float_promote_impl<
		typename float_promote_impl<T, U>::type,
		Tail...
	>
{};

}	// namespace detail

template <typename... Types>
struct float_promote
	: public detail::float_promote_impl<
		hamon::remove_cv_t<Types>...
	>
{};

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_FLOAT_PROMOTE_HPP
