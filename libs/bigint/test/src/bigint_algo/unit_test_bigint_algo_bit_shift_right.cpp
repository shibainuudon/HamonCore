/**
 *	@file	unit_test_bigint_algo_bit_shift_right.cpp
 *
 *	@brief	bigint_algo::bit_shift_right のテスト
 */

#include <hamon/bigint/bigint_algo/bit_shift_right.hpp>
#include <hamon/array.hpp>
#include <hamon/cstdint.hpp>
#include <gtest/gtest.h>
#include <vector>
#include "constexpr_test.hpp"

GTEST_TEST(BigIntAlgoTest, BitShiftRightTest)
{
	{
		std::vector<hamon::uint8_t> const a{0};
		EXPECT_EQ(hamon::detail::bigint_algo::bit_shift_right(a, 0), (std::vector<hamon::uint8_t>{0}));
		EXPECT_EQ(hamon::detail::bigint_algo::bit_shift_right(a, 1), (std::vector<hamon::uint8_t>{0}));
		EXPECT_EQ(hamon::detail::bigint_algo::bit_shift_right(a, 2), (std::vector<hamon::uint8_t>{0}));
		EXPECT_EQ(hamon::detail::bigint_algo::bit_shift_right(a, 100), (std::vector<hamon::uint8_t>{0}));
	}
	{
		std::vector<hamon::uint8_t> const a{0x00, 0x80};
		EXPECT_EQ(hamon::detail::bigint_algo::bit_shift_right(a,  0), (std::vector<hamon::uint8_t>{0x00, 0x80}));
		EXPECT_EQ(hamon::detail::bigint_algo::bit_shift_right(a,  1), (std::vector<hamon::uint8_t>{0x00, 0x40}));
		EXPECT_EQ(hamon::detail::bigint_algo::bit_shift_right(a,  2), (std::vector<hamon::uint8_t>{0x00, 0x20}));
		EXPECT_EQ(hamon::detail::bigint_algo::bit_shift_right(a,  3), (std::vector<hamon::uint8_t>{0x00, 0x10}));
		EXPECT_EQ(hamon::detail::bigint_algo::bit_shift_right(a,  4), (std::vector<hamon::uint8_t>{0x00, 0x08}));
		EXPECT_EQ(hamon::detail::bigint_algo::bit_shift_right(a,  5), (std::vector<hamon::uint8_t>{0x00, 0x04}));
		EXPECT_EQ(hamon::detail::bigint_algo::bit_shift_right(a,  6), (std::vector<hamon::uint8_t>{0x00, 0x02}));
		EXPECT_EQ(hamon::detail::bigint_algo::bit_shift_right(a,  7), (std::vector<hamon::uint8_t>{0x00, 0x01}));
		EXPECT_EQ(hamon::detail::bigint_algo::bit_shift_right(a,  8), (std::vector<hamon::uint8_t>{0x80}));
		EXPECT_EQ(hamon::detail::bigint_algo::bit_shift_right(a,  9), (std::vector<hamon::uint8_t>{0x40}));
		EXPECT_EQ(hamon::detail::bigint_algo::bit_shift_right(a, 10), (std::vector<hamon::uint8_t>{0x20}));
		EXPECT_EQ(hamon::detail::bigint_algo::bit_shift_right(a, 11), (std::vector<hamon::uint8_t>{0x10}));
		EXPECT_EQ(hamon::detail::bigint_algo::bit_shift_right(a, 12), (std::vector<hamon::uint8_t>{0x08}));
		EXPECT_EQ(hamon::detail::bigint_algo::bit_shift_right(a, 13), (std::vector<hamon::uint8_t>{0x04}));
		EXPECT_EQ(hamon::detail::bigint_algo::bit_shift_right(a, 14), (std::vector<hamon::uint8_t>{0x02}));
		EXPECT_EQ(hamon::detail::bigint_algo::bit_shift_right(a, 15), (std::vector<hamon::uint8_t>{0x01}));
		EXPECT_EQ(hamon::detail::bigint_algo::bit_shift_right(a, 16), (std::vector<hamon::uint8_t>{0x00}));
		EXPECT_EQ(hamon::detail::bigint_algo::bit_shift_right(a, 17), (std::vector<hamon::uint8_t>{0x00}));
	}
	{
		std::vector<hamon::uint16_t> const a{0x9ABC, 0x5678, 0x1234};
		EXPECT_EQ(hamon::detail::bigint_algo::bit_shift_right(a,  1), (std::vector<hamon::uint16_t>{0x4D5E, 0x2B3C, 0x091A}));
		EXPECT_EQ(hamon::detail::bigint_algo::bit_shift_right(a,  2), (std::vector<hamon::uint16_t>{0x26AF, 0x159E, 0x048D}));
		EXPECT_EQ(hamon::detail::bigint_algo::bit_shift_right(a,  3), (std::vector<hamon::uint16_t>{0x1357, 0x8ACF, 0x0246}));
		EXPECT_EQ(hamon::detail::bigint_algo::bit_shift_right(a,  4), (std::vector<hamon::uint16_t>{0x89AB, 0x4567, 0x0123}));
		EXPECT_EQ(hamon::detail::bigint_algo::bit_shift_right(a,  5), (std::vector<hamon::uint16_t>{0xC4D5, 0xA2B3, 0x0091}));
		EXPECT_EQ(hamon::detail::bigint_algo::bit_shift_right(a,  6), (std::vector<hamon::uint16_t>{0xE26A, 0xD159, 0x0048}));
		EXPECT_EQ(hamon::detail::bigint_algo::bit_shift_right(a,  7), (std::vector<hamon::uint16_t>{0xF135, 0x68AC, 0x0024}));
		EXPECT_EQ(hamon::detail::bigint_algo::bit_shift_right(a,  8), (std::vector<hamon::uint16_t>{0x789A, 0x3456, 0x0012}));
		EXPECT_EQ(hamon::detail::bigint_algo::bit_shift_right(a,  9), (std::vector<hamon::uint16_t>{0x3C4D, 0x1A2B, 0x0009}));
		EXPECT_EQ(hamon::detail::bigint_algo::bit_shift_right(a, 10), (std::vector<hamon::uint16_t>{0x9E26, 0x8D15, 0x0004}));
		EXPECT_EQ(hamon::detail::bigint_algo::bit_shift_right(a, 11), (std::vector<hamon::uint16_t>{0xCF13, 0x468A, 0x0002}));
		EXPECT_EQ(hamon::detail::bigint_algo::bit_shift_right(a, 12), (std::vector<hamon::uint16_t>{0x6789, 0x2345, 0x0001}));
		EXPECT_EQ(hamon::detail::bigint_algo::bit_shift_right(a, 13), (std::vector<hamon::uint16_t>{0xB3C4, 0x91A2}));
		EXPECT_EQ(hamon::detail::bigint_algo::bit_shift_right(a, 14), (std::vector<hamon::uint16_t>{0x59E2, 0x48D1}));
		EXPECT_EQ(hamon::detail::bigint_algo::bit_shift_right(a, 15), (std::vector<hamon::uint16_t>{0xACF1, 0x2468}));
		EXPECT_EQ(hamon::detail::bigint_algo::bit_shift_right(a, 16), (std::vector<hamon::uint16_t>{0x5678, 0x1234}));
		EXPECT_EQ(hamon::detail::bigint_algo::bit_shift_right(a, 17), (std::vector<hamon::uint16_t>{0x2B3C, 0x091A}));
		EXPECT_EQ(hamon::detail::bigint_algo::bit_shift_right(a, 18), (std::vector<hamon::uint16_t>{0x159E, 0x048D}));
		EXPECT_EQ(hamon::detail::bigint_algo::bit_shift_right(a, 19), (std::vector<hamon::uint16_t>{0x8ACF, 0x0246}));
		EXPECT_EQ(hamon::detail::bigint_algo::bit_shift_right(a, 20), (std::vector<hamon::uint16_t>{0x4567, 0x0123}));
		EXPECT_EQ(hamon::detail::bigint_algo::bit_shift_right(a, 21), (std::vector<hamon::uint16_t>{0xA2B3, 0x0091}));
		EXPECT_EQ(hamon::detail::bigint_algo::bit_shift_right(a, 22), (std::vector<hamon::uint16_t>{0xD159, 0x0048}));
		EXPECT_EQ(hamon::detail::bigint_algo::bit_shift_right(a, 23), (std::vector<hamon::uint16_t>{0x68AC, 0x0024}));
		EXPECT_EQ(hamon::detail::bigint_algo::bit_shift_right(a, 24), (std::vector<hamon::uint16_t>{0x3456, 0x0012}));
		EXPECT_EQ(hamon::detail::bigint_algo::bit_shift_right(a, 25), (std::vector<hamon::uint16_t>{0x1A2B, 0x0009}));
		EXPECT_EQ(hamon::detail::bigint_algo::bit_shift_right(a, 26), (std::vector<hamon::uint16_t>{0x8D15, 0x0004}));
		EXPECT_EQ(hamon::detail::bigint_algo::bit_shift_right(a, 27), (std::vector<hamon::uint16_t>{0x468A, 0x0002}));
		EXPECT_EQ(hamon::detail::bigint_algo::bit_shift_right(a, 28), (std::vector<hamon::uint16_t>{0x2345, 0x0001}));
		EXPECT_EQ(hamon::detail::bigint_algo::bit_shift_right(a, 29), (std::vector<hamon::uint16_t>{0x91A2}));
		EXPECT_EQ(hamon::detail::bigint_algo::bit_shift_right(a, 30), (std::vector<hamon::uint16_t>{0x48D1}));
		EXPECT_EQ(hamon::detail::bigint_algo::bit_shift_right(a, 31), (std::vector<hamon::uint16_t>{0x2468}));
		EXPECT_EQ(hamon::detail::bigint_algo::bit_shift_right(a, 32), (std::vector<hamon::uint16_t>{0x1234}));
		EXPECT_EQ(hamon::detail::bigint_algo::bit_shift_right(a, 33), (std::vector<hamon::uint16_t>{0x091A}));
		EXPECT_EQ(hamon::detail::bigint_algo::bit_shift_right(a, 34), (std::vector<hamon::uint16_t>{0x048D}));
		EXPECT_EQ(hamon::detail::bigint_algo::bit_shift_right(a, 35), (std::vector<hamon::uint16_t>{0x0246}));
		EXPECT_EQ(hamon::detail::bigint_algo::bit_shift_right(a, 36), (std::vector<hamon::uint16_t>{0x0123}));
		EXPECT_EQ(hamon::detail::bigint_algo::bit_shift_right(a, 37), (std::vector<hamon::uint16_t>{0x0091}));
		EXPECT_EQ(hamon::detail::bigint_algo::bit_shift_right(a, 38), (std::vector<hamon::uint16_t>{0x0048}));
		EXPECT_EQ(hamon::detail::bigint_algo::bit_shift_right(a, 39), (std::vector<hamon::uint16_t>{0x0024}));
		EXPECT_EQ(hamon::detail::bigint_algo::bit_shift_right(a, 40), (std::vector<hamon::uint16_t>{0x0012}));
		EXPECT_EQ(hamon::detail::bigint_algo::bit_shift_right(a, 41), (std::vector<hamon::uint16_t>{0x0009}));
		EXPECT_EQ(hamon::detail::bigint_algo::bit_shift_right(a, 42), (std::vector<hamon::uint16_t>{0x0004}));
		EXPECT_EQ(hamon::detail::bigint_algo::bit_shift_right(a, 43), (std::vector<hamon::uint16_t>{0x0002}));
		EXPECT_EQ(hamon::detail::bigint_algo::bit_shift_right(a, 44), (std::vector<hamon::uint16_t>{0x0001}));
		EXPECT_EQ(hamon::detail::bigint_algo::bit_shift_right(a, 45), (std::vector<hamon::uint16_t>{0x0000}));
		EXPECT_EQ(hamon::detail::bigint_algo::bit_shift_right(a, 200), (std::vector<hamon::uint16_t>{0x0000}));
	}
	{
		std::vector<hamon::uint32_t> const a{0x00000000, 0x00000000, 0x00000000, 0xFFFFFFFF};
		EXPECT_EQ(hamon::detail::bigint_algo::bit_shift_right(a,   0), (std::vector<hamon::uint32_t>{0x00000000, 0x00000000, 0x00000000, 0xFFFFFFFF}));
		EXPECT_EQ(hamon::detail::bigint_algo::bit_shift_right(a,   1), (std::vector<hamon::uint32_t>{0x00000000, 0x00000000, 0x80000000, 0x7FFFFFFF}));
		EXPECT_EQ(hamon::detail::bigint_algo::bit_shift_right(a,   2), (std::vector<hamon::uint32_t>{0x00000000, 0x00000000, 0xC0000000, 0x3FFFFFFF}));
		EXPECT_EQ(hamon::detail::bigint_algo::bit_shift_right(a,   3), (std::vector<hamon::uint32_t>{0x00000000, 0x00000000, 0xE0000000, 0x1FFFFFFF}));
		EXPECT_EQ(hamon::detail::bigint_algo::bit_shift_right(a,   4), (std::vector<hamon::uint32_t>{0x00000000, 0x00000000, 0xF0000000, 0x0FFFFFFF}));
		EXPECT_EQ(hamon::detail::bigint_algo::bit_shift_right(a,  31), (std::vector<hamon::uint32_t>{0x00000000, 0x00000000, 0xFFFFFFFE, 0x00000001}));
		EXPECT_EQ(hamon::detail::bigint_algo::bit_shift_right(a,  32), (std::vector<hamon::uint32_t>{0x00000000, 0x00000000, 0xFFFFFFFF}));
		EXPECT_EQ(hamon::detail::bigint_algo::bit_shift_right(a,  33), (std::vector<hamon::uint32_t>{0x00000000, 0x80000000, 0x7FFFFFFF}));
		EXPECT_EQ(hamon::detail::bigint_algo::bit_shift_right(a,  63), (std::vector<hamon::uint32_t>{0x00000000, 0xFFFFFFFE, 0x00000001}));
		EXPECT_EQ(hamon::detail::bigint_algo::bit_shift_right(a,  64), (std::vector<hamon::uint32_t>{0x00000000, 0xFFFFFFFF}));
		EXPECT_EQ(hamon::detail::bigint_algo::bit_shift_right(a,  65), (std::vector<hamon::uint32_t>{0x80000000, 0x7FFFFFFF}));
		EXPECT_EQ(hamon::detail::bigint_algo::bit_shift_right(a,  95), (std::vector<hamon::uint32_t>{0xFFFFFFFE, 0x00000001}));
		EXPECT_EQ(hamon::detail::bigint_algo::bit_shift_right(a,  96), (std::vector<hamon::uint32_t>{0xFFFFFFFF}));
		EXPECT_EQ(hamon::detail::bigint_algo::bit_shift_right(a,  97), (std::vector<hamon::uint32_t>{0x7FFFFFFF}));
		EXPECT_EQ(hamon::detail::bigint_algo::bit_shift_right(a, 127), (std::vector<hamon::uint32_t>{0x00000001}));
		EXPECT_EQ(hamon::detail::bigint_algo::bit_shift_right(a, 128), (std::vector<hamon::uint32_t>{0x00000000}));
		EXPECT_EQ(hamon::detail::bigint_algo::bit_shift_right(a, 129), (std::vector<hamon::uint32_t>{0x00000000}));
	}
	{
		std::vector<hamon::uint64_t> const a{0x1020304050607080, 0xF00000000000000F, 0x8000000000000000};
		EXPECT_EQ(hamon::detail::bigint_algo::bit_shift_right(a,   0), (std::vector<hamon::uint64_t>{0x1020304050607080, 0xF00000000000000F, 0x8000000000000000}));
		EXPECT_EQ(hamon::detail::bigint_algo::bit_shift_right(a,   1), (std::vector<hamon::uint64_t>{0x8810182028303840, 0x7800000000000007, 0x4000000000000000}));
		EXPECT_EQ(hamon::detail::bigint_algo::bit_shift_right(a,   2), (std::vector<hamon::uint64_t>{0xC4080C1014181C20, 0x3C00000000000003, 0x2000000000000000}));
		EXPECT_EQ(hamon::detail::bigint_algo::bit_shift_right(a,  63), (std::vector<hamon::uint64_t>{0xE00000000000001E, 0x0000000000000001, 0x0000000000000001}));
		EXPECT_EQ(hamon::detail::bigint_algo::bit_shift_right(a,  64), (std::vector<hamon::uint64_t>{0xF00000000000000F, 0x8000000000000000}));
		EXPECT_EQ(hamon::detail::bigint_algo::bit_shift_right(a,  65), (std::vector<hamon::uint64_t>{0x7800000000000007, 0x4000000000000000}));
		EXPECT_EQ(hamon::detail::bigint_algo::bit_shift_right(a, 127), (std::vector<hamon::uint64_t>{0x0000000000000001, 0x0000000000000001}));
		EXPECT_EQ(hamon::detail::bigint_algo::bit_shift_right(a, 128), (std::vector<hamon::uint64_t>{0x8000000000000000}));
		EXPECT_EQ(hamon::detail::bigint_algo::bit_shift_right(a, 129), (std::vector<hamon::uint64_t>{0x4000000000000000}));
		EXPECT_EQ(hamon::detail::bigint_algo::bit_shift_right(a, 191), (std::vector<hamon::uint64_t>{0x0000000000000001}));
		EXPECT_EQ(hamon::detail::bigint_algo::bit_shift_right(a, 192), (std::vector<hamon::uint64_t>{0x0000000000000000}));
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::array<hamon::uint8_t, 3> const a{0x00, 0xFF, 0x7F};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::detail::bigint_algo::bit_shift_right(a,  0), (hamon::array<hamon::uint8_t, 3>{0x00, 0xFF, 0x7F}));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::detail::bigint_algo::bit_shift_right(a,  1), (hamon::array<hamon::uint8_t, 3>{0x80, 0xFF, 0x3F}));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::detail::bigint_algo::bit_shift_right(a,  2), (hamon::array<hamon::uint8_t, 3>{0xC0, 0xFF, 0x1F}));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::detail::bigint_algo::bit_shift_right(a,  3), (hamon::array<hamon::uint8_t, 3>{0xE0, 0xFF, 0x0F}));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::detail::bigint_algo::bit_shift_right(a,  4), (hamon::array<hamon::uint8_t, 3>{0xF0, 0xFF, 0x07}));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::detail::bigint_algo::bit_shift_right(a,  5), (hamon::array<hamon::uint8_t, 3>{0xF8, 0xFF, 0x03}));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::detail::bigint_algo::bit_shift_right(a,  6), (hamon::array<hamon::uint8_t, 3>{0xFC, 0xFF, 0x01}));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::detail::bigint_algo::bit_shift_right(a,  7), (hamon::array<hamon::uint8_t, 3>{0xFE, 0xFF, 0x00}));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::detail::bigint_algo::bit_shift_right(a,  8), (hamon::array<hamon::uint8_t, 3>{0xFF, 0x7F, 0x00}));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::detail::bigint_algo::bit_shift_right(a,  9), (hamon::array<hamon::uint8_t, 3>{0xFF, 0x3F, 0x00}));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::detail::bigint_algo::bit_shift_right(a, 10), (hamon::array<hamon::uint8_t, 3>{0xFF, 0x1F, 0x00}));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::detail::bigint_algo::bit_shift_right(a, 11), (hamon::array<hamon::uint8_t, 3>{0xFF, 0x0F, 0x00}));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::detail::bigint_algo::bit_shift_right(a, 12), (hamon::array<hamon::uint8_t, 3>{0xFF, 0x07, 0x00}));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::detail::bigint_algo::bit_shift_right(a, 13), (hamon::array<hamon::uint8_t, 3>{0xFF, 0x03, 0x00}));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::detail::bigint_algo::bit_shift_right(a, 14), (hamon::array<hamon::uint8_t, 3>{0xFF, 0x01, 0x00}));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::detail::bigint_algo::bit_shift_right(a, 15), (hamon::array<hamon::uint8_t, 3>{0xFF, 0x00, 0x00}));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::detail::bigint_algo::bit_shift_right(a, 16), (hamon::array<hamon::uint8_t, 3>{0x7F, 0x00, 0x00}));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::detail::bigint_algo::bit_shift_right(a, 17), (hamon::array<hamon::uint8_t, 3>{0x3F, 0x00, 0x00}));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::detail::bigint_algo::bit_shift_right(a, 18), (hamon::array<hamon::uint8_t, 3>{0x1F, 0x00, 0x00}));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::detail::bigint_algo::bit_shift_right(a, 19), (hamon::array<hamon::uint8_t, 3>{0x0F, 0x00, 0x00}));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::detail::bigint_algo::bit_shift_right(a, 20), (hamon::array<hamon::uint8_t, 3>{0x07, 0x00, 0x00}));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::detail::bigint_algo::bit_shift_right(a, 21), (hamon::array<hamon::uint8_t, 3>{0x03, 0x00, 0x00}));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::detail::bigint_algo::bit_shift_right(a, 22), (hamon::array<hamon::uint8_t, 3>{0x01, 0x00, 0x00}));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::detail::bigint_algo::bit_shift_right(a, 23), (hamon::array<hamon::uint8_t, 3>{0x00, 0x00, 0x00}));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::detail::bigint_algo::bit_shift_right(a, 24), (hamon::array<hamon::uint8_t, 3>{0x00, 0x00, 0x00}));
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::array<hamon::uint16_t, 4> const a{0x1234, 0x5678, 0x9ABC, 0xDEF0};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::detail::bigint_algo::bit_shift_right(a,  0), (hamon::array<hamon::uint16_t, 4>{0x1234, 0x5678, 0x9ABC, 0xDEF0}));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::detail::bigint_algo::bit_shift_right(a,  1), (hamon::array<hamon::uint16_t, 4>{0x091A, 0x2B3C, 0x4D5E, 0x6F78}));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::detail::bigint_algo::bit_shift_right(a,  2), (hamon::array<hamon::uint16_t, 4>{0x048D, 0x159E, 0x26AF, 0x37BC}));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::detail::bigint_algo::bit_shift_right(a, 15), (hamon::array<hamon::uint16_t, 4>{0xACF0, 0x3578, 0xBDE1, 0x0001}));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::detail::bigint_algo::bit_shift_right(a, 16), (hamon::array<hamon::uint16_t, 4>{0x5678, 0x9ABC, 0xDEF0, 0x0000}));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::detail::bigint_algo::bit_shift_right(a, 17), (hamon::array<hamon::uint16_t, 4>{0x2B3C, 0x4D5E, 0x6F78, 0x0000}));
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::array<hamon::uint64_t, 2> const a{0x0000000000000000, 0x0123456789ABCDEF};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::detail::bigint_algo::bit_shift_right(a,  0), (hamon::array<hamon::uint64_t, 2>{0x0000000000000000, 0x0123456789ABCDEF}));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::detail::bigint_algo::bit_shift_right(a,  1), (hamon::array<hamon::uint64_t, 2>{0x8000000000000000, 0x0091A2B3C4D5E6F7}));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::detail::bigint_algo::bit_shift_right(a, 64), (hamon::array<hamon::uint64_t, 2>{0x0123456789ABCDEF, 0x0000000000000000}));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::detail::bigint_algo::bit_shift_right(a, 65), (hamon::array<hamon::uint64_t, 2>{0x0091A2B3C4D5E6F7, 0x0000000000000000}));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::detail::bigint_algo::bit_shift_right(a, 127), (hamon::array<hamon::uint64_t, 2>{0x0000000000000000, 0x0000000000000000}));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::detail::bigint_algo::bit_shift_right(a, 128), (hamon::array<hamon::uint64_t, 2>{0x0000000000000000, 0x0000000000000000}));
	}
}
