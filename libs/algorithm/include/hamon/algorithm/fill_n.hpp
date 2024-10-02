/**
 *	@file	fill_n.hpp
 *
 *	@brief	fill_n の定義
 */

#ifndef HAMON_ALGORITHM_FILL_N_HPP
#define HAMON_ALGORITHM_FILL_N_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_ALGORITHM) && \
	defined(__cpp_lib_algorithm_default_value_type) && (__cpp_lib_algorithm_default_value_type >= 202403L)

#include <algorithm>

namespace hamon
{

using std::fill_n;

}	// namespace hamon

#else

#include <hamon/iterator/iterator_traits.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 27.7.6 Fill[alg.fill]

/**
 *	@brief		指定された値を出力の範囲に指定された個数書き込む
 *
 *	@tparam		OutputIterator
 *	@tparam		Size
 *	@tparam		T
 *
 *	@param		first
 *	@param		n
 *	@param		value
 *
 *	@require	value は output iterator へ書き込み可能でなければならない
 *				Size は integral type に変換可能でなければならない
 *
 *	@return		n が 1 以上の場合は first + n、そうでない場合は first を返す。
 *
 *	@effect		n が 1 以上の場合は [first,first + n) 内の全ての要素に value を代入し、
 *				そうでない場合は何もしない。
 *
 *	@complexity	n が 1 以上の場合は n 回、そうでない場合は 0 回の代入を行う。
 */
template <
	typename OutputIterator,
	typename Size,
	typename T = typename hamon::iterator_traits<OutputIterator>::value_type
>
HAMON_CXX14_CONSTEXPR OutputIterator
fill_n(OutputIterator first, Size n, T const& value)
{
	while (n-- > 0)
	{
		*first++ = value;
	}

	return first;
}

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_FILL_N_HPP
