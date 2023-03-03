/**
 *	@file	is_assignable.hpp
 *
 *	@brief	is_assignable の定義
 */

#ifndef HAMON_TYPE_TRAITS_IS_ASSIGNABLE_HPP
#define HAMON_TYPE_TRAITS_IS_ASSIGNABLE_HPP

#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/config.hpp>
#include <type_traits>

namespace hamon
{

/**
 *	@brief	型Tが型Uから代入可能か調べる。
 *
 *	@tparam		T
 *	@tparam		U
 *
 *	@require	型Tおよび型Uは完全型であるか、void(cv修飾を含む)か、要素数不明の配列型でなければならない。
 *
 *	is_assignableは、型Tが型Uから代入可能であるならば
 *	true_typeから派生し、そうでなければfalse_typeから派生する。
 *	declval<T>() = declval<U>()という実際には評価されない式が適格ならば代入可能であると判断される。
 */
template <typename T, typename U>
struct is_assignable
	: public hamon::bool_constant<
		std::is_assignable<T, U>::value
	>
{};

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

template <typename T, typename U>
HAMON_INLINE_VAR HAMON_CONSTEXPR
bool is_assignable_v = is_assignable<T, U>::value;

#endif

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_IS_ASSIGNABLE_HPP
