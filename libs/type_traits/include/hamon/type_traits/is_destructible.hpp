/**
 *	@file	is_destructible.hpp
 *
 *	@brief	is_destructible の定義
 */

#ifndef HAMON_TYPE_TRAITS_IS_DESTRUCTIBLE_HPP
#define HAMON_TYPE_TRAITS_IS_DESTRUCTIBLE_HPP

#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/config.hpp>
#include <type_traits>

namespace hamon
{

/**
 *	@brief	型Tが破棄可能か調べる
 *
 *	@tparam		T	チェックする型
 *
 *	@require	型Tは完全型であるか、void(cv修飾を含む)か、要素数不明の配列型でなければならない
 *
 *	is_destructibleは、型Tが破棄可能であるならば
 *	true_typeから派生し、そうでなければfalse_typeから派生する。
 *
 *	実行時に評価されない文脈で、オブジェクト型Tに対する式 declval<T&>().~T() が
 *	有効であれば破棄可能、そうでなければ破棄できないと判断される。
 *	以下、オブジェクト型に含まれない型の場合の判断について記載する：
 *	・Tがvoidの場合は破棄できない
 *	・Tが参照型の場合は破棄可能
 *	・Tが関数型の場合は破棄できない
 */
template <typename T>
struct is_destructible
	: public hamon::bool_constant<
		std::is_destructible<T>::value
	>
{};

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

template <typename T>
HAMON_INLINE_VAR HAMON_CONSTEXPR
bool is_destructible_v = is_destructible<T>::value;

#endif

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_IS_DESTRUCTIBLE_HPP
