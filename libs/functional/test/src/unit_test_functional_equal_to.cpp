/**
 *	@file	unit_test_functional_equal_to.cpp
 *
 *	@brief	equal_to のテスト
 */

#include <hamon/functional/equal_to.hpp>
#include <hamon/string.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "functional_test.hpp"

namespace hamon_functional_test
{

namespace equal_to_test
{

GTEST_TEST(FunctionalTest, EqualToTest)
{
	{
		using type = hamon::equal_to<int>;
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (type()(0, 0));
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(type()(2, 3));
		static_assert(!has_is_transparent<type>::value, "");
	}
	{
		using type = hamon::equal_to<float>;
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (type()(0.5,  0.5));
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(type()(0.5, -0.5));
		static_assert(!has_is_transparent<type>::value, "");
	}
	{
		using type = hamon::equal_to<>;
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (type()(1, 1.0));
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(type()(1.5, 2U));
		EXPECT_TRUE (type()(hamon::string("Hello"), "Hello"));
		EXPECT_FALSE(type()(hamon::string("Hello"), "hello"));
		static_assert( has_is_transparent<type>::value, "");
	}
}

}	// namespace equal_to_test

}	// namespace hamon_functional_test
