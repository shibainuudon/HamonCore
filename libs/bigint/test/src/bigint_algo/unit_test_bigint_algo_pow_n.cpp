/**
 *	@file	unit_test_bigint_algo_pow_n.cpp
 *
 *	@brief	bigint_algo::pow_n のテスト
 */

#include <hamon/bigint/bigint_algo/pow_n.hpp>
#include <hamon/array.hpp>
#include <hamon/cstdint.hpp>
#include <hamon/inplace_vector.hpp>
#include <hamon/vector.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_bigint_test
{

namespace bigint_algo_pow_n_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename VectorType>
inline HAMON_CXX14_CONSTEXPR bool
test(VectorType a, hamon::uintmax_t b, VectorType const& expected, bool overflow)
{
	{
		VectorType c{};
		bool f = hamon::bigint_algo::pow_n(c, a, b);
		VERIFY(c == expected);
		VERIFY(f == overflow);
	}
	return true;
}

#undef VERIFY

GTEST_TEST(BigIntAlgoTest, PowNTest)
{
#if 0
	{
		using VectorType = hamon::vector<hamon::uint8_t>;
		VectorType a{2};
		VectorType c{};
		hamon::bigint_algo::pow_n(c, a, 10000);
	}
	{
		using VectorType = hamon::array<hamon::uint8_t, 32>;
		VectorType a{2};
		VectorType c{};
		hamon::bigint_algo::pow_n(c, a, 10000);
	}
	for (int i = 0; i < 100000; ++i)
	{
		using VectorType = hamon::vector<hamon::uint8_t>;
		VectorType a{13};
		VectorType c{};
		hamon::bigint_algo::pow_n(c, a, 19);
	}
	for (int i = 0; i < 1000; ++i)
	{
		using VectorType = hamon::array<hamon::uint8_t, 32>;
		VectorType a{13};
		VectorType c{};
		hamon::bigint_algo::pow_n(c, a, 19);
	}
#endif

	// vector
	{
		using VectorType = hamon::vector<hamon::uint8_t>;
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(VectorType{0},   0, VectorType{1}, false));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(VectorType{0},   1, VectorType{0}, false));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(VectorType{0},   2, VectorType{0}, false));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(VectorType{0},   8, VectorType{0}, false));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(VectorType{0}, 100, VectorType{0}, false));
	}
	{
		using VectorType = hamon::vector<hamon::uint8_t>;
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(VectorType{1},   0, VectorType{1}, false));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(VectorType{1},   1, VectorType{1}, false));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(VectorType{1},   2, VectorType{1}, false));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(VectorType{1},   8, VectorType{1}, false));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(VectorType{1}, 100, VectorType{1}, false));
	}
	{
		using VectorType = hamon::vector<hamon::uint8_t>;
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(VectorType{2},  0, VectorType{0x01}, false));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(VectorType{2},  1, VectorType{0x02}, false));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(VectorType{2},  2, VectorType{0x04}, false));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(VectorType{2},  3, VectorType{0x08}, false));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(VectorType{2},  4, VectorType{0x10}, false));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(VectorType{2},  5, VectorType{0x20}, false));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(VectorType{2},  6, VectorType{0x40}, false));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(VectorType{2},  7, VectorType{0x80}, false));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(VectorType{2},  8, VectorType{0x00, 0x01}, false));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(VectorType{2},  9, VectorType{0x00, 0x02}, false));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(VectorType{2}, 10, VectorType{0x00, 0x04}, false));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(VectorType{2}, 11, VectorType{0x00, 0x08}, false));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(VectorType{2}, 12, VectorType{0x00, 0x10}, false));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(VectorType{2}, 13, VectorType{0x00, 0x20}, false));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(VectorType{2}, 14, VectorType{0x00, 0x40}, false));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(VectorType{2}, 15, VectorType{0x00, 0x80}, false));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(VectorType{2}, 16, VectorType{0x00, 0x00, 0x01}, false));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(VectorType{2}, 17, VectorType{0x00, 0x00, 0x02}, false));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(VectorType{2}, 18, VectorType{0x00, 0x00, 0x04}, false));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(VectorType{2}, 19, VectorType{0x00, 0x00, 0x08}, false));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(VectorType{2}, 20, VectorType{0x00, 0x00, 0x10}, false));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(VectorType{2}, 21, VectorType{0x00, 0x00, 0x20}, false));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(VectorType{2}, 22, VectorType{0x00, 0x00, 0x40}, false));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(VectorType{2}, 23, VectorType{0x00, 0x00, 0x80}, false));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(VectorType{2}, 24, VectorType{0x00, 0x00, 0x00, 0x01}, false));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(VectorType{2}, 32, VectorType{0x00, 0x00, 0x00, 0x00, 0x01}, false));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(VectorType{2}, 40, VectorType{0x00, 0x00, 0x00, 0x00, 0x00, 0x01}, false));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(VectorType{2}, 48, VectorType{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01}, false));
	}
	{
		using VectorType = hamon::vector<hamon::uint8_t>;
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(VectorType{3},  0, VectorType{0x01}, false));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(VectorType{3},  1, VectorType{0x03}, false));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(VectorType{3},  2, VectorType{0x09}, false));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(VectorType{3},  3, VectorType{0x1B}, false));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(VectorType{3},  4, VectorType{0x51}, false));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(VectorType{3},  5, VectorType{0xF3}, false));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(VectorType{3},  6, VectorType{0xD9, 0x02}, false));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(VectorType{3},  7, VectorType{0x8B, 0x08}, false));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(VectorType{3},  8, VectorType{0xA1, 0x19}, false));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(VectorType{3},  9, VectorType{0xE3, 0x4C}, false));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(VectorType{3}, 10, VectorType{0xA9, 0xE6}, false));
	}
	{
		using VectorType = hamon::vector<hamon::uint8_t>;
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(VectorType{0x34, 0x12}, 0, VectorType{0x01}, false));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(VectorType{0x34, 0x12}, 1, VectorType{0x34, 0x12}, false));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(VectorType{0x34, 0x12}, 2, VectorType{0x90, 0x5A, 0x4B, 0x01}, false));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(VectorType{0x34, 0x12}, 3, VectorType{0x40, 0x85, 0xAC, 0x8F, 0x17}, false));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(VectorType{0x34, 0x12}, 4, VectorType{0x00, 0x91, 0x69, 0x50, 0xE3, 0xAC, 0x01}, false));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(VectorType{0x34, 0x12}, 5, VectorType{0x00, 0x74, 0xA3, 0xC1, 0xD3, 0x19, 0x7F, 0x1E}, false));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(VectorType{0x34, 0x12}, 6, VectorType{0x00, 0x90, 0x5B, 0xD3, 0xA0, 0x22, 0xA2, 0x21, 0x2B, 0x02}, false));
	}
	{
		using VectorType = hamon::vector<hamon::uint16_t>;
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(VectorType{0x0ABC}, 0, VectorType{0x0001}, false));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(VectorType{0x0ABC}, 1, VectorType{0x0ABC}, false));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(VectorType{0x0ABC}, 2, VectorType{0x3A10, 0x0073}, false));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(VectorType{0x0ABC}, 3, VectorType{0x43C0, 0xD4E3, 0x0004}, false));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(VectorType{0x0ABC}, 4, VectorType{0x4100, 0x378B, 0x33DD}, false));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(VectorType{0x0ABC}, 5, VectorType{0xBC00, 0x3ACD, 0xBAA0, 0x022C}, false));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(VectorType{0x0ABC}, 6, VectorType{0x1000, 0x386E, 0x4FF7, 0x5823, 0x0017}, false));
	}
	{
		using VectorType = hamon::vector<hamon::uint32_t>;
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(VectorType{0x00012345}, 0, VectorType{0x00000001}, false));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(VectorType{0x00012345}, 1, VectorType{0x00012345}, false));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(VectorType{0x00012345}, 2, VectorType{0x4B65F099, 0x00000001}, false));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(VectorType{0x00012345}, 3, VectorType{0x32F7C43D, 0x0001790E}, false));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(VectorType{0x00012345}, 4, VectorType{0x60D93B71, 0xAD00C4C3, 0x00000001}, false));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(VectorType{0x00012345}, 5, VectorType{0x091E7875, 0x80DF1FC0, 0x0001E81B}, false));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(VectorType{0x00012345}, 6, VectorType{0x18237689, 0x5D3AD920, 0x2B5AD2E7, 0x00000002}, false));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(VectorType{0x00012345}, 7, VectorType{0xD14CADED, 0x05AC0116, 0xED37D756, 0x000277DD}, false));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(VectorType{0x00012345}, 8, VectorType{0x935F47E1, 0x0C993B10, 0x69D3D2A2, 0xCEEB9377, 0x00000002}, false));
	}
	{
		using VectorType = hamon::vector<hamon::uint64_t>;
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(VectorType{0x00012345}, 0, VectorType{0x0000000000000001}, false));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(VectorType{0x00012345}, 1, VectorType{0x0000000000012345}, false));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(VectorType{0x00012345}, 2, VectorType{0x000000014B65F099}, false));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(VectorType{0x00012345}, 3, VectorType{0x0001790E32F7C43D}, false));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(VectorType{0x00012345}, 4, VectorType{0xAD00C4C360D93B71, 0x0000000000000001}, false));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(VectorType{0x00012345}, 5, VectorType{0x80DF1FC0091E7875, 0x000000000001E81B}, false));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(VectorType{0x00012345}, 6, VectorType{0x5D3AD92018237689, 0x000000022B5AD2E7}, false));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(VectorType{0x00012345}, 7, VectorType{0x05AC0116D14CADED, 0x000277DDED37D756}, false));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(VectorType{0x00012345}, 8, VectorType{0x0C993B10935F47E1, 0xCEEB937769D3D2A2, 0x0000000000000002}, false));
	}

	// inplace_vector
	{
		using VectorType = hamon::inplace_vector<hamon::uint8_t, 10>;
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(VectorType{0},   0, VectorType{1}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(VectorType{0},   1, VectorType{0}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(VectorType{0},   2, VectorType{0}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(VectorType{0},   8, VectorType{0}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(VectorType{0}, 100, VectorType{0}, false));
	}
	{
		using VectorType = hamon::inplace_vector<hamon::uint8_t, 10>;
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(VectorType{1},   0, VectorType{1}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(VectorType{1},   1, VectorType{1}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(VectorType{1},   2, VectorType{1}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(VectorType{1},   8, VectorType{1}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(VectorType{1}, 100, VectorType{1}, false));
	}
	{
		using VectorType = hamon::inplace_vector<hamon::uint8_t, 8>;
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(VectorType{0x34, 0x12}, 0, VectorType{0x01}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(VectorType{0x34, 0x12}, 1, VectorType{0x34, 0x12}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(VectorType{0x34, 0x12}, 2, VectorType{0x90, 0x5A, 0x4B, 0x01}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(VectorType{0x34, 0x12}, 3, VectorType{0x40, 0x85, 0xAC, 0x8F, 0x17}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(VectorType{0x34, 0x12}, 4, VectorType{0x00, 0x91, 0x69, 0x50, 0xE3, 0xAC, 0x01}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(VectorType{0x34, 0x12}, 5, VectorType{0x00, 0x74, 0xA3, 0xC1, 0xD3, 0x19, 0x7F, 0x1E}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(VectorType{0x34, 0x12}, 6, VectorType{0x00, 0x90, 0x5B, 0xD3, 0xA0, 0x22, 0xA2, 0x21}, true));
	}
	{
		using VectorType = hamon::inplace_vector<hamon::uint16_t, 4>;
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(VectorType{0x0ABC}, 0, VectorType{0x0001}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(VectorType{0x0ABC}, 1, VectorType{0x0ABC}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(VectorType{0x0ABC}, 2, VectorType{0x3A10, 0x0073}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(VectorType{0x0ABC}, 3, VectorType{0x43C0, 0xD4E3, 0x0004}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(VectorType{0x0ABC}, 4, VectorType{0x4100, 0x378B, 0x33DD}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(VectorType{0x0ABC}, 5, VectorType{0xBC00, 0x3ACD, 0xBAA0, 0x022C}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(VectorType{0x0ABC}, 6, VectorType{0x1000, 0x386E, 0x4FF7, 0x5823}, true));
	}

	// array
	{
		using VectorType = hamon::array<hamon::uint8_t, 8>;
		HAMON_CXX14_CONSTEXPR VectorType const a{0x34, 0x12};
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(a, 0, VectorType{0x01}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(a, 1, VectorType{0x34, 0x12}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(a, 2, VectorType{0x90, 0x5A, 0x4B, 0x01}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(a, 3, VectorType{0x40, 0x85, 0xAC, 0x8F, 0x17}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(a, 4, VectorType{0x00, 0x91, 0x69, 0x50, 0xE3, 0xAC, 0x01}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(a, 5, VectorType{0x00, 0x74, 0xA3, 0xC1, 0xD3, 0x19, 0x7F, 0x1E}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(a, 6, VectorType{0x00, 0x90, 0x5B, 0xD3, 0xA0, 0x22, 0xA2, 0x21}, true));
	}
	{
		using VectorType = hamon::array<hamon::uint16_t, 4>;
		HAMON_CXX14_CONSTEXPR VectorType const a{0x0ABC};
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(a, 0, VectorType{0x0001}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(a, 1, VectorType{0x0ABC}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(a, 2, VectorType{0x3A10, 0x0073}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(a, 3, VectorType{0x43C0, 0xD4E3, 0x0004}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(a, 4, VectorType{0x4100, 0x378B, 0x33DD}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(a, 5, VectorType{0xBC00, 0x3ACD, 0xBAA0, 0x022C}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(a, 6, VectorType{0x1000, 0x386E, 0x4FF7, 0x5823}, true));
	}
	{
		using VectorType = hamon::array<hamon::uint32_t, 4>;
		HAMON_CXX14_CONSTEXPR VectorType const a{0x00012345};
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(a, 0, VectorType{0x00000001}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(a, 1, VectorType{0x00012345}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(a, 2, VectorType{0x4B65F099, 0x00000001}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(a, 3, VectorType{0x32F7C43D, 0x0001790E}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(a, 4, VectorType{0x60D93B71, 0xAD00C4C3, 0x00000001}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(a, 5, VectorType{0x091E7875, 0x80DF1FC0, 0x0001E81B}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(a, 6, VectorType{0x18237689, 0x5D3AD920, 0x2B5AD2E7, 0x00000002}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(a, 7, VectorType{0xD14CADED, 0x05AC0116, 0xED37D756, 0x000277DD}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(a, 8, VectorType{0x935F47E1, 0x0C993B10, 0x69D3D2A2, 0xCEEB9377}, true));
	}
	{
		using VectorType = hamon::array<hamon::uint64_t, 2>;
		HAMON_CXX14_CONSTEXPR VectorType const a{0x00012345};
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(a, 0, VectorType{0x0000000000000001}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(a, 1, VectorType{0x0000000000012345}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(a, 2, VectorType{0x000000014B65F099}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(a, 3, VectorType{0x0001790E32F7C43D}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(a, 4, VectorType{0xAD00C4C360D93B71, 0x0000000000000001}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(a, 5, VectorType{0x80DF1FC0091E7875, 0x000000000001E81B}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(a, 6, VectorType{0x5D3AD92018237689, 0x000000022B5AD2E7}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(a, 7, VectorType{0x05AC0116D14CADED, 0x000277DDED37D756}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(a, 8, VectorType{0x0C993B10935F47E1, 0xCEEB937769D3D2A2}, true));
	}
}

}	// namespace bigint_algo_pow_n_test

}	// namespace hamon_bigint_test
