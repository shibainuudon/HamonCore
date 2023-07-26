/**
 *	@file	unit_test_bigint_algo_bit_or.cpp
 *
 *	@brief	bigint_algo::bit_or のテスト
 */

#include <hamon/bigint/bigint_algo/bit_or.hpp>
#include <hamon/array.hpp>
#include <hamon/cstdint.hpp>
#include <gtest/gtest.h>
#include <vector>
#include "constexpr_test.hpp"

namespace hamon_bigint_test
{

namespace bigint_algo_bit_or_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename VectorType>
inline HAMON_CXX14_CONSTEXPR bool
BitOrTest(VectorType const& a, VectorType const& b, VectorType const& expected)
{
	// a | b
	{
		VectorType c = a;
		hamon::bigint_algo::bit_or(c, b);
		VERIFY(c == expected);
	}
	// b | a
	{
		VectorType c = b;
		hamon::bigint_algo::bit_or(c, a);
		VERIFY(c == expected);
	}
	return true;
}

#undef VERIFY

GTEST_TEST(BigIntAlgoTest, BitOrTest)
{
	EXPECT_TRUE(BitOrTest(
		std::vector<hamon::uint8_t>{0},
		std::vector<hamon::uint8_t>{0},
		std::vector<hamon::uint8_t>{0}));
	EXPECT_TRUE(BitOrTest(
		std::vector<hamon::uint8_t>{0x12, 0x34, 0x56, 0x78},
		std::vector<hamon::uint8_t>{0xFF, 0xFF, 0xFF},
		std::vector<hamon::uint8_t>{0xFF, 0xFF, 0xFF, 0x78}));
	EXPECT_TRUE(BitOrTest(
		std::vector<hamon::uint8_t>{0x12, 0x34, 0x56, 0x78},
		std::vector<hamon::uint8_t>{0xFF, 0x0F, 0xF0},
		std::vector<hamon::uint8_t>{0xFF, 0x3F, 0xF6, 0x78}));
	EXPECT_TRUE(BitOrTest(
		std::vector<hamon::uint16_t>{0x4996, 0x02D2},
		std::vector<hamon::uint16_t>{0x12B9, 0xB0A1},
		std::vector<hamon::uint16_t>{0x5BBF, 0xB2F3}));
	EXPECT_TRUE(BitOrTest(
		std::vector<hamon::uint16_t>{0x4996, 0x02D2, 0xFFFF, 0x1234},
		std::vector<hamon::uint16_t>{0x0000},
		std::vector<hamon::uint16_t>{0x4996, 0x02D2, 0xFFFF, 0x1234}));
	EXPECT_TRUE(BitOrTest(
		std::vector<hamon::uint16_t>{0xFFFF, 0xFF00, 0x0000},
		std::vector<hamon::uint16_t>{0x0000, 0x00FF, 0x0F0F},
		std::vector<hamon::uint16_t>{0xFFFF, 0xFFFF, 0x0F0F}));
	EXPECT_TRUE(BitOrTest(
		std::vector<hamon::uint16_t>{0x1234, 0x5678, 0x9ABC},
		std::vector<hamon::uint16_t>{0x1234, 0x5678, 0x9ABC},
		std::vector<hamon::uint16_t>{0x1234, 0x5678, 0x9ABC}));
	EXPECT_TRUE(BitOrTest(
		std::vector<hamon::uint32_t>{0},
		std::vector<hamon::uint32_t>{0},
		std::vector<hamon::uint32_t>{0}));
	EXPECT_TRUE(BitOrTest(
		std::vector<hamon::uint32_t>{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF},
		std::vector<hamon::uint32_t>{0xFFFF0000, 0xFF00FF00, 0xF0F0F0F0},
		std::vector<hamon::uint32_t>{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}));
	EXPECT_TRUE(BitOrTest(
		std::vector<hamon::uint64_t>{0x0123456789ABCDEF, 0x1122334455667788},
		std::vector<hamon::uint64_t>{0xFFFF0000FF00FF00, 0xFFFFFFFF00000000},
		std::vector<hamon::uint64_t>{0xFFFF4567FFABFFEF, 0xFFFFFFFF55667788}));

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(BitOrTest(
		hamon::array<hamon::uint8_t, 4>{0x12, 0x34, 0x56, 0x78},
		hamon::array<hamon::uint8_t, 4>{0xFF, 0xFF, 0xFF, 0xFF},
		hamon::array<hamon::uint8_t, 4>{0xFF, 0xFF, 0xFF, 0xFF}));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(BitOrTest(
		hamon::array<hamon::uint8_t, 4>{0x12, 0x34, 0x56, 0x78},
		hamon::array<hamon::uint8_t, 4>{0x00, 0x00, 0x00, 0x00},
		hamon::array<hamon::uint8_t, 4>{0x12, 0x34, 0x56, 0x78}));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(BitOrTest(
		hamon::array<hamon::uint8_t, 2>{0xCB, 0xE1},
		hamon::array<hamon::uint8_t, 2>{0xFA, 0x0F},
		hamon::array<hamon::uint8_t, 2>{0xFB, 0xEF}));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(BitOrTest(
		hamon::array<hamon::uint16_t, 2>{0x4996, 0x02D2},
		hamon::array<hamon::uint16_t, 2>{0x12B9, 0xB0A1},
		hamon::array<hamon::uint16_t, 2>{0x5BBF, 0xB2F3}));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(BitOrTest(
		hamon::array<hamon::uint16_t, 3>{0xFFFF, 0xFF00, 0x0000},
		hamon::array<hamon::uint16_t, 3>{0x0000, 0x00FF, 0x0F0F},
		hamon::array<hamon::uint16_t, 3>{0xFFFF, 0xFFFF, 0x0F0F}));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(BitOrTest(
		hamon::array<hamon::uint16_t, 3>{0x1234, 0x5678, 0x9ABC},
		hamon::array<hamon::uint16_t, 3>{0x1234, 0x5678, 0x9ABC},
		hamon::array<hamon::uint16_t, 3>{0x1234, 0x5678, 0x9ABC}));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(BitOrTest(
		hamon::array<hamon::uint32_t, 3>{0},
		hamon::array<hamon::uint32_t, 3>{0},
		hamon::array<hamon::uint32_t, 3>{0}));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(BitOrTest(
		hamon::array<hamon::uint32_t, 3>{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF},
		hamon::array<hamon::uint32_t, 3>{0xFFFF0000, 0xFF00FF00, 0xF0F0F0F0},
		hamon::array<hamon::uint32_t, 3>{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(BitOrTest(
		hamon::array<hamon::uint64_t, 2>{0x0123456789ABCDEF, 0x1122334455667788},
		hamon::array<hamon::uint64_t, 2>{0xFFFF0000FF00FF00, 0xFFFFFFFF00000000},
		hamon::array<hamon::uint64_t, 2>{0xFFFF4567FFABFFEF, 0xFFFFFFFF55667788}));
}

}	// namespace bigint_algo_bit_or_test

}	// namespace hamon_bigint_test
