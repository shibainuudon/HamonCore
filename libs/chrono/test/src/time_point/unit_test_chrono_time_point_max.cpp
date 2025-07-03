/**
 *	@file	unit_test_chrono_time_point_max.cpp
 *
 *	@brief	max() のテスト
 *
 *	static constexpr time_point max() noexcept;
 */

#include <hamon/chrono/time_point.hpp>
#include <hamon/chrono/duration.hpp>
#include <hamon/ratio.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_chrono_test
{

namespace time_point_max_test
{

struct MyClock
{};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Clock, typename Duration>
HAMON_CXX14_CONSTEXPR bool test()
{
	using TimePoint = hamon::chrono::time_point<Clock, Duration>;

	static_assert(hamon::is_same<decltype(TimePoint::max()), TimePoint>::value, "");
	static_assert(noexcept(TimePoint::max()), "");

	VERIFY(TimePoint::max().time_since_epoch() == Duration::max());

	return true;
}

#undef VERIFY

GTEST_TEST(TimePointTest, MaxTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<MyClock, hamon::chrono::duration<int, hamon::ratio<60>>>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<MyClock, hamon::chrono::duration<long, hamon::milli>>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<MyClock, hamon::chrono::duration<float, hamon::ratio<1, 30>>>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<MyClock, hamon::chrono::duration<double, hamon::ratio<120>>>()));
}

}	// namespace time_point_max_test

}	// namespace hamon_chrono_test
