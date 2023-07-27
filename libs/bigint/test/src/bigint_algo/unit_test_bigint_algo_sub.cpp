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

namespace hamon_bigint_test
{

namespace bigint_algo_sub_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename VectorType>
inline HAMON_CXX14_CONSTEXPR bool
SubTest(VectorType a, VectorType const& b, VectorType const& expected)
{
	hamon::bigint_algo::sub(a, b);
	VERIFY(a == expected);
	return true;
}

#undef VERIFY

GTEST_TEST(BigIntAlgoTest, SubTest)
{
#if 0
	{
		std::vector<hamon::uint8_t> a{0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC, 0xDE, 0xF0};
		std::vector<hamon::uint8_t> b{0xFF, 0x01};
		for (hamon::size_t i = 0; i < 10000000; ++i)
		{
			hamon::bigint_algo::sub(a, b);
		}
	}
	{
		hamon::array<hamon::uint8_t, 8> a{0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC, 0xDE, 0xF0};
		hamon::array<hamon::uint8_t, 8> b{0xFF, 0x01};
		for (hamon::size_t i = 0; i < 10000000; ++i)
		{
			hamon::bigint_algo::sub(a, b);
		}
	}
#endif

	EXPECT_TRUE(SubTest(
		std::vector<hamon::uint8_t>{0x39, 0x30},	// 12345
		std::vector<hamon::uint8_t>{0x03},
		std::vector<hamon::uint8_t>{0x36, 0x30}));	// 12342
	EXPECT_TRUE(SubTest(
		std::vector<hamon::uint8_t>{0x00, 0x00, 0x01},
		std::vector<hamon::uint8_t>{0x01},
		std::vector<hamon::uint8_t>{0xFF, 0xFF}));
	EXPECT_TRUE(SubTest(
		std::vector<hamon::uint8_t>{0x56, 0x34, 0x12},
		std::vector<hamon::uint8_t>{0x89, 0x30, 0x12},
		std::vector<hamon::uint8_t>{0xCD, 0x03}));
	EXPECT_TRUE(SubTest(
		std::vector<hamon::uint8_t>{0x78, 0x56, 0x34, 0x12},
		std::vector<hamon::uint8_t>{0x78, 0x56, 0x34, 0x12},
		std::vector<hamon::uint8_t>{0x00}));
	EXPECT_TRUE(SubTest(
		std::vector<hamon::uint8_t>{0x15, 0x81, 0xE9, 0x7D, 0xF4, 0x10, 0x22, 0x11, 0x1E, 0x78, 0xBE, 0x41, 0x1D, 0x42, 0x70, 0x50},
		std::vector<hamon::uint8_t>{0xD0, 0x08, 0x51, 0xF2, 0x96, 0xFA, 0x5D, 0x0D, 0x81, 0x42, 0x21, 0x00, 0x28, 0x88, 0x24, 0x33},
		std::vector<hamon::uint8_t>{0x45, 0x78, 0x98, 0x8B, 0x5D, 0x16, 0xC4, 0x03, 0x9D, 0x35, 0x9D, 0x41, 0xF5, 0xB9, 0x4B, 0x1D}));
	EXPECT_TRUE(SubTest(
		std::vector<hamon::uint16_t>{0x0000, 0x0000, 0x0000, 0x0001},
		std::vector<hamon::uint16_t>{0x0002},
		std::vector<hamon::uint16_t>{0xFFFE, 0xFFFF, 0xFFFF}));
	EXPECT_TRUE(SubTest(
		std::vector<hamon::uint16_t>{0xB0A1, 0x12B9},
		std::vector<hamon::uint16_t>{0x614E, 0x00BC},
		std::vector<hamon::uint16_t>{0x4F53, 0x11FD}));
	EXPECT_TRUE(SubTest(
		std::vector<hamon::uint16_t>{0x8115, 0x7DE9, 0x10F4, 0x1122, 0x781E, 0x41BE, 0x421D, 0x5070},
		std::vector<hamon::uint16_t>{0x08D0, 0xF251, 0xFA96, 0x0D5D, 0x4281, 0x0021, 0x8828, 0x3324},
		std::vector<hamon::uint16_t>{0x7845, 0x8B98, 0x165D, 0x03C4, 0x359D, 0x419D, 0xB9F5, 0x1D4B}));
	EXPECT_TRUE(SubTest(
		std::vector<hamon::uint32_t>{0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000010},
		std::vector<hamon::uint32_t>{0x00000000, 0x00000001},
		std::vector<hamon::uint32_t>{0x00000000, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0000000F}));
	EXPECT_TRUE(SubTest(
		std::vector<hamon::uint32_t>{0x7DE98115, 0x112210F4, 0x41BE781E, 0x5070421D},
		std::vector<hamon::uint32_t>{0xF25108D0, 0x0D5DFA96, 0x00214281, 0x33248828},
		std::vector<hamon::uint32_t>{0x8B987845, 0x03C4165D, 0x419D359D, 0x1D4BB9F5}));
	EXPECT_TRUE(SubTest(
		std::vector<hamon::uint64_t>{0x112210F47DE98115, 0x5070421D41BE781E},
		std::vector<hamon::uint64_t>{0x0D5DFA96F25108D0, 0x3324882800214281},
		std::vector<hamon::uint64_t>{0x03C4165D8B987845, 0x1D4BB9F5419D359D}));

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(SubTest(
		hamon::array<hamon::uint8_t, 4>{0x00, 0x00, 0x00, 0xFF},
		hamon::array<hamon::uint8_t, 4>{0x01},
		hamon::array<hamon::uint8_t, 4>{0xFF, 0xFF, 0xFF, 0xFE}));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(SubTest(
		hamon::array<hamon::uint8_t, 4>{0x02},
		hamon::array<hamon::uint8_t, 4>{0x01},
		hamon::array<hamon::uint8_t, 4>{0x01}));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(SubTest(
		hamon::array<hamon::uint8_t, 4>{0x01},
		hamon::array<hamon::uint8_t, 4>{0x02},
		hamon::array<hamon::uint8_t, 4>{0xFF, 0xFF, 0xFF, 0xFF}));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(SubTest(
		hamon::array<hamon::uint8_t, 16>{0x15, 0x81, 0xE9, 0x7D, 0xF4, 0x10, 0x22, 0x11, 0x1E, 0x78, 0xBE, 0x41, 0x1D, 0x42, 0x70, 0x50},
		hamon::array<hamon::uint8_t, 16>{0xD0, 0x08, 0x51, 0xF2, 0x96, 0xFA, 0x5D, 0x0D, 0x81, 0x42, 0x21, 0x00, 0x28, 0x88, 0x24, 0x33},
		hamon::array<hamon::uint8_t, 16>{0x45, 0x78, 0x98, 0x8B, 0x5D, 0x16, 0xC4, 0x03, 0x9D, 0x35, 0x9D, 0x41, 0xF5, 0xB9, 0x4B, 0x1D}));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(SubTest(
		hamon::array<hamon::uint16_t, 3>{0x1111, 0x1111, 0x1111},
		hamon::array<hamon::uint16_t, 3>{0x0987, 0x6543, 0x0020},
		hamon::array<hamon::uint16_t, 3>{0x078A, 0xABCE, 0x10F0}));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(SubTest(
		hamon::array<hamon::uint16_t, 8>{0x8115, 0x7DE9, 0x10F4, 0x1122, 0x781E, 0x41BE, 0x421D, 0x5070},
		hamon::array<hamon::uint16_t, 8>{0x08D0, 0xF251, 0xFA96, 0x0D5D, 0x4281, 0x0021, 0x8828, 0x3324},
		hamon::array<hamon::uint16_t, 8>{0x7845, 0x8B98, 0x165D, 0x03C4, 0x359D, 0x419D, 0xB9F5, 0x1D4B}));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(SubTest(
		hamon::array<hamon::uint32_t, 5>{0},
		hamon::array<hamon::uint32_t, 5>{2},
		hamon::array<hamon::uint32_t, 5>{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(SubTest(
		hamon::array<hamon::uint32_t, 4>{0x7DE98115, 0x112210F4, 0x41BE781E, 0x5070421D},
		hamon::array<hamon::uint32_t, 4>{0xF25108D0, 0x0D5DFA96, 0x00214281, 0x33248828},
		hamon::array<hamon::uint32_t, 4>{0x8B987845, 0x03C4165D, 0x419D359D, 0x1D4BB9F5}));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(SubTest(
		hamon::array<hamon::uint64_t, 2>{0x112210F47DE98115, 0x5070421D41BE781E},
		hamon::array<hamon::uint64_t, 2>{0x0D5DFA96F25108D0, 0x3324882800214281},
		hamon::array<hamon::uint64_t, 2>{0x03C4165D8B987845, 0x1D4BB9F5419D359D}));
}

}	// namespace bigint_algo_sub_test

}	// namespace hamon_bigint_test
