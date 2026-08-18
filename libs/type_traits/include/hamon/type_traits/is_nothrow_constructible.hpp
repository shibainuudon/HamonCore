/**
 *	@file	is_nothrow_constructible.hpp
 *
 *	@brief	is_nothrow_constructible の定義
 */

#ifndef HAMON_TYPE_TRAITS_IS_NOTHROW_CONSTRUCTIBLE_HPP
#define HAMON_TYPE_TRAITS_IS_NOTHROW_CONSTRUCTIBLE_HPP

#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/detail/is_nothrow_constructible_impl.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 21.3.5.4 Type properties[meta.unary.prop]

/**
 *	@brief	型Tのコンストラクタ呼出しが適格であり、かつそのコンストラクタが例外を投げないか調べる
 *
 *	@tparam		T		チェックする型
 *	@tparam		Args...	パラメータパック
 *
 *	@require	型TおよびパラメータパックArgs...のすべての型は完全型であるか、
 *				void(cv修飾を含む)か、要素数不明の配列型でなければならない。
 *
 *	is_nothrow_constructibleは、型Tが例外を投げない保証のもとに構築可能であるならば
 *	true_typeから派生し、そうでなければfalse_typeから派生する。
 *	is_constructible<T, Args...>::value == trueかつ、いかなる例外も投げないならば、
 *	例外を投げない構築が可能であると判断される。
 */
template <typename T, typename... Args>
struct is_nothrow_constructible
	: public hamon::bool_constant<
#if HAMON_HAS_BUILTIN(__is_nothrow_constructible) && !defined(HAMON_MSVC)	// MSVCの__is_nothrow_constructibleは挙動がおかしいので使わない
		__is_nothrow_constructible(T, Args...)
#else
		hamon::detail::is_nothrow_constructible_impl<T, Args...>::value
#endif
	>
{};

template <typename T, typename... Args>
HAMON_INLINE_VAR HAMON_CXX11_CONSTEXPR
bool is_nothrow_constructible_v = is_nothrow_constructible<T, Args...>::value;

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_IS_NOTHROW_CONSTRUCTIBLE_HPP
