/**
 *	@file	unit_test_bitset_none.cpp
 *
 *	@brief	none関数のテスト
 *
 *	constexpr bool none() const noexcept;
 */

#include <hamon/bitset.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

GTEST_TEST(BitsetTest, NoneTest)
{
	{
		HAMON_CXX11_CONSTEXPR hamon::bitset<0> b;
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(b.none());
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::bitset<1> b0{};
		HAMON_CXX11_CONSTEXPR hamon::bitset<1> b1{1};

		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (b0.none());
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(b1.none());
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::bitset<4> b0("0000");
		HAMON_CXX11_CONSTEXPR hamon::bitset<4> b1("1110");
		HAMON_CXX11_CONSTEXPR hamon::bitset<4> b2("0111");
		HAMON_CXX11_CONSTEXPR hamon::bitset<4> b3("1111");

		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (b0.none());
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(b1.none());
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(b2.none());
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(b3.none());
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::bitset<7> b0("0000000");
		HAMON_CXX11_CONSTEXPR hamon::bitset<7> b1("1000000");
		HAMON_CXX11_CONSTEXPR hamon::bitset<7> b2("0000001");
		HAMON_CXX11_CONSTEXPR hamon::bitset<7> b3("1111111");

		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (b0.none());
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(b1.none());
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(b2.none());
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(b3.none());
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::bitset<9> b0("000000000");
		HAMON_CXX11_CONSTEXPR hamon::bitset<9> b1("100000000");
		HAMON_CXX11_CONSTEXPR hamon::bitset<9> b2("000000001");
		HAMON_CXX11_CONSTEXPR hamon::bitset<9> b3("111111111");

		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (b0.none());
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(b1.none());
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(b2.none());
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(b3.none());
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::bitset<127> b0{};
		HAMON_CXX11_CONSTEXPR hamon::bitset<127> b1{1};
		HAMON_CXX11_CONSTEXPR hamon::bitset<127> b2 = ~hamon::bitset<127>{};

		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (b0.none());
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(b1.none());
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(b2.none());
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::bitset<128> b0(0);
		HAMON_CXX11_CONSTEXPR hamon::bitset<128> b1(1);
		HAMON_CXX11_CONSTEXPR hamon::bitset<128> b2 = ~hamon::bitset<128>{};

		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (b0.none());
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(b1.none());
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(b2.none());
	}
}
