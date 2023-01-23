/**
 *	@file	numbers_test.hpp
 *
 *	@brief
 */

#ifndef UNIT_TEST_NUMBERS_NUMBERS_TEST_HPP
#define UNIT_TEST_NUMBERS_NUMBERS_TEST_HPP

#include <hamon/config.hpp>

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)
#define HAMON_NUMBERS_TEST(X, expected, error)	\
	EXPECT_NEAR((double)(HAMON_PP_CAT(X, _fn)<T>()), (double)(expected), error);	\
	EXPECT_EQ(HAMON_PP_CAT(X, _v)<T>, HAMON_PP_CAT(X, _fn)<T>())
#else
#define HAMON_NUMBERS_TEST(X, expected, error)	\
	EXPECT_NEAR((double)(HAMON_PP_CAT(X, _fn)<T>()), (double)(expected), error)
#endif

#endif // UNIT_TEST_NUMBERS_NUMBERS_TEST_HPP
