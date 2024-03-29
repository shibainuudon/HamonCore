﻿/**
 *	@file	unit_test_span_rend.cpp
 *
 *	@brief	reverse_iterator span::rend() のテスト
 */

#include <hamon/span.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/string.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_span_test
{

namespace rend_test
{

template <typename Span>
HAMON_CXX11_CONSTEXPR bool test1(Span s)
{
	static_assert(hamon::is_same<decltype(s.rend()), typename Span::reverse_iterator>::value, "");
	return
		(s.rend() == s.rbegin()) &&
		(static_cast<size_t>(s.rend() - s.rbegin()) == s.size());
}

template <typename Span>
HAMON_CXX11_CONSTEXPR bool test2(Span s)
{
	static_assert(hamon::is_same<decltype(s.rend()), typename Span::reverse_iterator>::value, "");
	return
		(s.rend() != s.rbegin()) &&
		(static_cast<size_t>(s.rend() - s.rbegin()) == s.size());
}

struct A {};
bool operator==(A, A) { return true; }

GTEST_TEST(SpanTest, REndTest)
{
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(test1(hamon::span<int>()));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(test1(hamon::span<long>()));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(test1(hamon::span<double>()));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(test1(hamon::span<A>()));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(test1(hamon::span<hamon::string>()));

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(test1(hamon::span<int, 0>()));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(test1(hamon::span<long, 0>()));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(test1(hamon::span<double, 0>()));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(test1(hamon::span<A, 0>()));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(test1(hamon::span<hamon::string, 0>()));

	HAMON_CXX11_CONSTEXPR int arr[] ={10, 11, 12, 13, 14, 15, 16, 17, 18, 19};
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(test2(hamon::span<int const>(arr, 1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(test2(hamon::span<int const>(arr, 2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(test2(hamon::span<int const>(arr, 3)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(test2(hamon::span<int const>(arr, 4)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(test2(hamon::span<int const>(arr, 5)));
}

}	// namespace rend_test

}	// namespace hamon_span_test
