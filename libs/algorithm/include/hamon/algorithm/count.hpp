/**
 *	@file	count.hpp
 *
 *	@brief	count の定義
 */

#ifndef HAMON_ALGORITHM_COUNT_HPP
#define HAMON_ALGORITHM_COUNT_HPP

#include <hamon/algorithm/config.hpp>
#include <hamon/iterator/config.hpp>

#if defined(HAMON_USE_STD_ALGORITHM) && defined(HAMON_USE_STD_RANGES_ITERATOR)

#include <algorithm>

namespace hamon
{

using std::count;

}	// namespace hamon

#else

#include <hamon/iterator/iter_difference_t.hpp>
#include <hamon/config.hpp>

namespace hamon
{

/**
 *	@brief		指定された値と等値な要素の数を数える
 *
 *	@tparam		InputIterator
 *	@tparam		T
 *
 *	@param		first
 *	@param		last
 *	@param		value
 *
 *	@return		[first,last) 内のイテレータ i について、*i == value であるイテレータの数を返す
 *
 *	@complexity	正確に last - first 回の比較を行う
 */
template <typename InputIterator, typename T>
inline HAMON_CXX14_CONSTEXPR hamon::iter_difference_t<InputIterator>
count(InputIterator first, InputIterator last, T const& value)
{
	hamon::iter_difference_t<InputIterator> ret = 0;

	for (; first != last; ++first)
	{
		if (value == *first)
		{
			ret++;
		}
	}

	return ret;
}

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_COUNT_HPP
