/**
 *	@file	is_copy_constructible.hpp
 *
 *	@brief	is_copy_constructible の定義
 */

#ifndef HAMON_TYPE_TRAITS_IS_COPY_CONSTRUCTIBLE_HPP
#define HAMON_TYPE_TRAITS_IS_COPY_CONSTRUCTIBLE_HPP

#include <hamon/type_traits/add_const.hpp>
#include <hamon/type_traits/add_lvalue_reference.hpp>
#include <hamon/type_traits/is_constructible.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 21.3.5.4 Type properties[meta.unary.prop]

/**
 *	@brief	型Tがコピー構築可能か調べる
 *
 *	@tparam		T	チェックする型
 *
 *	@require	型Tは完全型であるか、void(cv修飾を含む)か、要素数不明の配列型でなければならない
 *
 *	is_copy_constructibleは、型Tがコピー構築可能であるならば
 *	true_typeから派生し、そうでなければfalse_typeから派生する。
 */
template <typename T>
struct is_copy_constructible
	: public hamon::is_constructible<T, hamon::add_lvalue_reference_t<hamon::add_const_t<T>>>
{};

template <typename T>
HAMON_INLINE_VAR HAMON_CXX11_CONSTEXPR
bool is_copy_constructible_v = is_copy_constructible<T>::value;

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_IS_COPY_CONSTRUCTIBLE_HPP
