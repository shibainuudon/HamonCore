/**
 *	@file	is_nothrow_assignable.hpp
 *
 *	@brief	is_nothrow_assignable の定義
 */

#ifndef HAMON_TYPE_TRAITS_IS_NOTHROW_ASSIGNABLE_HPP
#define HAMON_TYPE_TRAITS_IS_NOTHROW_ASSIGNABLE_HPP

#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/config.hpp>
#include <type_traits>

namespace hamon
{

/**
 *	@brief	型Tが型Uから代入可能で、かつ代入操作が例外を投げないかを調べる。
 *
 *	@tparam		T
 *	@tparam		U
 *
 *	@require	型Tおよび型Uは完全型であるか、void(cv修飾を含む)か、要素数不明の配列型でなければならない。
 *
 *	is_nothrow_assignableは、型Tが型Uから例外を投げない保証のもとに代入可能であるならば
 *	true_typeから派生し、そうでなければfalse_typeから派生する。
 *	is_assignable<T, U>::value == trueかつ、いかなる例外も投げないならば、
 *	例外を投げない代入が可能であると判断される。
 */
template <typename T, typename U>
struct is_nothrow_assignable
	: public hamon::bool_constant<
		std::is_nothrow_assignable<T, U>::value
	>
{};

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

template <typename T, typename U>
HAMON_INLINE_VAR HAMON_CONSTEXPR
bool is_nothrow_assignable_v = is_nothrow_assignable<T, U>::value;

#endif

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_IS_NOTHROW_ASSIGNABLE_HPP
