/**
 *	@file	unit_test_span_make_span.cpp
 *
 *	@brief	make_span のテスト
 */

#include <hamon/span.hpp>
#include <hamon/algorithm/equal.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/iterator/begin.hpp>
#include <hamon/iterator/end.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/array.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include <array>

namespace hamon_span_test
{
namespace make_span_test
{

#define ASSERT_SAME_TYPE(...) \
    static_assert((hamon::is_same<__VA_ARGS__>::value), \
                 "Types differ unexpectedly")

template <typename T>
struct MyRange
{
	HAMON_CXX14_CONSTEXPR MyRange() : m_value{} {}
	HAMON_CXX14_CONSTEXPR hamon::size_t size() const noexcept { return 1; }
	HAMON_CXX14_CONSTEXPR T      * data()        noexcept { return &m_value; }
	HAMON_CXX14_CONSTEXPR T const* data()  const noexcept { return &m_value; }
	HAMON_CXX14_CONSTEXPR T      * begin()       noexcept { return &m_value; }
	HAMON_CXX14_CONSTEXPR T const* begin() const noexcept { return &m_value; }
	HAMON_CXX14_CONSTEXPR T      * end()         noexcept { return &m_value + 1; }
	HAMON_CXX14_CONSTEXPR T const* end()   const noexcept { return &m_value + 1; }

	HAMON_CXX14_CONSTEXPR T const* getV() const noexcept { return &m_value; } // for checking
	T m_value;
};

GTEST_TEST(SpanTest, MakeSpanTest)
{
	// It, EndOrSize
	{
		int arr[] = { 1,2,3 };
		auto s = hamon::make_span(hamon::begin(arr), hamon::end(arr));
		ASSERT_SAME_TYPE(decltype(s), hamon::span<int, hamon::dynamic_extent>);
		EXPECT_TRUE((hamon::equal(hamon::begin(arr), hamon::end(arr), s.begin(), s.end())));
	}
	{
		int arr[] = { 1,2,3 };
		auto s = hamon::make_span(hamon::begin(arr), 3u);
		ASSERT_SAME_TYPE(decltype(s), hamon::span<int, hamon::dynamic_extent>);
		EXPECT_TRUE((hamon::equal(hamon::begin(arr), hamon::end(arr), s.begin(), s.end())));
	}

	// T(&)[N]
	{
		int arr[] = { 1,2,3 };
		auto s = hamon::make_span(arr);
		ASSERT_SAME_TYPE(decltype(s), hamon::span<int, 3>);
		EXPECT_TRUE((hamon::equal(hamon::begin(arr), hamon::end(arr), s.begin(), s.end())));
	}

	// hamon::array<T, N>&
	{
		hamon::array<double, 4> arr = { 1.0, 2.0, 3.0, 4.0 };
		auto s = hamon::make_span(arr);
		ASSERT_SAME_TYPE(decltype(s), hamon::span<double, 4>);
		EXPECT_TRUE((hamon::equal(hamon::begin(arr), hamon::end(arr), s.begin(), s.end())));
	}

	// hamon::array<T, N> const&
	{
		hamon::array<long, 5> const arr = { 4, 5, 6, 7, 8 };
		auto s = hamon::make_span(arr);
		ASSERT_SAME_TYPE(decltype(s), hamon::span<long const, 5>);
		EXPECT_TRUE((hamon::equal(hamon::begin(arr), hamon::end(arr), s.begin(), s.end())));
	}

	// std::array<T, N>&
	{
		std::array<double, 4> arr = { 1.0, 2.0, 3.0, 4.0 };
		auto s = hamon::make_span(arr);
		ASSERT_SAME_TYPE(decltype(s), hamon::span<double, 4>);
		EXPECT_TRUE((hamon::equal(hamon::begin(arr), hamon::end(arr), s.begin(), s.end())));
	}

	// std::array<T, N> const&
	{
		std::array<long, 5> const arr = { 4, 5, 6, 7, 8 };
		auto s = hamon::make_span(arr);
		ASSERT_SAME_TYPE(decltype(s), hamon::span<long const, 5>);
		EXPECT_TRUE((hamon::equal(hamon::begin(arr), hamon::end(arr), s.begin(), s.end())));
	}

	// Range&&
	{
		MyRange<int> r;
		auto s = hamon::make_span(r);
		ASSERT_SAME_TYPE(decltype(s), hamon::span<int>);
		EXPECT_TRUE(static_cast<hamon::size_t>(s.size()) == r.size());
		EXPECT_TRUE((hamon::equal(hamon::begin(r), hamon::end(r), s.begin(), s.end())));
	}
	{
		MyRange<char> const r;
		auto s = hamon::make_span(r);
		ASSERT_SAME_TYPE(decltype(s), hamon::span<char const>);
		EXPECT_TRUE(static_cast<hamon::size_t>(s.size()) == r.size());
		EXPECT_TRUE((hamon::equal(hamon::begin(r), hamon::end(r), s.begin(), s.end())));
	}
}

#undef ASSERT_SAME_TYPE

}	// namespace make_span_test
}	// namespace hamon_span_test
