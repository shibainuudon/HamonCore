﻿/**
 *	@file	unit_test_config_current_function.cpp
 *
 *	@brief	HAMON_CURRENT_FUNCTION のテスト
 */

#include <hamon/config.hpp>
#include <gtest/gtest.h>

namespace hamon_config_current_function_test
{

static char const* s_function_name_1;
static char const* s_function_name_2;
static char const* s_function_name_3;

static void f(void)
{
	s_function_name_1 = HAMON_CURRENT_FUNCTION;
}

static void f(int)
{
	s_function_name_2 = HAMON_CURRENT_FUNCTION;
}

template <typename T>
char const* f()
{
	return HAMON_CURRENT_FUNCTION;
}

GTEST_TEST(ConfigTest, CurrentFunctionTest)
{
	s_function_name_3 = HAMON_CURRENT_FUNCTION;

	f();
	f(0);

	EXPECT_TRUE(s_function_name_1 != nullptr);
	EXPECT_TRUE(s_function_name_2 != nullptr);
	EXPECT_TRUE(s_function_name_3 != nullptr);
	EXPECT_STRNE(s_function_name_1, s_function_name_2);
	EXPECT_STRNE(s_function_name_1, s_function_name_3);
	EXPECT_STRNE(s_function_name_2, s_function_name_3);

	auto s1 = f<int>();
	auto s2 = f<float>();
	EXPECT_STRNE(s1, s2);
	EXPECT_STRNE(s1, s_function_name_1);
	EXPECT_STRNE(s1, s_function_name_2);
	EXPECT_STRNE(s1, s_function_name_3);
}

}	// namespace hamon_config_current_function_test
