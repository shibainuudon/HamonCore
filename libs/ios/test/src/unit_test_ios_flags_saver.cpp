/**
 *	@file	unit_test_ios_flags_saver.cpp
 *
 *	@brief	flags_saver のテスト
 */

#include <hamon/ios/flags_saver.hpp>
#include <gtest/gtest.h>
#include <sstream>

GTEST_TEST(IosTest, FlagsSaverTest)
{
	{
		std::stringstream ss;
		{
			hamon::ios::flags_saver fs(ss);
			ss << std::boolalpha;
			ss << true << " ";
		}
		{
			ss << true << " ";
		}
		{
			hamon::ios::flags_saver fs(ss);
			ss << std::boolalpha;
			ss << false << " ";
		}
		{
			ss << false << " ";
		}
		EXPECT_EQ("true 1 false 0 ", ss.str());
	}
	{
		std::stringstream ss;
		ss << 123 << " ";
		{
			hamon::ios::flags_saver fs(ss);
			ss << std::hex;
			ss << 123 << " ";
			{
				hamon::ios::flags_saver fs2(ss);
				ss << std::showbase;
				ss << 123 << " ";
				{
					hamon::ios::flags_saver fs3(ss);
					ss << std::uppercase;
					ss << 123 << " ";
				}
				ss << 123 << " ";
			}
			ss << 123 << " ";
		}
		ss << 123 << " ";
		EXPECT_EQ("123 7b 0x7b 0X7B 0x7b 7b 123 ", ss.str());
	}
	{
		std::stringstream ss;
		{
			hamon::ios::flags_saver fs(ss);
			ss << std::showpoint;
			ss << 1.0 << " ";
		}
		{
			hamon::ios::flags_saver fs(ss);
			ss << std::showpos;
			ss << 1.0 << " ";
		}
		{
			ss << 1.0 << " ";
		}
		EXPECT_EQ("1.00000 +1 1 ", ss.str());
	}
}
