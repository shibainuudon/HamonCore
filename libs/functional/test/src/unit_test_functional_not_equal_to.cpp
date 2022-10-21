/**
 *	@file	unit_test_functional_not_equal_to.cpp
 *
 *	@brief	not_equal_to のテスト
 */

#include <hamon/functional/not_equal_to.hpp>
#include <gtest/gtest.h>
#include <string>
#include "constexpr_test.hpp"
#include "functional_test.hpp"

namespace hamon_functional_test
{

namespace not_equal_to_test
{

GTEST_TEST(FunctionalTest, NotEqualToTest)
{
	{
		using type = hamon::not_equal_to<int>;
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(type()(0, 0));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (type()(2, 3));
		static_assert(!has_is_transparent<type>::value, "");
	}
	{
		using type = hamon::not_equal_to<float>;
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(type()(0.5,  0.5));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (type()(0.5, -0.5));
		static_assert(!has_is_transparent<type>::value, "");
	}
	{
		using type = hamon::not_equal_to<>;
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(type()(1, 1.0));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (type()(1.5, 2U));
		EXPECT_FALSE(type()(std::string("Hello"), "Hello"));
		EXPECT_TRUE (type()(std::string("Hello"), "hello"));
		static_assert( has_is_transparent<type>::value, "");
	}
}

}	// namespace not_equal_to_test

}	// namespace hamon_functional_test
