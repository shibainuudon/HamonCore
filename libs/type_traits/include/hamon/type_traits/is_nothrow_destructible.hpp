/**
 *	@file	is_nothrow_destructible.hpp
 *
 *	@brief	is_nothrow_destructible の定義
 */

#ifndef HAMON_TYPE_TRAITS_IS_NOTHROW_DESTRUCTIBLE_HPP
#define HAMON_TYPE_TRAITS_IS_NOTHROW_DESTRUCTIBLE_HPP

#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/detail/is_nothrow_destructible_impl.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 21.3.5.4 Type properties[meta.unary.prop]

/**
 *	@brief	型Tが破棄でき、かつそのデストラクタが例外を投げないか調べる
 *
 *	@tparam		T	チェックする型
 *
 *	@require	型Tは完全型であるか、void(cv修飾を含む)か、要素数不明の配列型でなければならない
 *
 *	is_nothrow_destructibleは、型Tが例外を投げない保証のもとに破棄可能であるならば
 *	true_typeから派生し、そうでなければfalse_typeから派生する。
 */
template <typename T>
struct is_nothrow_destructible
	: public hamon::bool_constant<
#if HAMON_HAS_BUILTIN(__is_nothrow_destructible) || defined(HAMON_MSVC)
		__is_nothrow_destructible(T)
#else
		hamon::detail::is_nothrow_destructible_impl<T>::value
#endif
	>
{};

template <typename T>
HAMON_INLINE_VAR HAMON_CXX11_CONSTEXPR
bool is_nothrow_destructible_v = is_nothrow_destructible<T>::value;

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_IS_NOTHROW_DESTRUCTIBLE_HPP
