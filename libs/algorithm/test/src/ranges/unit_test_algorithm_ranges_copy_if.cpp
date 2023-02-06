/**
 *	@file	unit_test_algorithm_ranges_copy_if.cpp
 *
 *	@brief	ranges::copy_if のテスト
 */

#include <hamon/algorithm/ranges/copy_if.hpp>
#include <hamon/algorithm/ranges/equal.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_algorithm_test
{

namespace ranges_copy_if_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

struct IsEven
{
	constexpr bool operator()(int i) const { return i % 2 == 0; }
};

struct IsOdd
{
	constexpr bool operator()(int i) const { return i % 2 == 1; }
};

inline HAMON_CXX14_CONSTEXPR bool test01()
{
	namespace ranges = hamon::ranges;
	{
		int x[] = { 3,1,4,1,5,9,2,6,5};
		int w[3] = {};
		auto res = ranges::copy_if(x, w, IsEven{});
		VERIFY(res.in == x+9 && res.out == w+3);
		int y[] = { 4,2,6 };
		VERIFY(ranges::equal(w, y));
	}
	{
		int x[] = { 3,1,4,1,5,9,2,6,5};
		int w[6] = {};
		auto res = ranges::copy_if(x, w, IsOdd{});
		VERIFY(res.in == x+9 && res.out == w+6);
		int y[] = { 3,1,1,5,9,5 };
		VERIFY(ranges::equal(w, y));
	}
	return true;
}

inline bool test02()
{
	namespace ranges = hamon::ranges;

	int x[] = { 1,2,3,4,5,6,7 };

	{
		int w[7];
		test_input_range<int>  rx(x);
		test_output_range<int> rw(w);
		auto res = ranges::copy_if(rx, rw.begin(),
			[](int a) { return (a%2)==0; });
		VERIFY(res.in == rx.end() && res.out.m_ptr == w+3);
		const int y[] = { 2,4,6 };
		VERIFY(ranges::equal(w, w+3, y, y+3));
	}
	{
		int w[7];
		test_input_range<int>  rx(x);
		test_output_range<int> rw(w);
		auto res = ranges::copy_if(rx, rw.begin(),
			[](int a) { return (a%2)==1; });
		VERIFY(res.in == rx.end() && res.out.m_ptr == w+4);
		const int y[] = { 1,3,5,7 };
		VERIFY(ranges::equal(w, w+4, y, y+4));
	}
	{
		int w[7];
		test_input_range<int>  rx(x);
		test_output_range<int> rw(w);
		auto res = ranges::copy_if(rx, rw.begin(),
			[](int a) { return (a%2)==0; },
			[](int a) { return a+1; });
		VERIFY(res.in == rx.end() && res.out.m_ptr == w+4);
		const int y[] = { 1,3,5,7 };
		VERIFY(ranges::equal(w, w+4, y, y+4));
	}
	return true;
}

#undef VERIFY

GTEST_TEST(AlgorithmTest, RangesCopyIfTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	EXPECT_TRUE(test02());
}

}	// namespace ranges_copy_if_test

}	// namespace hamon_algorithm_test
