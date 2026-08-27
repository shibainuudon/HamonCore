/**
 *	@file	numbers_test.hpp
 *
 *	@brief
 */

#ifndef UNIT_TEST_NUMBERS_NUMBERS_TEST_HPP
#define UNIT_TEST_NUMBERS_NUMBERS_TEST_HPP

#define HAMON_NUMBERS_TEST(X, expected, error)	\
	EXPECT_NEAR((double)(HAMON_PP_CAT(X, _v)<T>), (double)(expected), error);	\
	EXPECT_EQ(X, HAMON_PP_CAT(X, _v)<double>)

#endif // UNIT_TEST_NUMBERS_NUMBERS_TEST_HPP
