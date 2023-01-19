/**
 *	@file	remove_if.hpp
 *
 *	@brief	remove_if の定義
 */

#ifndef HAMON_ALGORITHM_REMOVE_IF_HPP
#define HAMON_ALGORITHM_REMOVE_IF_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_ALGORITHM)

#include <algorithm>

namespace hamon
{

using std::remove_if;

}	// namespace hamon

#else

#include <hamon/algorithm/find_if.hpp>
#include <hamon/config.hpp>
#include <utility>

namespace hamon
{

/**
 *	@brief		条件を満たす要素を取り除く
 *
 *	@tparam		ForwardIterator
 *	@tparam		Predicate
 *
 *	@param		first
 *	@param		last
 *	@param		pred
 *
 *	@require	*first の型は MoveAssignable の要件を満たす必要がある
 *
 *	@return		有効な要素の末尾の次を指すイテレータを返す。
 *
 *	@effect		[first,last) 内にあるイテレータ i について、
 *				pred(*i) != false である要素を取り除き、有効な要素を範囲の前に寄せる。
 *
 *	@complexity	正確に last - first 回の述語の適用を行う
 *
 *	@note		有効な要素を範囲の前方に集める処理には、ムーブを使用する。
 *				取り除いた要素の先頭を指すイテレータをretとし、
 *				範囲[ret, last)の各要素には、有効な要素からムーブされた値が設定される。
 *				それらの値は、「有効だが未規定な値」となる。
 *
 *	@see	remove_if_erase
 */
template <typename ForwardIterator, typename Predicate>
inline HAMON_CXX14_CONSTEXPR ForwardIterator
remove_if(
	ForwardIterator first,
	ForwardIterator last,
	Predicate pred)
{
	first = hamon::find_if(first, last, pred);

	auto result = first;

	for (; first != last; ++first)
	{
		if (!pred(*first))
		{
			*result = std::move(*first);
			++result;
		}
	}

	return result;
}

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_REMOVE_IF_HPP
