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

#define HAMON_IS_OBJECT_TEST_CV(b, T)	\
	HAMON_IS_OBJECT_TEST(b,                T);	\
	HAMON_IS_OBJECT_TEST(b, const          T);	\
	HAMON_IS_OBJECT_TEST(b,       volatile T);	\
	HAMON_IS_OBJECT_TEST(b, const volatile T)

HAMON_IS_OBJECT_TEST_CV(true,  int);
HAMON_IS_OBJECT_TEST_CV(true,  int*);
HAMON_IS_OBJECT_TEST_CV(false, int&);
HAMON_IS_OBJECT_TEST_CV(false, int&&);
HAMON_IS_OBJECT_TEST_CV(true,  int[2]);
HAMON_IS_OBJECT_TEST_CV(true,  int[]);
HAMON_IS_OBJECT_TEST_CV(true,  int(*)[2]);
HAMON_IS_OBJECT_TEST_CV(true,  int(*)[]);
HAMON_IS_OBJECT_TEST_CV(false, int(&)[2]);
HAMON_IS_OBJECT_TEST_CV(false, int(&)[]);
HAMON_IS_OBJECT_TEST_CV(false, int(&&)[2]);
HAMON_IS_OBJECT_TEST_CV(false, int(&&)[]);

HAMON_IS_OBJECT_TEST_CV(false, void);

HAMON_IS_OBJECT_TEST_CV(true,  bool);
HAMON_IS_OBJECT_TEST_CV(true,  char);
HAMON_IS_OBJECT_TEST_CV(true,  wchar_t);
#if defined(HAMON_HAS_CXX20_CHAR8_T)
HAMON_IS_OBJECT_TEST_CV(true,  char8_t);
#endif
HAMON_IS_OBJECT_TEST_CV(true,  char16_t);
HAMON_IS_OBJECT_TEST_CV(true,  char32_t);
HAMON_IS_OBJECT_TEST_CV(true,  signed char);
HAMON_IS_OBJECT_TEST_CV(true,  short);
HAMON_IS_OBJECT_TEST_CV(true,  int);
HAMON_IS_OBJECT_TEST_CV(true,  long);
HAMON_IS_OBJECT_TEST_CV(true,  long long);
HAMON_IS_OBJECT_TEST_CV(true,  unsigned char);
HAMON_IS_OBJECT_TEST_CV(true,  unsigned short);
HAMON_IS_OBJECT_TEST_CV(true,  unsigned int);
HAMON_IS_OBJECT_TEST_CV(true,  unsigned long);
HAMON_IS_OBJECT_TEST_CV(true,  unsigned long long);
HAMON_IS_OBJECT_TEST_CV(true,  float);
HAMON_IS_OBJECT_TEST_CV(true,  double);
HAMON_IS_OBJECT_TEST_CV(true,  long double);
HAMON_IS_OBJECT_TEST_CV(true,  void*);
HAMON_IS_OBJECT_TEST_CV(true,  enum_UDT);
HAMON_IS_OBJECT_TEST_CV(true,  enum_class_UDT);
HAMON_IS_OBJECT_TEST_CV(true,  UDT);
HAMON_IS_OBJECT_TEST_CV(true,  POD_UDT);
HAMON_IS_OBJECT_TEST_CV(true,  f1);
HAMON_IS_OBJECT_TEST_CV(true,  f2);
HAMON_IS_OBJECT_TEST_CV(true,  f3);
HAMON_IS_OBJECT_TEST_CV(true,  mf1);
HAMON_IS_OBJECT_TEST_CV(true,  mf2);
HAMON_IS_OBJECT_TEST_CV(true,  mf3);
HAMON_IS_OBJECT_TEST_CV(true,  mf4);
HAMON_IS_OBJECT_TEST_CV(true,  mp);
HAMON_IS_OBJECT_TEST_CV(true,  cmf);
HAMON_IS_OBJECT_TEST(false, foo0_t);
HAMON_IS_OBJECT_TEST(false, foo1_t);
HAMON_IS_OBJECT_TEST(false, foo2_t);
HAMON_IS_OBJECT_TEST(false, foo3_t);
HAMON_IS_OBJECT_TEST(false, foo4_t);

#if defined(HAMON_HAS_INT128)
HAMON_IS_OBJECT_TEST_CV(true, __int128_t);
HAMON_IS_OBJECT_TEST_CV(true, __uint128_t);
#endif

#undef HAMON_IS_OBJECT_TEST
#undef HAMON_IS_OBJECT_TEST_CV
