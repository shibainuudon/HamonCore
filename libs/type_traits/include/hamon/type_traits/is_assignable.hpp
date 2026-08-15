/**
 *	@file	is_assignable.hpp
 *
 *	@brief	is_assignable の定義
 */

#ifndef HAMON_TYPE_TRAITS_IS_ASSIGNABLE_HPP
#define HAMON_TYPE_TRAITS_IS_ASSIGNABLE_HPP

#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 21.3.5.4 Type properties[meta.unary.prop]

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
#if HAMON_HAS_BUILTIN(__is_assignable) || defined(HAMON_MSVC)
		__is_assignable(T, U)
#else
		// TODO
#endif
	>
{};

template <typename T, typename U>
HAMON_INLINE_VAR HAMON_CXX11_CONSTEXPR
bool is_assignable_v = is_assignable<T, U>::value;

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_IS_ASSIGNABLE_HPP
