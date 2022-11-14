/**
 *	@file	unit_test_bitflags_to_ulong.cpp
 *
 *	@brief	to_ulong関数のテスト
 */

#include <hamon/bitflags.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "bitflags_test.hpp"

namespace hamon_bitflags_test
{

GTEST_TEST(BitflagsTest, ToULongTest)
{
	{
		HAMON_CONSTEXPR Bitflag1 const b =
			Bitflag1(kOption1) |
			Bitflag1(kOption2) |
			Bitflag1(kOption3);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(b.to_ulong(), 7u);
	}
	{
		HAMON_CONSTEXPR Bitflag1 const b =
			Bitflag1(kOption1) |
			Bitflag1(kOption2);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(b.to_ulong(), 3u);
	}
	{
		HAMON_CONSTEXPR Bitflag2 const b =
			Bitflag2(Enum2::kOption4) |
			Bitflag2(Enum2::kOption5) |
			Bitflag2(Enum2::kOption6) |
			Bitflag2(Enum2::kOption7) |
			Bitflag2(Enum2::kOption8);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(b.to_ulong(), 31u);
	}
	{
		HAMON_CONSTEXPR Bitflag2 const b =
			Bitflag2(Enum2::kOption5) |
			Bitflag2(Enum2::kOption6) |
			Bitflag2(Enum2::kOption7) |
			Bitflag2(Enum2::kOption8);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(b.to_ulong(), 30u);
	}
	{
		HAMON_CONSTEXPR Bitflag3 const b =
			Bitflag3(Enum3::kOption7) |
			Bitflag3(Enum3::kOption8);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(b.to_ulong(), 18u);
	}
	{
		HAMON_CONSTEXPR Bitflag3 const b =
			Bitflag3(Enum3::kOption7) |
			Bitflag3(Enum3::kOption9) |
			Bitflag3(Enum3::kOption8);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(b.to_ulong(), 50u);
	}
}

}	// namespace hamon_bitflags_test
