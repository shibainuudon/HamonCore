/**
 *	@file	unit_test_chrono_duration_ostream.cpp
 *
 *	@brief	operator<<() のテスト
 *
 *	template<class charT, class traits, class Rep, class Period>
 *	basic_ostream<charT, traits>&
 *	operator<<(basic_ostream<charT, traits>& os, const duration<Rep, Period>& d);
 */

#include <hamon/chrono/duration.hpp>
#include <hamon/ratio.hpp>
#include <gtest/gtest.h>
#include <sstream>

namespace hamon_chrono_test
{

namespace duration_ostream_test
{

template <typename Period, typename Rep, typename CharT>
void test(Rep v, CharT const* str)
{
	auto const d = hamon::chrono::duration<Rep, Period>{v};
	std::basic_stringstream<CharT> ss;
	auto& r = (ss << d);
	EXPECT_TRUE(&r == &ss);
	EXPECT_EQ(str, ss.str());
}

GTEST_TEST(DurationTest, OStreamTest)
{
	test<hamon::atto> (1, "1as");
	test<hamon::femto>(2.5, "2.5fs");
	test<hamon::pico> (3, "3ps");
	test<hamon::nano> (4.5f, "4.5ns");
	test<hamon::micro>(5, "5us");
	test<hamon::milli>(6, "6ms");
	test<hamon::centi>(7, "7cs");
	test<hamon::deci> (8, "8ds");
	test<hamon::ratio<1>>(9, "9s");
	test<hamon::deca> (10, "10das");
	test<hamon::hecto>(11, "11hs");
	test<hamon::kilo> (12, "12ks");
	test<hamon::mega> (13, "13Ms");
	test<hamon::giga> (14, "14Gs");
	test<hamon::tera> (15, "15Ts");
	test<hamon::peta> (16, "16Ps");
	test<hamon::exa>  (17, "17Es");
	test<hamon::ratio<60>>   (18, "18min");
	test<hamon::ratio<3600>> (19, "19h");
	test<hamon::ratio<86400>>(20, "20d");
	test<hamon::ratio<30>>   (21, "21[30]s");
	test<hamon::ratio<3, 4>> (22, "22[3/4]s");

	test<hamon::atto> (1, L"1as");
	test<hamon::femto>(2.5, L"2.5fs");
	test<hamon::pico> (3, L"3ps");
	test<hamon::nano> (4.5f, L"4.5ns");
	test<hamon::micro>(5, L"5us");
	test<hamon::milli>(6, L"6ms");
	test<hamon::centi>(7, L"7cs");
	test<hamon::deci> (8, L"8ds");
	test<hamon::ratio<1>>(9, L"9s");
	test<hamon::deca> (10, L"10das");
	test<hamon::hecto>(11, L"11hs");
	test<hamon::kilo> (12, L"12ks");
	test<hamon::mega> (13, L"13Ms");
	test<hamon::giga> (14, L"14Gs");
	test<hamon::tera> (15, L"15Ts");
	test<hamon::peta> (16, L"16Ps");
	test<hamon::exa>  (17, L"17Es");
	test<hamon::ratio<60>>   (18, L"18min");
	test<hamon::ratio<3600>> (19, L"19h");
	test<hamon::ratio<86400>>(20, L"20d");
	test<hamon::ratio<61>>   (21, L"21[61]s");
	test<hamon::ratio<17, 1000>> (22, L"22[17/1000]s");
}

}	// namespace duration_ostream_test

}	// namespace hamon_chrono_test
