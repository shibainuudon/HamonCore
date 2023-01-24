/**
 *	@file	unit_test_span_end.cpp
 *
 *	@brief	iterator span::end() のテスト
 */

#include <hamon/span.hpp>
#include <gtest/gtest.h>
#include <string>
#include <type_traits>
#include "constexpr_test.hpp"

namespace hamon_span_test
{

namespace end_test
{

template <typename Span>
HAMON_CXX11_CONSTEXPR bool test1(Span s)
{
	static_assert(std::is_same<decltype(s.end()), typename Span::iterator>::value, "");
	return
		(s.end() == s.begin()) &&
		(static_cast<std::size_t>(s.end() - s.begin()) == s.size());
}

template <typename Span>
HAMON_CXX11_CONSTEXPR bool test2(Span s)
{
	static_assert(std::is_same<decltype(s.end()), typename Span::iterator>::value, "");
	return
		(s.end() != s.begin()) &&
		(&*(s.end()-1) == &*(s.begin() + std::ptrdiff_t(s.size()) - 1)) &&
		(static_cast<std::size_t>(s.end() - s.begin()) == s.size());
}

struct A{};
bool operator==(A, A) {return true;}

GTEST_TEST(SpanTest, EndTest)
{
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(test1(hamon::span<int>()));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(test1(hamon::span<long>()));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(test1(hamon::span<double>()));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(test1(hamon::span<A>()));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(test1(hamon::span<std::string>()));

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(test1(hamon::span<int, 0>()));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(test1(hamon::span<long, 0>()));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(test1(hamon::span<double, 0>()));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(test1(hamon::span<A, 0>()));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(test1(hamon::span<std::string, 0>()));

	HAMON_CXX11_CONSTEXPR int arr[] = {10, 11, 12, 13, 14, 15, 16, 17, 18, 19};
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(test2(hamon::span<int const>(arr, 1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(test2(hamon::span<int const>(arr, 2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(test2(hamon::span<int const>(arr, 3)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(test2(hamon::span<int const>(arr, 4)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(test2(hamon::span<int const>(arr, 5)));
}

}	// namespace end_test

}	// namespace hamon_span_test
