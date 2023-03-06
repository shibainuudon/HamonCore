/**
 *	@file	is_trivially_assignable.hpp
 *
 *	@brief	is_trivially_assignable の定義
 */

#ifndef HAMON_TYPE_TRAITS_IS_TRIVIALLY_ASSIGNABLE_HPP
#define HAMON_TYPE_TRAITS_IS_TRIVIALLY_ASSIGNABLE_HPP

#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/config.hpp>
#include <type_traits>

namespace hamon
{

/**
 *	@brief	型Tが型Uからトリビアルに代入可能か調べる。
 *
 *	@tparam		T
 *	@tparam		U
 *
 *	@require	型Tおよび型Uは完全型であるか、void(cv修飾を含む)か、要素数不明の配列型でなければならない。
 *
 *	is_trivially_assignableは、型Tが型Uからトリビアルに代入可能であるならば
 *	true_typeから派生し、そうでなければfalse_typeから派生する。
 *	「トリビアルに代入可能」とは、ユーザー定義されない代入演算子を持っているということを意味する。
 */
template <typename T, typename U>
struct is_trivially_assignable
	: public hamon::bool_constant<
		std::is_trivially_assignable<T, U>::value
	>
{};

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

template <typename T, typename U>
HAMON_INLINE_VAR HAMON_CONSTEXPR
bool is_trivially_assignable_v = is_trivially_assignable<T, U>::value;

#endif

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_IS_TRIVIALLY_ASSIGNABLE_HPP
