/**
 *	@file	accumulate.hpp
 *
 *	@brief	accumulate の定義
 */

#ifndef HAMON_NUMERIC_ACCUMULATE_HPP
#define HAMON_NUMERIC_ACCUMULATE_HPP

#include <hamon/numeric/config.hpp>

#if defined(HAMON_USE_STD_NUMERIC)

#include <numeric>

namespace hamon
{

using std::accumulate;

}	// namespace hamon

#else

#include <hamon/functional/plus.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/config.hpp>

namespace hamon
{

/**
 *	@brief	1つのシーケンスの任意の範囲の値を足し合わせる
 *
 *	@tparam	InputIterator	シーケンスのイテレータ型
 *	@tparam	T				集計結果の型
 *	@tparam	BinaryOperation	アキュムレータの型
 *
 *	@param	first		シーケンスの先頭
 *	@param	last		シーケンスの終端
 *	@param	init		初期値
 *	@param	binary_op	アキュームレータ。InputIteratorの要素型を2引数とり、その要素型を返す関数
 *
 *	@return	集計結果の値
 *
 *	@note	binary_opでシーケンスの要素を書き換えることと、
 *			イテレータを無効にすることは禁止されている。
 *			それ以外の操作は全て認められる。
 */
template <
	typename InputIterator,
	typename T,
	typename BinaryOperation
>
HAMON_CXX14_CONSTEXPR T
accumulate(
	InputIterator first,
	InputIterator last,
	T init,
	BinaryOperation binary_op)
{
	while (first != last)
	{
		init = binary_op(hamon::move(init), *first++);
	}

	return init;
}

/**
 *	@brief	1つのシーケンスの任意の範囲の値を足し合わせる
 *
 *	@tparam	InputIterator	シーケンスのイテレータ型
 *	@tparam	T				集計結果の型
 *
 *	@param	first		シーケンスの先頭
 *	@param	last		シーケンスの終端
 *	@param	init		初期値
 *
 *	@return	集計結果の値
 */
template <typename InputIterator, typename T>
HAMON_CXX14_CONSTEXPR T
accumulate(
	InputIterator first,
	InputIterator last,
	T init)
{
	return hamon::accumulate(
		hamon::move(first),
		hamon::move(last),
		hamon::move(init),
		hamon::plus<>());
}

}	// namespace hamon

#endif

#endif // HAMON_NUMERIC_ACCUMULATE_HPP
