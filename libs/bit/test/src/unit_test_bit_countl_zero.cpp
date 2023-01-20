/**
 *	@file	unit_test_bit_countl_zero.cpp
 *
 *	@brief	countl_zero のテスト
 */

#include <hamon/bit/countl_zero.hpp>
#include <gtest/gtest.h>
#include <cstdint>
#include "constexpr_test.hpp"

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4307)	// 整数定数がオーバーフローしました。

namespace hamon_bit_test
{

namespace countl_zero_test
{

template <typename T>
void CountlZeroTestU8(void)
{
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0, hamon::countl_zero((T)0xff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0, hamon::countl_zero((T)0x80));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1, hamon::countl_zero((T)0x7f));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1, hamon::countl_zero((T)0x40));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2, hamon::countl_zero((T)0x3f));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2, hamon::countl_zero((T)0x20));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3, hamon::countl_zero((T)0x1f));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3, hamon::countl_zero((T)0x10));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(4, hamon::countl_zero((T)0x0f));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(4, hamon::countl_zero((T)0x08));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(5, hamon::countl_zero((T)0x07));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(5, hamon::countl_zero((T)0x04));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(6, hamon::countl_zero((T)0x03));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(6, hamon::countl_zero((T)0x02));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(7, hamon::countl_zero((T)0x01));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(8, hamon::countl_zero((T)0x00));
}

template <typename T>
void CountlZeroTestU16(void)
{
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, hamon::countl_zero((T)0xffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, hamon::countl_zero((T)0x8000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1, hamon::countl_zero((T)0x7fff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1, hamon::countl_zero((T)0x4000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 2, hamon::countl_zero((T)0x3fff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 2, hamon::countl_zero((T)0x2000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 3, hamon::countl_zero((T)0x1fff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 3, hamon::countl_zero((T)0x1000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 4, hamon::countl_zero((T)0x0fff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 4, hamon::countl_zero((T)0x0800));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 5, hamon::countl_zero((T)0x07ff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 5, hamon::countl_zero((T)0x0400));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 6, hamon::countl_zero((T)0x03ff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 6, hamon::countl_zero((T)0x0200));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 7, hamon::countl_zero((T)0x01ff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 7, hamon::countl_zero((T)0x0100));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 8, hamon::countl_zero((T)0x00ff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 8, hamon::countl_zero((T)0x0080));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 9, hamon::countl_zero((T)0x007f));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 9, hamon::countl_zero((T)0x0040));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(10, hamon::countl_zero((T)0x003f));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(10, hamon::countl_zero((T)0x0020));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(11, hamon::countl_zero((T)0x001f));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(11, hamon::countl_zero((T)0x0010));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(12, hamon::countl_zero((T)0x000f));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(12, hamon::countl_zero((T)0x0008));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(13, hamon::countl_zero((T)0x0007));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(13, hamon::countl_zero((T)0x0004));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(14, hamon::countl_zero((T)0x0003));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(14, hamon::countl_zero((T)0x0002));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(15, hamon::countl_zero((T)0x0001));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(16, hamon::countl_zero((T)0x0000));
}

template <typename T>
void CountlZeroTestU32(void)
{
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, hamon::countl_zero((T)0xffffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, hamon::countl_zero((T)0x80000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1, hamon::countl_zero((T)0x7fffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1, hamon::countl_zero((T)0x40000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 2, hamon::countl_zero((T)0x3fffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 2, hamon::countl_zero((T)0x20000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 3, hamon::countl_zero((T)0x1fffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 3, hamon::countl_zero((T)0x10000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 4, hamon::countl_zero((T)0x0fffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 4, hamon::countl_zero((T)0x08000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 5, hamon::countl_zero((T)0x07ffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 5, hamon::countl_zero((T)0x04000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 6, hamon::countl_zero((T)0x03ffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 6, hamon::countl_zero((T)0x02000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 7, hamon::countl_zero((T)0x01ffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 7, hamon::countl_zero((T)0x01000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 8, hamon::countl_zero((T)0x00ffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 8, hamon::countl_zero((T)0x00800000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 9, hamon::countl_zero((T)0x007fffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 9, hamon::countl_zero((T)0x00400000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(10, hamon::countl_zero((T)0x003fffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(10, hamon::countl_zero((T)0x00200000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(11, hamon::countl_zero((T)0x001fffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(11, hamon::countl_zero((T)0x00100000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(12, hamon::countl_zero((T)0x000fffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(12, hamon::countl_zero((T)0x00080000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(13, hamon::countl_zero((T)0x0007ffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(13, hamon::countl_zero((T)0x00040000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(14, hamon::countl_zero((T)0x0003ffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(14, hamon::countl_zero((T)0x00020000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(15, hamon::countl_zero((T)0x0001ffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(15, hamon::countl_zero((T)0x00010000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(16, hamon::countl_zero((T)0x0000ffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(16, hamon::countl_zero((T)0x00008000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(17, hamon::countl_zero((T)0x00007fff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(17, hamon::countl_zero((T)0x00004000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(18, hamon::countl_zero((T)0x00003fff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(18, hamon::countl_zero((T)0x00002000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(19, hamon::countl_zero((T)0x00001fff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(19, hamon::countl_zero((T)0x00001000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(20, hamon::countl_zero((T)0x00000fff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(20, hamon::countl_zero((T)0x00000800));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(21, hamon::countl_zero((T)0x000007ff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(21, hamon::countl_zero((T)0x00000400));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(22, hamon::countl_zero((T)0x000003ff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(22, hamon::countl_zero((T)0x00000200));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(23, hamon::countl_zero((T)0x000001ff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(23, hamon::countl_zero((T)0x00000100));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(24, hamon::countl_zero((T)0x000000ff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(24, hamon::countl_zero((T)0x00000080));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(25, hamon::countl_zero((T)0x0000007f));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(25, hamon::countl_zero((T)0x00000040));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(26, hamon::countl_zero((T)0x0000003f));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(26, hamon::countl_zero((T)0x00000020));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(27, hamon::countl_zero((T)0x0000001f));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(27, hamon::countl_zero((T)0x00000010));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(28, hamon::countl_zero((T)0x0000000f));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(28, hamon::countl_zero((T)0x00000008));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(29, hamon::countl_zero((T)0x00000007));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(29, hamon::countl_zero((T)0x00000004));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(30, hamon::countl_zero((T)0x00000003));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(30, hamon::countl_zero((T)0x00000002));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(31, hamon::countl_zero((T)0x00000001));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(32, hamon::countl_zero((T)0x00000000));
}

template <typename T>
void CountlZeroTestU64(void)
{
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, hamon::countl_zero((T)0xffffffffffffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, hamon::countl_zero((T)0x8000000000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1, hamon::countl_zero((T)0x7fffffffffffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1, hamon::countl_zero((T)0x4000000000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 2, hamon::countl_zero((T)0x3fffffffffffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 2, hamon::countl_zero((T)0x2000000000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 3, hamon::countl_zero((T)0x1fffffffffffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 3, hamon::countl_zero((T)0x1000000000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 4, hamon::countl_zero((T)0x0fffffffffffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 4, hamon::countl_zero((T)0x0800000000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 5, hamon::countl_zero((T)0x07ffffffffffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 5, hamon::countl_zero((T)0x0400000000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 6, hamon::countl_zero((T)0x03ffffffffffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 6, hamon::countl_zero((T)0x0200000000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 7, hamon::countl_zero((T)0x01ffffffffffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 7, hamon::countl_zero((T)0x0100000000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 8, hamon::countl_zero((T)0x00ffffffffffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 8, hamon::countl_zero((T)0x0080000000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 9, hamon::countl_zero((T)0x007fffffffffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 9, hamon::countl_zero((T)0x0040000000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(10, hamon::countl_zero((T)0x003fffffffffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(10, hamon::countl_zero((T)0x0020000000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(11, hamon::countl_zero((T)0x001fffffffffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(11, hamon::countl_zero((T)0x0010000000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(12, hamon::countl_zero((T)0x000fffffffffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(12, hamon::countl_zero((T)0x0008000000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(13, hamon::countl_zero((T)0x0007ffffffffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(13, hamon::countl_zero((T)0x0004000000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(14, hamon::countl_zero((T)0x0003ffffffffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(14, hamon::countl_zero((T)0x0002000000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(15, hamon::countl_zero((T)0x0001ffffffffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(15, hamon::countl_zero((T)0x0001000000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(16, hamon::countl_zero((T)0x0000ffffffffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(16, hamon::countl_zero((T)0x0000800000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(17, hamon::countl_zero((T)0x00007fffffffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(17, hamon::countl_zero((T)0x0000400000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(18, hamon::countl_zero((T)0x00003fffffffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(18, hamon::countl_zero((T)0x0000200000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(19, hamon::countl_zero((T)0x00001fffffffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(19, hamon::countl_zero((T)0x0000100000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(20, hamon::countl_zero((T)0x00000fffffffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(20, hamon::countl_zero((T)0x0000080000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(21, hamon::countl_zero((T)0x000007ffffffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(21, hamon::countl_zero((T)0x0000040000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(22, hamon::countl_zero((T)0x000003ffffffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(22, hamon::countl_zero((T)0x0000020000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(23, hamon::countl_zero((T)0x000001ffffffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(23, hamon::countl_zero((T)0x0000010000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(24, hamon::countl_zero((T)0x000000ffffffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(24, hamon::countl_zero((T)0x0000008000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(25, hamon::countl_zero((T)0x0000007fffffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(25, hamon::countl_zero((T)0x0000004000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(26, hamon::countl_zero((T)0x0000003fffffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(26, hamon::countl_zero((T)0x0000002000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(27, hamon::countl_zero((T)0x0000001fffffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(27, hamon::countl_zero((T)0x0000001000000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(28, hamon::countl_zero((T)0x0000000fffffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(28, hamon::countl_zero((T)0x0000000800000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(29, hamon::countl_zero((T)0x00000007ffffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(29, hamon::countl_zero((T)0x0000000400000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(30, hamon::countl_zero((T)0x00000003ffffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(30, hamon::countl_zero((T)0x0000000200000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(31, hamon::countl_zero((T)0x00000001ffffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(31, hamon::countl_zero((T)0x0000000100000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(32, hamon::countl_zero((T)0x00000000ffffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(32, hamon::countl_zero((T)0x0000000080000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(33, hamon::countl_zero((T)0x000000007fffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(33, hamon::countl_zero((T)0x0000000040000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(34, hamon::countl_zero((T)0x000000003fffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(34, hamon::countl_zero((T)0x0000000020000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(35, hamon::countl_zero((T)0x000000001fffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(35, hamon::countl_zero((T)0x0000000010000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(36, hamon::countl_zero((T)0x000000000fffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(36, hamon::countl_zero((T)0x0000000008000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(37, hamon::countl_zero((T)0x0000000007ffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(37, hamon::countl_zero((T)0x0000000004000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(38, hamon::countl_zero((T)0x0000000003ffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(38, hamon::countl_zero((T)0x0000000002000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(39, hamon::countl_zero((T)0x0000000001ffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(39, hamon::countl_zero((T)0x0000000001000000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(40, hamon::countl_zero((T)0x0000000000ffffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(40, hamon::countl_zero((T)0x0000000000800000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(41, hamon::countl_zero((T)0x00000000007fffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(41, hamon::countl_zero((T)0x0000000000400000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(42, hamon::countl_zero((T)0x00000000003fffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(42, hamon::countl_zero((T)0x0000000000200000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(43, hamon::countl_zero((T)0x00000000001fffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(43, hamon::countl_zero((T)0x0000000000100000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(44, hamon::countl_zero((T)0x00000000000fffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(44, hamon::countl_zero((T)0x0000000000080000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(45, hamon::countl_zero((T)0x000000000007ffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(45, hamon::countl_zero((T)0x0000000000040000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(46, hamon::countl_zero((T)0x000000000003ffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(46, hamon::countl_zero((T)0x0000000000020000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(47, hamon::countl_zero((T)0x000000000001ffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(47, hamon::countl_zero((T)0x0000000000010000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(48, hamon::countl_zero((T)0x000000000000ffff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(48, hamon::countl_zero((T)0x0000000000008000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(49, hamon::countl_zero((T)0x0000000000007fff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(49, hamon::countl_zero((T)0x0000000000004000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(50, hamon::countl_zero((T)0x0000000000003fff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(50, hamon::countl_zero((T)0x0000000000002000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(51, hamon::countl_zero((T)0x0000000000001fff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(51, hamon::countl_zero((T)0x0000000000001000));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(52, hamon::countl_zero((T)0x0000000000000fff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(52, hamon::countl_zero((T)0x0000000000000800));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(53, hamon::countl_zero((T)0x00000000000007ff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(53, hamon::countl_zero((T)0x0000000000000400));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(54, hamon::countl_zero((T)0x00000000000003ff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(54, hamon::countl_zero((T)0x0000000000000200));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(55, hamon::countl_zero((T)0x00000000000001ff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(55, hamon::countl_zero((T)0x0000000000000100));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(56, hamon::countl_zero((T)0x00000000000000ff));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(56, hamon::countl_zero((T)0x0000000000000080));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(57, hamon::countl_zero((T)0x000000000000007f));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(57, hamon::countl_zero((T)0x0000000000000040));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(58, hamon::countl_zero((T)0x000000000000003f));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(58, hamon::countl_zero((T)0x0000000000000020));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(59, hamon::countl_zero((T)0x000000000000001f));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(59, hamon::countl_zero((T)0x0000000000000010));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(60, hamon::countl_zero((T)0x000000000000000f));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(60, hamon::countl_zero((T)0x0000000000000008));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(61, hamon::countl_zero((T)0x0000000000000007));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(61, hamon::countl_zero((T)0x0000000000000004));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(62, hamon::countl_zero((T)0x0000000000000003));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(62, hamon::countl_zero((T)0x0000000000000002));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(63, hamon::countl_zero((T)0x0000000000000001));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(64, hamon::countl_zero((T)0x0000000000000000));
}

GTEST_TEST(BitTest, CountlZeroTest)
{
	CountlZeroTestU8<std::uint8_t>();
	CountlZeroTestU16<std::uint16_t>();
	CountlZeroTestU32<std::uint32_t>();
	CountlZeroTestU64<std::uint64_t>();
}

}	// namespace countl_zero_test

}	// namespace hamon_bit_test

HAMON_WARNING_POP()
