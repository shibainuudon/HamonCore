/**
 *	@file	unit_test_condition_variable_condition_variable_ctor_default.cpp
 *
 *	@brief	デフォルトコンストラクタのテスト
 *
 *	condition_variable();
 */

#include <hamon/condition_variable/condition_variable.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>

namespace hamon_condition_variable_test
{

namespace ctor_default_test
{

static_assert( hamon::is_default_constructible_v<hamon::condition_variable>, "");
static_assert(!hamon::is_nothrow_default_constructible_v<hamon::condition_variable>, "");
static_assert(!hamon::is_trivially_default_constructible_v<hamon::condition_variable>, "");
static_assert( hamon::is_implicitly_default_constructible_v<hamon::condition_variable>, "");

// [thread.condition.condvar]/1
static_assert(hamon::is_standard_layout_v<hamon::condition_variable>, "");

GTEST_TEST(ConditionVariableTest, CtorDefaultTest)
{
	hamon::condition_variable cv;
	(void)cv;
}

}	// namespace ctor_default_test

}	// namespace hamon_condition_variable_test
