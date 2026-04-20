/**
 *	@file	unit_test_type_traits_is_unsigned.cpp
 *
 *	@brief	is_unsigned のテスト
 */

#include <hamon/type_traits/is_unsigned.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/cstddef/nullptr_t.hpp>
#include <hamon/config.hpp>
#include <cstdint>	// WCHAR_MIN
#include <climits>	// CHAR_MIN
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

#define HAMON_IS_UNSIGNED_TEST_CV(b, T)	\
	HAMON_IS_UNSIGNED_TEST(b,                T);	\
	HAMON_IS_UNSIGNED_TEST(b, const          T);	\
	HAMON_IS_UNSIGNED_TEST(b,       volatile T);	\
	HAMON_IS_UNSIGNED_TEST(b, const volatile T)

HAMON_IS_UNSIGNED_TEST_CV(true,  unsigned int);
HAMON_IS_UNSIGNED_TEST_CV(false, unsigned int*);
HAMON_IS_UNSIGNED_TEST_CV(false, unsigned int&);
HAMON_IS_UNSIGNED_TEST_CV(false, unsigned int&&);
HAMON_IS_UNSIGNED_TEST_CV(false, unsigned int[2]);
HAMON_IS_UNSIGNED_TEST_CV(false, unsigned int[]);
HAMON_IS_UNSIGNED_TEST_CV(false, unsigned int(*)[2]);
HAMON_IS_UNSIGNED_TEST_CV(false, unsigned int(*)[]);
HAMON_IS_UNSIGNED_TEST_CV(false, unsigned int(&)[2]);
HAMON_IS_UNSIGNED_TEST_CV(false, unsigned int(&)[]);
HAMON_IS_UNSIGNED_TEST_CV(false, unsigned int(&&)[2]);
HAMON_IS_UNSIGNED_TEST_CV(false, unsigned int(&&)[]);

HAMON_IS_UNSIGNED_TEST_CV(true,  bool);
#if CHAR_MIN < 0
HAMON_IS_UNSIGNED_TEST_CV(false, char);
#else
HAMON_IS_UNSIGNED_TEST_CV(true,  char);
#endif
#if WCHAR_MIN < 0
HAMON_IS_UNSIGNED_TEST_CV(false, wchar_t);
#else
HAMON_IS_UNSIGNED_TEST_CV(true,  wchar_t);
#endif
#if defined(HAMON_HAS_CXX20_CHAR8_T)
HAMON_IS_UNSIGNED_TEST_CV(true,  char8_t);
#endif
HAMON_IS_UNSIGNED_TEST_CV(true,  char16_t);
HAMON_IS_UNSIGNED_TEST_CV(true,  char32_t);
HAMON_IS_UNSIGNED_TEST_CV(false, signed char);
HAMON_IS_UNSIGNED_TEST_CV(false, short);
HAMON_IS_UNSIGNED_TEST_CV(false, int);
HAMON_IS_UNSIGNED_TEST_CV(false, long);
HAMON_IS_UNSIGNED_TEST_CV(false, long long);
HAMON_IS_UNSIGNED_TEST_CV(true,  unsigned char);
HAMON_IS_UNSIGNED_TEST_CV(true,  unsigned short);
HAMON_IS_UNSIGNED_TEST_CV(true,  unsigned int);
HAMON_IS_UNSIGNED_TEST_CV(true,  unsigned long);
HAMON_IS_UNSIGNED_TEST_CV(true,  unsigned long long);
HAMON_IS_UNSIGNED_TEST_CV(true,  hamon::size_t);
HAMON_IS_UNSIGNED_TEST_CV(false, float);
HAMON_IS_UNSIGNED_TEST_CV(false, double);
HAMON_IS_UNSIGNED_TEST_CV(false, long double);
HAMON_IS_UNSIGNED_TEST_CV(false, void);
HAMON_IS_UNSIGNED_TEST_CV(false, void*);
HAMON_IS_UNSIGNED_TEST_CV(false, hamon::nullptr_t);
HAMON_IS_UNSIGNED_TEST_CV(false, decltype(nullptr));
HAMON_IS_UNSIGNED_TEST_CV(false, enum_UDT);
HAMON_IS_UNSIGNED_TEST_CV(false, enum_uint32_t_UDT);
HAMON_IS_UNSIGNED_TEST_CV(false, enum_uint16_t_UDT);
HAMON_IS_UNSIGNED_TEST_CV(false, enum_uint8_t_UDT);
HAMON_IS_UNSIGNED_TEST_CV(false, enum_int32_t_UDT);
HAMON_IS_UNSIGNED_TEST_CV(false, enum_int16_t_UDT);
HAMON_IS_UNSIGNED_TEST_CV(false, enum_int8_t_UDT);
HAMON_IS_UNSIGNED_TEST_CV(false, enum_class_UDT);
HAMON_IS_UNSIGNED_TEST_CV(false, enum_class_uint32_t_UDT);
HAMON_IS_UNSIGNED_TEST_CV(false, enum_class_uint16_t_UDT);
HAMON_IS_UNSIGNED_TEST_CV(false, enum_class_uint8_t_UDT);
HAMON_IS_UNSIGNED_TEST_CV(false, enum_class_int32_t_UDT);
HAMON_IS_UNSIGNED_TEST_CV(false, enum_class_int16_t_UDT);
HAMON_IS_UNSIGNED_TEST_CV(false, enum_class_int8_t_UDT);
HAMON_IS_UNSIGNED_TEST_CV(false, UDT);
HAMON_IS_UNSIGNED_TEST_CV(false, POD_UDT);
HAMON_IS_UNSIGNED_TEST_CV(false, union_UDT);
HAMON_IS_UNSIGNED_TEST_CV(false, POD_union_UDT);
HAMON_IS_UNSIGNED_TEST_CV(false, f1);
HAMON_IS_UNSIGNED_TEST_CV(false, f2);
HAMON_IS_UNSIGNED_TEST_CV(false, f3);
HAMON_IS_UNSIGNED_TEST_CV(false, mf1);
HAMON_IS_UNSIGNED_TEST_CV(false, mf2);
HAMON_IS_UNSIGNED_TEST_CV(false, mf3);
HAMON_IS_UNSIGNED_TEST_CV(false, mf4);
HAMON_IS_UNSIGNED_TEST_CV(false, mp);
HAMON_IS_UNSIGNED_TEST_CV(false, cmf);
HAMON_IS_UNSIGNED_TEST(false, foo0_t);
HAMON_IS_UNSIGNED_TEST(false, foo1_t);
HAMON_IS_UNSIGNED_TEST(false, foo2_t);
HAMON_IS_UNSIGNED_TEST(false, foo3_t);
HAMON_IS_UNSIGNED_TEST(false, foo4_t);

#undef HAMON_IS_UNSIGNED_TEST
#undef HAMON_IS_UNSIGNED_TEST_CV
