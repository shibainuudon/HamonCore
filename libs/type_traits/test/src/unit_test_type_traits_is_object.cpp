/**
 *	@file	unit_test_type_traits_is_object.cpp
 *
 *	@brief	is_object のテスト
 */

#include <hamon/type_traits/is_object.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "type_traits_test_utility.hpp"

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

#define HAMON_IS_OBJECT_TEST(b, T)	\
	static_assert(hamon::is_object_v<T>      == b, #T);	\
	static_assert(hamon::is_object<T>::value == b, #T);	\
	static_assert(hamon::is_object<T>{}()    == b, #T);	\
	static_assert(hamon::is_object<T>{}      == b, #T)

#else

#define HAMON_IS_OBJECT_TEST(b, T)	\
	static_assert(hamon::is_object<T>::value == b, #T);	\
	static_assert(hamon::is_object<T>{}()    == b, #T);	\
	static_assert(hamon::is_object<T>{}      == b, #T)

#endif

HAMON_IS_OBJECT_TEST(true,                 int);
HAMON_IS_OBJECT_TEST(true,  const          int);
HAMON_IS_OBJECT_TEST(true,        volatile int);
HAMON_IS_OBJECT_TEST(true,  const volatile int);
HAMON_IS_OBJECT_TEST(true,                 int*);
HAMON_IS_OBJECT_TEST(true,  const          int*);
HAMON_IS_OBJECT_TEST(true,        volatile int*);
HAMON_IS_OBJECT_TEST(true,  const volatile int*);
HAMON_IS_OBJECT_TEST(false,                int&);
HAMON_IS_OBJECT_TEST(false, const          int&);
HAMON_IS_OBJECT_TEST(false,       volatile int&);
HAMON_IS_OBJECT_TEST(false, const volatile int&);
HAMON_IS_OBJECT_TEST(false,                int&&);
HAMON_IS_OBJECT_TEST(false, const          int&&);
HAMON_IS_OBJECT_TEST(false,       volatile int&&);
HAMON_IS_OBJECT_TEST(false, const volatile int&&);
HAMON_IS_OBJECT_TEST(true,                 int[2]);
HAMON_IS_OBJECT_TEST(true,  const          int[2]);
HAMON_IS_OBJECT_TEST(true,        volatile int[2]);
HAMON_IS_OBJECT_TEST(true,  const volatile int[2]);
HAMON_IS_OBJECT_TEST(true,                 int[]);
HAMON_IS_OBJECT_TEST(true,  const          int[]);
HAMON_IS_OBJECT_TEST(true,        volatile int[]);
HAMON_IS_OBJECT_TEST(true,  const volatile int[]);
HAMON_IS_OBJECT_TEST(true,  int(*)[2]);
HAMON_IS_OBJECT_TEST(true,  int(*)[]);
HAMON_IS_OBJECT_TEST(false, int(&)[2]);
HAMON_IS_OBJECT_TEST(false, int(&)[]);
HAMON_IS_OBJECT_TEST(false, int(&&)[2]);
HAMON_IS_OBJECT_TEST(false, int(&&)[]);

HAMON_IS_OBJECT_TEST(false,                void);
HAMON_IS_OBJECT_TEST(false, const          void);
HAMON_IS_OBJECT_TEST(false,       volatile void);
HAMON_IS_OBJECT_TEST(false, const volatile void);

HAMON_IS_OBJECT_TEST(true,  bool);
HAMON_IS_OBJECT_TEST(true,  char);
HAMON_IS_OBJECT_TEST(true,  float);
HAMON_IS_OBJECT_TEST(true,  void*);
HAMON_IS_OBJECT_TEST(true,  enum_UDT);
HAMON_IS_OBJECT_TEST(true,  enum_class_UDT);
HAMON_IS_OBJECT_TEST(true,  UDT);
HAMON_IS_OBJECT_TEST(true,  POD_UDT);
HAMON_IS_OBJECT_TEST(true,  f1);
HAMON_IS_OBJECT_TEST(true,  f2);
HAMON_IS_OBJECT_TEST(true,  f3);
HAMON_IS_OBJECT_TEST(true,  mf1);
HAMON_IS_OBJECT_TEST(true,  mf2);
HAMON_IS_OBJECT_TEST(true,  mf3);
HAMON_IS_OBJECT_TEST(true,  mf4);
HAMON_IS_OBJECT_TEST(true,  mp);
HAMON_IS_OBJECT_TEST(true,  cmf);
HAMON_IS_OBJECT_TEST(false, foo0_t);
HAMON_IS_OBJECT_TEST(false, foo1_t);
HAMON_IS_OBJECT_TEST(false, foo2_t);
HAMON_IS_OBJECT_TEST(false, foo3_t);
HAMON_IS_OBJECT_TEST(false, foo4_t);

#undef HAMON_IS_OBJECT_TEST
