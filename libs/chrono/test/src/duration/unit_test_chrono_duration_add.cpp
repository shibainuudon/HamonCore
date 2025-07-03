/**
 *	@file	unit_test_chrono_duration_add.cpp
 *
 *	@brief	operator+() のテスト
 *
 *	template<class Rep1, class Period1, class Rep2, class Period2>
 *	constexpr common_type_t<duration<Rep1, Period1>, duration<Rep2, Period2>>
 *	operator+(const duration<Rep1, Period1>& lhs, const duration<Rep2, Period2>& rhs);
 */

#include <hamon/chrono/duration.hpp>
#include <hamon/ratio.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_chrono_test
{

namespace duration_add_test
{

GTEST_TEST(DurationTest, AddTest)
{
	{
		using Duration1 = hamon::chrono::duration<int, hamon::ratio<1, 1000>>;
		using Duration2 = hamon::chrono::duration<float, hamon::ratio<1>>;

		static_assert(hamon::is_same<
			decltype(hamon::declval<Duration1>() + hamon::declval<Duration2>()),
			hamon::chrono::duration<float, hamon::ratio<1, 1000>>
		>::value, "");
#if !defined(HAMON_USE_STD_CHRONO)
		static_assert(noexcept(hamon::declval<Duration1>() + hamon::declval<Duration2>()), "");
#endif

		HAMON_CXX11_CONSTEXPR auto d = Duration1{2} + Duration2{3};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3002, d.count());
	}
	{
		using Duration1 = hamon::chrono::duration<double, hamon::ratio<200>>;
		using Duration2 = hamon::chrono::duration<short, hamon::ratio<1, 1000>>;

		static_assert(hamon::is_same<
			decltype(hamon::declval<Duration1>() + hamon::declval<Duration2>()),
			hamon::chrono::duration<double, hamon::ratio<1, 1000>>
		>::value, "");
#if !defined(HAMON_USE_STD_CHRONO)
		static_assert(noexcept(hamon::declval<Duration1>() + hamon::declval<Duration2>()), "");
#endif

		HAMON_CXX11_CONSTEXPR auto d = Duration1{3} + Duration2{4};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(600004, d.count());
	}

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::chrono::seconds{182}, hamon::chrono::seconds{2} + hamon::chrono::minutes{3});
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::chrono::minutes{70}, hamon::chrono::hours{1} + hamon::chrono::minutes{10});
}

}	// namespace duration_add_test

}	// namespace hamon_chrono_test
