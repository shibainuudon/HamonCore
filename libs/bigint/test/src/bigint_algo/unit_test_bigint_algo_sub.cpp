/**
 *	@file	unit_test_bigint_algo_sub.cpp
 *
 *	@brief	bigint_algo::sub のテスト
 */

#include <hamon/bigint/bigint_algo/sub.hpp>
#include <hamon/array.hpp>
#include <hamon/cstdint.hpp>
#include <gtest/gtest.h>
#include <vector>
#include "constexpr_test.hpp"

GTEST_TEST(BigIntAlgoTest, SubTest)
{
	{
		std::vector<hamon::uint8_t> const a{0x39, 0x30};	// 12345
		std::vector<hamon::uint8_t> const b{0x03};
		auto const c = hamon::bigint_algo::sub(a, b);
		std::vector<hamon::uint8_t> const expected{0x36, 0x30};	// 12342
		EXPECT_EQ(expected, c);
	}
	{
		std::vector<hamon::uint8_t> const a{0x00, 0x00, 0x01};
		std::vector<hamon::uint8_t> const b{0x01};
		auto const c = hamon::bigint_algo::sub(a, b);
		std::vector<hamon::uint8_t> const expected{0xFF, 0xFF};
		EXPECT_EQ(expected, c);
	}
	{
		std::vector<hamon::uint8_t> const a{0x56, 0x34, 0x12};
		std::vector<hamon::uint8_t> const b{0x89, 0x30, 0x12};
		auto const c = hamon::bigint_algo::sub(a, b);
		std::vector<hamon::uint8_t> const expected{0xCD, 0x03};
		EXPECT_EQ(expected, c);
	}
	{
		std::vector<hamon::uint8_t> const a{0x78, 0x56, 0x34, 0x12};
		std::vector<hamon::uint8_t> const b{0x78, 0x56, 0x34, 0x12};
		auto const c = hamon::bigint_algo::sub(a, b);
		std::vector<hamon::uint8_t> const expected{0x00};
		EXPECT_EQ(expected, c);
	}
	{
		std::vector<hamon::uint8_t> const a{0x15, 0x81, 0xE9, 0x7D, 0xF4, 0x10, 0x22, 0x11, 0x1E, 0x78, 0xBE, 0x41, 0x1D, 0x42, 0x70, 0x50};
		std::vector<hamon::uint8_t> const b{0xD0, 0x08, 0x51, 0xF2, 0x96, 0xFA, 0x5D, 0x0D, 0x81, 0x42, 0x21, 0x00, 0x28, 0x88, 0x24, 0x33};
		auto const c = hamon::bigint_algo::sub(a, b);
		std::vector<hamon::uint8_t> const expected{0x45, 0x78, 0x98, 0x8B, 0x5D, 0x16, 0xC4, 0x03, 0x9D, 0x35, 0x9D, 0x41, 0xF5, 0xB9, 0x4B, 0x1D};
		EXPECT_EQ(expected, c);
	}
	{
		std::vector<hamon::uint16_t> const a{0x0000, 0x0000, 0x0000, 0x0001};
		std::vector<hamon::uint16_t> const b{0x02};
		auto const c = hamon::bigint_algo::sub(a, b);
		std::vector<hamon::uint16_t> const expected{0xFFFE, 0xFFFF, 0xFFFF};
		EXPECT_EQ(expected, c);
	}
	{
		std::vector<hamon::uint16_t> const a{0xB0A1, 0x12B9};
		std::vector<hamon::uint16_t> const b{0x614E, 0x00BC};
		auto const c = hamon::bigint_algo::sub(a, b);
		std::vector<hamon::uint16_t> const expected{0x4F53, 0x11FD};
		EXPECT_EQ(expected, c);
	}
	{
		std::vector<hamon::uint16_t> const a{0x8115, 0x7DE9, 0x10F4, 0x1122, 0x781E, 0x41BE, 0x421D, 0x5070};
		std::vector<hamon::uint16_t> const b{0x08D0, 0xF251, 0xFA96, 0x0D5D, 0x4281, 0x0021, 0x8828, 0x3324};
		auto const c = hamon::bigint_algo::sub(a, b);
		std::vector<hamon::uint16_t> const expected{0x7845, 0x8B98, 0x165D, 0x03C4, 0x359D, 0x419D, 0xB9F5, 0x1D4B};
		EXPECT_EQ(expected, c);
	}
	{
		std::vector<hamon::uint32_t> const a{0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000010};
		std::vector<hamon::uint32_t> const b{0x00000000, 0x00000001};
		auto const c = hamon::bigint_algo::sub(a, b);
		std::vector<hamon::uint32_t> const expected{0x00000000, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0F};
		EXPECT_EQ(expected, c);
	}
	{
		std::vector<hamon::uint32_t> const a{0x7DE98115, 0x112210F4, 0x41BE781E, 0x5070421D};
		std::vector<hamon::uint32_t> const b{0xF25108D0, 0x0D5DFA96, 0x00214281, 0x33248828};
		auto const c = hamon::bigint_algo::sub(a, b);
		std::vector<hamon::uint32_t> const expected{0x8B987845, 0x03C4165D, 0x419D359D, 0x1D4BB9F5};
		EXPECT_EQ(expected, c);
	}
	{
		std::vector<hamon::uint64_t> const a{0x112210F47DE98115, 0x5070421D41BE781E};
		std::vector<hamon::uint64_t> const b{0x0D5DFA96F25108D0, 0x3324882800214281};
		auto const c = hamon::bigint_algo::sub(a, b);
		std::vector<hamon::uint64_t> const expected{0x03C4165D8B987845, 0x1D4BB9F5419D359D};
		EXPECT_EQ(expected, c);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::array<hamon::uint8_t, 4> a{0x00, 0x00, 0x00, 0xFF};
		HAMON_CXX11_CONSTEXPR hamon::array<hamon::uint8_t, 4> b{0x01};
		HAMON_CXX11_CONSTEXPR auto c = hamon::bigint_algo::sub(a, b);
		HAMON_CXX11_CONSTEXPR hamon::array<hamon::uint8_t, 4> expected{0xFF, 0xFF, 0xFF, 0xFE};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(expected, c);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::array<hamon::uint8_t, 4> a{0x02};
		HAMON_CXX11_CONSTEXPR hamon::array<hamon::uint8_t, 4> b{0x01};
		HAMON_CXX11_CONSTEXPR auto c = hamon::bigint_algo::sub(a, b);
		HAMON_CXX11_CONSTEXPR hamon::array<hamon::uint8_t, 4> expected{0x01, 0x00, 0x00, 0x00};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(expected, c);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::array<hamon::uint8_t, 4> a{0x01};
		HAMON_CXX11_CONSTEXPR hamon::array<hamon::uint8_t, 4> b{0x02};
		HAMON_CXX11_CONSTEXPR auto c = hamon::bigint_algo::sub(a, b);
		HAMON_CXX11_CONSTEXPR hamon::array<hamon::uint8_t, 4> expected{0xFF, 0xFF, 0xFF, 0xFF};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(expected, c);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::array<hamon::uint8_t, 16> a{0x15, 0x81, 0xE9, 0x7D, 0xF4, 0x10, 0x22, 0x11, 0x1E, 0x78, 0xBE, 0x41, 0x1D, 0x42, 0x70, 0x50};
		HAMON_CXX11_CONSTEXPR hamon::array<hamon::uint8_t, 16> b{0xD0, 0x08, 0x51, 0xF2, 0x96, 0xFA, 0x5D, 0x0D, 0x81, 0x42, 0x21, 0x00, 0x28, 0x88, 0x24, 0x33};
		HAMON_CXX11_CONSTEXPR auto c = hamon::bigint_algo::sub(a, b);
		HAMON_CXX11_CONSTEXPR hamon::array<hamon::uint8_t, 16> expected{0x45, 0x78, 0x98, 0x8B, 0x5D, 0x16, 0xC4, 0x03, 0x9D, 0x35, 0x9D, 0x41, 0xF5, 0xB9, 0x4B, 0x1D};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(expected, c);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::array<hamon::uint16_t, 3> a{0x1111, 0x1111, 0x1111};
		HAMON_CXX11_CONSTEXPR hamon::array<hamon::uint16_t, 3> b{0x0987, 0x6543, 0x0020};
		HAMON_CXX11_CONSTEXPR auto c = hamon::bigint_algo::sub(a, b);
		HAMON_CXX11_CONSTEXPR hamon::array<hamon::uint16_t, 3> expected{0x078A, 0xABCE, 0x10F0};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(expected, c);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::array<hamon::uint16_t, 8> a{0x8115, 0x7DE9, 0x10F4, 0x1122, 0x781E, 0x41BE, 0x421D, 0x5070};
		HAMON_CXX11_CONSTEXPR hamon::array<hamon::uint16_t, 8> b{0x08D0, 0xF251, 0xFA96, 0x0D5D, 0x4281, 0x0021, 0x8828, 0x3324};
		HAMON_CXX11_CONSTEXPR auto c = hamon::bigint_algo::sub(a, b);
		HAMON_CXX11_CONSTEXPR hamon::array<hamon::uint16_t, 8> expected{0x7845, 0x8B98, 0x165D, 0x03C4, 0x359D, 0x419D, 0xB9F5, 0x1D4B};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(expected, c);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::array<hamon::uint32_t, 5> a{0};
		HAMON_CXX11_CONSTEXPR hamon::array<hamon::uint32_t, 5> b{2};
		HAMON_CXX11_CONSTEXPR auto c = hamon::bigint_algo::sub(a, b);
		HAMON_CXX11_CONSTEXPR hamon::array<hamon::uint32_t, 5> expected{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(expected, c);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::array<hamon::uint32_t, 4> a{0x7DE98115, 0x112210F4, 0x41BE781E, 0x5070421D};
		HAMON_CXX11_CONSTEXPR hamon::array<hamon::uint32_t, 4> b{0xF25108D0, 0x0D5DFA96, 0x00214281, 0x33248828};
		HAMON_CXX11_CONSTEXPR auto c = hamon::bigint_algo::sub(a, b);
		HAMON_CXX11_CONSTEXPR hamon::array<hamon::uint32_t, 4> expected{0x8B987845, 0x03C4165D, 0x419D359D, 0x1D4BB9F5};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(expected, c);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::array<hamon::uint64_t, 3> a{0x112210F47DE98115, 0x5070421D41BE781E};
		HAMON_CXX11_CONSTEXPR hamon::array<hamon::uint64_t, 3> b{0x0D5DFA96F25108D0, 0x3324882800214281};
		HAMON_CXX11_CONSTEXPR auto c = hamon::bigint_algo::sub(a, b);
		HAMON_CXX11_CONSTEXPR hamon::array<hamon::uint64_t, 3> expected{0x03C4165D8B987845, 0x1D4BB9F5419D359D};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(expected, c);
	}
}
