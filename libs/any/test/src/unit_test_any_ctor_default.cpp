/**
 *	@file	unit_test_any_ctor_default.cpp
 *
 *	@brief	デフォルトコンストラクタのテスト
 *
 *	constexpr any() noexcept;
 */

#include <hamon/any.hpp>
#include <hamon/type_traits/is_nothrow_default_constructible.hpp>
#include <gtest/gtest.h>

static_assert(hamon::is_nothrow_default_constructible<hamon::any>::value, "");

GTEST_TEST(AnyTest, CtorDefaultTest)
{
	hamon::any a;
	EXPECT_FALSE(a.has_value());
}
