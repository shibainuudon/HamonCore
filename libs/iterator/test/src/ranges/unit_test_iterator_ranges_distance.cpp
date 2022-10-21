/**
 *	@file	unit_test_iterator_ranges_distance.cpp
 *
 *	@brief	ranges::distance のテスト
 */

#include <hamon/iterator/ranges/distance.hpp>
#include <hamon/iterator/ranges/next.hpp>
#include <hamon/ranges/concepts/range.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_iterator_test
{

namespace ranges_distance_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test01()
{
	int a[10] ={};
	VERIFY(hamon::ranges::distance(a) == 10);

	test_random_access_range<int> c(a);
	VERIFY(hamon::ranges::distance(c) == 10);

	auto b = c.begin();
	auto e = c.end();
	auto ei = hamon::ranges::next(b, e);
	VERIFY(hamon::ranges::distance(b, e) == 10);
	VERIFY(hamon::ranges::distance(ei, b) == -10);

	const auto cb = b;
	const auto ce = e;
	const auto cei = ei;
	VERIFY(hamon::ranges::distance(cb, ce) == 10);
	VERIFY(hamon::ranges::distance(cei, cb) == -10);

	test_random_access_sized_range<int> c2(a);
	VERIFY(hamon::ranges::distance(c2) == 10);

	return true;
}

HAMON_CXX14_CONSTEXPR bool test02()
{
	int a[2] ={};
	VERIFY(hamon::ranges::distance(a) == 2);

	test_bidirectional_range<int> c(a);
	VERIFY(hamon::ranges::distance(c) == 2);

	auto b = c.begin();
	auto e = c.end();
	VERIFY(hamon::ranges::distance(b, e) == 2);

	const auto cb = b;
	const auto ce = e;
	VERIFY(hamon::ranges::distance(cb, ce) == 2);

	test_bidirectional_sized_range<int> c2(a);
	VERIFY(hamon::ranges::distance(c2) == 2);

	return true;
}

HAMON_CXX14_CONSTEXPR bool test03()
{
	int a[3] ={};
	test_forward_range<int> c(a);
	VERIFY(hamon::ranges::distance(c) == 3);

	auto b = c.begin();
	auto e = c.end();
	VERIFY(hamon::ranges::distance(b, e) == 3);

	const auto cb = b;
	const auto ce = e;
	VERIFY(hamon::ranges::distance(cb, ce) == 3);

	test_forward_sized_range<int> c2(a);
	VERIFY(hamon::ranges::distance(c2) == 3);

	return true;
}

HAMON_CXX14_CONSTEXPR bool test04()
{
	int a[4] ={};
	test_input_range<int> c(a);
	static_assert(hamon::ranges::range_t<decltype(c)>::value, "");

	VERIFY(hamon::ranges::distance(c) == 4);

	c = test_input_range<int>(a);
	auto b = c.begin();
	auto e = c.end();
	VERIFY(hamon::ranges::distance(b, e) == 4);

	test_input_range<int> c2(a);
	const auto cb = c2.begin();
	const auto ce = c2.end();
	VERIFY(hamon::ranges::distance(cb, ce) == 4);

	test_input_sized_range<int> c3(a);
	VERIFY(hamon::ranges::distance(c3) == 4);

	return true;
}

HAMON_CXX14_CONSTEXPR bool test05()
{
	int a[5] ={};
	test_output_range<int> c(a);
	VERIFY(hamon::ranges::distance(c) == 5);

	test_output_range<int> c2(a);
	auto b = c2.begin();
	auto e = c2.end();
	VERIFY(hamon::ranges::distance(b, e) == 5);

	test_output_range<int> c3(a);
	const auto cb = c3.begin();
	const auto ce = c3.end();
	VERIFY(hamon::ranges::distance(cb, ce) == 5);

	test_output_sized_range<int> c4(a);
	VERIFY(hamon::ranges::distance(c4) == 5);

	return true;
}

#undef VERIFY

GTEST_TEST(IteratorTest, RangesDistanceTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test03());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test04());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test05());
}

}	// namespace ranges_distance_test

}	// namespace hamon_iterator_test
