﻿/**
 *	@file	is_swappable_with.hpp
 *
 *	@brief	is_swappable_with の定義
 */

#ifndef HAMON_TYPE_TRAITS_IS_SWAPPABLE_WITH_HPP
#define HAMON_TYPE_TRAITS_IS_SWAPPABLE_WITH_HPP

#include <hamon/config.hpp>
#include <type_traits>

#if defined(__cpp_lib_is_swappable) && (__cpp_lib_is_swappable >= 201603)

namespace hamon
{

using std::is_swappable_with;

}	// namespace hamon

#else

#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/utility/declval.hpp>
#include <utility>

namespace hamon
{

/**
 *	@brief		型T と 型U がSwap可能か調べる
 *
 *	@tparam		T	チェックする型
 *	@tparam		U	チェックする型
 *
 *	@require	型Tと型Uは両方とも完全型であるか、void(cv修飾を含む)か、要素数不明の配列型でなければならない
 *
 *	is_swappable_withは、型T と 型U がSwappableコンセプトを満たしていればtrue_typeから派生し、
 *	そうでなければfalse_typeから派生する。
 *	型TとUは参照でなければswapできないのでTとUが参照でない場合、結果はfalseとなる。
 */
template <typename T, typename U>
struct is_swappable_with;

namespace is_swappable_detail
{

using std::swap;

template <typename T, typename U>
struct is_swappable_with_impl
{
private:
	template <
		typename T2,
		typename U2,
		typename = decltype(
			swap(hamon::declval<T2>(), hamon::declval<U2>()),
			swap(hamon::declval<U2>(), hamon::declval<T2>()))
	>
	static hamon::true_type test(int);

	template <typename, typename>
	static hamon::false_type test(...);

public:
	using type = decltype(test<T, U>(0));
};

}	// namespace is_swappable_detail

template <typename T, typename U>
struct is_swappable_with
	: public is_swappable_detail::is_swappable_with_impl<T, U>::type
{};

}	// namespace hamon

#endif

namespace hamon
{

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

template <typename T, typename U>
HAMON_INLINE_VAR HAMON_CONSTEXPR
bool is_swappable_with_v = is_swappable_with<T, U>::value;

#endif

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_IS_SWAPPABLE_WITH_HPP
