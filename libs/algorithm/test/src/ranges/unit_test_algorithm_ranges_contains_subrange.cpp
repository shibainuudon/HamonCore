/**
 *	@file	unit_test_algorithm_ranges_contains_subrange.cpp
 *
 *	@brief	ranges::contains_subrange のテスト
 */

#include <hamon/algorithm/ranges/contains_subrange.hpp>
#include <hamon/array.hpp>
#include <hamon/forward_list.hpp>
#include <hamon/list.hpp>
#include <hamon/vector.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_algorithm_test
{

namespace ranges_contains_subrange_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool Test01()
{
	namespace ranges = hamon::ranges;

	int x[] = { 3, 1, 4, 1, 5 };
	int y[] = { 1, 4, 1 };
	int z[] = { 1, 4, 2 };
	{
		VERIFY( ranges::contains_subrange(x, x+5, y, y+3));
		VERIFY(!ranges::contains_subrange(x, x+5, z, z+3));
		VERIFY( ranges::contains_subrange(x, y));
		VERIFY(!ranges::contains_subrange(x, z));
	}
	{
		test_forward_range<int> r(x);
		VERIFY( ranges::contains_subrange(r, y));
		VERIFY(!ranges::contains_subrange(r, z));
		VERIFY( ranges::contains_subrange(r, test_forward_range<int>(y)));
		VERIFY(!ranges::contains_subrange(r, test_forward_range<int>(z)));
	}
	return true;
}

struct X { int i; };

inline bool Test02()
{
	namespace ranges = hamon::ranges;

	X x[] = { {3}, {1}, {4}, {1}, {5} };
	int y[] = { 1, 4, 1 };
	int z[] = { 1, 4, 2 };
	{
		VERIFY( ranges::contains_subrange(x, x+5, y, y+3, {}, &X::i));
		VERIFY(!ranges::contains_subrange(x, x+5, z, z+3, {}, &X::i));
		VERIFY( ranges::contains_subrange(x, y, {}, &X::i));
		VERIFY(!ranges::contains_subrange(x, z, {}, &X::i));
	}
	{
		test_forward_range<X> r(x);
		VERIFY( ranges::contains_subrange(r, y, {}, &X::i));
		VERIFY(!ranges::contains_subrange(r, z, {}, &X::i));
		VERIFY( ranges::contains_subrange(r, test_forward_range<int>(y), {}, &X::i));
		VERIFY(!ranges::contains_subrange(r, test_forward_range<int>(z), {}, &X::i));
	}
	return true;
}

struct Y { int i; int j; };

inline bool Test03()
{
	namespace ranges = hamon::ranges;

	Y x[] = { {1,2}, {2,4}, {3,6} };
	X y[] = { {1}, {2} };
	X z[] = { {4}, {6} };
	VERIFY( ranges::contains_subrange(x, y, {}, &Y::i, &X::i));
	VERIFY(!ranges::contains_subrange(x, z, {}, &Y::i, &X::i));
	VERIFY(!ranges::contains_subrange(x, y, {}, &Y::j, &X::i));
	VERIFY( ranges::contains_subrange(x, z, {}, &Y::j, &X::i));

	return true;
}

inline HAMON_CXX14_CONSTEXPR bool TestArray()
{
	namespace ranges = hamon::ranges;

	hamon::array<int, 5> x = { 3, 1, 4, 1, 5 };
	hamon::array<int, 3> y = { 1, 4, 1 };
	hamon::array<int, 3> z = { 1, 4, 2 };
	VERIFY( ranges::contains_subrange(x, y));
	VERIFY(!ranges::contains_subrange(x, z));

	return true;
}

inline bool TestVector()
{
	namespace ranges = hamon::ranges;

	hamon::vector<int> x = { 1, 3, 5, 7, 9, 11, 13 };
	hamon::vector<int> y = { 1, 3, 1 };
	hamon::vector<int> z = { 5, 7, 9, 11 };
	VERIFY(!ranges::contains_subrange(x, y));
	VERIFY( ranges::contains_subrange(x, z));

	return true;
}

inline bool TestList()
{
	namespace ranges = hamon::ranges;

	hamon::list<int> x = { 1, 2, 3, 4, 5, 6 };
	hamon::list<int> y = { 4, 5, 6 };
	hamon::list<int> z = { 1, 2, 3, 5 };
	VERIFY( ranges::contains_subrange(x, y));
	VERIFY(!ranges::contains_subrange(x, z));

	return true;
}

inline bool TestForwardList()
{
	namespace ranges = hamon::ranges;

	hamon::forward_list<int> x = { 1, 2, 3, 4, 5, 6 };
	hamon::forward_list<int> y = { 4, 5, 6, 7 };
	hamon::forward_list<int> z = { 1, 2, 3 };
	VERIFY(!ranges::contains_subrange(x, y));
	VERIFY( ranges::contains_subrange(x, z));

	return true;
}

#undef VERIFY

GTEST_TEST(AlgorithmTest, RangesContainsSubrangeTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(Test01());
	EXPECT_TRUE(Test02());
	EXPECT_TRUE(Test03());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(TestArray());
	EXPECT_TRUE(TestVector());
	EXPECT_TRUE(TestList());
	EXPECT_TRUE(TestForwardList());
}

}	// namespace ranges_contains_subrange_test

}	// namespace hamon_algorithm_test
