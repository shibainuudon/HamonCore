/**
 *	@file	unit_test_algorithm_ranges_replace.cpp
 *
 *	@brief	ranges::replace のテスト
 */

#include <hamon/algorithm/ranges/replace.hpp>
#include <hamon/algorithm/ranges/equal.hpp>
#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/end.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_algorithm_test
{

namespace ranges_replace_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool test01()
{
	namespace ranges = hamon::ranges;
	{
		int x[] = { 3,1,4,1,5 };
		auto res = ranges::replace(x, x+5, 1, 0);
		VERIFY(res == x+5);
		int y[] = { 3,0,4,0,5 };
		VERIFY(ranges::equal(x, y));
	}
	return true;
}

inline HAMON_CXX14_CONSTEXPR bool test02()
{
	namespace ranges = hamon::ranges;
	{
		int x[] = { 1,3,1,4,1,5,1 };
		test_input_range<int> rx(x);
		auto res = ranges::replace(rx, 1, 0);
		VERIFY(res == rx.end());
		int y[] = { 0,3,0,4,0,5,0 };
		VERIFY(ranges::equal(x, y));
	}
	return true;
}

struct X
{
	int i;

	friend HAMON_CXX14_CONSTEXPR bool
	operator==(const X& a, const X& b)
	{
		return a.i == b.i;
	}

	friend HAMON_CXX14_CONSTEXPR bool
	operator!=(const X& a, const X& b)
	{
		return !(a == b);
	}
};

struct Y
{
	int i;
	int j;

	friend HAMON_CXX14_CONSTEXPR bool
	operator==(const Y& a, const Y& b)
	{
		return a.i == b.i && a.j == b.j;
	}

	friend HAMON_CXX14_CONSTEXPR bool
	operator!=(const Y& a, const Y& b)
	{
		return !(a == b);
	}
};

inline HAMON_CXX14_CONSTEXPR bool test03()
{
	namespace ranges = hamon::ranges;
	{
		X x[6] = { {2}, {2}, {6}, {8}, {10}, {8} };
		auto res = ranges::replace(ranges::begin(x), ranges::begin(x) + 5, 8, X{9}, &X::i);
		VERIFY(res == ranges::begin(x) + 5);
		X y[6] = { {2}, {2}, {6}, {9}, {10}, {8} };
		VERIFY(ranges::equal(x, y));
	}
	return true;
}

inline HAMON_CXX14_CONSTEXPR bool test04()
{
	namespace ranges = hamon::ranges;
	{
		Y x[] = { {3,2}, {2,4}, {3,6} };
		auto res = ranges::replace(x, 3, Y{4,5}, &Y::i);
		VERIFY(res == ranges::end(x));
		Y y[] = { {4,5}, {2,4}, {4,5} };
		VERIFY(ranges::equal(x, y));
	}
	return true;
}

inline HAMON_CXX14_CONSTEXPR bool test05()
{
	namespace ranges = hamon::ranges;
	{
		X x[6] = { {2}, {2}, {6}, {8}, {10}, {8} };
		auto res = ranges::replace(ranges::begin(x), ranges::end(x), {6}, {0});
		VERIFY(res == ranges::end(x));
		X y[6] = { {2}, {2}, {0}, {8}, {10}, {8} };
		VERIFY(ranges::equal(x, y));
	}
	return true;
}

inline HAMON_CXX14_CONSTEXPR bool test06()
{
	namespace ranges = hamon::ranges;
	{
		Y x[] = { {3,2}, {2,4}, {3,6} };
		auto res = ranges::replace(x, {2,4}, {4,5});
		VERIFY(res == ranges::end(x));
		Y y[] = { {3,2}, {4,5}, {3,6} };
		VERIFY(ranges::equal(x, y));
	}
	return true;
}

#undef VERIFY

GTEST_TEST(AlgorithmTest, RangesReplaceTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
#if defined(HAMON_GCC_VERSION) && (HAMON_GCC_VERSION < 100000)
	EXPECT_TRUE(test03());
	EXPECT_TRUE(test04());
#else
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test03());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test04());
#endif
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test05());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test06());
}

}	// namespace ranges_replace_test

}	// namespace hamon_algorithm_test
