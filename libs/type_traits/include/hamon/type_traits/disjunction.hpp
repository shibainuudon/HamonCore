/**
 *	@file	disjunction.hpp
 *
 *	@brief	disjunction
 */

#ifndef HAMON_TYPE_TRAITS_DISJUNCTION_HPP
#define HAMON_TYPE_TRAITS_DISJUNCTION_HPP

#include <hamon/config.hpp>
#include <type_traits>

namespace hamon
{

#if defined(__cpp_lib_logical_traits) && (__cpp_lib_logical_traits >= 201510)

using std::disjunction;

#else

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
struct disjunction;

namespace detail
{

template <typename...>
struct disjunction_impl;

template <>
struct disjunction_impl<>
	: public std::false_type
{};

template <typename B0>
struct disjunction_impl<B0>
	: public B0
{};

template <typename B0, typename... Bn>
struct disjunction_impl<B0, Bn...>
	: public std::conditional<
		static_cast<bool>(B0::value),
		B0,
		disjunction_impl<Bn...>
	>::type
{};

}	// namespace detail

template <typename... B>
struct disjunction
	: public detail::disjunction_impl<B...>
{};

#endif

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

template <typename... B>
HAMON_INLINE_VAR HAMON_CONSTEXPR
bool disjunction_v = disjunction<B...>::value;

#endif

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_DISJUNCTION_HPP
