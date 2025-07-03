/**
 *	@file	unit_test_chrono_time_point_time_point_cast.cpp
 *
 *	@brief	time_point_cast() のテスト
 *
 *	template<class ToDuration, class Clock, class Duration>
 *	constexpr time_point<Clock, ToDuration>
 *	time_point_cast(const time_point<Clock, Duration>& t);
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

namespace time_point_time_point_cast_test
{

struct MyClock
{};

template <typename ToDuration, typename Clock, typename Duration, typename = void>
struct is_invocable_time_point_cast
	: public hamon::false_type {};

template <typename ToDuration, typename Clock, typename Duration>
struct is_invocable_time_point_cast<ToDuration, Clock, Duration,
	hamon::void_t<decltype(hamon::chrono::time_point_cast<ToDuration>(hamon::declval<hamon::chrono::time_point<Clock, Duration>>()))>>
	: public hamon::true_type {};

static_assert( is_invocable_time_point_cast<hamon::chrono::duration<int>, MyClock, hamon::chrono::duration<int>>::value, "");
static_assert( is_invocable_time_point_cast<hamon::chrono::duration<int>, MyClock, hamon::chrono::duration<float>>::value, "");
static_assert( is_invocable_time_point_cast<hamon::chrono::duration<float>, MyClock, hamon::chrono::duration<int>>::value, "");
static_assert( is_invocable_time_point_cast<hamon::chrono::duration<float>, MyClock, hamon::chrono::duration<float>>::value, "");
static_assert(!is_invocable_time_point_cast<int, MyClock, hamon::chrono::duration<int>>::value, "");
//static_assert(!is_invocable_time_point_cast<hamon::chrono::duration<int>, MyClock, int>::value, "");

GTEST_TEST(TimePointTest, TimePointCastTest)
{
	using hamon::chrono::time_point_cast;
	{
		using Duration1 = hamon::chrono::duration<int, hamon::ratio<1, 1000>>;
		using Duration2 = hamon::chrono::duration<int, hamon::ratio<1>>;
		using TimePoint1 = hamon::chrono::time_point<MyClock, Duration1>;
		using TimePoint2 = hamon::chrono::time_point<MyClock, Duration2>;
		static_assert(hamon::is_same<
			decltype(time_point_cast<Duration2>(hamon::declval<TimePoint1>())),
			TimePoint2
		>::value, "");
#if !defined(HAMON_USE_STD_CHRONO)
		static_assert(noexcept(time_point_cast<Duration2>(hamon::declval<TimePoint1>())), "");
#endif

		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(time_point_cast<Duration2>(TimePoint1{Duration1{-3900}}).time_since_epoch().count(), -3);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(time_point_cast<Duration2>(TimePoint1{Duration1{-3500}}).time_since_epoch().count(), -3);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(time_point_cast<Duration2>(TimePoint1{Duration1{-3100}}).time_since_epoch().count(), -3);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(time_point_cast<Duration2>(TimePoint1{Duration1{-3000}}).time_since_epoch().count(), -3);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(time_point_cast<Duration2>(TimePoint1{Duration1{-2900}}).time_since_epoch().count(), -2);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(time_point_cast<Duration2>(TimePoint1{Duration1{-2500}}).time_since_epoch().count(), -2);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(time_point_cast<Duration2>(TimePoint1{Duration1{-2100}}).time_since_epoch().count(), -2);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(time_point_cast<Duration2>(TimePoint1{Duration1{-2000}}).time_since_epoch().count(), -2);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(time_point_cast<Duration2>(TimePoint1{Duration1{-1900}}).time_since_epoch().count(), -1);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(time_point_cast<Duration2>(TimePoint1{Duration1{-1500}}).time_since_epoch().count(), -1);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(time_point_cast<Duration2>(TimePoint1{Duration1{-1100}}).time_since_epoch().count(), -1);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(time_point_cast<Duration2>(TimePoint1{Duration1{-1000}}).time_since_epoch().count(), -1);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(time_point_cast<Duration2>(TimePoint1{Duration1{ -900}}).time_since_epoch().count(),  0);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(time_point_cast<Duration2>(TimePoint1{Duration1{ -500}}).time_since_epoch().count(),  0);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(time_point_cast<Duration2>(TimePoint1{Duration1{ -100}}).time_since_epoch().count(),  0);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(time_point_cast<Duration2>(TimePoint1{Duration1{    0}}).time_since_epoch().count(),  0);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(time_point_cast<Duration2>(TimePoint1{Duration1{  100}}).time_since_epoch().count(),  0);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(time_point_cast<Duration2>(TimePoint1{Duration1{  500}}).time_since_epoch().count(),  0);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(time_point_cast<Duration2>(TimePoint1{Duration1{  900}}).time_since_epoch().count(),  0);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(time_point_cast<Duration2>(TimePoint1{Duration1{ 1000}}).time_since_epoch().count(),  1);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(time_point_cast<Duration2>(TimePoint1{Duration1{ 1100}}).time_since_epoch().count(),  1);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(time_point_cast<Duration2>(TimePoint1{Duration1{ 1500}}).time_since_epoch().count(),  1);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(time_point_cast<Duration2>(TimePoint1{Duration1{ 1900}}).time_since_epoch().count(),  1);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(time_point_cast<Duration2>(TimePoint1{Duration1{ 2000}}).time_since_epoch().count(),  2);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(time_point_cast<Duration2>(TimePoint1{Duration1{ 2100}}).time_since_epoch().count(),  2);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(time_point_cast<Duration2>(TimePoint1{Duration1{ 2500}}).time_since_epoch().count(),  2);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(time_point_cast<Duration2>(TimePoint1{Duration1{ 2900}}).time_since_epoch().count(),  2);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(time_point_cast<Duration2>(TimePoint1{Duration1{ 3000}}).time_since_epoch().count(),  3);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(time_point_cast<Duration2>(TimePoint1{Duration1{ 3100}}).time_since_epoch().count(),  3);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(time_point_cast<Duration2>(TimePoint1{Duration1{ 3500}}).time_since_epoch().count(),  3);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(time_point_cast<Duration2>(TimePoint1{Duration1{ 3900}}).time_since_epoch().count(),  3);
	}
	{
		using Duration1 = hamon::chrono::duration<int, hamon::ratio<1, 1000>>;
		using Duration2 = hamon::chrono::duration<float, hamon::ratio<1>>;
		using TimePoint1 = hamon::chrono::time_point<MyClock, Duration1>;
		using TimePoint2 = hamon::chrono::time_point<MyClock, Duration2>;
		static_assert(hamon::is_same<
			decltype(time_point_cast<Duration2>(hamon::declval<TimePoint1>())),
			TimePoint2
		>::value, "");
#if !defined(HAMON_USE_STD_CHRONO)
		static_assert(noexcept(time_point_cast<Duration2>(hamon::declval<TimePoint1>())), "");
#endif

		{
			HAMON_CXX11_CONSTEXPR TimePoint1 d1{Duration1{1500}};
			HAMON_CXX11_CONSTEXPR TimePoint2 d2 = time_point_cast<Duration2>(d1);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(d2.time_since_epoch().count(), 1.5f);
		}
		{
			HAMON_CXX11_CONSTEXPR TimePoint1 d1{Duration1{-1500}};
			HAMON_CXX11_CONSTEXPR TimePoint2 d2 = time_point_cast<Duration2>(d1);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(d2.time_since_epoch().count(), -1.5f);
		}
	}
	{
		using Duration1 = hamon::chrono::duration<int, hamon::ratio<17>>;
		using Duration2 = hamon::chrono::duration<int, hamon::ratio<23>>;
		using TimePoint1 = hamon::chrono::time_point<MyClock, Duration1>;
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(time_point_cast<Duration2>(TimePoint1{Duration1{100}}).time_since_epoch().count(), 73);
	}
	{
		using Duration1 = hamon::chrono::duration<int, hamon::ratio<17>>;
		using Duration2 = hamon::chrono::duration<float, hamon::ratio<23>>;
		using TimePoint1 = hamon::chrono::time_point<MyClock, Duration1>;
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(time_point_cast<Duration2>(TimePoint1{Duration1{100}}).time_since_epoch().count(), 100.f / 23 * 17);	// ≒ 73.91304347826087
	}
}

}	// namespace time_point_time_point_cast_test

}	// namespace hamon_chrono_test
