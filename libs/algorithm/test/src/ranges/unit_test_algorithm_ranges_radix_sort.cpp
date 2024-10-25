/**
 *	@file	unit_test_algorithm_ranges_radix_sort.cpp
 *
 *	@brief	ranges::radix_sort のテスト
 */

#include <hamon/algorithm/ranges/radix_sort.hpp>
#include <hamon/algorithm/ranges/equal.hpp>
#include <hamon/algorithm/ranges/is_sorted.hpp>
#include <hamon/algorithm/ranges/sort.hpp>
#include <hamon/cstddef.hpp>
#include <hamon/string.hpp>
#include <hamon/vector.hpp>
#include <hamon/random.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include <chrono>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_algorithm_test
{

namespace ranges_radix_sort_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool test01()
{
	namespace ranges = hamon::ranges;
	{
		unsigned char x[] = { 3,1,4,1,5,9,2,6 };
		unsigned char tmp[64]{};
		auto res = ranges::radix_sort(x + 0, x + 8, tmp);
		VERIFY(res == x + 8);
		unsigned char const y[] = { 1,1,2,3,4,5,6,9 };
		VERIFY(ranges::equal(x, y));
	}
	{
		unsigned short x[] = { 5,1,3,5,5,2,5,1,5,1, };
		unsigned short tmp[64]{};
		auto res = ranges::radix_sort(x, tmp);
		VERIFY(res == x + 10);
		unsigned short const y[] = { 1,1,1,2,3,5,5,5,5,5, };
		VERIFY(ranges::equal(x, y));
	}
	{
		unsigned int x[] =
		{
			96580, 71212, 93844,  8683, 51070, 63008, 30816, 56650,
			 2872,  1799, 48614, 74299, 94453, 65547, 17404, 91217,
		};
		test_random_access_range<unsigned int> r(x);
		unsigned int tmp[64]{};
		auto res = ranges::radix_sort(r, tmp);
		VERIFY(res == r.end());
		unsigned int const y[] =
		{
			 1799,  2872,  8683, 17404, 30816, 48614, 51070, 56650,
			63008, 65547, 71212, 74299, 91217, 93844, 94453, 96580,
		};
		VERIFY(ranges::equal(x, y));
	}
	{
		unsigned long long x[] =
		{
			76813, 2398,37548,37796,17013,70225,67808, 6876, 1838,62903,
			91810,95592,64844,67240,42143,95681,69405,39267,80218,10788,
		};
		unsigned long long tmp[64]{};
		auto res = ranges::radix_sort(x, tmp);
		VERIFY(res == x + 20);
		unsigned long long const y[] =
		{
			 1838, 2398, 6876,10788,17013,37548,37796,39267,42143,62903,
			64844,67240,67808,69405,70225,76813,80218,91810,95592,95681,
		};
		VERIFY(ranges::equal(x, y));
	}
	return true;
}

struct X
{
	unsigned int	index;
	hamon::string	name;

	bool operator==(X const& rhs) const
	{
		return index == rhs.index &&
			name == rhs.name;
	}
	bool operator!=(X const& rhs) const
	{
		return !(*this == rhs);
	}
};

inline bool test02()
{
	namespace ranges = hamon::ranges;
	{
		X x[] =
		{
			{3, "Alice"},
			{4, "Bob"},
			{2, "Carol"},
			{1, "Dave"},
			{5, "Eve"},
		};
		X tmp[5];
		auto res = ranges::radix_sort(x, tmp, &X::index);
		VERIFY(res == x + 5);
		X const y[] =
		{
			{1, "Dave"},
			{2, "Carol"},
			{3, "Alice"},
			{4, "Bob"},
			{5, "Eve"},
		};
		VERIFY(ranges::equal(x, y));
	}
	{
		X x[] =
		{
			{200, "Alice"},
			{100, "Bob"},
			{200, "Carol"},
			{100, "Dave"},
			{100, "Eve"},
		};
		test_random_access_range<X> r(x);
		X tmp[5];
		auto res = ranges::radix_sort(r, tmp, &X::index);
		VERIFY(res == r.end());
		X const y[] =
		{
			{100, "Bob"},
			{100, "Dave"},
			{100, "Eve"},
			{200, "Alice"},
			{200, "Carol"},
		};
		VERIFY(ranges::equal(x, y));
	}
	{
		hamon::mt19937 rng;
		unsigned int const min = 0;
		unsigned int const max = 0xFFFFFFFF;
		hamon::uniform_int_distribution<unsigned int> dist(min, max);
		hamon::size_t const n = 100;
		hamon::vector<unsigned int> v(n);
		for (auto& x : v)
		{
			x = dist(rng);
		}
		hamon::vector<unsigned int> tmp(n);
		ranges::radix_sort(v, tmp.begin());
		VERIFY(ranges::is_sorted(v));
	}
	return true;
}

#undef VERIFY

GTEST_TEST(AlgorithmTest, RangesRadixSortTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	EXPECT_TRUE(test02());

#if 0
	namespace ranges = hamon::ranges;
	{
		std::size_t const n_tbl[] =
		{
			10,
			100,
			1000,
			10000,
			100000,
			1000000,
			10000000,
			100000000,
			//1000000000,
		};

		unsigned int const max_tbl[] =
		{
			10,
			100,
			10000,
			1000000,
			//100000000,
		};

		enum SortAlgo
		{
			StdSort,
			RadixSort,
		};

		SortAlgo const algo_tbl[] = {StdSort, RadixSort};

		hamon::mt19937 rng;

		for (auto algo : algo_tbl)
		{
			std::cout << ((algo == StdSort) ? "sort" : "radix_sort") << ":" << std::endl;
			for (auto max : max_tbl)
			{
				unsigned int const min = 0;
				std::cout << "distribution(" << min << ", " << max << "):" << std::endl;
				for (auto n : n_tbl)
				{
					hamon::uniform_int_distribution<unsigned int> dist(min, max);
					hamon::vector<unsigned int> v(n);
					for (auto& x : v)
					{
						x = dist(rng);
					}
					hamon::vector<unsigned int> tmp(n);

					{
						auto t1 = std::chrono::high_resolution_clock::now();

						if (algo == StdSort)
						{
							ranges::sort(v);
						}
						else
						{
							ranges::radix_sort(v, tmp.begin());
						}

						auto t2 = std::chrono::high_resolution_clock::now();
						auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
						std::cout << std::right << std::setw(10);
						std::cout << n << ": " << elapsed_time.count() << " ms"<< std::endl;
					}

					EXPECT_TRUE(ranges::is_sorted(v));
				}
			}

			std::cout << std::endl;
		}
	}
#endif
}

}	// namespace ranges_radix_sort_test

}	// namespace hamon_algorithm_test
