/**
 *	@file	unit_test_algorithm_ranges_shift_left.cpp
 *
 *	@brief	ranges::shift_left のテスト
 */

#include <hamon/algorithm/ranges/shift_left.hpp>
#include <hamon/algorithm/ranges/equal.hpp>
#include <hamon/iterator/ranges/next.hpp>
#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/end.hpp>
#include <hamon/ranges/empty.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_algorithm_test
{

namespace ranges_shift_left_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool test01()
{
	namespace ranges = hamon::ranges;

	{
		int x[] = { 1,2,3,4,5 };
		auto ret = ranges::shift_left(ranges::begin(x), ranges::end(x), 0);
		int const y[] = { 1,2,3,4,5 };
		VERIFY(ret.begin() == ranges::begin(x));
		VERIFY(ret.end()   == ranges::next(ranges::begin(x), 5));
		VERIFY(ranges::equal(ret, y));
		VERIFY(ranges::equal(x, y));
	}
	{
		int x[] = { 1,2,3,4,5 };
		auto ret = ranges::shift_left(ranges::begin(x), ranges::end(x), 1);
		int const y[] = { 2,3,4,5 };
		VERIFY(ret.begin() == ranges::begin(x));
		VERIFY(ret.end()   == ranges::next(ranges::begin(x), 4));
		VERIFY(ranges::equal(ret, y));
	}
	{
		int x[] = { 1,2,3,4,5 };
		auto ret = ranges::shift_left(ranges::begin(x), ranges::end(x), 2);
		int const y[] = { 3,4,5 };
		VERIFY(ret.begin() == ranges::begin(x));
		VERIFY(ret.end()   == ranges::next(ranges::begin(x), 3));
		VERIFY(ranges::equal(ret, y));
	}
	{
		int x[] = { 1,2,3,4,5 };
		auto ret = ranges::shift_left(ranges::begin(x), ranges::end(x), 3);
		int const y[] = { 4,5 };
		VERIFY(ret.begin() == ranges::begin(x));
		VERIFY(ret.end()   == ranges::next(ranges::begin(x), 2));
		VERIFY(ranges::equal(ret, y));
	}
	{
		int x[] = { 1,2,3,4,5 };
		auto ret = ranges::shift_left(ranges::begin(x), ranges::end(x), 4);
		int const y[] = { 5 };
		VERIFY(ret.begin() == ranges::begin(x));
		VERIFY(ret.end()   == ranges::next(ranges::begin(x), 1));
		VERIFY(ranges::equal(ret, y));
	}
	{
		int x[] = { 1,2,3,4,5 };
		auto ret = ranges::shift_left(ranges::begin(x), ranges::end(x), 5);
		int const y[] = { 1,2,3,4,5 };
		VERIFY(ret.begin() == ranges::begin(x));
		VERIFY(ret.end()   == ranges::next(ranges::begin(x), 0));
		VERIFY(ranges::empty(ret));
		VERIFY(ranges::equal(x, y));
	}
	{
		int x[] = { 1,2,3,4,5 };
		auto ret = ranges::shift_left(ranges::begin(x), ranges::end(x), 6);
		int const y[] = { 1,2,3,4,5 };
		VERIFY(ret.begin() == ranges::begin(x));
		VERIFY(ret.end()   == ranges::next(ranges::begin(x), 0));
		VERIFY(ranges::empty(ret));
		VERIFY(ranges::equal(x, y));
	}

	return true;
}

template <template <typename> class RangeWrapper>
inline HAMON_CXX14_CONSTEXPR bool test02()
{
	namespace ranges = hamon::ranges;

	{
		int x[] = { 10, 11, 12, 13 };
		RangeWrapper<int> rx(x);
		auto ret = ranges::shift_left(rx, 0);
		int const y[] = { 10, 11, 12, 13 };
		VERIFY(ret.begin() == ranges::begin(rx));
		VERIFY(ret.end()   == ranges::next(ranges::begin(rx), 4));
		VERIFY(ranges::equal(ret, y));
		VERIFY(ranges::equal(x, y));
	}
	{
		int x[] = { 10, 11, 12, 13 };
		RangeWrapper<int> rx(x);
		auto ret = ranges::shift_left(rx, 1);
		int const y[] = { 11, 12, 13 };
		VERIFY(ret.begin() == ranges::begin(rx));
		VERIFY(ret.end()   == ranges::next(ranges::begin(rx), 3));
		VERIFY(ranges::equal(ret, y));
	}
	{
		int x[] = { 10, 11, 12, 13 };
		RangeWrapper<int> rx(x);
		auto ret = ranges::shift_left(rx, 2);
		int const y[] = { 12, 13 };
		VERIFY(ret.begin() == ranges::begin(rx));
		VERIFY(ret.end()   == ranges::next(ranges::begin(rx), 2));
		VERIFY(ranges::equal(ret, y));
	}
	{
		int x[] = { 10, 11, 12, 13 };
		RangeWrapper<int> rx(x);
		auto ret = ranges::shift_left(rx, 3);
		int const y[] = { 13 };
		VERIFY(ret.begin() == ranges::begin(rx));
		VERIFY(ret.end()   == ranges::next(ranges::begin(rx), 1));
		VERIFY(ranges::equal(ret, y));
	}
	{
		int x[] = { 10, 11, 12, 13 };
		RangeWrapper<int> rx(x);
		auto ret = ranges::shift_left(rx, 4);
		int const y[] = { 10, 11, 12, 13 };
		VERIFY(ret.begin() == ranges::begin(rx));
		VERIFY(ret.end()   == ranges::next(ranges::begin(rx), 0));
		VERIFY(ranges::empty(ret));
		VERIFY(ranges::equal(x, y));
	}
	{
		int x[] = { 10, 11, 12, 13 };
		RangeWrapper<int> rx(x);
		auto ret = ranges::shift_left(rx, 5);
		int const y[] = { 10, 11, 12, 13 };
		VERIFY(ret.begin() == ranges::begin(rx));
		VERIFY(ret.end()   == ranges::next(ranges::begin(rx), 0));
		VERIFY(ranges::empty(ret));
		VERIFY(ranges::equal(x, y));
	}

	return true;
}

#undef VERIFY

GTEST_TEST(AlgorithmTest, RangesShiftLeftTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
//	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02<test_input_range>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02<test_forward_range>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02<test_bidirectional_range>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02<test_random_access_range>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02<test_contiguous_range>());
}

}	// namespace ranges_shift_left_test

}	// namespace hamon_algorithm_test
