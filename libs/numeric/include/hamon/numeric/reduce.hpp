/**
 *	@file	reduce.hpp
 *
 *	@brief	reduce の定義
 */

#ifndef HAMON_NUMERIC_REDUCE_HPP
#define HAMON_NUMERIC_REDUCE_HPP

#include <hamon/concepts/convertible_to.hpp>
#include <hamon/concepts/detail/cpp17_move_constructible.hpp>
#include <hamon/functional/plus.hpp>
#include <hamon/iterator/concepts/random_access_iterator.hpp>
#include <hamon/iterator/detail/cpp17_input_iterator.hpp>
#include <hamon/iterator/iterator_traits.hpp>
#include <hamon/iterator/next.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

template <typename InputIterator, typename T, typename BinaryOperation,
	hamon::enable_if_t<!hamon::random_access_iterator<InputIterator>>* = nullptr>
inline HAMON_CXX11_CONSTEXPR T
reduce_impl(InputIterator first, InputIterator last, T init, BinaryOperation binary_op)
{
	return
		first == last ?
			init:
		reduce_impl(
			hamon::next(first),
			last,
			static_cast<T>(binary_op(init, *first)),
			binary_op);
}

template <typename InputIterator, typename T, typename BinaryOperation,
	hamon::enable_if_t<hamon::random_access_iterator<InputIterator>>* = nullptr>
inline HAMON_CXX11_CONSTEXPR T
reduce_impl(InputIterator first, InputIterator last, T init, BinaryOperation binary_op)
{
	return
		(last - first) == 0 ?
			init :
		(last - first) == 1 ?
			static_cast<T>(binary_op(init, first[0])) :
		(last - first) == 2 ?
			static_cast<T>(binary_op(
				init,
				static_cast<T>(binary_op(first[0], first[1])))) :
		(last - first) == 3 ?
			static_cast<T>(binary_op(
				static_cast<T>(binary_op(init, first[0])),
				static_cast<T>(binary_op(first[1], first[2])))) :
		(last - first) == 4 ?
			static_cast<T>(binary_op(
				init,
				static_cast<T>(binary_op(
					static_cast<T>(binary_op(first[0], first[1])),
					static_cast<T>(binary_op(first[2], first[3])))))) :
		(last - first) == 5 ?
			static_cast<T>(binary_op(
				static_cast<T>(binary_op(
					init,
					first[0])),
				static_cast<T>(binary_op(
					static_cast<T>(binary_op(first[1], first[2])),
					static_cast<T>(binary_op(first[3], first[4])))))) :
		(last - first) == 6 ?
			static_cast<T>(binary_op(
				static_cast<T>(binary_op(
					init,
					static_cast<T>(binary_op(first[0], first[1])))),
				static_cast<T>(binary_op(
					static_cast<T>(binary_op(first[2], first[3])),
					static_cast<T>(binary_op(first[4], first[5])))))) :
		(last - first) == 7 ?
			static_cast<T>(binary_op(
				static_cast<T>(binary_op(
					static_cast<T>(binary_op(init,     first[0])),
					static_cast<T>(binary_op(first[1], first[2])))),
				static_cast<T>(binary_op(
					static_cast<T>(binary_op(first[3], first[4])),
					static_cast<T>(binary_op(first[5], first[6])))))) :
		reduce_impl(
			first,
			first + (last - first) / 2,
			reduce_impl(
				first + (last - first) / 2,
				last,
				init,
				binary_op),
			binary_op);
}

}	// namespace detail

// 26.10.4 Reduce[reduce]

/**
 *	@brief	イテレータ範囲を集計する
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
 *	@note	accumulate()関数は範囲の先頭から順に要素を集計するが、
 *			この関数は並列計算のために集計順を規定しない。
 *			初期値(init)とイテレータ範囲[first, last)を合算したリストの任意の組み合わせに、
 *			順不同でbinary_op(binary_op(a, b), binary_op(c, d))のように適用していき、
 *			集計値を計算する。
 * 
 *	@complexity	関数オブジェクトbinary_opをO(last - first)回だけ適用する
 */
template <typename InputIterator, typename T, typename BinaryOperation>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
T reduce(InputIterator first, InputIterator last, T init, BinaryOperation binary_op)
{
	// [algorithms.requirements]/4.2
	static_assert(hamon::detail::cpp17_input_iterator<InputIterator>, "");

	// [reduce]/5
	static_assert(hamon::convertible_to<decltype(binary_op(init, *first)), T>, "");
	static_assert(hamon::convertible_to<decltype(binary_op(*first, init)), T>, "");
	static_assert(hamon::convertible_to<decltype(binary_op(init, init)), T>, "");
	static_assert(hamon::convertible_to<decltype(binary_op(*first, *first)), T>, "");

	// [reduce]/6
	static_assert(hamon::detail::cpp17_move_constructible<T>, "");

	return detail::reduce_impl(first, last, init, binary_op);
}

// TODO
//template <typename ExecutionPolicy, typename ForwardIterator, typename T, typename BinaryOperation>
//T reduce(ExecutionPolicy&& exec, ForwardIterator first, ForwardIterator last, T init, BinaryOperation binary_op);

/**
 *	@overload
 */
template <typename InputIterator, typename T>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
T reduce(InputIterator first, InputIterator last, T init)
{
	// [reduce]/3
	return hamon::reduce(first, last, init, hamon::plus<>{});
}

// TODO
//template <typename ExecutionPolicy, typename ForwardIterator, typename T>
//HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
//T reduce(ExecutionPolicy&& exec, ForwardIterator first, ForwardIterator last, T init)
//{
//	// [reduce]/4
//	return hamon::reduce(hamon::forward<ExecutionPolicy>(exec), first, last, init, hamon::plus<>());
//}

/**
 *	@overload
 */
template <typename InputIterator>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
typename hamon::iterator_traits<InputIterator>::value_type
reduce(InputIterator first, InputIterator last)
{
	// [reduce]/1
	return hamon::reduce(first, last,
		typename hamon::iterator_traits<InputIterator>::value_type{});
}

// TODO
//template <typename ExecutionPolicy, typename ForwardIterator>
//HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
//typename hamon::iterator_traits<ForwardIterator>::value_type
//reduce(ExecutionPolicy&& exec, ForwardIterator first, ForwardIterator last)
//{
//	// [reduce]/2
//	return hamon::reduce(hamon::forward<ExecutionPolicy>(exec), first, last,
//		typename hamon::iterator_traits<ForwardIterator>::value_type{});
//}

}	// namespace hamon

#endif // HAMON_NUMERIC_REDUCE_HPP
