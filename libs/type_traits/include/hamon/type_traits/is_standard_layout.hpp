/**
 *	@file	is_standard_layout.hpp
 *
 *	@brief	is_standard_layout の定義
 */

#ifndef HAMON_TYPE_TRAITS_IS_STANDARD_LAYOUT_HPP
#define HAMON_TYPE_TRAITS_IS_STANDARD_LAYOUT_HPP

#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/config.hpp>
#include <type_traits>

namespace hamon
{

/**
 *	@brief	型Tがスタンダードレイアウト型か調べる。
 *
 *	@tparam		T
 *
 *	@require	型remove_all_extents<T>::typeは完全型であるか、void(cv修飾を含む)でなければならない。
 *
 *	is_standard_layoutは、型Tがスタンダードレイアウト型であるならば
 *	true_typeから派生し、そうでなければfalse_typeから派生する。
 *
 *	スタンダードレイアウト型は、以下の全てを満たす型を指す：
 *	・非スタンダードレイアウト型の非静的データメンバもしくは参照を持たない
 *	・仮想関数を持たず、仮想基本クラスを持たない
 *	・非スタンダードレイアウト型の基本クラスを持たない
 *	・最派生クラスに非静的データメンバを持つ場合、基底クラスに非静的データメンバを持たない
 *	・最初の非静的データメンバと同じ基本クラスを持たない
 */
template <typename T>
struct is_standard_layout
	: public hamon::bool_constant<
		std::is_standard_layout<T>::value
	>
{};

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

template <typename T>
HAMON_INLINE_VAR HAMON_CONSTEXPR
bool is_standard_layout_v = is_standard_layout<T>::value;

#endif

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_IS_STANDARD_LAYOUT_HPP
