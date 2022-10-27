/**
 *	@file	unit_test_type_traits_is_swappable_with.cpp
 *
 *	@brief	is_swappable_with のテスト
 */

#include <hamon/type_traits/is_swappable_with.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "type_traits_test_utility.hpp"

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

#define HAMON_IS_SWAPPABLE_WITH_TEST(b, T1, T2)	\
	static_assert(hamon::is_swappable_with_v<T1, T2>      == b, #T1 ", " #T2);	\
	static_assert(hamon::is_swappable_with<T1, T2>::value == b, #T1 ", " #T2);	\
	static_assert(hamon::is_swappable_with<T1, T2>()      == b, #T1 ", " #T2)

#else

#define HAMON_IS_SWAPPABLE_WITH_TEST(b, T1, T2)	\
	static_assert(hamon::is_swappable_with<T1, T2>::value == b, #T1 ", " #T2);	\
	static_assert(hamon::is_swappable_with<T1, T2>()      == b, #T1 ", " #T2)

#endif

HAMON_IS_SWAPPABLE_WITH_TEST(false,                int,                int);
HAMON_IS_SWAPPABLE_WITH_TEST(false,                int, const          int);
HAMON_IS_SWAPPABLE_WITH_TEST(false,                int,       volatile int);
HAMON_IS_SWAPPABLE_WITH_TEST(false,                int, const volatile int);
HAMON_IS_SWAPPABLE_WITH_TEST(false, const          int,                int);
#if HAMON_CXX_STANDARD >= 17
HAMON_IS_SWAPPABLE_WITH_TEST(false, const          int, const          int);
#endif
HAMON_IS_SWAPPABLE_WITH_TEST(false, const          int,       volatile int);
HAMON_IS_SWAPPABLE_WITH_TEST(false, const          int, const volatile int);
HAMON_IS_SWAPPABLE_WITH_TEST(false,       volatile int,                int);
HAMON_IS_SWAPPABLE_WITH_TEST(false,       volatile int, const          int);
HAMON_IS_SWAPPABLE_WITH_TEST(false,       volatile int,       volatile int);
HAMON_IS_SWAPPABLE_WITH_TEST(false,       volatile int, const volatile int);
HAMON_IS_SWAPPABLE_WITH_TEST(false, const volatile int,                int);
HAMON_IS_SWAPPABLE_WITH_TEST(false, const volatile int, const          int);
HAMON_IS_SWAPPABLE_WITH_TEST(false, const volatile int,       volatile int);
HAMON_IS_SWAPPABLE_WITH_TEST(false, const volatile int, const volatile int);

HAMON_IS_SWAPPABLE_WITH_TEST(true,                 int&,                int&);
HAMON_IS_SWAPPABLE_WITH_TEST(false,                int&, const          int&);
HAMON_IS_SWAPPABLE_WITH_TEST(false,                int&,       volatile int&);
HAMON_IS_SWAPPABLE_WITH_TEST(false,                int&, const volatile int&);
HAMON_IS_SWAPPABLE_WITH_TEST(false, const          int&,                int&);
#if HAMON_CXX_STANDARD >= 17
HAMON_IS_SWAPPABLE_WITH_TEST(false, const          int&, const          int&);
#endif
HAMON_IS_SWAPPABLE_WITH_TEST(false, const          int&,       volatile int&);
HAMON_IS_SWAPPABLE_WITH_TEST(false, const          int&, const volatile int&);
HAMON_IS_SWAPPABLE_WITH_TEST(false,       volatile int&,                int&);
HAMON_IS_SWAPPABLE_WITH_TEST(false,       volatile int&, const          int&);
HAMON_IS_SWAPPABLE_WITH_TEST(true,        volatile int&,       volatile int&);
HAMON_IS_SWAPPABLE_WITH_TEST(false,       volatile int&, const volatile int&);
HAMON_IS_SWAPPABLE_WITH_TEST(false, const volatile int&,                int&);
HAMON_IS_SWAPPABLE_WITH_TEST(false, const volatile int&, const          int&);
HAMON_IS_SWAPPABLE_WITH_TEST(false, const volatile int&,       volatile int&);
#if HAMON_CXX_STANDARD >= 17
HAMON_IS_SWAPPABLE_WITH_TEST(false, const volatile int&, const volatile int&);
#endif

HAMON_IS_SWAPPABLE_WITH_TEST(false, int, int*);
HAMON_IS_SWAPPABLE_WITH_TEST(false, int, int&);
HAMON_IS_SWAPPABLE_WITH_TEST(false, int, int&&);
HAMON_IS_SWAPPABLE_WITH_TEST(false, int, int[2]);
HAMON_IS_SWAPPABLE_WITH_TEST(false, int, int[]);
HAMON_IS_SWAPPABLE_WITH_TEST(false, int, int(&)[2]);
HAMON_IS_SWAPPABLE_WITH_TEST(false, int, int(&)[]);
HAMON_IS_SWAPPABLE_WITH_TEST(false, int, int(&&)[2]);
HAMON_IS_SWAPPABLE_WITH_TEST(false, int, int(&&)[]);
HAMON_IS_SWAPPABLE_WITH_TEST(false, int, int(*)[2]);
HAMON_IS_SWAPPABLE_WITH_TEST(false, int, int(*)[]);
HAMON_IS_SWAPPABLE_WITH_TEST(false, int, short);
HAMON_IS_SWAPPABLE_WITH_TEST(false, int, long);
HAMON_IS_SWAPPABLE_WITH_TEST(false, int, unsigned int);
HAMON_IS_SWAPPABLE_WITH_TEST(false, int, float);
HAMON_IS_SWAPPABLE_WITH_TEST(false, int, void);
HAMON_IS_SWAPPABLE_WITH_TEST(false, int, void*);
HAMON_IS_SWAPPABLE_WITH_TEST(false, int, enum_UDT);

HAMON_IS_SWAPPABLE_WITH_TEST(false, int*, int*);
HAMON_IS_SWAPPABLE_WITH_TEST(false, int*, int&);
HAMON_IS_SWAPPABLE_WITH_TEST(false, int*, int&&);
HAMON_IS_SWAPPABLE_WITH_TEST(false, int*, int[2]);
HAMON_IS_SWAPPABLE_WITH_TEST(false, int*, int[]);
HAMON_IS_SWAPPABLE_WITH_TEST(false, int*, int(&)[2]);
HAMON_IS_SWAPPABLE_WITH_TEST(false, int*, int(&)[]);
HAMON_IS_SWAPPABLE_WITH_TEST(false, int*, int(&&)[2]);
HAMON_IS_SWAPPABLE_WITH_TEST(false, int*, int(&&)[]);
HAMON_IS_SWAPPABLE_WITH_TEST(false, int*, int(*)[2]);
HAMON_IS_SWAPPABLE_WITH_TEST(false, int*, int(*)[]);
HAMON_IS_SWAPPABLE_WITH_TEST(false, int*, short*);
HAMON_IS_SWAPPABLE_WITH_TEST(false, int*, long*);
HAMON_IS_SWAPPABLE_WITH_TEST(false, int*, unsigned int*);
HAMON_IS_SWAPPABLE_WITH_TEST(false, int*, float*);
HAMON_IS_SWAPPABLE_WITH_TEST(false, int*, void);
HAMON_IS_SWAPPABLE_WITH_TEST(false, int*, void*);
HAMON_IS_SWAPPABLE_WITH_TEST(false, int*, enum_UDT);

HAMON_IS_SWAPPABLE_WITH_TEST(false, int&, int*);
HAMON_IS_SWAPPABLE_WITH_TEST(true,  int&, int&);
HAMON_IS_SWAPPABLE_WITH_TEST(false, int&, int&&);
HAMON_IS_SWAPPABLE_WITH_TEST(false, int&, int[2]);
HAMON_IS_SWAPPABLE_WITH_TEST(false, int&, int[]);
HAMON_IS_SWAPPABLE_WITH_TEST(false, int&, int(&)[2]);
HAMON_IS_SWAPPABLE_WITH_TEST(false, int&, int(&)[]);
HAMON_IS_SWAPPABLE_WITH_TEST(false, int&, int(&&)[2]);
HAMON_IS_SWAPPABLE_WITH_TEST(false, int&, int(&&)[]);
HAMON_IS_SWAPPABLE_WITH_TEST(false, int&, int(*)[2]);
HAMON_IS_SWAPPABLE_WITH_TEST(false, int&, int(*)[]);
HAMON_IS_SWAPPABLE_WITH_TEST(false, int&, short&);
HAMON_IS_SWAPPABLE_WITH_TEST(false, int&, long&);
HAMON_IS_SWAPPABLE_WITH_TEST(false, int&, unsigned int&);
HAMON_IS_SWAPPABLE_WITH_TEST(false, int&, float&);
HAMON_IS_SWAPPABLE_WITH_TEST(false, int&, void);
HAMON_IS_SWAPPABLE_WITH_TEST(false, int&, void*);
HAMON_IS_SWAPPABLE_WITH_TEST(false, int&, enum_UDT);

HAMON_IS_SWAPPABLE_WITH_TEST(false, int&&, int*);
HAMON_IS_SWAPPABLE_WITH_TEST(false, int&&, int&);
HAMON_IS_SWAPPABLE_WITH_TEST(false, int&&, int&&);
HAMON_IS_SWAPPABLE_WITH_TEST(false, int&&, int[2]);
HAMON_IS_SWAPPABLE_WITH_TEST(false, int&&, int[]);
HAMON_IS_SWAPPABLE_WITH_TEST(false, int&&, int(&)[2]);
HAMON_IS_SWAPPABLE_WITH_TEST(false, int&&, int(&)[]);
HAMON_IS_SWAPPABLE_WITH_TEST(false, int&&, int(&&)[2]);
HAMON_IS_SWAPPABLE_WITH_TEST(false, int&&, int(&&)[]);
HAMON_IS_SWAPPABLE_WITH_TEST(false, int&&, int(*)[2]);
HAMON_IS_SWAPPABLE_WITH_TEST(false, int&&, int(*)[]);
HAMON_IS_SWAPPABLE_WITH_TEST(false, int&&, short&&);
HAMON_IS_SWAPPABLE_WITH_TEST(false, int&&, long&&);
HAMON_IS_SWAPPABLE_WITH_TEST(false, int&&, unsigned int&&);
HAMON_IS_SWAPPABLE_WITH_TEST(false, int&&, float&&);
HAMON_IS_SWAPPABLE_WITH_TEST(false, int&&, void);
HAMON_IS_SWAPPABLE_WITH_TEST(false, int&&, void*);
HAMON_IS_SWAPPABLE_WITH_TEST(false, int&&, enum_UDT);

#undef HAMON_IS_SWAPPABLE_WITH_TEST
