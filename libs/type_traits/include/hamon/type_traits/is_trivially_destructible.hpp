/**
 *	@file	is_trivially_destructible.hpp
 *
 *	@brief	is_trivially_destructible の定義
 */

#ifndef HAMON_TYPE_TRAITS_IS_TRIVIALLY_DESTRUCTIBLE_HPP
#define HAMON_TYPE_TRAITS_IS_TRIVIALLY_DESTRUCTIBLE_HPP

#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/is_destructible.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 21.3.5.4 Type properties[meta.unary.prop]

/**
 *	@brief	型Tがトリビアルに破棄可能か調べる
 *
 *	@tparam		T	チェックする型
 *
 *	@require	型Tは完全型であるか、void(cv修飾を含む)か、要素数不明の配列型でなければならない
 *
 *	is_trivially_destructibleは、型Tがトリビアルに破棄可能であるならば
 *	true_typeから派生し、そうでなければfalse_typeから派生する。
 *	「トリビアルに破棄可能」とは、ユーザー定義されないデストラクタを持っているということを意味する。
 */
template <typename T>
struct is_trivially_destructible
	: public hamon::bool_constant<
#if HAMON_HAS_BUILTIN(__is_trivially_destructible) || defined(HAMON_MSVC)
		__is_trivially_destructible(T)
#elif HAMON_HAS_BUILTIN(__has_trivial_destructor)
		hamon::is_destructible_v<T> && __has_trivial_destructor(T)
#else
		// TODO
#endif
	>
{};

template <typename T>
HAMON_INLINE_VAR HAMON_CXX11_CONSTEXPR
bool is_trivially_destructible_v = is_trivially_destructible<T>::value;

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_IS_TRIVIALLY_DESTRUCTIBLE_HPP
