﻿/**
 *	@file	remove.hpp
 *
 *	@brief	remove の定義
 */

#ifndef HAMON_ALGORITHM_REMOVE_HPP
#define HAMON_ALGORITHM_REMOVE_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_ALGORITHM) && \
	defined(__cpp_lib_algorithm_default_value_type) && (__cpp_lib_algorithm_default_value_type >= 202403L)

#include <algorithm>

namespace hamon
{

using std::remove;

}	// namespace hamon

#else

#include <hamon/algorithm/find.hpp>
#include <hamon/iterator/iterator_traits.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 27.7.8 Remove[alg.remove]

/**
 *	@brief		指定された要素を取り除く
 *
 *	@tparam		ForwardIterator
 *	@tparam		T
 *
 *	@param		first
 *	@param		last
 *	@param		value
 *
 *	@require	*first の型は MoveAssignable の要件を満たす必要がある
 *
 *	@return		有効な要素の末尾の次を指すイテレータを返す。
 *
 *	@effect		[first,last) 内にあるイテレータ i について、
 *				*i == value である要素を取り除き、有効な要素を範囲の前に寄せる。
 *
 *	@complexity	正確に last - first 回の比較を行う
 *
 *	@note		有効な要素を範囲の前方に集める処理には、ムーブを使用する。
 *				取り除いた要素の先頭を指すイテレータをretとし、
 *				範囲[ret, last)の各要素には、有効な要素からムーブされた値が設定される。
 *				それらの値は、「有効だが未規定な値」となる。
 *
 *	@see	remove_erase
 */
template <typename ForwardIterator,
	typename T = typename hamon::iterator_traits<ForwardIterator>::value_type>
HAMON_CXX14_CONSTEXPR ForwardIterator
remove(
	ForwardIterator first,
	ForwardIterator last,
	T const& value)
{
	first = hamon::find(first, last, value);

	auto result = first;

	for (; first != last; ++first)
	{
		if (!(*first == value))
		{
			*result = hamon::move(*first);
			++result;
		}
	}

	return result;
}

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_REMOVE_HPP
