/**
 *	@file	unit_test_fnd_bit_bit_cast.cpp
 *
 *	@brief	bit_cast のテスト
 */

#include <hamon/bit/bit_cast.hpp>
#include <gtest/gtest.h>
#include <cstdint>
#include "constexpr_test.hpp"

#if defined(HAMON_HAS_CONSTEXPR_BIT_CAST)
#  define HAMON_BIT_CAST_CONSTEXPR           HAMON_CXX20_CONSTEXPR
#  define HAMON_BIT_CAST_CONSTEXPR_EXPECT_EQ HAMON_CXX20_CONSTEXPR_EXPECT_EQ
#else
#  define HAMON_BIT_CAST_CONSTEXPR           /**/
#  define HAMON_BIT_CAST_CONSTEXPR_EXPECT_EQ EXPECT_EQ
#endif

GTEST_TEST(BitTest, BitCastTest)
{
	{
		HAMON_BIT_CAST_CONSTEXPR float	x = 1.0f;
		HAMON_BIT_CAST_CONSTEXPR auto  y = hamon::bit_cast<std::uint32_t>(x);
		HAMON_BIT_CAST_CONSTEXPR_EXPECT_EQ(std::uint32_t(0x3f800000), y);
	}
	{
		HAMON_BIT_CAST_CONSTEXPR float	x = 3.14159265358979f;
		HAMON_BIT_CAST_CONSTEXPR auto  y = hamon::bit_cast<std::int32_t>(x);
		HAMON_BIT_CAST_CONSTEXPR_EXPECT_EQ(std::int32_t(0x40490fdb), y);
	}
	{
		HAMON_BIT_CAST_CONSTEXPR double x = 1.0;
		HAMON_BIT_CAST_CONSTEXPR auto	 y = hamon::bit_cast<std::uint64_t>(x);
		HAMON_BIT_CAST_CONSTEXPR_EXPECT_EQ(std::uint64_t(0x3FF0000000000000), y);
	}
}

#undef HAMON_BIT_CAST_CONSTEXPR           
#undef HAMON_BIT_CAST_CONSTEXPR_EXPECT_EQ
