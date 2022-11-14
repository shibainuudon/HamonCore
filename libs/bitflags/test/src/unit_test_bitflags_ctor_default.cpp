/**
 *	@file	unit_test_bitflags_ctor_default.cpp
 *
 *	@brief	デフォルトコンストラクタのテスト
 */

#include <hamon/bitflags.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "bitflags_test.hpp"

namespace hamon_bitflags_test
{

GTEST_TEST(BitflagsTest, CtorDefaultTest)
{
	HAMON_CONSTEXPR Bitflag1 const b1;
	HAMON_CONSTEXPR Bitflag2 const b2{};
	HAMON_CONSTEXPR Bitflag3 const b3={};

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(b1.to_ulong(), 0u);
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(b2.to_ulong(), 0u);
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(b3.to_ulong(), 0u);
}

}	// namespace hamon_bitflags_test
