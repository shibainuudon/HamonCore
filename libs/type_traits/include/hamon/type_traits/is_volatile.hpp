/**
 *	@file	is_volatile.hpp
 *
 *	@brief	is_volatile の定義
 */

#ifndef HAMON_TYPE_TRAITS_IS_VOLATILE_HPP
#define HAMON_TYPE_TRAITS_IS_VOLATILE_HPP

#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 21.3.5.4 Type properties[meta.unary.prop]

/**
 *	@brief	型Tがvolatile修飾型かを調べる。
 *
 *	@tparam		T	チェックする型
 *
 *	is_volatileは、型Tがvolatile修飾型であるならば
 *	true_typeから派生し、そうでなければfalse_typeから派生する。
 *	volatile修飾型は、volatile および const volatile を含む。
 *
 *	参照型は、volatile修飾型でない。
 */
template <typename T>
struct is_volatile : public hamon::false_type{};

template <typename T>
struct is_volatile<T volatile> : public hamon::true_type{};

template <typename T>
HAMON_INLINE_VAR HAMON_CXX11_CONSTEXPR
bool is_volatile_v = is_volatile<T>::value;

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_IS_VOLATILE_HPP
