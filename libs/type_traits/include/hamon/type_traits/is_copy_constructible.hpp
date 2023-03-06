/**
 *	@file	is_copy_constructible.hpp
 *
 *	@brief	is_copy_constructible の定義
 */

#ifndef HAMON_TYPE_TRAITS_IS_COPY_CONSTRUCTIBLE_HPP
#define HAMON_TYPE_TRAITS_IS_COPY_CONSTRUCTIBLE_HPP

#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/config.hpp>
#include <type_traits>

namespace hamon
{

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
	: public hamon::bool_constant<
		std::is_copy_constructible<T>::value
	>
{};

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

template <typename T>
HAMON_INLINE_VAR HAMON_CONSTEXPR
bool is_copy_constructible_v = is_copy_constructible<T>::value;

#endif

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_IS_COPY_CONSTRUCTIBLE_HPP
