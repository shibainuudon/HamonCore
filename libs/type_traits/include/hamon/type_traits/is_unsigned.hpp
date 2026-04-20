/**
 *	@file	is_unsigned.hpp
 *
 *	@brief	is_unsigned の定義
 */

#ifndef HAMON_TYPE_TRAITS_IS_UNSIGNED_HPP
#define HAMON_TYPE_TRAITS_IS_UNSIGNED_HPP

#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/is_arithmetic.hpp>
#include <hamon/type_traits/remove_cv.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

template <typename T, bool = hamon::is_arithmetic<T>::value>
struct is_unsigned_impl
	: public hamon::false_type {};

template <typename T>
struct is_unsigned_impl<T, true>
	: public hamon::bool_constant<T(0) < T(-1)> {};

}	// namespace detail

/**
 *	@brief	型Tが符号なし算術型かを調べる。
 *
 *	@tparam		T	チェックする型
 *
 *	is_unsignedは、型Tが符号なし算術型(cv修飾を許容する) であるならば
 *	true_typeから派生し、そうでなければfalse_typeから派生する。
 *
 *	符号なし算術型と見なす条件は以下：
 *	is_arithmetic<T>::value == trueの場合、
 *	integral_constant<bool, T(0) < T(-1)>::valueの結果を真偽の結果とする。
 *	そうでなければ偽の結果とする。
 */
template <typename T>
struct is_unsigned
	: public hamon::detail::is_unsigned_impl<hamon::remove_cv_t<T>> {};

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

template <typename T>
HAMON_INLINE_VAR HAMON_CONSTEXPR
bool is_unsigned_v = is_unsigned<T>::value;

#endif

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_IS_UNSIGNED_HPP
