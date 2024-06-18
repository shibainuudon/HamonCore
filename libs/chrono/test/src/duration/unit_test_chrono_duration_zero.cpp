/**
 *	@file	unit_test_chrono_duration_zero.cpp
 *
 *	@brief	zero() のテスト
 *
 *	static constexpr duration zero() noexcept;
 */

#include <hamon/chrono/duration.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include <ratio>
#include "constexpr_test.hpp"

namespace hamon_chrono_test
{

namespace duration_zero_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Rep, typename Period>
HAMON_CXX14_CONSTEXPR bool test()
{
	using Duration = hamon::chrono::duration<Rep, Period>;

	static_assert(hamon::is_same<decltype(Duration::zero()), Duration>::value, "");
	static_assert(noexcept(Duration::zero()), "");

	VERIFY(Duration::zero().count() == 0);

	return true;
}

#undef VERIFY

GTEST_TEST(DurationTest, ZeroTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<int, std::ratio<60>>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<long, std::milli>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<double, std::ratio<1, 30>>()));
}

}	// namespace duration_zero_test

}	// namespace hamon_chrono_test
