/**
 *	@file	unit_test_chrono_duration_unary_plus.cpp
 *
 *	@brief	operator+() のテスト
 *
 *	constexpr common_type_t<duration> operator+() const;
 */

#include <hamon/chrono/duration.hpp>
#include <hamon/ratio.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_chrono_test
{

namespace duration_unary_plus_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Rep, typename Period>
HAMON_CXX14_CONSTEXPR bool test()
{
	using Duration = hamon::chrono::duration<Rep, Period>;

	Duration const d{10};
	static_assert(hamon::is_same<decltype(+d), Duration>::value, "");
#if !defined(HAMON_USE_STD_CHRONO)
	static_assert(noexcept(+d), "");
#endif

	auto const d2 = +d;
	VERIFY(d2.count() == 10);

	return true;
}

#undef VERIFY

GTEST_TEST(DurationTest, UnaryPlusTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<int, hamon::ratio<60>>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<long, hamon::milli>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<double, hamon::ratio<1, 30>>()));
}

}	// namespace duration_unary_plus_test

}	// namespace hamon_chrono_test
