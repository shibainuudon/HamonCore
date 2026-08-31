/**
 *	@file	unit_test_span_first.cpp
 *
 *	@brief	span::first() のテスト
 */

#include <hamon/span.hpp>
#include <hamon/algorithm/equal.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "noexcept_test.hpp"

#define ASSERT_SAME_TYPE(...) \
    static_assert((hamon::is_same<__VA_ARGS__>::value), \
                 "Types differ unexpectedly")

namespace hamon_span_test
{

namespace first_test
{

template <hamon::size_t Count, typename Span, typename S1, typename S2>
HAMON_CXX11_CONSTEXPR bool test1_sub(S1 s1, S2 s2)
{
	ASSERT_SAME_TYPE(typename Span::value_type, typename S1::value_type);
	ASSERT_SAME_TYPE(typename Span::value_type, typename S2::value_type);
	static_assert(S1::extent == Count, "");
	static_assert(S2::extent == hamon::dynamic_extent, "");
	return
		s1.data() == s2.data() &&
		s1.size() == s2.size();
}

template <hamon::size_t Count, typename Span>
HAMON_CXX11_CONSTEXPR bool test1(Span sp)
{
	HAMON_ASSERT_NOEXCEPT_TRUE(sp.template first<Count>());
	HAMON_ASSERT_NOEXCEPT_TRUE(sp.first(Count));
	return test1_sub<Count, Span>(sp.template first<Count>(), sp.first(Count));
}

template <typename Span, typename S1, typename S2>
HAMON_CXX14_CONSTEXPR bool test2_sub(Span sp, S1 s1, S2 s2)
{
	return
		hamon::equal(s1.begin(), s1.end(), sp.begin()) &&
		hamon::equal(s2.begin(), s2.end(), sp.begin());
}

template <hamon::size_t Count, typename Span>
HAMON_CXX14_CONSTEXPR bool test2(Span sp)
{
	return test2_sub(sp, sp.template first<Count>(), sp.first(Count));
}

GTEST_TEST(SpanTest, FirstTest)
{
	HAMON_CXX14_CONSTEXPR int carr1[] = {1, 2, 3, 4};
	{
		using Sp = hamon::span<const int>;
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((test1<0>(Sp{})));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((test1<0>(Sp{carr1})));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((test1<1>(Sp{carr1})));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((test1<2>(Sp{carr1})));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((test1<3>(Sp{carr1})));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((test1<4>(Sp{carr1})));

		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test2<0>(Sp{})));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test2<0>(Sp{carr1})));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test2<1>(Sp{carr1})));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test2<2>(Sp{carr1})));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test2<3>(Sp{carr1})));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test2<4>(Sp{carr1})));
	}
	{
		using Sp = hamon::span<const int, 4>;
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((test1<0>(Sp{carr1})));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((test1<1>(Sp{carr1})));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((test1<2>(Sp{carr1})));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((test1<3>(Sp{carr1})));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((test1<4>(Sp{carr1})));

		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test2<0>(Sp{carr1})));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test2<1>(Sp{carr1})));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test2<2>(Sp{carr1})));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test2<3>(Sp{carr1})));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test2<4>(Sp{carr1})));
	}
}

}	// namespace first_test

}	// namespace hamon_span_test

#undef ASSERT_SAME_TYPE
