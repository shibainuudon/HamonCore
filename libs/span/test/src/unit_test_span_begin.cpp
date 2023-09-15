/**
 *	@file	unit_test_span_begin.cpp
 *
 *	@brief	iterator span::begin() のテスト
 */

#include <hamon/span.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/string.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_span_test
{

namespace begin_test
{

template <typename Span>
HAMON_CXX11_CONSTEXPR bool test1(Span s)
{
	static_assert(hamon::is_same<decltype(s.begin()), typename Span::iterator>::value, "");
	return s.begin() == s.end();
}

template <typename Span>
HAMON_CXX11_CONSTEXPR bool test2(Span s)
{
	static_assert(hamon::is_same<decltype(s.begin()), typename Span::iterator>::value, "");
	return
		( *(s.begin()) ==  s[0]) &&
		(&*(s.begin()) == &s[0]);
}

struct A {};
bool operator==(A, A) { return true; }

GTEST_TEST(SpanTest, BeginTest)
{
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(test1(hamon::span<int>        ()));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(test1(hamon::span<long>       ()));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(test1(hamon::span<double>     ()));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(test1(hamon::span<A>          ()));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(test1(hamon::span<hamon::string>()));

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(test1(hamon::span<int,         0>()));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(test1(hamon::span<long,        0>()));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(test1(hamon::span<double,      0>()));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(test1(hamon::span<A,           0>()));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(test1(hamon::span<hamon::string, 0>()));

	HAMON_CXX11_CONSTEXPR int arr[] = {10, 11, 12, 13, 14, 15, 16, 17, 18, 19};
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(test2(hamon::span<int const>(arr, 1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(test2(hamon::span<int const>(arr, 2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(test2(hamon::span<int const>(arr, 3)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(test2(hamon::span<int const>(arr, 4)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(test2(hamon::span<int const>(arr, 5)));
}

}	// namespace begin_test

}	// namespace hamon_span_test
