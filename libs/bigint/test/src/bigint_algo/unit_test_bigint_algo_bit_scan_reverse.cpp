/**
 *	@file	unit_test_bigint_algo_bit_scan_reverse.cpp
 *
 *	@brief	bigint_algo::bit_scan_reverse のテスト
 */

#include <hamon/bigint/bigint_algo/bit_scan_reverse.hpp>
#include <hamon/array.hpp>
#include <hamon/cstddef.hpp>
#include <hamon/cstdint.hpp>
#include <hamon/inplace_vector.hpp>
#include <hamon/vector.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_bigint_test
{

namespace bigint_algo_bit_scan_reverse_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename VectorType>
inline HAMON_CXX14_CONSTEXPR bool
test(VectorType const& vec, hamon::size_t expected, bool found)
{
	hamon::size_t index{};
	bool f = hamon::bigint_algo::bit_scan_reverse(&index, vec);
	VERIFY(f == found)
	if (found)
	{
		VERIFY(index == expected);
	}
	return true;
}

#undef VERIFY

GTEST_TEST(BigIntAlgoTest, BitScanReverseTest)
{
	// array
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint8_t, 1>{0x00}, 0, false));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint8_t, 1>{0x01}, 0, true));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint8_t, 1>{0x02}, 1, true));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint8_t, 1>{0x03}, 1, true));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint8_t, 1>{0x04}, 2, true));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint8_t, 1>{0x0c}, 3, true));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint8_t, 1>{0x10}, 4, true));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint8_t, 1>{0x3f}, 5, true));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint8_t, 1>{0x40}, 6, true));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint8_t, 1>{0x80}, 7, true));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint8_t, 1>{0xff}, 7, true));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint8_t, 2>{0x00, 0x00},  0, false));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint8_t, 2>{0x01, 0x00},  0, true));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint8_t, 2>{0x10, 0x00},  4, true));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint8_t, 2>{0x80, 0x00},  7, true));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint8_t, 2>{0x00, 0x01},  8, true));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint8_t, 2>{0x00, 0x02},  9, true));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint8_t, 2>{0x00, 0x80}, 15, true));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint8_t, 2>{0xff, 0xff}, 15, true));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint16_t, 1>{0x0000},  0, false));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint16_t, 1>{0x0001},  0, true));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint16_t, 1>{0x0002},  1, true));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint16_t, 1>{0x0004},  2, true));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint16_t, 1>{0x0008},  3, true));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint16_t, 1>{0x0011},  4, true));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint16_t, 1>{0x0111},  8, true));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint16_t, 1>{0x1111}, 12, true));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint16_t, 1>{0x8111}, 15, true));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint16_t, 1>{0xffff}, 15, true));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint16_t, 2>{0x0000, 0x0000},  0, false));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint16_t, 2>{0x0001, 0x0000},  0, true));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint16_t, 2>{0x0010, 0x0000},  4, true));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint16_t, 2>{0x0100, 0x0000},  8, true));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint16_t, 2>{0x1000, 0x0000}, 12, true));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint16_t, 2>{0x0000, 0x0001}, 16, true));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint16_t, 2>{0x0000, 0x0010}, 20, true));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint16_t, 2>{0x0000, 0x0100}, 24, true));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint16_t, 2>{0x0000, 0x1000}, 28, true));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint32_t, 3>{0x00000000, 0x00000000, 0x00000000},  0, false));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint32_t, 3>{0x0000000f, 0x00000000, 0x00000000},  3, true));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint32_t, 3>{0x000000ff, 0x00000000, 0x00000000},  7, true));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint32_t, 3>{0x00000fff, 0x00000000, 0x00000000}, 11, true));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint32_t, 3>{0x0000ffff, 0x00000000, 0x00000000}, 15, true));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint32_t, 3>{0x000fffff, 0x00000000, 0x00000000}, 19, true));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint32_t, 3>{0x00ffffff, 0x00000000, 0x00000000}, 23, true));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint32_t, 3>{0x0fffffff, 0x00000000, 0x00000000}, 27, true));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint32_t, 3>{0xffffffff, 0x00000000, 0x00000000}, 31, true));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint32_t, 3>{0xffffffff, 0x0000000f, 0x00000000}, 35, true));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint32_t, 3>{0xffffffff, 0x000000ff, 0x00000000}, 39, true));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint32_t, 3>{0xffffffff, 0x00000fff, 0x00000000}, 43, true));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint32_t, 3>{0xffffffff, 0x0000ffff, 0x00000000}, 47, true));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint32_t, 3>{0xffffffff, 0x000fffff, 0x00000000}, 51, true));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint32_t, 3>{0xffffffff, 0x00ffffff, 0x00000000}, 55, true));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint32_t, 3>{0xffffffff, 0x0fffffff, 0x00000000}, 59, true));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint32_t, 3>{0xffffffff, 0xffffffff, 0x00000000}, 63, true));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint32_t, 3>{0xffffffff, 0xffffffff, 0x0000000f}, 67, true));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint32_t, 3>{0xffffffff, 0xffffffff, 0x000000ff}, 71, true));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint32_t, 3>{0xffffffff, 0xffffffff, 0x00000fff}, 75, true));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint32_t, 3>{0xffffffff, 0xffffffff, 0x0000ffff}, 79, true));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint32_t, 3>{0xffffffff, 0xffffffff, 0x000fffff}, 83, true));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint32_t, 3>{0xffffffff, 0xffffffff, 0x00ffffff}, 87, true));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint32_t, 3>{0xffffffff, 0xffffffff, 0x0fffffff}, 91, true));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint32_t, 3>{0xffffffff, 0xffffffff, 0xffffffff}, 95, true));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint64_t, 4>{0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000},   0, false));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint64_t, 4>{0x0000000000000001, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000},   0, true));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint64_t, 4>{0x8000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000},  63, true));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint64_t, 4>{0x0000000000000000, 0x0000000000000001, 0x0000000000000000, 0x0000000000000000},  64, true));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint64_t, 4>{0x0000000000000000, 0x8000000000000000, 0x0000000000000000, 0x0000000000000000}, 127, true));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint64_t, 4>{0x0000000000000000, 0x0000000000000000, 0x0000000000000001, 0x0000000000000000}, 128, true));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint64_t, 4>{0x0000000000000000, 0x0000000000000000, 0x8000000000000000, 0x0000000000000000}, 191, true));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint64_t, 4>{0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000001}, 192, true));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint64_t, 4>{0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x8000000000000000}, 255, true));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(hamon::array<hamon::uint64_t, 4>{0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff}, 255, true));

	// vector
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint8_t>{0x00}, 0, false));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint8_t>{0x01}, 0, true));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint8_t>{0x12}, 4, true));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint8_t>{0x23, 0x01}, 8, true));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint8_t>{0x34, 0x12}, 12, true));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint8_t>{0x00, 0x00, 0x01}, 16, true));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint8_t>{0x00, 0x00, 0x02}, 17, true));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint16_t>{0x0000},  0, false));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint16_t>{0x0001},  0, true));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint16_t>{0x0002},  1, true));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint16_t>{0x4000}, 14, true));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint16_t>{0x4000, 0x0001}, 16, true));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint16_t>{0x4000, 0x0001, 0x8000}, 47, true));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0x00000000},  0, false));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0x00000001},  0, true));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0x00000003},  1, true));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0x00000007},  2, true));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0x0000000f},  3, true));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0x0000001f},  4, true));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0x0000003f},  5, true));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0x0000007f},  6, true));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0x000000ff},  7, true));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0x000001ff},  8, true));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0x000003ff},  9, true));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0x000007ff}, 10, true));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0x00000fff}, 11, true));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0x00001fff}, 12, true));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0x00003fff}, 13, true));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0x00007fff}, 14, true));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0x0000ffff}, 15, true));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0x0001ffff}, 16, true));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0x0003ffff}, 17, true));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0x0007ffff}, 18, true));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0x000fffff}, 19, true));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0x001fffff}, 20, true));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0x003fffff}, 21, true));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0x007fffff}, 22, true));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0x00ffffff}, 23, true));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0x01ffffff}, 24, true));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0x03ffffff}, 25, true));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0x07ffffff}, 26, true));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0x0fffffff}, 27, true));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0x1fffffff}, 28, true));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0x3fffffff}, 29, true));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0x7fffffff}, 30, true));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0xffffffff}, 31, true));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0xffffffff, 0x00000001}, 32, true));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0xffffffff, 0x00000003}, 33, true));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0xffffffff, 0x00000007}, 34, true));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0xffffffff, 0x0000000f}, 35, true));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0xffffffff, 0x0000001f}, 36, true));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0xffffffff, 0x0000003f}, 37, true));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0xffffffff, 0x0000007f}, 38, true));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0xffffffff, 0x000000ff}, 39, true));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0xffffffff, 0x000001ff}, 40, true));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0xffffffff, 0x000003ff}, 41, true));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0xffffffff, 0x000007ff}, 42, true));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0xffffffff, 0x00000fff}, 43, true));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0xffffffff, 0x00001fff}, 44, true));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0xffffffff, 0x00003fff}, 45, true));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0xffffffff, 0x00007fff}, 46, true));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0xffffffff, 0x0000ffff}, 47, true));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0xffffffff, 0x0001ffff}, 48, true));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0xffffffff, 0x0003ffff}, 49, true));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0xffffffff, 0x0007ffff}, 50, true));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0xffffffff, 0x000fffff}, 51, true));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0xffffffff, 0x001fffff}, 52, true));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0xffffffff, 0x003fffff}, 53, true));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0xffffffff, 0x007fffff}, 54, true));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0xffffffff, 0x00ffffff}, 55, true));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0xffffffff, 0x01ffffff}, 56, true));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0xffffffff, 0x03ffffff}, 57, true));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0xffffffff, 0x07ffffff}, 58, true));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0xffffffff, 0x0fffffff}, 59, true));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0xffffffff, 0x1fffffff}, 60, true));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0xffffffff, 0x3fffffff}, 61, true));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0xffffffff, 0x7fffffff}, 62, true));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0xffffffff, 0xffffffff}, 63, true));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0xffffffff, 0xffffffff, 0x00000001}, 64, true));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0xffffffff, 0xffffffff, 0x00000003}, 65, true));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0xffffffff, 0xffffffff, 0x00000007}, 66, true));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0xffffffff, 0xffffffff, 0x0000000f}, 67, true));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0xffffffff, 0xffffffff, 0x0000001f}, 68, true));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0xffffffff, 0xffffffff, 0x0000003f}, 69, true));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0xffffffff, 0xffffffff, 0x0000007f}, 70, true));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0xffffffff, 0xffffffff, 0x000000ff}, 71, true));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0xffffffff, 0xffffffff, 0x000001ff}, 72, true));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0xffffffff, 0xffffffff, 0x000003ff}, 73, true));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0xffffffff, 0xffffffff, 0x000007ff}, 74, true));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0xffffffff, 0xffffffff, 0x00000fff}, 75, true));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0xffffffff, 0xffffffff, 0x00001fff}, 76, true));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0xffffffff, 0xffffffff, 0x00003fff}, 77, true));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0xffffffff, 0xffffffff, 0x00007fff}, 78, true));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0xffffffff, 0xffffffff, 0x0000ffff}, 79, true));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0xffffffff, 0xffffffff, 0x0001ffff}, 80, true));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0xffffffff, 0xffffffff, 0x0003ffff}, 81, true));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0xffffffff, 0xffffffff, 0x0007ffff}, 82, true));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0xffffffff, 0xffffffff, 0x000fffff}, 83, true));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0xffffffff, 0xffffffff, 0x001fffff}, 84, true));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0xffffffff, 0xffffffff, 0x003fffff}, 85, true));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0xffffffff, 0xffffffff, 0x007fffff}, 86, true));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0xffffffff, 0xffffffff, 0x00ffffff}, 87, true));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0xffffffff, 0xffffffff, 0x01ffffff}, 88, true));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0xffffffff, 0xffffffff, 0x03ffffff}, 89, true));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0xffffffff, 0xffffffff, 0x07ffffff}, 90, true));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0xffffffff, 0xffffffff, 0x0fffffff}, 91, true));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0xffffffff, 0xffffffff, 0x1fffffff}, 92, true));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0xffffffff, 0xffffffff, 0x3fffffff}, 93, true));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0xffffffff, 0xffffffff, 0x7fffffff}, 94, true));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint32_t>{0xffffffff, 0xffffffff, 0xffffffff}, 95, true));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint64_t>{0x0000000000000000},  0, false));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint64_t>{0x0000000000000001},  0, true));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint64_t>{0x0000000000000000, 0x0000000000000001},  64, true));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::vector<hamon::uint64_t>{0xffffffffffffffff, 0xffffffffffffffff}, 127, true));

	// inplace_vector
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::inplace_vector<hamon::uint8_t, 3>{0x00}, 0, false));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::inplace_vector<hamon::uint8_t, 3>{0x01}, 0, true));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::inplace_vector<hamon::uint8_t, 3>{0x12}, 4, true));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::inplace_vector<hamon::uint8_t, 3>{0x23, 0x01}, 8, true));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::inplace_vector<hamon::uint8_t, 3>{0x34, 0x12}, 12, true));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::inplace_vector<hamon::uint8_t, 3>{0x00, 0x00, 0x01}, 16, true));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::inplace_vector<hamon::uint8_t, 3>{0x00, 0x00, 0x02}, 17, true));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::inplace_vector<hamon::uint16_t, 4>{0x0000},  0, false));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::inplace_vector<hamon::uint16_t, 4>{0x0001},  0, true));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::inplace_vector<hamon::uint16_t, 4>{0x0002},  1, true));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::inplace_vector<hamon::uint16_t, 4>{0x4000}, 14, true));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::inplace_vector<hamon::uint16_t, 4>{0x4000, 0x0001}, 16, true));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::inplace_vector<hamon::uint16_t, 4>{0x4000, 0x0001, 0x8000}, 47, true));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::inplace_vector<hamon::uint32_t, 3>{0x00000000},  0, false));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::inplace_vector<hamon::uint32_t, 3>{0x00000001},  0, true));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::inplace_vector<hamon::uint32_t, 3>{0xffffffff, 0xffffffff, 0x00000001}, 64, true));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::inplace_vector<hamon::uint64_t, 2>{0x0000000000000000},  0, false));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::inplace_vector<hamon::uint64_t, 2>{0x0000000000000001},  0, true));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::inplace_vector<hamon::uint64_t, 2>{0x0000000000000000, 0x0000000000000001},  64, true));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(hamon::inplace_vector<hamon::uint64_t, 2>{0xffffffffffffffff, 0xffffffffffffffff}, 127, true));
}

}	// namespace bigint_algo_bit_scan_reverse_test

}	// namespace hamon_bigint_test
