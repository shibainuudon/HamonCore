/**
 *	@file	for_each.hpp
 *
 *	@brief	for_each の定義
 */

#ifndef HAMON_ALGORITHM_FOR_EACH_HPP
#define HAMON_ALGORITHM_FOR_EACH_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_ALGORITHM)

#include <algorithm>

namespace hamon
{

using std::for_each;

}	// namespace hamon

#else

#include <hamon/config.hpp>

namespace hamon
{

/**
 *	@brief		範囲の全ての要素に、指定された関数を適用する
 *
 *	@tparam		InputIterator
 *	@tparam		Function
 *
 *	@param		first
 *	@param		last
 *	@param		f
 *
 *	@require	Function は MoveConstructible の要件を満たす必要があるが、
 *				CopyConstructible の要件を満たす必要はない。
 *
 *	@effect		[first,last) 内の全てのイテレータ i に f(*i) という操作を行う。
 *				first から順番に処理し、last - 1 まで行う。
 *				このアルゴリズムはその他のアルゴリズムと違い、Function の内部で *i の値を書き換えても構わない
 *				（もちろんイテレータの型が mutable iterator の要件を満たしている場合に限る）。
 *
 *	@return		move(f)
 *
 *	@complexity	正確に f を last - first 回適用する
 *
 *	@note		f に戻り値がある場合、それは単に無視される。
 */
template <typename InputIterator, typename Function>
inline HAMON_CXX14_CONSTEXPR Function
for_each(
	InputIterator first,
	InputIterator last,
	Function f)
{
	for (; first != last; ++first)
	{
		f(*first);
	}

	return f;
}

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_FOR_EACH_HPP
