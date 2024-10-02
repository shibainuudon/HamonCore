/**
 *	@file	replace_if.hpp
 *
 *	@brief	replace_if の定義
 */

#ifndef HAMON_ALGORITHM_REPLACE_IF_HPP
#define HAMON_ALGORITHM_REPLACE_IF_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_ALGORITHM) && \
	defined(__cpp_lib_algorithm_default_value_type) && (__cpp_lib_algorithm_default_value_type >= 202403L)

#include <algorithm>

namespace hamon
{

using std::replace_if;

}	// namespace hamon

#else

#include <hamon/iterator/iterator_traits.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 27.7.5 Replace[alg.replace]

/**
 *	@brief		条件を満たす要素を指定された値に置き換える
 *
 *	@tparam		ForwardIterator
 *	@tparam		Predicate
 *	@tparam		T
 *
 *	@param		first
 *	@param		last
 *	@param		pred
 *	@param		new_value
 *
 *	@require	*first = new_value という式が有効でなければならない。
 *
 *	@effect		[first,last) 内のイテレータ i について、
 *				pred(*i) != false であるものは *i = new_value という式によって置き換えられる。
 *
 *	@complexity	正確に last - first 回の述語の適用を行う。
 */
template <
	typename ForwardIterator,
	typename Predicate,
	typename T = typename hamon::iterator_traits<ForwardIterator>::value_type
>
HAMON_CXX14_CONSTEXPR void
replace_if(
	ForwardIterator first,
	ForwardIterator last,
	Predicate pred,
	T const& new_value)
{
	for (; first != last; ++first)
	{
		if (pred(*first))
		{
			*first = new_value;
		}
	}
}

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_REPLACE_IF_HPP
