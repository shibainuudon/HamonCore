/**
 *	@file	unit_test_bit_popcount.cpp
 *
 *	@brief	popcount のテスト
 */

#include <hamon/bit/popcount.hpp>
#include <hamon/cstdint.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4307)	// 整数定数がオーバーフローしました。

namespace hamon_bit_test
{

namespace popcount_test
{

template <typename T>
void PopCountTestU8(void)
{
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0, hamon::popcount((T)0x00));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1, hamon::popcount((T)0x01));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1, hamon::popcount((T)0x02));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2, hamon::popcount((T)0x03));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1, hamon::popcount((T)0x04));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2, hamon::popcount((T)0x05));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2, hamon::popcount((T)0x06));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3, hamon::popcount((T)0x07));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1, hamon::popcount((T)0x08));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2, hamon::popcount((T)0x09));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2, hamon::popcount((T)0x0a));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3, hamon::popcount((T)0x0b));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2, hamon::popcount((T)0x0c));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3, hamon::popcount((T)0x0d));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3, hamon::popcount((T)0x0e));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(4, hamon::popcount((T)0x0f));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1, hamon::popcount((T)0x10));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1, hamon::popcount((T)0x20));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1, hamon::popcount((T)0x40));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1, hamon::popcount((T)0x80));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(4, hamon::popcount((T)0xf0));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(5, hamon::popcount((T)0xf1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(6, hamon::popcount((T)0xf3));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(7, hamon::popcount((T)0xf7));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(8, hamon::popcount((T)0xff));
}

template <typename T>
void PopCountTestU16(void)
{
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1, hamon::popcount((T)0x0100));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1, hamon::popcount((T)0x0200));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1, hamon::popcount((T)0x0400));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1, hamon::popcount((T)0x0800));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1, hamon::popcount((T)0x1000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1, hamon::popcount((T)0x2000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1, hamon::popcount((T)0x4000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1, hamon::popcount((T)0x8000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 9, hamon::popcount((T)0x01ff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(10, hamon::popcount((T)0x03ff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(11, hamon::popcount((T)0x07ff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(12, hamon::popcount((T)0x0fff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(13, hamon::popcount((T)0x1fff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(14, hamon::popcount((T)0x3fff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(15, hamon::popcount((T)0x7fff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(16, hamon::popcount((T)0xffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 5, hamon::popcount((T)0xf100));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 6, hamon::popcount((T)0xf300));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 7, hamon::popcount((T)0xf700));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 8, hamon::popcount((T)0xff00));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 5, hamon::popcount((T)0x1234));
}

template <typename T>
void PopCountTestU32(void)
{
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1, hamon::popcount((T)0x00010000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1, hamon::popcount((T)0x00020000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1, hamon::popcount((T)0x00040000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1, hamon::popcount((T)0x00080000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1, hamon::popcount((T)0x00100000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1, hamon::popcount((T)0x00200000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1, hamon::popcount((T)0x00400000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1, hamon::popcount((T)0x00800000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1, hamon::popcount((T)0x01000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1, hamon::popcount((T)0x02000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1, hamon::popcount((T)0x04000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1, hamon::popcount((T)0x08000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1, hamon::popcount((T)0x10000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1, hamon::popcount((T)0x20000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1, hamon::popcount((T)0x40000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1, hamon::popcount((T)0x80000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(17, hamon::popcount((T)0x0001ffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(18, hamon::popcount((T)0x0003ffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(19, hamon::popcount((T)0x0007ffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(20, hamon::popcount((T)0x000fffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(21, hamon::popcount((T)0x001fffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(22, hamon::popcount((T)0x003fffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(23, hamon::popcount((T)0x007fffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(24, hamon::popcount((T)0x00ffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(25, hamon::popcount((T)0x01ffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(26, hamon::popcount((T)0x03ffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(27, hamon::popcount((T)0x07ffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(28, hamon::popcount((T)0x0fffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(29, hamon::popcount((T)0x1fffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(30, hamon::popcount((T)0x3fffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(31, hamon::popcount((T)0x7fffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(32, hamon::popcount((T)0xffffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 5, hamon::popcount((T)0xf1000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 6, hamon::popcount((T)0xf3000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 7, hamon::popcount((T)0xf7000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 8, hamon::popcount((T)0xff000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(13, hamon::popcount((T)0x12345678));
}

template <typename T>
void PopCountTestU64(void)
{
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(64, hamon::popcount((T)0xffffffffffffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(63, hamon::popcount((T)0xfffffffffffffffe));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(62, hamon::popcount((T)0xfffffffffffffffc));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(61, hamon::popcount((T)0xfffffffffffffff8));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(60, hamon::popcount((T)0xfffffffffffffff0));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(59, hamon::popcount((T)0xffffffffffffffe0));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(58, hamon::popcount((T)0xffffffffffffffc0));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(57, hamon::popcount((T)0xffffffffffffff80));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(56, hamon::popcount((T)0xffffffffffffff00));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(55, hamon::popcount((T)0xfffffffffffffe00));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(54, hamon::popcount((T)0xfffffffffffffc00));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(53, hamon::popcount((T)0xfffffffffffff800));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(52, hamon::popcount((T)0xfffffffffffff000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(51, hamon::popcount((T)0xffffffffffffe000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(50, hamon::popcount((T)0xffffffffffffc000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(49, hamon::popcount((T)0xffffffffffff8000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(48, hamon::popcount((T)0xffffffffffff0000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(47, hamon::popcount((T)0xfffffffffffe0000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(46, hamon::popcount((T)0xfffffffffffc0000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(45, hamon::popcount((T)0xfffffffffff80000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(44, hamon::popcount((T)0xfffffffffff00000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(43, hamon::popcount((T)0xffffffffffe00000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(42, hamon::popcount((T)0xffffffffffc00000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(41, hamon::popcount((T)0xffffffffff800000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(40, hamon::popcount((T)0xffffffffff000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(39, hamon::popcount((T)0xfffffffffe000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(38, hamon::popcount((T)0xfffffffffc000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(37, hamon::popcount((T)0xfffffffff8000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(36, hamon::popcount((T)0xfffffffff0000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(35, hamon::popcount((T)0xffffffffe0000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(34, hamon::popcount((T)0xffffffffc0000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(33, hamon::popcount((T)0xffffffff80000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(32, hamon::popcount((T)0xffffffff00000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(31, hamon::popcount((T)0xfffffffe00000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(30, hamon::popcount((T)0xfffffffc00000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(29, hamon::popcount((T)0xfffffff800000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(28, hamon::popcount((T)0xfffffff000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(27, hamon::popcount((T)0xffffffe000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(26, hamon::popcount((T)0xffffffc000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(25, hamon::popcount((T)0xffffff8000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(24, hamon::popcount((T)0xffffff0000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(23, hamon::popcount((T)0xfffffe0000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(22, hamon::popcount((T)0xfffffc0000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(21, hamon::popcount((T)0xfffff80000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(20, hamon::popcount((T)0xfffff00000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(19, hamon::popcount((T)0xffffe00000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(18, hamon::popcount((T)0xffffc00000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(17, hamon::popcount((T)0xffff800000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(16, hamon::popcount((T)0xffff000000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(15, hamon::popcount((T)0xfffe000000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(14, hamon::popcount((T)0xfffc000000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(13, hamon::popcount((T)0xfff8000000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(12, hamon::popcount((T)0xfff0000000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(11, hamon::popcount((T)0xffe0000000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(10, hamon::popcount((T)0xffc0000000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 9, hamon::popcount((T)0xff80000000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 8, hamon::popcount((T)0xff00000000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 7, hamon::popcount((T)0xfe00000000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 6, hamon::popcount((T)0xfc00000000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 5, hamon::popcount((T)0xf800000000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 4, hamon::popcount((T)0xf000000000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 3, hamon::popcount((T)0xe000000000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 2, hamon::popcount((T)0xc000000000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1, hamon::popcount((T)0x8000000000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, hamon::popcount((T)0x0000000000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(32, hamon::popcount((T)0x123456789abcdef0));
}

GTEST_TEST(BitTest, PopCountTest)
{
	PopCountTestU8<hamon::uint8_t>();
	PopCountTestU8<hamon::uint16_t>();
	PopCountTestU8<hamon::uint32_t>();
	PopCountTestU8<hamon::uint64_t>();

	PopCountTestU16<hamon::uint16_t>();
	PopCountTestU16<hamon::uint32_t>();
	PopCountTestU16<hamon::uint64_t>();

	PopCountTestU32<hamon::uint32_t>();
	PopCountTestU32<hamon::uint64_t>();

	PopCountTestU64<hamon::uint64_t>();
}

}	// namespace popcount_test

}	// namespace hamon_bit_test

HAMON_WARNING_POP()
