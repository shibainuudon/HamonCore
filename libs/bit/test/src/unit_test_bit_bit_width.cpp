/**
 *	@file	unit_test_bit_bit_width.cpp
 *
 *	@brief	bit_width のテスト
 */

#include <hamon/bit/bit_width.hpp>
#include <gtest/gtest.h>
#include <cstdint>
#include "constexpr_test.hpp"

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4307)	// 整数定数がオーバーフローしました。

namespace hamon_bit_test
{

namespace bit_width_test
{

template <typename T>
void BitWidthTestU8(void)
{
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)0, hamon::bit_width((T)0));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)1, hamon::bit_width((T)1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)2, hamon::bit_width((T)2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)2, hamon::bit_width((T)3));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)3, hamon::bit_width((T)4));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)3, hamon::bit_width((T)5));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)3, hamon::bit_width((T)6));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)3, hamon::bit_width((T)7));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)4, hamon::bit_width((T)8));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)4, hamon::bit_width((T)15));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)5, hamon::bit_width((T)16));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)5, hamon::bit_width((T)31));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)6, hamon::bit_width((T)32));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)6, hamon::bit_width((T)63));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)7, hamon::bit_width((T)64));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)7, hamon::bit_width((T)127));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)8, hamon::bit_width((T)128));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)8, hamon::bit_width((T)255));
}

template <typename T>
void BitWidthTestU16(void)
{
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T) 9, hamon::bit_width((T)0x0100));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T) 9, hamon::bit_width((T)0x01ff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)10, hamon::bit_width((T)0x0200));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)10, hamon::bit_width((T)0x03ff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)11, hamon::bit_width((T)0x0400));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)11, hamon::bit_width((T)0x07ff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)12, hamon::bit_width((T)0x0800));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)12, hamon::bit_width((T)0x0fff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)13, hamon::bit_width((T)0x1000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)13, hamon::bit_width((T)0x1fff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)14, hamon::bit_width((T)0x2000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)14, hamon::bit_width((T)0x3fff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)15, hamon::bit_width((T)0x4000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)15, hamon::bit_width((T)0x7fff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)16, hamon::bit_width((T)0x8000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)16, hamon::bit_width((T)0xffff));
}

template <typename T>
void BitWidthTestU32(void)
{
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)17, hamon::bit_width((T)0x00010000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)17, hamon::bit_width((T)0x0001ffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)18, hamon::bit_width((T)0x00020000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)18, hamon::bit_width((T)0x0003ffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)19, hamon::bit_width((T)0x00040000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)19, hamon::bit_width((T)0x0007ffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)20, hamon::bit_width((T)0x00080000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)20, hamon::bit_width((T)0x000fffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)21, hamon::bit_width((T)0x00100000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)21, hamon::bit_width((T)0x001fffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)22, hamon::bit_width((T)0x00200000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)22, hamon::bit_width((T)0x003fffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)23, hamon::bit_width((T)0x00400000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)23, hamon::bit_width((T)0x007fffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)24, hamon::bit_width((T)0x00800000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)24, hamon::bit_width((T)0x00ffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)25, hamon::bit_width((T)0x01000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)25, hamon::bit_width((T)0x01ffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)26, hamon::bit_width((T)0x02000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)26, hamon::bit_width((T)0x03ffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)27, hamon::bit_width((T)0x04000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)27, hamon::bit_width((T)0x07ffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)28, hamon::bit_width((T)0x08000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)28, hamon::bit_width((T)0x0fffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)29, hamon::bit_width((T)0x10000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)29, hamon::bit_width((T)0x1fffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)30, hamon::bit_width((T)0x20000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)30, hamon::bit_width((T)0x3fffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)31, hamon::bit_width((T)0x40000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)31, hamon::bit_width((T)0x7fffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)32, hamon::bit_width((T)0x80000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)32, hamon::bit_width((T)0xffffffff));
}

template <typename T>
void BitWidthTestU64(void)
{
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)33, hamon::bit_width((T)0x0000000100000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)33, hamon::bit_width((T)0x00000001ffffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)34, hamon::bit_width((T)0x0000000200000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)34, hamon::bit_width((T)0x00000003ffffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)35, hamon::bit_width((T)0x0000000400000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)35, hamon::bit_width((T)0x00000007ffffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)36, hamon::bit_width((T)0x0000000800000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)36, hamon::bit_width((T)0x0000000fffffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)37, hamon::bit_width((T)0x0000001000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)37, hamon::bit_width((T)0x0000001fffffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)38, hamon::bit_width((T)0x0000002000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)38, hamon::bit_width((T)0x0000003fffffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)39, hamon::bit_width((T)0x0000004000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)39, hamon::bit_width((T)0x0000007fffffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)40, hamon::bit_width((T)0x0000008000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)40, hamon::bit_width((T)0x000000ffffffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)41, hamon::bit_width((T)0x0000010000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)41, hamon::bit_width((T)0x000001ffffffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)42, hamon::bit_width((T)0x0000020000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)42, hamon::bit_width((T)0x000003ffffffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)43, hamon::bit_width((T)0x0000040000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)43, hamon::bit_width((T)0x000007ffffffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)44, hamon::bit_width((T)0x0000080000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)44, hamon::bit_width((T)0x00000fffffffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)45, hamon::bit_width((T)0x0000100000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)45, hamon::bit_width((T)0x00001fffffffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)46, hamon::bit_width((T)0x0000200000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)46, hamon::bit_width((T)0x00003fffffffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)47, hamon::bit_width((T)0x0000400000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)47, hamon::bit_width((T)0x00007fffffffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)48, hamon::bit_width((T)0x0000800000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)48, hamon::bit_width((T)0x0000ffffffffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)49, hamon::bit_width((T)0x0001000000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)49, hamon::bit_width((T)0x0001ffffffffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)50, hamon::bit_width((T)0x0002000000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)50, hamon::bit_width((T)0x0003ffffffffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)51, hamon::bit_width((T)0x0004000000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)51, hamon::bit_width((T)0x0007ffffffffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)52, hamon::bit_width((T)0x0008000000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)52, hamon::bit_width((T)0x000fffffffffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)53, hamon::bit_width((T)0x0010000000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)53, hamon::bit_width((T)0x001fffffffffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)54, hamon::bit_width((T)0x0020000000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)54, hamon::bit_width((T)0x003fffffffffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)55, hamon::bit_width((T)0x0040000000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)55, hamon::bit_width((T)0x007fffffffffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)56, hamon::bit_width((T)0x0080000000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)56, hamon::bit_width((T)0x00ffffffffffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)57, hamon::bit_width((T)0x0100000000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)57, hamon::bit_width((T)0x01ffffffffffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)58, hamon::bit_width((T)0x0200000000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)58, hamon::bit_width((T)0x03ffffffffffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)59, hamon::bit_width((T)0x0400000000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)59, hamon::bit_width((T)0x07ffffffffffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)60, hamon::bit_width((T)0x0800000000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)60, hamon::bit_width((T)0x0fffffffffffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)61, hamon::bit_width((T)0x1000000000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)61, hamon::bit_width((T)0x1fffffffffffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)62, hamon::bit_width((T)0x2000000000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)62, hamon::bit_width((T)0x3fffffffffffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)63, hamon::bit_width((T)0x4000000000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)63, hamon::bit_width((T)0x7fffffffffffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)64, hamon::bit_width((T)0x8000000000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)64, hamon::bit_width((T)0xffffffffffffffff));
}

GTEST_TEST(BitTest, BitWidthTest)
{
	BitWidthTestU8<std::uint8_t>();
	BitWidthTestU8<std::uint16_t>();
	BitWidthTestU8<std::uint32_t>();
	BitWidthTestU8<std::uint64_t>();

	BitWidthTestU16<std::uint16_t>();
	BitWidthTestU16<std::uint32_t>();
	BitWidthTestU16<std::uint64_t>();

	BitWidthTestU32<std::uint32_t>();
	BitWidthTestU32<std::uint64_t>();

	BitWidthTestU64<std::uint64_t>();
}

}	// namespace bit_width_test

}	// namespace hamon_bit_test

HAMON_WARNING_POP()
