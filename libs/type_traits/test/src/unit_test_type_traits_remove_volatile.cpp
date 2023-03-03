/**
 *	@file	unit_test_type_traits_remove_volatile.cpp
 *
 *	@brief	remove_volatile のテスト
 */

#include <hamon/type_traits/remove_volatile.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include "type_traits_test_utility.hpp"

HAMON_TRANSFORM_TEST(hamon::remove_volatile, /**/          , /**/);
HAMON_TRANSFORM_TEST(hamon::remove_volatile, const         , const);
HAMON_TRANSFORM_TEST(hamon::remove_volatile,       volatile, /**/);
HAMON_TRANSFORM_TEST(hamon::remove_volatile, const volatile, const);
HAMON_TRANSFORM_TEST(hamon::remove_volatile,                &,                &);
HAMON_TRANSFORM_TEST(hamon::remove_volatile, const          &, const          &);
HAMON_TRANSFORM_TEST(hamon::remove_volatile,       volatile &,       volatile &);
HAMON_TRANSFORM_TEST(hamon::remove_volatile, const volatile &, const volatile &);
HAMON_TRANSFORM_TEST(hamon::remove_volatile,                &&,                &&);
HAMON_TRANSFORM_TEST(hamon::remove_volatile, const          &&, const          &&);
HAMON_TRANSFORM_TEST(hamon::remove_volatile,       volatile &&,       volatile &&);
HAMON_TRANSFORM_TEST(hamon::remove_volatile, const volatile &&, const volatile &&);
HAMON_TRANSFORM_TEST(hamon::remove_volatile, *               , *               );
HAMON_TRANSFORM_TEST(hamon::remove_volatile, * const         , * const         );
HAMON_TRANSFORM_TEST(hamon::remove_volatile, *       volatile, *               );
HAMON_TRANSFORM_TEST(hamon::remove_volatile, * const volatile, * const         );
HAMON_TRANSFORM_TEST(hamon::remove_volatile, const          *, const          *);
HAMON_TRANSFORM_TEST(hamon::remove_volatile,       volatile *,       volatile *);
HAMON_TRANSFORM_TEST(hamon::remove_volatile, const volatile *, const volatile *);
HAMON_TRANSFORM_TEST(hamon::remove_volatile,                [2],                [2]);
HAMON_TRANSFORM_TEST(hamon::remove_volatile, const          [2], const          [2]);
HAMON_TRANSFORM_TEST(hamon::remove_volatile,       volatile [2],                [2]);
HAMON_TRANSFORM_TEST(hamon::remove_volatile, const volatile [2], const          [2]);
HAMON_TRANSFORM_TEST(hamon::remove_volatile,                [],                []);
HAMON_TRANSFORM_TEST(hamon::remove_volatile, const          [], const          []);
HAMON_TRANSFORM_TEST(hamon::remove_volatile,       volatile [],                []);
HAMON_TRANSFORM_TEST(hamon::remove_volatile, const volatile [], const          []);
HAMON_TRANSFORM_TEST(hamon::remove_volatile,                (&)[2],                (&)[2]);
HAMON_TRANSFORM_TEST(hamon::remove_volatile, const          (&)[2], const          (&)[2]);
HAMON_TRANSFORM_TEST(hamon::remove_volatile,       volatile (&)[2],       volatile (&)[2]);
HAMON_TRANSFORM_TEST(hamon::remove_volatile, const volatile (&)[2], const volatile (&)[2]);
HAMON_TRANSFORM_TEST(hamon::remove_volatile,                (&)[],                (&)[]);
HAMON_TRANSFORM_TEST(hamon::remove_volatile, const          (&)[], const          (&)[]);
HAMON_TRANSFORM_TEST(hamon::remove_volatile,       volatile (&)[],       volatile (&)[]);
HAMON_TRANSFORM_TEST(hamon::remove_volatile, const volatile (&)[], const volatile (&)[]);
HAMON_TRANSFORM_TEST(hamon::remove_volatile,                (&&)[2],                (&&)[2]);
HAMON_TRANSFORM_TEST(hamon::remove_volatile, const          (&&)[2], const          (&&)[2]);
HAMON_TRANSFORM_TEST(hamon::remove_volatile,       volatile (&&)[2],       volatile (&&)[2]);
HAMON_TRANSFORM_TEST(hamon::remove_volatile, const volatile (&&)[2], const volatile (&&)[2]);
HAMON_TRANSFORM_TEST(hamon::remove_volatile,                (&&)[],                (&&)[]);
HAMON_TRANSFORM_TEST(hamon::remove_volatile, const          (&&)[], const          (&&)[]);
HAMON_TRANSFORM_TEST(hamon::remove_volatile,       volatile (&&)[],       volatile (&&)[]);
HAMON_TRANSFORM_TEST(hamon::remove_volatile, const volatile (&&)[], const volatile (&&)[]);
HAMON_TRANSFORM_TEST(hamon::remove_volatile,                (*)[2],                (*)[2]);
HAMON_TRANSFORM_TEST(hamon::remove_volatile, const          (*)[2], const          (*)[2]);
HAMON_TRANSFORM_TEST(hamon::remove_volatile,       volatile (*)[2],       volatile (*)[2]);
HAMON_TRANSFORM_TEST(hamon::remove_volatile, const volatile (*)[2], const volatile (*)[2]);
HAMON_TRANSFORM_TEST(hamon::remove_volatile,                (*)[],                (*)[]);
HAMON_TRANSFORM_TEST(hamon::remove_volatile, const          (*)[], const          (*)[]);
HAMON_TRANSFORM_TEST(hamon::remove_volatile,       volatile (*)[],       volatile (*)[]);
HAMON_TRANSFORM_TEST(hamon::remove_volatile, const volatile (*)[], const volatile (*)[]);

#define HAMON_REMOVE_VOLATILE_TEST(T1, T2)	\
	static_assert(hamon::is_same<hamon::remove_volatile_t<T1>, T2>::value, "");	\
	static_assert(hamon::is_same<hamon::remove_volatile<T1>::type, T2>::value, "")

HAMON_REMOVE_VOLATILE_TEST(               void,       void);
HAMON_REMOVE_VOLATILE_TEST(const          void, const void);
HAMON_REMOVE_VOLATILE_TEST(      volatile void,       void);
HAMON_REMOVE_VOLATILE_TEST(const volatile void, const void);
HAMON_REMOVE_VOLATILE_TEST(void(void), void(void));
HAMON_REMOVE_VOLATILE_TEST(int(void), int(void));
HAMON_REMOVE_VOLATILE_TEST(void(int), void(int));
HAMON_REMOVE_VOLATILE_TEST(int(int), int(int));
HAMON_REMOVE_VOLATILE_TEST(int(char, short), int(char, short));
HAMON_REMOVE_VOLATILE_TEST(int(float, double, long double), int(float, double, long double));
HAMON_REMOVE_VOLATILE_TEST(int(*)(int), int(*)(int));
HAMON_REMOVE_VOLATILE_TEST(int(&)(int), int(&)(int));
HAMON_REMOVE_VOLATILE_TEST(int(&&)(int), int(&&)(int));
HAMON_REMOVE_VOLATILE_TEST(void (UDT::*)(void), void (UDT::*)(void));
HAMON_REMOVE_VOLATILE_TEST(int (UDT::*)(int), int (UDT::*)(int));
HAMON_REMOVE_VOLATILE_TEST(int (UDT::*)(int, float), int (UDT::*)(int, float));
HAMON_REMOVE_VOLATILE_TEST(int (UDT::*)(int) const, int (UDT::*)(int) const);
HAMON_REMOVE_VOLATILE_TEST(int (UDT::*)(int) volatile, int (UDT::*)(int) volatile);
HAMON_REMOVE_VOLATILE_TEST(int (UDT::*)(int) const volatile, int (UDT::*)(int) const volatile);
HAMON_REMOVE_VOLATILE_TEST(int (UDT::*), int (UDT::*));
HAMON_REMOVE_VOLATILE_TEST(const float (UDT::*), const float (UDT::*));

#undef HAMON_REMOVE_VOLATILE_TEST
