/**
 *	@file	unit_test_span_size.cpp
 *
 *	@brief	index_type span::size() のテスト
 */

#include <hamon/span.hpp>
#include <gtest/gtest.h>
#include <cstddef>
#include <string>
#include "constexpr_test.hpp"
#include "noexcept_test.hpp"

namespace hamon_span_test
{

namespace size_test
{

template <typename Span>
HAMON_CXX11_CONSTEXPR bool test(Span sp, std::size_t sz)
{
	HAMON_ASSERT_NOEXCEPT_TRUE(sp.size());
	return sp.size() == sz;
}

struct A {};

GTEST_TEST(SpanTest, SizeTest)
{
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(test(hamon::span<int>(),          0));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(test(hamon::span<long>(),         0));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(test(hamon::span<double>(),       0));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(test(hamon::span<A>(),            0));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(test(hamon::span<std::string>(),  0));

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(test(hamon::span<int, 0>(),         0));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(test(hamon::span<long, 0>(),        0));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(test(hamon::span<double, 0>(),      0));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(test(hamon::span<A, 0>(),           0));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(test(hamon::span<std::string, 0>(), 0));

	HAMON_CXX11_CONSTEXPR int arr[] = {10, 11, 12, 13, 14, 15, 16, 17, 18, 19};
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(test(hamon::span<int const>(arr, 1), 1));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(test(hamon::span<int const>(arr, 2), 2));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(test(hamon::span<int const>(arr, 3), 3));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(test(hamon::span<int const>(arr, 4), 4));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(test(hamon::span<int const>(arr, 5), 5));

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(test(hamon::span<int const, 1>(arr + 5, 1), 1));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(test(hamon::span<int const, 2>(arr + 4, 2), 2));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(test(hamon::span<int const, 3>(arr + 3, 3), 3));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(test(hamon::span<int const, 4>(arr + 2, 4), 4));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(test(hamon::span<int const, 5>(arr + 1, 5), 5));
}

}	// namespace size_test

}	// namespace hamon_span_test
