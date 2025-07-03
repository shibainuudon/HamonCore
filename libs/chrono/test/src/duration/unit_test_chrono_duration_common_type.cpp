/**
 *	@file	unit_test_chrono_duration_common_type.cpp
 *
 *	@brief	common_type のテスト
 *
 *	template<class Rep1, class Period1, class Rep2, class Period2>
 *	struct common_type<
 *		chrono::duration<Rep1, Period1>,
 *		chrono::duration<Rep2, Period2>>;
 */

#include <hamon/chrono/duration.hpp>
#include <hamon/ratio.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_chrono_test
{

namespace duration_common_type_test
{

GTEST_TEST(DurationTest, CommonTypeTest)
{
	{
		using Duration1 = hamon::chrono::duration<int, hamon::ratio<1>>;
		using Duration2 = hamon::chrono::duration<int, hamon::ratio<1>>;
		using CT = hamon::common_type_t<Duration1, Duration2>;
		static_assert(hamon::is_same<int, typename CT::rep>::value, "");
		static_assert(1 == CT::period::num, "");
		static_assert(1 == CT::period::den, "");
	}
	{
		using Duration1 = hamon::chrono::duration<int,   hamon::ratio<3, 4>>;
		using Duration2 = hamon::chrono::duration<float, hamon::ratio<2, 3>>;
		using CT = hamon::common_type_t<Duration1, Duration2>;
		static_assert(hamon::is_same<float, typename CT::rep>::value, "");
		static_assert( 1 == CT::period::num, "");
		static_assert(12 == CT::period::den, "");
	}
	{
		using Duration1 = hamon::chrono::duration<char, hamon::ratio<630>>;
		using Duration2 = hamon::chrono::duration<int,  hamon::ratio<300>>;
		using CT = hamon::common_type_t<Duration1, Duration2>;
		static_assert(hamon::is_same<int, typename CT::rep>::value, "");
		static_assert(30 == CT::period::num, "");
		static_assert( 1 == CT::period::den, "");
	}
	{
		using Duration1 = hamon::chrono::duration<float,  hamon::ratio<100>>;
		using Duration2 = hamon::chrono::duration<double, hamon::ratio<1, 1000>>;
		using CT = hamon::common_type_t<Duration1, Duration2>;
		static_assert(hamon::is_same<double, typename CT::rep>::value, "");
		static_assert(   1 == CT::period::num, "");
		static_assert(1000 == CT::period::den, "");
	}
}

}	// namespace duration_common_type_test

}	// namespace hamon_chrono_test
