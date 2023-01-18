/**
 *	@file	for_each_n.hpp
 *
 *	@brief	for_each_n の定義
 */

#ifndef HAMON_ALGORITHM_FOR_EACH_N_HPP
#define HAMON_ALGORITHM_FOR_EACH_N_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_ALGORITHM)

#include <algorithm>

namespace hamon
{

using std::for_each_n;

}	// namespace hamon

#else

#include <hamon/config.hpp>

namespace hamon
{

/**
 *	@brief		範囲の全ての要素に、指定された関数を適用する
 *
 *	@tparam		InputIterator
 *	@tparam		Size
 *	@tparam		Function
 *
 *	@param		first	関数を適用する範囲の初め
 *	@param		n		関数を適用する要素の数
 *	@param		f		適用する関数
 *
 *	@require	InputIterator は InputIterator の要件を満たす必要がある
 *				Function は MoveConstructible の要件を満たす必要があるが、
 *				CopyConstructible の要件を満たす必要はない。
 *
 *	@effect		[first, first + n) 内の全てのイテレータ i に
 *				先頭から順番に f(*i) という操作を行う。
 *				このアルゴリズムはその他のアルゴリズムと違い、Function の内部で *i の値を書き換えても構わない
 *				（もちろんイテレータの型が mutable iterator の要件を満たしている場合に限る）。
 *
 *	@return		first + n
 *
 *	@complexity	正確に f を n 回適用する
 *
 *	@note		f に戻り値がある場合、それは単に無視される。
 */
template <typename InputIterator, typename Size, typename Function>
inline HAMON_CXX14_CONSTEXPR InputIterator
for_each_n(InputIterator first, Size n, Function f)
{
	while (n-- > 0)
	{
		f(*first);
		++first;
	}

	return first;
}

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_FOR_EACH_N_HPP
