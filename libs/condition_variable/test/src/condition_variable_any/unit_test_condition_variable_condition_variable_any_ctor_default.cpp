/**
 *	@file	unit_test_condition_variable_condition_variable_any_ctor_default.cpp
 *
 *	@brief	デフォルトコンストラクタのテスト
 *
 *	condition_variable_any();
 */

#include <hamon/condition_variable/condition_variable_any.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>

namespace hamon_condition_variable_any_test
{

namespace ctor_default_test
{

static_assert( hamon::is_default_constructible_v<hamon::condition_variable_any>, "");
static_assert(!hamon::is_nothrow_default_constructible_v<hamon::condition_variable_any>, "");
static_assert(!hamon::is_trivially_default_constructible_v<hamon::condition_variable_any>, "");
static_assert( hamon::is_implicitly_default_constructible_v<hamon::condition_variable_any>, "");

GTEST_TEST(ConditionVariableAnyTest, CtorDefaultTest)
{
	hamon::condition_variable_any cv;
	(void)cv;
}

}	// namespace ctor_default_test

}	// namespace hamon_condition_variable_any_test
