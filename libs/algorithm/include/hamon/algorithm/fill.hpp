/**
 *	@file	fill.hpp
 *
 *	@brief	fill の定義
 */

#ifndef HAMON_ALGORITHM_FILL_HPP
#define HAMON_ALGORITHM_FILL_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_ALGORITHM) && \
	defined(__cpp_lib_algorithm_default_value_type) && (__cpp_lib_algorithm_default_value_type >= 202403L)

#include <algorithm>

namespace hamon
{

using std::fill;

}	// namespace hamon

#else

#include <hamon/algorithm/fill_n.hpp>
#include <hamon/iterator/iterator_category.hpp>
#include <hamon/iterator/iterator_traits.hpp>
#include <hamon/iterator/forward_iterator_tag.hpp>
#include <hamon/iterator/random_access_iterator_tag.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

template <typename ForwardIterator, typename T>
HAMON_CXX14_CONSTEXPR void
fill_impl(
	ForwardIterator first,
	ForwardIterator last,
	T const& value,
	hamon::forward_iterator_tag const*)
{
	while (first != last)
	{
		*first++ = value;
	}
}

template <typename RandomAccessIterator, typename T>
HAMON_CXX14_CONSTEXPR void
fill_impl(
	RandomAccessIterator first,
	RandomAccessIterator last,
	T const& value,
	hamon::random_access_iterator_tag const*)
{
	hamon::fill_n(first, last - first, value);
}

}	// namespace detail

// 27.7.6 Fill[alg.fill]

/**
 *	@brief		指定された値を出力の範囲に書き込む
 *
 *	@tparam		ForwardIterator
 *	@tparam		T
 *
 *	@param		first
 *	@param		last
 *	@param		value
 *
 *	@require	value は output iterator へ書き込み可能でなければならない
 *
 *	@effect		[first,last) 内の全ての要素に value を代入する
 *
 *	@complexity	正確に last - first 回の代入を行う
 */
template <typename ForwardIterator,
	typename T = typename hamon::iterator_traits<ForwardIterator>::value_type>
HAMON_CXX14_CONSTEXPR void
fill(ForwardIterator first, ForwardIterator last, T const& value)
{
	using Category = hamon::iterator_category<ForwardIterator>*;
	hamon::detail::fill_impl(first, last, value, Category());
}

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_FILL_HPP
