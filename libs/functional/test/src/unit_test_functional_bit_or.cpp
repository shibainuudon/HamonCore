/**
 *	@file	unit_test_functional_bit_or.cpp
 *
 *	@brief	bit_or のテスト
 */

#include <hamon/functional/bit_or.hpp>
#include <hamon/cstdint/uint8_t.hpp>
#include <hamon/cstdint/uint16_t.hpp>
#include <hamon/cstdint/uint32_t.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "functional_test.hpp"

namespace hamon_functional_test
{

namespace bit_or_test
{

GTEST_TEST(FunctionalTest, BitOrTest)
{
	{
		using type = hamon::bit_or<int>;
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x3F, type()(0x0F, 0x35));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0xF5, type()(0x35, 0xf0));
		static_assert(!has_is_transparent<type>::value, "");
	}
	{
		using type = hamon::bit_or<>;
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint16_t(0x1F), type()(hamon::uint8_t (0x0F), hamon::uint16_t(0x12)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint32_t(0x77), type()(hamon::uint32_t(0x77), hamon::uint16_t(0x20)));
		static_assert( has_is_transparent<type>::value, "");
	}
}

}	// namespace bit_or_test

}	// namespace hamon_functional_test
