/**
 *	@file	unit_test_bigint_algo_add.cpp
 *
 *	@brief	bigint_algo::add のテスト
 */

#include <hamon/bigint/bigint_algo/add.hpp>
#include <hamon/array.hpp>
#include <hamon/cstdint.hpp>
#include <gtest/gtest.h>
#include <vector>
#include "constexpr_test.hpp"

namespace hamon_bigint_test
{

namespace bigint_algo_add_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename VectorType>
inline HAMON_CXX14_CONSTEXPR bool
AddTest(VectorType const& a, VectorType const& b, VectorType const& expected, bool overflow)
{
	// a + b
	{
		VectorType c = a;
		bool f = hamon::bigint_algo::add(c, b);
		VERIFY(c == expected);
		VERIFY(f == overflow);
	}
	// b + a
	{
		VectorType c = b;
		bool f = hamon::bigint_algo::add(c, a);
		VERIFY(c == expected);
		VERIFY(f == overflow);
	}
	return true;
}

#undef VERIFY

GTEST_TEST(BigIntAlgoTest, AddTest)
{
	EXPECT_TRUE(AddTest(
		std::vector<hamon::uint8_t>{0},
		std::vector<hamon::uint8_t>{0},
		std::vector<hamon::uint8_t>{0},
		false));
	EXPECT_TRUE(AddTest(
		std::vector<hamon::uint8_t>{2},
		std::vector<hamon::uint8_t>{3},
		std::vector<hamon::uint8_t>{5},
		false));
	EXPECT_TRUE(AddTest(
		std::vector<hamon::uint8_t>{0xFF},
		std::vector<hamon::uint8_t>{0x03},
		std::vector<hamon::uint8_t>{0x02, 0x01},
		false));
	EXPECT_TRUE(AddTest(
		std::vector<hamon::uint8_t>{0x04},
		std::vector<hamon::uint8_t>{0xFE},
		std::vector<hamon::uint8_t>{0x02, 0x01},
		false));
	EXPECT_TRUE(AddTest(
		std::vector<hamon::uint8_t>{0xFF, 0xFF, 0xFF},
		std::vector<hamon::uint8_t>{0xFF, 0xFF, 0xFF},
		std::vector<hamon::uint8_t>{0xFE, 0xFF, 0xFF, 0x01},
		false));
	EXPECT_TRUE(AddTest(
		std::vector<hamon::uint8_t>{0x07, 0xFF, 0x88, 0x50, 0x07},
		std::vector<hamon::uint8_t>{0x6B, 0x08, 0x39, 0xE6, 0x78, 0x02},
		std::vector<hamon::uint8_t>{0x72, 0x07, 0xC2, 0x36, 0x80, 0x02},
		false));
	EXPECT_TRUE(AddTest(
		std::vector<hamon::uint8_t>{0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
		std::vector<hamon::uint8_t>{0x01},
		std::vector<hamon::uint8_t>{0x00, 0x00, 0x00, 0x00, 0x00, 0x01},
		false));
	EXPECT_TRUE(AddTest(
		std::vector<hamon::uint16_t>{0},
		std::vector<hamon::uint16_t>{0},
		std::vector<hamon::uint16_t>{0},
		false));
	EXPECT_TRUE(AddTest(
		std::vector<hamon::uint16_t>{2},
		std::vector<hamon::uint16_t>{3},
		std::vector<hamon::uint16_t>{5},
		false));
	EXPECT_TRUE(AddTest(
		std::vector<hamon::uint16_t>{0xFF},
		std::vector<hamon::uint16_t>{0x03},
		std::vector<hamon::uint16_t>{0x0102},
		false));
	EXPECT_TRUE(AddTest(
		std::vector<hamon::uint16_t>{0xFFFF},
		std::vector<hamon::uint16_t>{0x0001},
		std::vector<hamon::uint16_t>{0x0000, 0x0001},
		false));
	EXPECT_TRUE(AddTest(
		std::vector<hamon::uint16_t>{0xFFFF, 0xFFFF},
		std::vector<hamon::uint16_t>{0xFFFF, 0xFFFF},
		std::vector<hamon::uint16_t>{0xFFFE, 0xFFFF, 0x0001},
		false));
	EXPECT_TRUE(AddTest(
		std::vector<hamon::uint16_t>{0xFF07, 0x5088},
		std::vector<hamon::uint16_t>{0x086B, 0xE639, 0x0278},
		std::vector<hamon::uint16_t>{0x0772, 0x36C2, 0x0279},
		false));
	EXPECT_TRUE(AddTest(
		std::vector<hamon::uint32_t>{0x5088FF07, 0x00000007},
		std::vector<hamon::uint32_t>{0xE639086B, 0x00000278},
		std::vector<hamon::uint32_t>{0x36C20772, 0x00000280},
		false));
	EXPECT_TRUE(AddTest(
		std::vector<hamon::uint32_t>{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF},
		std::vector<hamon::uint32_t>{0x01},
		std::vector<hamon::uint32_t>{0x00000000, 0x00000000, 0x00000000, 0x00000001},
		false));
	EXPECT_TRUE(AddTest(
		std::vector<hamon::uint32_t>{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF},
		std::vector<hamon::uint32_t>{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF},
		std::vector<hamon::uint32_t>{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000001},
		false));
	EXPECT_TRUE(AddTest(
		std::vector<hamon::uint64_t>{0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF},
		std::vector<hamon::uint64_t>{1},
		std::vector<hamon::uint64_t>{0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000001},
		false));
	EXPECT_TRUE(AddTest(
		std::vector<hamon::uint64_t>{0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF},
		std::vector<hamon::uint64_t>{0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF},
		std::vector<hamon::uint64_t>{0xFFFFFFFFFFFFFFFE, 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF, 0x0000000000000001},
		false));

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AddTest(
		hamon::array<hamon::uint8_t, 4>{0},
		hamon::array<hamon::uint8_t, 4>{0},
		hamon::array<hamon::uint8_t, 4>{0},
		false));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AddTest(
		hamon::array<hamon::uint8_t, 4>{1},
		hamon::array<hamon::uint8_t, 4>{2},
		hamon::array<hamon::uint8_t, 4>{3},
		false));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AddTest(
		hamon::array<hamon::uint8_t, 4>{0xff},
		hamon::array<hamon::uint8_t, 4>{0x01},
		hamon::array<hamon::uint8_t, 4>{0x00, 0x01},
		false));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AddTest(
		hamon::array<hamon::uint8_t, 4>{0x34, 0x12},
		hamon::array<hamon::uint8_t, 4>{0x01, 0x00},
		hamon::array<hamon::uint8_t, 4>{0x35, 0x12},
		false));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AddTest(
		hamon::array<hamon::uint8_t, 4>{0xFF, 0xFF},
		hamon::array<hamon::uint8_t, 4>{0x01, 0x00},
		hamon::array<hamon::uint8_t, 4>{0x00, 0x00, 0x01},
		false));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AddTest(
		hamon::array<hamon::uint8_t, 4>{0xFF, 0xFF},
		hamon::array<hamon::uint8_t, 4>{0xFF, 0xFF},
		hamon::array<hamon::uint8_t, 4>{0xFE, 0xFF, 0x01},
		false));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AddTest(
		hamon::array<hamon::uint8_t, 4>{0xFF, 0xFF, 0xFF, 0xFF},
		hamon::array<hamon::uint8_t, 4>{0xFF, 0xFF, 0xFF, 0xFF},
		hamon::array<hamon::uint8_t, 4>{0xFE, 0xFF, 0xFF, 0xFF},
		true));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AddTest(
		hamon::array<hamon::uint8_t, 4>{0x03, 0x00, 0x00, 0x00},
		hamon::array<hamon::uint8_t, 4>{0xFF, 0xFF, 0xFF, 0xFF},
		hamon::array<hamon::uint8_t, 4>{0x02, 0x00, 0x00, 0x00},
		true));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AddTest(
		hamon::array<hamon::uint8_t, 8>{0xFF, 0xFF, 0xFF, 0xFF},
		hamon::array<hamon::uint8_t, 8>{0xFF, 0xFF, 0xFF, 0xFF},
		hamon::array<hamon::uint8_t, 8>{0xFE, 0xFF, 0xFF, 0xFF, 0x01},
		false));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AddTest(
		hamon::array<hamon::uint8_t, 8>{0x07, 0xFF, 0x88, 0x50, 0x07, 0x00, 0x00, 0x00},
		hamon::array<hamon::uint8_t, 8>{0x6B, 0x08, 0x39, 0xE6, 0x78, 0x02, 0x00, 0x00},
		hamon::array<hamon::uint8_t, 8>{0x72, 0x07, 0xC2, 0x36, 0x80, 0x02, 0x00, 0x00},
		false));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AddTest(
		hamon::array<hamon::uint16_t, 4>{0},
		hamon::array<hamon::uint16_t, 4>{0},
		hamon::array<hamon::uint16_t, 4>{0},
		false));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AddTest(
		hamon::array<hamon::uint16_t, 4>{1},
		hamon::array<hamon::uint16_t, 4>{2},
		hamon::array<hamon::uint16_t, 4>{3},
		false));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AddTest(
		hamon::array<hamon::uint16_t, 4>{0x00ff},
		hamon::array<hamon::uint16_t, 4>{0x0001},
		hamon::array<hamon::uint16_t, 4>{0x0100},
		false));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AddTest(
		hamon::array<hamon::uint16_t, 4>{0xFFFF},
		hamon::array<hamon::uint16_t, 4>{0x0001},
		hamon::array<hamon::uint16_t, 4>{0x0000, 0x0001},
		false));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AddTest(
		hamon::array<hamon::uint16_t, 4>{0xFFFF},
		hamon::array<hamon::uint16_t, 4>{0xFFFF},
		hamon::array<hamon::uint16_t, 4>{0xFFFE, 0x0001},
		false));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AddTest(
		hamon::array<hamon::uint16_t, 4>{0x5678, 0x1234},
		hamon::array<hamon::uint16_t, 4>{0x0001, 0x0000},
		hamon::array<hamon::uint16_t, 4>{0x5679, 0x1234},
		false));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AddTest(
		hamon::array<hamon::uint16_t, 4>{0xFFFF, 0xFFFF, 0xFFFF},
		hamon::array<hamon::uint16_t, 4>{0x0001, 0x0000, 0x0000},
		hamon::array<hamon::uint16_t, 4>{0x0000, 0x0000, 0x0000, 0x0001},
		false));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AddTest(
		hamon::array<hamon::uint16_t, 4>{0xFFFF, 0xFFFF, 0xFFFF},
		hamon::array<hamon::uint16_t, 4>{0xFFFF, 0xFFFF, 0xFFFF},
		hamon::array<hamon::uint16_t, 4>{0xFFFE, 0xFFFF, 0xFFFF, 0x0001},
		false));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AddTest(
		hamon::array<hamon::uint16_t, 4>{0x4996, 0x02D2},
		hamon::array<hamon::uint16_t, 4>{0x4711, 0x0008},
		hamon::array<hamon::uint16_t, 4>{0x90A7, 0x02DA},
		false));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AddTest(
		hamon::array<hamon::uint16_t, 4>{0xFF07, 0x5088, 0x0007, 0x0000},
		hamon::array<hamon::uint16_t, 4>{0x086B, 0xE639, 0x0278, 0x0000},
		hamon::array<hamon::uint16_t, 4>{0x0772, 0x36C2, 0x0280},
		false));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AddTest(
		hamon::array<hamon::uint16_t, 4>{0x0002, 0x0000, 0x0000, 0x0000},
		hamon::array<hamon::uint16_t, 4>{0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF},
		hamon::array<hamon::uint16_t, 4>{0x0001, 0x0000, 0x0000, 0x0000},
		true));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AddTest(
		hamon::array<hamon::uint32_t, 4>{0x499602D2},
		hamon::array<hamon::uint32_t, 4>{0x47110008},
		hamon::array<hamon::uint32_t, 4>{0x90A702DA},
		false));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AddTest(
		hamon::array<hamon::uint32_t, 4>{0x5088FF07, 0x00000007},
		hamon::array<hamon::uint32_t, 4>{0xE639086B, 0x00000278},
		hamon::array<hamon::uint32_t, 4>{0x36C20772, 0x00000280},
		false));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AddTest(
		hamon::array<hamon::uint32_t, 4>{0x00000001},
		hamon::array<hamon::uint32_t, 4>{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0FFFFFFF},
		hamon::array<hamon::uint32_t, 4>{0x00000000, 0x00000000, 0x00000000, 0x10000000},
		false));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AddTest(
		hamon::array<hamon::uint32_t, 4>{0x00000001},
		hamon::array<hamon::uint32_t, 4>{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF},
		hamon::array<hamon::uint32_t, 4>{0x00000000, 0x00000000, 0x00000000, 0x00000000},
		true));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AddTest(
		hamon::array<hamon::uint64_t, 3>{0x000000075088FF07},
		hamon::array<hamon::uint64_t, 3>{0x00000278E639086B},
		hamon::array<hamon::uint64_t, 3>{0x0000028036C20772},
		false));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AddTest(
		hamon::array<hamon::uint64_t, 3>{0x0000000000000001},
		hamon::array<hamon::uint64_t, 3>{0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF, 0x1FFFFFFFFFFFFFFF},
		hamon::array<hamon::uint64_t, 3>{0x0000000000000000, 0x0000000000000000, 0x2000000000000000},
		false));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AddTest(
		hamon::array<hamon::uint64_t, 3>{0x0000000000000001},
		hamon::array<hamon::uint64_t, 3>{0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF},
		hamon::array<hamon::uint64_t, 3>{0x0000000000000000, 0x0000000000000000, 0x0000000000000000},
		true));
}

}	// namespace bigint_algo_add_test

}	// namespace hamon_bigint_test
