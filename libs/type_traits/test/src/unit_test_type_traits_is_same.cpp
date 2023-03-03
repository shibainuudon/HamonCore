/**
 *	@file	unit_test_type_traits_is_same.cpp
 *
 *	@brief	is_same のテスト
 */

#include <hamon/type_traits/is_same.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include <cstddef>
#include "type_traits_test_utility.hpp"

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

#define HAMON_IS_SAME_TEST(b, T1, T2)	\
	static_assert(hamon::is_same_v<T1, T2>      == b, #T1 ", " #T2);	\
	static_assert(hamon::is_same<T1, T2>::value == b, #T1 ", " #T2);	\
	static_assert(hamon::is_same<T1, T2>{}()    == b, #T1 ", " #T2);	\
	static_assert(hamon::is_same<T1, T2>{}      == b, #T1 ", " #T2)

#else

#define HAMON_IS_SAME_TEST(b, T1, T2)	\
	static_assert(hamon::is_same<T1, T2>::value == b, #T1 ", " #T2);	\
	static_assert(hamon::is_same<T1, T2>{}()    == b, #T1 ", " #T2);	\
	static_assert(hamon::is_same<T1, T2>{}      == b, #T1 ", " #T2)

#endif

HAMON_IS_SAME_TEST(true,                 int,                int);
HAMON_IS_SAME_TEST(false,                int, const          int);
HAMON_IS_SAME_TEST(false,                int,       volatile int);
HAMON_IS_SAME_TEST(false,                int, const volatile int);
HAMON_IS_SAME_TEST(false, const          int,                int);
HAMON_IS_SAME_TEST(true,  const          int, const          int);
HAMON_IS_SAME_TEST(false, const          int,       volatile int);
HAMON_IS_SAME_TEST(false, const          int, const volatile int);
HAMON_IS_SAME_TEST(false,       volatile int,                int);
HAMON_IS_SAME_TEST(false,       volatile int, const          int);
HAMON_IS_SAME_TEST(true,        volatile int,       volatile int);
HAMON_IS_SAME_TEST(false,       volatile int, const volatile int);
HAMON_IS_SAME_TEST(false, const volatile int,                int);
HAMON_IS_SAME_TEST(false, const volatile int, const          int);
HAMON_IS_SAME_TEST(false, const volatile int,       volatile int);
HAMON_IS_SAME_TEST(true,  const volatile int, const volatile int);
HAMON_IS_SAME_TEST(false, int, int*);
HAMON_IS_SAME_TEST(false, int, int&);
HAMON_IS_SAME_TEST(false, int, int&&);
HAMON_IS_SAME_TEST(false, int, int[2]);
HAMON_IS_SAME_TEST(false, int, int[]);
HAMON_IS_SAME_TEST(false, int, int(&)[2]);
HAMON_IS_SAME_TEST(false, int, int(&)[]);
HAMON_IS_SAME_TEST(false, int, int(&&)[2]);
HAMON_IS_SAME_TEST(false, int, int(&&)[]);

HAMON_IS_SAME_TEST(false, int*, int);
HAMON_IS_SAME_TEST(true,  int*, int*);
HAMON_IS_SAME_TEST(false, int*, int&);
HAMON_IS_SAME_TEST(false, int*, int&&);
HAMON_IS_SAME_TEST(false, int*, int[2]);
HAMON_IS_SAME_TEST(false, int*, int[]);
HAMON_IS_SAME_TEST(false, int*, int(&)[2]);
HAMON_IS_SAME_TEST(false, int*, int(&)[]);
HAMON_IS_SAME_TEST(false, int*, int(&&)[2]);
HAMON_IS_SAME_TEST(false, int*, int(&&)[]);

HAMON_IS_SAME_TEST(false, int&, int);
HAMON_IS_SAME_TEST(false, int&, int*);
HAMON_IS_SAME_TEST(true,  int&, int&);
HAMON_IS_SAME_TEST(false, int&, int&&);
HAMON_IS_SAME_TEST(false, int&, int[2]);
HAMON_IS_SAME_TEST(false, int&, int[]);
HAMON_IS_SAME_TEST(false, int&, int(&)[2]);
HAMON_IS_SAME_TEST(false, int&, int(&)[]);
HAMON_IS_SAME_TEST(false, int&, int(&&)[2]);
HAMON_IS_SAME_TEST(false, int&, int(&&)[]);

HAMON_IS_SAME_TEST(false, int&&, int);
HAMON_IS_SAME_TEST(false, int&&, int*);
HAMON_IS_SAME_TEST(false, int&&, int&);
HAMON_IS_SAME_TEST(true,  int&&, int&&);
HAMON_IS_SAME_TEST(false, int&&, int[2]);
HAMON_IS_SAME_TEST(false, int&&, int[]);
HAMON_IS_SAME_TEST(false, int&&, int(&)[2]);
HAMON_IS_SAME_TEST(false, int&&, int(&)[]);
HAMON_IS_SAME_TEST(false, int&&, int(&&)[2]);
HAMON_IS_SAME_TEST(false, int&&, int(&&)[]);

HAMON_IS_SAME_TEST(false, int[2], int);
HAMON_IS_SAME_TEST(false, int[2], int*);
HAMON_IS_SAME_TEST(false, int[2], int&);
HAMON_IS_SAME_TEST(false, int[2], int&&);
HAMON_IS_SAME_TEST(true,  int[2], int[2]);
HAMON_IS_SAME_TEST(false, int[2], int[]);
HAMON_IS_SAME_TEST(false, int[2], int(&)[2]);
HAMON_IS_SAME_TEST(false, int[2], int(&)[]);
HAMON_IS_SAME_TEST(false, int[2], int(&&)[2]);
HAMON_IS_SAME_TEST(false, int[2], int(&&)[]);

HAMON_IS_SAME_TEST(false, int[], int);
HAMON_IS_SAME_TEST(false, int[], int*);
HAMON_IS_SAME_TEST(false, int[], int&);
HAMON_IS_SAME_TEST(false, int[], int&&);
HAMON_IS_SAME_TEST(false, int[], int[2]);
HAMON_IS_SAME_TEST(true,  int[], int[]);
HAMON_IS_SAME_TEST(false, int[], int(&)[2]);
HAMON_IS_SAME_TEST(false, int[], int(&)[]);
HAMON_IS_SAME_TEST(false, int[], int(&&)[2]);
HAMON_IS_SAME_TEST(false, int[], int(&&)[]);

HAMON_IS_SAME_TEST(false, int(&)[2], int);
HAMON_IS_SAME_TEST(false, int(&)[2], int*);
HAMON_IS_SAME_TEST(false, int(&)[2], int&);
HAMON_IS_SAME_TEST(false, int(&)[2], int&&);
HAMON_IS_SAME_TEST(false, int(&)[2], int[2]);
HAMON_IS_SAME_TEST(false, int(&)[2], int[]);
HAMON_IS_SAME_TEST(true,  int(&)[2], int(&)[2]);
HAMON_IS_SAME_TEST(false, int(&)[2], int(&)[]);
HAMON_IS_SAME_TEST(false, int(&)[2], int(&&)[2]);
HAMON_IS_SAME_TEST(false, int(&)[2], int(&&)[]);

HAMON_IS_SAME_TEST(false, int(&)[], int);
HAMON_IS_SAME_TEST(false, int(&)[], int*);
HAMON_IS_SAME_TEST(false, int(&)[], int&);
HAMON_IS_SAME_TEST(false, int(&)[], int&&);
HAMON_IS_SAME_TEST(false, int(&)[], int[2]);
HAMON_IS_SAME_TEST(false, int(&)[], int[]);
HAMON_IS_SAME_TEST(false, int(&)[], int(&)[2]);
HAMON_IS_SAME_TEST(true,  int(&)[], int(&)[]);
HAMON_IS_SAME_TEST(false, int(&)[], int(&&)[2]);
HAMON_IS_SAME_TEST(false, int(&)[], int(&&)[]);

HAMON_IS_SAME_TEST(false, int(&&)[2], int);
HAMON_IS_SAME_TEST(false, int(&&)[2], int*);
HAMON_IS_SAME_TEST(false, int(&&)[2], int&);
HAMON_IS_SAME_TEST(false, int(&&)[2], int&&);
HAMON_IS_SAME_TEST(false, int(&&)[2], int[2]);
HAMON_IS_SAME_TEST(false, int(&&)[2], int[]);
HAMON_IS_SAME_TEST(false, int(&&)[2], int(&)[2]);
HAMON_IS_SAME_TEST(false, int(&&)[2], int(&)[]);
HAMON_IS_SAME_TEST(true,  int(&&)[2], int(&&)[2]);
HAMON_IS_SAME_TEST(false, int(&&)[2], int(&&)[]);

HAMON_IS_SAME_TEST(false, int(&&)[], int);
HAMON_IS_SAME_TEST(false, int(&&)[], int*);
HAMON_IS_SAME_TEST(false, int(&&)[], int&);
HAMON_IS_SAME_TEST(false, int(&&)[], int&&);
HAMON_IS_SAME_TEST(false, int(&&)[], int[2]);
HAMON_IS_SAME_TEST(false, int(&&)[], int[]);
HAMON_IS_SAME_TEST(false, int(&&)[], int(&)[2]);
HAMON_IS_SAME_TEST(false, int(&&)[], int(&)[]);
HAMON_IS_SAME_TEST(false, int(&&)[], int(&&)[2]);
HAMON_IS_SAME_TEST(true,  int(&&)[], int(&&)[]);

HAMON_IS_SAME_TEST(true,                 void,                void);
HAMON_IS_SAME_TEST(false,                void, const          void);
HAMON_IS_SAME_TEST(false,                void,       volatile void);
HAMON_IS_SAME_TEST(false,                void, const volatile void);
HAMON_IS_SAME_TEST(false, const          void,                void);
HAMON_IS_SAME_TEST(true,  const          void, const          void);
HAMON_IS_SAME_TEST(false, const          void,       volatile void);
HAMON_IS_SAME_TEST(false, const          void, const volatile void);
HAMON_IS_SAME_TEST(false,       volatile void,                void);
HAMON_IS_SAME_TEST(false,       volatile void, const          void);
HAMON_IS_SAME_TEST(true,        volatile void,       volatile void);
HAMON_IS_SAME_TEST(false,       volatile void, const volatile void);
HAMON_IS_SAME_TEST(false, const volatile void,                void);
HAMON_IS_SAME_TEST(false, const volatile void, const          void);
HAMON_IS_SAME_TEST(false, const volatile void,       volatile void);
HAMON_IS_SAME_TEST(true,  const volatile void, const volatile void);

HAMON_IS_SAME_TEST(true, decltype(nullptr), std::nullptr_t);
HAMON_IS_SAME_TEST(false, int, char);
HAMON_IS_SAME_TEST(false, int, unsigned int);
HAMON_IS_SAME_TEST(false, int[2], int[3]);
HAMON_IS_SAME_TEST(false, int[2], long[2]);
HAMON_IS_SAME_TEST(false, int, enum_UDT);
HAMON_IS_SAME_TEST(false, int, enum_class_UDT);
HAMON_IS_SAME_TEST(false, int, int_constructible);
HAMON_IS_SAME_TEST(false, int, int_convertible);
HAMON_IS_SAME_TEST(false, Base, Derived);
HAMON_IS_SAME_TEST(false, Base, Derived2);

#undef HAMON_IS_SAME_TEST
