/**
 *	@file	unit_test_bitflags_size.cpp
 *
 *	@brief	size関数のテスト
 */

#include <hamon/bitflags.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "bitflags_test.hpp"

namespace hamon_bitflags_test
{

GTEST_TEST(BitflagsTest, SizeTest)
{
	{
		HAMON_CONSTEXPR Bitflag1 const b{};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(32u, b.size());
	}
	{
		HAMON_CONSTEXPR Bitflag1 const b =
			Bitflag1(kOption1) |
			Bitflag1(kOption2) |
			Bitflag1(kOption3);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(32u, b.size());
	}
	{
		HAMON_CONSTEXPR Bitflag2 const b{};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(5u, b.size());
	}
	{
		HAMON_CONSTEXPR Bitflag2 const b =
			Bitflag2(Enum2::kOption4) |
			Bitflag2(Enum2::kOption6) |
			Bitflag2(Enum2::kOption8);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(5u, b.size());
	}
	{
		HAMON_CONSTEXPR Bitflag3 const b{};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(16u, b.size());
	}
	{
		HAMON_CONSTEXPR Bitflag3 const b =
			Bitflag3(Enum3::kOption7) |
			Bitflag3(Enum3::kOption8) |
			Bitflag3(Enum3::kOption9);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(16u, b.size());
	}
}

}	// namespace hamon_bitflags_test
