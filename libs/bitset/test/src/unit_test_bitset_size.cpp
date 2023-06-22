/**
 *	@file	unit_test_bitset_size.cpp
 *
 *	@brief	size関数のテスト
 *
 *	constexpr size_t size() const noexcept;
 */

#include <hamon/bitset.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

GTEST_TEST(BitsetTest, SizeTest)
{
	{
		HAMON_CXX11_CONSTEXPR hamon::bitset<0> b;
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0u, b.size());
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::bitset<1> b;
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1u, b.size());
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::bitset<8> b;
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(8u, b.size());
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::bitset<8> b("11111111");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(8u, b.size());
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::bitset<12> b;
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(12u, b.size());
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::bitset<64> b;
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(64u, b.size());
	}
}
