/**
 *	@file	unit_test_bigint_algo_negate.cpp
 *
 *	@brief	bigint_algo::negate のテスト
 */

#include <hamon/bigint/bigint_algo/negate.hpp>
#include <hamon/array.hpp>
#include <hamon/cstdint.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_bigint_test
{

namespace bigint_algo_negate_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename VectorType>
inline HAMON_CXX14_CONSTEXPR bool
NegateTest(VectorType a, VectorType const& expected)
{
	hamon::bigint_algo::negate(a);
	VERIFY(a == expected);
	return true;
}

#undef VERIFY

GTEST_TEST(BigIntAlgoTest, NegateTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(NegateTest(
		hamon::array<hamon::uint8_t, 4>{0x00, 0x00, 0x00, 0x00},
		hamon::array<hamon::uint8_t, 4>{0x00, 0x00, 0x00, 0x00}));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(NegateTest(
		hamon::array<hamon::uint8_t, 4>{0x01, 0x00, 0x00, 0x00},
		hamon::array<hamon::uint8_t, 4>{0xFF, 0xFF, 0xFF, 0xFF}));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(NegateTest(
		hamon::array<hamon::uint8_t, 4>{0xFF, 0xFF, 0xFF, 0xFF},
		hamon::array<hamon::uint8_t, 4>{0x01, 0x00, 0x00, 0x00}));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(NegateTest(
		hamon::array<hamon::uint8_t, 4>{0x12, 0x34, 0x56, 0x78},
		hamon::array<hamon::uint8_t, 4>{0xEE, 0xCB, 0xA9, 0x87}));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(NegateTest(
		hamon::array<hamon::uint16_t, 3>{0x0002, 0x0000, 0x0000},
		hamon::array<hamon::uint16_t, 3>{0xFFFE, 0xFFFF, 0xFFFF}));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(NegateTest(
		hamon::array<hamon::uint16_t, 2>{0xFFFF, 0xFFFF},
		hamon::array<hamon::uint16_t, 2>{0x0001, 0x0000}));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(NegateTest(
		hamon::array<hamon::uint16_t, 3>{0x1234, 0x5678, 0x9ABC},
		hamon::array<hamon::uint16_t, 3>{0xEDCC, 0xA987, 0x6543}));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(NegateTest(
		hamon::array<hamon::uint32_t, 1>{0x00000000},
		hamon::array<hamon::uint32_t, 1>{0x00000000}));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(NegateTest(
		hamon::array<hamon::uint32_t, 3>{0x12345678, 0x9ABCDEF0, 0x00000000},
		hamon::array<hamon::uint32_t, 3>{0xEDCBA988, 0x6543210F, 0xFFFFFFFF}));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(NegateTest(
		hamon::array<hamon::uint64_t, 2>{0x123456789ABCDEF0, 0x0000000000000000},
		hamon::array<hamon::uint64_t, 2>{0xEDCBA98765432110, 0xFFFFFFFFFFFFFFFF}));
}

}	// namespace bigint_algo_negate_test

}	// namespace hamon_bigint_test
