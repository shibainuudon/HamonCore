/**
 *	@file	unit_test_type_traits_is_trivially_copyable.cpp
 *
 *	@brief	is_trivially_copyable のテスト
 */

#include <hamon/type_traits/is_trivially_copyable.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "type_traits_test_utility.hpp"

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

#define HAMON_IS_TRIVIALLY_COPYABLE_TEST(b, T)	\
	static_assert(hamon::is_trivially_copyable_v<T>      == b, #T " == " #b);	\
	static_assert(hamon::is_trivially_copyable<T>::value == b, #T " == " #b);	\
	static_assert(hamon::is_trivially_copyable<T>{}()    == b, #T " == " #b);	\
	static_assert(hamon::is_trivially_copyable<T>{}      == b, #T " == " #b)

#else

#define HAMON_IS_TRIVIALLY_COPYABLE_TEST(b, T)	\
	static_assert(hamon::is_trivially_copyable<T>::value == b, #T " == " #b);	\
	static_assert(hamon::is_trivially_copyable<T>{}()    == b, #T " == " #b);	\
	static_assert(hamon::is_trivially_copyable<T>{}      == b, #T " == " #b)

#endif

HAMON_IS_TRIVIALLY_COPYABLE_TEST(true,                 int);
HAMON_IS_TRIVIALLY_COPYABLE_TEST(true,  const          int);
//HAMON_IS_TRIVIALLY_COPYABLE_TEST(false,       volatile int);
//HAMON_IS_TRIVIALLY_COPYABLE_TEST(false, const volatile int);
HAMON_IS_TRIVIALLY_COPYABLE_TEST(true,                 int*);
HAMON_IS_TRIVIALLY_COPYABLE_TEST(true,  const          int*);
HAMON_IS_TRIVIALLY_COPYABLE_TEST(true,        volatile int*);
HAMON_IS_TRIVIALLY_COPYABLE_TEST(true,  const volatile int*);
HAMON_IS_TRIVIALLY_COPYABLE_TEST(true,  int* const         );
//HAMON_IS_TRIVIALLY_COPYABLE_TEST(false, int*       volatile);
//HAMON_IS_TRIVIALLY_COPYABLE_TEST(false, int* const volatile);
HAMON_IS_TRIVIALLY_COPYABLE_TEST(false, int&);
HAMON_IS_TRIVIALLY_COPYABLE_TEST(false, int&&);
HAMON_IS_TRIVIALLY_COPYABLE_TEST(true,                 int[2]);
HAMON_IS_TRIVIALLY_COPYABLE_TEST(true,  const          int[2]);
//HAMON_IS_TRIVIALLY_COPYABLE_TEST(false,       volatile int[2]);
//HAMON_IS_TRIVIALLY_COPYABLE_TEST(false, const volatile int[2]);
HAMON_IS_TRIVIALLY_COPYABLE_TEST(true,                 int[]);
HAMON_IS_TRIVIALLY_COPYABLE_TEST(true,  const          int[]);
//HAMON_IS_TRIVIALLY_COPYABLE_TEST(false,       volatile int[]);
//HAMON_IS_TRIVIALLY_COPYABLE_TEST(false, const volatile int[]);
HAMON_IS_TRIVIALLY_COPYABLE_TEST(false, int(&)[2]);
HAMON_IS_TRIVIALLY_COPYABLE_TEST(false, int(&)[]);
HAMON_IS_TRIVIALLY_COPYABLE_TEST(false, int(&&)[2]);
HAMON_IS_TRIVIALLY_COPYABLE_TEST(false, int(&&)[]);

HAMON_IS_TRIVIALLY_COPYABLE_TEST(false,                void);
HAMON_IS_TRIVIALLY_COPYABLE_TEST(false, const          void);
HAMON_IS_TRIVIALLY_COPYABLE_TEST(false,       volatile void);
HAMON_IS_TRIVIALLY_COPYABLE_TEST(false, const volatile void);

HAMON_IS_TRIVIALLY_COPYABLE_TEST(false,                UDT);
HAMON_IS_TRIVIALLY_COPYABLE_TEST(false, const          UDT);
HAMON_IS_TRIVIALLY_COPYABLE_TEST(false,       volatile UDT);
HAMON_IS_TRIVIALLY_COPYABLE_TEST(false, const volatile UDT);
HAMON_IS_TRIVIALLY_COPYABLE_TEST(true,                 UDT*);
HAMON_IS_TRIVIALLY_COPYABLE_TEST(true,  const          UDT*);
HAMON_IS_TRIVIALLY_COPYABLE_TEST(true,        volatile UDT*);
HAMON_IS_TRIVIALLY_COPYABLE_TEST(true,  const volatile UDT*);
HAMON_IS_TRIVIALLY_COPYABLE_TEST(false,                UDT&);
HAMON_IS_TRIVIALLY_COPYABLE_TEST(false,                UDT&&);
HAMON_IS_TRIVIALLY_COPYABLE_TEST(false,                UDT[2]);
HAMON_IS_TRIVIALLY_COPYABLE_TEST(false,                UDT[]);
HAMON_IS_TRIVIALLY_COPYABLE_TEST(true,                 POD_UDT);
HAMON_IS_TRIVIALLY_COPYABLE_TEST(true,  const          POD_UDT);
//HAMON_IS_TRIVIALLY_COPYABLE_TEST(false,       volatile POD_UDT);
//HAMON_IS_TRIVIALLY_COPYABLE_TEST(false, const volatile POD_UDT);
HAMON_IS_TRIVIALLY_COPYABLE_TEST(true,                 POD_UDT*);
HAMON_IS_TRIVIALLY_COPYABLE_TEST(false,                POD_UDT&);
HAMON_IS_TRIVIALLY_COPYABLE_TEST(false,                POD_UDT&&);
HAMON_IS_TRIVIALLY_COPYABLE_TEST(true,                 POD_UDT[2]);
HAMON_IS_TRIVIALLY_COPYABLE_TEST(true,                 POD_UDT[]);

HAMON_IS_TRIVIALLY_COPYABLE_TEST(true, f1);
HAMON_IS_TRIVIALLY_COPYABLE_TEST(true, f2);
HAMON_IS_TRIVIALLY_COPYABLE_TEST(true, f3);
HAMON_IS_TRIVIALLY_COPYABLE_TEST(true, mf1);
HAMON_IS_TRIVIALLY_COPYABLE_TEST(true, mf2);
HAMON_IS_TRIVIALLY_COPYABLE_TEST(true, mf3);
HAMON_IS_TRIVIALLY_COPYABLE_TEST(true, mf4);
HAMON_IS_TRIVIALLY_COPYABLE_TEST(true, mp);
HAMON_IS_TRIVIALLY_COPYABLE_TEST(true, cmf);
HAMON_IS_TRIVIALLY_COPYABLE_TEST(false, foo0_t);
HAMON_IS_TRIVIALLY_COPYABLE_TEST(false, foo1_t);
HAMON_IS_TRIVIALLY_COPYABLE_TEST(false, foo2_t);
HAMON_IS_TRIVIALLY_COPYABLE_TEST(false, foo3_t);
HAMON_IS_TRIVIALLY_COPYABLE_TEST(false, foo4_t);

HAMON_IS_TRIVIALLY_COPYABLE_TEST(true,	trivial_except_construct);
HAMON_IS_TRIVIALLY_COPYABLE_TEST(false, trivial_except_destroy);
HAMON_IS_TRIVIALLY_COPYABLE_TEST(false, trivial_except_copy_ctor);
HAMON_IS_TRIVIALLY_COPYABLE_TEST(false, trivial_except_copy_assign);
HAMON_IS_TRIVIALLY_COPYABLE_TEST(false,	trivial_except_move_ctor);
HAMON_IS_TRIVIALLY_COPYABLE_TEST(false,	trivial_except_move_assign);

#undef HAMON_IS_TRIVIALLY_COPYABLE_TEST
