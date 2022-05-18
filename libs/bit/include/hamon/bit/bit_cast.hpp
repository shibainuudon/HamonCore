﻿/**
 *	@file	bit_cast.hpp
 *
 *	@brief	bit_cast 関数テンプレートを定義
 */

#ifndef HAMON_BIT_BIT_CAST_HPP
#define HAMON_BIT_BIT_CAST_HPP

#include <hamon/bit/config.hpp>

#if defined(HAMON_HAS_CXX_LIB_BIT_CAST)

// bit_cast が constexpr であることを定義
#define	HAMON_HAS_CONSTEXPR_BIT_CAST

#include <bit>

namespace hamon
{

using std::bit_cast;

}	// namespace hamon

#else

#include <type_traits>
#include <cstring>	// memcpy

namespace hamon
{

/**
 *	@brief	ビットレベルの再解釈キャスト
 *
 *	@tparam	To		キャスト先の型
 *	@tparam	From	キャスト元の型
 *
 *	@param	src		キャストする値
 *
 *	@return	srcのビット値を維持したまま型Toの値を返す
 *
 *	以下の条件のいずれかを満たさない場合、この関数はオーバーロード解決の候補から除外される：
 *	・sizeof(To) == sizeof(From)であること
 *	・is_trivially_copyable_v<To> == trueであること
 *	・is_trivially_copyable_v<From> == trueであること
 *
 *  C++20でstd::bit_castが使える場合そちらを使い、
 *	型ToとFrom、およびその全てのサブオブジェクトが以下の条件を全て満たす場合、constexpr関数として評価される：
 *	・is_union_v<T> == false
 *	・is_pointer_v<T> == false
 *	・is_member_pointer_v<T> == false
 *	・is_volatile_v<T> == false
 *	・Tが参照の非静的メンバ変数を持たないこと
 * 
 *  std::bit_castが使えない場合、constexprにすることはできない
 */
template <
	typename To,
	typename From,
	typename = typename std::enable_if<
		sizeof(To) == sizeof(From) &&
		std::is_trivially_copyable<To>::value &&
		std::is_trivially_copyable<From>::value
	>::type
>
inline To bit_cast(From const& src) HAMON_NOEXCEPT
{
	To dst;
	std::memcpy(&dst, &src, sizeof(To));
	return dst;
}

}	// namespace hamon

#endif

#endif // HAMON_BIT_BIT_CAST_HPP
