/**
 *	@file	unit_test_chrono_time_point_min.cpp
 *
 *	@brief	min() のテスト
 *
 *	static constexpr time_point min() noexcept;
 */

#include <hamon/chrono/time_point.hpp>
#include <hamon/chrono/duration.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_chrono_test
{

namespace time_point_min_test
{

struct MyClock
{};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Clock, typename Duration>
HAMON_CXX14_CONSTEXPR bool test()
{
	using TimePoint = hamon::chrono::time_point<Clock, Duration>;

	static_assert(hamon::is_same<decltype(TimePoint::min()), TimePoint>::value, "");
	static_assert(noexcept(TimePoint::min()), "");

	VERIFY(TimePoint::min().time_since_epoch() == Duration::min());

	return true;
}

#undef VERIFY

GTEST_TEST(TimePointTest, MinTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<MyClock, hamon::chrono::duration<int, std::ratio<60>>>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<MyClock, hamon::chrono::duration<long, std::milli>>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<MyClock, hamon::chrono::duration<float, std::ratio<1, 30>>>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<MyClock, hamon::chrono::duration<double, std::ratio<120>>>()));
}

}	// namespace time_point_min_test

}	// namespace hamon_chrono_test
