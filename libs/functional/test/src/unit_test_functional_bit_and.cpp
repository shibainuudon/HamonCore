/**
 *	@file	unit_test_functional_bit_and.cpp
 *
 *	@brief	bit_and のテスト
 */

#include <hamon/functional/bit_and.hpp>
#include <gtest/gtest.h>
#include <cstdint>
#include "constexpr_test.hpp"
#include "functional_test.hpp"

namespace hamon_functional_test
{

namespace bit_and_test
{

GTEST_TEST(FunctionalTest, BitAndTest)
{
	{
		using type = hamon::bit_and<int>;
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x05, type()(0x0F, 0x35));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x30, type()(0x35, 0xf0));
		static_assert(!has_is_transparent<type>::value, "");
	}
	{
		using type = hamon::bit_and<>;
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(std::uint16_t(0x02), type()(std::uint8_t (0x0F), std::uint16_t(0x12)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(std::uint32_t(0x20), type()(std::uint32_t(0x77), std::uint16_t(0x20)));
		static_assert( has_is_transparent<type>::value, "");
	}
}

}	// namespace bit_and_test

}	// namespace hamon_functional_test
