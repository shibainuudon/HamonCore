/**
 *	@file	unit_test_functional_plus.cpp
 *
 *	@brief	plus のテスト
 */

#include <hamon/functional/plus.hpp>
#include <hamon/string.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "functional_test.hpp"

namespace hamon_functional_test
{

namespace plus_test
{

GTEST_TEST(FunctionalTest, PlusTest)
{
	{
		using type = hamon::plus<int>;
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, type()(  0,  0));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(37, type()( 42, -5));
		static_assert(!has_is_transparent<type>::value, "");
	}
	{
		using type = hamon::plus<float>;
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 2.75, type()(  0.5,  2.25));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-6.5,  type()( -1.5, -5.0));
		static_assert(!has_is_transparent<type>::value, "");
	}
	{
		using type = hamon::plus<>;
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1.5, type()(  1,   0.5));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 6.5, type()( -1.5, 8U));
		EXPECT_EQ("Hello world", type()(hamon::string("Hello "), "world"));
		static_assert( has_is_transparent<type>::value, "");
	}
}

}	// namespace plus_test

}	// namespace hamon_functional_test
