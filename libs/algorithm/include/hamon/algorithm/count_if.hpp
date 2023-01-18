/**
 *	@file	count_if.hpp
 *
 *	@brief	count_if の定義
 */

#ifndef HAMON_ALGORITHM_COUNT_IF_HPP
#define HAMON_ALGORITHM_COUNT_IF_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_ALGORITHM)

#include <algorithm>

namespace hamon
{

using std::count_if;

}	// namespace hamon

#else

#include <hamon/iterator/iter_difference_t.hpp>
#include <hamon/config.hpp>

namespace hamon
{

/**
 *	@brief		条件を満たしている要素の数を数える
 *
 *	@tparam		InputIterator
 *	@tparam		Predicate
 *
 *	@param		first
 *	@param		last
 *	@param		pred
 *
 *	@return		[first,last) 内のイテレータ i について、pred(*i) != false であるイテレータの数を返す
 *
 *	@complexity	正確に last - first 回の述語の適用を行う
 */
template <typename InputIterator, typename Predicate>
inline HAMON_CXX14_CONSTEXPR hamon::iter_difference_t<InputIterator>
count_if(InputIterator first, InputIterator last, Predicate pred)
{
	hamon::iter_difference_t<InputIterator> ret = 0;

	for (; first != last; ++first)
	{
		if (pred(*first))
		{
			ret++;
		}
	}

	return ret;
}

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_COUNT_IF_HPP
