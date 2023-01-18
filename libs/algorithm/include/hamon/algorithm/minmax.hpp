/**
 *	@file	minmax.hpp
 *
 *	@brief	minmax の定義
 */

#ifndef HAMON_ALGORITHM_MINMAX_HPP
#define HAMON_ALGORITHM_MINMAX_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_ALGORITHM)

#include <algorithm>

namespace hamon
{

using std::minmax;

}	// namespace hamon

#else

#include <hamon/algorithm/minmax_element.hpp>
#include <hamon/functional/less.hpp>
#include <hamon/config.hpp>
#include <utility>
#include <initializer_list>

namespace hamon
{

/**
 *	@brief		同じ型の2つの値のうち、最小値と最大値の組を取得する。
 *
 *	@tparam		T
 *	@tparam		Compare
 *
 *	@param		a
 *	@param		b
 *	@param		comp
 *
 *	@return		firstが最小値、secondが最大値となるpairオブジェクト
 *
 *	@complexity	正確に1回の述語適用
 */
template <typename T, typename Compare>
inline HAMON_CXX14_CONSTEXPR std::pair<T const&, T const&>
minmax(T const& a, T const& b, Compare comp)
{
	return comp(a, b) ?
		std::pair<T const&, T const&>(a, b) :
		std::pair<T const&, T const&>(b, a);
}

/**
 *	@brief		同じ型の2つの値のうち、最小値と最大値の組を取得する。
 *
 *	@tparam		T
 *
 *	@param		a
 *	@param		b
 *
 *	@require	型Tがoperator<による比較が可能であること。
 *
 *	@return		firstが最小値、secondが最大値となるpairオブジェクト
 *
 *	@complexity	正確に1回の比較
 */
template <typename T>
inline HAMON_CXX14_CONSTEXPR std::pair<T const&, T const&>
minmax(T const& a, T const& b)
{
	return hamon::minmax(a, b, hamon::less<>());
}

/**
 *	@brief		initializer_listによるN個の値のうち、最小値と最大値の組を取得する。
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
 *	@return		firstが最小値、secondが最大値となるpairオブジェクト
 *
 *	@complexity	高々(3/2) * t.size()回の述語適用
 */
template <typename T, typename Compare>
inline HAMON_CXX14_CONSTEXPR std::pair<T, T>
minmax(std::initializer_list<T> t, Compare comp)
{
	auto const p = hamon::minmax_element(t.begin(), t.end(), comp);
	return std::pair<T, T>(*p.first, *p.second);
}

/**
 *	@brief		initializer_listによるN個の値のうち、最小値と最大値の組を取得する。
 *
 *	@tparam		T
 *
 *	@param		a
 *	@param		b
 *
 *	@require	型Tがoperator<による比較が可能であること。
 *				要素数が1以上であり、Tがコピーコンストラクト可能であること。
 *
 *	@return		firstが最小値、secondが最大値となるpairオブジェクト
 *
 *	@complexity	高々(3/2) * t.size()回の比較
 */
template <typename T>
inline HAMON_CXX14_CONSTEXPR std::pair<T, T>
minmax(std::initializer_list<T> t)
{
	return hamon::minmax(t, hamon::less<>());
}

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_MINMAX_HPP
