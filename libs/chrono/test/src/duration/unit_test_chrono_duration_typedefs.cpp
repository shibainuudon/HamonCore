/**
 *	@file	unit_test_chrono_duration_typedefs.cpp
 *
 *	@brief	convenience typedefs のテスト
 */

#include <hamon/chrono/duration.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>

namespace hamon_chrono_test
{

namespace duration_typedefs_test
{

GTEST_TEST(DurationTest, TypedefsTest)
{
	{
		using Duration = hamon::chrono::nanoseconds;
		using Rep = typename Duration::rep;
		using Period = typename Duration::period;
		static_assert(hamon::is_signed<Rep>::value, "");
		static_assert(sizeof(Rep) * 8 >= 64, "");
		static_assert(Period::num == 1, "");
		static_assert(Period::den == 1000000000, "");
	}
	{
		using Duration = hamon::chrono::microseconds;
		using Rep = typename Duration::rep;
		using Period = typename Duration::period;
		static_assert(hamon::is_signed<Rep>::value, "");
		static_assert(sizeof(Rep) * 8 >= 55, "");
		static_assert(Period::num == 1, "");
		static_assert(Period::den == 1000000, "");
	}
	{
		using Duration = hamon::chrono::milliseconds;
		using Rep = typename Duration::rep;
		using Period = typename Duration::period;
		static_assert(hamon::is_signed<Rep>::value, "");
		static_assert(sizeof(Rep) * 8 >= 45, "");
		static_assert(Period::num == 1, "");
		static_assert(Period::den == 1000, "");
	}
	{
		using Duration = hamon::chrono::seconds;
		using Rep = typename Duration::rep;
		using Period = typename Duration::period;
		static_assert(hamon::is_signed<Rep>::value, "");
		static_assert(sizeof(Rep) * 8 >= 35, "");
		static_assert(Period::num == 1, "");
		static_assert(Period::den == 1, "");
	}
	{
		using Duration = hamon::chrono::minutes;
		using Rep = typename Duration::rep;
		using Period = typename Duration::period;
		static_assert(hamon::is_signed<Rep>::value, "");
		static_assert(sizeof(Rep) * 8 >= 29, "");
		static_assert(Period::num == 60, "");
		static_assert(Period::den == 1, "");
	}
	{
		using Duration = hamon::chrono::hours;
		using Rep = typename Duration::rep;
		using Period = typename Duration::period;
		static_assert(hamon::is_signed<Rep>::value, "");
		static_assert(sizeof(Rep) * 8 >= 23, "");
		static_assert(Period::num == 3600, "");
		static_assert(Period::den == 1, "");
	}
	{
		using Duration = hamon::chrono::days;
		using Rep = typename Duration::rep;
		using Period = typename Duration::period;
		static_assert(hamon::is_signed<Rep>::value, "");
		static_assert(sizeof(Rep) * 8 >= 25, "");
		static_assert(Period::num == 86400, "");
		static_assert(Period::den == 1, "");
	}
	{
		using Duration = hamon::chrono::weeks;
		using Rep = typename Duration::rep;
		using Period = typename Duration::period;
		static_assert(hamon::is_signed<Rep>::value, "");
		static_assert(sizeof(Rep) * 8 >= 22, "");
		static_assert(Period::num == 604800, "");
		static_assert(Period::den == 1, "");
	}
	{
		using Duration = hamon::chrono::years;
		using Rep = typename Duration::rep;
		using Period = typename Duration::period;
		static_assert(hamon::is_signed<Rep>::value, "");
		static_assert(sizeof(Rep) * 8 >= 17, "");
		static_assert(Period::num == 31556952, "");
		static_assert(Period::den == 1, "");
	}
	{
		using Duration = hamon::chrono::months;
		using Rep = typename Duration::rep;
		using Period = typename Duration::period;
		static_assert(hamon::is_signed<Rep>::value, "");
		static_assert(sizeof(Rep) * 8 >= 20, "");
		static_assert(Period::num == 2629746, "");
		static_assert(Period::den == 1, "");
	}
}

}	// namespace duration_typedefs_test

}	// namespace hamon_chrono_test
