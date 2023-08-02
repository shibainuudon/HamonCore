/**
 *	@file	unit_test_bigint_algo_is_zero.cpp
 *
 *	@brief	bigint_algo::is_zero のテスト
 */

#include <hamon/bigint/bigint_algo/is_zero.hpp>
#include <hamon/array.hpp>
#include <hamon/cstdint.hpp>
#include <gtest/gtest.h>
#include <vector>
#include "constexpr_test.hpp"

GTEST_TEST(BigIntAlgoTest, IsZeroTest)
{
	{
		using VectorType = std::vector<hamon::uint8_t>;
		EXPECT_EQ(true,  hamon::bigint_algo::is_zero(VectorType{0x00}));
		EXPECT_EQ(false, hamon::bigint_algo::is_zero(VectorType{0x01}));
		EXPECT_EQ(false, hamon::bigint_algo::is_zero(VectorType{0x00, 0x01}));
		EXPECT_EQ(false, hamon::bigint_algo::is_zero(VectorType{0x00, 0x00, 0x01}));
		EXPECT_EQ(false, hamon::bigint_algo::is_zero(VectorType{0xFF, 0xFF, 0xFF}));
	}
	{
		using VectorType = std::vector<hamon::uint16_t>;
		EXPECT_EQ(true,  hamon::bigint_algo::is_zero(VectorType{0x0000}));
		EXPECT_EQ(false, hamon::bigint_algo::is_zero(VectorType{0x0001}));
		EXPECT_EQ(false, hamon::bigint_algo::is_zero(VectorType{0x0000, 0x0001}));
		EXPECT_EQ(false, hamon::bigint_algo::is_zero(VectorType{0x0000, 0x0000, 0x0001}));
		EXPECT_EQ(false, hamon::bigint_algo::is_zero(VectorType{0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF}));
	}
	{
		using VectorType = std::vector<hamon::uint32_t>;
		EXPECT_EQ(true,  hamon::bigint_algo::is_zero(VectorType{0x00000000}));
		EXPECT_EQ(false, hamon::bigint_algo::is_zero(VectorType{0x00000002}));
		EXPECT_EQ(false, hamon::bigint_algo::is_zero(VectorType{0x00000000, 0xFFFFFFFF}));
		EXPECT_EQ(false, hamon::bigint_algo::is_zero(VectorType{0x00000000, 0x00000000, 0x00000001}));
		EXPECT_EQ(false, hamon::bigint_algo::is_zero(VectorType{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}));
	}
	{
		using VectorType = std::vector<hamon::uint64_t>;
		EXPECT_EQ(true,  hamon::bigint_algo::is_zero(VectorType{0}));
		EXPECT_EQ(false, hamon::bigint_algo::is_zero(VectorType{1}));
		EXPECT_EQ(false, hamon::bigint_algo::is_zero(VectorType{0, 1}));
		EXPECT_EQ(false, hamon::bigint_algo::is_zero(VectorType{0, 0, 1}));
	}

	{
		using VectorType = hamon::array<hamon::uint8_t, 4>;
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(true,  hamon::bigint_algo::is_zero(VectorType{0x00}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(false, hamon::bigint_algo::is_zero(VectorType{0x01}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(false, hamon::bigint_algo::is_zero(VectorType{0x00, 0x01}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(false, hamon::bigint_algo::is_zero(VectorType{0x00, 0x00, 0x01}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(false, hamon::bigint_algo::is_zero(VectorType{0xFF, 0xFF, 0xFF}));
	}
	{
		using VectorType = hamon::array<hamon::uint16_t, 5>;
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(true,  hamon::bigint_algo::is_zero(VectorType{0x0000}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(false, hamon::bigint_algo::is_zero(VectorType{0x0001}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(false, hamon::bigint_algo::is_zero(VectorType{0x0000, 0x0001}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(false, hamon::bigint_algo::is_zero(VectorType{0x0000, 0x0000, 0x0001}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(false, hamon::bigint_algo::is_zero(VectorType{0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF}));
	}
	{
		using VectorType = hamon::array<hamon::uint32_t, 3>;
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(true,  hamon::bigint_algo::is_zero(VectorType{0x00000000}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(false, hamon::bigint_algo::is_zero(VectorType{0x00000002}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(false, hamon::bigint_algo::is_zero(VectorType{0x00000000, 0xFFFFFFFF}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(false, hamon::bigint_algo::is_zero(VectorType{0x00000000, 0x00000000, 0x00000001}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(false, hamon::bigint_algo::is_zero(VectorType{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}));
	}
	{
		using VectorType = hamon::array<hamon::uint64_t, 4>;
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(true,  hamon::bigint_algo::is_zero(VectorType{0}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(false, hamon::bigint_algo::is_zero(VectorType{1}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(false, hamon::bigint_algo::is_zero(VectorType{0, 1}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(false, hamon::bigint_algo::is_zero(VectorType{0, 0, 1}));
	}
}
