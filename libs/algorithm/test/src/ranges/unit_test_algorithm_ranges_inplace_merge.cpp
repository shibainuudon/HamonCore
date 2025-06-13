/**
 *	@file	unit_test_algorithm_ranges_inplace_merge.cpp
 *
 *	@brief	ranges::inplace_merge のテスト
 */

#include <hamon/algorithm/ranges/inplace_merge.hpp>
#include <hamon/algorithm/ranges/equal.hpp>
#include <hamon/functional/ranges/greater.hpp>
#include <hamon/functional/negate.hpp>
#include <hamon/iterator/ranges/next.hpp>
#include <hamon/ranges/adaptors/zip_view.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_algorithm_test
{

namespace ranges_inplace_merge_test
{

struct X
{
	int i;
};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool test01()
{
	namespace ranges = hamon::ranges;
	{
		int x[] = { 1,4,5,  2,3,6 };
		test_bidirectional_range<int> rx(x);
		auto ret = ranges::inplace_merge(rx, ranges::next(rx.begin(), 3));
		VERIFY(ret == rx.end());
		int const y[] = {1,2,3,4,5,6};
		VERIFY(ranges::equal(x, y));
	}
	{
		int x[] = { 7,5,2,1,  6,5,3,3,2,2 };
		test_bidirectional_range<int> rx(x);
		auto ret = ranges::inplace_merge(rx, ranges::next(rx.begin(), 4), ranges::greater{});
		VERIFY(ret == rx.end());
		int const y[] = {7,6,5,5,3,3,2,2,2,1};
		VERIFY(ranges::equal(x, y));
	}
	{
		int x[] = { 1,2,4,5,6,  3 };
		test_bidirectional_range<int> rx(x);
		auto ret = ranges::inplace_merge(rx, ranges::next(rx.begin(), 5), ranges::greater{}, hamon::negate<>{});
		VERIFY(ret == rx.end());
		int const y[] = {1,2,3,4,5,6};
		VERIFY(ranges::equal(x, y));
	}
	return true;
}

inline HAMON_CXX14_CONSTEXPR bool test02()
{
	namespace ranges = hamon::ranges;
	{
		X x[] = { {1},{2},{6},  {1},{3},{5} };
		test_bidirectional_range<X> rx(x);
		auto ret = ranges::inplace_merge(rx, ranges::next(rx.begin(), 3), {}, &X::i);
		VERIFY(ret == rx.end());
		int const y[] = {1,1,2,3,5,6};
		VERIFY(ranges::equal(x, y, {}, &X::i));
	}
	return true;
}

inline HAMON_CXX14_CONSTEXPR bool test03()
{
	namespace ranges = hamon::ranges;
	{
		int x[] = { 2,4,6,  1,3,5,7 };
		char y[] = { 'a','b','c', 'd','e','f','g' };
		auto rg = ranges::views::zip(x, y);
		ranges::inplace_merge(rg, ranges::next(rg.begin(), 3));
		VERIFY(hamon::get<0>(rg[0]) == 1);
		VERIFY(hamon::get<0>(rg[1]) == 2);
		VERIFY(hamon::get<0>(rg[2]) == 3);
		VERIFY(hamon::get<0>(rg[3]) == 4);
		VERIFY(hamon::get<0>(rg[4]) == 5);
		VERIFY(hamon::get<0>(rg[5]) == 6);
		VERIFY(hamon::get<0>(rg[6]) == 7);
		VERIFY(hamon::get<1>(rg[0]) == 'd');
		VERIFY(hamon::get<1>(rg[1]) == 'a');
		VERIFY(hamon::get<1>(rg[2]) == 'e');
		VERIFY(hamon::get<1>(rg[3]) == 'b');
		VERIFY(hamon::get<1>(rg[4]) == 'f');
		VERIFY(hamon::get<1>(rg[5]) == 'c');
		VERIFY(hamon::get<1>(rg[6]) == 'g');
	}
	return true;
}

#undef VERIFY

GTEST_TEST(AlgorithmTest, RangesInplaceMergeTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test03());
}

}	// namespace ranges_inplace_merge_test

}	// namespace hamon_algorithm_test
