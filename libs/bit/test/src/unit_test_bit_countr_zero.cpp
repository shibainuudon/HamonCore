/**
 *	@file	unit_test_bit_countr_zero.cpp
 *
 *	@brief	countr_zero のテスト
 */

#include <hamon/bit/countr_zero.hpp>
#include <hamon/cstdint.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4307)	// 整数定数がオーバーフローしました。

namespace hamon_bit_test
{

namespace countr_zero_test
{

template <typename T>
void CountrZeroTestU8(void)
{
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0, hamon::countr_zero((T)0xff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1, hamon::countr_zero((T)0xfe));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2, hamon::countr_zero((T)0xfc));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3, hamon::countr_zero((T)0xf8));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(4, hamon::countr_zero((T)0xf0));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(5, hamon::countr_zero((T)0xe0));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(6, hamon::countr_zero((T)0xc0));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(7, hamon::countr_zero((T)0x80));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(8, hamon::countr_zero((T)0x00));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0, hamon::countr_zero((T)0x01));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1, hamon::countr_zero((T)0x02));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2, hamon::countr_zero((T)0x04));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3, hamon::countr_zero((T)0x08));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(4, hamon::countr_zero((T)0x10));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(5, hamon::countr_zero((T)0x20));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(6, hamon::countr_zero((T)0x40));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(7, hamon::countr_zero((T)0x80));
}

template <typename T>
void CountrZeroTestU16(void)
{
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, hamon::countr_zero((T)0xffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1, hamon::countr_zero((T)0xfffe));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 2, hamon::countr_zero((T)0xfffc));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 3, hamon::countr_zero((T)0xfff8));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 4, hamon::countr_zero((T)0xfff0));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 5, hamon::countr_zero((T)0xffe0));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 6, hamon::countr_zero((T)0xffc0));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 7, hamon::countr_zero((T)0xff80));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 8, hamon::countr_zero((T)0xff00));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 9, hamon::countr_zero((T)0xfe00));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(10, hamon::countr_zero((T)0xfc00));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(11, hamon::countr_zero((T)0xf800));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(12, hamon::countr_zero((T)0xf000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(13, hamon::countr_zero((T)0xe000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(14, hamon::countr_zero((T)0xc000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(15, hamon::countr_zero((T)0x8000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(16, hamon::countr_zero((T)0x0000));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 8, hamon::countr_zero((T)0x0100));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 9, hamon::countr_zero((T)0x0200));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(10, hamon::countr_zero((T)0x0400));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(11, hamon::countr_zero((T)0x0800));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(12, hamon::countr_zero((T)0x1000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(13, hamon::countr_zero((T)0x2000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(14, hamon::countr_zero((T)0x4000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(15, hamon::countr_zero((T)0x8000));
}

template <typename T>
void CountrZeroTestU32(void)
{
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, hamon::countr_zero((T)0xffffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1, hamon::countr_zero((T)0xfffffffe));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 2, hamon::countr_zero((T)0xfffffffc));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 3, hamon::countr_zero((T)0xfffffff8));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 4, hamon::countr_zero((T)0xfffffff0));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 5, hamon::countr_zero((T)0xffffffe0));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 6, hamon::countr_zero((T)0xffffffc0));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 7, hamon::countr_zero((T)0xffffff80));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 8, hamon::countr_zero((T)0xffffff00));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 9, hamon::countr_zero((T)0xfffffe00));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(10, hamon::countr_zero((T)0xfffffc00));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(11, hamon::countr_zero((T)0xfffff800));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(12, hamon::countr_zero((T)0xfffff000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(13, hamon::countr_zero((T)0xffffe000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(14, hamon::countr_zero((T)0xffffc000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(15, hamon::countr_zero((T)0xffff8000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(16, hamon::countr_zero((T)0xffff0000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(17, hamon::countr_zero((T)0xfffe0000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(18, hamon::countr_zero((T)0xfffc0000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(19, hamon::countr_zero((T)0xfff80000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(20, hamon::countr_zero((T)0xfff00000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(21, hamon::countr_zero((T)0xffe00000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(22, hamon::countr_zero((T)0xffc00000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(23, hamon::countr_zero((T)0xff800000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(24, hamon::countr_zero((T)0xff000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(25, hamon::countr_zero((T)0xfe000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(26, hamon::countr_zero((T)0xfc000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(27, hamon::countr_zero((T)0xf8000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(28, hamon::countr_zero((T)0xf0000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(29, hamon::countr_zero((T)0xe0000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(30, hamon::countr_zero((T)0xc0000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(31, hamon::countr_zero((T)0x80000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(32, hamon::countr_zero((T)0x00000000));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(16, hamon::countr_zero((T)0x00010000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(17, hamon::countr_zero((T)0x00020000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(18, hamon::countr_zero((T)0x00040000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(19, hamon::countr_zero((T)0x00080000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(20, hamon::countr_zero((T)0x00100000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(21, hamon::countr_zero((T)0x00200000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(22, hamon::countr_zero((T)0x00400000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(23, hamon::countr_zero((T)0x00800000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(24, hamon::countr_zero((T)0x01000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(25, hamon::countr_zero((T)0x02000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(26, hamon::countr_zero((T)0x04000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(27, hamon::countr_zero((T)0x08000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(28, hamon::countr_zero((T)0x10000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(29, hamon::countr_zero((T)0x20000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(30, hamon::countr_zero((T)0x40000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(31, hamon::countr_zero((T)0x80000000));
}

template <typename T>
void CountrZeroTestU64(void)
{
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, hamon::countr_zero((T)0xffffffffffffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1, hamon::countr_zero((T)0xfffffffffffffffe));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 2, hamon::countr_zero((T)0xfffffffffffffffc));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 3, hamon::countr_zero((T)0xfffffffffffffff8));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 4, hamon::countr_zero((T)0xfffffffffffffff0));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 5, hamon::countr_zero((T)0xffffffffffffffe0));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 6, hamon::countr_zero((T)0xffffffffffffffc0));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 7, hamon::countr_zero((T)0xffffffffffffff80));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 8, hamon::countr_zero((T)0xffffffffffffff00));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 9, hamon::countr_zero((T)0xfffffffffffffe00));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(10, hamon::countr_zero((T)0xfffffffffffffc00));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(11, hamon::countr_zero((T)0xfffffffffffff800));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(12, hamon::countr_zero((T)0xfffffffffffff000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(13, hamon::countr_zero((T)0xffffffffffffe000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(14, hamon::countr_zero((T)0xffffffffffffc000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(15, hamon::countr_zero((T)0xffffffffffff8000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(16, hamon::countr_zero((T)0xffffffffffff0000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(17, hamon::countr_zero((T)0xfffffffffffe0000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(18, hamon::countr_zero((T)0xfffffffffffc0000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(19, hamon::countr_zero((T)0xfffffffffff80000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(20, hamon::countr_zero((T)0xfffffffffff00000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(21, hamon::countr_zero((T)0xffffffffffe00000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(22, hamon::countr_zero((T)0xffffffffffc00000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(23, hamon::countr_zero((T)0xffffffffff800000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(24, hamon::countr_zero((T)0xffffffffff000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(25, hamon::countr_zero((T)0xfffffffffe000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(26, hamon::countr_zero((T)0xfffffffffc000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(27, hamon::countr_zero((T)0xfffffffff8000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(28, hamon::countr_zero((T)0xfffffffff0000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(29, hamon::countr_zero((T)0xffffffffe0000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(30, hamon::countr_zero((T)0xffffffffc0000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(31, hamon::countr_zero((T)0xffffffff80000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(32, hamon::countr_zero((T)0xffffffff00000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(33, hamon::countr_zero((T)0xfffffffe00000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(34, hamon::countr_zero((T)0xfffffffc00000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(35, hamon::countr_zero((T)0xfffffff800000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(36, hamon::countr_zero((T)0xfffffff000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(37, hamon::countr_zero((T)0xffffffe000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(38, hamon::countr_zero((T)0xffffffc000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(39, hamon::countr_zero((T)0xffffff8000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(40, hamon::countr_zero((T)0xffffff0000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(41, hamon::countr_zero((T)0xfffffe0000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(42, hamon::countr_zero((T)0xfffffc0000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(43, hamon::countr_zero((T)0xfffff80000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(44, hamon::countr_zero((T)0xfffff00000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(45, hamon::countr_zero((T)0xffffe00000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(46, hamon::countr_zero((T)0xffffc00000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(47, hamon::countr_zero((T)0xffff800000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(48, hamon::countr_zero((T)0xffff000000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(49, hamon::countr_zero((T)0xfffe000000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(50, hamon::countr_zero((T)0xfffc000000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(51, hamon::countr_zero((T)0xfff8000000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(52, hamon::countr_zero((T)0xfff0000000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(53, hamon::countr_zero((T)0xffe0000000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(54, hamon::countr_zero((T)0xffc0000000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(55, hamon::countr_zero((T)0xff80000000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(56, hamon::countr_zero((T)0xff00000000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(57, hamon::countr_zero((T)0xfe00000000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(58, hamon::countr_zero((T)0xfc00000000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(59, hamon::countr_zero((T)0xf800000000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(60, hamon::countr_zero((T)0xf000000000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(61, hamon::countr_zero((T)0xe000000000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(62, hamon::countr_zero((T)0xc000000000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(63, hamon::countr_zero((T)0x8000000000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(64, hamon::countr_zero((T)0x0000000000000000));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(32, hamon::countr_zero((T)0x0000000100000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(33, hamon::countr_zero((T)0x0000000200000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(34, hamon::countr_zero((T)0x0000000400000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(35, hamon::countr_zero((T)0x0000000800000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(36, hamon::countr_zero((T)0x0000001000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(37, hamon::countr_zero((T)0x0000002000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(38, hamon::countr_zero((T)0x0000004000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(39, hamon::countr_zero((T)0x0000008000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(40, hamon::countr_zero((T)0x0000010000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(41, hamon::countr_zero((T)0x0000020000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(42, hamon::countr_zero((T)0x0000040000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(43, hamon::countr_zero((T)0x0000080000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(44, hamon::countr_zero((T)0x0000100000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(45, hamon::countr_zero((T)0x0000200000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(46, hamon::countr_zero((T)0x0000400000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(47, hamon::countr_zero((T)0x0000800000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(48, hamon::countr_zero((T)0x0001000000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(49, hamon::countr_zero((T)0x0002000000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(50, hamon::countr_zero((T)0x0004000000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(51, hamon::countr_zero((T)0x0008000000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(52, hamon::countr_zero((T)0x0010000000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(53, hamon::countr_zero((T)0x0020000000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(54, hamon::countr_zero((T)0x0040000000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(55, hamon::countr_zero((T)0x0080000000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(56, hamon::countr_zero((T)0x0100000000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(57, hamon::countr_zero((T)0x0200000000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(58, hamon::countr_zero((T)0x0400000000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(59, hamon::countr_zero((T)0x0800000000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(60, hamon::countr_zero((T)0x1000000000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(61, hamon::countr_zero((T)0x2000000000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(62, hamon::countr_zero((T)0x4000000000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(63, hamon::countr_zero((T)0x8000000000000000));
}

GTEST_TEST(BitTest, CountrZeroTest)
{
	CountrZeroTestU8<hamon::uint8_t>();
	CountrZeroTestU16<hamon::uint16_t>();
	CountrZeroTestU32<hamon::uint32_t>();
	CountrZeroTestU64<hamon::uint64_t>();
}

}	// namespace countr_zero_test

}	// namespace hamon_bit_test

HAMON_WARNING_POP()
