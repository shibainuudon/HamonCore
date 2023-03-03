/**
 *	@file	is_arithmetic.hpp
 *
 *	@brief	is_arithmetic の定義
 */

#ifndef HAMON_TYPE_TRAITS_IS_ARITHMETIC_HPP
#define HAMON_TYPE_TRAITS_IS_ARITHMETIC_HPP

#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/config.hpp>
#include <type_traits>

namespace hamon
{

/**
 *	@brief	型Tが算術型か調べる
 *
 *	@tparam		T	チェックする型
 *
 *	is_arithmeticは、型Tが算術型であればtrue_typeから派生し、
 *	そうでなければfalse_typeから派生する。
 *	算術型は、整数型、浮動小数点型、およびそれらのcv修飾を含む。
 */
template <typename T>
struct is_arithmetic
	: public hamon::bool_constant<
		std::is_arithmetic<T>::value
	>
{};

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

template <typename T>
HAMON_INLINE_VAR HAMON_CONSTEXPR
bool is_arithmetic_v = is_arithmetic<T>::value;

#endif

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_IS_ARITHMETIC_HPP
