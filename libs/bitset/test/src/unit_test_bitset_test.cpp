/**
 *	@file	unit_test_bitset_test.cpp
 *
 *	@brief	test関数のテスト
 *
 *	constexpr bool test(size_t pos) const;
 */

#include <hamon/bitset.hpp>
#include <hamon/stdexcept/out_of_range.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

GTEST_TEST(BitsetTest, TestTest)
{
	{
		HAMON_CXX11_CONSTEXPR hamon::bitset<0> b;
		(void)b;
#if !defined(HAMON_NO_EXCEPTIONS)
		EXPECT_THROW((void)b.test(0), hamon::out_of_range);
#endif
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::bitset<7> b("0011010");
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(b.test(0));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (b.test(1));
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(b.test(2));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (b.test(3));
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(b.test(6));
#if !defined(HAMON_NO_EXCEPTIONS)
		EXPECT_THROW((void)b.test(7), hamon::out_of_range);
#endif
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::bitset<8> b("00110110");
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(b.test(0));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (b.test(1));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (b.test(2));
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(b.test(3));
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(b.test(7));
#if !defined(HAMON_NO_EXCEPTIONS)
		EXPECT_THROW((void)b.test(8), hamon::out_of_range);
#endif
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::bitset<9> b("100110110");
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(b.test(0));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (b.test(1));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (b.test(2));
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(b.test(3));
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(b.test(7));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (b.test(8));
#if !defined(HAMON_NO_EXCEPTIONS)
		EXPECT_THROW((void)b.test(9), hamon::out_of_range);
#endif
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::bitset<63> b("010111110101111101011111010111110101111101011111010111110101111");
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (b.test(0));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (b.test(1));
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(b.test(4));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (b.test(7));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (b.test(8));
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(b.test(14));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (b.test(15));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (b.test(16));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (b.test(31));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (b.test(32));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (b.test(61));
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(b.test(62));
#if !defined(HAMON_NO_EXCEPTIONS)
		EXPECT_THROW((void)b.test(63), hamon::out_of_range);
#endif
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::bitset<64> b("0101111101011111010111110101111101011111010111110101111101011111");
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (b.test(0));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (b.test(1));
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(b.test(7));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (b.test(8));
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(b.test(31));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (b.test(32));
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(b.test(63));
#if !defined(HAMON_NO_EXCEPTIONS)
		EXPECT_THROW((void)b.test(64), hamon::out_of_range);
#endif
	}
}
