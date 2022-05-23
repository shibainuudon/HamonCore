/**
 *	@file	unit_test_preprocessor_variadic_size.cpp
 *
 *	@brief	HAMON_PP_VARIADIC_SIZEのテスト
 */

#include <hamon/preprocessor/variadic/size.hpp>
#include <gtest/gtest.h>

GTEST_TEST(PreprocessorTest, VariadicSizeTest)
{
	static_assert(HAMON_PP_VARIADIC_SIZE() == 1, "");
	static_assert(HAMON_PP_VARIADIC_SIZE(1) == 1, "");
	static_assert(HAMON_PP_VARIADIC_SIZE(1, 1) == 2, "");
	static_assert(HAMON_PP_VARIADIC_SIZE(1, 1, 1) == 3, "");
	static_assert(HAMON_PP_VARIADIC_SIZE(1, 1, 1, 1) == 4, "");
}
