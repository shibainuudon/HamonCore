/**
 *	@file	unit_test_bitset_to_ullong.cpp
 *
 *	@brief	to_ullong関数のテスト
 *
 *	constexpr unsigned long long to_ullong() const;
 */

#include <hamon/bitset.hpp>
#include <hamon/stdexcept/overflow_error.hpp>
#include <hamon/cstdint.hpp>
#include <hamon/limits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

GTEST_TEST(BitsetTest, ToUllongTest)
{
	{
		HAMON_CXX11_CONSTEXPR hamon::bitset<0> b;
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0u, b.to_ullong());
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::bitset<8> b("10110001");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(177u, b.to_ullong());
	}
	{
		HAMON_CXX11_CONSTEXPR auto b = ~hamon::bitset<64>();
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::numeric_limits<hamon::uint64_t>::max(), b.to_ullong());
	}
	{
		HAMON_CXX11_CONSTEXPR auto b = hamon::bitset<65>();
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0u, b.to_ullong());
	}
	{
		HAMON_CXX11_CONSTEXPR auto b = hamon::bitset<65>(hamon::numeric_limits<hamon::uint64_t>::max());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::numeric_limits<hamon::uint64_t>::max(), b.to_ullong());
	}
	{
		HAMON_CXX11_CONSTEXPR auto b = ~hamon::bitset<65>();
		(void)b;
#if !defined(HAMON_NO_EXCEPTIONS)
		EXPECT_THROW((void)b.to_ullong(), hamon::overflow_error);
#endif
	}
	{
		HAMON_CXX11_CONSTEXPR auto b = hamon::bitset<128>(hamon::numeric_limits<hamon::uint64_t>::max()) << 1;
		(void)b;
#if !defined(HAMON_NO_EXCEPTIONS)
		EXPECT_THROW((void)b.to_ullong(), hamon::overflow_error);
#endif
	}
}
