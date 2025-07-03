/**
 *	@file	unit_test_chrono_duration_mul.cpp
 *
 *	@brief	operator*() のテスト
 *
 *	template<class Rep1, class Period, class Rep2>
 *	constexpr duration<common_type_t<Rep1, Rep2>, Period>
 *	operator*(const duration<Rep1, Period>& d, const Rep2& s);
 *
 *	template<class Rep1, class Rep2, class Period>
 *	constexpr duration<common_type_t<Rep1, Rep2>, Period>
 *	operator*(const Rep1& s, const duration<Rep2, Period>& d);
 */

#include <hamon/chrono/duration.hpp>
#include <hamon/ratio.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_chrono_test
{

namespace duration_mul_test
{

GTEST_TEST(DurationTest, MulTest)
{
	{
		using Duration = hamon::chrono::duration<int, hamon::ratio<1, 1000>>;

		static_assert(hamon::is_same<
			decltype(hamon::declval<Duration>() * hamon::declval<int>()),
			hamon::chrono::duration<int, hamon::ratio<1, 1000>>
		>::value, "");
		static_assert(hamon::is_same<
			decltype(hamon::declval<float>() * hamon::declval<Duration>()),
			hamon::chrono::duration<float, hamon::ratio<1, 1000>>
		>::value, "");
#if !defined(HAMON_USE_STD_CHRONO)
		static_assert(noexcept(hamon::declval<Duration>() * hamon::declval<int>()), "");
		static_assert(noexcept(hamon::declval<float>() * hamon::declval<Duration>()), "");
#endif

		{
			HAMON_CXX11_CONSTEXPR auto d = Duration{2} * 3;
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(d.count(), 6);
		}
		{
			HAMON_CXX11_CONSTEXPR auto d = 0.5 * Duration{3};
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(d.count(), 1.5);
		}
	}
	{
		using Duration = hamon::chrono::duration<double, hamon::ratio<60>>;

		static_assert(hamon::is_same<
			decltype(hamon::declval<Duration>() * hamon::declval<int>()),
			hamon::chrono::duration<double, hamon::ratio<60>>
		>::value, "");
		static_assert(hamon::is_same<
			decltype(hamon::declval<float>() * hamon::declval<Duration>()),
			hamon::chrono::duration<double, hamon::ratio<60>>
		>::value, "");
#if !defined(HAMON_USE_STD_CHRONO)
		static_assert(noexcept(hamon::declval<Duration>() * hamon::declval<int>()), "");
		static_assert(noexcept(hamon::declval<float>() * hamon::declval<Duration>()), "");
#endif

		{
			HAMON_CXX11_CONSTEXPR auto d = Duration{2.5} * 3;
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(d.count(), 7.5);
		}
		{
			HAMON_CXX11_CONSTEXPR auto d = 0.5 * Duration{3};
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(d.count(), 1.5);
		}
	}
}

}	// namespace duration_mul_test

}	// namespace hamon_chrono_test
