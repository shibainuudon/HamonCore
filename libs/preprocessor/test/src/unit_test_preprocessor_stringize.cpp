/**
 *	@file	unit_test_preprocessor_stringize.cpp
 *
 *	@brief	HAMON_PP_STRINGIZEのテスト
 */

#include <hamon/preprocessor/stringize.hpp>
#include <hamon/preprocessor/cat.hpp>
#include <gtest/gtest.h>

GTEST_TEST(PreprocessorTest, StringizeTest)
{
	EXPECT_STREQ("ab", HAMON_PP_STRINGIZE(HAMON_PP_CAT(a, b)));
}
