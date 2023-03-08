/**
 *	@file	unit_test_type_traits_is_integral.cpp
 *
 *	@brief	is_integral のテスト
 */

#include <hamon/type_traits/is_integral.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/cstddef/nullptr_t.hpp>
#include <hamon/cstdint.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "type_traits_test_utility.hpp"

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

#define HAMON_IS_INTEGRAL_TEST(b, T)	\
	static_assert(hamon::is_integral_v<T>      == b, #T);	\
	static_assert(hamon::is_integral<T>::value == b, #T);	\
	static_assert(hamon::is_integral<T>{}()    == b, #T);	\
	static_assert(hamon::is_integral<T>{}      == b, #T)

#else

#define HAMON_IS_INTEGRAL_TEST(b, T)	\
	static_assert(hamon::is_integral<T>::value == b, #T);	\
	static_assert(hamon::is_integral<T>{}()    == b, #T);	\
	static_assert(hamon::is_integral<T>{}      == b, #T)

#endif

#define HAMON_IS_INTEGRAL_TEST_CV(b, T)	\
	HAMON_IS_INTEGRAL_TEST(b,                T);	\
	HAMON_IS_INTEGRAL_TEST(b, const          T);	\
	HAMON_IS_INTEGRAL_TEST(b,       volatile T);	\
	HAMON_IS_INTEGRAL_TEST(b, const volatile T)

HAMON_IS_INTEGRAL_TEST_CV(true, bool);
HAMON_IS_INTEGRAL_TEST_CV(true, char);
HAMON_IS_INTEGRAL_TEST_CV(true, wchar_t);
HAMON_IS_INTEGRAL_TEST_CV(true, char16_t);
HAMON_IS_INTEGRAL_TEST_CV(true, char32_t);
HAMON_IS_INTEGRAL_TEST_CV(true, signed char);
HAMON_IS_INTEGRAL_TEST_CV(true, short);
HAMON_IS_INTEGRAL_TEST_CV(true, int);
HAMON_IS_INTEGRAL_TEST_CV(true, long);
HAMON_IS_INTEGRAL_TEST_CV(true, long long);
HAMON_IS_INTEGRAL_TEST_CV(true, unsigned char);
HAMON_IS_INTEGRAL_TEST_CV(true, unsigned short);
HAMON_IS_INTEGRAL_TEST_CV(true, unsigned int);
HAMON_IS_INTEGRAL_TEST_CV(true, unsigned long);
HAMON_IS_INTEGRAL_TEST_CV(true, unsigned long long);
HAMON_IS_INTEGRAL_TEST_CV(true, hamon::size_t);
HAMON_IS_INTEGRAL_TEST_CV(true, hamon::int8_t);
HAMON_IS_INTEGRAL_TEST_CV(true, hamon::int16_t);
HAMON_IS_INTEGRAL_TEST_CV(true, hamon::int32_t);
HAMON_IS_INTEGRAL_TEST_CV(true, hamon::int64_t);
HAMON_IS_INTEGRAL_TEST_CV(true, hamon::uint8_t);
HAMON_IS_INTEGRAL_TEST_CV(true, hamon::uint16_t);
HAMON_IS_INTEGRAL_TEST_CV(true, hamon::uint32_t);
HAMON_IS_INTEGRAL_TEST_CV(true, hamon::uint64_t);

HAMON_IS_INTEGRAL_TEST_CV(false, float);
HAMON_IS_INTEGRAL_TEST_CV(false, double);
HAMON_IS_INTEGRAL_TEST_CV(false, long double);
HAMON_IS_INTEGRAL_TEST_CV(false, int*);
HAMON_IS_INTEGRAL_TEST_CV(false, int**);
HAMON_IS_INTEGRAL_TEST_CV(false, int&);
HAMON_IS_INTEGRAL_TEST_CV(false, int&&);
HAMON_IS_INTEGRAL_TEST_CV(false, int[2]);
HAMON_IS_INTEGRAL_TEST_CV(false, int[]);
HAMON_IS_INTEGRAL_TEST_CV(false, int(*)[2]);
HAMON_IS_INTEGRAL_TEST_CV(false, int(*)[]);
HAMON_IS_INTEGRAL_TEST_CV(false, int(&)[2]);
HAMON_IS_INTEGRAL_TEST_CV(false, int(&)[]);
HAMON_IS_INTEGRAL_TEST_CV(false, int(&&)[2]);
HAMON_IS_INTEGRAL_TEST_CV(false, int(&&)[]);
HAMON_IS_INTEGRAL_TEST_CV(false, void);
HAMON_IS_INTEGRAL_TEST_CV(false, void*);
HAMON_IS_INTEGRAL_TEST_CV(false, hamon::nullptr_t);
HAMON_IS_INTEGRAL_TEST_CV(false, decltype(nullptr));
HAMON_IS_INTEGRAL_TEST_CV(false, enum_UDT);
HAMON_IS_INTEGRAL_TEST_CV(false, enum_uint32_t_UDT);
HAMON_IS_INTEGRAL_TEST_CV(false, enum_uint16_t_UDT);
HAMON_IS_INTEGRAL_TEST_CV(false, enum_uint8_t_UDT);
HAMON_IS_INTEGRAL_TEST_CV(false, enum_int32_t_UDT);
HAMON_IS_INTEGRAL_TEST_CV(false, enum_int16_t_UDT);
HAMON_IS_INTEGRAL_TEST_CV(false, enum_int8_t_UDT);
HAMON_IS_INTEGRAL_TEST_CV(false, enum_class_UDT);
HAMON_IS_INTEGRAL_TEST_CV(false, enum_class_uint32_t_UDT);
HAMON_IS_INTEGRAL_TEST_CV(false, enum_class_uint16_t_UDT);
HAMON_IS_INTEGRAL_TEST_CV(false, enum_class_uint8_t_UDT);
HAMON_IS_INTEGRAL_TEST_CV(false, enum_class_int32_t_UDT);
HAMON_IS_INTEGRAL_TEST_CV(false, enum_class_int16_t_UDT);
HAMON_IS_INTEGRAL_TEST_CV(false, enum_class_int8_t_UDT);
HAMON_IS_INTEGRAL_TEST_CV(false, UDT);
HAMON_IS_INTEGRAL_TEST_CV(false, union_UDT);
HAMON_IS_INTEGRAL_TEST_CV(false, non_pointer);
HAMON_IS_INTEGRAL_TEST_CV(false, non_int_pointer);
HAMON_IS_INTEGRAL_TEST_CV(false, int_constructible);
HAMON_IS_INTEGRAL_TEST_CV(false, int_convertible);
HAMON_IS_INTEGRAL_TEST_CV(false, incomplete_type);
HAMON_IS_INTEGRAL_TEST(false, f1);
HAMON_IS_INTEGRAL_TEST(false, f2);
HAMON_IS_INTEGRAL_TEST(false, f3);
HAMON_IS_INTEGRAL_TEST(false, mf1);
HAMON_IS_INTEGRAL_TEST(false, mf2);
HAMON_IS_INTEGRAL_TEST(false, mf3);
HAMON_IS_INTEGRAL_TEST(false, mf4);
HAMON_IS_INTEGRAL_TEST(false, mp);
HAMON_IS_INTEGRAL_TEST(false, cmf);
HAMON_IS_INTEGRAL_TEST(false, foo0_t);
HAMON_IS_INTEGRAL_TEST(false, foo1_t);
HAMON_IS_INTEGRAL_TEST(false, foo2_t);
HAMON_IS_INTEGRAL_TEST(false, foo3_t);
HAMON_IS_INTEGRAL_TEST(false, foo4_t);

#undef HAMON_IS_INTEGRAL_TEST
#undef HAMON_IS_INTEGRAL_TEST_CV
