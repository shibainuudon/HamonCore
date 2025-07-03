/**
 *	@file	unit_test_chrono_time_point_ctor_conv.cpp
 *
 *	@brief	変換コンストラクタのテスト
 *
 *	template<class Duration2>
 *	constexpr time_point(const time_point<clock, Duration2>& t);
 */

#include <hamon/chrono/time_point.hpp>
#include <hamon/chrono/duration.hpp>
#include <hamon/ratio.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_chrono_test
{

namespace time_point_ctor_conv_test
{

struct MyClock
{};

struct MyClock2
{};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Clock, typename Rep>
HAMON_CXX14_CONSTEXPR bool test_integer()
{
	using hamon::chrono::duration;
	using hamon::chrono::time_point;
	using Duration = duration<Rep, hamon::micro>;
	using TimePoint = time_point<Clock, Duration>;

	static_assert(!hamon::is_constructible<TimePoint, time_point<Clock, duration<int, hamon::nano>>>::value, "");
	static_assert( hamon::is_constructible<TimePoint, time_point<Clock, duration<int, hamon::micro>>>::value, "");
	static_assert( hamon::is_constructible<TimePoint, time_point<Clock, duration<int, hamon::milli>>>::value, "");
	static_assert(!hamon::is_constructible<TimePoint, time_point<Clock, duration<float, hamon::nano>>>::value, "");
	static_assert(!hamon::is_constructible<TimePoint, time_point<Clock, duration<float, hamon::micro>>>::value, "");
	static_assert(!hamon::is_constructible<TimePoint, time_point<Clock, duration<float, hamon::milli>>>::value, "");
	static_assert(!hamon::is_constructible<TimePoint, time_point<MyClock2, duration<int, hamon::nano>>>::value, "");
	static_assert(!hamon::is_constructible<TimePoint, time_point<MyClock2, duration<int, hamon::micro>>>::value, "");
	static_assert(!hamon::is_constructible<TimePoint, time_point<MyClock2, duration<int, hamon::milli>>>::value, "");

#if !defined(HAMON_USE_STD_CHRONO)
	static_assert( hamon::is_nothrow_constructible<TimePoint, time_point<Clock, duration<int, hamon::milli>>>::value, "");
#endif
	static_assert(!hamon::is_trivially_constructible<TimePoint, time_point<Clock, duration<int, hamon::milli>>>::value, "");
	static_assert( hamon::is_implicitly_constructible<TimePoint, time_point<Clock, duration<int, hamon::milli>>>::value, "");

	{
		using Duration2 = duration<int, hamon::milli>;
		using TimePoint2 = time_point<Clock, Duration2>;
		TimePoint2 ms(Duration2{3});
		TimePoint tp{ms};
		VERIFY(tp.time_since_epoch().count() == 3000);
	}
	return true;
}

template <typename Clock, typename Rep>
HAMON_CXX14_CONSTEXPR bool test_float()
{
	using hamon::chrono::duration;
	using hamon::chrono::time_point;
	using Duration = duration<Rep, hamon::micro>;
	using TimePoint = time_point<Clock, Duration>;

	static_assert( hamon::is_constructible<TimePoint, time_point<Clock, duration<int, hamon::nano>>>::value, "");
	static_assert( hamon::is_constructible<TimePoint, time_point<Clock, duration<int, hamon::micro>>>::value, "");
	static_assert( hamon::is_constructible<TimePoint, time_point<Clock, duration<int, hamon::milli>>>::value, "");
	static_assert( hamon::is_constructible<TimePoint, time_point<Clock, duration<float, hamon::nano>>>::value, "");
	static_assert( hamon::is_constructible<TimePoint, time_point<Clock, duration<float, hamon::micro>>>::value, "");
	static_assert( hamon::is_constructible<TimePoint, time_point<Clock, duration<float, hamon::milli>>>::value, "");
	static_assert(!hamon::is_constructible<TimePoint, time_point<MyClock2, duration<int, hamon::nano>>>::value, "");
	static_assert(!hamon::is_constructible<TimePoint, time_point<MyClock2, duration<int, hamon::micro>>>::value, "");
	static_assert(!hamon::is_constructible<TimePoint, time_point<MyClock2, duration<int, hamon::milli>>>::value, "");

#if !defined(HAMON_USE_STD_CHRONO)
	static_assert( hamon::is_nothrow_constructible<TimePoint, time_point<Clock, duration<int, hamon::nano>>>::value, "");
	static_assert( hamon::is_nothrow_constructible<TimePoint, time_point<Clock, duration<int, hamon::micro>>>::value, "");
	static_assert( hamon::is_nothrow_constructible<TimePoint, time_point<Clock, duration<int, hamon::milli>>>::value, "");
	static_assert( hamon::is_nothrow_constructible<TimePoint, time_point<Clock, duration<float, hamon::nano>>>::value, "");
//	static_assert( hamon::is_nothrow_constructible<TimePoint, time_point<Clock, duration<float, hamon::micro>>>::value, "");
	static_assert( hamon::is_nothrow_constructible<TimePoint, time_point<Clock, duration<float, hamon::milli>>>::value, "");
#endif

	static_assert(!hamon::is_trivially_constructible<TimePoint, time_point<Clock, duration<int, hamon::nano>>>::value, "");
	static_assert(!hamon::is_trivially_constructible<TimePoint, time_point<Clock, duration<int, hamon::micro>>>::value, "");
	static_assert(!hamon::is_trivially_constructible<TimePoint, time_point<Clock, duration<int, hamon::milli>>>::value, "");
	static_assert(!hamon::is_trivially_constructible<TimePoint, time_point<Clock, duration<float, hamon::nano>>>::value, "");
//	static_assert(!hamon::is_trivially_constructible<TimePoint, time_point<Clock, duration<float, hamon::micro>>>::value, "");
	static_assert(!hamon::is_trivially_constructible<TimePoint, time_point<Clock, duration<float, hamon::milli>>>::value, "");

	static_assert( hamon::is_implicitly_constructible<TimePoint, time_point<Clock, duration<int, hamon::nano>>>::value, "");
	static_assert( hamon::is_implicitly_constructible<TimePoint, time_point<Clock, duration<int, hamon::micro>>>::value, "");
	static_assert( hamon::is_implicitly_constructible<TimePoint, time_point<Clock, duration<int, hamon::milli>>>::value, "");
	static_assert( hamon::is_implicitly_constructible<TimePoint, time_point<Clock, duration<float, hamon::nano>>>::value, "");
//	static_assert( hamon::is_implicitly_constructible<TimePoint, time_point<Clock, duration<float, hamon::micro>>>::value, "");
	static_assert( hamon::is_implicitly_constructible<TimePoint, time_point<Clock, duration<float, hamon::milli>>>::value, "");

	{
		using Duration2 = duration<int, hamon::milli>;
		using TimePoint2 = time_point<Clock, Duration2>;
		TimePoint2 ms(Duration2{3});
		TimePoint tp{ms};
		VERIFY(tp.time_since_epoch().count() == 3000);
	}
	{
		using Duration2 = duration<int, hamon::nano>;
		using TimePoint2 = time_point<Clock, Duration2>;
		TimePoint2 ns(Duration2{500});
		TimePoint tp{ns};
		VERIFY(tp.time_since_epoch().count() == 0.5);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(TimePointTest, CtorConvTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test_integer<MyClock, int>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test_integer<MyClock, short>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test_integer<MyClock, long>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test_float<MyClock, float>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test_float<MyClock, double>()));
}

}	// namespace time_point_ctor_conv_test

}	// namespace hamon_chrono_test
