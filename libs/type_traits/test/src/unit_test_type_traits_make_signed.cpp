/**
 *	@file	unit_test_type_traits_make_signed.cpp
 *
 *	@brief	make_signed のテスト
 */

#include <hamon/type_traits/make_signed.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/is_integral.hpp>
#include <hamon/type_traits/is_signed.hpp>
#include <gtest/gtest.h>
#include "type_traits_test_utility.hpp"

#define HAMON_MAKE_SIGNED_TEST_1(T)	\
	static_assert(hamon::is_integral<hamon::make_signed<T>::type>::value, "");	\
	static_assert(hamon::is_signed<hamon::make_signed<T>::type>::value, "");	\
	static_assert(sizeof(hamon::make_signed<T>::type) == sizeof(T), "")

#define HAMON_MAKE_SIGNED_TEST_2(T1, T2)	\
	static_assert(hamon::is_same<hamon::make_signed<T1>::type, T2>::value, #T1 ", " #T2);	\
	static_assert(hamon::is_same<hamon::make_signed_t<T1>,     T2>::value, #T1 ", " #T2)

#define HAMON_MAKE_SIGNED_TEST(T1, T2)	\
	HAMON_MAKE_SIGNED_TEST_1(T1);	\
	HAMON_MAKE_SIGNED_TEST_2(               T1,                T2);	\
	HAMON_MAKE_SIGNED_TEST_2(const          T1, const          T2);	\
	HAMON_MAKE_SIGNED_TEST_2(      volatile T1,       volatile T2);	\
	HAMON_MAKE_SIGNED_TEST_2(const volatile T1, const volatile T2)

HAMON_MAKE_SIGNED_TEST(char,				signed char);
HAMON_MAKE_SIGNED_TEST(signed char,			signed char);
HAMON_MAKE_SIGNED_TEST(short,				signed short);
HAMON_MAKE_SIGNED_TEST(int,					signed int);
HAMON_MAKE_SIGNED_TEST(long,				signed long);
HAMON_MAKE_SIGNED_TEST(long long,			signed long long);
HAMON_MAKE_SIGNED_TEST(unsigned char,		signed char);
HAMON_MAKE_SIGNED_TEST(unsigned short,		signed short);
HAMON_MAKE_SIGNED_TEST(unsigned int,		signed int);
HAMON_MAKE_SIGNED_TEST(unsigned long,		signed long);
HAMON_MAKE_SIGNED_TEST(unsigned long long,	signed long long);

HAMON_MAKE_SIGNED_TEST_1(wchar_t);
HAMON_MAKE_SIGNED_TEST_1(enum_UDT);
HAMON_MAKE_SIGNED_TEST_1(enum_uint32_t_UDT);
HAMON_MAKE_SIGNED_TEST_1(enum_uint16_t_UDT);
HAMON_MAKE_SIGNED_TEST_1(enum_uint8_t_UDT);
HAMON_MAKE_SIGNED_TEST_1(enum_int32_t_UDT);
HAMON_MAKE_SIGNED_TEST_1(enum_int16_t_UDT);
HAMON_MAKE_SIGNED_TEST_1(enum_int8_t_UDT);
HAMON_MAKE_SIGNED_TEST_1(enum_class_UDT);
HAMON_MAKE_SIGNED_TEST_1(enum_class_uint32_t_UDT);
HAMON_MAKE_SIGNED_TEST_1(enum_class_uint16_t_UDT);
HAMON_MAKE_SIGNED_TEST_1(enum_class_uint8_t_UDT);
HAMON_MAKE_SIGNED_TEST_1(enum_class_int32_t_UDT);
HAMON_MAKE_SIGNED_TEST_1(enum_class_int16_t_UDT);
HAMON_MAKE_SIGNED_TEST_1(enum_class_int8_t_UDT);

// integralでもenumでもないとき、またはboolのときはエラーになる
//HAMON_MAKE_SIGNED_TEST_1(bool);
//HAMON_MAKE_SIGNED_TEST_1(float);
//HAMON_MAKE_SIGNED_TEST_1(double);
//HAMON_MAKE_SIGNED_TEST_1(long double);
//HAMON_MAKE_SIGNED_TEST_1(UDT);

#undef HAMON_MAKE_SIGNED_TEST_1
#undef HAMON_MAKE_SIGNED_TEST_2
#undef HAMON_MAKE_SIGNED_TEST
