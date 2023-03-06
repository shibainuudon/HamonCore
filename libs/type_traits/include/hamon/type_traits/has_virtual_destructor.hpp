/**
 *	@file	has_virtual_destructor.hpp
 *
 *	@brief	has_virtual_destructor の定義
 */

#ifndef HAMON_TYPE_TRAITS_HAS_VIRTUAL_DESTRUCTOR_HPP
#define HAMON_TYPE_TRAITS_HAS_VIRTUAL_DESTRUCTOR_HPP

#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/config.hpp>
#include <type_traits>

namespace hamon
{

/**
 *	@brief		型Tが仮想デストラクタを持っているか調べる
 *
 *	@tparam		T	チェックする型
 *
 *	@require	型Tが非共用体のクラスである場合、その型は完全型でなければならない
 *
 *	has_virtual_destructorは、型Tが仮想デストラクタを持っていればtrue_typeから派生し、
 *	そうでなければfalse_typeから派生する。
 */
template <typename T>
struct has_virtual_destructor
	: public hamon::bool_constant<
		std::has_virtual_destructor<T>::value
	>
{};

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

template <typename T>
HAMON_INLINE_VAR HAMON_CONSTEXPR
bool has_virtual_destructor_v = has_virtual_destructor<T>::value;

#endif

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_HAS_VIRTUAL_DESTRUCTOR_HPP
