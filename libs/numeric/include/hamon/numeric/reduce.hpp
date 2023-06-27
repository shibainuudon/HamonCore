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
#include <hamon/iterator/next.hpp>
#include <hamon/iterator/concepts/random_access_iterator.hpp>
#include <hamon/type_traits/is_invocable_r.hpp>
#include <hamon/type_traits/is_convertible.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

template <typename InputIterator, typename T, typename BinaryOperation,
	hamon::enable_if_t<!hamon::random_access_iterator_t<InputIterator>::value>* = nullptr>
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
	hamon::enable_if_t<hamon::random_access_iterator_t<InputIterator>::value>* = nullptr>
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
inline HAMON_CXX11_CONSTEXPR T
reduce(InputIterator first, InputIterator last, T init, BinaryOperation binary_op)
{
	using value_type = typename hamon::iterator_traits<InputIterator>::value_type;
	static_assert(hamon::is_invocable_r<T, BinaryOperation&, T&, T&>::value, "");
	static_assert(hamon::is_convertible<value_type, T>::value, "");

	return detail::reduce_impl(
		hamon::move(first),
		hamon::move(last),
		hamon::move(init),
		hamon::move(binary_op));
}

/**
 *	@overload
 */
template <typename InputIterator, typename T>
inline HAMON_CXX11_CONSTEXPR T
reduce(InputIterator first, InputIterator last, T init)
{
	return hamon::reduce(
		hamon::move(first),
		hamon::move(last),
		hamon::move(init),
		hamon::plus<>{});
}

/**
 *	@overload
 */
template <typename InputIterator>
inline HAMON_CXX11_CONSTEXPR typename hamon::iterator_traits<InputIterator>::value_type
reduce(InputIterator first, InputIterator last)
{
	using value_type = typename hamon::iterator_traits<InputIterator>::value_type;
	return hamon::reduce(
		hamon::move(first),
		hamon::move(last),
		value_type{},
		hamon::plus<>{});
}

}	// namespace hamon

#endif

#endif // HAMON_NUMERIC_REDUCE_HPP
