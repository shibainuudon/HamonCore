/**
 *	@file	is_void.hpp
 *
 *	@brief	is_void の定義
 */

#ifndef HAMON_TYPE_TRAITS_IS_VOID_HPP
#define HAMON_TYPE_TRAITS_IS_VOID_HPP

#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/config.hpp>
#include <type_traits>

namespace hamon
{

/**
 *	@brief	型Tがvoidかを調べる。
 *
 *	@tparam		T	チェックする型
 *
 *	is_voidは、型Tがvoid(cv修飾を許容する)であれば
 *	true_typeから派生し、そうでなければfalse_typeから派生する。
 */
template <typename T>
struct is_void
	: public hamon::bool_constant<
		std::is_void<T>::value
	>
{};

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

template <typename T>
HAMON_INLINE_VAR HAMON_CONSTEXPR
bool is_void_v = is_void<T>::value;

#endif

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_IS_VOID_HPP
