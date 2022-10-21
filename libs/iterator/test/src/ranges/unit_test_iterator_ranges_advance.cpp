/**
 *	@file	unit_test_iterator_ranges_advance.cpp
 *
 *	@brief	ranges::advance のテスト
 */

#include <hamon/iterator/ranges/advance.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_iterator_test
{

namespace ranges_advance_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test01()
{
	int a[2] ={};
	test_random_access_range<int> r(a);
	auto iter = r.begin();
	hamon::ranges::advance(iter, 1);
	VERIFY(iter != r.begin());
	VERIFY(iter != r.end());
	hamon::ranges::advance(iter, 1);
	VERIFY(iter == r.end());
	hamon::ranges::advance(iter, -2);
	VERIFY(iter == r.begin());

	hamon::ranges::advance(iter, r.begin() + 1);
	VERIFY(iter != r.begin());
	VERIFY(iter != r.end());
	hamon::ranges::advance(iter, r.begin());
	VERIFY(iter == r.begin());

	hamon::ranges::advance(iter, 99, r.end());
	VERIFY(iter == r.end());
	hamon::ranges::advance(iter, -222, r.begin());
	VERIFY(iter == r.begin());

	return true;
}

HAMON_CXX14_CONSTEXPR bool test02()
{
	int a[2] ={};
	test_bidirectional_range<int> r(a);
	auto iter = r.begin();
	hamon::ranges::advance(iter, 1);
	VERIFY(iter != r.begin());
	VERIFY(iter != r.end());
	hamon::ranges::advance(iter, 1);
	VERIFY(iter == r.end());
	hamon::ranges::advance(iter, -2);
	VERIFY(iter == r.begin());

	auto iter1 = r.begin();
	++iter1;
	hamon::ranges::advance(iter, iter1);
	VERIFY(iter != r.begin());
	VERIFY(iter != r.end());
	hamon::ranges::advance(iter, r.begin());
	VERIFY(iter == r.begin());

	hamon::ranges::advance(iter, 99, r.end());
	VERIFY(iter == r.end());
	hamon::ranges::advance(iter, -222, r.begin());
	VERIFY(iter == r.begin());

	return true;
}

HAMON_CXX14_CONSTEXPR bool test03()
{
	int a[2] ={};
	test_forward_range<int> r(a);
	auto iter = r.begin();
	hamon::ranges::advance(iter, 1);
	VERIFY(iter != r.begin());
	VERIFY(iter != r.end());
	hamon::ranges::advance(iter, 1);
	hamon::ranges::advance(iter, 0);
	VERIFY(iter == r.end());
	hamon::ranges::advance(iter, 0);
	VERIFY(iter == r.end());

	auto iter1 = r.begin();
	++iter1;
	hamon::ranges::advance(iter, iter1);
	VERIFY(iter != r.begin());
	VERIFY(iter != r.end());
	hamon::ranges::advance(iter, r.end());
	VERIFY(iter == r.end());
	hamon::ranges::advance(iter, r.end());
	VERIFY(iter == r.end());

	hamon::ranges::advance(iter, 99, r.end());
	VERIFY(iter == r.end());
	hamon::ranges::advance(iter, 99, r.end());
	VERIFY(iter == r.end());
	iter = r.begin();
	hamon::ranges::advance(iter, 99, r.end());
	VERIFY(iter == r.end());
	hamon::ranges::advance(iter, 99, r.end());
	VERIFY(iter == r.end());

	return true;
}

HAMON_CXX14_CONSTEXPR bool test04()
{
	int a[2] ={};
	test_input_range<int> r(a);
	auto iter = r.begin();
	hamon::ranges::advance(iter, 1);
	VERIFY(iter != r.end());
	hamon::ranges::advance(iter, 1);
	hamon::ranges::advance(iter, 0);
	VERIFY(iter == r.end());
	hamon::ranges::advance(iter, 0);
	VERIFY(iter == r.end());

	test_input_range<int> r2(a);
	iter = r2.begin();
	++iter;
	const auto iter1 = iter;
	hamon::ranges::advance(iter, iter1);
	VERIFY(iter == iter1);
	VERIFY(iter != r2.end());
	hamon::ranges::advance(iter, r2.end());
	VERIFY(iter == r2.end());
	hamon::ranges::advance(iter, r2.end());
	VERIFY(iter == r2.end());

	hamon::ranges::advance(iter, 99, r2.end());
	VERIFY(iter == r2.end());
	hamon::ranges::advance(iter, 99, r2.end());
	VERIFY(iter == r2.end());

	test_input_range<int> r3(a);
	iter = r3.begin();
	hamon::ranges::advance(iter, 99, r3.end());
	VERIFY(iter == r3.end());
	hamon::ranges::advance(iter, 99, r3.end());
	VERIFY(iter == r3.end());

	return true;
}

HAMON_CXX14_CONSTEXPR bool test05()
{
	int a[2] ={};
	test_output_range<int> r(a);
	auto iter = r.begin();
	hamon::ranges::advance(iter, 1);
	VERIFY(iter != r.end());
	hamon::ranges::advance(iter, 1);
	hamon::ranges::advance(iter, 0);
	VERIFY(iter == r.end());
	hamon::ranges::advance(iter, 0);
	VERIFY(iter == r.end());

	test_output_range<int> r2(a);
	iter = r2.begin();
	++iter;
	hamon::ranges::advance(iter, r2.end());
	VERIFY(iter == r2.end());
	hamon::ranges::advance(iter, r2.end());
	VERIFY(iter == r2.end());

	hamon::ranges::advance(iter, 99, r2.end());
	VERIFY(iter == r2.end());
	hamon::ranges::advance(iter, 99, r2.end());
	VERIFY(iter == r2.end());

	test_output_range<int> r3(a);
	iter = r3.begin();
	hamon::ranges::advance(iter, 99, r3.end());
	VERIFY(iter == r3.end());
	hamon::ranges::advance(iter, 99, r3.end());
	VERIFY(iter == r3.end());

	return true;
}

#undef VERIFY

GTEST_TEST(IteratorTest, RangesAdvanceTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test03());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test04());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test05());
}

}	// namespace ranges_advance_test

}	// namespace hamon_iterator_test
