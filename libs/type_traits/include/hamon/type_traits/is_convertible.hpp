/**
 *	@file	is_convertible.hpp
 *
 *	@brief	is_convertible の定義
 */

#ifndef HAMON_TYPE_TRAITS_IS_CONVERTIBLE_HPP
#define HAMON_TYPE_TRAITS_IS_CONVERTIBLE_HPP

#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/config.hpp>
#include <type_traits>

namespace hamon
{

/**
 *	@brief	型Fromから型Toに変換可能か調べる。
 *
 *	@tparam		From	変換元の型
 *	@tparam		To		変換先の型
 *
 *	@require	型Fromと型Toは完全型であるか、void(cv修飾を含む)か、要素数不明の配列型でなければならない
 *
 *	is_convertibleは、型Fromから型Toに変換可能であればtrue_typeから派生し、
 *	そうでなければfalse_typeから派生する。
 */
template <typename From, typename To>
struct is_convertible
	: public hamon::bool_constant<
		std::is_convertible<From, To>::value
	>
{};

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

template <typename From, typename To>
HAMON_INLINE_VAR HAMON_CONSTEXPR
bool is_convertible_v = is_convertible<From, To>::value;

#endif

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_IS_CONVERTIBLE_HPP
