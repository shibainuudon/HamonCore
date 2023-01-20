/**
 *	@file	unit_test_bit_countl_one.cpp
 *
 *	@brief	countl_one のテスト
 */

#include <hamon/bit/countl_one.hpp>
#include <gtest/gtest.h>
#include <cstdint>
#include "constexpr_test.hpp"

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4307)	// 整数定数がオーバーフローしました。

namespace hamon_bit_test
{

namespace countl_one_test
{

template <typename T>
void CountlOneTestU8(void)
{
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(8, hamon::countl_one((T)0xff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(7, hamon::countl_one((T)0xfe));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(6, hamon::countl_one((T)0xfc));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(5, hamon::countl_one((T)0xf8));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(4, hamon::countl_one((T)0xf0));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3, hamon::countl_one((T)0xe0));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2, hamon::countl_one((T)0xc0));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1, hamon::countl_one((T)0x80));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0, hamon::countl_one((T)0x00));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0, hamon::countl_one((T)0x01));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0, hamon::countl_one((T)0x02));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0, hamon::countl_one((T)0x03));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0, hamon::countl_one((T)0x04));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(4, hamon::countl_one((T)0xf1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(4, hamon::countl_one((T)0xf2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(4, hamon::countl_one((T)0xf3));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(4, hamon::countl_one((T)0xf4));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3, hamon::countl_one((T)0xe1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3, hamon::countl_one((T)0xe2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3, hamon::countl_one((T)0xe3));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3, hamon::countl_one((T)0xe4));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1, hamon::countl_one((T)0x81));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1, hamon::countl_one((T)0x82));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1, hamon::countl_one((T)0x83));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1, hamon::countl_one((T)0x84));
}

template <typename T>
void CountlOneTestU16(void)
{
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(16, hamon::countl_one((T)0xffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(15, hamon::countl_one((T)0xfffe));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(14, hamon::countl_one((T)0xfffc));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(13, hamon::countl_one((T)0xfff8));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(12, hamon::countl_one((T)0xfff0));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(11, hamon::countl_one((T)0xffe0));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(10, hamon::countl_one((T)0xffc0));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 9, hamon::countl_one((T)0xff80));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 8, hamon::countl_one((T)0xff00));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 7, hamon::countl_one((T)0xfe00));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 6, hamon::countl_one((T)0xfc00));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 5, hamon::countl_one((T)0xf800));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 4, hamon::countl_one((T)0xf000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 3, hamon::countl_one((T)0xe000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 2, hamon::countl_one((T)0xc000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1, hamon::countl_one((T)0x8000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, hamon::countl_one((T)0x0000));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, hamon::countl_one((T)0x0001));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, hamon::countl_one((T)0x0002));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, hamon::countl_one((T)0x0003));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, hamon::countl_one((T)0x0004));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 4, hamon::countl_one((T)0xf001));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 4, hamon::countl_one((T)0xf082));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 4, hamon::countl_one((T)0xf0c3));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 4, hamon::countl_one((T)0xf0f4));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 8, hamon::countl_one((T)0xff01));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 8, hamon::countl_one((T)0xff02));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 8, hamon::countl_one((T)0xff03));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 8, hamon::countl_one((T)0xff04));
}

template <typename T>
void CountlOneTestU32(void)
{
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(32, hamon::countl_one((T)0xffffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(31, hamon::countl_one((T)0xfffffffe));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(30, hamon::countl_one((T)0xfffffffc));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(29, hamon::countl_one((T)0xfffffff8));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(28, hamon::countl_one((T)0xfffffff0));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(27, hamon::countl_one((T)0xffffffe0));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(26, hamon::countl_one((T)0xffffffc0));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(25, hamon::countl_one((T)0xffffff80));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(24, hamon::countl_one((T)0xffffff00));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(23, hamon::countl_one((T)0xfffffe00));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(22, hamon::countl_one((T)0xfffffc00));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(21, hamon::countl_one((T)0xfffff800));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(20, hamon::countl_one((T)0xfffff000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(19, hamon::countl_one((T)0xffffe000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(18, hamon::countl_one((T)0xffffc000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(17, hamon::countl_one((T)0xffff8000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(16, hamon::countl_one((T)0xffff0000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(15, hamon::countl_one((T)0xfffe0000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(14, hamon::countl_one((T)0xfffc0000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(13, hamon::countl_one((T)0xfff80000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(12, hamon::countl_one((T)0xfff00000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(11, hamon::countl_one((T)0xffe00000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(10, hamon::countl_one((T)0xffc00000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 9, hamon::countl_one((T)0xff800000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 8, hamon::countl_one((T)0xff000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 7, hamon::countl_one((T)0xfe000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 6, hamon::countl_one((T)0xfc000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 5, hamon::countl_one((T)0xf8000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 4, hamon::countl_one((T)0xf0000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 3, hamon::countl_one((T)0xe0000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 2, hamon::countl_one((T)0xc0000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1, hamon::countl_one((T)0x80000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, hamon::countl_one((T)0x00000000));
}

template <typename T>
void CountlOneTestU64(void)
{
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(64, hamon::countl_one((T)0xffffffffffffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(63, hamon::countl_one((T)0xfffffffffffffffe));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(62, hamon::countl_one((T)0xfffffffffffffffc));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(61, hamon::countl_one((T)0xfffffffffffffff8));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(60, hamon::countl_one((T)0xfffffffffffffff0));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(59, hamon::countl_one((T)0xffffffffffffffe0));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(58, hamon::countl_one((T)0xffffffffffffffc0));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(57, hamon::countl_one((T)0xffffffffffffff80));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(56, hamon::countl_one((T)0xffffffffffffff00));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(55, hamon::countl_one((T)0xfffffffffffffe00));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(54, hamon::countl_one((T)0xfffffffffffffc00));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(53, hamon::countl_one((T)0xfffffffffffff800));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(52, hamon::countl_one((T)0xfffffffffffff000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(51, hamon::countl_one((T)0xffffffffffffe000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(50, hamon::countl_one((T)0xffffffffffffc000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(49, hamon::countl_one((T)0xffffffffffff8000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(48, hamon::countl_one((T)0xffffffffffff0000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(47, hamon::countl_one((T)0xfffffffffffe0000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(46, hamon::countl_one((T)0xfffffffffffc0000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(45, hamon::countl_one((T)0xfffffffffff80000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(44, hamon::countl_one((T)0xfffffffffff00000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(43, hamon::countl_one((T)0xffffffffffe00000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(42, hamon::countl_one((T)0xffffffffffc00000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(41, hamon::countl_one((T)0xffffffffff800000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(40, hamon::countl_one((T)0xffffffffff000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(39, hamon::countl_one((T)0xfffffffffe000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(38, hamon::countl_one((T)0xfffffffffc000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(37, hamon::countl_one((T)0xfffffffff8000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(36, hamon::countl_one((T)0xfffffffff0000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(35, hamon::countl_one((T)0xffffffffe0000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(34, hamon::countl_one((T)0xffffffffc0000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(33, hamon::countl_one((T)0xffffffff80000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(32, hamon::countl_one((T)0xffffffff00000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(31, hamon::countl_one((T)0xfffffffe00000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(30, hamon::countl_one((T)0xfffffffc00000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(29, hamon::countl_one((T)0xfffffff800000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(28, hamon::countl_one((T)0xfffffff000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(27, hamon::countl_one((T)0xffffffe000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(26, hamon::countl_one((T)0xffffffc000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(25, hamon::countl_one((T)0xffffff8000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(24, hamon::countl_one((T)0xffffff0000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(23, hamon::countl_one((T)0xfffffe0000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(22, hamon::countl_one((T)0xfffffc0000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(21, hamon::countl_one((T)0xfffff80000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(20, hamon::countl_one((T)0xfffff00000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(19, hamon::countl_one((T)0xffffe00000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(18, hamon::countl_one((T)0xffffc00000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(17, hamon::countl_one((T)0xffff800000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(16, hamon::countl_one((T)0xffff000000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(15, hamon::countl_one((T)0xfffe000000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(14, hamon::countl_one((T)0xfffc000000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(13, hamon::countl_one((T)0xfff8000000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(12, hamon::countl_one((T)0xfff0000000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(11, hamon::countl_one((T)0xffe0000000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(10, hamon::countl_one((T)0xffc0000000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 9, hamon::countl_one((T)0xff80000000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 8, hamon::countl_one((T)0xff00000000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 7, hamon::countl_one((T)0xfe00000000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 6, hamon::countl_one((T)0xfc00000000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 5, hamon::countl_one((T)0xf800000000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 4, hamon::countl_one((T)0xf000000000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 3, hamon::countl_one((T)0xe000000000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 2, hamon::countl_one((T)0xc000000000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1, hamon::countl_one((T)0x8000000000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, hamon::countl_one((T)0x0000000000000000));
}

GTEST_TEST(BitTest, CountlOneTest)
{
	CountlOneTestU8<std::uint8_t>();
	CountlOneTestU16<std::uint16_t>();
	CountlOneTestU32<std::uint32_t>();
	CountlOneTestU64<std::uint64_t>();
}

}	// namespace countl_one_test

}	// namespace hamon_bit_test

HAMON_WARNING_POP()
