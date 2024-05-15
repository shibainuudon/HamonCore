/**
 *	@file	unit_test_bit_bit_cast.cpp
 *
 *	@brief	bit_cast のテスト
 */

#include <hamon/bit/bit_cast.hpp>
#include <hamon/cstdint.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

#if defined(HAMON_HAS_CONSTEXPR_BIT_CAST)
#  define HAMON_BIT_CAST_CONSTEXPR           HAMON_CXX11_CONSTEXPR
#  define HAMON_BIT_CAST_CONSTEXPR_EXPECT_EQ HAMON_CXX11_CONSTEXPR_EXPECT_EQ
#else
#  define HAMON_BIT_CAST_CONSTEXPR           /**/
#  define HAMON_BIT_CAST_CONSTEXPR_EXPECT_EQ EXPECT_EQ
#endif

namespace hamon_bit_test
{

namespace bit_cast_test
{

struct S
{
	int x;
	int y;
	int z;

	constexpr S() = delete;
};

GTEST_TEST(BitTest, BitCastTest)
{
	{
		HAMON_BIT_CAST_CONSTEXPR float x = 1.0f;
		HAMON_BIT_CAST_CONSTEXPR auto  y = hamon::bit_cast<hamon::uint32_t>(x);
		HAMON_BIT_CAST_CONSTEXPR_EXPECT_EQ(hamon::uint32_t(0x3f800000), y);
	}
	{
		HAMON_BIT_CAST_CONSTEXPR float x = 3.14159265358979f;
		HAMON_BIT_CAST_CONSTEXPR auto  y = hamon::bit_cast<hamon::int32_t>(x);
		HAMON_BIT_CAST_CONSTEXPR_EXPECT_EQ(hamon::int32_t(0x40490fdb), y);
	}
	{
		HAMON_BIT_CAST_CONSTEXPR double x = 1.0;
		HAMON_BIT_CAST_CONSTEXPR auto   y = hamon::bit_cast<hamon::uint64_t>(x);
		HAMON_BIT_CAST_CONSTEXPR_EXPECT_EQ(hamon::uint64_t(0x3FF0000000000000), y);
	}
	{
		HAMON_BIT_CAST_CONSTEXPR int a[] = {3, 1, 4};
		HAMON_BIT_CAST_CONSTEXPR auto y = hamon::bit_cast<S>(a);
		HAMON_BIT_CAST_CONSTEXPR_EXPECT_EQ(3, y.x);
		HAMON_BIT_CAST_CONSTEXPR_EXPECT_EQ(1, y.y);
		HAMON_BIT_CAST_CONSTEXPR_EXPECT_EQ(4, y.z);
	}
}

}	// namespace bit_cast_test

}	// namespace hamon_bit_test

#undef HAMON_BIT_CAST_CONSTEXPR           
#undef HAMON_BIT_CAST_CONSTEXPR_EXPECT_EQ
