/**
 *	@file	unit_test_type_traits_remove_const.cpp
 *
 *	@brief	remove_const のテスト
 */

#include <hamon/type_traits/remove_const.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include "type_traits_test_utility.hpp"

HAMON_TRANSFORM_TEST(hamon::remove_const, /**/          , /**/);
HAMON_TRANSFORM_TEST(hamon::remove_const, const         , /**/);
HAMON_TRANSFORM_TEST(hamon::remove_const,       volatile,       volatile);
HAMON_TRANSFORM_TEST(hamon::remove_const, const volatile,       volatile);
HAMON_TRANSFORM_TEST(hamon::remove_const,                &,                &);
HAMON_TRANSFORM_TEST(hamon::remove_const, const          &, const          &);
HAMON_TRANSFORM_TEST(hamon::remove_const,       volatile &,       volatile &);
HAMON_TRANSFORM_TEST(hamon::remove_const, const volatile &, const volatile &);
HAMON_TRANSFORM_TEST(hamon::remove_const,                &&,                &&);
HAMON_TRANSFORM_TEST(hamon::remove_const, const          &&, const          &&);
HAMON_TRANSFORM_TEST(hamon::remove_const,       volatile &&,       volatile &&);
HAMON_TRANSFORM_TEST(hamon::remove_const, const volatile &&, const volatile &&);
HAMON_TRANSFORM_TEST(hamon::remove_const, *               , *               );
HAMON_TRANSFORM_TEST(hamon::remove_const, * const         , *               );
HAMON_TRANSFORM_TEST(hamon::remove_const, *       volatile, *       volatile);
HAMON_TRANSFORM_TEST(hamon::remove_const, * const volatile, *       volatile);
HAMON_TRANSFORM_TEST(hamon::remove_const, const          *, const          *);
HAMON_TRANSFORM_TEST(hamon::remove_const,       volatile *,       volatile *);
HAMON_TRANSFORM_TEST(hamon::remove_const, const volatile *, const volatile *);
HAMON_TRANSFORM_TEST(hamon::remove_const,                [2],                [2]);
HAMON_TRANSFORM_TEST(hamon::remove_const, const          [2],                [2]);
HAMON_TRANSFORM_TEST(hamon::remove_const,       volatile [2],       volatile [2]);
HAMON_TRANSFORM_TEST(hamon::remove_const, const volatile [2],       volatile [2]);
HAMON_TRANSFORM_TEST(hamon::remove_const,                [],                []);
HAMON_TRANSFORM_TEST(hamon::remove_const, const          [],                []);
HAMON_TRANSFORM_TEST(hamon::remove_const,       volatile [],       volatile []);
HAMON_TRANSFORM_TEST(hamon::remove_const, const volatile [],       volatile []);
HAMON_TRANSFORM_TEST(hamon::remove_const,                (&)[2],                (&)[2]);
HAMON_TRANSFORM_TEST(hamon::remove_const, const          (&)[2], const          (&)[2]);
HAMON_TRANSFORM_TEST(hamon::remove_const,       volatile (&)[2],       volatile (&)[2]);
HAMON_TRANSFORM_TEST(hamon::remove_const, const volatile (&)[2], const volatile (&)[2]);
HAMON_TRANSFORM_TEST(hamon::remove_const,                (&)[],                (&)[]);
HAMON_TRANSFORM_TEST(hamon::remove_const, const          (&)[], const          (&)[]);
HAMON_TRANSFORM_TEST(hamon::remove_const,       volatile (&)[],       volatile (&)[]);
HAMON_TRANSFORM_TEST(hamon::remove_const, const volatile (&)[], const volatile (&)[]);
HAMON_TRANSFORM_TEST(hamon::remove_const,                (&&)[2],                (&&)[2]);
HAMON_TRANSFORM_TEST(hamon::remove_const, const          (&&)[2], const          (&&)[2]);
HAMON_TRANSFORM_TEST(hamon::remove_const,       volatile (&&)[2],       volatile (&&)[2]);
HAMON_TRANSFORM_TEST(hamon::remove_const, const volatile (&&)[2], const volatile (&&)[2]);
HAMON_TRANSFORM_TEST(hamon::remove_const,                (&&)[],                (&&)[]);
HAMON_TRANSFORM_TEST(hamon::remove_const, const          (&&)[], const          (&&)[]);
HAMON_TRANSFORM_TEST(hamon::remove_const,       volatile (&&)[],       volatile (&&)[]);
HAMON_TRANSFORM_TEST(hamon::remove_const, const volatile (&&)[], const volatile (&&)[]);
HAMON_TRANSFORM_TEST(hamon::remove_const,                (*)[2],                (*)[2]);
HAMON_TRANSFORM_TEST(hamon::remove_const, const          (*)[2], const          (*)[2]);
HAMON_TRANSFORM_TEST(hamon::remove_const,       volatile (*)[2],       volatile (*)[2]);
HAMON_TRANSFORM_TEST(hamon::remove_const, const volatile (*)[2], const volatile (*)[2]);
HAMON_TRANSFORM_TEST(hamon::remove_const,                (*)[],                (*)[]);
HAMON_TRANSFORM_TEST(hamon::remove_const, const          (*)[], const          (*)[]);
HAMON_TRANSFORM_TEST(hamon::remove_const,       volatile (*)[],       volatile (*)[]);
HAMON_TRANSFORM_TEST(hamon::remove_const, const volatile (*)[], const volatile (*)[]);

#define HAMON_REMOVE_CONST_TEST(T1, T2)	\
	static_assert(hamon::is_same<hamon::remove_const_t<T1>, T2>::value, "");	\
	static_assert(hamon::is_same<hamon::remove_const<T1>::type, T2>::value, "")

HAMON_REMOVE_CONST_TEST(               void,          void);
HAMON_REMOVE_CONST_TEST(const          void,          void);
HAMON_REMOVE_CONST_TEST(      volatile void, volatile void);
HAMON_REMOVE_CONST_TEST(const volatile void, volatile void);
HAMON_REMOVE_CONST_TEST(void(void), void(void));
HAMON_REMOVE_CONST_TEST(int(void), int(void));
HAMON_REMOVE_CONST_TEST(void(int), void(int));
HAMON_REMOVE_CONST_TEST(int(int), int(int));
HAMON_REMOVE_CONST_TEST(int(char, short), int(char, short));
HAMON_REMOVE_CONST_TEST(int(float, double, long double), int(float, double, long double));
HAMON_REMOVE_CONST_TEST(int(*)(int), int(*)(int));
HAMON_REMOVE_CONST_TEST(int(&)(int), int(&)(int));
HAMON_REMOVE_CONST_TEST(int(&&)(int), int(&&)(int));
HAMON_REMOVE_CONST_TEST(void (UDT::*)(void), void (UDT::*)(void));
HAMON_REMOVE_CONST_TEST(int (UDT::*)(int), int (UDT::*)(int));
HAMON_REMOVE_CONST_TEST(int (UDT::*)(int, float), int (UDT::*)(int, float));
HAMON_REMOVE_CONST_TEST(int (UDT::*)(int) const, int (UDT::*)(int) const);
HAMON_REMOVE_CONST_TEST(int (UDT::*)(int) volatile, int (UDT::*)(int) volatile);
HAMON_REMOVE_CONST_TEST(int (UDT::*)(int) const volatile, int (UDT::*)(int) const volatile);
HAMON_REMOVE_CONST_TEST(int (UDT::*), int (UDT::*));
HAMON_REMOVE_CONST_TEST(const float (UDT::*), const float (UDT::*));

#undef HAMON_REMOVE_CONST_TEST
