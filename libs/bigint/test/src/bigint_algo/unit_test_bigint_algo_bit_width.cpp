/**
 *	@file	unit_test_bigint_algo_bit_width.cpp
 *
 *	@brief	bigint_algo::bit_width のテスト
 */

#include <hamon/bigint/bigint_algo/bit_width.hpp>
#include <hamon/array.hpp>
#include <hamon/cstddef.hpp>
#include <hamon/cstdint.hpp>
#include <hamon/inplace_vector.hpp>
#include <hamon/vector.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_bigint_test
{

namespace bigint_algo_bit_width_test
{

template <typename VectorType>
inline HAMON_CXX14_CONSTEXPR bool
test(VectorType const& vec, int expected)
{
	return hamon::bigint_algo::bit_width(vec) == expected;
}

GTEST_TEST(BigIntAlgoTest, BitWidthTest)
{
	// array
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint8_t, 1>{0x00}, 0));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint8_t, 1>{0x01}, 1));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint8_t, 1>{0x02}, 2));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint8_t, 1>{0x03}, 2));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint8_t, 1>{0x04}, 3));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint8_t, 1>{0x0c}, 4));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint8_t, 1>{0x10}, 5));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint8_t, 1>{0x3f}, 6));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint8_t, 1>{0x40}, 7));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint8_t, 1>{0x80}, 8));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint8_t, 1>{0xff}, 8));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint8_t, 2>{0x00, 0x00},  0));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint8_t, 2>{0x01, 0x00},  1));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint8_t, 2>{0x10, 0x00},  5));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint8_t, 2>{0x80, 0x00},  8));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint8_t, 2>{0x00, 0x01},  9));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint8_t, 2>{0x00, 0x02}, 10));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint8_t, 2>{0x00, 0x80}, 16));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint8_t, 2>{0xff, 0xff}, 16));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint16_t, 1>{0x0000},  0));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint16_t, 1>{0x0001},  1));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint16_t, 1>{0x0002},  2));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint16_t, 1>{0x0004},  3));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint16_t, 1>{0x0008},  4));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint16_t, 1>{0x0011},  5));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint16_t, 1>{0x0111},  9));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint16_t, 1>{0x1111}, 13));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint16_t, 1>{0x8111}, 16));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint16_t, 1>{0xffff}, 16));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint16_t, 2>{0x0000, 0x0000},  0));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint16_t, 2>{0x0001, 0x0000},  1));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint16_t, 2>{0x0010, 0x0000},  5));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint16_t, 2>{0x0100, 0x0000},  9));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint16_t, 2>{0x1000, 0x0000}, 13));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint16_t, 2>{0x0000, 0x0001}, 17));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint16_t, 2>{0x0000, 0x0010}, 21));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint16_t, 2>{0x0000, 0x0100}, 25));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint16_t, 2>{0x0000, 0x1000}, 29));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint32_t, 3>{0x00000000, 0x00000000, 0x00000000},  0));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint32_t, 3>{0x0000000f, 0x00000000, 0x00000000},  4));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint32_t, 3>{0x000000ff, 0x00000000, 0x00000000},  8));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint32_t, 3>{0x00000fff, 0x00000000, 0x00000000}, 12));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint32_t, 3>{0x0000ffff, 0x00000000, 0x00000000}, 16));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint32_t, 3>{0x000fffff, 0x00000000, 0x00000000}, 20));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint32_t, 3>{0x00ffffff, 0x00000000, 0x00000000}, 24));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint32_t, 3>{0x0fffffff, 0x00000000, 0x00000000}, 28));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint32_t, 3>{0xffffffff, 0x00000000, 0x00000000}, 32));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint32_t, 3>{0xffffffff, 0x0000000f, 0x00000000}, 36));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint32_t, 3>{0xffffffff, 0x000000ff, 0x00000000}, 40));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint32_t, 3>{0xffffffff, 0x00000fff, 0x00000000}, 44));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint32_t, 3>{0xffffffff, 0x0000ffff, 0x00000000}, 48));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint32_t, 3>{0xffffffff, 0x000fffff, 0x00000000}, 52));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint32_t, 3>{0xffffffff, 0x00ffffff, 0x00000000}, 56));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint32_t, 3>{0xffffffff, 0x0fffffff, 0x00000000}, 60));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint32_t, 3>{0xffffffff, 0xffffffff, 0x00000000}, 64));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint32_t, 3>{0xffffffff, 0xffffffff, 0x0000000f}, 68));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint32_t, 3>{0xffffffff, 0xffffffff, 0x000000ff}, 72));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint32_t, 3>{0xffffffff, 0xffffffff, 0x00000fff}, 76));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint32_t, 3>{0xffffffff, 0xffffffff, 0x0000ffff}, 80));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint32_t, 3>{0xffffffff, 0xffffffff, 0x000fffff}, 84));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint32_t, 3>{0xffffffff, 0xffffffff, 0x00ffffff}, 88));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint32_t, 3>{0xffffffff, 0xffffffff, 0x0fffffff}, 92));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint32_t, 3>{0xffffffff, 0xffffffff, 0xffffffff}, 96));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint64_t, 4>{0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000},   0));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint64_t, 4>{0x0000000000000001, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000},   1));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint64_t, 4>{0x8000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000},  64));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint64_t, 4>{0x0000000000000000, 0x0000000000000001, 0x0000000000000000, 0x0000000000000000},  65));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint64_t, 4>{0x0000000000000000, 0x8000000000000000, 0x0000000000000000, 0x0000000000000000}, 128));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint64_t, 4>{0x0000000000000000, 0x0000000000000000, 0x0000000000000001, 0x0000000000000000}, 129));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint64_t, 4>{0x0000000000000000, 0x0000000000000000, 0x8000000000000000, 0x0000000000000000}, 192));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint64_t, 4>{0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000001}, 193));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint64_t, 4>{0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x8000000000000000}, 256));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint64_t, 4>{0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff}, 256));

	// vector
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint8_t>{0x00}, 0));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint8_t>{0x01}, 1));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint8_t>{0x12}, 5));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint8_t>{0x23, 0x01}, 9));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint8_t>{0x34, 0x12}, 13));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint8_t>{0x00, 0x00, 0x01}, 17));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint8_t>{0x00, 0x00, 0x02}, 18));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint16_t>{0x0000},  0));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint16_t>{0x0001},  1));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint16_t>{0x0002},  2));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint16_t>{0x4000}, 15));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint16_t>{0x4000, 0x0001}, 17));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint16_t>{0x4000, 0x0001, 0x8000}, 48));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0x00000000},  0));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0x00000001},  1));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0x00000003},  2));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0x00000007},  3));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0x0000000f},  4));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0x0000001f},  5));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0x0000003f},  6));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0x0000007f},  7));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0x000000ff},  8));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0x000001ff},  9));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0x000003ff}, 10));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0x000007ff}, 11));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0x00000fff}, 12));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0x00001fff}, 13));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0x00003fff}, 14));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0x00007fff}, 15));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0x0000ffff}, 16));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0x0001ffff}, 17));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0x0003ffff}, 18));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0x0007ffff}, 19));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0x000fffff}, 20));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0x001fffff}, 21));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0x003fffff}, 22));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0x007fffff}, 23));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0x00ffffff}, 24));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0x01ffffff}, 25));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0x03ffffff}, 26));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0x07ffffff}, 27));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0x0fffffff}, 28));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0x1fffffff}, 29));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0x3fffffff}, 30));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0x7fffffff}, 31));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0xffffffff}, 32));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0xffffffff, 0x00000001}, 33));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0xffffffff, 0x00000003}, 34));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0xffffffff, 0x00000007}, 35));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0xffffffff, 0x0000000f}, 36));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0xffffffff, 0x0000001f}, 37));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0xffffffff, 0x0000003f}, 38));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0xffffffff, 0x0000007f}, 39));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0xffffffff, 0x000000ff}, 40));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0xffffffff, 0x000001ff}, 41));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0xffffffff, 0x000003ff}, 42));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0xffffffff, 0x000007ff}, 43));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0xffffffff, 0x00000fff}, 44));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0xffffffff, 0x00001fff}, 45));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0xffffffff, 0x00003fff}, 46));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0xffffffff, 0x00007fff}, 47));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0xffffffff, 0x0000ffff}, 48));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0xffffffff, 0x0001ffff}, 49));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0xffffffff, 0x0003ffff}, 50));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0xffffffff, 0x0007ffff}, 51));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0xffffffff, 0x000fffff}, 52));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0xffffffff, 0x001fffff}, 53));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0xffffffff, 0x003fffff}, 54));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0xffffffff, 0x007fffff}, 55));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0xffffffff, 0x00ffffff}, 56));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0xffffffff, 0x01ffffff}, 57));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0xffffffff, 0x03ffffff}, 58));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0xffffffff, 0x07ffffff}, 59));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0xffffffff, 0x0fffffff}, 60));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0xffffffff, 0x1fffffff}, 61));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0xffffffff, 0x3fffffff}, 62));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0xffffffff, 0x7fffffff}, 63));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0xffffffff, 0xffffffff}, 64));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0xffffffff, 0xffffffff, 0x00000001}, 65));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0xffffffff, 0xffffffff, 0x00000003}, 66));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0xffffffff, 0xffffffff, 0x00000007}, 67));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0xffffffff, 0xffffffff, 0x0000000f}, 68));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0xffffffff, 0xffffffff, 0x0000001f}, 69));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0xffffffff, 0xffffffff, 0x0000003f}, 70));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0xffffffff, 0xffffffff, 0x0000007f}, 71));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0xffffffff, 0xffffffff, 0x000000ff}, 72));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0xffffffff, 0xffffffff, 0x000001ff}, 73));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0xffffffff, 0xffffffff, 0x000003ff}, 74));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0xffffffff, 0xffffffff, 0x000007ff}, 75));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0xffffffff, 0xffffffff, 0x00000fff}, 76));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0xffffffff, 0xffffffff, 0x00001fff}, 77));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0xffffffff, 0xffffffff, 0x00003fff}, 78));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0xffffffff, 0xffffffff, 0x00007fff}, 79));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0xffffffff, 0xffffffff, 0x0000ffff}, 80));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0xffffffff, 0xffffffff, 0x0001ffff}, 81));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0xffffffff, 0xffffffff, 0x0003ffff}, 82));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0xffffffff, 0xffffffff, 0x0007ffff}, 83));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0xffffffff, 0xffffffff, 0x000fffff}, 84));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0xffffffff, 0xffffffff, 0x001fffff}, 85));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0xffffffff, 0xffffffff, 0x003fffff}, 86));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0xffffffff, 0xffffffff, 0x007fffff}, 87));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0xffffffff, 0xffffffff, 0x00ffffff}, 88));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0xffffffff, 0xffffffff, 0x01ffffff}, 89));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0xffffffff, 0xffffffff, 0x03ffffff}, 90));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0xffffffff, 0xffffffff, 0x07ffffff}, 91));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0xffffffff, 0xffffffff, 0x0fffffff}, 92));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0xffffffff, 0xffffffff, 0x1fffffff}, 93));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0xffffffff, 0xffffffff, 0x3fffffff}, 94));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0xffffffff, 0xffffffff, 0x7fffffff}, 95));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0xffffffff, 0xffffffff, 0xffffffff}, 96));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint64_t>{0x0000000000000000},  0));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint64_t>{0x0000000000000001},  1));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint64_t>{0x0000000000000000, 0x0000000000000001},  65));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint64_t>{0xffffffffffffffff, 0xffffffffffffffff}, 128));

	// inplace_vector
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::inplace_vector<hamon::uint8_t, 3>{0x00}, 0));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::inplace_vector<hamon::uint8_t, 3>{0x01}, 1));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::inplace_vector<hamon::uint8_t, 3>{0x12}, 5));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::inplace_vector<hamon::uint8_t, 3>{0x23, 0x01}, 9));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::inplace_vector<hamon::uint8_t, 3>{0x34, 0x12}, 13));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::inplace_vector<hamon::uint8_t, 3>{0x00, 0x00, 0x01}, 17));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::inplace_vector<hamon::uint8_t, 3>{0x00, 0x00, 0x02}, 18));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::inplace_vector<hamon::uint16_t, 4>{0x0000},  0));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::inplace_vector<hamon::uint16_t, 4>{0x0001},  1));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::inplace_vector<hamon::uint16_t, 4>{0x0002},  2));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::inplace_vector<hamon::uint16_t, 4>{0x4000}, 15));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::inplace_vector<hamon::uint16_t, 4>{0x4000, 0x0001}, 17));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::inplace_vector<hamon::uint16_t, 4>{0x4000, 0x0001, 0x8000}, 48));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::inplace_vector<hamon::uint32_t, 3>{0x00000000},  0));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::inplace_vector<hamon::uint32_t, 3>{0x00000001},  1));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::inplace_vector<hamon::uint32_t, 3>{0xffffffff, 0xffffffff, 0x00000001}, 65));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::inplace_vector<hamon::uint64_t, 2>{0x0000000000000000},  0));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::inplace_vector<hamon::uint64_t, 2>{0x0000000000000001},  1));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::inplace_vector<hamon::uint64_t, 2>{0x0000000000000000, 0x0000000000000001},  65));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::inplace_vector<hamon::uint64_t, 2>{0xffffffffffffffff, 0xffffffffffffffff}, 128));
}

}	// namespace bigint_algo_bit_width_test

}	// namespace hamon_bigint_test
