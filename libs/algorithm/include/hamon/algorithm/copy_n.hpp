/**
 *	@file	copy_n.hpp
 *
 *	@brief	copy_n の定義
 */

#ifndef HAMON_ALGORITHM_COPY_N_HPP
#define HAMON_ALGORITHM_COPY_N_HPP

#include <hamon/algorithm/copy.hpp>
#include <hamon/iterator/input_iterator_tag.hpp>
#include <hamon/iterator/iterator_category.hpp>
#include <hamon/iterator/random_access_iterator_tag.hpp>
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
	hamon::input_iterator_tag const*)
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
	hamon::random_access_iterator_tag const*)
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

#endif // HAMON_ALGORITHM_COPY_N_HPP
