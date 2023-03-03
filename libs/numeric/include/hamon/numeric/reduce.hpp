/**
 *	@file	reduce.hpp
 *
 *	@brief	reduce の定義
 */

#ifndef HAMON_NUMERIC_REDUCE_HPP
#define HAMON_NUMERIC_REDUCE_HPP

#include <hamon/numeric/config.hpp>

#if defined(HAMON_USE_STD_NUMERIC_PARALLEL)

#include <numeric>

namespace hamon
{

using std::reduce;

}	// namespace hamon

#else

#include <hamon/functional/plus.hpp>
#include <hamon/iterator/iterator_traits.hpp>
#include <hamon/iterator/concepts/random_access_iterator.hpp>
#include <hamon/type_traits/is_invocable_r.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/config.hpp>
#include <type_traits>
#include <utility>

namespace hamon
{

namespace detail
{

template <typename InputIterator, typename T, typename BinaryOperation>
inline HAMON_CXX14_CONSTEXPR T
reduce_impl(InputIterator first, InputIterator last, T init, BinaryOperation binary_op, hamon::false_type)
{
	for (; first != last; ++first)
	{
		init = static_cast<T>(binary_op(init, *first));
	}

	return init;
}

template <typename InputIterator, typename T, typename BinaryOperation>
inline HAMON_CXX14_CONSTEXPR T
reduce_impl(InputIterator first, InputIterator last, T init, BinaryOperation binary_op, hamon::true_type)
{
	while ((last - first) >= 4)
	{
		T v1 = static_cast<T>(binary_op(first[0], first[1]));
		T v2 = static_cast<T>(binary_op(first[2], first[3]));
		T v3 = static_cast<T>(binary_op(v1, v2));
		init = static_cast<T>(binary_op(init, v3));
		first += 4;
	}

	return reduce_impl(
		std::move(first),
		std::move(last),
		std::move(init),
		std::move(binary_op),
		hamon::false_type{});
}

}	// namespace detail

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
inline HAMON_CXX14_CONSTEXPR T
reduce(InputIterator first, InputIterator last, T init, BinaryOperation binary_op)
{
	using value_type = typename hamon::iterator_traits<InputIterator>::value_type;
	static_assert(hamon::is_invocable_r<T, BinaryOperation&, T&, T&>::value, "");
	static_assert(std::is_convertible<value_type, T>::value, "");

	return detail::reduce_impl(
		std::move(first),
		std::move(last),
		std::move(init),
		std::move(binary_op),
		hamon::random_access_iterator_t<InputIterator>{});
}

/**
 *	@overload
 */
template <typename InputIterator, typename T>
inline HAMON_CXX14_CONSTEXPR T
reduce(InputIterator first, InputIterator last, T init)
{
	return hamon::reduce(
		std::move(first),
		std::move(last),
		std::move(init),
		hamon::plus<>{});
}

/**
 *	@overload
 */
template <typename InputIterator>
inline HAMON_CXX14_CONSTEXPR typename hamon::iterator_traits<InputIterator>::value_type
reduce(InputIterator first, InputIterator last)
{
	using value_type = typename hamon::iterator_traits<InputIterator>::value_type;
	return hamon::reduce(
		std::move(first),
		std::move(last),
		value_type{},
		hamon::plus<>{});
}

}	// namespace hamon

#endif

#endif // HAMON_NUMERIC_REDUCE_HPP
