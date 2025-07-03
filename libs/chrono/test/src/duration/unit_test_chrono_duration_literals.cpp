/**
 *	@file	unit_test_chrono_duration_literals.cpp
 *
 *	@brief	ユーザー定義リテラルのテスト
 *
 *	constexpr chrono::hours                                 operator""h(unsigned long long);
 *	constexpr chrono::duration<unspecified, ratio<3600, 1>> operator""h(long double);
 *
 *	constexpr chrono::minutes                             operator""min(unsigned long long);
 *	constexpr chrono::duration<unspecified, ratio<60, 1>> operator""min(long double);
 *
 *	constexpr chrono::seconds               operator""s(unsigned long long);
 *	constexpr chrono::duration<unspecified> operator""s(long double);
 *
 *	constexpr chrono::milliseconds                 operator""ms(unsigned long long);
 *	constexpr chrono::duration<unspecified, milli> operator""ms(long double);
 *
 *	constexpr chrono::microseconds                 operator""us(unsigned long long);
 *	constexpr chrono::duration<unspecified, micro> operator""us(long double);
 *
 *	constexpr chrono::nanoseconds                 operator""ns(unsigned long long);
 *	constexpr chrono::duration<unspecified, nano> operator""ns(long double);
 */

#include <hamon/chrono/duration.hpp>
#include <hamon/ratio.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_chrono_test
{

namespace duration_literals_test
{

GTEST_TEST(DurationTest, LiteralsTest)
{
	{
		using namespace hamon::literals::chrono_literals;
		static_assert(hamon::is_same<decltype(1_h), hamon::chrono::hours>::value, "");
		static_assert(hamon::is_same<decltype(2.0_h), hamon::chrono::duration<double, hamon::ratio<3600>>>::value, "");
		static_assert(hamon::is_same<decltype(3_min), hamon::chrono::minutes>::value, "");
		static_assert(hamon::is_same<decltype(4.0_min), hamon::chrono::duration<double, hamon::ratio<60>>>::value, "");
		static_assert(hamon::is_same<decltype(5_s), hamon::chrono::seconds>::value, "");
		static_assert(hamon::is_same<decltype(6.0_s), hamon::chrono::duration<double>>::value, "");
		static_assert(hamon::is_same<decltype(7_ms), hamon::chrono::milliseconds>::value, "");
		static_assert(hamon::is_same<decltype(8.0_ms), hamon::chrono::duration<double, hamon::milli>>::value, "");
		static_assert(hamon::is_same<decltype(9_us), hamon::chrono::microseconds>::value, "");
		static_assert(hamon::is_same<decltype(10.0_us), hamon::chrono::duration<double, hamon::micro>>::value, "");
		static_assert(hamon::is_same<decltype(11_ns), hamon::chrono::nanoseconds>::value, "");
		static_assert(hamon::is_same<decltype(12.0_ns), hamon::chrono::duration<double, hamon::nano>>::value, "");

		{
			HAMON_CXX11_CONSTEXPR auto aday = 24_h;
			HAMON_CXX11_CONSTEXPR auto lesson = 45_min;
			HAMON_CXX11_CONSTEXPR auto halfanhour = 0.5_h;
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::chrono::minutes(1440), aday);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::chrono::minutes(45),   lesson);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::chrono::minutes(30),   halfanhour);
		}
	}
	{
		using namespace hamon::chrono_literals;
		static_assert(hamon::is_same<decltype(1_h), hamon::chrono::hours>::value, "");
		static_assert(hamon::is_same<decltype(2.0_h), hamon::chrono::duration<double, hamon::ratio<3600>>>::value, "");
		static_assert(hamon::is_same<decltype(3_min), hamon::chrono::minutes>::value, "");
		static_assert(hamon::is_same<decltype(4.0_min), hamon::chrono::duration<double, hamon::ratio<60>>>::value, "");
		static_assert(hamon::is_same<decltype(5_s), hamon::chrono::seconds>::value, "");
		static_assert(hamon::is_same<decltype(6.0_s), hamon::chrono::duration<double>>::value, "");
		static_assert(hamon::is_same<decltype(7_ms), hamon::chrono::milliseconds>::value, "");
		static_assert(hamon::is_same<decltype(8.0_ms), hamon::chrono::duration<double, hamon::milli>>::value, "");
		static_assert(hamon::is_same<decltype(9_us), hamon::chrono::microseconds>::value, "");
		static_assert(hamon::is_same<decltype(10.0_us), hamon::chrono::duration<double, hamon::micro>>::value, "");
		static_assert(hamon::is_same<decltype(11_ns), hamon::chrono::nanoseconds>::value, "");
		static_assert(hamon::is_same<decltype(12.0_ns), hamon::chrono::duration<double, hamon::nano>>::value, "");

		{
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::chrono::minutes(60), 1_h);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::chrono::minutes(90), 1.5_h);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::chrono::seconds(120), 2_min);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::chrono::seconds(150), 2.5_min);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::chrono::milliseconds(3000), 3_s);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::chrono::milliseconds(3500), 3.5_s);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::chrono::microseconds(4000), 4_ms);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::chrono::microseconds(4500), 4.5_ms);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::chrono::nanoseconds(5000), 5_us);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::chrono::nanoseconds(5500), 5.5_us);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ((hamon::chrono::duration<int, hamon::pico>(6000)), 6_ns);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ((hamon::chrono::duration<int, hamon::pico>(6500)), 6.5_ns);
		}
	}
	{
		using namespace hamon::literals;
		static_assert(hamon::is_same<decltype(1_h), hamon::chrono::hours>::value, "");
		static_assert(hamon::is_same<decltype(2.0_h), hamon::chrono::duration<double, hamon::ratio<3600>>>::value, "");
		static_assert(hamon::is_same<decltype(3_min), hamon::chrono::minutes>::value, "");
		static_assert(hamon::is_same<decltype(4.0_min), hamon::chrono::duration<double, hamon::ratio<60>>>::value, "");
		static_assert(hamon::is_same<decltype(5_s), hamon::chrono::seconds>::value, "");
		static_assert(hamon::is_same<decltype(6.0_s), hamon::chrono::duration<double>>::value, "");
		static_assert(hamon::is_same<decltype(7_ms), hamon::chrono::milliseconds>::value, "");
		static_assert(hamon::is_same<decltype(8.0_ms), hamon::chrono::duration<double, hamon::milli>>::value, "");
		static_assert(hamon::is_same<decltype(9_us), hamon::chrono::microseconds>::value, "");
		static_assert(hamon::is_same<decltype(10.0_us), hamon::chrono::duration<double, hamon::micro>>::value, "");
		static_assert(hamon::is_same<decltype(11_ns), hamon::chrono::nanoseconds>::value, "");
		static_assert(hamon::is_same<decltype(12.0_ns), hamon::chrono::duration<double, hamon::nano>>::value, "");

		{
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1_h + 1.5_h, 150_min);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2_min + 2.5_min, 270_s);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3_s + 4_ms, 3004_ms);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(4.5_s + 5.0_ms, 4505_ms);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(5_ns + 6_us, 6005_ns);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(7.5_us + 8.0_ns, 7508_ns);
		}
	}
	{
		using namespace hamon::chrono;
		static_assert(hamon::is_same<decltype(1_h), hamon::chrono::hours>::value, "");
		static_assert(hamon::is_same<decltype(2.0_h), hamon::chrono::duration<double, hamon::ratio<3600>>>::value, "");
		static_assert(hamon::is_same<decltype(3_min), hamon::chrono::minutes>::value, "");
		static_assert(hamon::is_same<decltype(4.0_min), hamon::chrono::duration<double, hamon::ratio<60>>>::value, "");
		static_assert(hamon::is_same<decltype(5_s), hamon::chrono::seconds>::value, "");
		static_assert(hamon::is_same<decltype(6.0_s), hamon::chrono::duration<double>>::value, "");
		static_assert(hamon::is_same<decltype(7_ms), hamon::chrono::milliseconds>::value, "");
		static_assert(hamon::is_same<decltype(8.0_ms), hamon::chrono::duration<double, hamon::milli>>::value, "");
		static_assert(hamon::is_same<decltype(9_us), hamon::chrono::microseconds>::value, "");
		static_assert(hamon::is_same<decltype(10.0_us), hamon::chrono::duration<double, hamon::micro>>::value, "");
		static_assert(hamon::is_same<decltype(11_ns), hamon::chrono::nanoseconds>::value, "");
		static_assert(hamon::is_same<decltype(12.0_ns), hamon::chrono::duration<double, hamon::nano>>::value, "");
	}
	{
		using namespace hamon;
		static_assert(hamon::is_same<decltype(1_h), hamon::chrono::hours>::value, "");
		static_assert(hamon::is_same<decltype(2.0_h), hamon::chrono::duration<double, hamon::ratio<3600>>>::value, "");
		static_assert(hamon::is_same<decltype(3_min), hamon::chrono::minutes>::value, "");
		static_assert(hamon::is_same<decltype(4.0_min), hamon::chrono::duration<double, hamon::ratio<60>>>::value, "");
		static_assert(hamon::is_same<decltype(5_s), hamon::chrono::seconds>::value, "");
		static_assert(hamon::is_same<decltype(6.0_s), hamon::chrono::duration<double>>::value, "");
		static_assert(hamon::is_same<decltype(7_ms), hamon::chrono::milliseconds>::value, "");
		static_assert(hamon::is_same<decltype(8.0_ms), hamon::chrono::duration<double, hamon::milli>>::value, "");
		static_assert(hamon::is_same<decltype(9_us), hamon::chrono::microseconds>::value, "");
		static_assert(hamon::is_same<decltype(10.0_us), hamon::chrono::duration<double, hamon::micro>>::value, "");
		static_assert(hamon::is_same<decltype(11_ns), hamon::chrono::nanoseconds>::value, "");
		static_assert(hamon::is_same<decltype(12.0_ns), hamon::chrono::duration<double, hamon::nano>>::value, "");
	}
}

}	// namespace duration_literals_test

}	// namespace hamon_chrono_test
