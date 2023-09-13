/**
 *	@file	unit_test_bigint_algo_multiply.cpp
 *
 *	@brief	bigint_algo::multiply のテスト
 */

#include <hamon/bigint/bigint_algo/multiply.hpp>
#include <hamon/array.hpp>
#include <hamon/cstdint.hpp>
#include <hamon/vector.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_bigint_test
{

namespace bigint_algo_multiply_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename VectorType>
inline HAMON_CXX14_CONSTEXPR bool
MultiplyTest(VectorType const& a, VectorType const& b, VectorType const& expected, bool overflow)
{
	// c = a * b
	{
		VectorType c{0};
		bool f = hamon::bigint_algo::multiply(c, a, b);
		VERIFY(c == expected);
		VERIFY(f == overflow);
	}
	// c = b * a
	{
		VectorType c{0};
		bool f = hamon::bigint_algo::multiply(c, b, a);
		VERIFY(c == expected);
		VERIFY(f == overflow);
	}
	return true;
}

#undef VERIFY

GTEST_TEST(BigIntAlgoTest, MultiplyTest)
{
#if 0
	{
		hamon::vector<hamon::uint8_t> a{0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC, 0xDE, 0xF0};
		hamon::vector<hamon::uint8_t> b{0xFE, 0xDC, 0xBA, 0x98, 0x76, 0x54};
		hamon::vector<hamon::uint8_t> c{};
		for (hamon::size_t i = 0; i < 100000; ++i)
		{
			hamon::bigint_algo::multiply(c, a, b);
		}
	}
	{
		hamon::array<hamon::uint8_t, 8> a{0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC, 0xDE, 0xF0};
		hamon::array<hamon::uint8_t, 8> b{0xFE, 0xDC, 0xBA, 0x98, 0x76, 0x54};
		hamon::array<hamon::uint8_t, 8> c{};
		for (hamon::size_t i = 0; i < 100000; ++i)
		{
			hamon::bigint_algo::multiply(c, a, b);
		}
	}
#endif

	EXPECT_TRUE(MultiplyTest(
		hamon::vector<hamon::uint8_t>{0},
		hamon::vector<hamon::uint8_t>{0},
		hamon::vector<hamon::uint8_t>{0},
		false));
	EXPECT_TRUE(MultiplyTest(
		hamon::vector<hamon::uint8_t>{2},
		hamon::vector<hamon::uint8_t>{3},
		hamon::vector<hamon::uint8_t>{6},
		false));
	EXPECT_TRUE(MultiplyTest(
		hamon::vector<hamon::uint8_t>{123},
		hamon::vector<hamon::uint8_t>{45},
		hamon::vector<hamon::uint8_t>{0x9F, 0x15},	// 5535
		false));
	EXPECT_TRUE(MultiplyTest(
		hamon::vector<hamon::uint8_t>{0x20, 0x10},
		hamon::vector<hamon::uint8_t>{0x40, 0x30},
		hamon::vector<hamon::uint8_t>{0x00, 0x08, 0x0A, 0x03},
		false));
	EXPECT_TRUE(MultiplyTest(
		hamon::vector<hamon::uint8_t>{0xB1, 0x68, 0xDE, 0x3A},	// 987654321
		hamon::vector<hamon::uint8_t>{0x03},
		hamon::vector<hamon::uint8_t>{0x13, 0x3A, 0x9B, 0xB0},	// 2962962963
		false));
	EXPECT_TRUE(MultiplyTest(
		hamon::vector<hamon::uint8_t>{0x00},
		hamon::vector<hamon::uint8_t>{0x10, 0x20, 0x30},
		hamon::vector<hamon::uint8_t>{0x00},
		false));
	EXPECT_TRUE(MultiplyTest(
		hamon::vector<hamon::uint8_t>{0xFF, 0xFF, 0xFF, 0xFF},
		hamon::vector<hamon::uint8_t>{0x02},
		hamon::vector<hamon::uint8_t>{0xFE, 0xFF, 0xFF, 0xFF, 0x01},
		false));
	EXPECT_TRUE(MultiplyTest(
		hamon::vector<hamon::uint8_t>{0x07, 0xFF, 0x88, 0x50, 0x07},	// 31415926535
		hamon::vector<hamon::uint8_t>{0xEC, 0xE3, 0x38, 0x54, 0x06},	// 27182818284
		hamon::vector<hamon::uint8_t>{0x74, 0x4F, 0xF6, 0xCD, 0xF7, 0x0E, 0x43, 0x4B, 0x2E},	// 853973422224398765940
		false));
	EXPECT_TRUE(MultiplyTest(
		hamon::vector<hamon::uint16_t>{0xFF07, 0x5088, 0x0007},	// 31415926535
		hamon::vector<hamon::uint16_t>{0xE3EC, 0x5438, 0x0006},	// 27182818284
		hamon::vector<hamon::uint16_t>{0x4F74, 0xCDF6, 0x0EF7, 0x4B43, 0x002E},	// 853973422224398765940
		false));
	EXPECT_TRUE(MultiplyTest(
		hamon::vector<hamon::uint32_t>{0x5088FF07, 0x00000007},	// 31415926535
		hamon::vector<hamon::uint32_t>{0x5438E3EC, 0x00000006},	// 27182818284
		hamon::vector<hamon::uint32_t>{0xCDF64F74, 0x4B430EF7, 0x0000002E},	// 853973422224398765940
		false));
	EXPECT_TRUE(MultiplyTest(
		hamon::vector<hamon::uint64_t>{0x000000075088FF07},	// 31415926535
		hamon::vector<hamon::uint64_t>{0x000000065438E3EC},	// 27182818284
		hamon::vector<hamon::uint64_t>{0x4B430EF7CDF64F74, 0x000000000000002E},	// 853973422224398765940
		false));
	EXPECT_TRUE(MultiplyTest(
		hamon::vector<hamon::uint64_t>{0x07D5EB5B5BA4D7C6, 0x11},
		hamon::vector<hamon::uint64_t>{0x000000065438E3EC},
		hamon::vector<hamon::uint64_t>{0x84D22BFBD29B7C88, 0x6BC95E95CF},
		false));
	EXPECT_TRUE(MultiplyTest(
		hamon::vector<hamon::uint64_t>{0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF},
		hamon::vector<hamon::uint64_t>{0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF},
		hamon::vector<hamon::uint64_t>{0x0000000000000001, 0x0000000000000000, 0xFFFFFFFFFFFFFFFE, 0xFFFFFFFFFFFFFFFF},
		false));

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(MultiplyTest(
		hamon::array<hamon::uint8_t, 1>{0},
		hamon::array<hamon::uint8_t, 1>{0},
		hamon::array<hamon::uint8_t, 1>{0},
		false));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(MultiplyTest(
		hamon::array<hamon::uint8_t, 1>{2},
		hamon::array<hamon::uint8_t, 1>{3},
		hamon::array<hamon::uint8_t, 1>{6},
		false));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(MultiplyTest(
		hamon::array<hamon::uint8_t, 2>{123},
		hamon::array<hamon::uint8_t, 2>{45},
		hamon::array<hamon::uint8_t, 2>{0x9F, 0x15},
		false));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(MultiplyTest(
		hamon::array<hamon::uint8_t, 2>{0x20, 0x10},
		hamon::array<hamon::uint8_t, 2>{0x40, 0x30},
		hamon::array<hamon::uint8_t, 2>{0x00, 0x08},
		true));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(MultiplyTest(
		hamon::array<hamon::uint8_t, 4>{0x20, 0x10},
		hamon::array<hamon::uint8_t, 4>{0x40, 0x30},
		hamon::array<hamon::uint8_t, 4>{0x00, 0x08, 0x0A, 0x03},
		false));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(MultiplyTest(
		hamon::array<hamon::uint16_t, 4>{0x68B1, 0x3ADE},
		hamon::array<hamon::uint16_t, 4>{0x0003},
		hamon::array<hamon::uint16_t, 4>{0x3A13, 0xB09B},
		false));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(MultiplyTest(
		hamon::array<hamon::uint16_t, 4>{0xFF07, 0x5088, 0x0007},
		hamon::array<hamon::uint16_t, 4>{0xE3EC, 0x5438, 0x0006},
		hamon::array<hamon::uint16_t, 4>{0x4F74, 0xCDF6, 0x0EF7, 0x4B43},
		true));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(MultiplyTest(
		hamon::array<hamon::uint16_t, 5>{0xFF07, 0x5088, 0x0007},
		hamon::array<hamon::uint16_t, 5>{0xE3EC, 0x5438, 0x0006},
		hamon::array<hamon::uint16_t, 5>{0x4F74, 0xCDF6, 0x0EF7, 0x4B43, 0x002E},
		false));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(MultiplyTest(
		hamon::array<hamon::uint32_t, 4>{0x5088FF07, 0x00000007},
		hamon::array<hamon::uint32_t, 4>{0x5438E3EC, 0x00000006},
		hamon::array<hamon::uint32_t, 4>{0xCDF64F74, 0x4B430EF7, 0x0000002E},
		false));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(MultiplyTest(
		hamon::array<hamon::uint64_t, 2>{0x000000075088FF07},
		hamon::array<hamon::uint64_t, 2>{0x000000065438E3EC},
		hamon::array<hamon::uint64_t, 2>{0x4B430EF7CDF64F74, 0x000000000000002E},
		false));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(MultiplyTest(
		hamon::array<hamon::uint64_t, 3>{0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF},
		hamon::array<hamon::uint64_t, 3>{0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF},
		hamon::array<hamon::uint64_t, 3>{0x0000000000000001, 0x0000000000000000, 0xFFFFFFFFFFFFFFFE},
		true));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(MultiplyTest(
		hamon::array<hamon::uint64_t, 4>{0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF},
		hamon::array<hamon::uint64_t, 4>{0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF},
		hamon::array<hamon::uint64_t, 4>{0x0000000000000001, 0x0000000000000000, 0xFFFFFFFFFFFFFFFE, 0xFFFFFFFFFFFFFFFF},
		false));
}

}	// namespace bigint_algo_multiply_test

}	// namespace hamon_bigint_test
