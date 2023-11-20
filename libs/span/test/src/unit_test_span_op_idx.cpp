/**
 *	@file	unit_test_span_op_idx.cpp
 *
 *	@brief	reference span::operator[](index_type idx) のテスト
 */

#include <hamon/span.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "noexcept_test.hpp"

namespace hamon_span_test
{

namespace op_idx_test
{

template <typename Span>
HAMON_CXX11_CONSTEXPR bool test(Span sp, hamon::size_t idx)
{
#if !defined(HAMON_USE_STD_SPAN)
	HAMON_ASSERT_NOEXCEPT_TRUE(sp[idx]);
#endif
	static_assert(hamon::is_same<decltype(sp[idx]), typename Span::reference>::value, "");
	return sp[idx] == *(sp.data() + idx);
}

GTEST_TEST(SpanTest, OpIdxTest)
{
	HAMON_CXX11_CONSTEXPR int arr[] = {10, 11, 12, 13, 14, 15, 16, 17, 18, 19};
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(test(hamon::span<int const>(arr, 1), 0));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(test(hamon::span<int const>(arr, 2), 0));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(test(hamon::span<int const>(arr, 2), 1));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(test(hamon::span<int const>(arr, 3), 0));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(test(hamon::span<int const>(arr, 3), 1));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(test(hamon::span<int const>(arr, 3), 2));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(test(hamon::span<int const>(arr, 4), 0));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(test(hamon::span<int const>(arr, 4), 1));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(test(hamon::span<int const>(arr, 4), 2));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(test(hamon::span<int const>(arr, 4), 3));

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(test(hamon::span<int const, 1>(arr, 1), 0));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(test(hamon::span<int const, 2>(arr, 2), 0));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(test(hamon::span<int const, 2>(arr, 2), 1));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(test(hamon::span<int const, 3>(arr, 3), 0));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(test(hamon::span<int const, 3>(arr, 3), 1));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(test(hamon::span<int const, 3>(arr, 3), 2));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(test(hamon::span<int const, 4>(arr, 4), 0));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(test(hamon::span<int const, 4>(arr, 4), 1));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(test(hamon::span<int const, 4>(arr, 4), 2));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(test(hamon::span<int const, 4>(arr, 4), 3));
}

}	// namespace op_idx_test

}	// namespace hamon_span_test
