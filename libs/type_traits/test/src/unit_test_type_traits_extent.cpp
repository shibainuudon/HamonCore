/**
 *	@file	unit_test_type_traits_extent.cpp
 *
 *	@brief	extent のテスト
 */

#include <hamon/type_traits/extent.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "type_traits_test_utility.hpp"

namespace type_traits_test
{

namespace alignment_of_test
{

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

#define HAMON_EXTENT_TEST(n, T)	\
	static_assert(n == hamon::extent_v<T>,      #T);	\
	static_assert(n == hamon::extent<T>::value, #T);	\
	static_assert(n == hamon::extent<T>{}(),    #T);	\
	static_assert(n == hamon::extent<T>{},      #T)

#define HAMON_EXTENT_TEST_2(n, T, i)	\
	static_assert(n == hamon::extent_v<T, i>,      #T);	\
	static_assert(n == hamon::extent<T, i>::value, #T);	\
	static_assert(n == hamon::extent<T, i>{}(),    #T);	\
	static_assert(n == hamon::extent<T, i>{},      #T)

#else

#define HAMON_EXTENT_TEST(n, T)	\
	static_assert(n == hamon::extent<T>::value, #T);	\
	static_assert(n == hamon::extent<T>{}(),    #T);	\
	static_assert(n == hamon::extent<T>{},      #T)

#define HAMON_EXTENT_TEST_2(n, T, i)	\
	static_assert(n == hamon::extent<T, i>::value, #T);	\
	static_assert(n == hamon::extent<T, i>{}(),    #T);	\
	static_assert(n == hamon::extent<T, i>{},      #T)

#endif

HAMON_EXTENT_TEST  ( 0, int);
HAMON_EXTENT_TEST  ( 0, int*);
HAMON_EXTENT_TEST  ( 0, int&);
HAMON_EXTENT_TEST  ( 0, int&&);
HAMON_EXTENT_TEST  ( 0, int[]);
HAMON_EXTENT_TEST  ( 2, int[2]);
HAMON_EXTENT_TEST  ( 3, int[3]);
HAMON_EXTENT_TEST_2( 2, int[2], 0);
HAMON_EXTENT_TEST_2( 0, int[2], 1);
HAMON_EXTENT_TEST  ( 2, int[2][3]);
HAMON_EXTENT_TEST_2( 2, int[2][3], 0);
HAMON_EXTENT_TEST_2( 3, int[2][3], 1);
HAMON_EXTENT_TEST_2( 0, int[2][3], 2);
HAMON_EXTENT_TEST_2( 5, int[5][10][40], 0);
HAMON_EXTENT_TEST_2(10, int[5][10][40], 1);
HAMON_EXTENT_TEST_2(40, int[5][10][40], 2);
HAMON_EXTENT_TEST_2( 0, int[5][10][40], 3);
HAMON_EXTENT_TEST  ( 0, int(&)[2]);
HAMON_EXTENT_TEST  ( 0, int(&)[]);
HAMON_EXTENT_TEST  ( 0, int(&&)[2]);
HAMON_EXTENT_TEST  ( 0, int(&&)[]);

HAMON_EXTENT_TEST  ( 0, UDT);
HAMON_EXTENT_TEST  ( 0, UDT*);
HAMON_EXTENT_TEST  ( 0, UDT&);
HAMON_EXTENT_TEST  ( 0, UDT&&);
HAMON_EXTENT_TEST  ( 0, UDT[]);
HAMON_EXTENT_TEST  ( 2, UDT[2]);
HAMON_EXTENT_TEST  ( 3, UDT[3]);
HAMON_EXTENT_TEST_2( 2, UDT[2], 0);
HAMON_EXTENT_TEST_2( 0, UDT[2], 1);
HAMON_EXTENT_TEST  ( 2, UDT[2][3]);
HAMON_EXTENT_TEST_2( 2, UDT[2][3], 0);
HAMON_EXTENT_TEST_2( 3, UDT[2][3], 1);
HAMON_EXTENT_TEST_2( 0, UDT[2][3], 2);
HAMON_EXTENT_TEST_2( 5, UDT[5][10][40], 0);
HAMON_EXTENT_TEST_2(10, UDT[5][10][40], 1);
HAMON_EXTENT_TEST_2(40, UDT[5][10][40], 2);
HAMON_EXTENT_TEST_2( 0, UDT[5][10][40], 3);
HAMON_EXTENT_TEST  ( 0, UDT(&)[2]);
HAMON_EXTENT_TEST  ( 0, UDT(&)[]);
HAMON_EXTENT_TEST  ( 0, UDT(&&)[2]);
HAMON_EXTENT_TEST  ( 0, UDT(&&)[]);

#undef HAMON_EXTENT_TEST
#undef HAMON_EXTENT_TEST_2

}	// namespace alignment_of_test

}	// namespace type_traits_test
