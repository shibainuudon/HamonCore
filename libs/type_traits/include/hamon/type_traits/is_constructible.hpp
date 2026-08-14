/**
 *	@file	is_constructible.hpp
 *
 *	@brief	is_constructible の定義
 */

#ifndef HAMON_TYPE_TRAITS_IS_CONSTRUCTIBLE_HPP
#define HAMON_TYPE_TRAITS_IS_CONSTRUCTIBLE_HPP

#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 21.3.5.4 Type properties[meta.unary.prop]

/**
 *	@brief	型Tのコンストラクタ呼出しが適格か調べる。
 *
 *	@tparam		T		チェックする型
 *	@tparam		Args...	パラメータパック
 *
 *	@require	型TおよびパラメータパックArgs...のすべての型は、完全型であるか、
 *				void(cv修飾を含む)か、要素数不明の配列型でなければならない。
 *
 *	is_constructibleは、T obj(declval<Args>()...);の形式の変数定義が適格であるならば
 *	true_typeから派生し、そうでなければfalse_typeから派生する。
 */
template <typename T, typename... Args>
struct is_constructible
	: public hamon::bool_constant<
#if HAMON_HAS_BUILTIN(__is_constructible) || defined(HAMON_MSVC)
		__is_constructible(T, Args...)
#else
		// TODO
#endif
	>
{};

template <typename T, typename... Args>
HAMON_INLINE_VAR HAMON_CXX11_CONSTEXPR
bool is_constructible_v = is_constructible<T, Args...>::value;

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_IS_CONSTRUCTIBLE_HPP
