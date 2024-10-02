/**
 *	@file	unit_test_algorithm_ranges_replace_copy_if.cpp
 *
 *	@brief	ranges::replace_copy_if のテスト
 */

#include <hamon/algorithm/ranges/replace_copy_if.hpp>
#include <hamon/algorithm/ranges/equal.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_algorithm_test
{

namespace ranges_replace_copy_if_test
{

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

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool test01()
{
	namespace ranges = hamon::ranges;
	{
		int const x[] = { 1,2,3,4,5,6,7,8,9 };
		int w[9] = {};
		auto res = ranges::replace_copy_if(x, x+9, w, Less<5>{}, 0);
		VERIFY(res.in  == x+9);
		VERIFY(res.out == w+9);
		int const y[] = { 0,0,0,0,5,6,7,8,9 };
		VERIFY(!ranges::equal(x, y));
		VERIFY( ranges::equal(w, y));
	}
	{
		int const x[] = { 1,2,3,4,5,6,7,8,9 };
		int w[9] = {};
		auto res = ranges::replace_copy_if(x, x+9, w, Greater<5>{}, 1);
		VERIFY(res.in  == x+9);
		VERIFY(res.out == w+9);
		int const y[] = { 1,2,3,4,5,1,1,1,1 };
		VERIFY(!ranges::equal(x, y));
		VERIFY( ranges::equal(w, y));
	}
	return true;
}

inline HAMON_CXX14_CONSTEXPR bool test02()
{
	namespace ranges = hamon::ranges;
	{
		int const x[] = { 3,1,4,1,5,9,2,6,5 };
		int w[9] = {};
		test_input_range<int const> rx(x);
		test_output_range<int> rw(w);
		auto res = ranges::replace_copy_if(rx, rw.begin(), Less<5>{}, 0);
		VERIFY(res.in  == rx.end());
		VERIFY(res.out == rw.end());
		int const y[] = { 0,0,0,0,5,9,0,6,5 };
		VERIFY(!ranges::equal(x, y));
		VERIFY( ranges::equal(w, y));
	}
	{
		int const x[] = { 3,1,4,1,5,9,2,6,5 };
		int w[9] = {};
		test_input_range<int const> rx(x);
		test_output_range<int> rw(w);
		auto res = ranges::replace_copy_if(rx, rw.begin(), Greater<3>{}, 8);
		VERIFY(res.in  == rx.end());
		VERIFY(res.out == rw.end());
		int const y[] = { 3,1,8,1,8,8,2,8,8 };
		VERIFY(!ranges::equal(x, y));
		VERIFY( ranges::equal(w, y));
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
		X const x[6] = { {1}, {2}, {3}, {4}, {5}, {6} };
		X w[6] = {};
		auto res = ranges::replace_copy_if(x, x+5, w,
			[](int a){return a%2 == 0; }, X{ 9 }, &X::i);
		VERIFY(res.in  == x+5);
		VERIFY(res.out == w+5);
		X const y[6] = { {1}, {9}, {3}, {9}, {5}, {0} };
		VERIFY(ranges::equal(w, y));
	}
	return true;
}

inline HAMON_CXX17_CONSTEXPR bool test04()
{
	namespace ranges = hamon::ranges;
	{
		Y const x[] = { {1,2}, {2,4}, {3,6} };
		Y w[3] = {};
		auto res = ranges::replace_copy_if(x, w,
			[](int a){return a%2 == 1; }, Y{ 4,5 }, &Y::i);
		VERIFY(res.in  == x+3);
		VERIFY(res.out == w+3);
		Y const y[] = { {4,5}, {2,4}, {4,5} };
		VERIFY(ranges::equal(w, y));
	}
	{
		Y const x[] = { {1,2}, {2,4}, {3,6} };
		Y w[3] = {};
		auto res = ranges::replace_copy_if(x, w,
			[](int a){return a%2 == 1; }, Y{ 4,5 }, &Y::j);
		VERIFY(res.in  == x+3);
		VERIFY(res.out == w+3);
		Y const y[] = { {1,2}, {2,4}, {3,6} };
		VERIFY(ranges::equal(w, y));
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
		Y w[3] = {};
		auto res = ranges::replace_copy_if(ranges::begin(x), ranges::end(x), ranges::begin(w), Pred{}, {4,5});
		VERIFY(res.in == ranges::end(x));
		VERIFY(res.out == ranges::end(w));
		Y y[] = { {4,5}, {2,4}, {3,6} };
		VERIFY(ranges::equal(w, y));
	}
	{
		Y x[] = { {1,2}, {2,4}, {3,6} };
		Y w[3] = {};
		auto res = ranges::replace_copy_if(x, ranges::begin(w), Pred{}, {4,5});
		VERIFY(res.in == ranges::end(x));
		VERIFY(res.out == ranges::end(w));
		Y y[] = { {4,5}, {2,4}, {3,6} };
		VERIFY(ranges::equal(w, y));
	}
	return true;
}

#undef VERIFY

GTEST_TEST(AlgorithmTest, RangesReplaceCopyIfTest)
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

}	// namespace ranges_replace_copy_if_test

}	// namespace hamon_algorithm_test
