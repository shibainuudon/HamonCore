/**
 *	@file	find.hpp
 *
 *	@brief	find の定義
 */

#ifndef HAMON_ALGORITHM_FIND_HPP
#define HAMON_ALGORITHM_FIND_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_ALGORITHM) && \
	defined(__cpp_lib_algorithm_default_value_type) && (__cpp_lib_algorithm_default_value_type >= 202403L)

#include <algorithm>

namespace hamon
{

using std::find;

}	// namespace hamon

#else

#include <hamon/iterator/iterator_traits.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 27.6.6 Find[alg.find]

/**
 *	@brief		指定された値を検索する
 *
 *	@tparam		InputIterator
 *	@tparam		T
 *
 *	@param		first
 *	@param		last
 *	@param		value
 *
 *	@return		[first,last) 内のイテレータ i について、*i == value であるような最初のイテレータを返す。
 *				そのようなイテレータが見つからなかった場合は last を返す。
 *
 *	@complexity	最大で last - first 回比較を行う
 */
template <typename InputIterator,
	typename T = typename hamon::iterator_traits<InputIterator>::value_type>
HAMON_CXX14_CONSTEXPR InputIterator
find(InputIterator first, InputIterator last, T const& value)
{
	for (; first != last; ++first)
	{
		if (*first == value)
		{
			break;
		}
	}

	return first;
}

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_FIND_HPP
