﻿/**
 *	@file	unit_test_span_as_bytes.cpp
 *
 *	@brief	hamon::as_bytes() のテスト
 */

#include <hamon/span.hpp>
#include <hamon/cstddef/byte.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include <cstddef>
#include <string>
#include <type_traits>
#include "noexcept_test.hpp"

#define ASSERT_SAME_TYPE(...) \
    static_assert((std::is_same<__VA_ARGS__>::value), \
                 "Types differ unexpectedly")

namespace hamon_span_test
{

namespace as_bytes_test
{

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4307)	// 整数定数がオーバーフローしました。

template <typename Span>
void test(Span sp)
{
	HAMON_ASSERT_NOEXCEPT_TRUE(hamon::as_bytes(sp));

	auto sp_bytes = hamon::as_bytes(sp);
	using SB = decltype(sp_bytes);
	ASSERT_SAME_TYPE(hamon::byte const, typename SB::element_type);

	auto const e =
		(sp.extent == hamon::dynamic_extent) ?
		hamon::dynamic_extent :
		sizeof(typename Span::element_type) * sp.extent;
	EXPECT_TRUE(sp_bytes.extent == e);

	EXPECT_TRUE(static_cast<void const*>(sp_bytes.data()) == static_cast<void const*>(sp.data()));
	EXPECT_TRUE(sp_bytes.size() == sp.size_bytes());
}

HAMON_WARNING_POP()

struct A {};

GTEST_TEST(SpanTest, AsBytesTest)
{
	test(hamon::span<int>        ());
	test(hamon::span<long>       ());
	test(hamon::span<double>     ());
	test(hamon::span<A>          ());
	test(hamon::span<std::string>());

	test(hamon::span<int,         0>());
	test(hamon::span<long,        0>());
	test(hamon::span<double,      0>());
	test(hamon::span<A,           0>());
	test(hamon::span<std::string, 0>());

	int arr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	test(hamon::span<int>(arr, 1));
	test(hamon::span<int>(arr, 2));
	test(hamon::span<int>(arr, 3));
	test(hamon::span<int>(arr, 4));
	test(hamon::span<int>(arr, 5));

	test(hamon::span<int, 1>(arr + 5, 1));
	test(hamon::span<int, 2>(arr + 4, 2));
	test(hamon::span<int, 3>(arr + 3, 3));
	test(hamon::span<int, 4>(arr + 2, 4));
	test(hamon::span<int, 5>(arr + 1, 5));

	std::string s;
	test(hamon::span<std::string>(&s, static_cast<std::size_t>(0)));
	test(hamon::span<std::string>(&s, 1));
}

}	// namespace as_bytes_test

}	// namespace hamon_span_test

#undef ASSERT_SAME_TYPE