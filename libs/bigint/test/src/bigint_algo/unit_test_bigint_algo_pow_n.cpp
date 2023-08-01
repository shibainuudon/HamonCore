/**
 *	@file	unit_test_bigint_algo_pow_n.cpp
 *
 *	@brief	bigint_algo::pow_n のテスト
 */

#include <hamon/bigint/bigint_algo/pow_n.hpp>
#include <hamon/array.hpp>
#include <hamon/cstdint.hpp>
#include <gtest/gtest.h>
#include <vector>
#include "constexpr_test.hpp"

namespace hamon_bigint_test
{

namespace bigint_algo_pow_n_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename VectorType>
inline HAMON_CXX14_CONSTEXPR bool
PowNTest(VectorType a, hamon::uintmax_t b, VectorType const& expected, bool overflow)
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
		using VectorType = std::vector<hamon::uint8_t>;
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
		using VectorType = std::vector<hamon::uint8_t>;
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

	{
		using VectorType = std::vector<hamon::uint8_t>;
		VectorType const a{0};
		EXPECT_TRUE(PowNTest(a,   0, VectorType{1}, false));
		EXPECT_TRUE(PowNTest(a,   1, VectorType{0}, false));
		EXPECT_TRUE(PowNTest(a,   2, VectorType{0}, false));
		EXPECT_TRUE(PowNTest(a,   8, VectorType{0}, false));
		EXPECT_TRUE(PowNTest(a, 100, VectorType{0}, false));
	}
	{
		using VectorType = std::vector<hamon::uint8_t>;
		VectorType const a{1};
		EXPECT_TRUE(PowNTest(a,   0, VectorType{1}, false));
		EXPECT_TRUE(PowNTest(a,   1, VectorType{1}, false));
		EXPECT_TRUE(PowNTest(a,   2, VectorType{1}, false));
		EXPECT_TRUE(PowNTest(a,   8, VectorType{1}, false));
		EXPECT_TRUE(PowNTest(a, 100, VectorType{1}, false));
	}
	{
		using VectorType = std::vector<hamon::uint8_t>;
		VectorType const a{2};
		EXPECT_TRUE(PowNTest(a,  0, VectorType{0x01}, false));
		EXPECT_TRUE(PowNTest(a,  1, VectorType{0x02}, false));
		EXPECT_TRUE(PowNTest(a,  2, VectorType{0x04}, false));
		EXPECT_TRUE(PowNTest(a,  3, VectorType{0x08}, false));
		EXPECT_TRUE(PowNTest(a,  4, VectorType{0x10}, false));
		EXPECT_TRUE(PowNTest(a,  5, VectorType{0x20}, false));
		EXPECT_TRUE(PowNTest(a,  6, VectorType{0x40}, false));
		EXPECT_TRUE(PowNTest(a,  7, VectorType{0x80}, false));
		EXPECT_TRUE(PowNTest(a,  8, VectorType{0x00, 0x01}, false));
		EXPECT_TRUE(PowNTest(a,  9, VectorType{0x00, 0x02}, false));
		EXPECT_TRUE(PowNTest(a, 10, VectorType{0x00, 0x04}, false));
		EXPECT_TRUE(PowNTest(a, 11, VectorType{0x00, 0x08}, false));
		EXPECT_TRUE(PowNTest(a, 12, VectorType{0x00, 0x10}, false));
		EXPECT_TRUE(PowNTest(a, 13, VectorType{0x00, 0x20}, false));
		EXPECT_TRUE(PowNTest(a, 14, VectorType{0x00, 0x40}, false));
		EXPECT_TRUE(PowNTest(a, 15, VectorType{0x00, 0x80}, false));
		EXPECT_TRUE(PowNTest(a, 16, VectorType{0x00, 0x00, 0x01}, false));
		EXPECT_TRUE(PowNTest(a, 17, VectorType{0x00, 0x00, 0x02}, false));
		EXPECT_TRUE(PowNTest(a, 18, VectorType{0x00, 0x00, 0x04}, false));
		EXPECT_TRUE(PowNTest(a, 19, VectorType{0x00, 0x00, 0x08}, false));
		EXPECT_TRUE(PowNTest(a, 20, VectorType{0x00, 0x00, 0x10}, false));
		EXPECT_TRUE(PowNTest(a, 21, VectorType{0x00, 0x00, 0x20}, false));
		EXPECT_TRUE(PowNTest(a, 22, VectorType{0x00, 0x00, 0x40}, false));
		EXPECT_TRUE(PowNTest(a, 23, VectorType{0x00, 0x00, 0x80}, false));
		EXPECT_TRUE(PowNTest(a, 24, VectorType{0x00, 0x00, 0x00, 0x01}, false));
		EXPECT_TRUE(PowNTest(a, 32, VectorType{0x00, 0x00, 0x00, 0x00, 0x01}, false));
		EXPECT_TRUE(PowNTest(a, 40, VectorType{0x00, 0x00, 0x00, 0x00, 0x00, 0x01}, false));
		EXPECT_TRUE(PowNTest(a, 48, VectorType{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01}, false));
	}
	{
		using VectorType = std::vector<hamon::uint8_t>;
		VectorType const a{3};
		EXPECT_TRUE(PowNTest(a,  0, VectorType{0x01}, false));
		EXPECT_TRUE(PowNTest(a,  1, VectorType{0x03}, false));
		EXPECT_TRUE(PowNTest(a,  2, VectorType{0x09}, false));
		EXPECT_TRUE(PowNTest(a,  3, VectorType{0x1B}, false));
		EXPECT_TRUE(PowNTest(a,  4, VectorType{0x51}, false));
		EXPECT_TRUE(PowNTest(a,  5, VectorType{0xF3}, false));
		EXPECT_TRUE(PowNTest(a,  6, VectorType{0xD9, 0x02}, false));
		EXPECT_TRUE(PowNTest(a,  7, VectorType{0x8B, 0x08}, false));
		EXPECT_TRUE(PowNTest(a,  8, VectorType{0xA1, 0x19}, false));
		EXPECT_TRUE(PowNTest(a,  9, VectorType{0xE3, 0x4C}, false));
		EXPECT_TRUE(PowNTest(a, 10, VectorType{0xA9, 0xE6}, false));
	}
	{
		using VectorType = std::vector<hamon::uint8_t>;
		VectorType const a{0x34, 0x12};
		EXPECT_TRUE(PowNTest(a, 0, VectorType{0x01}, false));
		EXPECT_TRUE(PowNTest(a, 1, VectorType{0x34, 0x12}, false));
		EXPECT_TRUE(PowNTest(a, 2, VectorType{0x90, 0x5A, 0x4B, 0x01}, false));
		EXPECT_TRUE(PowNTest(a, 3, VectorType{0x40, 0x85, 0xAC, 0x8F, 0x17}, false));
		EXPECT_TRUE(PowNTest(a, 4, VectorType{0x00, 0x91, 0x69, 0x50, 0xE3, 0xAC, 0x01}, false));
		EXPECT_TRUE(PowNTest(a, 5, VectorType{0x00, 0x74, 0xA3, 0xC1, 0xD3, 0x19, 0x7F, 0x1E}, false));
		EXPECT_TRUE(PowNTest(a, 6, VectorType{0x00, 0x90, 0x5B, 0xD3, 0xA0, 0x22, 0xA2, 0x21, 0x2B, 0x02}, false));
	}
	{
		using VectorType = std::vector<hamon::uint16_t>;
		VectorType const a{0x0ABC};
		EXPECT_TRUE(PowNTest(a, 0, VectorType{0x0001}, false));
		EXPECT_TRUE(PowNTest(a, 1, VectorType{0x0ABC}, false));
		EXPECT_TRUE(PowNTest(a, 2, VectorType{0x3A10, 0x0073}, false));
		EXPECT_TRUE(PowNTest(a, 3, VectorType{0x43C0, 0xD4E3, 0x0004}, false));
		EXPECT_TRUE(PowNTest(a, 4, VectorType{0x4100, 0x378B, 0x33DD}, false));
		EXPECT_TRUE(PowNTest(a, 5, VectorType{0xBC00, 0x3ACD, 0xBAA0, 0x022C}, false));
		EXPECT_TRUE(PowNTest(a, 6, VectorType{0x1000, 0x386E, 0x4FF7, 0x5823, 0x0017}, false));
	}
	{
		using VectorType = std::vector<hamon::uint32_t>;
		VectorType const a{0x00012345};
		EXPECT_TRUE(PowNTest(a, 0, VectorType{0x00000001}, false));
		EXPECT_TRUE(PowNTest(a, 1, VectorType{0x00012345}, false));
		EXPECT_TRUE(PowNTest(a, 2, VectorType{0x4B65F099, 0x00000001}, false));
		EXPECT_TRUE(PowNTest(a, 3, VectorType{0x32F7C43D, 0x0001790E}, false));
		EXPECT_TRUE(PowNTest(a, 4, VectorType{0x60D93B71, 0xAD00C4C3, 0x00000001}, false));
		EXPECT_TRUE(PowNTest(a, 5, VectorType{0x091E7875, 0x80DF1FC0, 0x0001E81B}, false));
		EXPECT_TRUE(PowNTest(a, 6, VectorType{0x18237689, 0x5D3AD920, 0x2B5AD2E7, 0x00000002}, false));
		EXPECT_TRUE(PowNTest(a, 7, VectorType{0xD14CADED, 0x05AC0116, 0xED37D756, 0x000277DD}, false));
		EXPECT_TRUE(PowNTest(a, 8, VectorType{0x935F47E1, 0x0C993B10, 0x69D3D2A2, 0xCEEB9377, 0x00000002}, false));
	}
	{
		using VectorType = std::vector<hamon::uint64_t>;
		VectorType const a{0x00012345};
		EXPECT_TRUE(PowNTest(a, 0, VectorType{0x0000000000000001}, false));
		EXPECT_TRUE(PowNTest(a, 1, VectorType{0x0000000000012345}, false));
		EXPECT_TRUE(PowNTest(a, 2, VectorType{0x000000014B65F099}, false));
		EXPECT_TRUE(PowNTest(a, 3, VectorType{0x0001790E32F7C43D}, false));
		EXPECT_TRUE(PowNTest(a, 4, VectorType{0xAD00C4C360D93B71, 0x0000000000000001}, false));
		EXPECT_TRUE(PowNTest(a, 5, VectorType{0x80DF1FC0091E7875, 0x000000000001E81B}, false));
		EXPECT_TRUE(PowNTest(a, 6, VectorType{0x5D3AD92018237689, 0x000000022B5AD2E7}, false));
		EXPECT_TRUE(PowNTest(a, 7, VectorType{0x05AC0116D14CADED, 0x000277DDED37D756}, false));
		EXPECT_TRUE(PowNTest(a, 8, VectorType{0x0C993B10935F47E1, 0xCEEB937769D3D2A2, 0x0000000000000002}, false));
	}

	{
		using VectorType = hamon::array<hamon::uint8_t, 8>;
		HAMON_CXX14_CONSTEXPR VectorType const a{0x34, 0x12};
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(PowNTest(a, 0, VectorType{0x01}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(PowNTest(a, 1, VectorType{0x34, 0x12}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(PowNTest(a, 2, VectorType{0x90, 0x5A, 0x4B, 0x01}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(PowNTest(a, 3, VectorType{0x40, 0x85, 0xAC, 0x8F, 0x17}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(PowNTest(a, 4, VectorType{0x00, 0x91, 0x69, 0x50, 0xE3, 0xAC, 0x01}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(PowNTest(a, 5, VectorType{0x00, 0x74, 0xA3, 0xC1, 0xD3, 0x19, 0x7F, 0x1E}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(PowNTest(a, 6, VectorType{0x00, 0x90, 0x5B, 0xD3, 0xA0, 0x22, 0xA2, 0x21}, true));
	}
	{
		using VectorType = hamon::array<hamon::uint16_t, 4>;
		HAMON_CXX14_CONSTEXPR VectorType const a{0x0ABC};
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(PowNTest(a, 0, VectorType{0x0001}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(PowNTest(a, 1, VectorType{0x0ABC}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(PowNTest(a, 2, VectorType{0x3A10, 0x0073}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(PowNTest(a, 3, VectorType{0x43C0, 0xD4E3, 0x0004}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(PowNTest(a, 4, VectorType{0x4100, 0x378B, 0x33DD}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(PowNTest(a, 5, VectorType{0xBC00, 0x3ACD, 0xBAA0, 0x022C}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(PowNTest(a, 6, VectorType{0x1000, 0x386E, 0x4FF7, 0x5823}, true));
	}
	{
		using VectorType = hamon::array<hamon::uint32_t, 4>;
		HAMON_CXX14_CONSTEXPR VectorType const a{0x00012345};
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(PowNTest(a, 0, VectorType{0x00000001}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(PowNTest(a, 1, VectorType{0x00012345}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(PowNTest(a, 2, VectorType{0x4B65F099, 0x00000001}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(PowNTest(a, 3, VectorType{0x32F7C43D, 0x0001790E}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(PowNTest(a, 4, VectorType{0x60D93B71, 0xAD00C4C3, 0x00000001}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(PowNTest(a, 5, VectorType{0x091E7875, 0x80DF1FC0, 0x0001E81B}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(PowNTest(a, 6, VectorType{0x18237689, 0x5D3AD920, 0x2B5AD2E7, 0x00000002}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(PowNTest(a, 7, VectorType{0xD14CADED, 0x05AC0116, 0xED37D756, 0x000277DD}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(PowNTest(a, 8, VectorType{0x935F47E1, 0x0C993B10, 0x69D3D2A2, 0xCEEB9377}, true));
	}
	{
		using VectorType = hamon::array<hamon::uint64_t, 2>;
		HAMON_CXX14_CONSTEXPR VectorType const a{0x00012345};
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(PowNTest(a, 0, VectorType{0x0000000000000001}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(PowNTest(a, 1, VectorType{0x0000000000012345}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(PowNTest(a, 2, VectorType{0x000000014B65F099}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(PowNTest(a, 3, VectorType{0x0001790E32F7C43D}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(PowNTest(a, 4, VectorType{0xAD00C4C360D93B71, 0x0000000000000001}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(PowNTest(a, 5, VectorType{0x80DF1FC0091E7875, 0x000000000001E81B}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(PowNTest(a, 6, VectorType{0x5D3AD92018237689, 0x000000022B5AD2E7}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(PowNTest(a, 7, VectorType{0x05AC0116D14CADED, 0x000277DDED37D756}, false));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(PowNTest(a, 8, VectorType{0x0C993B10935F47E1, 0xCEEB937769D3D2A2}, true));
	}
}

}	// namespace bigint_algo_pow_n_test

}	// namespace hamon_bigint_test
