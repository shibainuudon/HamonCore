/**
 *	@file	unit_test_type_traits_is_pointer.cpp
 *
 *	@brief	is_pointer のテスト
 */

#include <hamon/type_traits/is_pointer.hpp>
#include <hamon/cstddef/nullptr_t.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "type_traits_test_utility.hpp"

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

#define HAMON_IS_POINTER_TEST_IMPL(b, T)	\
	static_assert(hamon::is_pointer_v<T>      == b, #T);	\
	static_assert(hamon::is_pointer<T>::value == b, #T);	\
	static_assert(hamon::is_pointer<T>{}()    == b, #T);	\
	static_assert(hamon::is_pointer<T>{}      == b, #T)

#else

#define HAMON_IS_POINTER_TEST_IMPL(b, T)	\
	static_assert(hamon::is_pointer<T>::value == b, #T);	\
	static_assert(hamon::is_pointer<T>{}()    == b, #T);	\
	static_assert(hamon::is_pointer<T>{}      == b, #T)

#endif

HAMON_IS_POINTER_TEST_IMPL(false,                int);
HAMON_IS_POINTER_TEST_IMPL(false, const          int);
HAMON_IS_POINTER_TEST_IMPL(false,       volatile int);
HAMON_IS_POINTER_TEST_IMPL(false, const volatile int);
HAMON_IS_POINTER_TEST_IMPL(true,                 int*);
HAMON_IS_POINTER_TEST_IMPL(true,  const          int*);
HAMON_IS_POINTER_TEST_IMPL(true,        volatile int*);
HAMON_IS_POINTER_TEST_IMPL(true,  const volatile int*);
HAMON_IS_POINTER_TEST_IMPL(true,                 int* const);
HAMON_IS_POINTER_TEST_IMPL(true,  const          int* const);
HAMON_IS_POINTER_TEST_IMPL(true,        volatile int* const);
HAMON_IS_POINTER_TEST_IMPL(true,  const volatile int* const);
HAMON_IS_POINTER_TEST_IMPL(true,                 int* volatile);
HAMON_IS_POINTER_TEST_IMPL(true,  const          int* volatile);
HAMON_IS_POINTER_TEST_IMPL(true,        volatile int* volatile);
HAMON_IS_POINTER_TEST_IMPL(true,  const volatile int* volatile);
HAMON_IS_POINTER_TEST_IMPL(true,                 int* const volatile);
HAMON_IS_POINTER_TEST_IMPL(true,  const          int* const volatile);
HAMON_IS_POINTER_TEST_IMPL(true,        volatile int* const volatile);
HAMON_IS_POINTER_TEST_IMPL(true,  const volatile int* const volatile);
HAMON_IS_POINTER_TEST_IMPL(true,  int**);
HAMON_IS_POINTER_TEST_IMPL(false, int*&);
HAMON_IS_POINTER_TEST_IMPL(false, int*&&);
HAMON_IS_POINTER_TEST_IMPL(false, int&);
HAMON_IS_POINTER_TEST_IMPL(false, int&&);
HAMON_IS_POINTER_TEST_IMPL(false, int[2]);
HAMON_IS_POINTER_TEST_IMPL(false, int[]);
HAMON_IS_POINTER_TEST_IMPL(true,  int(*)[2]);
HAMON_IS_POINTER_TEST_IMPL(true,  int(*)[]);
HAMON_IS_POINTER_TEST_IMPL(false, int(&)[2]);
HAMON_IS_POINTER_TEST_IMPL(false, int(&)[]);
HAMON_IS_POINTER_TEST_IMPL(false, int(&&)[2]);
HAMON_IS_POINTER_TEST_IMPL(false, int(&&)[]);

HAMON_IS_POINTER_TEST_IMPL(false,                UDT);
HAMON_IS_POINTER_TEST_IMPL(false, const          UDT);
HAMON_IS_POINTER_TEST_IMPL(false,       volatile UDT);
HAMON_IS_POINTER_TEST_IMPL(false, const volatile UDT);
HAMON_IS_POINTER_TEST_IMPL(true,                 UDT*);
HAMON_IS_POINTER_TEST_IMPL(true,  const          UDT*);
HAMON_IS_POINTER_TEST_IMPL(true,        volatile UDT*);
HAMON_IS_POINTER_TEST_IMPL(true,  const volatile UDT*);
HAMON_IS_POINTER_TEST_IMPL(true,                 UDT* const);
HAMON_IS_POINTER_TEST_IMPL(true,  const          UDT* const);
HAMON_IS_POINTER_TEST_IMPL(true,        volatile UDT* const);
HAMON_IS_POINTER_TEST_IMPL(true,  const volatile UDT* const);
HAMON_IS_POINTER_TEST_IMPL(true,                 UDT* volatile);
HAMON_IS_POINTER_TEST_IMPL(true,  const          UDT* volatile);
HAMON_IS_POINTER_TEST_IMPL(true,        volatile UDT* volatile);
HAMON_IS_POINTER_TEST_IMPL(true,  const volatile UDT* volatile);
HAMON_IS_POINTER_TEST_IMPL(true,                 UDT* const volatile);
HAMON_IS_POINTER_TEST_IMPL(true,  const          UDT* const volatile);
HAMON_IS_POINTER_TEST_IMPL(true,        volatile UDT* const volatile);
HAMON_IS_POINTER_TEST_IMPL(true,  const volatile UDT* const volatile);
HAMON_IS_POINTER_TEST_IMPL(true,  UDT**);
HAMON_IS_POINTER_TEST_IMPL(false, UDT*&);
HAMON_IS_POINTER_TEST_IMPL(false, UDT*&&);
HAMON_IS_POINTER_TEST_IMPL(false, UDT&);
HAMON_IS_POINTER_TEST_IMPL(false, UDT&&);
HAMON_IS_POINTER_TEST_IMPL(false, UDT[2]);
HAMON_IS_POINTER_TEST_IMPL(false, UDT[]);
HAMON_IS_POINTER_TEST_IMPL(true,  UDT(*)[2]);
HAMON_IS_POINTER_TEST_IMPL(true,  UDT(*)[]);
HAMON_IS_POINTER_TEST_IMPL(false, UDT(&)[2]);
HAMON_IS_POINTER_TEST_IMPL(false, UDT(&)[]);
HAMON_IS_POINTER_TEST_IMPL(false, UDT(&&)[2]);
HAMON_IS_POINTER_TEST_IMPL(false, UDT(&&)[]);

HAMON_IS_POINTER_TEST_IMPL(false,                void);
HAMON_IS_POINTER_TEST_IMPL(false, const          void);
HAMON_IS_POINTER_TEST_IMPL(false,       volatile void);
HAMON_IS_POINTER_TEST_IMPL(false, const volatile void);
HAMON_IS_POINTER_TEST_IMPL(true,                 void*);
HAMON_IS_POINTER_TEST_IMPL(true,  const          void*);
HAMON_IS_POINTER_TEST_IMPL(true,        volatile void*);
HAMON_IS_POINTER_TEST_IMPL(true,  const volatile void*);

HAMON_IS_POINTER_TEST_IMPL(false, hamon::nullptr_t);
HAMON_IS_POINTER_TEST_IMPL(false, decltype(nullptr));
HAMON_IS_POINTER_TEST_IMPL(true,  f1);
HAMON_IS_POINTER_TEST_IMPL(true,  f2);
HAMON_IS_POINTER_TEST_IMPL(true,  f3);
HAMON_IS_POINTER_TEST_IMPL(false, mf1);
HAMON_IS_POINTER_TEST_IMPL(false, mf2);
HAMON_IS_POINTER_TEST_IMPL(false, mf3);
HAMON_IS_POINTER_TEST_IMPL(false, mf4);
HAMON_IS_POINTER_TEST_IMPL(false, mp);
HAMON_IS_POINTER_TEST_IMPL(false, cmf);
HAMON_IS_POINTER_TEST_IMPL(false, foo0_t);
HAMON_IS_POINTER_TEST_IMPL(false, foo1_t);
HAMON_IS_POINTER_TEST_IMPL(false, foo2_t);
HAMON_IS_POINTER_TEST_IMPL(false, foo3_t);
HAMON_IS_POINTER_TEST_IMPL(false, foo4_t);

#undef HAMON_IS_POINTER_TEST_IMPL
