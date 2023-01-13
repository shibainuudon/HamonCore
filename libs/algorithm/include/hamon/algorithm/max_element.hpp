/**
 *	@file	max_element.hpp
 *
 *	@brief	max_element の定義
 */

#ifndef HAMON_ALGORITHM_MAX_ELEMENT_HPP
#define HAMON_ALGORITHM_MAX_ELEMENT_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_ALGORITHM)

#include <algorithm>

namespace hamon
{

using std::max_element;

}	// namespace hamon

#else

#include <hamon/functional/less.hpp>
#include <hamon/config.hpp>

namespace hamon
{

/**
 *	@brief		[first, last)の範囲において、最大要素を指すイテレータを取得する
 *
 *	@tparam		ForwardIterator
 *	@tparam		Compare
 *
 *	@param		first
 *	@param		last
 *	@param		comp
 *
 *	@return		comp(*j, *i) の比較によって最大と判断された要素を指すイテレータ
 *
 *	@complexity	max((last - first) - 1, 0)回の比較を行う
 */
template <typename ForwardIterator, typename Compare>
inline HAMON_CXX14_CONSTEXPR ForwardIterator
max_element(ForwardIterator first, ForwardIterator last, Compare comp)
{
	if (first == last)
	{
		return first;
	}

	auto result = first++;

	for (; first != last; ++first)
	{
		if (comp(*result, *first))
		{
			result = first;
		}
	}

	return result;
}

/**
 *	@brief		[first, last)の範囲において、最大要素を指すイテレータを取得する
 *
 *	@tparam		ForwardIterator
 *
 *	@param		first
 *	@param		last
 *
 *	@return		*j < *i の比較によって最大と判断された要素を指すイテレータ
 *
 *	@complexity	max((last - first) - 1, 0)回の比較を行う
 */
template <typename ForwardIterator>
inline HAMON_CXX14_CONSTEXPR ForwardIterator
max_element(ForwardIterator first, ForwardIterator last)
{
	return hamon::max_element(
		first, last, hamon::less<>());
}

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_MAX_ELEMENT_HPP
