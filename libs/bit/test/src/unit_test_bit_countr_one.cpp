/**
 *	@file	unit_test_bit_countr_one.cpp
 *
 *	@brief	countr_one のテスト
 */

#include <hamon/bit/countr_one.hpp>
#include <hamon/cstdint.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4307)	// 整数定数がオーバーフローしました。

namespace hamon_bit_test
{

namespace countr_one_test
{

template <typename T>
void CountrOneTestU8(void)
{
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(8, hamon::countr_one((T)0xff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(7, hamon::countr_one((T)0x7f));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(6, hamon::countr_one((T)0x3f));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(5, hamon::countr_one((T)0x1f));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(4, hamon::countr_one((T)0x0f));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3, hamon::countr_one((T)0x07));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2, hamon::countr_one((T)0x03));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1, hamon::countr_one((T)0x01));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0, hamon::countr_one((T)0x00));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0, hamon::countr_one((T)0x02));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0, hamon::countr_one((T)0x04));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0, hamon::countr_one((T)0x08));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0, hamon::countr_one((T)0x10));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0, hamon::countr_one((T)0x20));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0, hamon::countr_one((T)0x40));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0, hamon::countr_one((T)0x80));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3, hamon::countr_one((T)0xf7));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3, hamon::countr_one((T)0xe7));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3, hamon::countr_one((T)0xc7));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3, hamon::countr_one((T)0x87));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2, hamon::countr_one((T)0xf3));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2, hamon::countr_one((T)0xe3));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2, hamon::countr_one((T)0xc3));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2, hamon::countr_one((T)0x83));
}

template <typename T>
void CountrOneTestU16(void)
{
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(16, hamon::countr_one((T)0xffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(15, hamon::countr_one((T)0x7fff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(14, hamon::countr_one((T)0x3fff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(13, hamon::countr_one((T)0x1fff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(12, hamon::countr_one((T)0x0fff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(11, hamon::countr_one((T)0x07ff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(10, hamon::countr_one((T)0x03ff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 9, hamon::countr_one((T)0x01ff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 8, hamon::countr_one((T)0x00ff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 7, hamon::countr_one((T)0x007f));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 6, hamon::countr_one((T)0x003f));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 5, hamon::countr_one((T)0x001f));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 4, hamon::countr_one((T)0x000f));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 3, hamon::countr_one((T)0x0007));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 2, hamon::countr_one((T)0x0003));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1, hamon::countr_one((T)0x0001));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, hamon::countr_one((T)0x0000));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, hamon::countr_one((T)0x0002));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, hamon::countr_one((T)0x0004));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, hamon::countr_one((T)0x0008));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, hamon::countr_one((T)0x0010));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, hamon::countr_one((T)0x0020));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, hamon::countr_one((T)0x0040));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, hamon::countr_one((T)0x0080));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 6, hamon::countr_one((T)0xf03f));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 6, hamon::countr_one((T)0xe03f));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 6, hamon::countr_one((T)0xc03f));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 6, hamon::countr_one((T)0x803f));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(11, hamon::countr_one((T)0xf7ff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(11, hamon::countr_one((T)0xe7ff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(11, hamon::countr_one((T)0xc7ff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(11, hamon::countr_one((T)0x87ff));
}

template <typename T>
void CountrOneTestU32(void)
{
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(32, hamon::countr_one((T)0xffffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(31, hamon::countr_one((T)0x7fffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(30, hamon::countr_one((T)0x3fffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(29, hamon::countr_one((T)0x1fffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(28, hamon::countr_one((T)0x0fffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(27, hamon::countr_one((T)0x07ffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(26, hamon::countr_one((T)0x03ffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(25, hamon::countr_one((T)0x01ffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(24, hamon::countr_one((T)0x00ffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(23, hamon::countr_one((T)0x007fffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(22, hamon::countr_one((T)0x003fffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(21, hamon::countr_one((T)0x001fffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(20, hamon::countr_one((T)0x000fffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(19, hamon::countr_one((T)0x0007ffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(18, hamon::countr_one((T)0x0003ffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(17, hamon::countr_one((T)0x0001ffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(16, hamon::countr_one((T)0x0000ffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(15, hamon::countr_one((T)0x00007fff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(14, hamon::countr_one((T)0x00003fff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(13, hamon::countr_one((T)0x00001fff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(12, hamon::countr_one((T)0x00000fff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(11, hamon::countr_one((T)0x000007ff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(10, hamon::countr_one((T)0x000003ff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 9, hamon::countr_one((T)0x000001ff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 8, hamon::countr_one((T)0x000000ff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 7, hamon::countr_one((T)0x0000007f));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 6, hamon::countr_one((T)0x0000003f));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 5, hamon::countr_one((T)0x0000001f));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 4, hamon::countr_one((T)0x0000000f));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 3, hamon::countr_one((T)0x00000007));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 2, hamon::countr_one((T)0x00000003));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1, hamon::countr_one((T)0x00000001));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, hamon::countr_one((T)0x00000000));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, hamon::countr_one((T)0x00000010));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, hamon::countr_one((T)0x00000100));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, hamon::countr_one((T)0x00001000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, hamon::countr_one((T)0x00010000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, hamon::countr_one((T)0x00100000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, hamon::countr_one((T)0x01000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, hamon::countr_one((T)0x10000000));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 5, hamon::countr_one((T)0xf000001f));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 5, hamon::countr_one((T)0xff00001f));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 5, hamon::countr_one((T)0xfff0001f));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 5, hamon::countr_one((T)0xffff001f));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(15, hamon::countr_one((T)0xffff7fff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(15, hamon::countr_one((T)0xfffe7fff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(15, hamon::countr_one((T)0xfffc7fff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(15, hamon::countr_one((T)0xfff87fff));
}

template <typename T>
void CountrOneTestU64(void)
{
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(64, hamon::countr_one((T)0xffffffffffffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(63, hamon::countr_one((T)0x7fffffffffffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(62, hamon::countr_one((T)0x3fffffffffffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(61, hamon::countr_one((T)0x1fffffffffffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(60, hamon::countr_one((T)0x0fffffffffffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(59, hamon::countr_one((T)0x07ffffffffffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(58, hamon::countr_one((T)0x03ffffffffffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(57, hamon::countr_one((T)0x01ffffffffffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(56, hamon::countr_one((T)0x00ffffffffffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(55, hamon::countr_one((T)0x007fffffffffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(54, hamon::countr_one((T)0x003fffffffffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(53, hamon::countr_one((T)0x001fffffffffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(52, hamon::countr_one((T)0x000fffffffffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(51, hamon::countr_one((T)0x0007ffffffffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(50, hamon::countr_one((T)0x0003ffffffffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(49, hamon::countr_one((T)0x0001ffffffffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(48, hamon::countr_one((T)0x0000ffffffffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(47, hamon::countr_one((T)0x00007fffffffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(46, hamon::countr_one((T)0x00003fffffffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(45, hamon::countr_one((T)0x00001fffffffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(44, hamon::countr_one((T)0x00000fffffffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(43, hamon::countr_one((T)0x000007ffffffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(42, hamon::countr_one((T)0x000003ffffffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(41, hamon::countr_one((T)0x000001ffffffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(40, hamon::countr_one((T)0x000000ffffffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(39, hamon::countr_one((T)0x0000007fffffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(38, hamon::countr_one((T)0x0000003fffffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(37, hamon::countr_one((T)0x0000001fffffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(36, hamon::countr_one((T)0x0000000fffffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(35, hamon::countr_one((T)0x00000007ffffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(34, hamon::countr_one((T)0x00000003ffffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(33, hamon::countr_one((T)0x00000001ffffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(32, hamon::countr_one((T)0x00000000ffffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(31, hamon::countr_one((T)0x000000007fffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(30, hamon::countr_one((T)0x000000003fffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(29, hamon::countr_one((T)0x000000001fffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(28, hamon::countr_one((T)0x000000000fffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(27, hamon::countr_one((T)0x0000000007ffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(26, hamon::countr_one((T)0x0000000003ffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(25, hamon::countr_one((T)0x0000000001ffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(24, hamon::countr_one((T)0x0000000000ffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(23, hamon::countr_one((T)0x00000000007fffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(22, hamon::countr_one((T)0x00000000003fffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(21, hamon::countr_one((T)0x00000000001fffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(20, hamon::countr_one((T)0x00000000000fffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(19, hamon::countr_one((T)0x000000000007ffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(18, hamon::countr_one((T)0x000000000003ffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(17, hamon::countr_one((T)0x000000000001ffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(16, hamon::countr_one((T)0x000000000000ffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(15, hamon::countr_one((T)0x0000000000007fff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(14, hamon::countr_one((T)0x0000000000003fff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(13, hamon::countr_one((T)0x0000000000001fff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(12, hamon::countr_one((T)0x0000000000000fff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(11, hamon::countr_one((T)0x00000000000007ff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(10, hamon::countr_one((T)0x00000000000003ff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 9, hamon::countr_one((T)0x00000000000001ff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 8, hamon::countr_one((T)0x00000000000000ff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 7, hamon::countr_one((T)0x000000000000007f));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 6, hamon::countr_one((T)0x000000000000003f));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 5, hamon::countr_one((T)0x000000000000001f));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 4, hamon::countr_one((T)0x000000000000000f));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 3, hamon::countr_one((T)0x0000000000000007));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 2, hamon::countr_one((T)0x0000000000000003));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1, hamon::countr_one((T)0x0000000000000001));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, hamon::countr_one((T)0x0000000000000000));
}

GTEST_TEST(BitTest, CountrOneTest)
{
	CountrOneTestU8<hamon::uint8_t>();
	CountrOneTestU16<hamon::uint16_t>();
	CountrOneTestU32<hamon::uint32_t>();
	CountrOneTestU64<hamon::uint64_t>();
}

}	// namespace countr_one_test

}	// namespace hamon_bit_test

HAMON_WARNING_POP()
