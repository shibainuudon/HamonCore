/**
 *	@file	unit_test_string_to_string.cpp
 *
 *	@brief	to_string のテスト
 *
 *	string to_string(int val);
 *	string to_string(unsigned val);
 *	string to_string(long val);
 *	string to_string(unsigned long val);
 *	string to_string(long long val);
 *	string to_string(unsigned long long val);
 *	string to_string(float val);
 *	string to_string(double val);
 *	string to_string(long double val);
 */

#include <hamon/string/to_string.hpp>
#include <hamon/limits.hpp>
#include <hamon/cstdint.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_test
{
namespace string_test
{
namespace to_string_test
{

GTEST_TEST(StringTest, ToStringTest)
{
	EXPECT_EQ("123",                  hamon::to_string(static_cast<int>(123)));
	EXPECT_EQ("-123",                 hamon::to_string(static_cast<int>(-123)));
	EXPECT_EQ("1234",                 hamon::to_string(static_cast<long>(1234)));
	EXPECT_EQ("-1234",                hamon::to_string(static_cast<long>(-1234)));
	EXPECT_EQ("12345",                hamon::to_string(static_cast<long long>(12345)));
	EXPECT_EQ("-12345",               hamon::to_string(static_cast<long long>(-12345)));

	EXPECT_EQ("-128",                 hamon::to_string(hamon::numeric_limits<hamon::int8_t>::min()));
	EXPECT_EQ("127",                  hamon::to_string(hamon::numeric_limits<hamon::int8_t>::max()));
	EXPECT_EQ("-32768",               hamon::to_string(hamon::numeric_limits<hamon::int16_t>::min()));
	EXPECT_EQ("32767",                hamon::to_string(hamon::numeric_limits<hamon::int16_t>::max()));
	EXPECT_EQ("-2147483648",          hamon::to_string(hamon::numeric_limits<hamon::int32_t>::min()));
	EXPECT_EQ("2147483647",           hamon::to_string(hamon::numeric_limits<hamon::int32_t>::max()));
	EXPECT_EQ("-9223372036854775808", hamon::to_string(hamon::numeric_limits<hamon::int64_t>::min()));
	EXPECT_EQ("9223372036854775807",  hamon::to_string(hamon::numeric_limits<hamon::int64_t>::max()));

	EXPECT_EQ("98765",                hamon::to_string(static_cast<unsigned int>(98765)));
	EXPECT_EQ("9876",                 hamon::to_string(static_cast<unsigned long>(9876)));
	EXPECT_EQ("987",                  hamon::to_string(static_cast<unsigned long long>(987)));

	EXPECT_EQ("0",                    hamon::to_string(hamon::numeric_limits<hamon::uint8_t>::min()));
	EXPECT_EQ("255",                  hamon::to_string(hamon::numeric_limits<hamon::uint8_t>::max()));
	EXPECT_EQ("0",                    hamon::to_string(hamon::numeric_limits<hamon::uint16_t>::min()));
	EXPECT_EQ("65535",                hamon::to_string(hamon::numeric_limits<hamon::uint16_t>::max()));
	EXPECT_EQ("0",                    hamon::to_string(hamon::numeric_limits<hamon::uint32_t>::min()));
	EXPECT_EQ("4294967295",           hamon::to_string(hamon::numeric_limits<hamon::uint32_t>::max()));
	EXPECT_EQ("0",                    hamon::to_string(hamon::numeric_limits<hamon::uint64_t>::min()));
	EXPECT_EQ("18446744073709551615", hamon::to_string(hamon::numeric_limits<hamon::uint64_t>::max()));

	EXPECT_EQ("23.430000",                    hamon::to_string(static_cast<float>(23.43)));
	EXPECT_EQ("0.000000",                     hamon::to_string(static_cast<float>(1e-09)));
	EXPECT_EQ("100000002004087734272.000000", hamon::to_string(static_cast<float>(1e+20)));
	EXPECT_EQ("123456792.000000",             hamon::to_string(static_cast<float>(123456789.0)));
	EXPECT_EQ("340282346638528859811704183484516925440.000000", hamon::to_string(hamon::numeric_limits<float>::max()));

	EXPECT_EQ("23.430000",                    hamon::to_string(static_cast<double>(23.43)));
	EXPECT_EQ("0.000000",                     hamon::to_string(static_cast<double>(1e-09)));
	EXPECT_EQ("100000000000000000000.000000", hamon::to_string(static_cast<double>(1e+20)));
	EXPECT_EQ("10000000000000000303786028427003666890752.000000", hamon::to_string(static_cast<double>(1e+40)));
	EXPECT_EQ("123456789.000000",             hamon::to_string(static_cast<double>(123456789.0)));
	EXPECT_EQ("179769313486231570814527423731704356798070567525844996598917476803157260780028538760589558632766878171540458953514382464234321326889464182768467546703537516986049910576551282076245490090389328944075868508455133942304583236903222948165808559332123348274797826204144723168738177180919299881250404026184124858368.000000", hamon::to_string(hamon::numeric_limits<double>::max()));

	EXPECT_EQ("23.430000",                    hamon::to_string(static_cast<long double>(23.43)));
	EXPECT_EQ("0.000000",                     hamon::to_string(static_cast<long double>(1e-09)));
	EXPECT_EQ("100000000000000000000.000000", hamon::to_string(static_cast<long double>(1e+20)));
	EXPECT_EQ("10000000000000000303786028427003666890752.000000", hamon::to_string(static_cast<long double>(1e+40)));
	EXPECT_EQ("123456789.000000",             hamon::to_string(static_cast<long double>(123456789.0)));
//	EXPECT_EQ("179769313486231570814527423731704356798070567525844996598917476803157260780028538760589558632766878171540458953514382464234321326889464182768467546703537516986049910576551282076245490090389328944075868508455133942304583236903222948165808559332123348274797826204144723168738177180919299881250404026184124858368.000000", hamon::to_string(hamon::numeric_limits<long double>::max()));
}

}	// namespace to_string_test
}	// namespace string_test
}	// namespace hamon_test
