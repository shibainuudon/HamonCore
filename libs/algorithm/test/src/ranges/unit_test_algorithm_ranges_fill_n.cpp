/**
 *	@file	unit_test_algorithm_ranges_fill_n.cpp
 *
 *	@brief	ranges::fill_n のテスト
 */

#include <hamon/algorithm/ranges/fill_n.hpp>
#include <hamon/algorithm/ranges/equal.hpp>
#include <hamon/iterator/ranges/next.hpp>
#include <hamon/vector.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_algorithm_test
{

namespace ranges_fill_n_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool test01()
{
	namespace ranges = hamon::ranges;
	{
		int x[] = { 1, 2, 3, 4, 5, 6 };
		auto res = ranges::fill_n(x, 3, 17);
		VERIFY(res == ranges::next(x, 3));
		int const y[] = { 17, 17, 17, 4, 5, 6 };
		VERIFY(ranges::equal(x, y));
	}
	{
		int x[] = { 1, 2, 3, 4, 5, 6 };
		auto res = ranges::fill_n(x, -1, 17);
		VERIFY(res == x);
		int const y[] = { 1, 2, 3, 4, 5, 6 };
		VERIFY(ranges::equal(x, y));
	}
	{
		int x[] = { 1, 2, 3, 4, 5, 6 };
		test_output_range<int> rx(x);
		auto res = ranges::fill_n(rx.begin(), 3, 17);
		VERIFY(res.m_ptr == ranges::next(x, 3));
		int const y[] = { 17, 17, 17, 4, 5, 6 };
		VERIFY(ranges::equal(x, y));
	}
	return true;
}

struct X
{
	int i;
};

inline bool test02()
{
	namespace ranges = hamon::ranges;
	{
		X x[6] = { {1}, {2}, {3}, {4}, {5}, {6} };
		auto res = ranges::fill_n(x, 3, X{ 17 });
		VERIFY(res == ranges::next(x, 3));
		int const y[] = { 17, 17, 17, 4, 5, 6 };
		VERIFY(ranges::equal(x, y, {}, &X::i, {}));
	}
	{
		hamon::vector<int> x(5);
		auto res = ranges::fill_n(x.begin(), 2, 42);
		VERIFY(res == ranges::next(x.begin(), 2));
		int const y[] = { 42, 42, 0, 0, 0 };
		VERIFY(ranges::equal(x, y));
	}
	return true;
}

#undef VERIFY

GTEST_TEST(AlgorithmTest, RangesFillNTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	EXPECT_TRUE(test02());
}

}	// namespace ranges_fill_n_test

}	// namespace hamon_algorithm_test
