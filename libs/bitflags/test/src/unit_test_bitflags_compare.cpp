/**
 *	@file	unit_test_bitflags_compare.cpp
 *
 *	@brief	比較演算子のテスト
 */

#include <hamon/bitflags.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "bitflags_test.hpp"

namespace hamon_bitflags_test
{

namespace compare_test
{

GTEST_TEST(BitflagsTest, CompareTest)
{
	{
		HAMON_CONSTEXPR Bitflag1 const b1 = Bitflag1(kOption1) | Bitflag1(kOption2) | Bitflag1(kOption3);
		HAMON_CONSTEXPR Bitflag1 const b2 = Bitflag1(kOption1) | Bitflag1(kOption2) | Bitflag1(kOption3);
		HAMON_CONSTEXPR Bitflag1 const b3 =                      Bitflag1(kOption2) | Bitflag1(kOption3);
		HAMON_CONSTEXPR Bitflag1 const b4 = Bitflag1(kOption1) |                      Bitflag1(kOption3);
		HAMON_CONSTEXPR Bitflag1 const b5 = Bitflag1(kOption1) | Bitflag1(kOption2)                     ;
		HAMON_CONSTEXPR Bitflag1 const b6;

		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( b1 == b1);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( b1 == b2);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(b1 == b3);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(b1 == b4);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(b1 == b5);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(b1 == b6);

		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(b1 != b1);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(b1 != b2);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( b1 != b3);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( b1 != b4);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( b1 != b5);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( b1 != b6);
	}
	{
		HAMON_CONSTEXPR Bitflag2 const b1 = Bitflag2(Enum2::kOption4) | Bitflag2(Enum2::kOption6) | Bitflag2(Enum2::kOption8);
		HAMON_CONSTEXPR Bitflag2 const b2 = Bitflag2(Enum2::kOption4) | Bitflag2(Enum2::kOption6) | Bitflag2(Enum2::kOption8);
		HAMON_CONSTEXPR Bitflag2 const b3 = Bitflag2(Enum2::kOption5) | Bitflag2(Enum2::kOption6) | Bitflag2(Enum2::kOption8);
		HAMON_CONSTEXPR Bitflag2 const b4 = Bitflag2(Enum2::kOption4) | Bitflag2(Enum2::kOption7) | Bitflag2(Enum2::kOption8);
		HAMON_CONSTEXPR Bitflag2 const b5 = Bitflag2(Enum2::kOption4) | Bitflag2(Enum2::kOption6) | Bitflag2(Enum2::kOption7);
		HAMON_CONSTEXPR Bitflag2 const b6;

		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( b1 == b1);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( b1 == b2);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(b1 == b3);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(b1 == b4);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(b1 == b5);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(b1 == b6);

		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(b1 != b1);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(b1 != b2);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( b1 != b3);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( b1 != b4);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( b1 != b5);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( b1 != b6);
	}
	{
		HAMON_CONSTEXPR Bitflag3 const b1 = Bitflag3(Enum3::kOption7) | Bitflag3(Enum3::kOption8) | Bitflag3(Enum3::kOption9);
		HAMON_CONSTEXPR Bitflag3 const b2 = Bitflag3(Enum3::kOption7) | Bitflag3(Enum3::kOption8) | Bitflag3(Enum3::kOption9);
		HAMON_CONSTEXPR Bitflag3 const b3 = Bitflag3(Enum3::kOption7) | Bitflag3(Enum3::kOption8);
		HAMON_CONSTEXPR Bitflag3 const b4 = Bitflag3(Enum3::kOption7);
		HAMON_CONSTEXPR Bitflag3 const b5 = Bitflag3(Enum3::kOption8);
		HAMON_CONSTEXPR Bitflag3 const b6;

		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( b1 == b1);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( b1 == b2);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(b1 == b3);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(b1 == b4);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(b1 == b5);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(b1 == b6);

		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(b1 != b1);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(b1 != b2);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( b1 != b3);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( b1 != b4);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( b1 != b5);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( b1 != b6);
	}
}

}	// namespace compare_test

}	// namespace hamon_bitflags_test
