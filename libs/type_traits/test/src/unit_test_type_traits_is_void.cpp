/**
 *	@file	unit_test_type_traits_is_void.cpp
 *
 *	@brief	is_void のテスト
 */

#include <hamon/type_traits/is_void.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include <cstddef>
#include "type_traits_test_utility.hpp"

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

#define HAMON_IS_VOID_TEST(b, T)	\
	static_assert(hamon::is_void_v<T>      == b, #T);	\
	static_assert(hamon::is_void<T>::value == b, #T);	\
	static_assert(hamon::is_void<T>{}()    == b, #T);	\
	static_assert(hamon::is_void<T>{}      == b, #T)

#else

#define HAMON_IS_VOID_TEST(b, T)	\
	static_assert(hamon::is_void<T>::value == b, #T);	\
	static_assert(hamon::is_void<T>{}()    == b, #T);	\
	static_assert(hamon::is_void<T>{}      == b, #T)

#endif

HAMON_IS_VOID_TEST(true,                 void);
HAMON_IS_VOID_TEST(true,  const          void);
HAMON_IS_VOID_TEST(true,        volatile void);
HAMON_IS_VOID_TEST(true,  const volatile void);

HAMON_IS_VOID_TEST(false,                int);
HAMON_IS_VOID_TEST(false, const          int);
HAMON_IS_VOID_TEST(false,       volatile int);
HAMON_IS_VOID_TEST(false, const volatile int);
HAMON_IS_VOID_TEST(false, int*);
HAMON_IS_VOID_TEST(false, int&);
HAMON_IS_VOID_TEST(false, int&&);
HAMON_IS_VOID_TEST(false, int[2]);
HAMON_IS_VOID_TEST(false, int[]);
HAMON_IS_VOID_TEST(false, int(*)[2]);
HAMON_IS_VOID_TEST(false, int(*)[]);
HAMON_IS_VOID_TEST(false, int(&)[2]);
HAMON_IS_VOID_TEST(false, int(&)[]);
HAMON_IS_VOID_TEST(false, int(&&)[2]);
HAMON_IS_VOID_TEST(false, int(&&)[]);

HAMON_IS_VOID_TEST(false, bool);
HAMON_IS_VOID_TEST(false, char);
HAMON_IS_VOID_TEST(false, wchar_t);
HAMON_IS_VOID_TEST(false, signed char);
HAMON_IS_VOID_TEST(false, short);
HAMON_IS_VOID_TEST(false, long);
HAMON_IS_VOID_TEST(false, long long);
HAMON_IS_VOID_TEST(false, unsigned char);
HAMON_IS_VOID_TEST(false, unsigned int);
HAMON_IS_VOID_TEST(false, unsigned short);
HAMON_IS_VOID_TEST(false, unsigned long);
HAMON_IS_VOID_TEST(false, unsigned long long);
HAMON_IS_VOID_TEST(false, hamon::size_t);
HAMON_IS_VOID_TEST(false, float);
HAMON_IS_VOID_TEST(false, double);
HAMON_IS_VOID_TEST(false, long double);
HAMON_IS_VOID_TEST(false, void*);
HAMON_IS_VOID_TEST(false, std::nullptr_t);
HAMON_IS_VOID_TEST(false, decltype(nullptr));
HAMON_IS_VOID_TEST(false, enum_UDT);
HAMON_IS_VOID_TEST(false, enum_uint32_t_UDT);
HAMON_IS_VOID_TEST(false, enum_class_UDT);
HAMON_IS_VOID_TEST(false, enum_class_uint32_t_UDT);
HAMON_IS_VOID_TEST(false, UDT);
HAMON_IS_VOID_TEST(false, POD_UDT);
HAMON_IS_VOID_TEST(false, union_UDT);
HAMON_IS_VOID_TEST(false, POD_union_UDT);
HAMON_IS_VOID_TEST(false, incomplete_type);
HAMON_IS_VOID_TEST(false, f1);
HAMON_IS_VOID_TEST(false, f2);
HAMON_IS_VOID_TEST(false, f3);
HAMON_IS_VOID_TEST(false, mf1);
HAMON_IS_VOID_TEST(false, mf2);
HAMON_IS_VOID_TEST(false, mf3);
HAMON_IS_VOID_TEST(false, mf4);
HAMON_IS_VOID_TEST(false, mp);
HAMON_IS_VOID_TEST(false, cmf);
HAMON_IS_VOID_TEST(false, foo0_t);
HAMON_IS_VOID_TEST(false, foo1_t);
HAMON_IS_VOID_TEST(false, foo2_t);
HAMON_IS_VOID_TEST(false, foo3_t);
HAMON_IS_VOID_TEST(false, foo4_t);

#undef HAMON_IS_VOID_TEST
