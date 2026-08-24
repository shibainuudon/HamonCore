/**
 *	@file	count.hpp
 *
 *	@brief	count の定義
 */

#ifndef HAMON_ALGORITHM_COUNT_HPP
#define HAMON_ALGORITHM_COUNT_HPP

#include <hamon/iterator/iterator_traits.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 27.6.11 Count[alg.count]

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
template <typename InputIterator,
	typename T = typename hamon::iterator_traits<InputIterator>::value_type>
HAMON_CXX14_CONSTEXPR typename hamon::iterator_traits<InputIterator>::difference_type
count(InputIterator first, InputIterator last, T const& value)
{
	typename hamon::iterator_traits<InputIterator>::difference_type ret = 0;

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

#endif // HAMON_ALGORITHM_COUNT_HPP
