/**
 *	@file	unit_test_type_traits_float_promote.cpp
 *
 *	@brief	float_promote のテスト
 */

#include <hamon/type_traits/float_promote.hpp>
#include <hamon/type_traits/is_same.hpp>

#define HAMON_FLOAT_PROMOTE_TEST(T, ...)	\
	static_assert(hamon::is_same<T, hamon::float_promote<__VA_ARGS__>::type>::value, "");	\
	static_assert(hamon::is_same<T, hamon::float_promote_t<__VA_ARGS__>>::value, "")

HAMON_FLOAT_PROMOTE_TEST(float, float);
HAMON_FLOAT_PROMOTE_TEST(double, double);
HAMON_FLOAT_PROMOTE_TEST(long double, long double);
HAMON_FLOAT_PROMOTE_TEST(double, int);
HAMON_FLOAT_PROMOTE_TEST(double, char);
HAMON_FLOAT_PROMOTE_TEST(double, short);
HAMON_FLOAT_PROMOTE_TEST(double, long);
HAMON_FLOAT_PROMOTE_TEST(double, long long);
HAMON_FLOAT_PROMOTE_TEST(double, unsigned int);
HAMON_FLOAT_PROMOTE_TEST(double, unsigned char);
HAMON_FLOAT_PROMOTE_TEST(double, unsigned short);
HAMON_FLOAT_PROMOTE_TEST(double, unsigned long);
HAMON_FLOAT_PROMOTE_TEST(double, unsigned long long);

HAMON_FLOAT_PROMOTE_TEST(float, float, float);
HAMON_FLOAT_PROMOTE_TEST(double, float, double);
HAMON_FLOAT_PROMOTE_TEST(long double, float, long double);
HAMON_FLOAT_PROMOTE_TEST(double, double, float);
HAMON_FLOAT_PROMOTE_TEST(double, double, double);
HAMON_FLOAT_PROMOTE_TEST(long double, double, long double);
HAMON_FLOAT_PROMOTE_TEST(long double, long double, float);
HAMON_FLOAT_PROMOTE_TEST(long double, long double, double);
HAMON_FLOAT_PROMOTE_TEST(long double, long double, long double);

HAMON_FLOAT_PROMOTE_TEST(double, int, int);
HAMON_FLOAT_PROMOTE_TEST(double, int, char);
HAMON_FLOAT_PROMOTE_TEST(double, int, float);
HAMON_FLOAT_PROMOTE_TEST(double, int, double);
HAMON_FLOAT_PROMOTE_TEST(long double, int, long double);
HAMON_FLOAT_PROMOTE_TEST(double, float, int);
HAMON_FLOAT_PROMOTE_TEST(double, float, char);
HAMON_FLOAT_PROMOTE_TEST(double, double, int);
HAMON_FLOAT_PROMOTE_TEST(double, double, char);
HAMON_FLOAT_PROMOTE_TEST(long double, long double, int);
HAMON_FLOAT_PROMOTE_TEST(long double, long double, char);

HAMON_FLOAT_PROMOTE_TEST(double, int, int, int);
HAMON_FLOAT_PROMOTE_TEST(double, int, int, float);
HAMON_FLOAT_PROMOTE_TEST(double, int, float, int);
HAMON_FLOAT_PROMOTE_TEST(double, int, float, float);
HAMON_FLOAT_PROMOTE_TEST(double, float, int, int);
HAMON_FLOAT_PROMOTE_TEST(double, float, int, float);
HAMON_FLOAT_PROMOTE_TEST(double, float, float, int);
HAMON_FLOAT_PROMOTE_TEST(float, float, float, float);

HAMON_FLOAT_PROMOTE_TEST(double, int, int, double);
HAMON_FLOAT_PROMOTE_TEST(double, int, double, int);
HAMON_FLOAT_PROMOTE_TEST(double, int, double, double);
HAMON_FLOAT_PROMOTE_TEST(double, double, int, int);
HAMON_FLOAT_PROMOTE_TEST(double, double, int, double);
HAMON_FLOAT_PROMOTE_TEST(double, double, double, int);
HAMON_FLOAT_PROMOTE_TEST(double, double, double, double);

HAMON_FLOAT_PROMOTE_TEST(long double, int, int, long double);
HAMON_FLOAT_PROMOTE_TEST(long double, int, long double, int);
HAMON_FLOAT_PROMOTE_TEST(long double, int, long double, long double);
HAMON_FLOAT_PROMOTE_TEST(long double, long double, int, int);
HAMON_FLOAT_PROMOTE_TEST(long double, long double, int, long double);
HAMON_FLOAT_PROMOTE_TEST(long double, long double, long double, int);
HAMON_FLOAT_PROMOTE_TEST(long double, long double, long double, long double);

HAMON_FLOAT_PROMOTE_TEST(double, float, float, double);
HAMON_FLOAT_PROMOTE_TEST(long double, float, float, long double);

#undef HAMON_FLOAT_PROMOTE_TEST
