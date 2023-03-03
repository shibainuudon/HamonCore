/**
 *	@file	is_integral.hpp
 *
 *	@brief	is_integral の定義
 */

#ifndef HAMON_TYPE_TRAITS_IS_INTEGRAL_HPP
#define HAMON_TYPE_TRAITS_IS_INTEGRAL_HPP

#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/config.hpp>
#include <type_traits>

namespace hamon
{

/**
 *	@brief	型Tが整数型かを調べる
 *
 *	@tparam		T	チェックする型
 *
 *	is_integralは、型Tが整数型(cv修飾も許容される)であるならば
 *	true_typeから派生し、そうでなければfalse_typeから派生する。
 *
 *	以下のような型が、整数型として判定される：
 *	・bool
 *	・char
 *	・char16_t
 *	・char32_t
 *	・wchar_t
 *	・short
 *	・int
 *	・long
 *	・long long
 *	enumは整数型とは判定されない。
 */
template <typename T>
struct is_integral
	: public hamon::bool_constant<
		std::is_integral<T>::value
	>
{};

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

template <typename T>
HAMON_INLINE_VAR HAMON_CONSTEXPR
bool is_integral_v = is_integral<T>::value;

#endif

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_IS_INTEGRAL_HPP
