/**
 *	@file	unit_test_algorithm_ranges_find_last.cpp
 *
 *	@brief	ranges::find_last のテスト
 */

#include <hamon/algorithm/ranges/find_last.hpp>
#include <hamon/algorithm/ranges/equal.hpp>
#include <hamon/ranges/empty.hpp>
#include <hamon/ranges/end.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_algorithm_test
{

namespace ranges_find_last_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

struct plus3
{
	constexpr int operator()(int n) const { return n + 3; }
};

struct plus4
{
	constexpr int operator()(int n) const { return n + 4; }
};

inline HAMON_CXX14_CONSTEXPR bool test01()
{
	namespace ranges = hamon::ranges;

	int x[] = { 1, 2, 1, 2, 1, 2, 1, 2 };
	
	{
		auto sr = ranges::find_last(x, 0);
		VERIFY(ranges::empty(sr));
		VERIFY(sr.begin() == ranges::end(x));
	}
	{
		auto sr = ranges::find_last(x, 1);
		int const y[] = { 1, 2 };
		VERIFY(ranges::equal(sr, y));
		VERIFY(sr.begin() == &x[6]);
	}
	{
		auto sr = ranges::find_last(x, 2);
		int const y[] = { 2 };
		VERIFY(ranges::equal(sr, y));
		VERIFY(sr.begin() == &x[7]);
	}

	{
		auto sr = ranges::find_last(x, 3, plus3{});
		VERIFY(ranges::empty(sr));
		VERIFY(sr.begin() == ranges::end(x));
	}
	{
		auto sr = ranges::find_last(x, 4, plus3{});
		int const y[] = { 1, 2 };
		VERIFY(ranges::equal(sr, y));
		VERIFY(sr.begin() == &x[6]);
	}
	{
		auto sr = ranges::find_last(x, 5, plus3{});
		int const y[] = { 2 };
		VERIFY(ranges::equal(sr, y));
		VERIFY(sr.begin() == &x[7]);
	}

	return true;
}

inline HAMON_CXX14_CONSTEXPR bool test02()
{
	namespace ranges = hamon::ranges;

	int x[] = { 1, 2, 3, 1, 2, 3, 1, 2, 3 };
	test_forward_range<int> rx(x);

	{
		auto sr = ranges::find_last(rx, 0);
		VERIFY(ranges::empty(sr));
		VERIFY(sr.begin() == ranges::end(rx));
	}
	{
		auto sr = ranges::find_last(rx, 1);
		int const y[] = { 1, 2, 3 };
		VERIFY(ranges::equal(sr, y));
		VERIFY(sr.begin().m_ptr == &x[6]);
	}
	{
		auto sr = ranges::find_last(rx, 2);
		int const y[] = { 2, 3 };
		VERIFY(ranges::equal(sr, y));
		VERIFY(sr.begin().m_ptr == &x[7]);
	}
	{
		auto sr = ranges::find_last(rx, 3);
		int const y[] = { 3 };
		VERIFY(ranges::equal(sr, y));
		VERIFY(sr.begin().m_ptr == &x[8]);
	}

	{
		auto sr = ranges::find_last(rx, 4, plus4{});
		VERIFY(ranges::empty(sr));
		VERIFY(sr.begin() == ranges::end(rx));
	}
	{
		auto sr = ranges::find_last(rx, 5, plus4{});
		int const y[] = { 1, 2, 3 };
		VERIFY(ranges::equal(sr, y));
		VERIFY(sr.begin().m_ptr == &x[6]);
	}
	{
		auto sr = ranges::find_last(rx, 6, plus4{});
		int const y[] = { 2, 3 };
		VERIFY(ranges::equal(sr, y));
		VERIFY(sr.begin().m_ptr == &x[7]);
	}
	{
		auto sr = ranges::find_last(rx, 7, plus4{});
		int const y[] = { 3 };
		VERIFY(ranges::equal(sr, y));
		VERIFY(sr.begin().m_ptr == &x[8]);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(AlgorithmTest, RangesFindLastTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
}

}	// namespace ranges_find_last_test

}	// namespace hamon_algorithm_test
