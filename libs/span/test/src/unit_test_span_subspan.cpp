/**
 *	@file	unit_test_span_subspan.cpp
 *
 *	@brief	span::subspan() のテスト
 */

#include <hamon/span.hpp>
#include <hamon/algorithm/equal.hpp>
#include <gtest/gtest.h>
#include <cstddef>
#include <type_traits>
#include "constexpr_test.hpp"
#include "noexcept_test.hpp"

#define ASSERT_SAME_TYPE(...) \
    static_assert((std::is_same<__VA_ARGS__>::value), \
                 "Types differ unexpectedly")

namespace hamon_span_test
{

namespace subspan_test
{

template <std::size_t Offset, std::size_t Count, typename Span, typename S1, typename S2>
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

template <std::size_t Offset, std::size_t Count, typename Span>
HAMON_CXX11_CONSTEXPR bool test1(Span sp)
{
	HAMON_ASSERT_NOEXCEPT_TRUE(sp.template subspan<Offset, Count>());
	HAMON_ASSERT_NOEXCEPT_TRUE(sp.subspan(Offset, Count));
	return test1_sub<Offset, Count, Span>(sp.template subspan<Offset, Count>(), sp.subspan(Offset, Count));
}

template <std::size_t Offset, std::size_t Count, typename Span>
HAMON_CXX14_CONSTEXPR bool test2(Span sp)
{
	auto s1 = sp.template subspan<Offset, Count>();
	auto s2 = sp.subspan(Offset, Count);
	return
		hamon::equal(s1.begin(), s1.end(), sp.begin() + Offset) &&
		hamon::equal(s2.begin(), s2.end(), sp.begin() + Offset);
}

template <std::size_t Offset, typename Span, typename S1, typename S2>
HAMON_CXX11_CONSTEXPR bool test1_sub(S1 s1, S2 s2)
{
	ASSERT_SAME_TYPE(typename Span::value_type, typename S1::value_type);
	ASSERT_SAME_TYPE(typename Span::value_type, typename S2::value_type);
	static_assert(S1::extent == (Span::extent == hamon::dynamic_extent ? hamon::dynamic_extent : Span::extent - Offset), "");
	static_assert(S2::extent == hamon::dynamic_extent, "");
	return
		s1.data() == s2.data() &&
		s1.size() == s2.size();
}

template <std::size_t Offset, typename Span>
HAMON_CXX11_CONSTEXPR bool test1(Span sp)
{
	HAMON_ASSERT_NOEXCEPT_TRUE(sp.template subspan<Offset>());
	HAMON_ASSERT_NOEXCEPT_TRUE(sp.subspan(Offset));
	return test1_sub<Offset, Span>(sp.template subspan<Offset>(), sp.subspan(Offset));
}

template <std::size_t Offset, typename Span>
HAMON_CXX14_CONSTEXPR bool test2(Span sp)
{
	auto s1 = sp.template subspan<Offset>();
	auto s2 = sp.subspan(Offset);
	return
		hamon::equal(s1.begin(), s1.end(), sp.begin() + Offset, sp.end()) &&
		hamon::equal(s2.begin(), s2.end(), sp.begin() + Offset, sp.end());
}

GTEST_TEST(SpanTest, SubspanTest)
{
	HAMON_CXX14_CONSTEXPR int carr1[] = {1, 2, 3, 4};
	{
		using Sp = hamon::span<const int>;
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((test1<0>(Sp{})));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((test1<0, 4>(Sp{carr1})));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((test1<0, 3>(Sp{carr1})));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((test1<0, 2>(Sp{carr1})));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((test1<0, 1>(Sp{carr1})));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((test1<0, 0>(Sp{carr1})));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((test1<1, 3>(Sp{carr1})));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((test1<2, 2>(Sp{carr1})));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((test1<3, 1>(Sp{carr1})));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((test1<4, 0>(Sp{carr1})));

		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test2<0>(Sp{})));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test2<0, 4>(Sp{carr1})));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test2<0, 3>(Sp{carr1})));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test2<0, 2>(Sp{carr1})));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test2<0, 1>(Sp{carr1})));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test2<0, 0>(Sp{carr1})));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test2<1, 3>(Sp{carr1})));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test2<2, 2>(Sp{carr1})));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test2<3, 1>(Sp{carr1})));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test2<4, 0>(Sp{carr1})));
	}

	{
		using Sp = hamon::span<const int, 4>;
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((test1<0, 4>(Sp{carr1})));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((test1<0, 3>(Sp{carr1})));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((test1<0, 2>(Sp{carr1})));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((test1<0, 1>(Sp{carr1})));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((test1<0, 0>(Sp{carr1})));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((test1<1, 3>(Sp{carr1})));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((test1<2, 2>(Sp{carr1})));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((test1<3, 1>(Sp{carr1})));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((test1<4, 0>(Sp{carr1})));

		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test2<0, 4>(Sp{carr1})));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test2<0, 3>(Sp{carr1})));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test2<0, 2>(Sp{carr1})));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test2<0, 1>(Sp{carr1})));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test2<0, 0>(Sp{carr1})));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test2<1, 3>(Sp{carr1})));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test2<2, 2>(Sp{carr1})));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test2<3, 1>(Sp{carr1})));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test2<4, 0>(Sp{carr1})));
	}

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

}	// namespace subspan_test

}	// namespace hamon_span_test

#undef ASSERT_SAME_TYPE
