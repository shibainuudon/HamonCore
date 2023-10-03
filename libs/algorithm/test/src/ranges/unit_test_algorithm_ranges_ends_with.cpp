/**
 *	@file	unit_test_algorithm_ranges_ends_with.cpp
 *
 *	@brief	ranges::ends_with のテスト
 */

#include <hamon/algorithm/ranges/ends_with.hpp>
#include <hamon/functional/ranges/equal_to.hpp>
#include <hamon/functional/identity.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_algorithm_test
{

namespace ranges_ends_with_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

struct plus1
{
	constexpr int operator()(int n) const { return n + 1; }
};

inline HAMON_CXX14_CONSTEXPR bool test01()
{
	namespace ranges = hamon::ranges;

	{
		int x[] = { 1,2,3,4,5,6 };
		int y[] = { 1,2,3,4,5,6 };
		VERIFY( ranges::ends_with(x, y));
		VERIFY( ranges::ends_with(x, x + 5, y, y + 5));
		VERIFY(!ranges::ends_with(x, x + 5, y, y + 4));
		VERIFY(!ranges::ends_with(x, x + 4, y, y + 5));
		VERIFY( ranges::ends_with(x, x + 5, y + 1, y + 5));
		VERIFY( ranges::ends_with(x, x + 5, y + 2, y + 5));
		VERIFY(!ranges::ends_with(x + 1, x + 5, y, y + 5));
		VERIFY(!ranges::ends_with(x + 2, x + 5, y, y + 5));
	}
	{
		int x[] = { 1,2,3,4,5,6 };
		int y[] = { 1,2,3,4,5 };
		VERIFY(!ranges::ends_with(x, y));
	}
	{
		int x[] = { 1,2,3,4,5,6 };
		int y[] = { 2,3,4,5,6 };
		VERIFY( ranges::ends_with(x, y));
	}
	{
		int x[] = { 1,2,3,4,5,6 };
		int y[] = { 6 };
		VERIFY( ranges::ends_with(x, y));
	}
	{
		int x[] = { 1,2,3,4,5 };
		int y[] = { 4,5,6 };
		VERIFY(ranges::ends_with(x, y, ranges::equal_to{}, plus1{}));
	}
	{
		int x[] = { 1,2,3,4,5 };
		int y[] = { 2,3,4 };
		VERIFY(ranges::ends_with(x, y, ranges::equal_to{}, hamon::identity{}, plus1{}));
	}

	return true;
}

template <template <typename> class RangeWrapper>
inline HAMON_CXX14_CONSTEXPR bool test02()
{
	namespace ranges = hamon::ranges;

	{
		int x[] = { 10, 11, 12, 13 };
		int y[] = { 10, 11, 12, 13 };
		RangeWrapper<int> rx(x);
		RangeWrapper<int> ry(y);
		VERIFY(ranges::ends_with(rx, ry));
	}
	{
		int x[] = { 10, 11, 12, 13 };
		int y[] = { 11, 12, 13 };
		RangeWrapper<int> rx(x);
		RangeWrapper<int> ry(y);
		VERIFY(ranges::ends_with(rx, ry));
	}
	{
		int x[] = { 10, 11, 12, 13 };
		int y[] = { 12, 13 };
		RangeWrapper<int> rx(x);
		RangeWrapper<int> ry(y);
		VERIFY(ranges::ends_with(rx, ry));
	}
	{
		int x[] = { 10, 11, 12, 13 };
		int y[] = { 13 };
		RangeWrapper<int> rx(x);
		RangeWrapper<int> ry(y);
		VERIFY(ranges::ends_with(rx, ry));
	}
	{
		int x[] = { 10, 11, 12, 13 };
		int y[] = { 10, 11, 13 };
		RangeWrapper<int> rx(x);
		RangeWrapper<int> ry(y);
		VERIFY(!ranges::ends_with(rx, ry));
	}
	{
		int x[] = { 10, 11, 12, 13 };
		int y[] = { 10, 12 };
		RangeWrapper<int> rx(x);
		RangeWrapper<int> ry(y);
		VERIFY(!ranges::ends_with(rx, ry));
	}
	{
		int x[] = { 10, 11, 12, 13 };
		int y[] = { 10, 11 };
		RangeWrapper<int> rx(x);
		RangeWrapper<int> ry(y);
		VERIFY(!ranges::ends_with(rx, ry));
	}

	return true;
}

#undef VERIFY

GTEST_TEST(AlgorithmTest, RangesEndsWithTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
//	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02<test_input_range>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02<test_forward_range>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02<test_bidirectional_range>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02<test_random_access_range>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02<test_contiguous_range>());
}

}	// namespace ranges_ends_with_test

}	// namespace hamon_algorithm_test
