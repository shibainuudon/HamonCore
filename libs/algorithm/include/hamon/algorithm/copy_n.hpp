/**
 *	@file	copy_n.hpp
 *
 *	@brief	copy_n の定義
 */

#ifndef HAMON_ALGORITHM_COPY_N_HPP
#define HAMON_ALGORITHM_COPY_N_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_ALGORITHM) &&	\
	!(defined(HAMON_MSVC) && (HAMON_MSVC == 1930) && (HAMON_MSVC_FULL_VER <= 193030705))

// 以下のコード
// char a[] { 1, 2, 3 };
// hamon::copy_n(a+1, 2, a);
// で、
// Visual Studio 2022 Version 17.0.(0-1) かつ、
// Releaseビルドかつ、
// 実行時(非constexpr)
// のときのみ、a[0]の値が想定通りにならない。
// Visual Studio 2022 のバグと思われる。
// (配列の型を変えると大丈夫な時があったりする。int型は大丈夫なときが多い)

#include <algorithm>

namespace hamon
{

using std::copy_n;

}	// namespace hamon

#else

#include <hamon/algorithm/copy.hpp>
#include <hamon/iterator/iterator_category.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

template <
	typename InputIterator,
	typename Size,
	typename OutputIterator
>
inline HAMON_CXX14_CONSTEXPR OutputIterator
copy_n_impl(
	InputIterator first,
	Size n,
	OutputIterator result,
	std::input_iterator_tag*)
{
	for (Size i = 0; i < n; i++)
	{
		*result++ = *first++;
	}

	return result;
}

template <
	typename RandomAccessIterator,
	typename Size,
	typename OutputIterator
>
inline HAMON_CXX14_CONSTEXPR OutputIterator
copy_n_impl(
	RandomAccessIterator first,
	Size n,
	OutputIterator result,
	std::random_access_iterator_tag*)
{
	return hamon::copy(first, first + n, result);
}

}	// namespace detail

/**
 *	@brief		指定された数の要素をコピーする
 *
 *	@tparam		InputIterator
 *	@tparam		Size
 *	@tparam		OutputIterator
 *
 *	@param		first
 *	@param		n
 *	@param		result
 *
 *	@return		result + n
 *
 *	@effect		0 以上 n 未満であるそれぞれの i について、*(result + i) = *(first + i) を行う。
 *
 *	@complexity	正確に n 回代入が行われる。
 */
template <
	typename InputIterator,
	typename Size,
	typename OutputIterator
>
inline HAMON_CXX14_CONSTEXPR OutputIterator
copy_n(InputIterator first, Size n, OutputIterator result)
{
	using Category = hamon::iterator_category<InputIterator>*;
	return hamon::detail::copy_n_impl(first, n, result, Category());
}

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_COPY_N_HPP
