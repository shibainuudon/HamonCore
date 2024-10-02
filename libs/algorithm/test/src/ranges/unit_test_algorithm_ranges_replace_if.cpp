/**
 *	@file	unit_test_algorithm_ranges_replace_if.cpp
 *
 *	@brief	ranges::replace_if のテスト
 */

#include <hamon/algorithm/ranges/replace_if.hpp>
#include <hamon/algorithm/ranges/equal.hpp>
#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/end.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_algorithm_test
{

namespace ranges_replace_if_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <int N>
struct Less
{
	HAMON_CXX11_CONSTEXPR bool operator()(int x) const
	{
		return x < N;
	}
};

template <int N>
struct Greater
{
	HAMON_CXX11_CONSTEXPR bool operator()(int x) const
	{
		return x > N;
	}
};

inline HAMON_CXX14_CONSTEXPR bool test01()
{
	namespace ranges = hamon::ranges;
	{
		int x[] = { 1,2,3,4,5,6,7,8,9 };
		auto res = ranges::replace_if(x, x+9, Less<5>{}, 0);
		VERIFY(res == x+9);
		int y[] = { 0,0,0,0,5,6,7,8,9 };
		VERIFY(ranges::equal(x, y));
	}
	{
		int x[] = { 1,2,3,4,5,6,7,8,9 };
		auto res = ranges::replace_if(x, x+9, Greater<5>{}, 1);
		VERIFY(res == x+9);
		int y[] = { 1,2,3,4,5,1,1,1,1 };
		VERIFY(ranges::equal(x, y));
	}
	return true;
}

inline HAMON_CXX14_CONSTEXPR bool test02()
{
	namespace ranges = hamon::ranges;
	{
		int x[] = { 3,1,4,1,5,9,2,6,5 };
		test_input_range<int> rx(x);
		auto res = ranges::replace_if(rx, Less<5>{}, 0);
		VERIFY(res == rx.end());
		int y[] = { 0,0,0,0,5,9,0,6,5 };
		VERIFY(ranges::equal(x, y));
	}
	{
		int x[] = { 3,1,4,1,5,9,2,6,5 };
		test_input_range<int> rx(x);
		auto res = ranges::replace_if(rx, Greater<3>{}, 8);
		VERIFY(res == rx.end());
		int y[] = { 3,1,8,1,8,8,2,8,8 };
		VERIFY(ranges::equal(x, y));
	}
	return true;
}

struct X
{
	int i;

	friend HAMON_CXX11_CONSTEXPR bool
	operator==(const X& a, const X& b)
	{
		return a.i == b.i;
	}

	friend HAMON_CXX11_CONSTEXPR bool
	operator!=(const X& a, const X& b)
	{
		return !(a == b);
	}
};

struct Y
{
	int i;
	int j;

	friend HAMON_CXX11_CONSTEXPR bool
	operator==(const Y& a, const Y& b)
	{
		return a.i == b.i && a.j == b.j;
	}

	friend HAMON_CXX11_CONSTEXPR bool
	operator!=(const Y& a, const Y& b)
	{
		return !(a == b);
	}
};

inline HAMON_CXX17_CONSTEXPR bool test03()
{
	namespace ranges = hamon::ranges;
	{
		X x[6] = { {1}, {2}, {3}, {4}, {5}, {6} };
		auto res = ranges::replace_if(x, x+5, [](int a){return a%2 == 0; }, X{ 9 }, &X::i);
		VERIFY(res == x+5);
		X y[6] = { {1}, {9}, {3}, {9}, {5}, {6} };
		VERIFY(ranges::equal(x, y));
	}
	return true;
}

inline HAMON_CXX17_CONSTEXPR bool test04()
{
	namespace ranges = hamon::ranges;
	{
		Y x[] = { {1,2}, {2,4}, {3,6} };
		auto res = ranges::replace_if(x, [](int a){return a%2 == 1; }, Y{ 4,5 }, &Y::i);
		VERIFY(res == ranges::end(x));
		Y y[] = { {4,5}, {2,4}, {4,5} };
		VERIFY(ranges::equal(x, y));
	}
	{
		Y x[] = { {1,2}, {2,4}, {3,6} };
		auto res = ranges::replace_if(x, [](int a){return a%2 == 1; }, Y{ 4,5 }, &Y::j);
		VERIFY(res == ranges::end(x));
		Y y[] = { {1,2}, {2,4}, {3,6} };
		VERIFY(ranges::equal(x, y));
	}
	return true;
}

struct Pred
{
	HAMON_CXX11_CONSTEXPR bool operator()(Y const& y) const
	{
		return y == Y{1,2};
	}
};

inline HAMON_CXX14_CONSTEXPR bool test05()
{
	namespace ranges = hamon::ranges;
	{
		Y x[] = { {1,2}, {2,4}, {3,6} };
		auto res = ranges::replace_if(ranges::begin(x), ranges::end(x), Pred{}, {4,5});
		VERIFY(res == ranges::end(x));
		Y y[] = { {4,5}, {2,4}, {3,6} };
		VERIFY(ranges::equal(x, y));
	}
	{
		Y x[] = { {1,2}, {2,4}, {3,6} };
		auto res = ranges::replace_if(x, Pred{}, {4,5});
		VERIFY(res == ranges::end(x));
		Y y[] = { {4,5}, {2,4}, {3,6} };
		VERIFY(ranges::equal(x, y));
	}
	return true;
}

#undef VERIFY

GTEST_TEST(AlgorithmTest, RangesReplaceIfTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
#if defined(HAMON_GCC_VERSION) && (HAMON_GCC_VERSION < 100000)
	EXPECT_TRUE(test03());
	EXPECT_TRUE(test04());
#else
	HAMON_CXX17_CONSTEXPR_EXPECT_TRUE(test03());
	HAMON_CXX17_CONSTEXPR_EXPECT_TRUE(test04());
#endif
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test05());
}

}	// namespace ranges_replace_if_test

}	// namespace hamon_algorithm_test
