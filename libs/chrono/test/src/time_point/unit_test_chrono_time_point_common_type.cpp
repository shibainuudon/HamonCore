/**
 *	@file	unit_test_chrono_time_point_common_type.cpp
 *
 *	@brief	common_type のテスト
 *
 *	template<class Clock, class Duration1, class Duration2>
 *	struct common_type<
 *		chrono::time_point<Clock, Duration1>,
 *		chrono::time_point<Clock, Duration2>>;
 */

#include <hamon/chrono/time_point.hpp>
#include <hamon/chrono/duration.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_chrono_test
{

namespace time_point_common_type_test
{

struct MyClock
{};

GTEST_TEST(TimePointTest, CommonTypeTest)
{
	{
		using Duration1 = hamon::chrono::duration<int, std::ratio<1>>;
		using Duration2 = hamon::chrono::duration<int, std::ratio<1>>;
		using TimePoint1 = hamon::chrono::time_point<MyClock, Duration1>;
		using TimePoint2 = hamon::chrono::time_point<MyClock, Duration2>;
		using CT = hamon::common_type_t<TimePoint1, TimePoint2>;
		static_assert(hamon::is_same<MyClock, typename CT::clock>::value, "");
		static_assert(hamon::is_same<int, typename CT::rep>::value, "");
		static_assert(1 == CT::period::num, "");
		static_assert(1 == CT::period::den, "");
	}
	{
		using Duration1 = hamon::chrono::duration<int,   std::ratio<3, 4>>;
		using Duration2 = hamon::chrono::duration<float, std::ratio<2, 3>>;
		using TimePoint1 = hamon::chrono::time_point<MyClock, Duration1>;
		using TimePoint2 = hamon::chrono::time_point<MyClock, Duration2>;
		using CT = hamon::common_type_t<TimePoint1, TimePoint2>;
		static_assert(hamon::is_same<MyClock, typename CT::clock>::value, "");
		static_assert(hamon::is_same<float, typename CT::rep>::value, "");
		static_assert( 1 == CT::period::num, "");
		static_assert(12 == CT::period::den, "");
	}
	{
		using Duration1 = hamon::chrono::duration<char, std::ratio<630>>;
		using Duration2 = hamon::chrono::duration<int,  std::ratio<300>>;
		using TimePoint1 = hamon::chrono::time_point<MyClock, Duration1>;
		using TimePoint2 = hamon::chrono::time_point<MyClock, Duration2>;
		using CT = hamon::common_type_t<TimePoint1, TimePoint2>;
		static_assert(hamon::is_same<MyClock, typename CT::clock>::value, "");
		static_assert(hamon::is_same<int, typename CT::rep>::value, "");
		static_assert(30 == CT::period::num, "");
		static_assert( 1 == CT::period::den, "");
	}
	{
		using Duration1 = hamon::chrono::duration<float,  std::ratio<100>>;
		using Duration2 = hamon::chrono::duration<double, std::ratio<1, 1000>>;
		using TimePoint1 = hamon::chrono::time_point<MyClock, Duration1>;
		using TimePoint2 = hamon::chrono::time_point<MyClock, Duration2>;
		using CT = hamon::common_type_t<TimePoint1, TimePoint2>;
		static_assert(hamon::is_same<MyClock, typename CT::clock>::value, "");
		static_assert(hamon::is_same<double, typename CT::rep>::value, "");
		static_assert(   1 == CT::period::num, "");
		static_assert(1000 == CT::period::den, "");
	}
}

}	// namespace time_point_common_type_test

}	// namespace hamon_chrono_test
