/**
 *	@file	unit_test_chrono_duration_max.cpp
 *
 *	@brief	max() のテスト
 *
 *	static constexpr duration max() noexcept;
 */

#include <hamon/chrono/duration.hpp>
#include <hamon/ratio.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/limits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_chrono_test
{

namespace duration_max_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Rep, typename Period>
HAMON_CXX14_CONSTEXPR bool test()
{
	using Duration = hamon::chrono::duration<Rep, Period>;

	static_assert(hamon::is_same<decltype(Duration::max()), Duration>::value, "");
	static_assert(noexcept(Duration::max()), "");

	VERIFY(Duration::max().count() == hamon::numeric_limits<Rep>::max());

	return true;
}

#undef VERIFY

GTEST_TEST(DurationTest, MaxTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<int, hamon::ratio<60>>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<long, hamon::milli>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<double, hamon::ratio<1, 30>>()));
}

}	// namespace duration_max_test

}	// namespace hamon_chrono_test
