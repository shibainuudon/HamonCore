/**
 *	@file	is_polymorphic.hpp
 *
 *	@brief	is_polymorphic の定義
 */

#ifndef HAMON_TYPE_TRAITS_IS_POLYMORPHIC_HPP
#define HAMON_TYPE_TRAITS_IS_POLYMORPHIC_HPP

#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 21.3.5.4 Type properties[meta.unary.prop]

/**
 *	@brief	型Tが多相的なクラスか調べる
 *
 *	@tparam		T	チェックする型
 *
 *	@require	型Tが非共用体のクラスである場合、その型は完全型でなければならない。
 *
 *	is_polymorphicは、型Tが多相的クラス (cv修飾を許容する) であるならば
 *	true_typeから派生し、そうでなければfalse_typeから派生する。
 *	多相的クラスは、少なくとも一つの仮想関数を持つクラスである。
 */
template <typename T>
struct is_polymorphic
	: public hamon::bool_constant<
#if HAMON_HAS_BUILTIN(__is_polymorphic) || defined(HAMON_MSVC)
		__is_polymorphic(T)
#else
		// TODO
#endif
	>
{};

template <typename T>
HAMON_INLINE_VAR HAMON_CXX11_CONSTEXPR
bool is_polymorphic_v = is_polymorphic<T>::value;

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_IS_POLYMORPHIC_HPP
