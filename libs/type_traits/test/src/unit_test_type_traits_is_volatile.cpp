/**
 *	@file	unit_test_type_traits_is_volatile.cpp
 *
 *	@brief	is_volatile のテスト
 */

#include <hamon/type_traits/is_volatile.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "type_traits_test_utility.hpp"

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

#define HAMON_IS_VOLATILE_TEST_IMPL(b, T)	\
	static_assert(hamon::is_volatile_v<T>      == b, #T);	\
	static_assert(hamon::is_volatile<T>::value == b, #T);	\
	static_assert(hamon::is_volatile<T>{}()    == b, #T);	\
	static_assert(hamon::is_volatile<T>{}      == b, #T)

#else

#define HAMON_IS_VOLATILE_TEST_IMPL(b, T)	\
	static_assert(hamon::is_volatile<T>::value == b, #T);	\
	static_assert(hamon::is_volatile<T>{}()    == b, #T);	\
	static_assert(hamon::is_volatile<T>{}      == b, #T)

#endif

#define HAMON_IS_VOLATILE_TEST(T)	\
	HAMON_IS_VOLATILE_TEST_IMPL(false,                T);	\
	HAMON_IS_VOLATILE_TEST_IMPL(false, const          T);	\
	HAMON_IS_VOLATILE_TEST_IMPL(true,        volatile T);	\
	HAMON_IS_VOLATILE_TEST_IMPL(true,  const volatile T);	\
	HAMON_IS_VOLATILE_TEST_IMPL(false,                T&);	\
	HAMON_IS_VOLATILE_TEST_IMPL(false, const          T&);	\
	HAMON_IS_VOLATILE_TEST_IMPL(false,       volatile T&);	\
	HAMON_IS_VOLATILE_TEST_IMPL(false, const volatile T&);	\
	HAMON_IS_VOLATILE_TEST_IMPL(false,                T&&);	\
	HAMON_IS_VOLATILE_TEST_IMPL(false, const          T&&);	\
	HAMON_IS_VOLATILE_TEST_IMPL(false,       volatile T&&);	\
	HAMON_IS_VOLATILE_TEST_IMPL(false, const volatile T&&);	\
	HAMON_IS_VOLATILE_TEST_IMPL(false,                T*);	\
	HAMON_IS_VOLATILE_TEST_IMPL(false, const          T*);	\
	HAMON_IS_VOLATILE_TEST_IMPL(false,       volatile T*);	\
	HAMON_IS_VOLATILE_TEST_IMPL(false, const volatile T*);	\
	HAMON_IS_VOLATILE_TEST_IMPL(false, T*               );	\
	HAMON_IS_VOLATILE_TEST_IMPL(false, T* const         );	\
	HAMON_IS_VOLATILE_TEST_IMPL(true,  T*       volatile);	\
	HAMON_IS_VOLATILE_TEST_IMPL(true,  T* const volatile);	\
	HAMON_IS_VOLATILE_TEST_IMPL(false,                T[2]);	\
	HAMON_IS_VOLATILE_TEST_IMPL(false, const          T[2]);	\
	HAMON_IS_VOLATILE_TEST_IMPL(true,        volatile T[2]);	\
	HAMON_IS_VOLATILE_TEST_IMPL(true,  const volatile T[2]);	\
	HAMON_IS_VOLATILE_TEST_IMPL(false,                T[]);	\
	HAMON_IS_VOLATILE_TEST_IMPL(false, const          T[]);	\
	HAMON_IS_VOLATILE_TEST_IMPL(true,        volatile T[]);	\
	HAMON_IS_VOLATILE_TEST_IMPL(true,  const volatile T[]);	\
	HAMON_IS_VOLATILE_TEST_IMPL(false,                T(*)[2]);	\
	HAMON_IS_VOLATILE_TEST_IMPL(false, const          T(*)[2]);	\
	HAMON_IS_VOLATILE_TEST_IMPL(false,       volatile T(*)[2]);	\
	HAMON_IS_VOLATILE_TEST_IMPL(false, const volatile T(*)[2]);	\
	HAMON_IS_VOLATILE_TEST_IMPL(false,                T(&)[2]);	\
	HAMON_IS_VOLATILE_TEST_IMPL(false, const          T(&)[2]);	\
	HAMON_IS_VOLATILE_TEST_IMPL(false,       volatile T(&)[2]);	\
	HAMON_IS_VOLATILE_TEST_IMPL(false, const volatile T(&)[2]);	\
	HAMON_IS_VOLATILE_TEST_IMPL(false,                T(&&)[2]);	\
	HAMON_IS_VOLATILE_TEST_IMPL(false, const          T(&&)[2]);	\
	HAMON_IS_VOLATILE_TEST_IMPL(false,       volatile T(&&)[2]);	\
	HAMON_IS_VOLATILE_TEST_IMPL(false, const volatile T(&&)[2])

HAMON_IS_VOLATILE_TEST(int);
HAMON_IS_VOLATILE_TEST(UDT);
HAMON_IS_VOLATILE_TEST(enum_UDT);
HAMON_IS_VOLATILE_TEST(f1);
HAMON_IS_VOLATILE_TEST(mf1);
HAMON_IS_VOLATILE_TEST(mp);
HAMON_IS_VOLATILE_TEST(cmf);
HAMON_IS_VOLATILE_TEST_IMPL(false, foo0_t);
HAMON_IS_VOLATILE_TEST_IMPL(false, foo1_t);
HAMON_IS_VOLATILE_TEST_IMPL(false, foo2_t);
HAMON_IS_VOLATILE_TEST_IMPL(false, foo3_t);
HAMON_IS_VOLATILE_TEST_IMPL(false, foo4_t);

#undef HAMON_IS_VOLATILE_TEST_IMPL
#undef HAMON_IS_VOLATILE_TEST
