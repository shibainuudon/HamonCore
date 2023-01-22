﻿/**
 *	@file	replace_copy_if.hpp
 *
 *	@brief	replace_copy_if の定義
 */

#ifndef HAMON_ALGORITHM_REPLACE_COPY_IF_HPP
#define HAMON_ALGORITHM_REPLACE_COPY_IF_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_ALGORITHM)

#include <algorithm>

namespace hamon
{

using std::replace_copy_if;

}	// namespace hamon

#else

#include <hamon/config.hpp>

namespace hamon
{

/**
 *	@brief		条件を満たす要素を指定された値に置き換え、その結果を出力の範囲へコピーする
 *
 *	@tparam		InputIterator
 *	@tparam		OutputIterator
 *	@tparam		Predicate
 *	@tparam		T
 *
 *	@param		first
 *	@param		last
 *	@param		result
 *	@param		pred
 *	@param		new_value
 *
 *	@require	*first と new_value は result へ書き込み可能でなければならない。
 *				また、[first,last) と [result,result + (last - first)) の範囲が重なっていてはならない。
 *
 *	@return		result + (last - first)
 *
 *	@effect		[result,result + (last - first)) 内のイテレータ i について、
 *				pred(*(first + (i - result))) != false である場合は new_value が代入され、
 *				そうでない場合は *(first + (i - result)) が 代入される。
 *
 *	@complexity	正確に last - first 回の述語の適用を行う
 */
template <
	typename InputIterator,
	typename OutputIterator,
	typename Predicate,
	typename T
>
inline HAMON_CXX14_CONSTEXPR OutputIterator
replace_copy_if(
	InputIterator first,
	InputIterator last,
	OutputIterator result,
	Predicate pred,
	T const& new_value)
{
	for (; first != last; ++first)
	{
		*result++ = (pred(*first) ? new_value : *first);
	}

	return result;
}

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_REPLACE_COPY_IF_HPP
