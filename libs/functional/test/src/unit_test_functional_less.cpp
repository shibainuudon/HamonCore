/**
 *	@file	unit_test_functional_less.cpp
 *
 *	@brief	less のテスト
 */

#include <hamon/functional/less.hpp>
#include <hamon/string.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "functional_test.hpp"

namespace hamon_functional_test
{

namespace less_test
{

GTEST_TEST(FunctionalTest, LessTest)
{
	{
		using type = hamon::less<int>;
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(type()(2, 2));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (type()(2, 3));
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(type()(2, 1));
		static_assert(!has_is_transparent<type>::value, "");
	}
	{
		using type = hamon::less<float>;
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(type()(-1.5f, -1.5f));
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(type()(-1.5f, -1.6f));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (type()(-1.6f, -1.5f));
		static_assert(!has_is_transparent<type>::value, "");
	}
	{
		using type = hamon::less<>;
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(type()(3U, 3.0));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (type()(3U, 3.1));
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(type()(3U, 2.9));
		EXPECT_FALSE(type()(hamon::string("A"), "A"));
		EXPECT_TRUE (type()(hamon::string("A"), "B"));
		EXPECT_FALSE(type()(hamon::string("B"), "A"));
		static_assert( has_is_transparent<type>::value, "");
	}
}

}	// namespace less_test

}	// namespace hamon_functional_test
