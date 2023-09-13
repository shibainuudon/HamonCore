/**
 *	@file	unit_test_bigint_algo_bit_shift_right.cpp
 *
 *	@brief	bigint_algo::bit_shift_right のテスト
 */

#include <hamon/bigint/bigint_algo/bit_shift_right.hpp>
#include <hamon/array.hpp>
#include <hamon/cstdint.hpp>
#include <hamon/vector.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_bigint_test
{

namespace bigint_algo_bit_shift_right_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename VectorType>
inline HAMON_CXX14_CONSTEXPR bool
BitShiftRightTest(VectorType a, hamon::uintmax_t b, VectorType const& expected)
{
	hamon::bigint_algo::bit_shift_right(a, b);
	VERIFY(a == expected);
	return true;
}

#undef VERIFY

GTEST_TEST(BigIntAlgoTest, BitShiftRightTest)
{
#if 0
	for (hamon::size_t j = 0; j < 100000; ++j)
	{
		{
			hamon::vector<hamon::uint8_t> a{0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC, 0xDE, 0xF0};
			for (hamon::size_t i = 0; i < 64; ++i)
			{
				hamon::bigint_algo::bit_shift_right(a, i);
			}
		}
		{
			hamon::array<hamon::uint8_t, 8> a{0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC, 0xDE, 0xF0};
			for (hamon::size_t i = 0; i < 64; ++i)
			{
				hamon::bigint_algo::bit_shift_right(a, i);
			}
		}
	}
#endif

	{
		hamon::vector<hamon::uint8_t> const a{0};
		EXPECT_TRUE(BitShiftRightTest(a, 0, hamon::vector<hamon::uint8_t>{0}));
		EXPECT_TRUE(BitShiftRightTest(a, 1, hamon::vector<hamon::uint8_t>{0}));
		EXPECT_TRUE(BitShiftRightTest(a, 2, hamon::vector<hamon::uint8_t>{0}));
		EXPECT_TRUE(BitShiftRightTest(a, 100, hamon::vector<hamon::uint8_t>{0}));
	}
	{
		hamon::vector<hamon::uint8_t> const a{0x00, 0x80};
		EXPECT_TRUE(BitShiftRightTest(a,  0, hamon::vector<hamon::uint8_t>{0x00, 0x80}));
		EXPECT_TRUE(BitShiftRightTest(a,  1, hamon::vector<hamon::uint8_t>{0x00, 0x40}));
		EXPECT_TRUE(BitShiftRightTest(a,  2, hamon::vector<hamon::uint8_t>{0x00, 0x20}));
		EXPECT_TRUE(BitShiftRightTest(a,  3, hamon::vector<hamon::uint8_t>{0x00, 0x10}));
		EXPECT_TRUE(BitShiftRightTest(a,  4, hamon::vector<hamon::uint8_t>{0x00, 0x08}));
		EXPECT_TRUE(BitShiftRightTest(a,  5, hamon::vector<hamon::uint8_t>{0x00, 0x04}));
		EXPECT_TRUE(BitShiftRightTest(a,  6, hamon::vector<hamon::uint8_t>{0x00, 0x02}));
		EXPECT_TRUE(BitShiftRightTest(a,  7, hamon::vector<hamon::uint8_t>{0x00, 0x01}));
		EXPECT_TRUE(BitShiftRightTest(a,  8, hamon::vector<hamon::uint8_t>{0x80}));
		EXPECT_TRUE(BitShiftRightTest(a,  9, hamon::vector<hamon::uint8_t>{0x40}));
		EXPECT_TRUE(BitShiftRightTest(a, 10, hamon::vector<hamon::uint8_t>{0x20}));
		EXPECT_TRUE(BitShiftRightTest(a, 11, hamon::vector<hamon::uint8_t>{0x10}));
		EXPECT_TRUE(BitShiftRightTest(a, 12, hamon::vector<hamon::uint8_t>{0x08}));
		EXPECT_TRUE(BitShiftRightTest(a, 13, hamon::vector<hamon::uint8_t>{0x04}));
		EXPECT_TRUE(BitShiftRightTest(a, 14, hamon::vector<hamon::uint8_t>{0x02}));
		EXPECT_TRUE(BitShiftRightTest(a, 15, hamon::vector<hamon::uint8_t>{0x01}));
		EXPECT_TRUE(BitShiftRightTest(a, 16, hamon::vector<hamon::uint8_t>{0x00}));
		EXPECT_TRUE(BitShiftRightTest(a, 17, hamon::vector<hamon::uint8_t>{0x00}));
	}
	{
		hamon::vector<hamon::uint16_t> const a{0x9ABC, 0x5678, 0x1234};
		EXPECT_TRUE(BitShiftRightTest(a,  1, hamon::vector<hamon::uint16_t>{0x4D5E, 0x2B3C, 0x091A}));
		EXPECT_TRUE(BitShiftRightTest(a,  2, hamon::vector<hamon::uint16_t>{0x26AF, 0x159E, 0x048D}));
		EXPECT_TRUE(BitShiftRightTest(a,  3, hamon::vector<hamon::uint16_t>{0x1357, 0x8ACF, 0x0246}));
		EXPECT_TRUE(BitShiftRightTest(a,  4, hamon::vector<hamon::uint16_t>{0x89AB, 0x4567, 0x0123}));
		EXPECT_TRUE(BitShiftRightTest(a,  5, hamon::vector<hamon::uint16_t>{0xC4D5, 0xA2B3, 0x0091}));
		EXPECT_TRUE(BitShiftRightTest(a,  6, hamon::vector<hamon::uint16_t>{0xE26A, 0xD159, 0x0048}));
		EXPECT_TRUE(BitShiftRightTest(a,  7, hamon::vector<hamon::uint16_t>{0xF135, 0x68AC, 0x0024}));
		EXPECT_TRUE(BitShiftRightTest(a,  8, hamon::vector<hamon::uint16_t>{0x789A, 0x3456, 0x0012}));
		EXPECT_TRUE(BitShiftRightTest(a,  9, hamon::vector<hamon::uint16_t>{0x3C4D, 0x1A2B, 0x0009}));
		EXPECT_TRUE(BitShiftRightTest(a, 10, hamon::vector<hamon::uint16_t>{0x9E26, 0x8D15, 0x0004}));
		EXPECT_TRUE(BitShiftRightTest(a, 11, hamon::vector<hamon::uint16_t>{0xCF13, 0x468A, 0x0002}));
		EXPECT_TRUE(BitShiftRightTest(a, 12, hamon::vector<hamon::uint16_t>{0x6789, 0x2345, 0x0001}));
		EXPECT_TRUE(BitShiftRightTest(a, 13, hamon::vector<hamon::uint16_t>{0xB3C4, 0x91A2}));
		EXPECT_TRUE(BitShiftRightTest(a, 14, hamon::vector<hamon::uint16_t>{0x59E2, 0x48D1}));
		EXPECT_TRUE(BitShiftRightTest(a, 15, hamon::vector<hamon::uint16_t>{0xACF1, 0x2468}));
		EXPECT_TRUE(BitShiftRightTest(a, 16, hamon::vector<hamon::uint16_t>{0x5678, 0x1234}));
		EXPECT_TRUE(BitShiftRightTest(a, 17, hamon::vector<hamon::uint16_t>{0x2B3C, 0x091A}));
		EXPECT_TRUE(BitShiftRightTest(a, 18, hamon::vector<hamon::uint16_t>{0x159E, 0x048D}));
		EXPECT_TRUE(BitShiftRightTest(a, 19, hamon::vector<hamon::uint16_t>{0x8ACF, 0x0246}));
		EXPECT_TRUE(BitShiftRightTest(a, 20, hamon::vector<hamon::uint16_t>{0x4567, 0x0123}));
		EXPECT_TRUE(BitShiftRightTest(a, 21, hamon::vector<hamon::uint16_t>{0xA2B3, 0x0091}));
		EXPECT_TRUE(BitShiftRightTest(a, 22, hamon::vector<hamon::uint16_t>{0xD159, 0x0048}));
		EXPECT_TRUE(BitShiftRightTest(a, 23, hamon::vector<hamon::uint16_t>{0x68AC, 0x0024}));
		EXPECT_TRUE(BitShiftRightTest(a, 24, hamon::vector<hamon::uint16_t>{0x3456, 0x0012}));
		EXPECT_TRUE(BitShiftRightTest(a, 25, hamon::vector<hamon::uint16_t>{0x1A2B, 0x0009}));
		EXPECT_TRUE(BitShiftRightTest(a, 26, hamon::vector<hamon::uint16_t>{0x8D15, 0x0004}));
		EXPECT_TRUE(BitShiftRightTest(a, 27, hamon::vector<hamon::uint16_t>{0x468A, 0x0002}));
		EXPECT_TRUE(BitShiftRightTest(a, 28, hamon::vector<hamon::uint16_t>{0x2345, 0x0001}));
		EXPECT_TRUE(BitShiftRightTest(a, 29, hamon::vector<hamon::uint16_t>{0x91A2}));
		EXPECT_TRUE(BitShiftRightTest(a, 30, hamon::vector<hamon::uint16_t>{0x48D1}));
		EXPECT_TRUE(BitShiftRightTest(a, 31, hamon::vector<hamon::uint16_t>{0x2468}));
		EXPECT_TRUE(BitShiftRightTest(a, 32, hamon::vector<hamon::uint16_t>{0x1234}));
		EXPECT_TRUE(BitShiftRightTest(a, 33, hamon::vector<hamon::uint16_t>{0x091A}));
		EXPECT_TRUE(BitShiftRightTest(a, 34, hamon::vector<hamon::uint16_t>{0x048D}));
		EXPECT_TRUE(BitShiftRightTest(a, 35, hamon::vector<hamon::uint16_t>{0x0246}));
		EXPECT_TRUE(BitShiftRightTest(a, 36, hamon::vector<hamon::uint16_t>{0x0123}));
		EXPECT_TRUE(BitShiftRightTest(a, 37, hamon::vector<hamon::uint16_t>{0x0091}));
		EXPECT_TRUE(BitShiftRightTest(a, 38, hamon::vector<hamon::uint16_t>{0x0048}));
		EXPECT_TRUE(BitShiftRightTest(a, 39, hamon::vector<hamon::uint16_t>{0x0024}));
		EXPECT_TRUE(BitShiftRightTest(a, 40, hamon::vector<hamon::uint16_t>{0x0012}));
		EXPECT_TRUE(BitShiftRightTest(a, 41, hamon::vector<hamon::uint16_t>{0x0009}));
		EXPECT_TRUE(BitShiftRightTest(a, 42, hamon::vector<hamon::uint16_t>{0x0004}));
		EXPECT_TRUE(BitShiftRightTest(a, 43, hamon::vector<hamon::uint16_t>{0x0002}));
		EXPECT_TRUE(BitShiftRightTest(a, 44, hamon::vector<hamon::uint16_t>{0x0001}));
		EXPECT_TRUE(BitShiftRightTest(a, 45, hamon::vector<hamon::uint16_t>{0x0000}));
		EXPECT_TRUE(BitShiftRightTest(a, 200, hamon::vector<hamon::uint16_t>{0x0000}));
	}
	{
		hamon::vector<hamon::uint32_t> const a{0x00000000, 0x00000000, 0x00000000, 0xFFFFFFFF};
		EXPECT_TRUE(BitShiftRightTest(a,   0, hamon::vector<hamon::uint32_t>{0x00000000, 0x00000000, 0x00000000, 0xFFFFFFFF}));
		EXPECT_TRUE(BitShiftRightTest(a,   1, hamon::vector<hamon::uint32_t>{0x00000000, 0x00000000, 0x80000000, 0x7FFFFFFF}));
		EXPECT_TRUE(BitShiftRightTest(a,   2, hamon::vector<hamon::uint32_t>{0x00000000, 0x00000000, 0xC0000000, 0x3FFFFFFF}));
		EXPECT_TRUE(BitShiftRightTest(a,   3, hamon::vector<hamon::uint32_t>{0x00000000, 0x00000000, 0xE0000000, 0x1FFFFFFF}));
		EXPECT_TRUE(BitShiftRightTest(a,   4, hamon::vector<hamon::uint32_t>{0x00000000, 0x00000000, 0xF0000000, 0x0FFFFFFF}));
		EXPECT_TRUE(BitShiftRightTest(a,  31, hamon::vector<hamon::uint32_t>{0x00000000, 0x00000000, 0xFFFFFFFE, 0x00000001}));
		EXPECT_TRUE(BitShiftRightTest(a,  32, hamon::vector<hamon::uint32_t>{0x00000000, 0x00000000, 0xFFFFFFFF}));
		EXPECT_TRUE(BitShiftRightTest(a,  33, hamon::vector<hamon::uint32_t>{0x00000000, 0x80000000, 0x7FFFFFFF}));
		EXPECT_TRUE(BitShiftRightTest(a,  63, hamon::vector<hamon::uint32_t>{0x00000000, 0xFFFFFFFE, 0x00000001}));
		EXPECT_TRUE(BitShiftRightTest(a,  64, hamon::vector<hamon::uint32_t>{0x00000000, 0xFFFFFFFF}));
		EXPECT_TRUE(BitShiftRightTest(a,  65, hamon::vector<hamon::uint32_t>{0x80000000, 0x7FFFFFFF}));
		EXPECT_TRUE(BitShiftRightTest(a,  95, hamon::vector<hamon::uint32_t>{0xFFFFFFFE, 0x00000001}));
		EXPECT_TRUE(BitShiftRightTest(a,  96, hamon::vector<hamon::uint32_t>{0xFFFFFFFF}));
		EXPECT_TRUE(BitShiftRightTest(a,  97, hamon::vector<hamon::uint32_t>{0x7FFFFFFF}));
		EXPECT_TRUE(BitShiftRightTest(a, 127, hamon::vector<hamon::uint32_t>{0x00000001}));
		EXPECT_TRUE(BitShiftRightTest(a, 128, hamon::vector<hamon::uint32_t>{0x00000000}));
		EXPECT_TRUE(BitShiftRightTest(a, 129, hamon::vector<hamon::uint32_t>{0x00000000}));
	}
	{
		hamon::vector<hamon::uint64_t> const a{0x1020304050607080, 0xF00000000000000F, 0x8000000000000000};
		EXPECT_TRUE(BitShiftRightTest(a,   0, hamon::vector<hamon::uint64_t>{0x1020304050607080, 0xF00000000000000F, 0x8000000000000000}));
		EXPECT_TRUE(BitShiftRightTest(a,   1, hamon::vector<hamon::uint64_t>{0x8810182028303840, 0x7800000000000007, 0x4000000000000000}));
		EXPECT_TRUE(BitShiftRightTest(a,   2, hamon::vector<hamon::uint64_t>{0xC4080C1014181C20, 0x3C00000000000003, 0x2000000000000000}));
		EXPECT_TRUE(BitShiftRightTest(a,  63, hamon::vector<hamon::uint64_t>{0xE00000000000001E, 0x0000000000000001, 0x0000000000000001}));
		EXPECT_TRUE(BitShiftRightTest(a,  64, hamon::vector<hamon::uint64_t>{0xF00000000000000F, 0x8000000000000000}));
		EXPECT_TRUE(BitShiftRightTest(a,  65, hamon::vector<hamon::uint64_t>{0x7800000000000007, 0x4000000000000000}));
		EXPECT_TRUE(BitShiftRightTest(a, 127, hamon::vector<hamon::uint64_t>{0x0000000000000001, 0x0000000000000001}));
		EXPECT_TRUE(BitShiftRightTest(a, 128, hamon::vector<hamon::uint64_t>{0x8000000000000000}));
		EXPECT_TRUE(BitShiftRightTest(a, 129, hamon::vector<hamon::uint64_t>{0x4000000000000000}));
		EXPECT_TRUE(BitShiftRightTest(a, 191, hamon::vector<hamon::uint64_t>{0x0000000000000001}));
		EXPECT_TRUE(BitShiftRightTest(a, 192, hamon::vector<hamon::uint64_t>{0x0000000000000000}));
	}
	{
		HAMON_CXX14_CONSTEXPR hamon::array<hamon::uint8_t, 3> const a{0x00, 0xFF, 0x7F};
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(BitShiftRightTest(a,  0, hamon::array<hamon::uint8_t, 3>{0x00, 0xFF, 0x7F}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(BitShiftRightTest(a,  1, hamon::array<hamon::uint8_t, 3>{0x80, 0xFF, 0x3F}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(BitShiftRightTest(a,  2, hamon::array<hamon::uint8_t, 3>{0xC0, 0xFF, 0x1F}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(BitShiftRightTest(a,  3, hamon::array<hamon::uint8_t, 3>{0xE0, 0xFF, 0x0F}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(BitShiftRightTest(a,  4, hamon::array<hamon::uint8_t, 3>{0xF0, 0xFF, 0x07}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(BitShiftRightTest(a,  5, hamon::array<hamon::uint8_t, 3>{0xF8, 0xFF, 0x03}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(BitShiftRightTest(a,  6, hamon::array<hamon::uint8_t, 3>{0xFC, 0xFF, 0x01}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(BitShiftRightTest(a,  7, hamon::array<hamon::uint8_t, 3>{0xFE, 0xFF, 0x00}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(BitShiftRightTest(a,  8, hamon::array<hamon::uint8_t, 3>{0xFF, 0x7F, 0x00}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(BitShiftRightTest(a,  9, hamon::array<hamon::uint8_t, 3>{0xFF, 0x3F, 0x00}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(BitShiftRightTest(a, 10, hamon::array<hamon::uint8_t, 3>{0xFF, 0x1F, 0x00}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(BitShiftRightTest(a, 11, hamon::array<hamon::uint8_t, 3>{0xFF, 0x0F, 0x00}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(BitShiftRightTest(a, 12, hamon::array<hamon::uint8_t, 3>{0xFF, 0x07, 0x00}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(BitShiftRightTest(a, 13, hamon::array<hamon::uint8_t, 3>{0xFF, 0x03, 0x00}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(BitShiftRightTest(a, 14, hamon::array<hamon::uint8_t, 3>{0xFF, 0x01, 0x00}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(BitShiftRightTest(a, 15, hamon::array<hamon::uint8_t, 3>{0xFF, 0x00, 0x00}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(BitShiftRightTest(a, 16, hamon::array<hamon::uint8_t, 3>{0x7F, 0x00, 0x00}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(BitShiftRightTest(a, 17, hamon::array<hamon::uint8_t, 3>{0x3F, 0x00, 0x00}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(BitShiftRightTest(a, 18, hamon::array<hamon::uint8_t, 3>{0x1F, 0x00, 0x00}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(BitShiftRightTest(a, 19, hamon::array<hamon::uint8_t, 3>{0x0F, 0x00, 0x00}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(BitShiftRightTest(a, 20, hamon::array<hamon::uint8_t, 3>{0x07, 0x00, 0x00}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(BitShiftRightTest(a, 21, hamon::array<hamon::uint8_t, 3>{0x03, 0x00, 0x00}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(BitShiftRightTest(a, 22, hamon::array<hamon::uint8_t, 3>{0x01, 0x00, 0x00}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(BitShiftRightTest(a, 23, hamon::array<hamon::uint8_t, 3>{0x00, 0x00, 0x00}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(BitShiftRightTest(a, 24, hamon::array<hamon::uint8_t, 3>{0x00, 0x00, 0x00}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(BitShiftRightTest(a, 48, hamon::array<hamon::uint8_t, 3>{0x00, 0x00, 0x00}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(BitShiftRightTest(a, 99, hamon::array<hamon::uint8_t, 3>{0x00, 0x00, 0x00}));
	}
	{
		HAMON_CXX14_CONSTEXPR hamon::array<hamon::uint16_t, 4> const a{0x1234, 0x5678, 0x9ABC, 0xDEF0};
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(BitShiftRightTest(a,  0, hamon::array<hamon::uint16_t, 4>{0x1234, 0x5678, 0x9ABC, 0xDEF0}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(BitShiftRightTest(a,  1, hamon::array<hamon::uint16_t, 4>{0x091A, 0x2B3C, 0x4D5E, 0x6F78}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(BitShiftRightTest(a,  2, hamon::array<hamon::uint16_t, 4>{0x048D, 0x159E, 0x26AF, 0x37BC}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(BitShiftRightTest(a, 15, hamon::array<hamon::uint16_t, 4>{0xACF0, 0x3578, 0xBDE1, 0x0001}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(BitShiftRightTest(a, 16, hamon::array<hamon::uint16_t, 4>{0x5678, 0x9ABC, 0xDEF0, 0x0000}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(BitShiftRightTest(a, 17, hamon::array<hamon::uint16_t, 4>{0x2B3C, 0x4D5E, 0x6F78, 0x0000}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(BitShiftRightTest(a, 64, hamon::array<hamon::uint16_t, 4>{0x0000, 0x0000, 0x0000, 0x0000}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(BitShiftRightTest(a, 99, hamon::array<hamon::uint16_t, 4>{0x0000, 0x0000, 0x0000, 0x0000}));
	}
	{
		HAMON_CXX14_CONSTEXPR hamon::array<hamon::uint64_t, 2> const a{0x0000000000000000, 0x0123456789ABCDEF};
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(BitShiftRightTest(a,  0, hamon::array<hamon::uint64_t, 2>{0x0000000000000000, 0x0123456789ABCDEF}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(BitShiftRightTest(a,  1, hamon::array<hamon::uint64_t, 2>{0x8000000000000000, 0x0091A2B3C4D5E6F7}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(BitShiftRightTest(a, 64, hamon::array<hamon::uint64_t, 2>{0x0123456789ABCDEF, 0x0000000000000000}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(BitShiftRightTest(a, 65, hamon::array<hamon::uint64_t, 2>{0x0091A2B3C4D5E6F7, 0x0000000000000000}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(BitShiftRightTest(a, 127, hamon::array<hamon::uint64_t, 2>{0x0000000000000000, 0x0000000000000000}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(BitShiftRightTest(a, 128, hamon::array<hamon::uint64_t, 2>{0x0000000000000000, 0x0000000000000000}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(BitShiftRightTest(a, 999, hamon::array<hamon::uint64_t, 2>{0x0000000000000000, 0x0000000000000000}));
	}
}

}	// namespace bigint_algo_bit_shift_right_test

}	// namespace hamon_bigint_test
