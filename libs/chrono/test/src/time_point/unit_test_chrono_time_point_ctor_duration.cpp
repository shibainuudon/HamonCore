/**
 *	@file	unit_test_chrono_time_point_ctor_duration.cpp
 *
 *	@brief	durationからのコンストラクタのテスト
 *
 *	constexpr explicit time_point(const duration& d);
 */

#include <hamon/chrono/time_point.hpp>
#include <hamon/chrono/duration.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_chrono_test
{

namespace time_point_ctor_duration_test
{

struct MyClock
{};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Clock, typename Duration>
HAMON_CXX14_CONSTEXPR bool test()
{
	using TimePoint = hamon::chrono::time_point<Clock, Duration>;

	static_assert( hamon::is_constructible<TimePoint, Duration const&>::value, "");
#if !defined(HAMON_USE_STD_CHRONO)
	static_assert( hamon::is_nothrow_constructible<TimePoint, Duration const&>::value, "");
#endif
	static_assert(!hamon::is_trivially_constructible<TimePoint, Duration const&>::value, "");
	static_assert(!hamon::is_implicitly_constructible<TimePoint, Duration const&>::value, "");

	Duration d{13};
	TimePoint tp{d};
	VERIFY(tp.time_since_epoch() == d);

	return true;
}

#undef VERIFY

GTEST_TEST(TimePointTest, CtorDurationTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<MyClock, hamon::chrono::duration<int, std::ratio<1, 1000>>>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<MyClock, hamon::chrono::duration<float>>()));
}

}	// namespace time_point_ctor_duration_test

}	// namespace hamon_chrono_test
