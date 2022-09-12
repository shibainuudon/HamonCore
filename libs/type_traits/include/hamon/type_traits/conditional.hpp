/**
 *	@file	conditional.hpp
 *
 *	@brief	conditional の定義
 */

#ifndef HAMON_TYPE_TRAITS_CONDITIONAL_HPP
#define HAMON_TYPE_TRAITS_CONDITIONAL_HPP

#include <type_traits>

namespace hamon
{

/**
 *	@brief		コンパイル時条件式
 *
 *	@tparam		B	条件式
 *	@tparam		T	条件式がtrueの時の型
 *	@tparam		F	条件式がfalseの時の型
 *
 *	conditionalは、条件式Bがtrueであれば型Tを、そうでなければ型Fを、メンバ型typeとして定義する。
 */
using std::conditional;

/**
 *	@brief	conditionalのエイリアステンプレート
 */
template <bool B, typename T, typename F>
using conditional_t = typename conditional<B, T, F>::type;

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_CONDITIONAL_HPP
