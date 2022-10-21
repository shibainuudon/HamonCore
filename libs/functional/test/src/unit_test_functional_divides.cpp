/**
 *	@file	unit_test_functional_divides.cpp
 *
 *	@brief	divides のテスト
 */

#include <hamon/functional/divides.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "functional_test.hpp"

namespace hamon_functional_test
{

namespace divides_test
{

GTEST_TEST(FunctionalTest, DividesTest)
{
	{
		using type = hamon::divides<int>;
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, type()(  0,  1));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-8, type()( 42, -5));
		static_assert(!has_is_transparent<type>::value, "");
	}
	{
		using type = hamon::divides<float>;
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0.25, type()(  0.5,  2.0));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0.5,  type()( -2.5, -5.0));
		static_assert(!has_is_transparent<type>::value, "");
	}
	{
		using type = hamon::divides<>;
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 2.0,  type()( 1,   0.5));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-0.25, type()(-2.0, 8U));
		static_assert( has_is_transparent<type>::value, "");
	}
}

}	// namespace divides_test

}	// namespace hamon_functional_test
