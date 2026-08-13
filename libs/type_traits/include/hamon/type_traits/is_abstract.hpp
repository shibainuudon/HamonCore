/**
 *	@file	is_abstract.hpp
 *
 *	@brief	is_abstract の定義
 */

#ifndef HAMON_TYPE_TRAITS_IS_ABSTRACT_HPP
#define HAMON_TYPE_TRAITS_IS_ABSTRACT_HPP

#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 21.3.5.4 Type properties[meta.unary.prop]

/**
 *	@brief	型Tが抽象クラスか調べる
 *
 *	@tparam		T	チェックする型
 *
 *	@require	型Tが非共用体のクラスである場合、その型は完全型でなければならない。
 *
 *	is_abstractは、型Tが抽象クラス (cv修飾を許容する) であればtrue_typeから派生し、
 *	そうでなければfalse_typeから派生する。
 *
 *	抽象クラスとは、少なくとも一つの純粋仮想関数を持つクラスである。
 */
template <typename T>
struct is_abstract
	: public hamon::bool_constant<
#if HAMON_HAS_BUILTIN(__is_abstract) || defined(HAMON_MSVC)
		__is_abstract(T)
#else
		// TODO
#endif
	>
{};

template <typename T>
HAMON_INLINE_VAR HAMON_CXX11_CONSTEXPR
bool is_abstract_v = is_abstract<T>::value;

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_IS_ABSTRACT_HPP
