/**
 *	@file	is_swappable_with.hpp
 *
 *	@brief	is_swappable_with の定義
 */

#ifndef HAMON_TYPE_TRAITS_IS_SWAPPABLE_WITH_HPP
#define HAMON_TYPE_TRAITS_IS_SWAPPABLE_WITH_HPP

#include <hamon/utility/detail/is_swappable.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 21.3.5.4 Type properties[meta.unary.prop]

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
struct is_swappable_with
	: public hamon::detail::is_swappable_with<T, U>
{};

template <typename T, typename U>
HAMON_INLINE_VAR HAMON_CXX11_CONSTEXPR
bool is_swappable_with_v = is_swappable_with<T, U>::value;

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_IS_SWAPPABLE_WITH_HPP
