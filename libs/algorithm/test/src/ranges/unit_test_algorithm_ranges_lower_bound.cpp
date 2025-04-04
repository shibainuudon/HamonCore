﻿/**
 *	@file	unit_test_algorithm_ranges_lower_bound.cpp
 *
 *	@brief	ranges::lower_bound のテスト
 */

#include <hamon/algorithm/ranges/lower_bound.hpp>
#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/end.hpp>
#include <hamon/cstddef/ptrdiff_t.hpp>
#include <hamon/iterator/ranges/next.hpp>
#include <hamon/functional/ranges/greater.hpp>
#include <hamon/forward_list.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_algorithm_test
{

namespace ranges_lower_bound_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool test01()
{
	namespace ranges = hamon::ranges;
	for (int i = 0; i < 8; ++i)
	{
		int x[] = {0,1,2,3,4,5,6,7};
		test_forward_range<int> r(x);
		auto res = ranges::lower_bound(r, i);
		VERIFY(res == ranges::next(r.begin(), i));
	}
	for (int i = 0; i < 8; ++i)
	{
		int x[] = {7,6,5,4,3,2,1,0};
		test_forward_range<int> r(x);
		auto res = ranges::lower_bound(r, i, ranges::greater{});
		VERIFY(res == ranges::next(r.begin(), hamon::ptrdiff_t(7) - i));
	}
	{
		int x[] = {0,0,1,1,1,2,2,2,2};
		auto res = ranges::lower_bound(x, 0);
		VERIFY(res == ranges::next(x, 0));
	}
	{
		int x[] = {0,0,1,1,1,2,2,2,2};
		auto res = ranges::lower_bound(x, 1);
		VERIFY(res == ranges::next(x, 2));
	}
	{
		int x[] = {0,0,1,1,1,2,2,2,2};
		auto res = ranges::lower_bound(x, 2);
		VERIFY(res == ranges::next(x, 5));
	}
	{
		int x[] = {0,1,2,3,4,5,6,7};
		auto res = ranges::lower_bound(x, 9);
		VERIFY(res == ranges::next(x, 8));
	}
	{
		int x[] = {7,6,5,4,3,2,1,0};
		auto res = ranges::lower_bound(x, -1, ranges::greater{});
		VERIFY(res == ranges::next(x, 8));
	}
	{
		int x[] = {0,1,2,3,4,5,6,7};
		auto res = ranges::lower_bound(x, x, 5);
		VERIFY(res == ranges::next(x, 0));
	}
	{
		int x[] = {7,6,5,4,3,2,1,0};
		auto res = ranges::lower_bound(x, x, 5, ranges::greater{});
		VERIFY(res == ranges::next(x, 0));
	}
	return true;
}

struct X
{
	int i;
};

inline HAMON_CXX11_CONSTEXPR bool
operator==(X const& lhs, X const& rhs)
{
	return lhs.i == rhs.i;
}
inline HAMON_CXX11_CONSTEXPR bool
operator!=(X const& lhs, X const& rhs)
{
	return lhs.i != rhs.i;
}
inline HAMON_CXX11_CONSTEXPR bool
operator<(X const& lhs, X const& rhs)
{
	return lhs.i < rhs.i;
}
inline HAMON_CXX11_CONSTEXPR bool
operator>(X const& lhs, X const& rhs)
{
	return lhs.i > rhs.i;
}
inline HAMON_CXX11_CONSTEXPR bool
operator<=(X const& lhs, X const& rhs)
{
	return lhs.i <= rhs.i;
}
inline HAMON_CXX11_CONSTEXPR bool
operator>=(X const& lhs, X const& rhs)
{
	return lhs.i >= rhs.i;
}

inline HAMON_CXX14_CONSTEXPR bool test02()
{
	namespace ranges = hamon::ranges;
	{
		X const x[] = { {0},{1},{1},{2},{2},{2},{4} };
		VERIFY(ranges::lower_bound(x, 0, {}, &X::i) == ranges::next(x, 0));
		VERIFY(ranges::lower_bound(x, 1, {}, &X::i) == ranges::next(x, 1));
		VERIFY(ranges::lower_bound(x, 2, {}, &X::i) == ranges::next(x, 3));
		VERIFY(ranges::lower_bound(x, 3, {}, &X::i) == ranges::next(x, 6));
		VERIFY(ranges::lower_bound(x, 4, {}, &X::i) == ranges::next(x, 6));
		VERIFY(ranges::lower_bound(x, 5, {}, &X::i) == ranges::next(x, 7));
	}
	{
		auto pred = ranges::greater{};
		X const x[] = { {5},{5},{5},{4},{3},{2},{1} };
		VERIFY(ranges::lower_bound(x, 6, pred, &X::i) == ranges::next(x, 0));
		VERIFY(ranges::lower_bound(x, 5, pred, &X::i) == ranges::next(x, 0));
		VERIFY(ranges::lower_bound(x, 4, pred, &X::i) == ranges::next(x, 3));
		VERIFY(ranges::lower_bound(x, 3, pred, &X::i) == ranges::next(x, 4));
		VERIFY(ranges::lower_bound(x, 2, pred, &X::i) == ranges::next(x, 5));
		VERIFY(ranges::lower_bound(x, 1, pred, &X::i) == ranges::next(x, 6));
		VERIFY(ranges::lower_bound(x, 0, pred, &X::i) == ranges::next(x, 7));
	}
	return true;
}

inline HAMON_CXX14_CONSTEXPR bool test03()
{
	namespace ranges = hamon::ranges;
	{
		X const x[] = { {0},{1},{1},{2},{2},{2},{4} };
		VERIFY(ranges::lower_bound(ranges::begin(x), ranges::end(x), {0}) == ranges::next(x, 0));
		VERIFY(ranges::lower_bound(ranges::begin(x), ranges::end(x), {1}) == ranges::next(x, 1));
		VERIFY(ranges::lower_bound(ranges::begin(x), ranges::end(x), {2}) == ranges::next(x, 3));
		VERIFY(ranges::lower_bound(ranges::begin(x), ranges::end(x), {3}) == ranges::next(x, 6));
		VERIFY(ranges::lower_bound(ranges::begin(x), ranges::end(x), {4}) == ranges::next(x, 6));
		VERIFY(ranges::lower_bound(ranges::begin(x), ranges::end(x), {5}) == ranges::next(x, 7));
		VERIFY(ranges::lower_bound(x, {0}) == ranges::next(x, 0));
		VERIFY(ranges::lower_bound(x, {1}) == ranges::next(x, 1));
		VERIFY(ranges::lower_bound(x, {2}) == ranges::next(x, 3));
		VERIFY(ranges::lower_bound(x, {3}) == ranges::next(x, 6));
		VERIFY(ranges::lower_bound(x, {4}) == ranges::next(x, 6));
		VERIFY(ranges::lower_bound(x, {5}) == ranges::next(x, 7));
	}
	return true;
}

#undef VERIFY

GTEST_TEST(AlgorithmTest, RangesLowerBoundTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
#if defined(HAMON_GCC_VERSION) && (HAMON_GCC_VERSION < 100000)
	EXPECT_TRUE(test02());
#else
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
#endif
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test03());

	{
		hamon::forward_list<int> x {};
		EXPECT_TRUE(hamon::ranges::lower_bound(x, 0) == x.end());
	}
}

}	// namespace ranges_lower_bound_test

}	// namespace hamon_algorithm_test
