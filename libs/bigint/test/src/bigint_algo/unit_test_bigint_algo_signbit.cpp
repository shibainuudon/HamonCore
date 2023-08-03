/**
 *	@file	unit_test_bigint_algo_signbit.cpp
 *
 *	@brief	bigint_algo::signbit のテスト
 */

#include <hamon/bigint/bigint_algo/signbit.hpp>
#include <hamon/array.hpp>
#include <hamon/cstdint.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

GTEST_TEST(BigIntAlgoTest, SignbitTest)
{
	using hamon::bigint_algo::signbit;

	{
		using Vector = hamon::array<hamon::uint8_t, 4>;
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true,  signbit(Vector{0xFF, 0xFF, 0xFF, 0xFF}));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, signbit(Vector{0xFF, 0xFF, 0xFF, 0x7F}));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, signbit(Vector{0xFF, 0xFF, 0xFF, 0x00}));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, signbit(Vector{0x00, 0x00, 0x00, 0x00}));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true,  signbit(Vector{0x00, 0x00, 0x00, 0x80}));
	}
	{
		using Vector = hamon::array<hamon::uint16_t, 3>;
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true,  signbit(Vector{0xFFFF, 0xFFFF, 0xFFFF}));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, signbit(Vector{0xFFFF, 0xFFFF, 0x7FFF}));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, signbit(Vector{0xFFFF, 0xFFFF, 0x0000}));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, signbit(Vector{0x0000, 0x0000, 0x0000}));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true,  signbit(Vector{0x0000, 0x0000, 0x8000}));
	}
	{
		using Vector = hamon::array<hamon::uint32_t, 1>;
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true,  signbit(Vector{0xFFFF0000}));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, signbit(Vector{0x7FFF0000}));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, signbit(Vector{0x01234567}));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, signbit(Vector{0x00000000}));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true,  signbit(Vector{0x80000000}));
	}
	{
		using Vector = hamon::array<hamon::uint64_t, 2>;
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true,  signbit(Vector{0x0000000000000000, 0xFFFF000000000000}));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, signbit(Vector{0x0000000000000000, 0x7FFF000000000000}));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, signbit(Vector{0x0000000000000000, 0x0123456700000000}));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, signbit(Vector{0x0000000000000000, 0x0000000000000000}));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true,  signbit(Vector{0x0000000000000000, 0x8000000000000000}));
	}
}
