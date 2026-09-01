/**
 *	@file	unit_test_ios_flags_saver.cpp
 *
 *	@brief	flags_saver のテスト
 */

#include <hamon/ios/detail/flags_saver.hpp>
#include <hamon/ios.hpp>
#include <hamon/sstream/stringstream.hpp>
#include <gtest/gtest.h>

GTEST_TEST(IosTest, FlagsSaverTest)
{
	{
		hamon::stringstream ss;
		{
			hamon::detail::flags_saver fs(ss);
			ss << hamon::boolalpha;
			ss << true << " ";
		}
		{
			ss << true << " ";
		}
		{
			hamon::detail::flags_saver fs(ss);
			ss << hamon::boolalpha;
			ss << false << " ";
		}
		{
			ss << false << " ";
		}
		EXPECT_EQ("true 1 false 0 ", ss.str());
	}
	{
		hamon::stringstream ss;
		ss << 123 << " ";
		{
			hamon::detail::flags_saver fs(ss);
			ss << hamon::hex;
			ss << 123 << " ";
			{
				hamon::detail::flags_saver fs2(ss);
				ss << hamon::showbase;
				ss << 123 << " ";
				{
					hamon::detail::flags_saver fs3(ss);
					ss << hamon::uppercase;
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
		hamon::stringstream ss;
		{
			hamon::detail::flags_saver fs(ss);
			ss << hamon::showpoint;
			ss << 1.0 << " ";
		}
		{
			hamon::detail::flags_saver fs(ss);
			ss << hamon::showpos;
			ss << 1.0 << " ";
		}
		{
			ss << 1.0 << " ";
		}
		EXPECT_EQ("1.00000 +1 1 ", ss.str());
	}
}
