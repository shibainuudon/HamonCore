/**
 *	@file	clamp.hpp
 *
 *	@brief	clamp の定義
 */

#ifndef HAMON_ALGORITHM_CLAMP_HPP
#define HAMON_ALGORITHM_CLAMP_HPP

#include <algorithm>

#if defined(__cpp_lib_clamp) && (__cpp_lib_clamp >= 201603)

namespace hamon
{

using std::clamp;

}	// namespace hamon

#else

#include <hamon/functional/less.hpp>
#include <hamon/assert.hpp>
#include <hamon/config.hpp>

namespace hamon
{

/**
 *	@brief		値を最小値と最大値の範囲内に収める
 *
 *	@tparam		T		対象となる値の型
 *	@tparam		Compare	比較関数の型
 *
 *	@param		v		対象となる値
 *	@param		lo		最小値
 *	@param		hi		最大値
 *	@param		comp	比較関数
 *
 *	@return		vがhiより小さければ、vとloの大きい方の値
 *				そうでなければ、     vとhiの小さい方の値
 *
 *	@complexity	最大で2回の比較
 */
template <typename T, typename Compare>
inline HAMON_CONSTEXPR T const&
clamp(T const& v, T const& lo, T const& hi, Compare comp)
{
	return HAMON_ASSERT(!comp(hi, lo)),
        comp(v, lo) ? lo : comp(hi, v) ? hi : v;
}

/**
 *	@brief		値を最小値と最大値の範囲内に収める
 *
 *	@tparam		T		対象となる値の型
 *
 *	@param		v		対象となる値
 *	@param		lo		最小値
 *	@param		hi		最大値
 *
 *	@require	T は LessThanComparable でなければならない
 *
 *	@return		vがhiより小さければ、vとloの大きい方の値
 *				そうでなければ、     vとhiの小さい方の値
 *
 *	@complexity	最大で2回の比較
 */
template <typename T>
inline HAMON_CONSTEXPR T const&
clamp(T const& v, T const& lo, T const& hi)
{
	return hamon::clamp(v, lo, hi, hamon::less<T>());
}

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_CLAMP_HPP
