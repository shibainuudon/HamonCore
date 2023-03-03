/**
 *	@file	is_const.hpp
 *
 *	@brief	is_const の定義
 */

#ifndef HAMON_TYPE_TRAITS_IS_CONST_HPP
#define HAMON_TYPE_TRAITS_IS_CONST_HPP

#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/config.hpp>
#include <type_traits>

namespace hamon
{

/**
 *	@brief	型Tがconst修飾型か調べる。
 *
 *	@tparam		T	チェックする型
 *
 *	is_constは、型Tがconst修飾型であればtrue_typeから派生し、
 *	そうでなければfalse_typeから派生する。
 *	const修飾型は、const および const volatile を含む。
 *	参照型は、const修飾型でない。
 */
template <typename T>
struct is_const
	: public hamon::bool_constant<
		std::is_const<T>::value
	>
{};

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

template <typename T>
HAMON_INLINE_VAR HAMON_CONSTEXPR
bool is_const_v = is_const<T>::value;

#endif

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_IS_CONST_HPP
