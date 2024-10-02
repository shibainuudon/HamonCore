/**
 *	@file	unit_test_algorithm_ranges_remove_copy.cpp
 *
 *	@brief	ranges::remove_copy のテスト
 */

#include <hamon/algorithm/ranges/remove_copy.hpp>
#include <hamon/algorithm/ranges/equal.hpp>
#include <hamon/iterator/ranges/next.hpp>
#include <hamon/forward_list.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_algorithm_test
{

namespace ranges_remove_copy_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool test01()
{
	namespace ranges = hamon::ranges;
	{
		int const x[] = { 1, 2, 3, 4, 5 };
		int w[5] = {};
		auto res = ranges::remove_copy(x, x+5, w, 3);
		VERIFY(res.in  == x+5);
		VERIFY(res.out == w+4);
		const int y[] = { 1, 2, 4, 5 };
		VERIFY(ranges::equal(w, w+4, y, y+4));
	}
	{
		int const x[] = { 1, 2, 3, 4, 5 };
		test_forward_range<int const> rx(x);
		int w[5] = {};
		auto res = ranges::remove_copy(rx, w, 2);
		VERIFY(res.in  == rx.end());
		VERIFY(res.out == w+4);
		const int y[] = { 1, 3, 4, 5 };
		VERIFY(ranges::equal(w, w+4, y, y+4));
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
		X const x[] = { {0}, {1}, {0}, {0}, {2}, {3}, {0}, {0}, {0} };
		X w[3] = {};
		auto res = ranges::remove_copy(x, x+9, w, 0, &X::i);
		VERIFY(res.in  == x+9);
		VERIFY(res.out == w+3);
		const int y[] = { 1, 2, 3 };
		VERIFY(ranges::equal(w, w+3, y, y+3, {}, &X::i));
	}
	{
		X x[] = { {1}, {2}, {3} };
		test_forward_range<X> rx(x);
		X w[3] = {};
		auto res = ranges::remove_copy(rx, w, 0, &X::i);
		VERIFY(res.in  == rx.end());
		VERIFY(res.out == w+3);
		const int y[] = { 1, 2, 3 };
		VERIFY(ranges::equal(w, w+3, y, y+3, {}, &X::i));
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
		Y const x[] = { {1,3}, {1,2}, {1,2}, {3,2}, {1,2}, };
		Y w[3] = {};
		auto res = ranges::remove_copy(x, x+5, w, {1,2});
		VERIFY(res.in  == x+5);
		VERIFY(res.out == w+2);
		VERIFY(w[0] == Y{1,3});
		VERIFY(w[1] == Y{3,2});
	}
	{
		Y const x[] = { {1,3}, {1,2}, {1,2}, {3,2}, {1,2}, };
		Y w[3] = {};
		auto res = ranges::remove_copy(x, w, {1,2});
		VERIFY(res.in  == x+5);
		VERIFY(res.out == w+2);
		VERIFY(w[0] == Y{1,3});
		VERIFY(w[1] == Y{3,2});
	}
	return true;
}

#undef VERIFY

GTEST_TEST(AlgorithmTest, RangesRemoveCopyTest)
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
		int w[3] = {};
		auto res = hamon::ranges::remove_copy(x, w, 0);
		EXPECT_TRUE(res.in  == x.end());
		EXPECT_TRUE(res.out == w+0);
	}
}

}	// namespace ranges_remove_copy_test

}	// namespace hamon_algorithm_test
