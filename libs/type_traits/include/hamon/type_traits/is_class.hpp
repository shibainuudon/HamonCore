/**
 *	@file	is_class.hpp
 *
 *	@brief	is_class の定義
 */

#ifndef HAMON_TYPE_TRAITS_IS_CLASS_HPP
#define HAMON_TYPE_TRAITS_IS_CLASS_HPP

#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/config.hpp>
#include <type_traits>

namespace hamon
{

/**
 *	@brief	型Tがクラス型か調べる
 *
 *	@tparam		T	チェックする型
 *
 *	is_classは、型Tがクラス型であればtrue_typeから派生し、
 *	そうでなければfalse_typeから派生する。
 *
 *	型Tがunion、enum、enum classの場合、is_classはfalse_typeから派生する。
 */
template <typename T>
struct is_class
	: public hamon::bool_constant<
		std::is_class<T>::value
	>
{};

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

template <typename T>
HAMON_INLINE_VAR HAMON_CONSTEXPR
bool is_class_v = is_class<T>::value;

#endif

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_IS_CLASS_HPP
