/**
 *	@file	unit_test_span_empty.cpp
 *
 *	@brief	bool span::empty() のテスト
 */

#include <hamon/span.hpp>
#include <gtest/gtest.h>
#include <string>
#include "constexpr_test.hpp"
#include "noexcept_test.hpp"

namespace hamon_span_test
{

namespace empty_test
{

template <typename Span>
HAMON_CXX11_CONSTEXPR bool test(Span sp)
{
	HAMON_ASSERT_NOEXCEPT_TRUE(sp.empty());
	return sp.empty();
}

struct A {};

GTEST_TEST(SpanTest, EmptyTest)
{
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(test(hamon::span<int>()));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(test(hamon::span<long>()));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(test(hamon::span<double>()));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(test(hamon::span<A>()));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(test(hamon::span<std::string>()));

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(test(hamon::span<int,         0>()));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(test(hamon::span<long,        0>()));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(test(hamon::span<double,      0>()));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(test(hamon::span<A,           0>()));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(test(hamon::span<std::string, 0>()));

	HAMON_CXX11_CONSTEXPR int arr[] = {10, 11, 12, 13, 14, 15, 16, 17, 18, 19};
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!test(hamon::span<int const>(arr, 1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!test(hamon::span<int const>(arr, 2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!test(hamon::span<int const>(arr, 3)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!test(hamon::span<int const>(arr, 4)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!test(hamon::span<int const>(arr, 5)));

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!test(hamon::span<int const, 1>(arr, 1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!test(hamon::span<int const, 2>(arr, 2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!test(hamon::span<int const, 3>(arr, 3)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!test(hamon::span<int const, 4>(arr, 4)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!test(hamon::span<int const, 5>(arr, 5)));
}

}	// namespace empty_test

}	// namespace hamon_span_test
