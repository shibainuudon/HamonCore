/**
 *	@file	unit_test_chrono_duration_mod.cpp
 *
 *	@brief	operator%() のテスト
 *
 *	template<class Rep1, class Period, class Rep2>
 *	constexpr duration<common_type_t<Rep1, Rep2>, Period>
 *	operator%(const duration<Rep1, Period>& d, const Rep2& s);
 *
 *	template<class Rep1, class Period1, class Rep2, class Period2>
 *	constexpr common_type_t<duration<Rep1, Period1>, duration<Rep2, Period2>>
 *	operator%(const duration<Rep1, Period1>& lhs, const duration<Rep2, Period2>& rhs);
 */

#include <hamon/chrono/duration.hpp>
#include <hamon/ratio.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_chrono_test
{

namespace duration_mod_test
{

GTEST_TEST(DurationTest, ModTest)
{
	{
		using Duration = hamon::chrono::duration<int, hamon::ratio<1, 1000>>;

		static_assert(hamon::is_same<
			decltype(hamon::declval<Duration>() % hamon::declval<short>()),
			hamon::chrono::duration<int, hamon::ratio<1, 1000>>
		>::value, "");
#if !defined(HAMON_USE_STD_CHRONO)
		static_assert(noexcept(hamon::declval<Duration>() % hamon::declval<short>()), "");
#endif

		{
			HAMON_CXX11_CONSTEXPR auto d = Duration{5} % 2;
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(d.count(), 1);
		}
	}
	{
		using Duration1 = hamon::chrono::duration<int, hamon::ratio<60>>;
		using Duration2 = hamon::chrono::duration<short, hamon::ratio<1>>;

		static_assert(hamon::is_same<
			decltype(hamon::declval<Duration1>() % hamon::declval<Duration2>()),
			hamon::chrono::duration<int, hamon::ratio<1>>
		>::value, "");
#if !defined(HAMON_USE_STD_CHRONO)
		static_assert(noexcept(hamon::declval<Duration1>() % hamon::declval<Duration2>()), "");
#endif

		{
			HAMON_CXX11_CONSTEXPR auto d = Duration1{3} % Duration2{7};
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(d.count(), 5);
		}
	}
}

}	// namespace duration_mod_test

}	// namespace hamon_chrono_test
