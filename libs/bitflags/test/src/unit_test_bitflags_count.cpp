/**
 *	@file	unit_test_bitflags_count.cpp
 *
 *	@brief	count関数のテスト
 */

#include <hamon/bitflags.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "bitflags_test.hpp"

namespace hamon_bitflags_test
{

GTEST_TEST(BitflagsTest, CountTest)
{
	{
		HAMON_CONSTEXPR Bitflag1 const b{};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0, b.count());
	}
	{
		HAMON_CONSTEXPR Bitflag1 const b(kOption1);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1, b.count());
	}
	{
		HAMON_CONSTEXPR Bitflag1 const b(kOption2);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1, b.count());
	}
	{
		HAMON_CONSTEXPR Bitflag1 const b =
			Bitflag1(kOption1) |
			Bitflag1(kOption3);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2, b.count());
	}
	{
		HAMON_CONSTEXPR Bitflag2 const b{};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0, b.count());
	}
	{
		HAMON_CONSTEXPR Bitflag2 const b =
			Bitflag2(Enum2::kOption4) |
			Bitflag2(Enum2::kOption6) |
			Bitflag2(Enum2::kOption8);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3, b.count());
	}
	{
		HAMON_CONSTEXPR Bitflag2 const b =
			Bitflag2(Enum2::kOption4) |
			Bitflag2(Enum2::kOption5) |
			Bitflag2(Enum2::kOption6) |
			Bitflag2(Enum2::kOption7) |
			Bitflag2(Enum2::kOption8);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(5, b.count());
	}
	{
		HAMON_CONSTEXPR Bitflag3 const b{};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0, b.count());
	}
	{
		HAMON_CONSTEXPR Bitflag3 const b =
			Bitflag3(Enum3::kOption7) |
			Bitflag3(Enum3::kOption8);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2, b.count());
	}
}

}	// namespace hamon_bitflags_test
