/**
 *	@file	unit_test_algorithm_ranges_sample.cpp
 *
 *	@brief	ranges::sample のテスト
 */

#include <hamon/algorithm/ranges/sample.hpp>
#include <hamon/algorithm/ranges/equal.hpp>
#include <hamon/algorithm/ranges/sort.hpp>
#include <hamon/algorithm/ranges/adjacent_find.hpp>
#include <hamon/algorithm/ranges/includes.hpp>
#include <gtest/gtest.h>
#include <random>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_algorithm_test
{

namespace ranges_sample_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <
	template <typename> class in_wrapper,
	template <typename> class out_wrapper,
	typename Rng
>
inline bool test01(Rng& rng)
{
	namespace ranges = hamon::ranges;

	const int x[] = { 1,2,3,4,5,6,7,8,9,10 };
	test_range<const int, in_wrapper<const int>> rx(x);
	{
		int y[10];
		test_range<int, out_wrapper<int>> ry(y);
		auto out = ranges::sample(rx.begin(), rx.end(), ry.begin(), 20, rng);
		VERIFY(out.m_ptr == y+10);
		VERIFY(ranges::equal(x, y));
	}

	for (int i = 0; i < 100; i++)
	{
		int z[5] = { 0 };
		test_range<int, out_wrapper<int>> rz(z);
		rx.m_first = x;
		auto out = ranges::sample(rx, rz.begin(), 5, rng);
		VERIFY(out.m_ptr == z+5);
		ranges::sort(z);
		VERIFY(ranges::adjacent_find(z) == out.m_ptr);
		VERIFY(ranges::includes(x, z));
	}
	return true;
}

#undef VERIFY

GTEST_TEST(AlgorithmTest, RangesSampleTest)
{
	std::mt19937 rng;
	EXPECT_TRUE((test01<forward_iterator_wrapper, output_iterator_wrapper>(rng)));
	EXPECT_TRUE((test01<input_iterator_wrapper, random_access_iterator_wrapper>(rng)));
}

}	// namespace ranges_sample_test

}	// namespace hamon_algorithm_test
