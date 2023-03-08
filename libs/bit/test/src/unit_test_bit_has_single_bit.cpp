/**
 *	@file	unit_test_bit_has_single_bit.cpp
 *
 *	@brief	has_single_bit のテスト
 */

#include <hamon/bit/has_single_bit.hpp>
#include <hamon/cstdint.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_bit_test
{

namespace has_single_bit_test
{

template <typename T>
void HasSingleBitTestU8(void)
{
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, hamon::has_single_bit((T) 0));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true , hamon::has_single_bit((T) 1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true , hamon::has_single_bit((T) 2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, hamon::has_single_bit((T) 3));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true , hamon::has_single_bit((T) 4));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, hamon::has_single_bit((T) 5));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, hamon::has_single_bit((T) 6));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, hamon::has_single_bit((T) 7));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true , hamon::has_single_bit((T) 8));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, hamon::has_single_bit((T) 9));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, hamon::has_single_bit((T)0x0f));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true , hamon::has_single_bit((T)0x10));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, hamon::has_single_bit((T)0x11));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, hamon::has_single_bit((T)0x1f));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true , hamon::has_single_bit((T)0x20));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, hamon::has_single_bit((T)0x21));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, hamon::has_single_bit((T)0x3f));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true , hamon::has_single_bit((T)0x40));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, hamon::has_single_bit((T)0x41));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, hamon::has_single_bit((T)0x7f));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true,  hamon::has_single_bit((T)0x80));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, hamon::has_single_bit((T)0x81));
}

template <typename T>
void HasSingleBitTestU16(void)
{
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, hamon::has_single_bit((T)0x00ff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true , hamon::has_single_bit((T)0x0100));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, hamon::has_single_bit((T)0x0101));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, hamon::has_single_bit((T)0x01ff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true , hamon::has_single_bit((T)0x0200));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, hamon::has_single_bit((T)0x0201));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, hamon::has_single_bit((T)0x03ff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true , hamon::has_single_bit((T)0x0400));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, hamon::has_single_bit((T)0x0401));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, hamon::has_single_bit((T)0x07ff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true , hamon::has_single_bit((T)0x0800));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, hamon::has_single_bit((T)0x0801));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, hamon::has_single_bit((T)0x0fff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true , hamon::has_single_bit((T)0x1000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, hamon::has_single_bit((T)0x1001));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, hamon::has_single_bit((T)0x1fff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true , hamon::has_single_bit((T)0x2000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, hamon::has_single_bit((T)0x2001));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, hamon::has_single_bit((T)0x3fff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true , hamon::has_single_bit((T)0x4000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, hamon::has_single_bit((T)0x4001));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, hamon::has_single_bit((T)0x7fff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true , hamon::has_single_bit((T)0x8000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, hamon::has_single_bit((T)0x8001));
}

template <typename T>
void HasSingleBitTestU32(void)
{
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, hamon::has_single_bit((T)0x00ffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true , hamon::has_single_bit((T)0x01000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, hamon::has_single_bit((T)0x01000001));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, hamon::has_single_bit((T)0x01ffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true , hamon::has_single_bit((T)0x02000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, hamon::has_single_bit((T)0x02000001));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, hamon::has_single_bit((T)0x03ffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true , hamon::has_single_bit((T)0x04000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, hamon::has_single_bit((T)0x04000001));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, hamon::has_single_bit((T)0x07ffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true , hamon::has_single_bit((T)0x08000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, hamon::has_single_bit((T)0x08000001));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, hamon::has_single_bit((T)0x0fffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true , hamon::has_single_bit((T)0x10000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, hamon::has_single_bit((T)0x10000001));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, hamon::has_single_bit((T)0x1fffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true , hamon::has_single_bit((T)0x20000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, hamon::has_single_bit((T)0x20000001));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, hamon::has_single_bit((T)0x3fffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true , hamon::has_single_bit((T)0x40000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, hamon::has_single_bit((T)0x40000001));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, hamon::has_single_bit((T)0x7fffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true , hamon::has_single_bit((T)0x80000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, hamon::has_single_bit((T)0x80000001));
}

template <typename T>
void HasSingleBitTestU64(void)
{
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, hamon::has_single_bit((T)0x00ffffffffffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true , hamon::has_single_bit((T)0x0100000000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, hamon::has_single_bit((T)0x0100000000000001));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, hamon::has_single_bit((T)0x01ffffffffffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true , hamon::has_single_bit((T)0x0200000000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, hamon::has_single_bit((T)0x0200000000000001));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, hamon::has_single_bit((T)0x03ffffffffffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true , hamon::has_single_bit((T)0x0400000000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, hamon::has_single_bit((T)0x0400000000000001));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, hamon::has_single_bit((T)0x07ffffffffffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true , hamon::has_single_bit((T)0x0800000000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, hamon::has_single_bit((T)0x0800000000000001));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, hamon::has_single_bit((T)0x0fffffffffffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true , hamon::has_single_bit((T)0x1000000000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, hamon::has_single_bit((T)0x1000000000000001));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, hamon::has_single_bit((T)0x1fffffffffffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true , hamon::has_single_bit((T)0x2000000000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, hamon::has_single_bit((T)0x2000000000000001));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, hamon::has_single_bit((T)0x3fffffffffffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true , hamon::has_single_bit((T)0x4000000000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, hamon::has_single_bit((T)0x4000000000000001));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, hamon::has_single_bit((T)0x7fffffffffffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true , hamon::has_single_bit((T)0x8000000000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, hamon::has_single_bit((T)0x8000000000000001));
}

GTEST_TEST(BitTest, HasSingleBitTest)
{
	HasSingleBitTestU8<hamon::uint8_t>();
	HasSingleBitTestU8<hamon::uint16_t>();
	HasSingleBitTestU8<hamon::uint32_t>();
	HasSingleBitTestU8<hamon::uint64_t>();

	HasSingleBitTestU16<hamon::uint16_t>();
	HasSingleBitTestU16<hamon::uint32_t>();
	HasSingleBitTestU16<hamon::uint64_t>();

	HasSingleBitTestU32<hamon::uint32_t>();
	HasSingleBitTestU32<hamon::uint64_t>();

	HasSingleBitTestU64<hamon::uint64_t>();
}

}	// namespace has_single_bit_test

}	// namespace hamon_bit_test
