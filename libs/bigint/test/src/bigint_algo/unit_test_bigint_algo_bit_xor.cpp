/**
 *	@file	unit_test_bigint_algo_bit_xor.cpp
 *
 *	@brief	bigint_algo::bit_xor のテスト
 */

#include <hamon/bigint/bigint_algo/bit_xor.hpp>
#include <hamon/array.hpp>
#include <hamon/cstdint.hpp>
#include <gtest/gtest.h>
#include <vector>
#include "constexpr_test.hpp"

GTEST_TEST(BigIntAlgoTest, BitXOrTest)
{
	{
		std::vector<hamon::uint8_t> const a{0};
		std::vector<hamon::uint8_t> const b{0};
		auto const c1 = hamon::detail::bigint_algo::bit_xor(a, b);
		auto const c2 = hamon::detail::bigint_algo::bit_xor(b, a);
		std::vector<hamon::uint8_t> const expected{0};
		EXPECT_EQ(c1, expected);
		EXPECT_EQ(c2, expected);
	}
	{
		std::vector<hamon::uint8_t> const a{0x12, 0x34, 0x56, 0x78};
		std::vector<hamon::uint8_t> const b{0xFF, 0xFF, 0xFF};
		auto const c1 = hamon::detail::bigint_algo::bit_xor(a, b);
		auto const c2 = hamon::detail::bigint_algo::bit_xor(b, a);
		std::vector<hamon::uint8_t> const expected{0xED, 0xCB, 0xA9, 0x78};
		EXPECT_EQ(c1, expected);
		EXPECT_EQ(c2, expected);
	}
	{
		std::vector<hamon::uint8_t> const a{0x12, 0x34, 0x56, 0x78};
		std::vector<hamon::uint8_t> const b{0xFF, 0x0F, 0xF0, 0xFF, 0x00};
		auto const c1 = hamon::detail::bigint_algo::bit_xor(a, b);
		auto const c2 = hamon::detail::bigint_algo::bit_xor(b, a);
		std::vector<hamon::uint8_t> const expected{0xED, 0x3B, 0xA6, 0x87};
		EXPECT_EQ(c1, expected);
		EXPECT_EQ(c2, expected);
	}

	{
		HAMON_CXX11_CONSTEXPR hamon::array<hamon::uint8_t, 4> const a{0x12, 0x34, 0x56, 0x78};
		HAMON_CXX11_CONSTEXPR hamon::array<hamon::uint8_t, 4> const b{0xFF, 0xFF, 0xFF, 0xFF};
		HAMON_CXX11_CONSTEXPR auto const c = hamon::detail::bigint_algo::bit_xor(a, b);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0xEDu, c[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0xCBu, c[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0xA9u, c[2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x87u, c[3]);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::array<hamon::uint8_t, 4> const a{0x12, 0x34, 0x56, 0x78};
		HAMON_CXX11_CONSTEXPR hamon::array<hamon::uint8_t, 4> const b{0x00, 0x00, 0x00, 0x00};
		HAMON_CXX11_CONSTEXPR auto const c = hamon::detail::bigint_algo::bit_xor(a, b);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x12u, c[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x34u, c[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x56u, c[2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x78u, c[3]);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::array<hamon::uint8_t, 2> const a{0xCB, 0xE1};
		HAMON_CXX11_CONSTEXPR hamon::array<hamon::uint8_t, 2> const b{0xFA, 0x0F};
		HAMON_CXX11_CONSTEXPR auto const c = hamon::detail::bigint_algo::bit_xor(a, b);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x31u, c[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0xEEu, c[1]);
	}

	{
		HAMON_CXX11_CONSTEXPR hamon::array<hamon::uint16_t, 2> const a{0x4996, 0x02D2};
		HAMON_CXX11_CONSTEXPR hamon::array<hamon::uint16_t, 2> const b{0x12B9, 0xB0A1};
		HAMON_CXX11_CONSTEXPR auto const c = hamon::detail::bigint_algo::bit_xor(a, b);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x5B2Fu, c[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0xB273u, c[1]);
	}

	{
		HAMON_CXX11_CONSTEXPR hamon::array<hamon::uint32_t, 3> const a{0};
		HAMON_CXX11_CONSTEXPR hamon::array<hamon::uint32_t, 3> const b{0};
		HAMON_CXX11_CONSTEXPR auto const c = hamon::detail::bigint_algo::bit_xor(a, b);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x00000000u, c[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x00000000u, c[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x00000000u, c[2]);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::array<hamon::uint32_t, 3> const a{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF};
		HAMON_CXX11_CONSTEXPR hamon::array<hamon::uint32_t, 3> const b{0xFFFF0000, 0xFF00FF00, 0xF0F0F0F0};
		HAMON_CXX11_CONSTEXPR auto const c = hamon::detail::bigint_algo::bit_xor(a, b);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x0000FFFFu, c[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x00FF00FFu, c[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x0F0F0F0Fu, c[2]);
	}
}
