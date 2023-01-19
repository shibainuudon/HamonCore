/**
 *	@file	partition_point.hpp
 *
 *	@brief	partition_point の定義
 */

#ifndef HAMON_ALGORITHM_PARTITION_POINT_HPP
#define HAMON_ALGORITHM_PARTITION_POINT_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_ALGORITHM)

#include <algorithm>

namespace hamon
{

using std::partition_point;

}	// namespace hamon

#else

#include <hamon/iterator/distance.hpp>
#include <hamon/iterator/next.hpp>
#include <hamon/config.hpp>

namespace hamon
{

/**
 *	@brief		与えられた範囲から条件によって区分化されている位置を得る。
 *
 *	@tparam		ForwardIterator
 *	@tparam		Predicate
 *
 *	@param		first
 *	@param		last
 *	@param		pred
 *
 *	@require	ForwardIterator の value type は Predicate の argument type へ変換可能でなければならない。
 *				[first,last) は pred によって区分化されていなければならない。
 *				つまり、pred を満たす全ての要素が、pred を満たさない全ての要素より前に出現してなければならない。
 *
 *	@return		all_of(first, mid, pred) と none_of(mid, last, pred) が
 *				true であるようなイテレータ mid を返す。
 *
 *	@complexity	O(log(last - first)) のオーダーで pred が適用される。
 */
template <typename ForwardIterator, typename Predicate>
inline HAMON_CXX14_CONSTEXPR ForwardIterator
partition_point(
	ForwardIterator first,
	ForwardIterator last,
	Predicate pred)
{
	for (auto len = hamon::distance(first, last); len != 0;)
	{
		auto half = len / 2;
		auto mid = hamon::next(first, half);

		if (pred(*mid))
		{
			len -= half + 1;
			first = hamon::next(mid);
		}
		else
		{
			len = half;
		}
	}

	return first;
}

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_PARTITION_POINT_HPP
