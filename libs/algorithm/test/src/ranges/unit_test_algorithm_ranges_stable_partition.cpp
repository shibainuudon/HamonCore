/**
 *	@file	unit_test_algorithm_ranges_stable_partition.cpp
 *
 *	@brief	ranges::stable_partition のテスト
 */

#include <hamon/algorithm/ranges/stable_partition.hpp>
#include <hamon/algorithm/ranges/equal.hpp>
#include <hamon/iterator/ranges/next.hpp>
#include <hamon/ranges/adaptors/zip_view.hpp>
#include <hamon/list.hpp>
#include <hamon/vector.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_algorithm_test
{

namespace ranges_stable_partition_test
{

HAMON_CONSTEXPR bool is_even(int x)
{
	return (x % 2) == 0;
}

HAMON_CONSTEXPR bool is_odd(int x)
{
	return (x % 2) == 1;
}

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool test01()
{
	namespace ranges = hamon::ranges;
	{
		int x[] = {1,2,3,4,5};
		test_bidirectional_range<int> rx(x);
		auto ret = ranges::stable_partition(rx, is_even);
		VERIFY(ret.begin() == ranges::next(rx.begin(), 2));
		VERIFY(ret.end()   == rx.end());
		int const y[] = {2,4,1,3,5};
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
			{ 3, 9.5f },
			{ 1, 8.5f },
			{ 4, 7.5f },
			{ 1, 6.5f },
			{ 5, 5.5f },
			{ 9, 4.5f },
			{ 2, 3.5f },
			{ 6, 2.5f },
			{ 5, 1.5f },
			{ 3, 0.5f },
		};
		test_bidirectional_range<Foo> rx(x);
		auto ret = ranges::stable_partition(rx, is_odd, &Foo::key);
		VERIFY(ret.begin() == ranges::next(rx.begin(), 7));
		VERIFY(ret.end()   == rx.end());
		VERIFY(3 == x[0].key);
		VERIFY(1 == x[1].key);
		VERIFY(1 == x[2].key);
		VERIFY(5 == x[3].key);
		VERIFY(9 == x[4].key);
		VERIFY(5 == x[5].key);
		VERIFY(3 == x[6].key);
		VERIFY(4 == x[7].key);
		VERIFY(2 == x[8].key);
		VERIFY(6 == x[9].key);
		VERIFY(9.5f == x[0].value);
		VERIFY(8.5f == x[1].value);
		VERIFY(6.5f == x[2].value);
		VERIFY(5.5f == x[3].value);
		VERIFY(4.5f == x[4].value);
		VERIFY(1.5f == x[5].value);
		VERIFY(0.5f == x[6].value);
		VERIFY(7.5f == x[7].value);
		VERIFY(3.5f == x[8].value);
		VERIFY(2.5f == x[9].value);
	}
	return true;
}

inline bool test03()
{
	namespace ranges = hamon::ranges;
	{
		hamon::vector<int> x = {1,2,3,4,5};
		auto ret = ranges::stable_partition(x, is_even);
		VERIFY(ret.begin() == ranges::next(x.begin(), 2));
		VERIFY(ret.end()   == x.end());
		int const y[] = {2,4,1,3,5};
		VERIFY(ranges::equal(x, y));
	}
	return true;
}

inline bool test04()
{
	namespace ranges = hamon::ranges;
	{
		hamon::list<int> x = {3,1,4,1,5,9,2,6,5};
		auto ret = ranges::stable_partition(x, [](int a) { return a > 3;});
		VERIFY(ret.begin() == ranges::next(x.begin(), 5));
		VERIFY(ret.end()   == x.end());
		int const y[] = {4,5,9,6,5,3,1,1,2};
		VERIFY(ranges::equal(x, y));
	}
	return true;
}

inline HAMON_CXX14_CONSTEXPR bool test05()
{
	namespace ranges = hamon::ranges;
	{
		struct Pred
		{
			constexpr bool operator()(hamon::tuple<int, char> const& t) const
			{
				return hamon::get<0>(t) > 3;
			}
		};

		int  x[] = { 4,  2,  2,  5,  3,  1,  4 };
		char y[] = {'a','b','c','d','e','f','g'};
		auto rg = ranges::views::zip(x, y);
		auto ret = ranges::stable_partition(rg, Pred{});
		VERIFY(ret.begin() == ranges::next(rg.begin(), 3));
		VERIFY(ret.end()   == rg.end());
		VERIFY(hamon::get<0>(rg[0]) == 4);
		VERIFY(hamon::get<0>(rg[1]) == 5);
		VERIFY(hamon::get<0>(rg[2]) == 4);
		VERIFY(hamon::get<0>(rg[3]) == 2);
		VERIFY(hamon::get<0>(rg[4]) == 2);
		VERIFY(hamon::get<0>(rg[5]) == 3);
		VERIFY(hamon::get<0>(rg[6]) == 1);
		VERIFY(hamon::get<1>(rg[0]) == 'a');
		VERIFY(hamon::get<1>(rg[1]) == 'd');
		VERIFY(hamon::get<1>(rg[2]) == 'g');
		VERIFY(hamon::get<1>(rg[3]) == 'b');
		VERIFY(hamon::get<1>(rg[4]) == 'c');
		VERIFY(hamon::get<1>(rg[5]) == 'e');
		VERIFY(hamon::get<1>(rg[6]) == 'f');
	}
	return true;
}

#undef VERIFY

GTEST_TEST(AlgorithmTest, RangesStablePartitionTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
	EXPECT_TRUE(test03());
	EXPECT_TRUE(test04());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test05());
}

}	// namespace ranges_stable_partition_test

}	// namespace hamon_algorithm_test
