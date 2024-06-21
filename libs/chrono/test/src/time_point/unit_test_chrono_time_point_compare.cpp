/**
 *	@file	unit_test_chrono_time_point_compare.cpp
 *
 *	@brief	operator+() のテスト
 *
 *	template<class Clock, class Duration1, class Duration2>
 *	constexpr bool operator==(const time_point<Clock, Duration1>& lhs, const time_point<Clock, Duration2>& rhs);
 *	
 *	template<class Clock, class Duration1, class Duration2>
 *	constexpr bool operator<(const time_point<Clock, Duration1>& lhs, const time_point<Clock, Duration2>& rhs);
 *	
 *	template<class Clock, class Duration1, class Duration2>
 *	constexpr bool operator>(const time_point<Clock, Duration1>& lhs, const time_point<Clock, Duration2>& rhs);
 *	
 *	template<class Clock, class Duration1, class Duration2>
 *	constexpr bool operator<=(const time_point<Clock, Duration1>& lhs, const time_point<Clock, Duration2>& rhs);
 *	
 *	template<class Clock, class Duration1, class Duration2>
 *	constexpr bool operator>=(const time_point<Clock, Duration1>& lhs, const time_point<Clock, Duration2>& rhs);
 *	
 *	template<class Clock, class Duration1,
 *	three_way_comparable_with<Duration1> Duration2>
 *	constexpr auto operator<=>(const time_point<Clock, Duration1>& lhs, const time_point<Clock, Duration2>& rhs);
 */

#include <hamon/chrono/time_point.hpp>
#include <hamon/chrono/duration.hpp>
#include <hamon/compare.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_chrono_test
{

namespace time_point_compare_test
{

struct MyClock
{};

GTEST_TEST(TimePointTest, CompareTest)
{
	using Duration1 = hamon::chrono::duration<int, std::ratio<60>>;
	using Duration2 = hamon::chrono::duration<short, std::ratio<1>>;
	using TimePoint1 = hamon::chrono::time_point<MyClock, Duration1>;
	using TimePoint2 = hamon::chrono::time_point<MyClock, Duration2>;

	static_assert(hamon::is_same<decltype(hamon::declval<TimePoint1>() == hamon::declval<TimePoint2>()), bool>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<TimePoint1>() != hamon::declval<TimePoint2>()), bool>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<TimePoint1>() <  hamon::declval<TimePoint2>()), bool>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<TimePoint1>() >  hamon::declval<TimePoint2>()), bool>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<TimePoint1>() <= hamon::declval<TimePoint2>()), bool>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<TimePoint1>() >= hamon::declval<TimePoint2>()), bool>::value, "");

#if !defined(HAMON_USE_STD_CHRONO)
	static_assert(noexcept(hamon::declval<TimePoint1>() == hamon::declval<TimePoint2>()), "");
	static_assert(noexcept(hamon::declval<TimePoint1>() != hamon::declval<TimePoint2>()), "");
	static_assert(noexcept(hamon::declval<TimePoint1>() <  hamon::declval<TimePoint2>()), "");
	static_assert(noexcept(hamon::declval<TimePoint1>() >  hamon::declval<TimePoint2>()), "");
	static_assert(noexcept(hamon::declval<TimePoint1>() <= hamon::declval<TimePoint2>()), "");
	static_assert(noexcept(hamon::declval<TimePoint1>() >= hamon::declval<TimePoint2>()), "");
#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
	static_assert(noexcept(hamon::declval<TimePoint1>() <=> hamon::declval<TimePoint2>()), "");
#endif
#endif

	{
		HAMON_CXX11_CONSTEXPR TimePoint1 tp1{Duration1{1}};
		HAMON_CXX11_CONSTEXPR TimePoint2 tp2{Duration2{1}};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!(tp1 == tp2));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( (tp1 != tp2));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!(tp1 <  tp2));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( (tp1 >  tp2));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!(tp1 <= tp2));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( (tp1 >= tp2));
#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::is_gt(tp1 <=> tp2));
#endif
	}
	{
		HAMON_CXX11_CONSTEXPR TimePoint1 tp1{Duration1{1}};
		HAMON_CXX11_CONSTEXPR TimePoint2 tp2{Duration2{60}};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( (tp1 == tp2));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!(tp1 != tp2));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!(tp1 <  tp2));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!(tp1 >  tp2));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( (tp1 <= tp2));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( (tp1 >= tp2));
#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::is_eq(tp1 <=> tp2));
#endif
	}
	{
		HAMON_CXX11_CONSTEXPR TimePoint1 tp1{Duration1{1}};
		HAMON_CXX11_CONSTEXPR TimePoint2 tp2{Duration2{61}};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!(tp1 == tp2));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( (tp1 != tp2));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( (tp1 <  tp2));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!(tp1 >  tp2));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( (tp1 <= tp2));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!(tp1 >= tp2));
#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::is_lt(tp1 <=> tp2));
#endif
	}
}

}	// namespace time_point_compare_test

}	// namespace hamon_chrono_test
