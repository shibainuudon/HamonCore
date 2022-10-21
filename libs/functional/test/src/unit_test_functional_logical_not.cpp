/**
 *	@file	unit_test_functional_logical_not.cpp
 *
 *	@brief	logical_not のテスト
 */

#include <hamon/functional/logical_not.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "functional_test.hpp"

namespace hamon_functional_test
{

namespace logical_not_test
{

GTEST_TEST(FunctionalTest, LogicalNotTest)
{
	{
		using type = hamon::logical_not<bool>;
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(type()(true));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (type()(false));
		static_assert(!has_is_transparent<type>::value, "");
	}
HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4800)	// 'int' : ブール値を 'true' または 'false' に強制的に設定します
	{
		using type = hamon::logical_not<int>;
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (type()(0));
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(type()(1));
		static_assert(!has_is_transparent<type>::value, "");
	}
HAMON_WARNING_POP()
	{
		using type = hamon::logical_not<>;
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(type()(true));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (type()(false));
		static_assert( has_is_transparent<type>::value, "");
	}
}

}	// namespace logical_not_test

}	// namespace hamon_functional_test
