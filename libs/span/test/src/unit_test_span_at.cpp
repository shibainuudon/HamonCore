/**
 *	@file	unit_test_span_at.cpp
 *
 *	@brief	at のテスト
 *
 *	constexpr reference at(size_type idx) const;                            // freestanding-deleted
 */

#include <hamon/span.hpp>
#include <hamon/stdexcept/out_of_range.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_span_test
{

namespace at_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test()
{
	int a[] {1, 2, 3};
	{
		using Span = hamon::span<int>;
		Span sp(a, 2);
		static_assert(hamon::is_same<decltype(sp.at(0)), typename Span::reference>::value, "");
		VERIFY(sp.at(0) == 1);
		VERIFY(sp.at(1) == 2);
	}
	{
		using Span = hamon::span<int, 3>;
		Span sp(a);
		static_assert(hamon::is_same<decltype(sp.at(0)), typename Span::reference>::value, "");
		VERIFY(sp.at(0) == 1);
		VERIFY(sp.at(1) == 2);
		VERIFY(sp.at(2) == 3);
	}
	return true;
}

#undef VERIFY

GTEST_TEST(SpanTest, AtTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test());

	int a[] = {10,11,12,13,14};
	{
		hamon::span<int> v(a, 3);
		EXPECT_EQ(10, v.at(0));
		EXPECT_EQ(11, v.at(1));
		EXPECT_EQ(12, v.at(2));
#if !defined(HAMON_NO_EXCEPTIONS)
		EXPECT_THROW((void)v.at(3), hamon::out_of_range);
#endif
	}
	{
		hamon::span<int, 5> const v(a);
		EXPECT_EQ(10, v.at(0));
		EXPECT_EQ(11, v.at(1));
		EXPECT_EQ(12, v.at(2));
		EXPECT_EQ(13, v.at(3));
		EXPECT_EQ(14, v.at(4));
#if !defined(HAMON_NO_EXCEPTIONS)
		EXPECT_THROW((void)v.at(5), hamon::out_of_range);
#endif
	}
}

}	// namespace at_test

}	// namespace hamon_span_test
