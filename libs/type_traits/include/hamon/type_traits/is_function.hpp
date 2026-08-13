/**
 *	@file	is_function.hpp
 *
 *	@brief	is_function の定義
 */

#ifndef HAMON_TYPE_TRAITS_IS_FUNCTION_HPP
#define HAMON_TYPE_TRAITS_IS_FUNCTION_HPP

#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/is_const.hpp>
#include <hamon/type_traits/is_reference.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 21.3.5.2 Primary type categories[meta.unary.cat]

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4180)	// 関数型へ適用された修飾子は無効なため、無視されます。

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
		// const修飾できないのは関数型と参照型のみ
		!hamon::is_const_v<T const> &&
		!hamon::is_reference_v<T>
	>
{};

HAMON_WARNING_POP()

template <typename T>
HAMON_INLINE_VAR HAMON_CXX11_CONSTEXPR
bool is_function_v = is_function<T>::value;

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_IS_FUNCTION_HPP
