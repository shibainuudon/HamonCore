/**
 *	@file	is_signed.hpp
 *
 *	@brief	is_signed の定義
 */

#ifndef HAMON_TYPE_TRAITS_IS_SIGNED_HPP
#define HAMON_TYPE_TRAITS_IS_SIGNED_HPP

#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/config.hpp>
#include <type_traits>

namespace hamon
{

/**
 *	@brief	型Tが符号付き算術型か調べる
 *
 *	@tparam		T	チェックする型
 *
 *	is_signedは、型Tが符号付き算術型 (cv修飾を許容する) であるならば
 *	true_typeから派生し、そうでなければfalse_typeから派生する。
 *
 *	符号付き算術型と見なす条件は以下：
 *	is_arithmetic<T>::value == trueの場合、
 *	integral_constant<bool, T(-1) < T(0)>::valueの結果を真偽の結果とする。
 *	そうでなければ偽の結果とする。
 */
template <typename T>
struct is_signed
	: public hamon::bool_constant<
		std::is_signed<T>::value
	>
{};

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

template <typename T>
HAMON_INLINE_VAR HAMON_CONSTEXPR
bool is_signed_v = is_signed<T>::value;

#endif

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_IS_SIGNED_HPP
