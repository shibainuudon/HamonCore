/**
 *	@file	is_empty.hpp
 *
 *	@brief	is_empty の定義
 */

#ifndef HAMON_TYPE_TRAITS_IS_EMPTY_HPP
#define HAMON_TYPE_TRAITS_IS_EMPTY_HPP

#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 21.3.5.4 Type properties[meta.unary.prop]

/**
 *	@brief	型Tが空のクラスか調べる
 *
 *	@tparam		T	チェックする型
 *
 *	@require	型Tが非共用体のクラスである場合、その型は完全型でなければならない
 *
 *	is_emptyは、型Tが空のクラスであるならばtrue_typeから派生し、
 *	そうでなければfalse_typeから派生する。
 *	空のクラスであるとは、以下の全ての条件を満たす型である（cv修飾を含む）：
 *	・クラス型である
 *	・共用型でない
 *	・長さ0のビットフィールド以外に、非静的データメンバを持たない
 *	・仮想メンバ関数を持たない
 *	・仮想基底クラスを持たない
 *	・空のクラスでない基底クラスを持たない
 */
template <typename T>
struct is_empty
	: public hamon::bool_constant<
#if HAMON_HAS_BUILTIN(__is_empty) || defined(HAMON_MSVC)
		__is_empty(T)
#else
		// TODO
#endif
	>
{};

template <typename T>
HAMON_INLINE_VAR HAMON_CXX11_CONSTEXPR
bool is_empty_v = is_empty<T>::value;

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_IS_EMPTY_HPP
