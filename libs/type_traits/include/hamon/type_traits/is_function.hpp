/**
 *	@file	is_function.hpp
 *
 *	@brief	is_function の定義
 */

#ifndef HAMON_TYPE_TRAITS_IS_FUNCTION_HPP
#define HAMON_TYPE_TRAITS_IS_FUNCTION_HPP

#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/config.hpp>
#include <type_traits>

namespace hamon
{

/**
 *	@brief	型Tが関数型か調べる
 *
 *	@tparam		T	チェックする型
 *
 *	is_functionは、型Tが関数型であるならば
 *	true_typeから派生し、そうでなければfalse_typeから派生する。
 */
template <typename T>
struct is_function
	: public hamon::bool_constant<
		std::is_function<T>::value
	>
{};

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

template <typename T>
HAMON_INLINE_VAR HAMON_CONSTEXPR
bool is_function_v = is_function<T>::value;

#endif

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_IS_FUNCTION_HPP
