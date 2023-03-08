/**
 *	@file	unit_test_functional_bit_xor.cpp
 *
 *	@brief	bit_xor のテスト
 */

#include <hamon/functional/bit_xor.hpp>
#include <hamon/cstdint/uint8_t.hpp>
#include <hamon/cstdint/uint16_t.hpp>
#include <hamon/cstdint/uint32_t.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "functional_test.hpp"

namespace hamon_functional_test
{

namespace bit_xor_test
{

GTEST_TEST(FunctionalTest, BitXorTest)
{
	{
		using type = hamon::bit_xor<int>;
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0xBD, type()(0xFA, 0x47));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0xC5, type()(0x35, 0xf0));
		static_assert(!has_is_transparent<type>::value, "");
	}
	{
		using type = hamon::bit_xor<>;
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint16_t(0xBD), type()(hamon::uint8_t (0xFA), hamon::uint16_t(0x47)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::uint32_t(0x53), type()(hamon::uint32_t(0x73), hamon::uint16_t(0x20)));
		static_assert( has_is_transparent<type>::value, "");
	}
}

}	// namespace bit_xor_test

}	// namespace hamon_functional_test
