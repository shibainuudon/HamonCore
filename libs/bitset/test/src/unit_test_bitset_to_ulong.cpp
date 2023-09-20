/**
 *	@file	unit_test_bitset_to_ulong.cpp
 *
 *	@brief	to_ulong関数のテスト
 *
 *	constexpr unsigned long to_ulong() const;
 */

#include <hamon/bitset.hpp>
#include <hamon/stdexcept/overflow_error.hpp>
#include <hamon/cstdint.hpp>
#include <hamon/limits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

GTEST_TEST(BitsetTest, ToUlongTest)
{
	{
		HAMON_CXX11_CONSTEXPR hamon::bitset<0> b;
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0u, b.to_ulong());
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::bitset<8> b("10110001");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(177u, b.to_ulong());
	}
	{
		HAMON_CXX11_CONSTEXPR auto b = hamon::bitset<32>();
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0u, b.to_ulong());
	}
	{
		HAMON_CXX11_CONSTEXPR auto b = ~hamon::bitset<32>();
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::numeric_limits<hamon::uint32_t>::max(), b.to_ulong());
	}
	{
		HAMON_CXX11_CONSTEXPR auto b = hamon::bitset<65>();
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0u, b.to_ulong());
	}
	{
		HAMON_CXX11_CONSTEXPR auto b = hamon::bitset<65>(ULONG_MAX);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(ULONG_MAX, b.to_ulong());
	}
	{
		HAMON_CXX11_CONSTEXPR auto b = hamon::bitset<65>(ULONG_MAX) << 1;
		(void)b;
#if !defined(HAMON_NO_EXCEPTIONS)
		EXPECT_THROW((void)b.to_ulong(), hamon::overflow_error);
#endif
	}
	{
#if ULONG_MAX > 4294967294
		HAMON_CXX11_CONSTEXPR auto b = ~hamon::bitset<65>();
#else
		HAMON_CXX11_CONSTEXPR auto b = ~hamon::bitset<33>();
#endif
		(void)b;
#if !defined(HAMON_NO_EXCEPTIONS)
		EXPECT_THROW((void)b.to_ulong(), hamon::overflow_error);
#endif
	}
}
