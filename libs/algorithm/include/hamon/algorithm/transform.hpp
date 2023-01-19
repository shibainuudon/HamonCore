/**
 *	@file	transform.hpp
 *
 *	@brief	transform の定義
 */

#ifndef HAMON_ALGORITHM_TRANSFORM_HPP
#define HAMON_ALGORITHM_TRANSFORM_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_ALGORITHM)

#include <algorithm>

namespace hamon
{

using std::transform;

}	// namespace hamon

#else

#include <hamon/config.hpp>

namespace hamon
{

/**
 *	@brief		全ての要素に関数を適用する
 *
 *	@tparam		InputIterator
 *	@tparam		OutputIterator
 *	@tparam		UnaryOperation
 *
 *	@param		first
 *	@param		last
 *	@param		result
 *	@param		unary_op
 *
 *	以下、last - first を N とおく。
 *
 *	@return		result + N
 *
 *	@require	unary_op は、[first, last], [result, result + N] 内のイテレータや
 *				subrange を無効にしたり、要素を書き換えてはならない。
 *
 *	@effect		[result, result + N) 内のイテレータ i の要素に、
 *				それぞれ unary_op(*(first + (i - result))) を代入する
 *
 *	@complexity	正確に N 回の unary_op の適用が行われる。
 *
 *	@note		result は first と同じであっても構わない。
 */
template <
	typename InputIterator,
	typename OutputIterator,
	typename UnaryOperation
>
inline HAMON_CXX14_CONSTEXPR OutputIterator
transform(
	InputIterator first,
	InputIterator last,
	OutputIterator result,
	UnaryOperation unary_op)
{
	while (first != last)
	{
		*result++ = unary_op(*first++);
	}

	return result;
}

template <
	typename InputIterator1,
	typename InputIterator2,
	typename OutputIterator,
	typename BinaryOperation
>
inline HAMON_CXX14_CONSTEXPR OutputIterator
transform(
	InputIterator1 first1, InputIterator1 last1,
	InputIterator2 first2,
	OutputIterator result,
	BinaryOperation binary_op)
{
	while (first1 != last1)
	{
		*result++ = binary_op(*first1++, *first2++);
	}

	return result;
}

}	// namespace hamon

#endif

#include <hamon/config.hpp>

namespace hamon
{

/**
 *	@brief		全ての要素に関数を適用する
 *
 *	@tparam		OutputRange
 *	@tparam		InputIterator1
 *	@tparam		InputIterator2
 *	@tparam		BinaryOperation
 *
 *	@param		first1
 *	@param		last1
 *	@param		first2
 *	@param		last2
 *	@param		result
 *	@param		binary_op
 *
 *	以下、min(last1 - first1, last2 - first2) を N とおく。
 *
 *	@return		result + N
 *
 *	@require	binary_op は、[first1, last1], [first2, last2], [result, result + N]
 *				内のイテレータや subrange を無効にしたり、要素を書き換えてはならない。
 *
 *	@effect		[result, result + N) 内のイテレータ i の要素に、
 *				それぞれ binary_op(*(first1 + (i - result)), *(first2 + (i - result))) を代入する。
 *
 *	@complexity	正確に N 回の unary_op の適用が行われる。
 *
 *	@note		result は first1 や first2 と同じであっても構わない。
 */
template <
	typename InputIterator1,
	typename InputIterator2,
	typename OutputIterator,
	typename BinaryOperation
>
inline HAMON_CXX14_CONSTEXPR OutputIterator
transform(
	InputIterator1 first1, InputIterator1 last1,
	InputIterator2 first2, InputIterator2 last2,
	OutputIterator result,
	BinaryOperation binary_op)
{
	while (first1 != last1 && first2 != last2)
	{
		*result++ = binary_op(*first1++, *first2++);
	}

	return result;
}

}	// namespace hamon

#endif // HAMON_ALGORITHM_TRANSFORM_HPP
