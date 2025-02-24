﻿/**
 *	@file	unit_test_algorithm_ranges_fill.cpp
 *
 *	@brief	ranges::fill のテスト
 */

#include <hamon/algorithm/ranges/fill.hpp>
#include <hamon/algorithm/ranges/equal.hpp>
#include <hamon/iterator/ranges/next.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_algorithm_test
{

namespace ranges_fill_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool test01()
{
	namespace ranges = hamon::ranges;
	{
		int x[] = { 1, 2, 3, 4, 5, 6 };
		auto res = ranges::fill(x, x + 3, 17);
		VERIFY(res == ranges::next(x, 3));
		int const y[] = { 17, 17, 17, 4, 5, 6 };
		VERIFY(ranges::equal(x, y));
	}
	{
		int x[] = { 1, 2, 3, 4, 5 };
		test_output_range<int> rx(x);
		auto res = ranges::fill(rx, 18);
		VERIFY(res == rx.end());
		int const y[] = { 18, 18, 18, 18, 18 };
		VERIFY(ranges::equal(x, y));
	}
	return true;
}

struct X
{
	int i;
};

inline HAMON_CXX14_CONSTEXPR bool test02()
{
	namespace ranges = hamon::ranges;
	{
		X x[] = { {1}, {2}, {3}, {4}, {5} };
		auto res = ranges::fill(x, x + 3, X{ 17 });
		VERIFY(res == ranges::next(x, 3));
		int const y[] = { 17, 17, 17, 4, 5 };
		VERIFY(ranges::equal(x, y, {}, &X::i, {}));
	}
	{
		X x[] = { {1}, {2}, {3}, {4}, {5} };
		test_range<X, output_iterator_wrapper<X>> rx(x);
		auto res = ranges::fill(rx, X{ 18 });
		VERIFY(res == rx.end());
		int const y[] = { 18, 18, 18, 18, 18 };
		VERIFY(ranges::equal(x, y, {}, &X::i, {}));
	}
	return true;
}

struct Y { int i; int j; };

inline HAMON_CXX11_CONSTEXPR bool
operator==(Y const& lhs, Y const& rhs)
{
	return lhs.i == rhs.i && lhs.j == rhs.j;
}

inline HAMON_CXX14_CONSTEXPR bool test03()
{
	namespace ranges = hamon::ranges;
	{
		Y a[3]{};
		auto res = ranges::fill(ranges::begin(a), ranges::end(a), {10,20});
		VERIFY(res == ranges::end(a));
		VERIFY(a[0] == Y{10,20});
		VERIFY(a[1] == Y{10,20});
		VERIFY(a[2] == Y{10,20});
	}
	{
		Y a[3]{};
		auto res = ranges::fill(a, {10,20});
		VERIFY(res == ranges::end(a));
		VERIFY(a[0] == Y{10,20});
		VERIFY(a[1] == Y{10,20});
		VERIFY(a[2] == Y{10,20});
	}
	return true;
}

#undef VERIFY

GTEST_TEST(AlgorithmTest, RangesFillTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
#if defined(HAMON_GCC_VERSION) && (HAMON_GCC_VERSION < 100000)
	EXPECT_TRUE(test02());
#else
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
#endif
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test03());
}

}	// namespace ranges_fill_test

}	// namespace hamon_algorithm_test
