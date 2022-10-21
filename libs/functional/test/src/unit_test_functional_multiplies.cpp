/**
 *	@file	unit_test_functional_multiplies.cpp
 *
 *	@brief	multiplies のテスト
 */

#include <hamon/functional/multiplies.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "functional_test.hpp"

namespace hamon_functional_test
{

namespace multiplies_test
{

GTEST_TEST(FunctionalTest, MultipliesTest)
{
	{
		using type = hamon::multiplies<int>;
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(   0, type()(  0,  0));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-210, type()( 42, -5));
		static_assert(!has_is_transparent<type>::value, "");
	}
	{
		using type = hamon::multiplies<float>;
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1.125, type()(  0.5,  2.25));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 7.5,   type()( -1.5, -5.0));
		static_assert(!has_is_transparent<type>::value, "");
	}
	{
		using type = hamon::multiplies<>;
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  0.5, type()(  1,   0.5));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-12.0, type()( -1.5, 8U));
		static_assert( has_is_transparent<type>::value, "");
	}
}

}	// namespace multiplies_test

}	// namespace hamon_functional_test
