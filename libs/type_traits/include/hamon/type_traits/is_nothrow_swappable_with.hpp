/**
 *	@file	is_nothrow_swappable_with.hpp
 *
 *	@brief	is_nothrow_swappable_with の定義
 */

#ifndef HAMON_TYPE_TRAITS_IS_NOTHROW_SWAPPABLE_WITH_HPP
#define HAMON_TYPE_TRAITS_IS_NOTHROW_SWAPPABLE_WITH_HPP

#include <hamon/config.hpp>
#include <type_traits>

#if defined(__cpp_lib_is_swappable) && (__cpp_lib_is_swappable >= 201603)

namespace hamon
{

using std::is_nothrow_swappable_with;

}	// namespace hamon

#else

#include <hamon/utility/detail/is_swappable.hpp>

namespace hamon
{

/**
 *	@brief		型T と 型U がSwap可能かつ、そのSwapが例外を投げないか調べる
 *
 *	@tparam		T	チェックする型
 *	@tparam		U	チェックする型
 *
 *	@require	型Tと型Uは両方とも完全型であるか、void(cv修飾を含む)か、要素数不明の配列型でなければならない
 *
 *	is_nothrow_swappable_withは、型T と 型U がSwappableコンセプトを満たしており、そのswap関数が例外を投げないならtrue_typeから派生し、
 *	そうでなければfalse_typeから派生する。
 *	型TとUは参照でなければswapできないのでTとUが参照でない場合、結果はfalseとなる。
 */
template <typename T, typename U>
struct is_nothrow_swappable_with
	: public hamon::detail::is_nothrow_swappable_with<T, U>
{};

}	// namespace hamon

#endif

namespace hamon
{

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

template <typename T, typename U>
HAMON_INLINE_VAR HAMON_CONSTEXPR
bool is_nothrow_swappable_with_v = is_nothrow_swappable_with<T, U>::value;

#endif

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_IS_NOTHROW_SWAPPABLE_WITH_HPP
