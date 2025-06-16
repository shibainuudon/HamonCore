/**
 *	@file	unit_test_algorithm_ranges_stable_sort.cpp
 *
 *	@brief	ranges::stable_sort のテスト
 */

#include <hamon/algorithm/ranges/stable_sort.hpp>
#include <hamon/algorithm/ranges/equal.hpp>
#include <hamon/functional/ranges/greater.hpp>
#include <hamon/ranges/adaptors/zip_view.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_algorithm_test
{

namespace ranges_stable_sort_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool test01()
{
	namespace ranges = hamon::ranges;
	{
		int x[] = {3,1,4,1,5,9,2};
		test_random_access_range<int> rx(x);
		auto ret = ranges::stable_sort(rx);
		VERIFY(ret == rx.end());
		int y[] = {1,1,2,3,4,5,9};
		VERIFY(ranges::equal(x, y));
	}
	{
		int x[] = {3,1,4,1,5,9,2};
		test_random_access_range<int> rx(x);
		auto ret = ranges::stable_sort(rx, ranges::greater{});
		VERIFY(ret == rx.end());
		int y[] = {9,5,4,3,2,1,1};
		VERIFY(ranges::equal(x, y));
	}
	return true;
}

struct Foo
{
	int key;
	float value;
};

inline HAMON_CXX14_CONSTEXPR bool test02()
{
	namespace ranges = hamon::ranges;
	{
		Foo x[] =
		{
			{ 3, 0.5f },
			{ 1, 1.5f },
			{ 4, 2.5f },
			{ 1, 3.5f },
			{ 5, 4.5f },
			{ 9, 5.5f },
			{ 2, 6.5f },
			{ 6, 7.5f },
			{ 5, 8.5f },
			{ 3, 9.5f },
		};
		test_random_access_range<Foo> rx(x);
		auto ret = ranges::stable_sort(rx, {}, &Foo::key);
		VERIFY(ret == rx.end());
		VERIFY(1.5 == x[0].value);
		VERIFY(3.5 == x[1].value);
		VERIFY(6.5 == x[2].value);
		VERIFY(0.5 == x[3].value);
		VERIFY(9.5 == x[4].value);
		VERIFY(2.5 == x[5].value);
		VERIFY(4.5 == x[6].value);
		VERIFY(8.5 == x[7].value);
		VERIFY(7.5 == x[8].value);
		VERIFY(5.5 == x[9].value);
	}
	return true;
}

inline HAMON_CXX14_CONSTEXPR bool test03()
{
	namespace ranges = hamon::ranges;
	{
		int  x[] = { 4,  2,  2,  3,  1,  4,  4 };
		char y[] = {'a','b','c','d','e','f','g'};
		auto rg = ranges::views::zip(x, y);
		ranges::stable_sort(rg);
		VERIFY(hamon::get<0>(rg[0]) == 1);
		VERIFY(hamon::get<0>(rg[1]) == 2);
		VERIFY(hamon::get<0>(rg[2]) == 2);
		VERIFY(hamon::get<0>(rg[3]) == 3);
		VERIFY(hamon::get<0>(rg[4]) == 4);
		VERIFY(hamon::get<0>(rg[5]) == 4);
		VERIFY(hamon::get<0>(rg[6]) == 4);
		VERIFY(hamon::get<1>(rg[0]) == 'e');
		VERIFY(hamon::get<1>(rg[1]) == 'b');
		VERIFY(hamon::get<1>(rg[2]) == 'c');
		VERIFY(hamon::get<1>(rg[3]) == 'd');
		VERIFY(hamon::get<1>(rg[4]) == 'a');
		VERIFY(hamon::get<1>(rg[5]) == 'f');
		VERIFY(hamon::get<1>(rg[6]) == 'g');
	}
	return true;
}

#undef VERIFY

GTEST_TEST(AlgorithmTest, RangesStableSortTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test03());
}

}	// namespace ranges_stable_sort_test

}	// namespace hamon_algorithm_test
