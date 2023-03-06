/**
 *	@file	is_nothrow_destructible.hpp
 *
 *	@brief	is_nothrow_destructible の定義
 */

#ifndef HAMON_TYPE_TRAITS_IS_NOTHROW_DESTRUCTIBLE_HPP
#define HAMON_TYPE_TRAITS_IS_NOTHROW_DESTRUCTIBLE_HPP

#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/config.hpp>
#include <type_traits>

namespace hamon
{

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
		std::is_nothrow_destructible<T>::value
	>
{};

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

template <typename T>
HAMON_INLINE_VAR HAMON_CONSTEXPR
bool is_nothrow_destructible_v = is_nothrow_destructible<T>::value;

#endif

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_IS_NOTHROW_DESTRUCTIBLE_HPP
