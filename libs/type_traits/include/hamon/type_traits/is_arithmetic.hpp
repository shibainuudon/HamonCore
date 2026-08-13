/**
 *	@file	is_arithmetic.hpp
 *
 *	@brief	is_arithmetic の定義
 */

#ifndef HAMON_TYPE_TRAITS_IS_ARITHMETIC_HPP
#define HAMON_TYPE_TRAITS_IS_ARITHMETIC_HPP

#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/is_integral.hpp>
#include <hamon/type_traits/is_floating_point.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 21.3.5.3 Composite type traits

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
		// 6.9.3 Fundamental types[basic.fundamental]/14
		// Integral and floating-point types are collectively termed arithmetic types.
		hamon::is_integral_v<T> ||
		hamon::is_floating_point_v<T>
	>
{};

template <typename T>
HAMON_INLINE_VAR HAMON_CXX11_CONSTEXPR
bool is_arithmetic_v = is_arithmetic<T>::value;

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_IS_ARITHMETIC_HPP
