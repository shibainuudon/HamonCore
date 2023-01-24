﻿/**
 *	@file	unit_test_bit_bit_ceil.cpp
 *
 *	@brief	bit_ceil のテスト
 */

#include <hamon/bit/bit_ceil.hpp>
#include <gtest/gtest.h>
#include <cstdint>
#include "constexpr_test.hpp"

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4307)	// 整数定数がオーバーフローしました。
//HAMON_WARNING_DISABLE_MSVC(4310)	// キャストによって定数値が切り捨てられました。

namespace hamon_bit_test
{

namespace bit_ceil_test
{

template <typename T>
void BitCeilTestU8(void)
{
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x01), hamon::bit_ceil(T(0x00)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x01), hamon::bit_ceil(T(0x01)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x02), hamon::bit_ceil(T(0x02)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x04), hamon::bit_ceil(T(0x03)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x04), hamon::bit_ceil(T(0x04)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x08), hamon::bit_ceil(T(0x05)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x08), hamon::bit_ceil(T(0x07)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x08), hamon::bit_ceil(T(0x08)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x10), hamon::bit_ceil(T(0x09)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x10), hamon::bit_ceil(T(0x0f)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x10), hamon::bit_ceil(T(0x10)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x20), hamon::bit_ceil(T(0x11)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x20), hamon::bit_ceil(T(0x1f)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x20), hamon::bit_ceil(T(0x20)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x40), hamon::bit_ceil(T(0x21)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x40), hamon::bit_ceil(T(0x3f)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x40), hamon::bit_ceil(T(0x40)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x80), hamon::bit_ceil(T(0x41)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x80), hamon::bit_ceil(T(0x7f)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x80), hamon::bit_ceil(T(0x80)));
	//HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x100), hamon::bit_ceil(T(0x81)));
	//HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x100), hamon::bit_ceil(T(0xff)));
}

template <typename T>
void BitCeilTestU16(void)
{
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x0100), hamon::bit_ceil(T(0x00ff)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x0100), hamon::bit_ceil(T(0x0100)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x0200), hamon::bit_ceil(T(0x0101)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x0200), hamon::bit_ceil(T(0x01ff)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x0200), hamon::bit_ceil(T(0x0200)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x0400), hamon::bit_ceil(T(0x0201)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x0400), hamon::bit_ceil(T(0x03ff)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x0400), hamon::bit_ceil(T(0x0400)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x0800), hamon::bit_ceil(T(0x0401)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x0800), hamon::bit_ceil(T(0x07ff)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x0800), hamon::bit_ceil(T(0x0800)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x1000), hamon::bit_ceil(T(0x0801)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x1000), hamon::bit_ceil(T(0x0fff)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x1000), hamon::bit_ceil(T(0x1000)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x2000), hamon::bit_ceil(T(0x1001)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x2000), hamon::bit_ceil(T(0x1fff)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x2000), hamon::bit_ceil(T(0x2000)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x4000), hamon::bit_ceil(T(0x2001)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x4000), hamon::bit_ceil(T(0x3fff)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x4000), hamon::bit_ceil(T(0x4000)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x8000), hamon::bit_ceil(T(0x4001)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x8000), hamon::bit_ceil(T(0x7fff)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x8000), hamon::bit_ceil(T(0x8000)));
	//HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x10000), hamon::bit_ceil(T(0x8001)));
	//HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x10000), hamon::bit_ceil(T(0xffff)));
}

template <typename T>
void BitCeilTestU32(void)
{
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x00010000), hamon::bit_ceil(T(0x0000ffff)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x00010000), hamon::bit_ceil(T(0x00010000)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x00020000), hamon::bit_ceil(T(0x00010001)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x00020000), hamon::bit_ceil(T(0x0001ffff)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x00020000), hamon::bit_ceil(T(0x00020000)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x00040000), hamon::bit_ceil(T(0x00020001)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x00040000), hamon::bit_ceil(T(0x0003ffff)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x00040000), hamon::bit_ceil(T(0x00040000)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x00080000), hamon::bit_ceil(T(0x00040001)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x00080000), hamon::bit_ceil(T(0x0007ffff)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x00080000), hamon::bit_ceil(T(0x00080000)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x00100000), hamon::bit_ceil(T(0x00080001)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x00100000), hamon::bit_ceil(T(0x000fffff)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x00100000), hamon::bit_ceil(T(0x00100000)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x00200000), hamon::bit_ceil(T(0x00100001)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x00200000), hamon::bit_ceil(T(0x001fffff)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x00200000), hamon::bit_ceil(T(0x00200000)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x00400000), hamon::bit_ceil(T(0x00200001)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x00400000), hamon::bit_ceil(T(0x003fffff)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x00400000), hamon::bit_ceil(T(0x00400000)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x00800000), hamon::bit_ceil(T(0x00400001)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x00800000), hamon::bit_ceil(T(0x007fffff)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x00800000), hamon::bit_ceil(T(0x00800000)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x01000000), hamon::bit_ceil(T(0x00ffffff)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x01000000), hamon::bit_ceil(T(0x01000000)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x02000000), hamon::bit_ceil(T(0x01000001)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x02000000), hamon::bit_ceil(T(0x01ffffff)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x02000000), hamon::bit_ceil(T(0x02000000)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x04000000), hamon::bit_ceil(T(0x02000001)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x04000000), hamon::bit_ceil(T(0x03ffffff)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x04000000), hamon::bit_ceil(T(0x04000000)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x08000000), hamon::bit_ceil(T(0x04000001)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x08000000), hamon::bit_ceil(T(0x07ffffff)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x08000000), hamon::bit_ceil(T(0x08000000)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x10000000), hamon::bit_ceil(T(0x08000001)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x10000000), hamon::bit_ceil(T(0x0fffffff)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x10000000), hamon::bit_ceil(T(0x10000000)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x20000000), hamon::bit_ceil(T(0x10000001)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x20000000), hamon::bit_ceil(T(0x1fffffff)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x20000000), hamon::bit_ceil(T(0x20000000)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x40000000), hamon::bit_ceil(T(0x20000001)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x40000000), hamon::bit_ceil(T(0x3fffffff)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x40000000), hamon::bit_ceil(T(0x40000000)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x80000000), hamon::bit_ceil(T(0x40000001)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x80000000), hamon::bit_ceil(T(0x7fffffff)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x80000000), hamon::bit_ceil(T(0x80000000)));
}

template <typename T>
void BitCeilTestU64(void)
{
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x0000000100000000), hamon::bit_ceil(T(0x00000000ffffffff)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x0000000100000000), hamon::bit_ceil(T(0x0000000100000000)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x0000000200000000), hamon::bit_ceil(T(0x0000000100000001)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x0000000200000000), hamon::bit_ceil(T(0x00000001ffffffff)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x0000000200000000), hamon::bit_ceil(T(0x0000000200000000)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x0000000400000000), hamon::bit_ceil(T(0x0000000200000001)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x0000000400000000), hamon::bit_ceil(T(0x00000003ffffffff)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x0000000400000000), hamon::bit_ceil(T(0x0000000400000000)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x0000000800000000), hamon::bit_ceil(T(0x0000000400000001)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x0000000800000000), hamon::bit_ceil(T(0x00000007ffffffff)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x0000000800000000), hamon::bit_ceil(T(0x0000000800000000)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x0000001000000000), hamon::bit_ceil(T(0x0000000800000001)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x0000001000000000), hamon::bit_ceil(T(0x0000000fffffffff)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x0000001000000000), hamon::bit_ceil(T(0x0000001000000000)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x0000002000000000), hamon::bit_ceil(T(0x0000001000000001)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x0000002000000000), hamon::bit_ceil(T(0x0000001fffffffff)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x0000002000000000), hamon::bit_ceil(T(0x0000002000000000)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x0000004000000000), hamon::bit_ceil(T(0x0000002000000001)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x0000004000000000), hamon::bit_ceil(T(0x0000003fffffffff)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x0000004000000000), hamon::bit_ceil(T(0x0000004000000000)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x0000008000000000), hamon::bit_ceil(T(0x0000004000000001)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x0000008000000000), hamon::bit_ceil(T(0x0000007fffffffff)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x0000008000000000), hamon::bit_ceil(T(0x0000008000000000)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x0000010000000000), hamon::bit_ceil(T(0x000000ffffffffff)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x0000010000000000), hamon::bit_ceil(T(0x0000010000000000)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x0000020000000000), hamon::bit_ceil(T(0x0000010000000001)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x0000020000000000), hamon::bit_ceil(T(0x000001ffffffffff)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x0000020000000000), hamon::bit_ceil(T(0x0000020000000000)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x0000040000000000), hamon::bit_ceil(T(0x0000020000000001)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x0000040000000000), hamon::bit_ceil(T(0x000003ffffffffff)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x0000040000000000), hamon::bit_ceil(T(0x0000040000000000)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x0000080000000000), hamon::bit_ceil(T(0x0000040000000001)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x0000080000000000), hamon::bit_ceil(T(0x000007ffffffffff)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x0000080000000000), hamon::bit_ceil(T(0x0000080000000000)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x0000100000000000), hamon::bit_ceil(T(0x0000080000000001)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x0000100000000000), hamon::bit_ceil(T(0x00000fffffffffff)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x0000100000000000), hamon::bit_ceil(T(0x0000100000000000)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x0000200000000000), hamon::bit_ceil(T(0x0000100000000001)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x0000200000000000), hamon::bit_ceil(T(0x00001fffffffffff)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x0000200000000000), hamon::bit_ceil(T(0x0000200000000000)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x0000400000000000), hamon::bit_ceil(T(0x0000200000000001)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x0000400000000000), hamon::bit_ceil(T(0x00003fffffffffff)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x0000400000000000), hamon::bit_ceil(T(0x0000400000000000)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x0000800000000000), hamon::bit_ceil(T(0x0000400000000001)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x0000800000000000), hamon::bit_ceil(T(0x00007fffffffffff)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x0000800000000000), hamon::bit_ceil(T(0x0000800000000000)));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x0001000000000000), hamon::bit_ceil(T(0x0000ffffffffffff)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x0001000000000000), hamon::bit_ceil(T(0x0001000000000000)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x0002000000000000), hamon::bit_ceil(T(0x0001000000000001)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x0002000000000000), hamon::bit_ceil(T(0x0001ffffffffffff)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x0002000000000000), hamon::bit_ceil(T(0x0002000000000000)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x0004000000000000), hamon::bit_ceil(T(0x0002000000000001)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x0004000000000000), hamon::bit_ceil(T(0x0003ffffffffffff)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x0004000000000000), hamon::bit_ceil(T(0x0004000000000000)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x0008000000000000), hamon::bit_ceil(T(0x0004000000000001)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x0008000000000000), hamon::bit_ceil(T(0x0007ffffffffffff)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x0008000000000000), hamon::bit_ceil(T(0x0008000000000000)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x0010000000000000), hamon::bit_ceil(T(0x0008000000000001)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x0010000000000000), hamon::bit_ceil(T(0x000fffffffffffff)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x0010000000000000), hamon::bit_ceil(T(0x0010000000000000)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x0020000000000000), hamon::bit_ceil(T(0x0010000000000001)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x0020000000000000), hamon::bit_ceil(T(0x001fffffffffffff)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x0020000000000000), hamon::bit_ceil(T(0x0020000000000000)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x0040000000000000), hamon::bit_ceil(T(0x0020000000000001)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x0040000000000000), hamon::bit_ceil(T(0x003fffffffffffff)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x0040000000000000), hamon::bit_ceil(T(0x0040000000000000)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x0080000000000000), hamon::bit_ceil(T(0x0040000000000001)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x0080000000000000), hamon::bit_ceil(T(0x007fffffffffffff)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x0080000000000000), hamon::bit_ceil(T(0x0080000000000000)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x0100000000000000), hamon::bit_ceil(T(0x00ffffffffffffff)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x0100000000000000), hamon::bit_ceil(T(0x0100000000000000)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x0200000000000000), hamon::bit_ceil(T(0x0100000000000001)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x0200000000000000), hamon::bit_ceil(T(0x01ffffffffffffff)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x0200000000000000), hamon::bit_ceil(T(0x0200000000000000)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x0400000000000000), hamon::bit_ceil(T(0x0200000000000001)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x0400000000000000), hamon::bit_ceil(T(0x03ffffffffffffff)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x0400000000000000), hamon::bit_ceil(T(0x0400000000000000)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x0800000000000000), hamon::bit_ceil(T(0x0400000000000001)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x0800000000000000), hamon::bit_ceil(T(0x07ffffffffffffff)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x0800000000000000), hamon::bit_ceil(T(0x0800000000000000)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x1000000000000000), hamon::bit_ceil(T(0x0800000000000001)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x1000000000000000), hamon::bit_ceil(T(0x0fffffffffffffff)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x1000000000000000), hamon::bit_ceil(T(0x1000000000000000)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x2000000000000000), hamon::bit_ceil(T(0x1000000000000001)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x2000000000000000), hamon::bit_ceil(T(0x1fffffffffffffff)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x2000000000000000), hamon::bit_ceil(T(0x2000000000000000)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x4000000000000000), hamon::bit_ceil(T(0x2000000000000001)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x4000000000000000), hamon::bit_ceil(T(0x3fffffffffffffff)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x4000000000000000), hamon::bit_ceil(T(0x4000000000000000)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x8000000000000000), hamon::bit_ceil(T(0x4000000000000001)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x8000000000000000), hamon::bit_ceil(T(0x7fffffffffffffff)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x8000000000000000), hamon::bit_ceil(T(0x8000000000000000)));
}

GTEST_TEST(BitTest, BitCeilTest)
{
	BitCeilTestU8<std::uint8_t>();
	BitCeilTestU8<std::uint16_t>();
	BitCeilTestU8<std::uint32_t>();
	BitCeilTestU8<std::uint64_t>();

	BitCeilTestU16<std::uint16_t>();
	BitCeilTestU16<std::uint32_t>();
	BitCeilTestU16<std::uint64_t>();

	BitCeilTestU32<std::uint32_t>();
	BitCeilTestU32<std::uint64_t>();

	BitCeilTestU64<std::uint64_t>();
}

}	// namespace bit_ceil_test

}	// namespace hamon_bit_test

HAMON_WARNING_POP()