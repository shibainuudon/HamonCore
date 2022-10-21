/**
 *	@file	unit_test_functional_logical_or.cpp
 *
 *	@brief	logical_or のテスト
 */

#include <hamon/functional/logical_or.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "functional_test.hpp"

namespace hamon_functional_test
{

namespace logical_or_test
{


GTEST_TEST(FunctionalTest, LogicalOrTest)
{
	{
		using type = hamon::logical_or<int>;
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(type()(0, 0));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (type()(1, 0));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (type()(0, 1));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (type()(1, 1));
		static_assert(!has_is_transparent<type>::value, "");
	}
	{
		using type = hamon::logical_or<>;
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(type()(false, false));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (type()(true , false));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (type()(false, true ));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (type()(true , true ));
		static_assert( has_is_transparent<type>::value, "");
	}
}

}	// namespace logical_or_test

}	// namespace hamon_functional_test
