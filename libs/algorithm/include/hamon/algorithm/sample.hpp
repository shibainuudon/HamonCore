/**
 *	@file	sample.hpp
 *
 *	@brief	sample の定義
 */

#ifndef HAMON_ALGORITHM_SAMPLE_HPP
#define HAMON_ALGORITHM_SAMPLE_HPP

#include <algorithm>

#if defined(__cpp_lib_sample) && (__cpp_lib_sample >= 201603)

namespace hamon
{

using std::sample;

}	// namespace hamon

#else

#include <hamon/algorithm/min.hpp>
#include <hamon/iterator/distance.hpp>
#include <hamon/iterator/input_iterator_tag.hpp>
#include <hamon/iterator/iterator_category.hpp>
#include <hamon/iterator/iter_difference_t.hpp>
#include <hamon/iterator/forward_iterator_tag.hpp>
#include <hamon/type_traits/common_type.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_integral.hpp>
#include <hamon/assert.hpp>
#include <hamon/config.hpp>
#include <iterator>
#include <random>

namespace hamon
{

namespace detail
{

template <
	typename PopulationIterator,
	typename SampleIterator,
	typename Distance,
	typename UniformRandomBitGenerator
>
inline SampleIterator
sample(
	PopulationIterator first,
	PopulationIterator last,
	SampleIterator out,
	Distance n,
	UniformRandomBitGenerator& g,
	hamon::input_iterator_tag const*)
{
	using Distribution = std::uniform_int_distribution<Distance>;

	Distance k = 0;
	for (; first != last && k < n; ++first, ++k)
	{
		out[k] = *first;
	}

	auto const sz = k;
	for (; first != last; ++first, ++k)
	{
		auto const r = Distribution(0, k)(g);
		if (r < sz)
		{
			out[r] = *first;
		}
	}

	return out + hamon::min(n, k);
}

template <
	typename PopulationIterator,
	typename SampleIterator,
	typename Distance,
	typename UniformRandomBitGenerator
>
inline SampleIterator
sample(
	PopulationIterator first,
	PopulationIterator last,
	SampleIterator out,
	Distance n,
	UniformRandomBitGenerator& g,
	hamon::forward_iterator_tag const*)
{
	using Distribution = std::uniform_int_distribution<Distance>;

	auto unsampled_sz = hamon::distance(first, last);
	for (n = hamon::min(n, unsampled_sz); n != 0; ++first)
	{
		auto const r = Distribution(0, --unsampled_sz)(g);

		if (r < n)
		{
			*out++ = *first;
			--n;
		}
	}

	return out;
}

}	// namespace detail

/**
 *	@brief		[first,last) から n 個の要素をランダムで選んで out に出力する
 *
 *	@tparam		PopulationIterator
 *	@tparam		SampleIterator
 *	@tparam		Distance
 *	@tparam		UniformRandomBitGenerator
 *
 *	@param		first
 *	@param		last
 *	@param		out
 *	@param		n
 *	@param		g
 *
 *	@require	・PopulationIterator は InputIterator の要件を満たす必要がある
 *				・SampleIterator は OutputIterator の要件を満たす必要がある
 *				・PopulationIterator が ForwardIterator の要件を満たさないとき、
 *				　SampleIterator は RandomAccessIterator の要件を満たす必要がある
 *				・PopulationIterator の value_type は out に書き込み可能でなければならない
 *				・Distance は整数型でなければならない
 *				・remove_reference_t<UniformRandomBitGenerator> は UniformRandomBitGenerator の要件を満たし、
 *				　かつ Distance に変換可能でなければならない
 *
 *	@return		出力後のout
 *
 *	@complexity	distance(first, last) に比例
 */
template <
	typename PopulationIterator,
	typename SampleIterator,
	typename Distance,
	typename UniformRandomBitGenerator,
	typename = hamon::enable_if_t<
		hamon::is_integral<Distance>::value
	>
>
inline SampleIterator
sample(
	PopulationIterator first,
	PopulationIterator last,
	SampleIterator out,
	Distance n,
	UniformRandomBitGenerator&& g)
{
	using Category = hamon::iterator_category<PopulationIterator>*;
	using Difference = hamon::iter_difference_t<PopulationIterator>;
	using CommonType = hamon::common_type_t<Distance, Difference>;

	HAMON_ASSERT(n >= 0);

	return hamon::detail::sample(
		first,
		last,
		out,
		CommonType(n),
		g,
		Category());
}

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_SAMPLE_HPP
