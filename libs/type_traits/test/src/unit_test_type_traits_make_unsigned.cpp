/**
 *	@file	unit_test_type_traits_make_unsigned.cpp
 *
 *	@brief	make_unsigned のテスト
 */

#include <hamon/type_traits/make_unsigned.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include <type_traits>
#include "type_traits_test_utility.hpp"

#define HAMON_MAKE_UNSIGNED_TEST_1(T)	\
	static_assert(std::is_integral<hamon::make_unsigned<T>::type>::value, "");	\
	static_assert(std::is_unsigned<hamon::make_unsigned<T>::type>::value, "");	\
	static_assert(sizeof(hamon::make_unsigned<T>::type) == sizeof(T), "")

#define HAMON_MAKE_UNSIGNED_TEST_2(T1, T2)	\
	static_assert(hamon::is_same<hamon::make_unsigned<T1>::type, T2>::value, #T1 ", " #T2);	\
	static_assert(hamon::is_same<hamon::make_unsigned_t<T1>,     T2>::value, #T1 ", " #T2)

#define HAMON_MAKE_UNSIGNED_TEST(T1, T2)	\
	HAMON_MAKE_UNSIGNED_TEST_1(T1);	\
	HAMON_MAKE_UNSIGNED_TEST_2(               T1,                T2);	\
	HAMON_MAKE_UNSIGNED_TEST_2(const          T1, const          T2);	\
	HAMON_MAKE_UNSIGNED_TEST_2(      volatile T1,       volatile T2);	\
	HAMON_MAKE_UNSIGNED_TEST_2(const volatile T1, const volatile T2)

HAMON_MAKE_UNSIGNED_TEST(char,					unsigned char);
HAMON_MAKE_UNSIGNED_TEST(signed char,			unsigned char);
HAMON_MAKE_UNSIGNED_TEST(short,					unsigned short);
HAMON_MAKE_UNSIGNED_TEST(int,					unsigned int);
HAMON_MAKE_UNSIGNED_TEST(long,					unsigned long);
HAMON_MAKE_UNSIGNED_TEST(long long,				unsigned long long);
HAMON_MAKE_UNSIGNED_TEST(unsigned char,			unsigned char);
HAMON_MAKE_UNSIGNED_TEST(unsigned short,		unsigned short);
HAMON_MAKE_UNSIGNED_TEST(unsigned int,			unsigned int);
HAMON_MAKE_UNSIGNED_TEST(unsigned long,			unsigned long);
HAMON_MAKE_UNSIGNED_TEST(unsigned long long,	unsigned long long);

HAMON_MAKE_UNSIGNED_TEST_1(wchar_t);
HAMON_MAKE_UNSIGNED_TEST_1(enum_UDT);
HAMON_MAKE_UNSIGNED_TEST_1(enum_uint32_t_UDT);
HAMON_MAKE_UNSIGNED_TEST_1(enum_uint16_t_UDT);
HAMON_MAKE_UNSIGNED_TEST_1(enum_uint8_t_UDT);
HAMON_MAKE_UNSIGNED_TEST_1(enum_int32_t_UDT);
HAMON_MAKE_UNSIGNED_TEST_1(enum_int16_t_UDT);
HAMON_MAKE_UNSIGNED_TEST_1(enum_int8_t_UDT);
HAMON_MAKE_UNSIGNED_TEST_1(enum_class_UDT);
HAMON_MAKE_UNSIGNED_TEST_1(enum_class_uint32_t_UDT);
HAMON_MAKE_UNSIGNED_TEST_1(enum_class_uint16_t_UDT);
HAMON_MAKE_UNSIGNED_TEST_1(enum_class_uint8_t_UDT);
HAMON_MAKE_UNSIGNED_TEST_1(enum_class_int32_t_UDT);
HAMON_MAKE_UNSIGNED_TEST_1(enum_class_int16_t_UDT);
HAMON_MAKE_UNSIGNED_TEST_1(enum_class_int8_t_UDT);

// integralでもenumでもないとき、またはboolのときはエラーになる
//HAMON_MAKE_UNSIGNED_TEST_1(bool);
//HAMON_MAKE_UNSIGNED_TEST_1(float);
//HAMON_MAKE_UNSIGNED_TEST_1(double);
//HAMON_MAKE_UNSIGNED_TEST_1(long double);
//HAMON_MAKE_UNSIGNED_TEST_1(UDT);

#undef HAMON_MAKE_UNSIGNED_TEST_1
#undef HAMON_MAKE_UNSIGNED_TEST_2
#undef HAMON_MAKE_UNSIGNED_TEST
