/**
 *	@file	accumulate.hpp
 *
 *	@brief	accumulate の定義
 */

#ifndef HAMON_NUMERIC_ACCUMULATE_HPP
#define HAMON_NUMERIC_ACCUMULATE_HPP

#include <hamon/concepts/detail/cpp17_copy_assignable.hpp>
#include <hamon/concepts/detail/cpp17_copy_constructible.hpp>
#include <hamon/functional/plus.hpp>
#include <hamon/iterator/detail/cpp17_input_iterator.hpp>
#include <hamon/iterator/next.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 26.10.3 Accumulate[accumulate]

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
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
T accumulate(InputIterator first, InputIterator last, T init, BinaryOperation binary_op)
{
	// [algorithms.requirements]/4.2
//	static_assert(hamon::detail::cpp17_input_iterator<InputIterator>, "");
	
	// [accumulate]/1
	static_assert(hamon::detail::cpp17_copy_constructible<T>, "");
	static_assert(hamon::detail::cpp17_copy_assignable<T>, "");

	// [accumulate]/2
	while (first != last)
	{
		init = binary_op(hamon::move(init), *first);
		first = hamon::next(first);
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
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
T accumulate(InputIterator first, InputIterator last, T init)
{
	return hamon::accumulate(first, last, init, hamon::plus<>());
}

}	// namespace hamon

#endif // HAMON_NUMERIC_ACCUMULATE_HPP
