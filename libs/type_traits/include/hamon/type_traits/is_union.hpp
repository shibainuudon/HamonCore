/**
 *	@file	is_union.hpp
 *
 *	@brief	is_union の定義
 */

#ifndef HAMON_TYPE_TRAITS_IS_UNION_HPP
#define HAMON_TYPE_TRAITS_IS_UNION_HPP

#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 21.3.5.2 Primary type categories[meta.unary.cat]

/**
 *	@brief	型Tが共用型かを調べる。
 *
 *	@tparam		T	チェックする型
 *
 *	is_unionは、型Tが共用型であるならば
 *	true_typeから派生し、そうでなければfalse_typeから派生する。
 */
template <typename T>
struct is_union
	: public hamon::bool_constant<
#if HAMON_HAS_BUILTIN(__is_union) || defined(HAMON_MSVC)
		__is_union(T)
#else
		// TODO
#endif
	>
{};

template <typename T>
HAMON_INLINE_VAR HAMON_CXX11_CONSTEXPR
bool is_union_v = is_union<T>::value;

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_IS_UNION_HPP
