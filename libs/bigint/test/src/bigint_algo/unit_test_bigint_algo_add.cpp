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

GTEST_TEST(BigIntAlgoTest, AddTest)
{
	{
		std::vector<hamon::uint8_t> const a{0};
		std::vector<hamon::uint8_t> const b{0};
		auto const c1 = hamon::detail::bigint_algo::add(a, b);
		auto const c2 = hamon::detail::bigint_algo::add(b, a);
		std::vector<hamon::uint8_t> const expected{0};
		EXPECT_EQ(c1, expected);
		EXPECT_EQ(c2, expected);
	}
	{
		std::vector<hamon::uint8_t> const a{3};
		std::vector<hamon::uint8_t> const b{2};
		auto const c1 = hamon::detail::bigint_algo::add(a, b);
		auto const c2 = hamon::detail::bigint_algo::add(b, a);
		std::vector<hamon::uint8_t> const expected{5};
		EXPECT_EQ(c1, expected);
		EXPECT_EQ(c2, expected);
	}
	{
		std::vector<hamon::uint8_t> const a{0xFF};
		std::vector<hamon::uint8_t> const b{3};
		auto const c1 = hamon::detail::bigint_algo::add(a, b);
		auto const c2 = hamon::detail::bigint_algo::add(b, a);
		std::vector<hamon::uint8_t> const expected{0x02, 0x01};
		EXPECT_EQ(c1, expected);
		EXPECT_EQ(c2, expected);
	}
	{
		std::vector<hamon::uint8_t> const a{0x04};
		std::vector<hamon::uint8_t> const b{0xFE};
		auto const c1 = hamon::detail::bigint_algo::add(a, b);
		auto const c2 = hamon::detail::bigint_algo::add(b, a);
		std::vector<hamon::uint8_t> const expected{0x02, 0x01};
		EXPECT_EQ(c1, expected);
		EXPECT_EQ(c2, expected);
	}
	{
		std::vector<hamon::uint8_t> const a{0xFF, 0xFF, 0xFF};
		std::vector<hamon::uint8_t> const b{0xFF, 0xFF, 0xFF};
		auto const c1 = hamon::detail::bigint_algo::add(a, b);
		auto const c2 = hamon::detail::bigint_algo::add(b, a);
		std::vector<hamon::uint8_t> const expected{0xFE, 0xFF, 0xFF, 0x01};
		EXPECT_EQ(c1, expected);
		EXPECT_EQ(c2, expected);
	}
	{
		std::vector<hamon::uint8_t> const a{0x07, 0xFF, 0x88, 0x50, 0x07};
		std::vector<hamon::uint8_t> const b{0x6B, 0x08, 0x39, 0xE6, 0x78, 0x02};
		auto const c1 = hamon::detail::bigint_algo::add(a, b);
		auto const c2 = hamon::detail::bigint_algo::add(b, a);
		std::vector<hamon::uint8_t> const expected{0x72, 0x07, 0xC2, 0x36, 0x80, 0x02};
		EXPECT_EQ(c1, expected);
		EXPECT_EQ(c2, expected);
	}
	{
		std::vector<hamon::uint8_t> const a{0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
		std::vector<hamon::uint8_t> const b{0x01};
		auto const c1 = hamon::detail::bigint_algo::add(a, b);
		auto const c2 = hamon::detail::bigint_algo::add(b, a);
		std::vector<hamon::uint8_t> const expected{0x00, 0x00, 0x00, 0x00, 0x00, 0x01};
		EXPECT_EQ(c1, expected);
		EXPECT_EQ(c2, expected);
	}
	{
		std::vector<hamon::uint16_t> const a{3};
		std::vector<hamon::uint16_t> const b{2};
		auto const c1 = hamon::detail::bigint_algo::add(a, b);
		auto const c2 = hamon::detail::bigint_algo::add(b, a);
		std::vector<hamon::uint16_t> const expected{5};
		EXPECT_EQ(c1, expected);
		EXPECT_EQ(c2, expected);
	}
	{
		std::vector<hamon::uint16_t> const a{0xFF};
		std::vector<hamon::uint16_t> const b{3};
		auto const c1 = hamon::detail::bigint_algo::add(a, b);
		auto const c2 = hamon::detail::bigint_algo::add(b, a);
		std::vector<hamon::uint16_t> const expected{0x0102};
		EXPECT_EQ(c1, expected);
		EXPECT_EQ(c2, expected);
	}
	{
		std::vector<hamon::uint16_t> const a{0xFFFF};
		std::vector<hamon::uint16_t> const b{1};
		auto const c1 = hamon::detail::bigint_algo::add(a, b);
		auto const c2 = hamon::detail::bigint_algo::add(b, a);
		std::vector<hamon::uint16_t> const expected{0x0000, 0x0001};
		EXPECT_EQ(c1, expected);
		EXPECT_EQ(c2, expected);
	}
	{
		std::vector<hamon::uint16_t> const a{0xFFFF, 0xFFFF};
		std::vector<hamon::uint16_t> const b{0xFFFF, 0xFFFF};
		auto const c1 = hamon::detail::bigint_algo::add(a, b);
		auto const c2 = hamon::detail::bigint_algo::add(b, a);
		std::vector<hamon::uint16_t> const expected{0xFFFE, 0xFFFF, 0x0001};
		EXPECT_EQ(c1, expected);
		EXPECT_EQ(c2, expected);
	}
	{
		std::vector<hamon::uint16_t> const a{0xFF07, 0x5088};
		std::vector<hamon::uint16_t> const b{0x086B, 0xE639, 0x0278};
		auto const c1 = hamon::detail::bigint_algo::add(a, b);
		auto const c2 = hamon::detail::bigint_algo::add(b, a);
		std::vector<hamon::uint16_t> const expected{0x0772, 0x36C2, 0x0279};
		EXPECT_EQ(c1, expected);
		EXPECT_EQ(c2, expected);
	}
	{
		std::vector<hamon::uint32_t> const a{0x5088FF07, 0x00000007};
		std::vector<hamon::uint32_t> const b{0xE639086B, 0x00000278};
		auto const c1 = hamon::detail::bigint_algo::add(a, b);
		auto const c2 = hamon::detail::bigint_algo::add(b, a);
		std::vector<hamon::uint32_t> const expected{0x36C20772, 0x00000280};
		EXPECT_EQ(c1, expected);
		EXPECT_EQ(c2, expected);
	}
	{
		std::vector<hamon::uint32_t> const a{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF};
		std::vector<hamon::uint32_t> const b{1};
		auto const c1 = hamon::detail::bigint_algo::add(a, b);
		auto const c2 = hamon::detail::bigint_algo::add(b, a);
		std::vector<hamon::uint32_t> const expected{0x00000000, 0x00000000, 0x00000000, 0x00000001};
		EXPECT_EQ(c1, expected);
		EXPECT_EQ(c2, expected);
	}
	{
		std::vector<hamon::uint64_t> const a{0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF};
		std::vector<hamon::uint64_t> const b{1};
		auto const c1 = hamon::detail::bigint_algo::add(a, b);
		auto const c2 = hamon::detail::bigint_algo::add(b, a);
		std::vector<hamon::uint64_t> const expected{0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000001};
		EXPECT_EQ(c1, expected);
		EXPECT_EQ(c2, expected);
	}
	{
		std::vector<hamon::uint64_t> const a{0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF};
		std::vector<hamon::uint64_t> const b{0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF};
		auto const c1 = hamon::detail::bigint_algo::add(a, b);
		auto const c2 = hamon::detail::bigint_algo::add(b, a);
		std::vector<hamon::uint64_t> const expected{0xFFFFFFFFFFFFFFFE, 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF, 0x0000000000000001};
		EXPECT_EQ(c1, expected);
		EXPECT_EQ(c2, expected);
	}

	{
		HAMON_CXX11_CONSTEXPR hamon::array<hamon::uint8_t, 4> a{};
		HAMON_CXX11_CONSTEXPR hamon::array<hamon::uint8_t, 4> b{};
		HAMON_CXX11_CONSTEXPR auto c = hamon::detail::bigint_algo::add(a, b);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x00u, c[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x00u, c[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x00u, c[2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x00u, c[3]);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::array<hamon::uint8_t, 4> a{1};
		HAMON_CXX11_CONSTEXPR hamon::array<hamon::uint8_t, 4> b{2};
		HAMON_CXX11_CONSTEXPR auto c = hamon::detail::bigint_algo::add(a, b);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x03u, c[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x00u, c[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x00u, c[2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x00u, c[3]);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::array<hamon::uint8_t, 4> a{0xff};
		HAMON_CXX11_CONSTEXPR hamon::array<hamon::uint8_t, 4> b{0x01};
		HAMON_CXX11_CONSTEXPR auto c = hamon::detail::bigint_algo::add(a, b);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x00u, c[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x01u, c[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x00u, c[2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x00u, c[3]);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::array<hamon::uint8_t, 4> a{0x34, 0x12};
		HAMON_CXX11_CONSTEXPR hamon::array<hamon::uint8_t, 4> b{0x01, 0x00};
		HAMON_CXX11_CONSTEXPR auto c = hamon::detail::bigint_algo::add(a, b);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x35u, c[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x12u, c[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x00u, c[2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x00u, c[3]);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::array<hamon::uint8_t, 8> a{0x07, 0xFF, 0x88, 0x50, 0x07, 0x00, 0x00, 0x00};
		HAMON_CXX11_CONSTEXPR hamon::array<hamon::uint8_t, 8> b{0x6B, 0x08, 0x39, 0xE6, 0x78, 0x02, 0x00, 0x00};
		HAMON_CXX11_CONSTEXPR auto c = hamon::detail::bigint_algo::add(a, b);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x72u, c[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x07u, c[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0xC2u, c[2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x36u, c[3]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x80u, c[4]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x02u, c[5]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x00u, c[6]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x00u, c[7]);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::array<hamon::uint8_t, 4> a{0xFF, 0xFF};
		HAMON_CXX11_CONSTEXPR hamon::array<hamon::uint8_t, 4> b{0x01, 0x00};
		HAMON_CXX11_CONSTEXPR auto c = hamon::detail::bigint_algo::add(a, b);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x00u, c[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x00u, c[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x01u, c[2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x00u, c[3]);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::array<hamon::uint8_t, 4> a{0xFF, 0xFF};
		HAMON_CXX11_CONSTEXPR hamon::array<hamon::uint8_t, 4> b{0xFF, 0xFF};
		HAMON_CXX11_CONSTEXPR auto c = hamon::detail::bigint_algo::add(a, b);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0xFEu, c[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0xFFu, c[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x01u, c[2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x00u, c[3]);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::array<hamon::uint8_t, 4> a{0xFF, 0xFF, 0xFF, 0xFF};
		HAMON_CXX11_CONSTEXPR hamon::array<hamon::uint8_t, 4> b{0xFF, 0xFF, 0xFF, 0xFF};
		HAMON_CXX11_CONSTEXPR auto c = hamon::detail::bigint_algo::add(a, b);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0xFEu, c[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0xFFu, c[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0xFFu, c[2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0xFFu, c[3]);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::array<hamon::uint8_t, 4> a{0x03, 0x00, 0x00, 0x00};
		HAMON_CXX11_CONSTEXPR hamon::array<hamon::uint8_t, 4> b{0xFF, 0xFF, 0xFF, 0xFF};
		HAMON_CXX11_CONSTEXPR auto c = hamon::detail::bigint_algo::add(a, b);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x02u, c[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x00u, c[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x00u, c[2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x00u, c[3]);
	}


	{
		HAMON_CXX11_CONSTEXPR hamon::array<hamon::uint16_t, 4> a{};
		HAMON_CXX11_CONSTEXPR hamon::array<hamon::uint16_t, 4> b{};
		HAMON_CXX11_CONSTEXPR auto c = hamon::detail::bigint_algo::add(a, b);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x0000u, c[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x0000u, c[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x0000u, c[2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x0000u, c[3]);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::array<hamon::uint16_t, 4> a{1};
		HAMON_CXX11_CONSTEXPR hamon::array<hamon::uint16_t, 4> b{2};
		HAMON_CXX11_CONSTEXPR auto c = hamon::detail::bigint_algo::add(a, b);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x0003u, c[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x0000u, c[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x0000u, c[2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x0000u, c[3]);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::array<hamon::uint16_t, 4> a{0x00FF};
		HAMON_CXX11_CONSTEXPR hamon::array<hamon::uint16_t, 4> b{0x0001};
		HAMON_CXX11_CONSTEXPR auto c = hamon::detail::bigint_algo::add(a, b);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x0100u, c[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x0000u, c[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x0000u, c[2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x0000u, c[3]);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::array<hamon::uint16_t, 4> a{0xFFFF};
		HAMON_CXX11_CONSTEXPR hamon::array<hamon::uint16_t, 4> b{0x0001};
		HAMON_CXX11_CONSTEXPR auto c = hamon::detail::bigint_algo::add(a, b);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x0000u, c[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x0001u, c[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x0000u, c[2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x0000u, c[3]);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::array<hamon::uint16_t, 4> a{0xFFFF};
		HAMON_CXX11_CONSTEXPR hamon::array<hamon::uint16_t, 4> b{0xFFFF};
		HAMON_CXX11_CONSTEXPR auto c = hamon::detail::bigint_algo::add(a, b);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0xFFFEu, c[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x0001u, c[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x0000u, c[2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x0000u, c[3]);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::array<hamon::uint16_t, 4> a{0x5678, 0x1234};
		HAMON_CXX11_CONSTEXPR hamon::array<hamon::uint16_t, 4> b{0x0001, 0x0000};
		HAMON_CXX11_CONSTEXPR auto c = hamon::detail::bigint_algo::add(a, b);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x5679u, c[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x1234u, c[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x0000u, c[2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x0000u, c[3]);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::array<hamon::uint16_t, 4> a{0xFFFF, 0xFFFF, 0xFFFF};
		HAMON_CXX11_CONSTEXPR hamon::array<hamon::uint16_t, 4> b{0x0001, 0x0000, 0x0000};
		HAMON_CXX11_CONSTEXPR auto c = hamon::detail::bigint_algo::add(a, b);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x0000u, c[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x0000u, c[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x0000u, c[2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x0001u, c[3]);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::array<hamon::uint16_t, 4> a{0xFF, 0xFF};
		HAMON_CXX11_CONSTEXPR hamon::array<hamon::uint16_t, 4> b{0xFF, 0xFF};
		HAMON_CXX11_CONSTEXPR auto c = hamon::detail::bigint_algo::add(a, b);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x01FEu, c[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x01FEu, c[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x0000u, c[2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x0000u, c[3]);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::array<hamon::uint16_t, 4> a{0xFFFF, 0xFFFF};
		HAMON_CXX11_CONSTEXPR hamon::array<hamon::uint16_t, 4> b{0xFFFF, 0xFFFF};
		HAMON_CXX11_CONSTEXPR auto c = hamon::detail::bigint_algo::add(a, b);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0xFFFEu, c[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0xFFFFu, c[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x0001u, c[2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x0000u, c[3]);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::array<hamon::uint16_t, 4> a{0x4996, 0x02D2};
		HAMON_CXX11_CONSTEXPR hamon::array<hamon::uint16_t, 4> b{0x4711, 0x0008};
		HAMON_CXX11_CONSTEXPR auto c = hamon::detail::bigint_algo::add(a, b);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x90A7u, c[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x02DAu, c[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x0000u, c[2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x0000u, c[3]);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::array<hamon::uint16_t, 5> a{0xFF07, 0x5088, 0x0007, 0x0000, 0x0000};
		HAMON_CXX11_CONSTEXPR hamon::array<hamon::uint16_t, 5> b{0x086B, 0xE639, 0x0278, 0x0000, 0x0000};
		HAMON_CXX11_CONSTEXPR auto c = hamon::detail::bigint_algo::add(a, b);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x0772u, c[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x36C2u, c[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x0280u, c[2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x0000u, c[3]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x0000u, c[4]);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::array<hamon::uint16_t, 4> a{0x0002, 0x0000, 0x0000, 0x0000};
		HAMON_CXX11_CONSTEXPR hamon::array<hamon::uint16_t, 4> b{0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF};
		HAMON_CXX11_CONSTEXPR auto c = hamon::detail::bigint_algo::add(a, b);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x0001u, c[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x0000u, c[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x0000u, c[2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x0000u, c[3]);
	}

	{
		HAMON_CXX11_CONSTEXPR hamon::array<hamon::uint32_t, 4> a{0x499602D2};
		HAMON_CXX11_CONSTEXPR hamon::array<hamon::uint32_t, 4> b{0x47110008};
		HAMON_CXX11_CONSTEXPR auto c = hamon::detail::bigint_algo::add(a, b);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x90A702DAu, c[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x00000000u, c[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x00000000u, c[2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x00000000u, c[3]);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::array<hamon::uint32_t, 3> a{0x5088FF07, 0x00000007, 0x00000000};
		HAMON_CXX11_CONSTEXPR hamon::array<hamon::uint32_t, 3> b{0xE639086B, 0x00000278, 0x00000000};
		HAMON_CXX11_CONSTEXPR auto c = hamon::detail::bigint_algo::add(a, b);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x36C20772u, c[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x00000280u, c[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x00000000u, c[2]);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::array<hamon::uint32_t, 3> a{0x00000001, 0x00000000, 0x00000000};
		HAMON_CXX11_CONSTEXPR hamon::array<hamon::uint32_t, 3> b{0xFFFFFFFF, 0xFFFFFFFF, 0x0FFFFFFF};
		HAMON_CXX11_CONSTEXPR auto c = hamon::detail::bigint_algo::add(a, b);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x00000000u, c[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x00000000u, c[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x10000000u, c[2]);
	}

	{
		HAMON_CXX11_CONSTEXPR hamon::array<hamon::uint64_t, 3> a{0x000000075088FF07, 0x0000000000000000, 0x0000000000000000};
		HAMON_CXX11_CONSTEXPR hamon::array<hamon::uint64_t, 3> b{0x00000278E639086B, 0x0000000000000000, 0x0000000000000000};
		HAMON_CXX11_CONSTEXPR auto c = hamon::detail::bigint_algo::add(a, b);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x0000028036C20772u, c[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x0000000000000000u, c[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x0000000000000000u, c[2]);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::array<hamon::uint64_t, 3> a{0x0000000000000001, 0x0000000000000000, 0x0000000000000000};
		HAMON_CXX11_CONSTEXPR hamon::array<hamon::uint64_t, 3> b{0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF, 0x1FFFFFFFFFFFFFFF};
		HAMON_CXX11_CONSTEXPR auto c = hamon::detail::bigint_algo::add(a, b);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x0000000000000000u, c[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x0000000000000000u, c[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x2000000000000000u, c[2]);
	}
}
