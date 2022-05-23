/**
 *	@file	unit_test_preprocessor_cat.cpp
 *
 *	@brief	HAMON_PP_CATのテスト
 */

#include <hamon/preprocessor/cat.hpp>
#include <gtest/gtest.h>

namespace hamon_preprocessor_test
{

namespace cat_test
{

#define HAMON_GEN_FUNC(name, i)	\
	int HAMON_PP_CAT(name, HAMON_PP_CAT(_, i))() \
	{	return i; }

HAMON_GEN_FUNC(funcA, 0)
HAMON_GEN_FUNC(funcA, 1)
HAMON_GEN_FUNC(funcA, 2)
HAMON_GEN_FUNC(funcB, 1)
HAMON_GEN_FUNC(funcB, 2)
HAMON_GEN_FUNC(funcB, 3)
HAMON_GEN_FUNC(funcB, 4)
HAMON_GEN_FUNC(funcB, 5)

#undef HAMON_GEN_FUNC

GTEST_TEST(PreprocessorTest, CatTest)
{
	EXPECT_EQ(0, funcA_0());
	EXPECT_EQ(1, funcA_1());
	EXPECT_EQ(2, funcA_2());
	EXPECT_EQ(1, funcB_1());
	EXPECT_EQ(2, funcB_2());
	EXPECT_EQ(3, funcB_3());
	EXPECT_EQ(4, funcB_4());
	EXPECT_EQ(5, funcB_5());
}

}	// namespace cat_test

}	// namespace hamon_preprocessor_test
