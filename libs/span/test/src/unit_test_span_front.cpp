/**
 *	@file	unit_test_span_front.cpp
 *
 *	@brief	reference span::front() のテスト
 */

#include <hamon/span.hpp>
#include <hamon/memory/addressof.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "noexcept_test.hpp"

namespace hamon_span_test
{

namespace front_test
{

template <typename Span>
HAMON_CXX11_CONSTEXPR bool test(Span sp)
{
#if !defined(HAMON_USE_STD_SPAN)
	HAMON_ASSERT_NOEXCEPT_TRUE(sp.front());
#endif
	return hamon::addressof(sp.front()) == sp.data();
}

GTEST_TEST(SpanTest, FrontTest)
{
	HAMON_CXX11_CONSTEXPR int arr[] = {10, 11, 12, 13, 14, 15, 16, 17, 18, 19};
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(test(hamon::span<int const>(arr + 5, 1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(test(hamon::span<int const>(arr + 4, 2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(test(hamon::span<int const>(arr + 3, 3)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(test(hamon::span<int const>(arr + 2, 4)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(test(hamon::span<int const>(arr + 1, 5)));

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(test(hamon::span<int const, 1>(arr + 5, 1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(test(hamon::span<int const, 2>(arr + 4, 2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(test(hamon::span<int const, 3>(arr + 3, 3)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(test(hamon::span<int const, 4>(arr + 2, 4)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(test(hamon::span<int const, 5>(arr + 1, 5)));
}

}	// namespace front_test

}	// namespace hamon_span_test
