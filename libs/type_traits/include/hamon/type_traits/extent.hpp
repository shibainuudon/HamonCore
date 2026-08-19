/**
 *	@file	extent.hpp
 *
 *	@brief	extent の定義
 */

#ifndef HAMON_TYPE_TRAITS_EXTENT_HPP
#define HAMON_TYPE_TRAITS_EXTENT_HPP

#include <hamon/type_traits/integral_constant.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 21.3.6 Type property queries[meta.unary.prop.query]

/**
 *	@brief	配列型のI番目の次元の要素数を取得する。
 *
 *	@tparam	T
 *	@tparam	I
 *
 *	型Tが配列型であり、配列の次元数がIより大きい場合、
 *	I次元目の要素数をメンバ定数valueとして定義する。
 *	型Tが配列型ではない、もしくは配列の次元数がI以下の場合、
 *	値0をメンバ定数valueとして定義する。
 */
template <typename T, unsigned int I = 0>
struct extent
	: public hamon::integral_constant<hamon::size_t, 0>
{};

template <typename T, hamon::size_t N>
struct extent<T[N], 0>
	: public hamon::integral_constant<hamon::size_t, N>
{};

template <typename T, hamon::size_t N, unsigned int I>
struct extent<T[N], I>
	: public hamon::integral_constant<hamon::size_t, extent<T, I - 1>::value>
{};

template <typename T, unsigned int I>
struct extent<T[], I>
	: public hamon::integral_constant<hamon::size_t, extent<T, I - 1>::value>
{};

template <typename T, unsigned int I = 0>
HAMON_INLINE_VAR HAMON_CXX11_CONSTEXPR
hamon::size_t extent_v = extent<T, I>::value;

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_EXTENT_HPP
