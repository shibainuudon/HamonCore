/**
 *	@file	unit_test_type_traits_nth.cpp
 *
 *	@brief	nth のテスト
 */

#include <hamon/type_traits/nth.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>

#define HAMON_TT_NTH_TEST(N, T, ...)	\
	static_assert(hamon::is_same<T, hamon::nth<N, __VA_ARGS__>::type>::value, "");	\
	static_assert(hamon::is_same<T, hamon::nth_t<N, __VA_ARGS__>>::value, "")

HAMON_TT_NTH_TEST(0, char,   char, int, float, double);
HAMON_TT_NTH_TEST(1, int,    char, int, float, double);
HAMON_TT_NTH_TEST(2, float,  char, int, float, double);
HAMON_TT_NTH_TEST(3, double, char, int, float, double);

HAMON_TT_NTH_TEST(0, int,          int, const int, volatile int, int*, const int*, int&, const int&);
HAMON_TT_NTH_TEST(1, const int,    int, const int, volatile int, int*, const int*, int&, const int&);
HAMON_TT_NTH_TEST(2, volatile int, int, const int, volatile int, int*, const int*, int&, const int&);
HAMON_TT_NTH_TEST(3, int*,         int, const int, volatile int, int*, const int*, int&, const int&);
HAMON_TT_NTH_TEST(4, const int*,   int, const int, volatile int, int*, const int*, int&, const int&);
HAMON_TT_NTH_TEST(5, int&,         int, const int, volatile int, int*, const int*, int&, const int&);
HAMON_TT_NTH_TEST(6, const int&,   int, const int, volatile int, int*, const int*, int&, const int&);

#define HAMON_100_INTS	\
			int, int, int, int, int, int, int, int, int, int,	\
			int, int, int, int, int, int, int, int, int, int,	\
			int, int, int, int, int, int, int, int, int, int,	\
			int, int, int, int, int, int, int, int, int, int,	\
			int, int, int, int, int, int, int, int, int, int,	\
			int, int, int, int, int, int, int, int, int, int,	\
			int, int, int, int, int, int, int, int, int, int,	\
			int, int, int, int, int, int, int, int, int, int,	\
			int, int, int, int, int, int, int, int, int, int,	\
			int, int, int, int, int, int, int, int, int, int

#define HAMON_1000_INTS		\
	HAMON_100_INTS, HAMON_100_INTS, HAMON_100_INTS, HAMON_100_INTS, HAMON_100_INTS, HAMON_100_INTS, HAMON_100_INTS, HAMON_100_INTS, HAMON_100_INTS, HAMON_100_INTS

// 101 parameters
HAMON_TT_NTH_TEST(  0, int,  HAMON_100_INTS, char);
HAMON_TT_NTH_TEST(  1, int,  HAMON_100_INTS, char);
HAMON_TT_NTH_TEST(  2, int,  HAMON_100_INTS, char);
HAMON_TT_NTH_TEST(  3, int,  HAMON_100_INTS, char);
HAMON_TT_NTH_TEST(  4, int,  HAMON_100_INTS, char);
HAMON_TT_NTH_TEST(  5, int,  HAMON_100_INTS, char);
HAMON_TT_NTH_TEST(  6, int,  HAMON_100_INTS, char);
HAMON_TT_NTH_TEST(  7, int,  HAMON_100_INTS, char);
HAMON_TT_NTH_TEST(  8, int,  HAMON_100_INTS, char);
HAMON_TT_NTH_TEST(  9, int,  HAMON_100_INTS, char);
HAMON_TT_NTH_TEST( 99, int,  HAMON_100_INTS, char);
HAMON_TT_NTH_TEST(100, char, HAMON_100_INTS, char);

// 201 parameters
HAMON_TT_NTH_TEST(  0, int,  HAMON_100_INTS, HAMON_100_INTS, char);
HAMON_TT_NTH_TEST(  1, int,  HAMON_100_INTS, HAMON_100_INTS, char);
HAMON_TT_NTH_TEST(  2, int,  HAMON_100_INTS, HAMON_100_INTS, char);
HAMON_TT_NTH_TEST(  3, int,  HAMON_100_INTS, HAMON_100_INTS, char);
HAMON_TT_NTH_TEST(  4, int,  HAMON_100_INTS, HAMON_100_INTS, char);
HAMON_TT_NTH_TEST(  5, int,  HAMON_100_INTS, HAMON_100_INTS, char);
HAMON_TT_NTH_TEST(  6, int,  HAMON_100_INTS, HAMON_100_INTS, char);
HAMON_TT_NTH_TEST(  7, int,  HAMON_100_INTS, HAMON_100_INTS, char);
HAMON_TT_NTH_TEST(  8, int,  HAMON_100_INTS, HAMON_100_INTS, char);
HAMON_TT_NTH_TEST(  9, int,  HAMON_100_INTS, HAMON_100_INTS, char);
HAMON_TT_NTH_TEST( 99, int,  HAMON_100_INTS, HAMON_100_INTS, char);
HAMON_TT_NTH_TEST(100, int,  HAMON_100_INTS, HAMON_100_INTS, char);
HAMON_TT_NTH_TEST(101, int,  HAMON_100_INTS, HAMON_100_INTS, char);
HAMON_TT_NTH_TEST(199, int,  HAMON_100_INTS, HAMON_100_INTS, char);
HAMON_TT_NTH_TEST(200, char, HAMON_100_INTS, HAMON_100_INTS, char);

// 1001 parameters
HAMON_TT_NTH_TEST(   0, int,  HAMON_1000_INTS, char);
HAMON_TT_NTH_TEST( 100, int,  HAMON_1000_INTS, char);
HAMON_TT_NTH_TEST( 200, int,  HAMON_1000_INTS, char);
HAMON_TT_NTH_TEST( 300, int,  HAMON_1000_INTS, char);
HAMON_TT_NTH_TEST( 400, int,  HAMON_1000_INTS, char);
HAMON_TT_NTH_TEST( 500, int,  HAMON_1000_INTS, char);
HAMON_TT_NTH_TEST( 600, int,  HAMON_1000_INTS, char);
HAMON_TT_NTH_TEST( 700, int,  HAMON_1000_INTS, char);
HAMON_TT_NTH_TEST( 800, int,  HAMON_1000_INTS, char);
HAMON_TT_NTH_TEST( 900, int,  HAMON_1000_INTS, char);
HAMON_TT_NTH_TEST(1000, char, HAMON_1000_INTS, char);

// 2001 parameters
HAMON_TT_NTH_TEST(   0, int,  HAMON_1000_INTS, HAMON_1000_INTS, char);
HAMON_TT_NTH_TEST( 100, int,  HAMON_1000_INTS, HAMON_1000_INTS, char);
HAMON_TT_NTH_TEST( 200, int,  HAMON_1000_INTS, HAMON_1000_INTS, char);
HAMON_TT_NTH_TEST( 300, int,  HAMON_1000_INTS, HAMON_1000_INTS, char);
HAMON_TT_NTH_TEST( 400, int,  HAMON_1000_INTS, HAMON_1000_INTS, char);
HAMON_TT_NTH_TEST( 500, int,  HAMON_1000_INTS, HAMON_1000_INTS, char);
HAMON_TT_NTH_TEST( 600, int,  HAMON_1000_INTS, HAMON_1000_INTS, char);
HAMON_TT_NTH_TEST( 700, int,  HAMON_1000_INTS, HAMON_1000_INTS, char);
HAMON_TT_NTH_TEST( 800, int,  HAMON_1000_INTS, HAMON_1000_INTS, char);
HAMON_TT_NTH_TEST( 900, int,  HAMON_1000_INTS, HAMON_1000_INTS, char);
HAMON_TT_NTH_TEST(1000, int,  HAMON_1000_INTS, HAMON_1000_INTS, char);
HAMON_TT_NTH_TEST(1999, int,  HAMON_1000_INTS, HAMON_1000_INTS, char);
HAMON_TT_NTH_TEST(2000, char, HAMON_1000_INTS, HAMON_1000_INTS, char);

#undef HAMON_100_INTS
#undef HAMON_1000_INTS
#undef HAMON_TT_NTH_TEST
