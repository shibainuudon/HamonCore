/**
 *	@file	unit_test_type_traits_remove_pointer.cpp
 *
 *	@brief	remove_pointer のテスト
 */

#include <hamon/type_traits/remove_pointer.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include "type_traits_test_utility.hpp"

HAMON_TRANSFORM_TEST(hamon::remove_pointer, /**/          , /**/          );
HAMON_TRANSFORM_TEST(hamon::remove_pointer, const         , const         );
HAMON_TRANSFORM_TEST(hamon::remove_pointer,       volatile,       volatile);
HAMON_TRANSFORM_TEST(hamon::remove_pointer, const volatile, const volatile);
HAMON_TRANSFORM_TEST(hamon::remove_pointer,                &,                &);
HAMON_TRANSFORM_TEST(hamon::remove_pointer, const          &, const          &);
HAMON_TRANSFORM_TEST(hamon::remove_pointer,       volatile &,       volatile &);
HAMON_TRANSFORM_TEST(hamon::remove_pointer, const volatile &, const volatile &);
HAMON_TRANSFORM_TEST(hamon::remove_pointer, *               , /**/);
HAMON_TRANSFORM_TEST(hamon::remove_pointer, * const         , /**/);
HAMON_TRANSFORM_TEST(hamon::remove_pointer, *       volatile, /**/);
HAMON_TRANSFORM_TEST(hamon::remove_pointer, * const volatile, /**/);
HAMON_TRANSFORM_TEST(hamon::remove_pointer, const          *, const         );
HAMON_TRANSFORM_TEST(hamon::remove_pointer,       volatile *,       volatile);
HAMON_TRANSFORM_TEST(hamon::remove_pointer, const volatile *, const volatile);
HAMON_TRANSFORM_TEST(hamon::remove_pointer,                [2],                [2]);
HAMON_TRANSFORM_TEST(hamon::remove_pointer, const          [2], const          [2]);
HAMON_TRANSFORM_TEST(hamon::remove_pointer,       volatile [2],       volatile [2]);
HAMON_TRANSFORM_TEST(hamon::remove_pointer, const volatile [2], const volatile [2]);
HAMON_TRANSFORM_TEST(hamon::remove_pointer,                (&)[2],                (&)[2]);
HAMON_TRANSFORM_TEST(hamon::remove_pointer, const          (&)[2], const          (&)[2]);
HAMON_TRANSFORM_TEST(hamon::remove_pointer,       volatile (&)[2],       volatile (&)[2]);
HAMON_TRANSFORM_TEST(hamon::remove_pointer, const volatile (&)[2], const volatile (&)[2]);
HAMON_TRANSFORM_TEST(hamon::remove_pointer,                &&,                &&);
HAMON_TRANSFORM_TEST(hamon::remove_pointer, const          &&, const          &&);
HAMON_TRANSFORM_TEST(hamon::remove_pointer,       volatile &&,       volatile &&);
HAMON_TRANSFORM_TEST(hamon::remove_pointer, const volatile &&, const volatile &&);
HAMON_TRANSFORM_TEST(hamon::remove_pointer,                (&&)[2],                (&&)[2]);
HAMON_TRANSFORM_TEST(hamon::remove_pointer, const          (&&)[2], const          (&&)[2]);
HAMON_TRANSFORM_TEST(hamon::remove_pointer,       volatile (&&)[2],       volatile (&&)[2]);
HAMON_TRANSFORM_TEST(hamon::remove_pointer, const volatile (&&)[2], const volatile (&&)[2]);

#define HAMON_REMOVE_POINTER_TEST(T1, T2)	\
	static_assert(hamon::is_same<hamon::remove_pointer_t<T1>, T2>::value, "");	\
	static_assert(hamon::is_same<hamon::remove_pointer<T1>::type, T2>::value, "")

HAMON_REMOVE_POINTER_TEST(               void*,                void);
HAMON_REMOVE_POINTER_TEST(const          void*, const          void);
HAMON_REMOVE_POINTER_TEST(      volatile void*,       volatile void);
HAMON_REMOVE_POINTER_TEST(const volatile void*, const volatile void);
HAMON_REMOVE_POINTER_TEST(void(void), void(void));
HAMON_REMOVE_POINTER_TEST(int(void), int(void));
HAMON_REMOVE_POINTER_TEST(void(int), void(int));
HAMON_REMOVE_POINTER_TEST(int(int), int(int));
HAMON_REMOVE_POINTER_TEST(int(char, short), int(char, short));
HAMON_REMOVE_POINTER_TEST(int(float, double, long double), int(float, double, long double));
HAMON_REMOVE_POINTER_TEST(int(*)(int), int(int));
HAMON_REMOVE_POINTER_TEST(int(&)(int), int(&)(int));
HAMON_REMOVE_POINTER_TEST(int(&&)(int), int(&&)(int));
HAMON_REMOVE_POINTER_TEST(void (UDT::*)(void), void (UDT::*)(void));
HAMON_REMOVE_POINTER_TEST(int (UDT::*)(int), int (UDT::*)(int));
HAMON_REMOVE_POINTER_TEST(int (UDT::*)(int, float), int (UDT::*)(int, float));
HAMON_REMOVE_POINTER_TEST(int (UDT::*)(int) const, int (UDT::*)(int) const);
HAMON_REMOVE_POINTER_TEST(int (UDT::*)(int) volatile, int (UDT::*)(int) volatile);
HAMON_REMOVE_POINTER_TEST(int (UDT::*)(int) const volatile, int (UDT::*)(int) const volatile);
HAMON_REMOVE_POINTER_TEST(int (UDT::*), int (UDT::*));
HAMON_REMOVE_POINTER_TEST(const float (UDT::*), const float (UDT::*));

#undef HAMON_REMOVE_POINTER_TEST
