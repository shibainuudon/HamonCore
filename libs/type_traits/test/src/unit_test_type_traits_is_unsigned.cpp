/**
 *	@file	unit_test_type_traits_is_unsigned.cpp
 *
 *	@brief	is_unsigned のテスト
 */

#include <hamon/type_traits/is_unsigned.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/config.hpp>
#include <cstdint>	// WCHAR_MIN
#include <climits>	// CHAR_MIN
#include <cstddef>
#include <gtest/gtest.h>
#include "type_traits_test_utility.hpp"

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

#define HAMON_IS_UNSIGNED_TEST(b, T)	\
	static_assert(hamon::is_unsigned_v<T>      == b, #T);	\
	static_assert(hamon::is_unsigned<T>::value == b, #T);	\
	static_assert(hamon::is_unsigned<T>{}()    == b, #T);	\
	static_assert(hamon::is_unsigned<T>{}      == b, #T)

#else

#define HAMON_IS_UNSIGNED_TEST(b, T)	\
	static_assert(hamon::is_unsigned<T>::value == b, #T);	\
	static_assert(hamon::is_unsigned<T>{}()    == b, #T);	\
	static_assert(hamon::is_unsigned<T>{}      == b, #T)

#endif

HAMON_IS_UNSIGNED_TEST(true,                 unsigned int);
HAMON_IS_UNSIGNED_TEST(true,  const          unsigned int);
HAMON_IS_UNSIGNED_TEST(true,        volatile unsigned int);
HAMON_IS_UNSIGNED_TEST(true,  const volatile unsigned int);
HAMON_IS_UNSIGNED_TEST(false, unsigned int*);
HAMON_IS_UNSIGNED_TEST(false, unsigned int&);
HAMON_IS_UNSIGNED_TEST(false, unsigned int&&);
HAMON_IS_UNSIGNED_TEST(false, unsigned int[2]);
HAMON_IS_UNSIGNED_TEST(false, unsigned int[]);
HAMON_IS_UNSIGNED_TEST(false, unsigned int(*)[2]);
HAMON_IS_UNSIGNED_TEST(false, unsigned int(*)[]);
HAMON_IS_UNSIGNED_TEST(false, unsigned int(&)[2]);
HAMON_IS_UNSIGNED_TEST(false, unsigned int(&)[]);
HAMON_IS_UNSIGNED_TEST(false, unsigned int(&&)[2]);
HAMON_IS_UNSIGNED_TEST(false, unsigned int(&&)[]);

HAMON_IS_UNSIGNED_TEST(true, bool);
#if CHAR_MIN < 0
HAMON_IS_UNSIGNED_TEST(false, char);
#else
HAMON_IS_UNSIGNED_TEST(true, char);
#endif
#if WCHAR_MIN < 0
HAMON_IS_UNSIGNED_TEST(false, wchar_t);
#else
HAMON_IS_UNSIGNED_TEST(true, wchar_t);
#endif
HAMON_IS_UNSIGNED_TEST(false, signed char);
HAMON_IS_UNSIGNED_TEST(false, int);
HAMON_IS_UNSIGNED_TEST(false, short);
HAMON_IS_UNSIGNED_TEST(false, long);
HAMON_IS_UNSIGNED_TEST(false, long long);
HAMON_IS_UNSIGNED_TEST(true, unsigned char);
HAMON_IS_UNSIGNED_TEST(true, unsigned int);
HAMON_IS_UNSIGNED_TEST(true, unsigned short);
HAMON_IS_UNSIGNED_TEST(true, unsigned long);
HAMON_IS_UNSIGNED_TEST(true, unsigned long long);
HAMON_IS_UNSIGNED_TEST(true, hamon::size_t);
HAMON_IS_UNSIGNED_TEST(false, float);
HAMON_IS_UNSIGNED_TEST(false, double);
HAMON_IS_UNSIGNED_TEST(false, long double);
HAMON_IS_UNSIGNED_TEST(false, void);
HAMON_IS_UNSIGNED_TEST(false, void*);
HAMON_IS_UNSIGNED_TEST(false, std::nullptr_t);
HAMON_IS_UNSIGNED_TEST(false, decltype(nullptr));
HAMON_IS_UNSIGNED_TEST(false, enum_UDT);
HAMON_IS_UNSIGNED_TEST(false, enum_uint32_t_UDT);
HAMON_IS_UNSIGNED_TEST(false, enum_uint16_t_UDT);
HAMON_IS_UNSIGNED_TEST(false, enum_uint8_t_UDT);
HAMON_IS_UNSIGNED_TEST(false, enum_int32_t_UDT);
HAMON_IS_UNSIGNED_TEST(false, enum_int16_t_UDT);
HAMON_IS_UNSIGNED_TEST(false, enum_int8_t_UDT);
HAMON_IS_UNSIGNED_TEST(false, enum_class_UDT);
HAMON_IS_UNSIGNED_TEST(false, enum_class_uint32_t_UDT);
HAMON_IS_UNSIGNED_TEST(false, enum_class_uint16_t_UDT);
HAMON_IS_UNSIGNED_TEST(false, enum_class_uint8_t_UDT);
HAMON_IS_UNSIGNED_TEST(false, enum_class_int32_t_UDT);
HAMON_IS_UNSIGNED_TEST(false, enum_class_int16_t_UDT);
HAMON_IS_UNSIGNED_TEST(false, enum_class_int8_t_UDT);
HAMON_IS_UNSIGNED_TEST(false, UDT);
HAMON_IS_UNSIGNED_TEST(false, POD_UDT);
HAMON_IS_UNSIGNED_TEST(false, union_UDT);
HAMON_IS_UNSIGNED_TEST(false, POD_union_UDT);
HAMON_IS_UNSIGNED_TEST(false, f1);
HAMON_IS_UNSIGNED_TEST(false, f2);
HAMON_IS_UNSIGNED_TEST(false, f3);
HAMON_IS_UNSIGNED_TEST(false, mf1);
HAMON_IS_UNSIGNED_TEST(false, mf2);
HAMON_IS_UNSIGNED_TEST(false, mf3);
HAMON_IS_UNSIGNED_TEST(false, mf4);
HAMON_IS_UNSIGNED_TEST(false, mp);
HAMON_IS_UNSIGNED_TEST(false, cmf);
HAMON_IS_UNSIGNED_TEST(false, foo0_t);
HAMON_IS_UNSIGNED_TEST(false, foo1_t);
HAMON_IS_UNSIGNED_TEST(false, foo2_t);
HAMON_IS_UNSIGNED_TEST(false, foo3_t);
HAMON_IS_UNSIGNED_TEST(false, foo4_t);

#undef HAMON_IS_UNSIGNED_TEST
