/**
 *	@file	unit_test_functional_negate.cpp
 *
 *	@brief	negate のテスト
 */

#include <hamon/functional/negate.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "functional_test.hpp"

namespace hamon_functional_test
{

namespace negate_test
{

GTEST_TEST(FunctionalTest, NegateTest)
{
	{
		using type = hamon::negate<int>;
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  0, type()(  0));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( -1, type()(  1));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 42, type()(-42));
		static_assert(!has_is_transparent<type>::value, "");
	}
	{
		using type = hamon::negate<float>;
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-0.5, type()( 0.5));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1.5, type()(-1.5));
		static_assert(!has_is_transparent<type>::value, "");
	}
	{
		using type = hamon::negate<>;
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-1,   type()( 1));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 2,   type()(-2));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0.5, type()(-0.5));
		static_assert( has_is_transparent<type>::value, "");
	}
}

}	// namespace negate_test

}	// namespace hamon_functional_test
