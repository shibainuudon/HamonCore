/**
 *	@file	shuffle.hpp
 *
 *	@brief	shuffle の定義
 */

#ifndef HAMON_ALGORITHM_SHUFFLE_HPP
#define HAMON_ALGORITHM_SHUFFLE_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_ALGORITHM)

#include <algorithm>

namespace hamon
{

using std::shuffle;

}	// namespace hamon

#else

#include <hamon/iterator/iter_difference_t.hpp>
#include <hamon/config.hpp>
#include <cstddef>
#include <random>
#include <utility>

namespace hamon
{

/**
 *	@brief		[first,last) のそれぞれの要素を同じ確率で並び替える
 *
 *	@tparam		RandomAccessIterator
 *	@tparam		UniformRandomNumberGenerator
 *
 *	@param		first
 *	@param		last
 *	@param		g
 *
 *	@require	RandomAccessIterator は ValueSwappable の要件を満たしている必要がある。
 *				UniformRandomNumberGenerator は uniform random number generator の要件を満たさなければならず、
 *				その戻り値の型はiterator_traits<RandomAccessIterator>::difference_type へ変換可能でなければならない。
 *
 *	@complexity	正確に (last - first) - 1 回 swap する。
 */
template <
	typename RandomAccessIterator,
	typename UniformRandomNumberGenerator
>
inline void
shuffle(
	RandomAccessIterator first,
	RandomAccessIterator last,
	UniformRandomNumberGenerator&& g)
{
	using difference_type = hamon::iter_difference_t<RandomAccessIterator>;
	using D = std::uniform_int_distribution<std::ptrdiff_t>;
	using P = typename D::param_type;
	
	auto d = last - first;

	if (d > 1)
	{
		D uid;

		for (--last, --d; first < last; ++first, --d)
		{
			auto i = uid(g, P(0, d));

			if (i != difference_type(0))
			{
				using std::swap;
				swap(*first, *(first + i));
			}
		}
	}
}

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_SHUFFLE_HPP
