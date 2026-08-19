/**
 *	@file	disjunction.hpp
 *
 *	@brief	disjunction
 */

#ifndef HAMON_TYPE_TRAITS_DISJUNCTION_HPP
#define HAMON_TYPE_TRAITS_DISJUNCTION_HPP

#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/conditional.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 21.3.9 Logical operator traits[meta.logical]

namespace detail
{

template <typename...>
struct disjunction_impl;

template <>
struct disjunction_impl<>
	: public hamon::false_type
{};

template <typename B0>
struct disjunction_impl<B0>
	: public B0
{};

template <typename B0, typename... Bn>
struct disjunction_impl<B0, Bn...>
	: public hamon::conditional<
		static_cast<bool>(B0::value),
		B0,
		disjunction_impl<Bn...>
	>::type
{};

}	// namespace detail

/**
 *	@brief		コンパイル時の論理OR
 *
 *	@tparam		B
 *
 *	disjunction<B1, ..., Bn> は最初にBi::value != false となるBiから派生する。
 *	もし全てのBiにおいて Bi::value == false ならBnから派生する。
 *	sizeof...(B) == 0 のときは、false_typeから派生する。
 *
 *	disjunctionはショート・サーキットされる：もしBi::value != falseとなったら、
 *	それ以降のBiはインスタンス化されない。
 *
 *	備考：
 *	Bは必ずしもtrue_typeまたはfalse_typeから派生している必要はない。
 *	B::valueを持っていて、B::valueがboolに変換可能であれば良い。
 *	例)
 *	disjunction<integral_constant<int, 2>, integral_constant<int, 4>>::value
 *	は 2 になる。
 */
template <typename... B>
struct disjunction
	: public detail::disjunction_impl<B...>
{};

template <typename... B>
HAMON_INLINE_VAR HAMON_CXX11_CONSTEXPR
bool disjunction_v = disjunction<B...>::value;

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_DISJUNCTION_HPP
