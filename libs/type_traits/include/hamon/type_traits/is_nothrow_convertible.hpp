/**
 *	@file	is_nothrow_convertible.hpp
 *
 *	@brief	is_nothrow_convertible
 */

#ifndef HAMON_TYPE_TRAITS_IS_NOTHROW_CONVERTIBLE_HPP
#define HAMON_TYPE_TRAITS_IS_NOTHROW_CONVERTIBLE_HPP

#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/detail/is_nothrow_convertible_impl.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 21.3.7 Relationships between types[meta.rel]

/**
 *	@brief		型Fromから型Toに例外を投げずに暗黙的に変換可能か調べる。
 *
 *	@tparam		From	変換元の型
 *	@tparam		To		変換先の型
 *
 *	@require	型Fromと型Toは完全型であるか、void(cv修飾を含む)か、要素数不明の配列型でなければならない
 *
 *	is_nothrow_convertibleは、型Fromから型Toに例外を投げずに暗黙的に変換可能であればtrue_typeから派生し、
 *	そうでなければfalse_typeから派生する。
 *
 *	return文による型変換、および非explicitなコンストラクタによる型変換は、暗黙的に変換可能であるとみなされる。
 *	explicitなコンストラクタによる明示的な型変換は、暗黙的に変換可能であるとは見なされない。
 */
template <typename From, typename To>
struct is_nothrow_convertible
	: public hamon::bool_constant<
#if HAMON_HAS_BUILTIN(__is_nothrow_convertible)
		__is_nothrow_convertible(From, To)
#else
		hamon::detail::is_nothrow_convertible_impl<From, To>::value
#endif
	>
{};

template <typename From, typename To>
HAMON_INLINE_VAR HAMON_CXX11_CONSTEXPR
bool is_nothrow_convertible_v = is_nothrow_convertible<From, To>::value;

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_IS_NOTHROW_CONVERTIBLE_HPP
