/**
 *	@file	unit_test_algorithm_ranges_remove.cpp
 *
 *	@brief	ranges::remove のテスト
 */

#include <hamon/algorithm/ranges/remove.hpp>
#include <hamon/algorithm/ranges/equal.hpp>
#include <hamon/iterator/ranges/next.hpp>
#include <hamon/forward_list.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_algorithm_test
{

namespace ranges_remove_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool test01()
{
	namespace ranges = hamon::ranges;
	{
		int x[] = { 1, 2, 3, 4, 5 };
		auto res = ranges::remove(x, x+5, 3);
		VERIFY(res.begin() == x+4 && res.end() == x+5);
		const int y[] = { 1, 2, 4, 5 };
		VERIFY(ranges::equal(x, x+4, y, y+4));
	}
	{
		int x[] = { 1, 2, 3, 4, 5 };
		test_forward_range<int> rx(x);
		auto res = ranges::remove(rx, 2);
		VERIFY(res.begin() == ranges::next(rx.begin(), 4));
		VERIFY(res.end()   == rx.end());
		const int y[] = { 1, 3, 4, 5 };
		VERIFY(ranges::equal(x, x+4, y, y+4));
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
		X x[] = { {0}, {1}, {0}, {0}, {2}, {3}, {0}, {0}, {0} };
		auto res = ranges::remove(x, x+9, 0, &X::i);
		VERIFY(res.begin() == x+3 && res.end() == x+9);
		const int y[] = { 1, 2, 3 };
		VERIFY(ranges::equal(x, x+3, y, y+3, {}, &X::i));
	}
	{
		X x[] = { {1}, {2}, {3} };
		test_forward_range<X> rx(x);
		auto res = ranges::remove(rx, 0, &X::i);
		VERIFY(res.begin() == rx.end());
		VERIFY(res.end()   == rx.end());
		const int y[] = { 1, 2, 3 };
		VERIFY(ranges::equal(x, x+3, y, y+3, {}, &X::i));
	}
	return true;
}

struct Y { int i; int j; };

inline HAMON_CXX11_CONSTEXPR bool
operator==(Y const& lhs, Y const& rhs)
{
	return lhs.i == rhs.i && lhs.j == rhs.j;
}

inline HAMON_CXX11_CONSTEXPR bool
operator!=(Y const& lhs, Y const& rhs)
{
	return !(lhs == rhs);
}

inline HAMON_CXX14_CONSTEXPR bool test03()
{
	namespace ranges = hamon::ranges;
	{
		Y x[] = { {1,3}, {1,2}, {1,2}, {3,2}, {1,2}, };
		auto res = ranges::remove(x, x+5, {1,2});
		VERIFY(res.begin() == x+2 && res.end() == x+5);
		VERIFY(x[0] == Y{1,3});
		VERIFY(x[1] == Y{3,2});
	}
	{
		Y x[] = { {1,3}, {1,2}, {1,2}, {3,2}, {1,2}, };
		auto res = ranges::remove(x, {1,2});
		VERIFY(res.begin() == x+2 && res.end() == x+5);
		VERIFY(x[0] == Y{1,3});
		VERIFY(x[1] == Y{3,2});
	}
	return true;
}

#undef VERIFY

GTEST_TEST(AlgorithmTest, RangesRemoveTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
#if defined(HAMON_GCC_VERSION) && (HAMON_GCC_VERSION < 100000)
	EXPECT_TRUE(test02());
#else
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
#endif
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test03());

	{
		hamon::forward_list<int> x = {};
		auto res = hamon::ranges::remove(x, 0);
		EXPECT_TRUE(res.begin() == x.end());
		EXPECT_TRUE(res.end()   == x.end());
	}
}

}	// namespace ranges_remove_test

}	// namespace hamon_algorithm_test
