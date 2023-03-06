/**
 *	@file	is_default_constructible.hpp
 *
 *	@brief	is_default_constructible の定義
 */

#ifndef HAMON_TYPE_TRAITS_IS_DEFAULT_CONSTRUCTIBLE_HPP
#define HAMON_TYPE_TRAITS_IS_DEFAULT_CONSTRUCTIBLE_HPP

#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/config.hpp>
#include <type_traits>

namespace hamon
{

/**
 *	@brief	型Tがデフォルト構築可能か調べる。
 *
 *	@tparam		T		チェックする型
 *
 *	@require	型Tは完全型であるか、void(cv修飾を含む)か、要素数不明の配列型でなければならない
 *
 *	is_default_constructibleは、型Tがデフォルトコンストラクト可能であるならば
 *	true_typeから派生し、そうでなければfalse_typeから派生する。
 *	is_constructible<T>::value == trueの時に、デフォルト構築可能であると判断される。
 */
template <typename T>
struct is_default_constructible
	: public hamon::bool_constant<
		std::is_default_constructible<T>::value
	>
{};

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

template <typename T>
HAMON_INLINE_VAR HAMON_CONSTEXPR
bool is_default_constructible_v = is_default_constructible<T>::value;

#endif

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_IS_DEFAULT_CONSTRUCTIBLE_HPP
