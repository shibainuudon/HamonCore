/**
 *	@file	unit_test_bigint_algo_bit_shift_left.cpp
 *
 *	@brief	bigint_algo::bit_shift_left のテスト
 */

#include <hamon/bigint/bigint_algo/bit_shift_left.hpp>
#include <hamon/array.hpp>
#include <hamon/cstdint.hpp>
#include <gtest/gtest.h>
#include <vector>
#include "constexpr_test.hpp"

namespace hamon_bigint_test
{

namespace bigint_algo_bit_shift_left_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename VectorType>
inline HAMON_CXX14_CONSTEXPR bool
BitShiftLeftTest(VectorType a, hamon::uintmax_t b, VectorType const& expected, bool overflow)
{
	bool f = hamon::bigint_algo::bit_shift_left(a, b);
	VERIFY(a == expected);
	VERIFY(f == overflow);
	return true;
}

#undef VERIFY

GTEST_TEST(BigIntAlgoTest, BitShiftLeftTest)
{
	{
		std::vector<hamon::uint8_t> const a{0};
		EXPECT_TRUE(BitShiftLeftTest(a, 0, std::vector<hamon::uint8_t>{0}, false));
		EXPECT_TRUE(BitShiftLeftTest(a, 1, std::vector<hamon::uint8_t>{0}, false));
		EXPECT_TRUE(BitShiftLeftTest(a, 2, std::vector<hamon::uint8_t>{0}, false));
		EXPECT_TRUE(BitShiftLeftTest(a, 8, std::vector<hamon::uint8_t>{0}, false));
		EXPECT_TRUE(BitShiftLeftTest(a, 100, std::vector<hamon::uint8_t>{0}, false));
	}
	{
		std::vector<hamon::uint8_t> const a{1};
		EXPECT_TRUE(BitShiftLeftTest(a,  0, std::vector<hamon::uint8_t>{0x01}, false));
		EXPECT_TRUE(BitShiftLeftTest(a,  1, std::vector<hamon::uint8_t>{0x02}, false));
		EXPECT_TRUE(BitShiftLeftTest(a,  2, std::vector<hamon::uint8_t>{0x04}, false));
		EXPECT_TRUE(BitShiftLeftTest(a,  3, std::vector<hamon::uint8_t>{0x08}, false));
		EXPECT_TRUE(BitShiftLeftTest(a,  7, std::vector<hamon::uint8_t>{0x80}, false));
		EXPECT_TRUE(BitShiftLeftTest(a,  8, std::vector<hamon::uint8_t>{0x00, 0x01}, false));
		EXPECT_TRUE(BitShiftLeftTest(a,  9, std::vector<hamon::uint8_t>{0x00, 0x02}, false));
		EXPECT_TRUE(BitShiftLeftTest(a, 15, std::vector<hamon::uint8_t>{0x00, 0x80}, false));
		EXPECT_TRUE(BitShiftLeftTest(a, 16, std::vector<hamon::uint8_t>{0x00, 0x00, 0x01}, false));
		EXPECT_TRUE(BitShiftLeftTest(a, 17, std::vector<hamon::uint8_t>{0x00, 0x00, 0x02}, false));
		EXPECT_TRUE(BitShiftLeftTest(a, 23, std::vector<hamon::uint8_t>{0x00, 0x00, 0x80}, false));
		EXPECT_TRUE(BitShiftLeftTest(a, 24, std::vector<hamon::uint8_t>{0x00, 0x00, 0x00, 0x01}, false));
		EXPECT_TRUE(BitShiftLeftTest(a, 25, std::vector<hamon::uint8_t>{0x00, 0x00, 0x00, 0x02}, false));
	}
	{
		std::vector<hamon::uint8_t> const a{0xFF, 0xFF};
		EXPECT_TRUE(BitShiftLeftTest(a,  0, std::vector<hamon::uint8_t>{0xFF, 0xFF}, false));
		EXPECT_TRUE(BitShiftLeftTest(a,  1, std::vector<hamon::uint8_t>{0xFE, 0xFF, 0x01}, false));
		EXPECT_TRUE(BitShiftLeftTest(a,  2, std::vector<hamon::uint8_t>{0xFC, 0xFF, 0x03}, false));
		EXPECT_TRUE(BitShiftLeftTest(a,  3, std::vector<hamon::uint8_t>{0xF8, 0xFF, 0x07}, false));
		EXPECT_TRUE(BitShiftLeftTest(a,  7, std::vector<hamon::uint8_t>{0x80, 0xFF, 0x7F}, false));
		EXPECT_TRUE(BitShiftLeftTest(a,  8, std::vector<hamon::uint8_t>{0x00, 0xFF, 0xFF}, false));
		EXPECT_TRUE(BitShiftLeftTest(a,  9, std::vector<hamon::uint8_t>{0x00, 0xFE, 0xFF, 0x01}, false));
		EXPECT_TRUE(BitShiftLeftTest(a, 15, std::vector<hamon::uint8_t>{0x00, 0x80, 0xFF, 0x7F}, false));
		EXPECT_TRUE(BitShiftLeftTest(a, 16, std::vector<hamon::uint8_t>{0x00, 0x00, 0xFF, 0xFF}, false));
		EXPECT_TRUE(BitShiftLeftTest(a, 17, std::vector<hamon::uint8_t>{0x00, 0x00, 0xFE, 0xFF, 0x01}, false));
		EXPECT_TRUE(BitShiftLeftTest(a, 23, std::vector<hamon::uint8_t>{0x00, 0x00, 0x80, 0xFF, 0x7F}, false));
		EXPECT_TRUE(BitShiftLeftTest(a, 24, std::vector<hamon::uint8_t>{0x00, 0x00, 0x00, 0xFF, 0xFF}, false));
		EXPECT_TRUE(BitShiftLeftTest(a, 25, std::vector<hamon::uint8_t>{0x00, 0x00, 0x00, 0xFE, 0xFF, 0x01}, false));
	}
	{
		std::vector<hamon::uint64_t> const a{0xFFFFFFFFFFFFFFFF};
		EXPECT_TRUE(BitShiftLeftTest(a,   0, std::vector<hamon::uint64_t>{0xFFFFFFFFFFFFFFFF}, false));
		EXPECT_TRUE(BitShiftLeftTest(a,   1, std::vector<hamon::uint64_t>{0xFFFFFFFFFFFFFFFE, 0x0000000000000001}, false));
		EXPECT_TRUE(BitShiftLeftTest(a,  63, std::vector<hamon::uint64_t>{0x8000000000000000, 0x7FFFFFFFFFFFFFFF}, false));
		EXPECT_TRUE(BitShiftLeftTest(a,  64, std::vector<hamon::uint64_t>{0x0000000000000000, 0xFFFFFFFFFFFFFFFF}, false));
		EXPECT_TRUE(BitShiftLeftTest(a,  65, std::vector<hamon::uint64_t>{0x0000000000000000, 0xFFFFFFFFFFFFFFFE, 0x0000000000000001}, false));
		EXPECT_TRUE(BitShiftLeftTest(a, 127, std::vector<hamon::uint64_t>{0x0000000000000000, 0x8000000000000000, 0x7FFFFFFFFFFFFFFF}, false));
		EXPECT_TRUE(BitShiftLeftTest(a, 128, std::vector<hamon::uint64_t>{0x0000000000000000, 0x0000000000000000, 0xFFFFFFFFFFFFFFFF}, false));
		EXPECT_TRUE(BitShiftLeftTest(a, 129, std::vector<hamon::uint64_t>{0x0000000000000000, 0x0000000000000000, 0xFFFFFFFFFFFFFFFE, 0x0000000000000001}, false));
	}
	{
		HAMON_CXX14_CONSTEXPR hamon::array<hamon::uint8_t, 3> const a{0xFF, 0x7F, 0x00};
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(BitShiftLeftTest(a,  0, hamon::array<hamon::uint8_t, 3>{0xFF, 0x7F, 0x00}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(BitShiftLeftTest(a,  1, hamon::array<hamon::uint8_t, 3>{0xFE, 0xFF, 0x00}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(BitShiftLeftTest(a,  2, hamon::array<hamon::uint8_t, 3>{0xFC, 0xFF, 0x01}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(BitShiftLeftTest(a,  7, hamon::array<hamon::uint8_t, 3>{0x80, 0xFF, 0x3F}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(BitShiftLeftTest(a,  8, hamon::array<hamon::uint8_t, 3>{0x00, 0xFF, 0x7F}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(BitShiftLeftTest(a,  9, hamon::array<hamon::uint8_t, 3>{0x00, 0xFE, 0xFF}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(BitShiftLeftTest(a, 10, hamon::array<hamon::uint8_t, 3>{0x00, 0xFC, 0xFF}, true));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(BitShiftLeftTest(a, 15, hamon::array<hamon::uint8_t, 3>{0x00, 0x80, 0xFF}, true));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(BitShiftLeftTest(a, 16, hamon::array<hamon::uint8_t, 3>{0x00, 0x00, 0xFF}, true));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(BitShiftLeftTest(a, 17, hamon::array<hamon::uint8_t, 3>{0x00, 0x00, 0xFE}, true));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(BitShiftLeftTest(a, 22, hamon::array<hamon::uint8_t, 3>{0x00, 0x00, 0xC0}, true));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(BitShiftLeftTest(a, 23, hamon::array<hamon::uint8_t, 3>{0x00, 0x00, 0x80}, true));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(BitShiftLeftTest(a, 24, hamon::array<hamon::uint8_t, 3>{0x00, 0x00, 0x00}, true));
	}
	{
		HAMON_CXX14_CONSTEXPR hamon::array<hamon::uint64_t, 2> const a{0x0123456789ABCDEF, 0x00};
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(BitShiftLeftTest(a,  0, hamon::array<hamon::uint64_t, 2>{0x0123456789ABCDEF, 0x0000000000000000}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(BitShiftLeftTest(a,  1, hamon::array<hamon::uint64_t, 2>{0x02468ACF13579BDE, 0x0000000000000000}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(BitShiftLeftTest(a,  2, hamon::array<hamon::uint64_t, 2>{0x048D159E26AF37BC, 0x0000000000000000}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(BitShiftLeftTest(a,  3, hamon::array<hamon::uint64_t, 2>{0x091A2B3C4D5E6F78, 0x0000000000000000}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(BitShiftLeftTest(a,  4, hamon::array<hamon::uint64_t, 2>{0x123456789ABCDEF0, 0x0000000000000000}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(BitShiftLeftTest(a,  5, hamon::array<hamon::uint64_t, 2>{0x2468ACF13579BDE0, 0x0000000000000000}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(BitShiftLeftTest(a,  6, hamon::array<hamon::uint64_t, 2>{0x48D159E26AF37BC0, 0x0000000000000000}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(BitShiftLeftTest(a,  7, hamon::array<hamon::uint64_t, 2>{0x91A2B3C4D5E6F780, 0x0000000000000000}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(BitShiftLeftTest(a,  8, hamon::array<hamon::uint64_t, 2>{0x23456789ABCDEF00, 0x0000000000000001}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(BitShiftLeftTest(a,  9, hamon::array<hamon::uint64_t, 2>{0x468ACF13579BDE00, 0x0000000000000002}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(BitShiftLeftTest(a, 10, hamon::array<hamon::uint64_t, 2>{0x8D159E26AF37BC00, 0x0000000000000004}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(BitShiftLeftTest(a, 11, hamon::array<hamon::uint64_t, 2>{0x1A2B3C4D5E6F7800, 0x0000000000000009}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(BitShiftLeftTest(a, 63, hamon::array<hamon::uint64_t, 2>{0x8000000000000000, 0x0091A2B3C4D5E6F7}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(BitShiftLeftTest(a, 64, hamon::array<hamon::uint64_t, 2>{0x0000000000000000, 0x0123456789ABCDEF}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(BitShiftLeftTest(a, 65, hamon::array<hamon::uint64_t, 2>{0x0000000000000000, 0x02468ACF13579BDE}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(BitShiftLeftTest(a, 66, hamon::array<hamon::uint64_t, 2>{0x0000000000000000, 0x048D159E26AF37BC}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(BitShiftLeftTest(a, 67, hamon::array<hamon::uint64_t, 2>{0x0000000000000000, 0x091A2B3C4D5E6F78}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(BitShiftLeftTest(a, 68, hamon::array<hamon::uint64_t, 2>{0x0000000000000000, 0x123456789ABCDEF0}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(BitShiftLeftTest(a, 69, hamon::array<hamon::uint64_t, 2>{0x0000000000000000, 0x2468ACF13579BDE0}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(BitShiftLeftTest(a, 70, hamon::array<hamon::uint64_t, 2>{0x0000000000000000, 0x48D159E26AF37BC0}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(BitShiftLeftTest(a, 71, hamon::array<hamon::uint64_t, 2>{0x0000000000000000, 0x91A2B3C4D5E6F780}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(BitShiftLeftTest(a, 72, hamon::array<hamon::uint64_t, 2>{0x0000000000000000, 0x23456789ABCDEF00}, true));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(BitShiftLeftTest(a, 73, hamon::array<hamon::uint64_t, 2>{0x0000000000000000, 0x468ACF13579BDE00}, true));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(BitShiftLeftTest(a, 74, hamon::array<hamon::uint64_t, 2>{0x0000000000000000, 0x8D159E26AF37BC00}, true));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(BitShiftLeftTest(a, 75, hamon::array<hamon::uint64_t, 2>{0x0000000000000000, 0x1A2B3C4D5E6F7800}, true));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(BitShiftLeftTest(a,126, hamon::array<hamon::uint64_t, 2>{0x0000000000000000, 0xC000000000000000}, true));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(BitShiftLeftTest(a,127, hamon::array<hamon::uint64_t, 2>{0x0000000000000000, 0x8000000000000000}, true));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(BitShiftLeftTest(a,128, hamon::array<hamon::uint64_t, 2>{0x0000000000000000, 0x0000000000000000}, true));
	}
}

}	// namespace bigint_algo_bit_shift_left_test

}	// namespace hamon_bigint_test
