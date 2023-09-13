/**
 *	@file	unit_test_bigint_algo_bit_not.cpp
 *
 *	@brief	bigint_algo::bit_not のテスト
 */

#include <hamon/bigint/bigint_algo/bit_not.hpp>
#include <hamon/array.hpp>
#include <hamon/cstdint.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_bigint_test
{

namespace bigint_algo_bit_not_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename VectorType>
inline HAMON_CXX14_CONSTEXPR bool
BitNotTest(VectorType a, VectorType const& expected)
{
	hamon::bigint_algo::bit_not(a);
	VERIFY(a == expected);
	return true;
}

#undef VERIFY

GTEST_TEST(BigIntAlgoTest, BitNotTest)
{
#if 0
	{
		hamon::array<hamon::uint8_t, 8> a{0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC, 0xDE, 0xF0};
		for (hamon::size_t i = 0; i < 10000000; ++i)
		{
			hamon::bigint_algo::bit_not(a);
		}
	}
#endif

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(BitNotTest(
		hamon::array<hamon::uint8_t, 4>{0x12, 0x34, 0x56, 0x78},
		hamon::array<hamon::uint8_t, 4>{0xED, 0xCB, 0xA9, 0x87}));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(BitNotTest(
		hamon::array<hamon::uint16_t, 3>{0x1234, 0x5678, 0x9ABC},
		hamon::array<hamon::uint16_t, 3>{0xEDCB, 0xA987, 0x6543}));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(BitNotTest(
		hamon::array<hamon::uint32_t, 3>{0x12345678, 0x9ABCDEF0, 0x00000000},
		hamon::array<hamon::uint32_t, 3>{0xEDCBA987, 0x6543210F, 0xFFFFFFFF}));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(BitNotTest(
		hamon::array<hamon::uint64_t, 2>{0x123456789ABCDEF0, 0x0000000000000000},
		hamon::array<hamon::uint64_t, 2>{0xEDCBA9876543210F, 0xFFFFFFFFFFFFFFFF}));
}

}	// namespace bigint_algo_bit_not_test

}	// namespace hamon_bigint_test
