/**
 *	@file	accumulation.hpp
 *
 *	@brief	accumulation の定義
 */

#ifndef HAMON_TYPE_TRAITS_ACCUMULATION_HPP
#define HAMON_TYPE_TRAITS_ACCUMULATION_HPP

#include <hamon/type_traits/common_type.hpp>
#include <hamon/config.hpp>
#include <type_traits>

namespace hamon
{

/**
 *	@brief		コンパイル時の集計
 *
 *	@tparam		Ts
 *
 *	accumulation<Ts...> は
 *	value が 全ての Ts::value の合計、
 *	value_type が common_type_t<typename Ts::value_type...> 
 *	となる integral_constantから派生する。
 *	sizeof...(Ts) == 0 のときは、integral_constant<int, 0> から派生する。
 * 
 *	Tsは必ずしもintegral_constantから派生している必要はなく、
 *	Ts::value_type と Ts::value を持っていれば良い。
 */
template <typename... Ts>
struct accumulation;

namespace detail
{

template <typename...>
struct accumulation_impl;

template <>
struct accumulation_impl<>
	: public std::integral_constant<int, 0>
{};

template <typename T>
struct accumulation_impl<T>
	: public std::integral_constant<
		typename T::value_type,
		T::value
	>
{};

template <typename T1, typename T2>
struct accumulation_impl<T1, T2>
	: public std::integral_constant<
		hamon::common_type_t<typename T1::value_type, typename T2::value_type>,
		T1::value + T2::value
	>
{};

template <typename T1, typename T2, typename... Ts>
struct accumulation_impl<T1, T2, Ts...>
	: public accumulation_impl<
		accumulation_impl<T1, T2>, Ts...
	>
{};

}	// namespace detail

template <typename... Ts>
struct accumulation
	: public detail::accumulation_impl<Ts...>
{};

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

template <typename... Ts>
HAMON_INLINE_VAR HAMON_CONSTEXPR
auto accumulation_v = accumulation<Ts...>::value;

#endif

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_ACCUMULATION_HPP
