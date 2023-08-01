/**
 *	@file	unit_test_bigint_ctor_integral.cpp
 *
 *	@brief	整数を引数に取るコンストラクタのテスト
 */

#include <hamon/bigint/bigint.hpp>
#include <hamon/cstdint.hpp>
#include <gtest/gtest.h>
#include <limits>

GTEST_TEST(BigIntTest, CtorIntegralTest)
{
	{
		hamon::bigint x{0};
		EXPECT_EQ("0", x.to_string());
	}
	{
		hamon::bigint x{-2};
		EXPECT_EQ("-2", x.to_string());
	}
	{
		hamon::bigint x{3};
		EXPECT_EQ("3", x.to_string());
	}
	{
		hamon::bigint x{std::numeric_limits<hamon::int8_t>::min()};
		EXPECT_EQ("-128", x.to_string());
	}
	{
		hamon::bigint x{std::numeric_limits<hamon::int8_t>::max()};
		EXPECT_EQ("127", x.to_string());
	}
	{
		hamon::bigint x{std::numeric_limits<hamon::int16_t>::min()};
		EXPECT_EQ("-32768", x.to_string());
	}
	{
		hamon::bigint x{std::numeric_limits<hamon::int16_t>::max()};
		EXPECT_EQ("32767", x.to_string());
	}
	{
		hamon::bigint x{std::numeric_limits<hamon::int32_t>::min()};
		EXPECT_EQ("-2147483648", x.to_string());
	}
	{
		hamon::bigint x{std::numeric_limits<hamon::int32_t>::max()};
		EXPECT_EQ("2147483647", x.to_string());
	}
	{
		hamon::bigint x{std::numeric_limits<hamon::int64_t>::min()};
		EXPECT_EQ("-9223372036854775808", x.to_string());
	}
	{
		hamon::bigint x{std::numeric_limits<hamon::int64_t>::max()};
		EXPECT_EQ("9223372036854775807", x.to_string());
	}
	{
		hamon::bigint x{std::numeric_limits<hamon::uint8_t>::min()};
		EXPECT_EQ("0", x.to_string());
	}
	{
		hamon::bigint x{std::numeric_limits<hamon::uint8_t>::max()};
		EXPECT_EQ("255", x.to_string());
	}
	{
		hamon::bigint x{std::numeric_limits<hamon::uint16_t>::min()};
		EXPECT_EQ("0", x.to_string());
	}
	{
		hamon::bigint x{std::numeric_limits<hamon::uint16_t>::max()};
		EXPECT_EQ("65535", x.to_string());
	}
	{
		hamon::bigint x{std::numeric_limits<hamon::uint32_t>::min()};
		EXPECT_EQ("0", x.to_string());
	}
	{
		hamon::bigint x{std::numeric_limits<hamon::uint32_t>::max()};
		EXPECT_EQ("4294967295", x.to_string());
	}
	{
		hamon::bigint x{std::numeric_limits<hamon::uint64_t>::min()};
		EXPECT_EQ("0", x.to_string());
	}
	{
		hamon::bigint x{std::numeric_limits<hamon::uint64_t>::max()};
		EXPECT_EQ("18446744073709551615", x.to_string());
	}
}
