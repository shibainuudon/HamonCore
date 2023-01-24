/**
 *	@file	unit_test_span_data.cpp
 *
 *	@brief	pointer span::data() のテスト
 */

#include <hamon/span.hpp>
#include <gtest/gtest.h>
#include <string>
#include "constexpr_test.hpp"
#include "noexcept_test.hpp"

namespace hamon_span_test
{

namespace data_test
{

template <typename Span>
HAMON_CXX11_CONSTEXPR bool test(Span sp, typename Span::pointer ptr)
{
	HAMON_ASSERT_NOEXCEPT_TRUE(sp.data());
	return sp.data() == ptr;
}

struct A{};

GTEST_TEST(SpanTest, DataTest)
{
	HAMON_CXX11_CONSTEXPR int arr[] = {10, 11, 12, 13, 14, 15, 16, 17, 18, 19};
	//  dynamic size
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(test(hamon::span<int>(),         nullptr));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(test(hamon::span<long>(),        nullptr));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(test(hamon::span<double>(),      nullptr));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(test(hamon::span<A>(),           nullptr));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(test(hamon::span<std::string>(), nullptr));

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(test(hamon::span<int const>(arr, 1), arr));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(test(hamon::span<int const>(arr, 2), arr));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(test(hamon::span<int const>(arr, 3), arr));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(test(hamon::span<int const>(arr, 4), arr));

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(test(hamon::span<int const>(arr + 1, 1), arr + 1));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(test(hamon::span<int const>(arr + 2, 2), arr + 2));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(test(hamon::span<int const>(arr + 3, 3), arr + 3));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(test(hamon::span<int const>(arr + 4, 4), arr + 4));

	//  static size
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(test(hamon::span<int, 0>(),         nullptr));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(test(hamon::span<long, 0>(),        nullptr));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(test(hamon::span<double, 0>(),      nullptr));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(test(hamon::span<A, 0>(),           nullptr));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(test(hamon::span<std::string, 0>(), nullptr));

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(test(hamon::span<int const, 1>(arr, 1), arr));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(test(hamon::span<int const, 2>(arr, 2), arr));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(test(hamon::span<int const, 3>(arr, 3), arr));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(test(hamon::span<int const, 4>(arr, 4), arr));

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(test(hamon::span<int const, 1>(arr + 1, 1), arr + 1));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(test(hamon::span<int const, 2>(arr + 2, 2), arr + 2));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(test(hamon::span<int const, 3>(arr + 3, 3), arr + 3));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(test(hamon::span<int const, 4>(arr + 4, 4), arr + 4));
}

}	// namespace data_test

}	// namespace hamon_span_test
