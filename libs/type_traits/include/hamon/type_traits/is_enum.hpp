/**
 *	@file	is_enum.hpp
 *
 *	@brief	is_enum の定義
 */

#ifndef HAMON_TYPE_TRAITS_IS_ENUM_HPP
#define HAMON_TYPE_TRAITS_IS_ENUM_HPP

#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/config.hpp>
#include <type_traits>

namespace hamon
{

/**
 *	@brief	型Tが列挙型か調べる
 *
 *	@tparam		T	チェックする型
 *
 *	@require	型Tが非共用体のクラスである場合、その型は完全型でなければならない
 *
 *	is_enumは、型Tが列挙型であるならばtrue_typeから派生し、
 *	そうでなければfalse_typeから派生する。
 */
template <typename T>
struct is_enum
	: public hamon::bool_constant<
		std::is_enum<T>::value
	>
{};

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

template <typename T>
HAMON_INLINE_VAR HAMON_CONSTEXPR
bool is_enum_v = is_enum<T>::value;

#endif

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_IS_ENUM_HPP
