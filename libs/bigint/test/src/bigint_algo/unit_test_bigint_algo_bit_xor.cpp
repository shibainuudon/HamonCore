/**
 *	@file	unit_test_bigint_algo_bit_xor.cpp
 *
 *	@brief	bigint_algo::bit_xor のテスト
 */

#include <hamon/bigint/bigint_algo/bit_xor.hpp>
#include <hamon/array.hpp>
#include <hamon/cstdint.hpp>
#include <hamon/vector.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_bigint_test
{

namespace bigint_algo_bit_xor_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename VectorType>
inline HAMON_CXX14_CONSTEXPR bool
BitXOrTest(VectorType const& a, VectorType const& b, VectorType const& expected)
{
	// a | b
	{
		VectorType c = a;
		hamon::bigint_algo::bit_xor(c, b);
		VERIFY(c == expected);
	}
	// b | a
	{
		VectorType c = b;
		hamon::bigint_algo::bit_xor(c, a);
		VERIFY(c == expected);
	}
	return true;
}

#undef VERIFY

GTEST_TEST(BigIntAlgoTest, BitXOrTest)
{
#if 0
	{
		hamon::vector<hamon::uint8_t> a{0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC, 0xDE, 0xF0};
		hamon::vector<hamon::uint8_t> b{0xFE, 0xDC, 0xBA};
		for (hamon::size_t i = 0; i < 10000000; ++i)
		{
			hamon::bigint_algo::bit_xor(a, b);
		}
	}
	{
		hamon::array<hamon::uint8_t, 8> a{0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC, 0xDE, 0xF0};
		hamon::array<hamon::uint8_t, 8> b{0xFE, 0xDC, 0xBA};
		for (hamon::size_t i = 0; i < 10000000; ++i)
		{
			hamon::bigint_algo::bit_xor(a, b);
		}
	}
#endif

	EXPECT_TRUE(BitXOrTest(
		hamon::vector<hamon::uint8_t>{0},
		hamon::vector<hamon::uint8_t>{0},
		hamon::vector<hamon::uint8_t>{0}));
	EXPECT_TRUE(BitXOrTest(
		hamon::vector<hamon::uint8_t>{0x12, 0x34, 0x56, 0x78},
		hamon::vector<hamon::uint8_t>{0xFF, 0xFF, 0xFF},
		hamon::vector<hamon::uint8_t>{0xED, 0xCB, 0xA9, 0x78}));
	EXPECT_TRUE(BitXOrTest(
		hamon::vector<hamon::uint8_t>{0x12, 0x34, 0x56, 0x78},
		hamon::vector<hamon::uint8_t>{0xFF, 0x0F, 0xF0, 0xFF},
		hamon::vector<hamon::uint8_t>{0xED, 0x3B, 0xA6, 0x87}));
	EXPECT_TRUE(BitXOrTest(
		hamon::vector<hamon::uint16_t>{0x4996, 0x02D2, 0xFFFF, 0x1234},
		hamon::vector<hamon::uint16_t>{0x0000},
		hamon::vector<hamon::uint16_t>{0x4996, 0x02D2, 0xFFFF, 0x1234}));
	EXPECT_TRUE(BitXOrTest(
		hamon::vector<hamon::uint16_t>{0xFFFF, 0xFF00, 0x0000},
		hamon::vector<hamon::uint16_t>{0x0000, 0x00FF, 0x0F0F},
		hamon::vector<hamon::uint16_t>{0xFFFF, 0xFFFF, 0x0F0F}));
	EXPECT_TRUE(BitXOrTest(
		hamon::vector<hamon::uint16_t>{0x1234, 0x5678, 0x9ABC},
		hamon::vector<hamon::uint16_t>{0x1234, 0x5678, 0x9ABC},
		hamon::vector<hamon::uint16_t>{0}));
	EXPECT_TRUE(BitXOrTest(
		hamon::vector<hamon::uint32_t>{0},
		hamon::vector<hamon::uint32_t>{0},
		hamon::vector<hamon::uint32_t>{0}));
	EXPECT_TRUE(BitXOrTest(
		hamon::vector<hamon::uint32_t>{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF},
		hamon::vector<hamon::uint32_t>{0xFFFF0000, 0xFF00FF00, 0xF0F0F0F0},
		hamon::vector<hamon::uint32_t>{0x0000FFFF, 0x00FF00FF, 0x0F0F0F0F}));
	EXPECT_TRUE(BitXOrTest(
		hamon::vector<hamon::uint64_t>{0x0123456789ABCDEF, 0x1122334455667788},
		hamon::vector<hamon::uint64_t>{0xFFFF0000FF00FF00, 0xFFFFFFFF00000000},
		hamon::vector<hamon::uint64_t>{0xFEDC456776AB32EF, 0xEEDDCCBB55667788}));

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(BitXOrTest(
		hamon::array<hamon::uint8_t, 4>{0x12, 0x34, 0x56, 0x78},
		hamon::array<hamon::uint8_t, 4>{0xFF, 0xFF, 0xFF, 0xFF},
		hamon::array<hamon::uint8_t, 4>{0xED, 0xCB, 0xA9, 0x87}));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(BitXOrTest(
		hamon::array<hamon::uint8_t, 4>{0x12, 0x34, 0x56, 0x78},
		hamon::array<hamon::uint8_t, 4>{0x00, 0x00, 0x00, 0x00},
		hamon::array<hamon::uint8_t, 4>{0x12, 0x34, 0x56, 0x78}));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(BitXOrTest(
		hamon::array<hamon::uint8_t, 2>{0xCB, 0xE1},
		hamon::array<hamon::uint8_t, 2>{0xFA, 0x0F},
		hamon::array<hamon::uint8_t, 2>{0x31, 0xEE}));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(BitXOrTest(
		hamon::array<hamon::uint16_t, 2>{0x4996, 0x02D2},
		hamon::array<hamon::uint16_t, 2>{0x12B9, 0xB0A1},
		hamon::array<hamon::uint16_t, 2>{0x5B2F, 0xB273}));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(BitXOrTest(
		hamon::array<hamon::uint16_t, 3>{0xFFFF, 0xFF00, 0x0000},
		hamon::array<hamon::uint16_t, 3>{0x0000, 0x00FF, 0x0F0F},
		hamon::array<hamon::uint16_t, 3>{0xFFFF, 0xFFFF, 0x0F0F}));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(BitXOrTest(
		hamon::array<hamon::uint16_t, 3>{0x1234, 0x5678, 0x9ABC},
		hamon::array<hamon::uint16_t, 3>{0x1234, 0x5678, 0x9ABC},
		hamon::array<hamon::uint16_t, 3>{0x0000, 0x0000, 0x0000}));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(BitXOrTest(
		hamon::array<hamon::uint32_t, 3>{0},
		hamon::array<hamon::uint32_t, 3>{0},
		hamon::array<hamon::uint32_t, 3>{0}));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(BitXOrTest(
		hamon::array<hamon::uint32_t, 3>{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF},
		hamon::array<hamon::uint32_t, 3>{0xFFFF0000, 0xFF00FF00, 0xF0F0F0F0},
		hamon::array<hamon::uint32_t, 3>{0x0000FFFF, 0x00FF00FF, 0x0F0F0F0F}));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(BitXOrTest(
		hamon::array<hamon::uint64_t, 2>{0x0123456789ABCDEF, 0x1122334455667788},
		hamon::array<hamon::uint64_t, 2>{0xFFFF0000FF00FF00, 0xFFFFFFFF00000000},
		hamon::array<hamon::uint64_t, 2>{0xFEDC456776AB32EF, 0xEEDDCCBB55667788}));
}

}	// namespace bigint_algo_bit_xor_test

}	// namespace hamon_bigint_test
