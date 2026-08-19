/**
 *	@file	enable_if.hpp
 *
 *	@brief	enable_if の定義
 */

#ifndef HAMON_TYPE_TRAITS_ENABLE_IF_HPP
#define HAMON_TYPE_TRAITS_ENABLE_IF_HPP

namespace hamon
{

// 21.3.8.7 Other transformations[meta.trans.other]

/**
 *	@brief	コンパイル時条件式が真の場合のみ有効な型。
 *
 *	@tparam	Condition	条件式
 *	@tparam	T			条件式が真の場合の型
 *
 *	enable_ifは、Conditionがtrueの場合のみ、型Tをメンバ型typeとして定義する。
 *	そうでなければenable_ifは、メンバ型typeを持たない。
 *
 *	enable_ifは、SFINAEと組み合わせて使用する。
 *	関数のパラメータ、戻り値型、デフォルトテンプレートパラメータ等のいずれかで
 *	enable_ifのメンバ型typeを使用することにより、テンプレートの置き換え失敗が発生し、
 *	SFINAEによってその関数がオーバーロード解決の候補から除外される。
 */
template <bool B, typename T = void>
struct enable_if
{
};

template <typename T>
struct enable_if<true, T>
{
	using type = T;
};

template <bool B, typename T = void>
using enable_if_t = typename enable_if<B, T>::type;

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_ENABLE_IF_HPP
