/**
 *	@file	unit_test_functional_minus.cpp
 *
 *	@brief	minus のテスト
 */

#include <hamon/functional/minus.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "functional_test.hpp"

namespace hamon_functional_test
{

namespace minus_test
{


GTEST_TEST(FunctionalTest, MinusTest)
{
	{
		using type = hamon::minus<int>;
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, type()(  0,  0));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(47, type()( 42, -5));
		static_assert(!has_is_transparent<type>::value, "");
	}
	{
		using type = hamon::minus<float>;
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-1.75, type()(  0.5,  2.25));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 3.5,  type()( -1.5, -5.0));
		static_assert(!has_is_transparent<type>::value, "");
	}
	{
		using type = hamon::minus<>;
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0.5, type()(  1,   0.5));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-9.5, type()( -1.5, 8U));
		static_assert( has_is_transparent<type>::value, "");
	}
}

}	// namespace minus_test

}	// namespace hamon_functional_test
