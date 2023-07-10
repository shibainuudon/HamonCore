﻿/**
 *	@file	unit_test_bit_shl.cpp
 *
 *	@brief	shl のテスト
 */

#include <hamon/bit/shl.hpp>
#include <hamon/cstdint.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

GTEST_TEST(BitTest, ShlTest)
{
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint8_t(0x01), hamon::shl(hamon::uint8_t(0x01),  0));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint8_t(0x02), hamon::shl(hamon::uint8_t(0x01),  1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint8_t(0x04), hamon::shl(hamon::uint8_t(0x01),  2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint8_t(0x08), hamon::shl(hamon::uint8_t(0x01),  3));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint8_t(0x10), hamon::shl(hamon::uint8_t(0x01),  4));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint8_t(0x20), hamon::shl(hamon::uint8_t(0x01),  5));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint8_t(0x40), hamon::shl(hamon::uint8_t(0x01),  6));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint8_t(0x80), hamon::shl(hamon::uint8_t(0x01),  7));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint8_t(0x00), hamon::shl(hamon::uint8_t(0x01),  8));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint16_t(0x0001), hamon::shl(hamon::uint16_t(0x0001),  0));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint16_t(0x0002), hamon::shl(hamon::uint16_t(0x0001),  1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint16_t(0x0004), hamon::shl(hamon::uint16_t(0x0001),  2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint16_t(0x0008), hamon::shl(hamon::uint16_t(0x0001),  3));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint16_t(0x0010), hamon::shl(hamon::uint16_t(0x0001),  4));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint16_t(0x0020), hamon::shl(hamon::uint16_t(0x0001),  5));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint16_t(0x0040), hamon::shl(hamon::uint16_t(0x0001),  6));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint16_t(0x0080), hamon::shl(hamon::uint16_t(0x0001),  7));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint16_t(0x0100), hamon::shl(hamon::uint16_t(0x0001),  8));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint16_t(0x0200), hamon::shl(hamon::uint16_t(0x0001),  9));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint16_t(0x0400), hamon::shl(hamon::uint16_t(0x0001), 10));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint16_t(0x0800), hamon::shl(hamon::uint16_t(0x0001), 11));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint16_t(0x1000), hamon::shl(hamon::uint16_t(0x0001), 12));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint16_t(0x2000), hamon::shl(hamon::uint16_t(0x0001), 13));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint16_t(0x4000), hamon::shl(hamon::uint16_t(0x0001), 14));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint16_t(0x8000), hamon::shl(hamon::uint16_t(0x0001), 15));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint16_t(0x0000), hamon::shl(hamon::uint16_t(0x0001), 16));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint16_t(0x1234), hamon::shl(hamon::uint16_t(0x1234),  0));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint16_t(0x2468), hamon::shl(hamon::uint16_t(0x1234),  1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint16_t(0x48D0), hamon::shl(hamon::uint16_t(0x1234),  2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint16_t(0x91A0), hamon::shl(hamon::uint16_t(0x1234),  3));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint16_t(0x2340), hamon::shl(hamon::uint16_t(0x1234),  4));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint16_t(0x4680), hamon::shl(hamon::uint16_t(0x1234),  5));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint16_t(0x8D00), hamon::shl(hamon::uint16_t(0x1234),  6));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint16_t(0x1A00), hamon::shl(hamon::uint16_t(0x1234),  7));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint16_t(0x3400), hamon::shl(hamon::uint16_t(0x1234),  8));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint16_t(0x6800), hamon::shl(hamon::uint16_t(0x1234),  9));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint16_t(0xD000), hamon::shl(hamon::uint16_t(0x1234), 10));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint16_t(0xA000), hamon::shl(hamon::uint16_t(0x1234), 11));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint16_t(0x4000), hamon::shl(hamon::uint16_t(0x1234), 12));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint16_t(0x8000), hamon::shl(hamon::uint16_t(0x1234), 13));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint16_t(0x0000), hamon::shl(hamon::uint16_t(0x1234), 14));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint16_t(0x0000), hamon::shl(hamon::uint16_t(0x1234), 15));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint16_t(0x0000), hamon::shl(hamon::uint16_t(0x1234), 16));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint32_t(0x00000001), hamon::shl(hamon::uint32_t(0x00000001),  0));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint32_t(0x00000002), hamon::shl(hamon::uint32_t(0x00000001),  1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint32_t(0x00000004), hamon::shl(hamon::uint32_t(0x00000001),  2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint32_t(0x00000008), hamon::shl(hamon::uint32_t(0x00000001),  3));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint32_t(0x00000010), hamon::shl(hamon::uint32_t(0x00000001),  4));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint32_t(0x00000020), hamon::shl(hamon::uint32_t(0x00000001),  5));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint32_t(0x00000040), hamon::shl(hamon::uint32_t(0x00000001),  6));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint32_t(0x00000080), hamon::shl(hamon::uint32_t(0x00000001),  7));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint32_t(0x00000100), hamon::shl(hamon::uint32_t(0x00000001),  8));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint32_t(0x00000200), hamon::shl(hamon::uint32_t(0x00000001),  9));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint32_t(0x00000400), hamon::shl(hamon::uint32_t(0x00000001), 10));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint32_t(0x00000800), hamon::shl(hamon::uint32_t(0x00000001), 11));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint32_t(0x00001000), hamon::shl(hamon::uint32_t(0x00000001), 12));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint32_t(0x00002000), hamon::shl(hamon::uint32_t(0x00000001), 13));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint32_t(0x00004000), hamon::shl(hamon::uint32_t(0x00000001), 14));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint32_t(0x00008000), hamon::shl(hamon::uint32_t(0x00000001), 15));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint32_t(0x00010000), hamon::shl(hamon::uint32_t(0x00000001), 16));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint32_t(0x00020000), hamon::shl(hamon::uint32_t(0x00000001), 17));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint32_t(0x00040000), hamon::shl(hamon::uint32_t(0x00000001), 18));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint32_t(0x00080000), hamon::shl(hamon::uint32_t(0x00000001), 19));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint32_t(0x00100000), hamon::shl(hamon::uint32_t(0x00000001), 20));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint32_t(0x00200000), hamon::shl(hamon::uint32_t(0x00000001), 21));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint32_t(0x00400000), hamon::shl(hamon::uint32_t(0x00000001), 22));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint32_t(0x00800000), hamon::shl(hamon::uint32_t(0x00000001), 23));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint32_t(0x01000000), hamon::shl(hamon::uint32_t(0x00000001), 24));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint32_t(0x02000000), hamon::shl(hamon::uint32_t(0x00000001), 25));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint32_t(0x04000000), hamon::shl(hamon::uint32_t(0x00000001), 26));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint32_t(0x08000000), hamon::shl(hamon::uint32_t(0x00000001), 27));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint32_t(0x10000000), hamon::shl(hamon::uint32_t(0x00000001), 28));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint32_t(0x20000000), hamon::shl(hamon::uint32_t(0x00000001), 29));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint32_t(0x40000000), hamon::shl(hamon::uint32_t(0x00000001), 30));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint32_t(0x80000000), hamon::shl(hamon::uint32_t(0x00000001), 31));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint32_t(0x00000000), hamon::shl(hamon::uint32_t(0x00000001), 32));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint32_t(0x12345678), hamon::shl(hamon::uint32_t(0x12345678),  0));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint32_t(0x2468ACF0), hamon::shl(hamon::uint32_t(0x12345678),  1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint32_t(0x48D159E0), hamon::shl(hamon::uint32_t(0x12345678),  2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint32_t(0x91A2B3C0), hamon::shl(hamon::uint32_t(0x12345678),  3));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint32_t(0x23456780), hamon::shl(hamon::uint32_t(0x12345678),  4));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint32_t(0x468ACF00), hamon::shl(hamon::uint32_t(0x12345678),  5));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint32_t(0x8D159E00), hamon::shl(hamon::uint32_t(0x12345678),  6));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint32_t(0x1A2B3C00), hamon::shl(hamon::uint32_t(0x12345678),  7));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint32_t(0x34567800), hamon::shl(hamon::uint32_t(0x12345678),  8));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint32_t(0x68ACF000), hamon::shl(hamon::uint32_t(0x12345678),  9));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint32_t(0xD159E000), hamon::shl(hamon::uint32_t(0x12345678), 10));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint32_t(0xA2B3C000), hamon::shl(hamon::uint32_t(0x12345678), 11));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint32_t(0x45678000), hamon::shl(hamon::uint32_t(0x12345678), 12));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint32_t(0x8ACF0000), hamon::shl(hamon::uint32_t(0x12345678), 13));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint32_t(0x159E0000), hamon::shl(hamon::uint32_t(0x12345678), 14));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint32_t(0x2B3C0000), hamon::shl(hamon::uint32_t(0x12345678), 15));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint32_t(0x56780000), hamon::shl(hamon::uint32_t(0x12345678), 16));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint32_t(0xACF00000), hamon::shl(hamon::uint32_t(0x12345678), 17));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint32_t(0x59E00000), hamon::shl(hamon::uint32_t(0x12345678), 18));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint32_t(0xB3C00000), hamon::shl(hamon::uint32_t(0x12345678), 19));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint32_t(0x67800000), hamon::shl(hamon::uint32_t(0x12345678), 20));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint32_t(0xCF000000), hamon::shl(hamon::uint32_t(0x12345678), 21));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint32_t(0x9E000000), hamon::shl(hamon::uint32_t(0x12345678), 22));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint32_t(0x3C000000), hamon::shl(hamon::uint32_t(0x12345678), 23));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint32_t(0x78000000), hamon::shl(hamon::uint32_t(0x12345678), 24));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint32_t(0xF0000000), hamon::shl(hamon::uint32_t(0x12345678), 25));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint32_t(0xE0000000), hamon::shl(hamon::uint32_t(0x12345678), 26));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint32_t(0xC0000000), hamon::shl(hamon::uint32_t(0x12345678), 27));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint32_t(0x80000000), hamon::shl(hamon::uint32_t(0x12345678), 28));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint32_t(0x00000000), hamon::shl(hamon::uint32_t(0x12345678), 29));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint32_t(0x00000000), hamon::shl(hamon::uint32_t(0x12345678), 30));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint32_t(0x00000000), hamon::shl(hamon::uint32_t(0x12345678), 31));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint32_t(0x00000000), hamon::shl(hamon::uint32_t(0x12345678), 32));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint32_t(0x00000000), hamon::shl(hamon::uint32_t(0x12345678), 33));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint32_t(0x00000000), hamon::shl(hamon::uint32_t(0x12345678), 64));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint32_t(0x00000000), hamon::shl(hamon::uint32_t(0x12345678), 65));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint32_t(0x00000000), hamon::shl(hamon::uint32_t(0x12345678), 96));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint32_t(0x00000000), hamon::shl(hamon::uint32_t(0x12345678), 97));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint64_t(0x0000000000000001), hamon::shl(hamon::uint64_t(0x0000000000000001),  0));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint64_t(0x0000000000000002), hamon::shl(hamon::uint64_t(0x0000000000000001),  1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint64_t(0x0000000000000004), hamon::shl(hamon::uint64_t(0x0000000000000001),  2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint64_t(0x0000000000000008), hamon::shl(hamon::uint64_t(0x0000000000000001),  3));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint64_t(0x0000000000000010), hamon::shl(hamon::uint64_t(0x0000000000000001),  4));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint64_t(0x0000000000000020), hamon::shl(hamon::uint64_t(0x0000000000000001),  5));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint64_t(0x0000000000000040), hamon::shl(hamon::uint64_t(0x0000000000000001),  6));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint64_t(0x0000000000000080), hamon::shl(hamon::uint64_t(0x0000000000000001),  7));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint64_t(0x0000000000000100), hamon::shl(hamon::uint64_t(0x0000000000000001),  8));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint64_t(0x0000000000000200), hamon::shl(hamon::uint64_t(0x0000000000000001),  9));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint64_t(0x0000000000000400), hamon::shl(hamon::uint64_t(0x0000000000000001), 10));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint64_t(0x0000000000000800), hamon::shl(hamon::uint64_t(0x0000000000000001), 11));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint64_t(0x0000000000001000), hamon::shl(hamon::uint64_t(0x0000000000000001), 12));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint64_t(0x0000000000002000), hamon::shl(hamon::uint64_t(0x0000000000000001), 13));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint64_t(0x0000000000004000), hamon::shl(hamon::uint64_t(0x0000000000000001), 14));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint64_t(0x0000000000008000), hamon::shl(hamon::uint64_t(0x0000000000000001), 15));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint64_t(0x0000000000010000), hamon::shl(hamon::uint64_t(0x0000000000000001), 16));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint64_t(0x0000000000020000), hamon::shl(hamon::uint64_t(0x0000000000000001), 17));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint64_t(0x0000000000040000), hamon::shl(hamon::uint64_t(0x0000000000000001), 18));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint64_t(0x0000000000080000), hamon::shl(hamon::uint64_t(0x0000000000000001), 19));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint64_t(0x0000000000100000), hamon::shl(hamon::uint64_t(0x0000000000000001), 20));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint64_t(0x0000000000200000), hamon::shl(hamon::uint64_t(0x0000000000000001), 21));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint64_t(0x0000000000400000), hamon::shl(hamon::uint64_t(0x0000000000000001), 22));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint64_t(0x0000000000800000), hamon::shl(hamon::uint64_t(0x0000000000000001), 23));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint64_t(0x0000000001000000), hamon::shl(hamon::uint64_t(0x0000000000000001), 24));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint64_t(0x0000000002000000), hamon::shl(hamon::uint64_t(0x0000000000000001), 25));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint64_t(0x0000000004000000), hamon::shl(hamon::uint64_t(0x0000000000000001), 26));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint64_t(0x0000000008000000), hamon::shl(hamon::uint64_t(0x0000000000000001), 27));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint64_t(0x0000000010000000), hamon::shl(hamon::uint64_t(0x0000000000000001), 28));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint64_t(0x0000000020000000), hamon::shl(hamon::uint64_t(0x0000000000000001), 29));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint64_t(0x0000000040000000), hamon::shl(hamon::uint64_t(0x0000000000000001), 30));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint64_t(0x0000000080000000), hamon::shl(hamon::uint64_t(0x0000000000000001), 31));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint64_t(0x0000000100000000), hamon::shl(hamon::uint64_t(0x0000000000000001), 32));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint64_t(0x0000000200000000), hamon::shl(hamon::uint64_t(0x0000000000000001), 33));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint64_t(0x0000000400000000), hamon::shl(hamon::uint64_t(0x0000000000000001), 34));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint64_t(0x0000000800000000), hamon::shl(hamon::uint64_t(0x0000000000000001), 35));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint64_t(0x0000001000000000), hamon::shl(hamon::uint64_t(0x0000000000000001), 36));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint64_t(0x0000002000000000), hamon::shl(hamon::uint64_t(0x0000000000000001), 37));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint64_t(0x0000004000000000), hamon::shl(hamon::uint64_t(0x0000000000000001), 38));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint64_t(0x0000008000000000), hamon::shl(hamon::uint64_t(0x0000000000000001), 39));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint64_t(0x0000010000000000), hamon::shl(hamon::uint64_t(0x0000000000000001), 40));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint64_t(0x0000020000000000), hamon::shl(hamon::uint64_t(0x0000000000000001), 41));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint64_t(0x0000040000000000), hamon::shl(hamon::uint64_t(0x0000000000000001), 42));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint64_t(0x0000080000000000), hamon::shl(hamon::uint64_t(0x0000000000000001), 43));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint64_t(0x0000100000000000), hamon::shl(hamon::uint64_t(0x0000000000000001), 44));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint64_t(0x0000200000000000), hamon::shl(hamon::uint64_t(0x0000000000000001), 45));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint64_t(0x0000400000000000), hamon::shl(hamon::uint64_t(0x0000000000000001), 46));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint64_t(0x0000800000000000), hamon::shl(hamon::uint64_t(0x0000000000000001), 47));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint64_t(0x0001000000000000), hamon::shl(hamon::uint64_t(0x0000000000000001), 48));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint64_t(0x0002000000000000), hamon::shl(hamon::uint64_t(0x0000000000000001), 49));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint64_t(0x0004000000000000), hamon::shl(hamon::uint64_t(0x0000000000000001), 50));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint64_t(0x0008000000000000), hamon::shl(hamon::uint64_t(0x0000000000000001), 51));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint64_t(0x0010000000000000), hamon::shl(hamon::uint64_t(0x0000000000000001), 52));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint64_t(0x0020000000000000), hamon::shl(hamon::uint64_t(0x0000000000000001), 53));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint64_t(0x0040000000000000), hamon::shl(hamon::uint64_t(0x0000000000000001), 54));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint64_t(0x0080000000000000), hamon::shl(hamon::uint64_t(0x0000000000000001), 55));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint64_t(0x0100000000000000), hamon::shl(hamon::uint64_t(0x0000000000000001), 56));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint64_t(0x0200000000000000), hamon::shl(hamon::uint64_t(0x0000000000000001), 57));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint64_t(0x0400000000000000), hamon::shl(hamon::uint64_t(0x0000000000000001), 58));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint64_t(0x0800000000000000), hamon::shl(hamon::uint64_t(0x0000000000000001), 59));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint64_t(0x1000000000000000), hamon::shl(hamon::uint64_t(0x0000000000000001), 60));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint64_t(0x2000000000000000), hamon::shl(hamon::uint64_t(0x0000000000000001), 61));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint64_t(0x4000000000000000), hamon::shl(hamon::uint64_t(0x0000000000000001), 62));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint64_t(0x8000000000000000), hamon::shl(hamon::uint64_t(0x0000000000000001), 63));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint64_t(0x0000000000000000), hamon::shl(hamon::uint64_t(0x0000000000000001), 64));
}
