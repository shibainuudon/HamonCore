/**
 *	@file	replace.hpp
 *
 *	@brief	replace の定義
 */

#ifndef HAMON_ALGORITHM_REPLACE_HPP
#define HAMON_ALGORITHM_REPLACE_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_ALGORITHM) && \
	defined(__cpp_lib_algorithm_default_value_type) && (__cpp_lib_algorithm_default_value_type >= 202403L)

#include <algorithm>

namespace hamon
{

using std::replace;

}	// namespace hamon

#else

#include <hamon/iterator/iterator_traits.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 27.7.5 Replace[alg.replace]

/**
 *	@brief		指定された値と一致する要素を指定された値に置き換える。
 *
 *	@tparam		ForwardIterator
 *	@tparam		T
 *
 *	@param		first
 *	@param		last
 *	@param		old_value
 *	@param		new_value
 *
 *	@require	*first = new_value という式が有効でなければならない。
 *
 *	@effect		[first,last) 内のイテレータ i について、
 *				*i == old_value であるものは *i = new_value という式によって置き換えられる。
 *
 *	@complexity	正確に last - first 回の比較を行う
 */
template <typename ForwardIterator,
	typename T = typename hamon::iterator_traits<ForwardIterator>::value_type>
HAMON_CXX14_CONSTEXPR void
replace(
	ForwardIterator first,
	ForwardIterator last,
	T const& old_value,
	T const& new_value)
{
	for (; first != last; ++first)
	{
		if (*first == old_value)
		{
			*first = new_value;
		}
	}
}

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_REPLACE_HPP
