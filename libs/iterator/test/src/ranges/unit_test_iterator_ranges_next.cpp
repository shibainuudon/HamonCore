/**
 *	@file	unit_test_iterator_ranges_next.cpp
 *
 *	@brief	ranges::next のテスト
 */

#include <hamon/iterator/ranges/next.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_iterator_test
{

namespace ranges_next_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

void test01()
{
	static HAMON_CXX11_CONSTEXPR int a[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	HAMON_CXX11_CONSTEXPR test_random_access_range<int const> r(a);
	HAMON_CXX11_CONSTEXPR auto begin = r.begin();
	HAMON_CXX11_CONSTEXPR auto end = r.end();
	HAMON_CXX11_CONSTEXPR auto endi = hamon::ranges::next(begin, end);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(*hamon::ranges::next(begin) == 1);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::ranges::next(begin, 0) == begin);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(*hamon::ranges::next(begin, 1) == 1);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(*hamon::ranges::next(begin, 3) == 3);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(*hamon::ranges::next(endi, -4) == 6);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::ranges::next(begin, begin) == begin);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::ranges::next(begin, end) == end);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::ranges::next(endi, end) == end);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::ranges::next(endi, begin) == begin);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::ranges::next(begin, 0, begin) == begin);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::ranges::next(begin, 5, begin) == begin);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::ranges::next(begin, -5, begin) == begin);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::ranges::next(begin, 0, end) == begin);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(*hamon::ranges::next(begin, 5, end) == 5);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::ranges::next(begin, 55, end) == end);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::ranges::next(endi, 0, end) == end);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::ranges::next(endi, -5, end) == end);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::ranges::next(endi, -55, end) == end);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::ranges::next(endi, 0, begin) == end);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(*hamon::ranges::next(endi, -5, begin) == 5);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::ranges::next(endi, -55, begin) == begin);
}

void test02()
{
	static HAMON_CXX14_CONSTEXPR int a[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	HAMON_CXX14_CONSTEXPR test_bidirectional_range<int const> r(a);
	HAMON_CXX14_CONSTEXPR auto begin = r.begin();
	HAMON_CXX14_CONSTEXPR auto end = r.end();
	HAMON_CXX14_CONSTEXPR auto endi = hamon::ranges::next(begin, end);
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(*hamon::ranges::next(begin) == 1);
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE( hamon::ranges::next(begin, 0) == begin);
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(*hamon::ranges::next(begin, 1) == 1);
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(*hamon::ranges::next(begin, 3) == 3);
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(*hamon::ranges::next(endi, -4) == 6);
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE( hamon::ranges::next(begin, begin) == begin);
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE( hamon::ranges::next(begin, end) == end);
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE( hamon::ranges::next(endi, end) == end);
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE( hamon::ranges::next(endi, begin) == begin);
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE( hamon::ranges::next(begin, 0, begin) == begin);
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE( hamon::ranges::next(begin, 5, begin) == begin);
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE( hamon::ranges::next(begin, -5, begin) == begin);
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE( hamon::ranges::next(begin, 0, end) == begin);
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(*hamon::ranges::next(begin, 5, end) == 5);
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE( hamon::ranges::next(begin, 55, end) == end);
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE( hamon::ranges::next(endi, 0, end) == end);
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE( hamon::ranges::next(endi, -5, end) == end);
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE( hamon::ranges::next(endi, -55, end) == end);
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE( hamon::ranges::next(endi, 0, begin) == end);
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(*hamon::ranges::next(endi, -5, begin) == 5);
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE( hamon::ranges::next(endi, -55, begin) == begin);
}

void test03()
{
	static HAMON_CXX14_CONSTEXPR int a[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	HAMON_CXX14_CONSTEXPR test_forward_range<int const> r(a);
	HAMON_CXX14_CONSTEXPR auto begin = r.begin();
	HAMON_CXX14_CONSTEXPR auto end = r.end();
	HAMON_CXX14_CONSTEXPR auto endi = hamon::ranges::next(begin, end);
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(*hamon::ranges::next(begin) == 1);
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE( hamon::ranges::next(begin, 0) == begin);
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(*hamon::ranges::next(begin, 1) == 1);
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(*hamon::ranges::next(begin, 3) == 3);
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE( hamon::ranges::next(begin, begin) == begin);
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE( hamon::ranges::next(begin, end) == end);
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE( hamon::ranges::next(endi, end) == end);
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE( hamon::ranges::next(begin, 0, begin) == begin);
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE( hamon::ranges::next(begin, 5, begin) == begin);
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE( hamon::ranges::next(begin, 0, end) == begin);
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(*hamon::ranges::next(begin, 5, end) == 5);
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE( hamon::ranges::next(begin, 55, end) == end);
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE( hamon::ranges::next(endi, 0, end) == end);
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE( hamon::ranges::next(endi, 5, end) == end);
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE( hamon::ranges::next(endi, 55, end) == end);
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE( hamon::ranges::next(endi, 0, begin) == end);
}

HAMON_CXX14_CONSTEXPR bool test04()
{
	int a[10] ={0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	test_input_range<int> r(a);
	auto begin = r.begin();
	auto end = r.end();
	auto iter = hamon::ranges::next(begin);
	VERIFY(*iter == 1);
	iter = hamon::ranges::next(iter, 0);
	VERIFY(*iter == 1);
	iter = hamon::ranges::next(iter, 1);
	VERIFY(*iter == 2);
	iter = hamon::ranges::next(iter, 4);
	VERIFY(*iter == 6);

	iter = hamon::ranges::next(iter, iter);
	VERIFY(*iter == 6);
	iter = hamon::ranges::next(iter, end);
	VERIFY(iter == end);
	iter = hamon::ranges::next(iter, end);
	VERIFY(iter == end);

	test_input_range<int> r2(a);
	begin = r2.begin();
	end = r2.end();
	auto endi = hamon::ranges::next(begin, end);
	// reset single-pass input range
	r2.m_first = a;
	iter = hamon::ranges::next(begin, 0, begin);
	VERIFY(*iter == 0);
	iter = hamon::ranges::next(begin, 5, begin);
	VERIFY(*iter == 0);
	iter = hamon::ranges::next(begin, 0, end);
	VERIFY(*iter == 0);
	iter = hamon::ranges::next(endi, 0, begin);
	VERIFY(iter == end);
	iter = hamon::ranges::next(begin, 5, end); // invalidates begin
	VERIFY(*iter == 5);
	iter = hamon::ranges::next(iter, 55, end);
	VERIFY(iter == end);
	iter = hamon::ranges::next(endi, 0, end);
	VERIFY(iter == end);
	iter = hamon::ranges::next(endi, 5, end);
	VERIFY(iter == end);

	return true;
}

HAMON_CXX14_CONSTEXPR bool test05()
{
	int a[10] ={0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	test_output_range<int> r(a);
	auto iter = r.begin();
	auto end = r.end(); // sentinel, !same_as<decltype(iter), decltype(end)>

	iter = hamon::ranges::next(iter);
	*iter = 10;
	VERIFY(a[1] == 10);
	iter = hamon::ranges::next(iter, 0);
	iter = hamon::ranges::next(iter, 1);
	*iter = 20;
	VERIFY(a[2] == 20);
	iter = hamon::ranges::next(iter, 4);
	iter = hamon::ranges::next(iter, 0);
	*iter = 60;
	VERIFY(a[6] == 60);

	iter = hamon::ranges::next(iter, end);
	VERIFY(iter == end);
	iter = hamon::ranges::next(iter, end);
	VERIFY(iter == end);

	test_output_range<int> r2(a);
	iter = hamon::ranges::next(r2.begin(), 5);
	end = r2.end();

	iter = hamon::ranges::next(iter, 0, end);
	*iter = 50;
	VERIFY(a[5] == 50);
	iter = hamon::ranges::next(iter, 2, end);
	*iter = 70;
	VERIFY(a[7] == 70);
	iter = hamon::ranges::next(iter, 5, end);
	VERIFY(iter == end);

	return true;
}

#undef VERIFY

GTEST_TEST(IteratorTest, RangesNextTest)
{
	test01();
	test02();
	test03();
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test04());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test05());
}

}	// namespace ranges_next_test

}	// namespace hamon_iterator_test
