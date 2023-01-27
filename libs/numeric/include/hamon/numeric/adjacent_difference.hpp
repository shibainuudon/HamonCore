/**
 *	@file	adjacent_difference.hpp
 *
 *	@brief	adjacent_difference の定義
 */

#ifndef HAMON_NUMERIC_ADJACENT_DIFFERENCE_HPP
#define HAMON_NUMERIC_ADJACENT_DIFFERENCE_HPP

#include <hamon/numeric/config.hpp>

#if defined(HAMON_USE_STD_NUMERIC)

#include <numeric>

namespace hamon
{

using std::adjacent_difference;

}	// namespace hamon

#else

#include <hamon/functional/minus.hpp>
#include <hamon/config.hpp>
#include <utility>

namespace hamon
{

/**
 *	@brief		隣接する要素間の差を計算する。
 *
 *	@tparam		InputIterator
 *	@tparam		OutputIterator
 *	@tparam		BinaryOperation
 *
 *	@param		first
 *	@param		last
 *	@param		result
 *	@param		binary_op
 *
 *	@require	InputIteratorが指す値の型が、MoveAssignableであり、*firstで初期化でき、result出力イテレータに書き込めること
 *				InputIteratorが指す値の型のオブジェクトaとbにおいて、式binary_op(b, a)の結果がresult出力イテレータに書き込めること
 *				binary_opの呼び出しが、範囲[first, last]および範囲[result, result + (last - first)]の要素変更、イテレータの無効化をしてはならない
 *
 *	@effect		*(result)   = *first;
 *				*(result+1) = *(first+1) - *(first);
 *				*(result+2) = *(first+2) - *(first+1);
 *				*(result+3) = *(first+3) - *(first+2);
 *				...
 *
 *	@return		result + (last - first)
 *
 *	@complexity	正確に(last - first) - 1回だけbinary_opを適用する
 */
template <
	typename InputIterator,
	typename OutputIterator,
	typename BinaryOperation
>
HAMON_CXX14_CONSTEXPR OutputIterator
adjacent_difference(
	InputIterator first,
	InputIterator last,
	OutputIterator result,
	BinaryOperation binary_op)
{
	if (first == last)
	{
		return result;
	}

	auto acc = *first;
	*result = acc;
	++result;
	++first;

	while (first != last)
	{
		auto val = *first;
		*result = binary_op(val, std::move(acc));
		acc = std::move(val);

		++result;
		++first;
	}

	return result;
}

/**
 *	@overload
 */
template <
	typename InputIterator,
	typename OutputIterator
>
HAMON_CXX14_CONSTEXPR OutputIterator
adjacent_difference(
	InputIterator first,
	InputIterator last,
	OutputIterator result)
{
	return hamon::adjacent_difference(
		std::move(first),
		std::move(last),
		std::move(result),
		hamon::minus<>());
}

}	// namespace hamon

#endif

#endif // HAMON_NUMERIC_ADJACENT_DIFFERENCE_HPP
