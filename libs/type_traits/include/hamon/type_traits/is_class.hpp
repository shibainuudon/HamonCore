/**
 *	@file	is_class.hpp
 *
 *	@brief	is_class の定義
 */

#ifndef HAMON_TYPE_TRAITS_IS_CLASS_HPP
#define HAMON_TYPE_TRAITS_IS_CLASS_HPP

#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 21.3.5.2 Primary type categories[meta.unary.cat]

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
#if HAMON_HAS_BUILTIN(__is_class) || defined(HAMON_MSVC)
		__is_class(T)
#else
		// TODO
#endif
	>
{};

template <typename T>
HAMON_INLINE_VAR HAMON_CXX11_CONSTEXPR
bool is_class_v = is_class<T>::value;

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_IS_CLASS_HPP
