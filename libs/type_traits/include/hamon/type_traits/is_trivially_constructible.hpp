/**
 *	@file	is_trivially_constructible.hpp
 *
 *	@brief	is_trivially_constructible の定義
 */

#ifndef HAMON_TYPE_TRAITS_IS_TRIVIALLY_CONSTRUCTIBLE_HPP
#define HAMON_TYPE_TRAITS_IS_TRIVIALLY_CONSTRUCTIBLE_HPP

#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/config.hpp>
#include <type_traits>

namespace hamon
{

/**
 *	@brief	型Tがトリビアルに構築可能か調べる。
 *
 *	@tparam		T		チェックする型
 *	@tparam		Args...	パラメータパック
 *
 *	@require	型TおよびパラメータパックArgs...のすべての型は、完全型であるか、
 *				void(cv修飾を含む)か、要素数不明の配列型でなければならない。
 *
 *	is_trivially_constructibleは、T obj(std::declval<Args>()...);の形式の変数定義がトリビアルに可能であるならば
 *	true_typeから派生し、そうでなければfalse_typeから派生する。
 *	このとき、std::declvalはトリビアルであるとみなされる。
 */
template <typename T, typename... Args>
struct is_trivially_constructible
	: public hamon::bool_constant<
		std::is_trivially_constructible<T, Args...>::value
	>
{};

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

template <typename T, typename... Args>
HAMON_INLINE_VAR HAMON_CONSTEXPR
bool is_trivially_constructible_v = is_trivially_constructible<T, Args...>::value;

#endif

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_IS_TRIVIALLY_CONSTRUCTIBLE_HPP
