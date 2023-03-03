/**
 *	@file	unit_test_type_traits_is_const.cpp
 *
 *	@brief	is_const のテスト
 */

#include <hamon/type_traits/is_const.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "type_traits_test_utility.hpp"

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

#define HAMON_IS_CONST_TEST_IMPL(b, T)	\
	static_assert(hamon::is_const_v<T>      == b, #T);	\
	static_assert(hamon::is_const<T>::value == b, #T);	\
	static_assert(hamon::is_const<T>{}()    == b, #T);	\
	static_assert(hamon::is_const<T>{}      == b, #T)

#else

#define HAMON_IS_CONST_TEST_IMPL(b, T)	\
	static_assert(hamon::is_const<T>::value == b, #T);	\
	static_assert(hamon::is_const<T>{}()    == b, #T);	\
	static_assert(hamon::is_const<T>{}      == b, #T)

#endif

#define HAMON_IS_CONST_TEST_CV(T)	\
	HAMON_IS_CONST_TEST_IMPL(false,                T);	\
	HAMON_IS_CONST_TEST_IMPL(true,  const          T);	\
	HAMON_IS_CONST_TEST_IMPL(false,       volatile T);	\
	HAMON_IS_CONST_TEST_IMPL(true,  const volatile T)

#define HAMON_IS_CONST_TEST(T)	\
	HAMON_IS_CONST_TEST_IMPL(false,                T);	\
	HAMON_IS_CONST_TEST_IMPL(true,  const          T);	\
	HAMON_IS_CONST_TEST_IMPL(false,       volatile T);	\
	HAMON_IS_CONST_TEST_IMPL(true,  const volatile T);	\
	HAMON_IS_CONST_TEST_IMPL(false,                T&);	\
	HAMON_IS_CONST_TEST_IMPL(false, const          T&);	\
	HAMON_IS_CONST_TEST_IMPL(false,       volatile T&);	\
	HAMON_IS_CONST_TEST_IMPL(false, const volatile T&);	\
	HAMON_IS_CONST_TEST_IMPL(false,                T&&);	\
	HAMON_IS_CONST_TEST_IMPL(false, const          T&&);	\
	HAMON_IS_CONST_TEST_IMPL(false,       volatile T&&);	\
	HAMON_IS_CONST_TEST_IMPL(false, const volatile T&&);	\
	HAMON_IS_CONST_TEST_IMPL(false,                T*);	\
	HAMON_IS_CONST_TEST_IMPL(false, const          T*);	\
	HAMON_IS_CONST_TEST_IMPL(false,       volatile T*);	\
	HAMON_IS_CONST_TEST_IMPL(false, const volatile T*);	\
	HAMON_IS_CONST_TEST_IMPL(false, T*               );	\
	HAMON_IS_CONST_TEST_IMPL(true,  T* const         );	\
	HAMON_IS_CONST_TEST_IMPL(false, T*       volatile);	\
	HAMON_IS_CONST_TEST_IMPL(true,  T* const volatile);	\
	HAMON_IS_CONST_TEST_IMPL(false,                T[2]);	\
	HAMON_IS_CONST_TEST_IMPL(true,  const          T[2]);	\
	HAMON_IS_CONST_TEST_IMPL(false,       volatile T[2]);	\
	HAMON_IS_CONST_TEST_IMPL(true,  const volatile T[2]);	\
	HAMON_IS_CONST_TEST_IMPL(false,                T[]);	\
	HAMON_IS_CONST_TEST_IMPL(true,  const          T[]);	\
	HAMON_IS_CONST_TEST_IMPL(false,       volatile T[]);	\
	HAMON_IS_CONST_TEST_IMPL(true,  const volatile T[]);	\
	HAMON_IS_CONST_TEST_IMPL(false,                T(*)[2]);	\
	HAMON_IS_CONST_TEST_IMPL(false, const          T(*)[2]);	\
	HAMON_IS_CONST_TEST_IMPL(false,       volatile T(*)[2]);	\
	HAMON_IS_CONST_TEST_IMPL(false, const volatile T(*)[2]);	\
	HAMON_IS_CONST_TEST_IMPL(false,                T(&)[2]);	\
	HAMON_IS_CONST_TEST_IMPL(false, const          T(&)[2]);	\
	HAMON_IS_CONST_TEST_IMPL(false,       volatile T(&)[2]);	\
	HAMON_IS_CONST_TEST_IMPL(false, const volatile T(&)[2]);	\
	HAMON_IS_CONST_TEST_IMPL(false,                T(&&)[2]);	\
	HAMON_IS_CONST_TEST_IMPL(false, const          T(&&)[2]);	\
	HAMON_IS_CONST_TEST_IMPL(false,       volatile T(&&)[2]);	\
	HAMON_IS_CONST_TEST_IMPL(false, const volatile T(&&)[2])

HAMON_IS_CONST_TEST(int);
HAMON_IS_CONST_TEST(float);
HAMON_IS_CONST_TEST(enum_UDT);
HAMON_IS_CONST_TEST(enum_class_UDT);
HAMON_IS_CONST_TEST(UDT);
HAMON_IS_CONST_TEST(union_UDT);
HAMON_IS_CONST_TEST_CV(void);
HAMON_IS_CONST_TEST_CV(f1);
HAMON_IS_CONST_TEST_CV(f2);
HAMON_IS_CONST_TEST_CV(f3);
HAMON_IS_CONST_TEST_CV(mf1);
HAMON_IS_CONST_TEST_CV(mf2);
HAMON_IS_CONST_TEST_CV(mf3);
HAMON_IS_CONST_TEST_CV(mf4);
HAMON_IS_CONST_TEST_CV(mp);
HAMON_IS_CONST_TEST_CV(cmf);
HAMON_IS_CONST_TEST_IMPL(false, foo0_t);
HAMON_IS_CONST_TEST_IMPL(false, foo1_t);
HAMON_IS_CONST_TEST_IMPL(false, foo2_t);
HAMON_IS_CONST_TEST_IMPL(false, foo3_t);
HAMON_IS_CONST_TEST_IMPL(false, foo4_t);

#undef HAMON_IS_CONST_TEST_IMPL
#undef HAMON_IS_CONST_TEST_CV
#undef HAMON_IS_CONST_TEST
