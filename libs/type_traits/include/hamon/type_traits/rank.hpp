/**
 *	@file	rank.hpp
 *
 *	@brief	rank の定義
 */

#ifndef HAMON_TYPE_TRAITS_RANK_HPP
#define HAMON_TYPE_TRAITS_RANK_HPP

#include <hamon/type_traits/integral_constant.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 21.3.6 Type property queries[meta.unary.prop.query]

/**
 *	@brief	配列型の次元数を取得する。
 *
 *	@tparam		T
 *
 *	型Tが配列型である場合、配列の次元数となる整数値をメンバ定数valueの値として定義する。
 *	配列型でなければ0をメンバ定数valueの値として定義する。
 */
template <typename T>
struct rank
	: public hamon::integral_constant<hamon::size_t, 0>
{};

template <typename T, hamon::size_t N>
struct rank<T[N]>
	: public hamon::integral_constant<hamon::size_t, hamon::rank<T>::value + 1>
{};

template <typename T>
struct rank<T[]>
	: public hamon::integral_constant<hamon::size_t, hamon::rank<T>::value + 1>
{};

template <typename T>
HAMON_INLINE_VAR HAMON_CXX11_CONSTEXPR
hamon::size_t rank_v = rank<T>::value;

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_RANK_HPP
