/**
 *	@file	min.hpp
 *
 *	@brief	min の定義
 */

#ifndef HAMON_ALGORITHM_MIN_HPP
#define HAMON_ALGORITHM_MIN_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_ALGORITHM)

#include <algorithm>

namespace hamon
{

using std::min;

}	// namespace hamon

#else

#include <hamon/algorithm/min_element.hpp>
#include <hamon/functional/less.hpp>
#include <hamon/config.hpp>
#include <initializer_list>

namespace hamon
{

/**
 *	@brief		同じ型の2つの値のうち、最小値を取得する。
 *
 *	@tparam		T
 *	@tparam		Compare
 *
 *	@param		a
 *	@param		b
 *	@param		comp
 *
 *	@return		最小値
 *
 *	@complexity	正確に1回の述語適用
 */
template <typename T, typename Compare>
inline HAMON_CONSTEXPR T const&
min(T const& a, T const& b, Compare comp)
{
	return comp(a, b) ? a : b;
}

/**
 *	@brief		同じ型の2つの値のうち、最小値を取得する。
 *
 *	@tparam		T
 *
 *	@param		a
 *	@param		b
 *
 *	@require	型Tがoperator<による比較が可能であること。
 *
 *	@return		最小値
 *
 *	@complexity	正確に1回の比較
 */
template <typename T>
inline HAMON_CONSTEXPR T const&
min(T const& a, T const& b)
{
	return hamon::min(a, b, hamon::less<>());
}

/**
 *	@brief		initializer_listによるN個の値のうち、最小値を取得する。
 *
 *	@tparam		T
 *	@tparam		Compare
 *
 *	@param		a
 *	@param		b
 *	@param		comp
 *
 *	@require	要素数が1以上であり、Tがコピーコンストラクト可能であること。
 *
 *	@return		最小値
 *
 *	@complexity	正確に t.size() - 1 回の述語適用
 */
template <typename T, typename Compare>
inline HAMON_CXX14_CONSTEXPR T
min(std::initializer_list<T> t, Compare comp)
{
	return *hamon::min_element(t.begin(), t.end(), comp);
}

/**
 *	@brief		initializer_listによるN個の値のうち、最小値を取得する。
 *
 *	@tparam		T
 *
 *	@param		a
 *	@param		b
 *
 *	@require	型Tがoperator<による比較が可能であること。
 *				要素数が1以上であり、Tがコピーコンストラクト可能であること。
 *
 *	@return		最小値
 *
 *	@complexity	正確に t.size() - 1 回の比較
 */
template <typename T>
inline HAMON_CXX14_CONSTEXPR T
min(std::initializer_list<T> t)
{
	return *hamon::min_element(t.begin(), t.end(), hamon::less<>());
}

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_MIN_HPP
