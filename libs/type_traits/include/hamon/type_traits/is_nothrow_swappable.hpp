/**
 *	@file	is_nothrow_swappable.hpp
 *
 *	@brief	is_nothrow_swappable の定義
 */

#ifndef HAMON_TYPE_TRAITS_IS_NOTHROW_SWAPPABLE_HPP
#define HAMON_TYPE_TRAITS_IS_NOTHROW_SWAPPABLE_HPP

#include <hamon/utility/detail/is_swappable.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 21.3.5.4 Type properties[meta.unary.prop]

/**
 *	@brief		型T が Swap可能かつ、そのSwapが例外を投げないかどうか調べる
 *
 *	@tparam		T	チェックする型
 *
 *	@require	型Tは完全型であるか、void(cv修飾を含む)か、要素数不明の配列型でなければならない
 *
 *	is_nothrow_swappableは、型T がSwappableコンセプトを満たしており、そのswap関数が例外を投げないならtrue_typeから派生し、
 *	そうでなければfalse_typeから派生する。
 *
 *	参照可能な型に対して、is_nothrow_swappable_with<T&, T&>::valueと同じ結果となり、参照可能でない型に対してはfalseとなる。
 *
 *	参照可能な型とは、以下のいずれかの条件に合致する型である：
 *	・オブジェクト型
 *	・CV修飾されていない、もしくは参照修飾されていない関数型
 *	・参照修飾されている型
 */
template <typename T>
struct is_nothrow_swappable
	: public hamon::detail::is_nothrow_swappable<T>
{};

template <typename T>
HAMON_INLINE_VAR HAMON_CXX11_CONSTEXPR
bool is_nothrow_swappable_v = is_nothrow_swappable<T>::value;

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_IS_NOTHROW_SWAPPABLE_HPP
