/**
 *	@file	radix_sort.hpp
 *
 *	@brief	radix_sort の定義
 */

#ifndef HAMON_ALGORITHM_RADIX_SORT_HPP
#define HAMON_ALGORITHM_RADIX_SORT_HPP

#include <hamon/algorithm/swap_ranges.hpp>
#include <hamon/bit/bitsof.hpp>
#include <hamon/bit/countr_zero.hpp>
#include <hamon/bit/has_single_bit.hpp>
#include <hamon/functional/identity.hpp>
#include <hamon/functional/invoke.hpp>
#include <hamon/iterator/ranges/distance.hpp>
#include <hamon/iterator/iter_value_t.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_CLANG("-Wsign-conversion")

template <
	hamon::size_t Radix,
	typename Iter1,
	typename Iter2,
	typename Proj,
	typename SizeType
>
inline HAMON_CXX14_CONSTEXPR void
radix_sort_loop(Iter1 input, Iter2 output, Proj proj, SizeType size, hamon::size_t shift)
{
	hamon::size_t const Mask = Radix - 1;

	hamon::size_t counts[Radix] = {};

	// Count occurrences
	for (SizeType i = 0; i < size; ++i)
	{
		auto const idx = (hamon::invoke(proj, input[i]) >> shift) & Mask;
		counts[idx]++;
	}

	// Prefix Sum
	for (hamon::size_t i = 1; i < Radix; ++i)
	{
		counts[i] += counts[i - 1];
	}

	// Build the output array
	for (auto i = size - 1; i >= 0; --i)
	{
		auto const idx = (hamon::invoke(proj, input[i]) >> shift) & Mask;
		output[--counts[idx]] = hamon::move(input[i]);
	}
}

HAMON_WARNING_POP()

}	// namespace detail

/**
 *	@brief		基数ソート
 *
 *	@tparam		RandomAccessIterator1
 *	@tparam		RandomAccessIterator2
 *	@tparam		Proj
 *
 *	@param		first
 *	@param		last
 *	@param		tmp_first
 *	@param		proj
 *
 *	以下、last - first を N とする。
 *
 *	基数ソートはその性質上、入力範囲と同じ大きさの一時バッファが必要となる。
 *	その範囲の先頭を tmp_first で与える。
 *
 *	基数ソートは符号なし整数をキーとしてソートするため、
 *	projでその変換関数を与える。
 *	*firstの型が符号なし整数のときは何も与えなくて良い。
 *
 *	@require	[first, last) と [tmp_first, tmp_first+N) の範囲が重なってはならない。
 *				0 以上 N 未満のそれぞれの n について、
 *				    invoke(proj, *(first + n)) の戻り値の型は符号なし整数型でなければならない。
 *				    *(first + n) と *(tmp_first + n) は Swappable でなければならない。
 *
 *	@effect		[first, last) の範囲をソートする
 *
 *	@complexity	O(N)
 *
 *	@note		呼び出し後の [tmp_first, tmp_first+N) の範囲の値は実装依存
 */
template <
	typename RandomAccessIterator1,
	typename RandomAccessIterator2,
	typename Proj = hamon::identity
>
inline HAMON_CXX14_CONSTEXPR void
radix_sort(
	RandomAccessIterator1 first, RandomAccessIterator1 last,
	RandomAccessIterator2 tmp_first,
	Proj proj = {})
{
	hamon::size_t const Radix = 0x100;
	static_assert(hamon::has_single_bit(Radix), "");

	using value_t = hamon::iter_value_t<RandomAccessIterator1>;
	auto const size = hamon::ranges::distance(first, last);

	int loop_count = 0;
	for (hamon::size_t shift = 0;
		shift < hamon::bitsof<value_t>();
		shift += hamon::countr_zero(Radix))
	{
		if (loop_count % 2 == 0)
		{
			detail::radix_sort_loop<Radix>(first, tmp_first, proj, size, shift);
		}
		else
		{
			detail::radix_sort_loop<Radix>(tmp_first, first, proj, size, shift);
		}

		++loop_count;
	}

	// Make sure original range is output
	if (loop_count % 2 == 1)
	{
		hamon::swap_ranges(
			first, last,
			tmp_first);
	}
}

}	// namespace hamon

#endif // HAMON_ALGORITHM_RADIX_SORT_HPP
