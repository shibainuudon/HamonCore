/**
 *	@file	unit_test_cstddef_byte.cpp
 *
 *	@brief	byte のテスト
 */

#include <hamon/cstddef/byte.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

GTEST_TEST(CStdDefTest, ByteTest)
{
	hamon::byte b = static_cast<hamon::byte>(42);
	EXPECT_EQ(42, hamon::to_integer<int>(b));

	b <<= 1;
	EXPECT_EQ(84, hamon::to_integer<int>(b));

	b >>= 2;
	EXPECT_EQ(21, hamon::to_integer<int>(b));

	EXPECT_EQ(42, hamon::to_integer<int>(b << 1));
	EXPECT_EQ(10, hamon::to_integer<int>(b >> 1));

	b |= static_cast<hamon::byte>(15);
	EXPECT_EQ(31, hamon::to_integer<int>(b));

	b &= static_cast<hamon::byte>(7);
	EXPECT_EQ(7, hamon::to_integer<int>(b));

	b ^= static_cast<hamon::byte>(31);
	EXPECT_EQ(24, hamon::to_integer<int>(b));

	EXPECT_EQ(127, hamon::to_integer<int>(b | static_cast<hamon::byte>(127)));
	EXPECT_EQ( 24, hamon::to_integer<int>(b & static_cast<hamon::byte>(127)));
	EXPECT_EQ(103, hamon::to_integer<int>(b ^ static_cast<hamon::byte>(127)));
	EXPECT_EQ(231, hamon::to_integer<int>(~b));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 64, hamon::to_integer<int>(static_cast<hamon::byte>(64)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(128, hamon::to_integer<int>(static_cast<hamon::byte>(64) << 1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 32, hamon::to_integer<int>(static_cast<hamon::byte>(64) >> 1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(240, hamon::to_integer<int>(static_cast<hamon::byte>(64) | static_cast<hamon::byte>(240)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 64, hamon::to_integer<int>(static_cast<hamon::byte>(64) & static_cast<hamon::byte>(240)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(176, hamon::to_integer<int>(static_cast<hamon::byte>(64) ^ static_cast<hamon::byte>(240)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(191, hamon::to_integer<int>(~static_cast<hamon::byte>(64)));
}
