/**
 *	@file	is_partitioned.hpp
 *
 *	@brief	is_partitioned の定義
 */

#ifndef HAMON_ALGORITHM_IS_PARTITIONED_HPP
#define HAMON_ALGORITHM_IS_PARTITIONED_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_ALGORITHM)

#include <algorithm>

namespace hamon
{

using std::is_partitioned;

}	// namespace hamon

#else

#include <hamon/config.hpp>

namespace hamon
{

/**
 *	@brief		与えられた範囲が条件によって区分化されているか判定する。
 *
 *	@tparam		InputIterator
 *	@tparam		Predicate
 *
 *	@param		first
 *	@param		last
 *	@param		pred
 *
 *	@require	InputIteratorのvalue typeは Predicate の引数型へ変換可能でなければならない。
 *				つまり pred(*first) という式が有効でなければならない。
 *
 *	@return		[first,last) が空、 または [first,last) が pred によって区分化されているなら true 、
 *				そうでなければ false を返す。
 *				つまり、pred を満たす全ての要素が、pred を満たさない全ての要素より前に出現するなら true を返す。
 *
 *	@complexity	線形時間。最大で last - first 回 pred が適用される。
 */
template <typename InputIterator, typename Predicate>
inline HAMON_CXX14_CONSTEXPR bool
is_partitioned(
	InputIterator first,
	InputIterator last,
	Predicate pred)
{
	for (; first != last; ++first)
	{
		if (!pred(*first))
		{
			break;
		}
	}

	if (first == last)
	{
		return true;
	}

	++first;
	
	for (; first != last; ++first)
	{
		if (pred(*first))
		{
			return false;
		}
	}

	return true;
}

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_IS_PARTITIONED_HPP
