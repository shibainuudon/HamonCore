/**
 *	@file	is_final.hpp
 *
 *	@brief	is_final の定義
 */

#ifndef HAMON_TYPE_TRAITS_IS_FINAL_HPP
#define HAMON_TYPE_TRAITS_IS_FINAL_HPP

#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 21.3.5.4 Type properties[meta.unary.prop]

/**
 *	@brief	型Tにfinalが付いているかを調べる。
 *
 *	@tparam		T	チェックする型
 *
 *	@require	型Tがクラス型である場合、その型は完全型でなければならない
 *
 *	is_finalは、型Tがfinal指定されていればtrue_typeから派生し、
 *	そうでなければfalse_typeから派生する。
 */
template <typename T>
struct is_final
	: public hamon::bool_constant<
#if HAMON_HAS_BUILTIN(__is_final) || defined(HAMON_MSVC)
		__is_final(T)
#else
		// TODO
#endif
	>
{};

template <typename T>
HAMON_INLINE_VAR HAMON_CXX11_CONSTEXPR
bool is_final_v = is_final<T>::value;

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_IS_FINAL_HPP
