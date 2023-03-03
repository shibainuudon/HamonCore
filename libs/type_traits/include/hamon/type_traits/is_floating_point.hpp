/**
 *	@file	is_floating_point.hpp
 *
 *	@brief	is_floating_point の定義
 */

#ifndef HAMON_TYPE_TRAITS_IS_FLOATING_POINT_HPP
#define HAMON_TYPE_TRAITS_IS_FLOATING_POINT_HPP

#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/config.hpp>
#include <type_traits>

namespace hamon
{

/**
 *	@brief	型Tが浮動小数点型か調べる
 *
 *	@tparam		T	チェックする型
 *
 *	is_floating_pointは、型Tが浮動小数点型(cv修飾を許容する)であれば
 *	true_typeから派生し、そうでなければfalse_typeから派生する。
 */
template <typename T>
struct is_floating_point
	: public hamon::bool_constant<
		std::is_floating_point<T>::value
	>
{};

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

template <typename T>
HAMON_INLINE_VAR HAMON_CONSTEXPR
bool is_floating_point_v = is_floating_point<T>::value;

#endif

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_IS_FLOATING_POINT_HPP
