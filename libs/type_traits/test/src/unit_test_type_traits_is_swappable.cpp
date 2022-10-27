/**
 *	@file	unit_test_type_traits_is_swappable.cpp
 *
 *	@brief	is_swappable のテスト
 */

#include <hamon/type_traits/is_swappable.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "type_traits_test_utility.hpp"

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

#define HAMON_IS_SWAPPABLE_TEST(b, T)	\
	static_assert(hamon::is_swappable_v<T>      == b, #T);	\
	static_assert(hamon::is_swappable<T>::value == b, #T);	\
	static_assert(hamon::is_swappable<T>()      == b, #T)

#else

#define HAMON_IS_SWAPPABLE_TEST(b, T)	\
	static_assert(hamon::is_swappable<T>::value == b, #T);	\
	static_assert(hamon::is_swappable<T>()      == b, #T)

#endif

#if defined(HAMON_STDLIB_DINKUMWARE) && (HAMON_CXX_STANDARD == 14)
#define SWAPPABLE	true
#else
#define SWAPPABLE	false
#endif

HAMON_IS_SWAPPABLE_TEST(true,                     int);
HAMON_IS_SWAPPABLE_TEST(SWAPPABLE, const          int);
HAMON_IS_SWAPPABLE_TEST(true,            volatile int);
HAMON_IS_SWAPPABLE_TEST(SWAPPABLE, const volatile int);
HAMON_IS_SWAPPABLE_TEST(true,                     bool);
HAMON_IS_SWAPPABLE_TEST(SWAPPABLE, const          bool);
HAMON_IS_SWAPPABLE_TEST(true,            volatile bool);
HAMON_IS_SWAPPABLE_TEST(SWAPPABLE, const volatile bool);
HAMON_IS_SWAPPABLE_TEST(SWAPPABLE,                int[]);
HAMON_IS_SWAPPABLE_TEST(SWAPPABLE, const          int[]);
HAMON_IS_SWAPPABLE_TEST(SWAPPABLE,       volatile int[]);
HAMON_IS_SWAPPABLE_TEST(SWAPPABLE, const volatile int[]);
HAMON_IS_SWAPPABLE_TEST(true,                     int[2]);
HAMON_IS_SWAPPABLE_TEST(SWAPPABLE, const          int[2]);
HAMON_IS_SWAPPABLE_TEST(true,            volatile int[2]);
HAMON_IS_SWAPPABLE_TEST(SWAPPABLE, const volatile int[2]);
HAMON_IS_SWAPPABLE_TEST(SWAPPABLE,                int[][3]);
HAMON_IS_SWAPPABLE_TEST(SWAPPABLE, const          int[][3]);
HAMON_IS_SWAPPABLE_TEST(SWAPPABLE,       volatile int[][3]);
HAMON_IS_SWAPPABLE_TEST(SWAPPABLE, const volatile int[][3]);
HAMON_IS_SWAPPABLE_TEST(true,                     int[1][2][3]);
HAMON_IS_SWAPPABLE_TEST(SWAPPABLE, const          int[1][2][3]);
HAMON_IS_SWAPPABLE_TEST(true,            volatile int[1][2][3]);
HAMON_IS_SWAPPABLE_TEST(SWAPPABLE, const volatile int[1][2][3]);
HAMON_IS_SWAPPABLE_TEST(SWAPPABLE,                int[][2][3]);
HAMON_IS_SWAPPABLE_TEST(SWAPPABLE, const          int[][2][3]);
HAMON_IS_SWAPPABLE_TEST(SWAPPABLE,       volatile int[][2][3]);
HAMON_IS_SWAPPABLE_TEST(SWAPPABLE, const volatile int[][2][3]);
HAMON_IS_SWAPPABLE_TEST(true,                     int&);
HAMON_IS_SWAPPABLE_TEST(SWAPPABLE, const          int&);
HAMON_IS_SWAPPABLE_TEST(true,            volatile int&);
HAMON_IS_SWAPPABLE_TEST(SWAPPABLE, const volatile int&);
HAMON_IS_SWAPPABLE_TEST(true,                     int&&);
HAMON_IS_SWAPPABLE_TEST(SWAPPABLE, const          int&&);
HAMON_IS_SWAPPABLE_TEST(true,            volatile int&&);
HAMON_IS_SWAPPABLE_TEST(SWAPPABLE, const volatile int&&);
HAMON_IS_SWAPPABLE_TEST(true,                     int*);
HAMON_IS_SWAPPABLE_TEST(true,      const          int*);
HAMON_IS_SWAPPABLE_TEST(true,            volatile int*);
HAMON_IS_SWAPPABLE_TEST(true,      const volatile int*);
HAMON_IS_SWAPPABLE_TEST(true,                     int(&)[2]);
HAMON_IS_SWAPPABLE_TEST(SWAPPABLE, const          int(&)[2]);
HAMON_IS_SWAPPABLE_TEST(true,            volatile int(&)[2]);
HAMON_IS_SWAPPABLE_TEST(SWAPPABLE, const volatile int(&)[2]);
HAMON_IS_SWAPPABLE_TEST(SWAPPABLE,                int(&)[]);
HAMON_IS_SWAPPABLE_TEST(SWAPPABLE, const          int(&)[]);
HAMON_IS_SWAPPABLE_TEST(SWAPPABLE,       volatile int(&)[]);
HAMON_IS_SWAPPABLE_TEST(SWAPPABLE, const volatile int(&)[]);
HAMON_IS_SWAPPABLE_TEST(true,                     int(&&)[2]);
HAMON_IS_SWAPPABLE_TEST(SWAPPABLE, const          int(&&)[2]);
HAMON_IS_SWAPPABLE_TEST(true,            volatile int(&&)[2]);
HAMON_IS_SWAPPABLE_TEST(SWAPPABLE, const volatile int(&&)[2]);
HAMON_IS_SWAPPABLE_TEST(SWAPPABLE,                int(&&)[]);
HAMON_IS_SWAPPABLE_TEST(SWAPPABLE, const          int(&&)[]);
HAMON_IS_SWAPPABLE_TEST(SWAPPABLE,       volatile int(&&)[]);
HAMON_IS_SWAPPABLE_TEST(SWAPPABLE, const volatile int(&&)[]);
HAMON_IS_SWAPPABLE_TEST(true,                     int(*)[2]);
HAMON_IS_SWAPPABLE_TEST(true,      const          int(*)[2]);
HAMON_IS_SWAPPABLE_TEST(true,            volatile int(*)[2]);
HAMON_IS_SWAPPABLE_TEST(true,      const volatile int(*)[2]);
HAMON_IS_SWAPPABLE_TEST(true,                     int(*)[]);
HAMON_IS_SWAPPABLE_TEST(true,      const          int(*)[]);
HAMON_IS_SWAPPABLE_TEST(true,            volatile int(*)[]);
HAMON_IS_SWAPPABLE_TEST(true,      const volatile int(*)[]);
HAMON_IS_SWAPPABLE_TEST(false,                    void);
HAMON_IS_SWAPPABLE_TEST(false,     const          void);
HAMON_IS_SWAPPABLE_TEST(false,           volatile void);
HAMON_IS_SWAPPABLE_TEST(false,     const volatile void);
HAMON_IS_SWAPPABLE_TEST(true,                     void*);
HAMON_IS_SWAPPABLE_TEST(true,      const          void*);
HAMON_IS_SWAPPABLE_TEST(true,            volatile void*);
HAMON_IS_SWAPPABLE_TEST(true,      const volatile void*);
HAMON_IS_SWAPPABLE_TEST(true,                     UDT);
HAMON_IS_SWAPPABLE_TEST(SWAPPABLE, const          UDT);
HAMON_IS_SWAPPABLE_TEST(SWAPPABLE,       volatile UDT);
HAMON_IS_SWAPPABLE_TEST(SWAPPABLE, const volatile UDT);
HAMON_IS_SWAPPABLE_TEST(true,                     POD_UDT);
HAMON_IS_SWAPPABLE_TEST(SWAPPABLE, const          POD_UDT);
HAMON_IS_SWAPPABLE_TEST(SWAPPABLE,       volatile POD_UDT);
HAMON_IS_SWAPPABLE_TEST(SWAPPABLE, const volatile POD_UDT);
HAMON_IS_SWAPPABLE_TEST(true,                     enum_UDT);
HAMON_IS_SWAPPABLE_TEST(SWAPPABLE, const          enum_UDT);
HAMON_IS_SWAPPABLE_TEST(true,            volatile enum_UDT);
HAMON_IS_SWAPPABLE_TEST(SWAPPABLE, const volatile enum_UDT);
HAMON_IS_SWAPPABLE_TEST(true,                     enum_class_UDT);
HAMON_IS_SWAPPABLE_TEST(SWAPPABLE, const          enum_class_UDT);
HAMON_IS_SWAPPABLE_TEST(true,            volatile enum_class_UDT);
HAMON_IS_SWAPPABLE_TEST(SWAPPABLE, const volatile enum_class_UDT);
HAMON_IS_SWAPPABLE_TEST(SWAPPABLE,                test_abc1);
HAMON_IS_SWAPPABLE_TEST(SWAPPABLE, const          test_abc1);
HAMON_IS_SWAPPABLE_TEST(SWAPPABLE,       volatile test_abc1);
HAMON_IS_SWAPPABLE_TEST(SWAPPABLE, const volatile test_abc1);
HAMON_IS_SWAPPABLE_TEST(SWAPPABLE,                test_abc2);
HAMON_IS_SWAPPABLE_TEST(SWAPPABLE, const          test_abc2);
HAMON_IS_SWAPPABLE_TEST(SWAPPABLE,       volatile test_abc2);
HAMON_IS_SWAPPABLE_TEST(SWAPPABLE, const volatile test_abc2);
HAMON_IS_SWAPPABLE_TEST(SWAPPABLE,                test_abc3);
HAMON_IS_SWAPPABLE_TEST(SWAPPABLE, const          test_abc3);
HAMON_IS_SWAPPABLE_TEST(SWAPPABLE,       volatile test_abc3);
HAMON_IS_SWAPPABLE_TEST(SWAPPABLE, const volatile test_abc3);

HAMON_IS_SWAPPABLE_TEST(true, f1);
HAMON_IS_SWAPPABLE_TEST(true, f2);
HAMON_IS_SWAPPABLE_TEST(true, f3);
HAMON_IS_SWAPPABLE_TEST(true, mf1);
HAMON_IS_SWAPPABLE_TEST(true, mf2);
HAMON_IS_SWAPPABLE_TEST(true, mf3);
HAMON_IS_SWAPPABLE_TEST(true, mf4);
HAMON_IS_SWAPPABLE_TEST(true, mp);
HAMON_IS_SWAPPABLE_TEST(true, cmf);
HAMON_IS_SWAPPABLE_TEST(SWAPPABLE, void());
HAMON_IS_SWAPPABLE_TEST(SWAPPABLE, foo0_t);
HAMON_IS_SWAPPABLE_TEST(SWAPPABLE, foo1_t);
HAMON_IS_SWAPPABLE_TEST(SWAPPABLE, foo2_t);
HAMON_IS_SWAPPABLE_TEST(SWAPPABLE, foo3_t);
HAMON_IS_SWAPPABLE_TEST(SWAPPABLE, foo4_t);

#undef SWAPPABLE
#undef HAMON_IS_SWAPPABLE_TEST
