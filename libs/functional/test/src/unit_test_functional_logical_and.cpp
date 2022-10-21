/**
 *	@file	unit_test_functional_logical_and.cpp
 *
 *	@brief	logical_and のテスト
 */

#include <hamon/functional/logical_and.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "functional_test.hpp"

namespace hamon_functional_test
{

namespace logical_and_test
{

GTEST_TEST(FunctionalTest, LogicalAndTest)
{
	{
		using type = hamon::logical_and<int>;
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(type()(0, 0));
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(type()(1, 0));
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(type()(0, 1));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (type()(1, 1));
		static_assert(!has_is_transparent<type>::value, "");
	}
	{
		using type = hamon::logical_and<>;
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(type()(false, false));
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(type()(true , false));
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(type()(false, true ));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (type()(true , true ));
		static_assert( has_is_transparent<type>::value, "");
	}
}

}	// namespace logical_and_test

}	// namespace hamon_functional_test
