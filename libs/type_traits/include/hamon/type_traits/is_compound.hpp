/**
 *	@file	is_compound.hpp
 *
 *	@brief	is_compound の定義
 */

#ifndef HAMON_TYPE_TRAITS_IS_COMPOUND_HPP
#define HAMON_TYPE_TRAITS_IS_COMPOUND_HPP

#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/config.hpp>
#include <type_traits>

namespace hamon
{

/**
 *	@brief	型Tが複合型 (Compound types) か調べる
 *
 *	@tparam		T	チェックする型
 *
 *	is_compoundは、型Tが複合型であればtrue_typeから派生し、
 *	そうでなければfalse_typeから派生する。
 *	複合型は、配列型、関数型、ポインタ型、参照型、クラス型、
 *	共用型、列挙型、メンバポインタ型、およびそれらのcv修飾を含む。
 *
 *	複合型は、すべての型の集合から、単純型の集合を除いたものに等しい。
 */
template <typename T>
struct is_compound
	: public hamon::bool_constant<
		std::is_compound<T>::value
	>
{};

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

template <typename T>
HAMON_INLINE_VAR HAMON_CONSTEXPR
bool is_compound_v = is_compound<T>::value;

#endif

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_IS_COMPOUND_HPP
