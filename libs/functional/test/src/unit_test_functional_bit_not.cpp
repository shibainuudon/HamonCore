/**
 *	@file	unit_test_functional_bit_not.cpp
 *
 *	@brief	bit_not のテスト
 */

#include <hamon/functional/bit_not.hpp>
#include <hamon/cstdint/uint8_t.hpp>
#include <hamon/cstdint/uint16_t.hpp>
#include <hamon/cstdint/uint32_t.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "functional_test.hpp"

namespace hamon_functional_test
{

namespace bit_not_test
{

GTEST_TEST(FunctionalTest, BitNotTest)
{
	{
		using type = hamon::bit_not<hamon::uint8_t>;
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x05, type()(0xFA));
		static_assert(!has_is_transparent<type>::value, "");
	}
	{
		using type = hamon::bit_not<hamon::uint16_t>;
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0xFF05, type()(0xFA));
		static_assert(!has_is_transparent<type>::value, "");
	}
	{
		using type = hamon::bit_not<>;
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0xF0, static_cast<hamon::uint8_t>(type()(static_cast<hamon::uint8_t>(0x0F))));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0xFFFFFF88, type()(static_cast<hamon::uint32_t>(0x77)));
		static_assert( has_is_transparent<type>::value, "");
	}
}

}	// namespace bit_not_test

}	// namespace hamon_functional_test
