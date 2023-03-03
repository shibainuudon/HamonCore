/**
 *	@file	unit_test_type_traits_add_rvalue_reference.cpp
 *
 *	@brief	add_rvalue_reference のテスト
 */

#include <hamon/type_traits/add_rvalue_reference.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include "type_traits_test_utility.hpp"

HAMON_TRANSFORM_TEST(hamon::add_rvalue_reference, /**/,                          &&);
HAMON_TRANSFORM_TEST(hamon::add_rvalue_reference, const,          const          &&);
HAMON_TRANSFORM_TEST(hamon::add_rvalue_reference,       volatile,       volatile &&);
HAMON_TRANSFORM_TEST(hamon::add_rvalue_reference, const volatile, const volatile &&);
HAMON_TRANSFORM_TEST(hamon::add_rvalue_reference,                &,                &);
HAMON_TRANSFORM_TEST(hamon::add_rvalue_reference, const          &, const          &);
HAMON_TRANSFORM_TEST(hamon::add_rvalue_reference,       volatile &,       volatile &);
HAMON_TRANSFORM_TEST(hamon::add_rvalue_reference, const volatile &, const volatile &);
HAMON_TRANSFORM_TEST(hamon::add_rvalue_reference,                *&,                *&);
HAMON_TRANSFORM_TEST(hamon::add_rvalue_reference, const          *&, const          *&);
HAMON_TRANSFORM_TEST(hamon::add_rvalue_reference,       volatile *&,       volatile *&);
HAMON_TRANSFORM_TEST(hamon::add_rvalue_reference, const volatile *&, const volatile *&);
HAMON_TRANSFORM_TEST(hamon::add_rvalue_reference, *,               *               &&);
HAMON_TRANSFORM_TEST(hamon::add_rvalue_reference, *const,          *const          &&);
HAMON_TRANSFORM_TEST(hamon::add_rvalue_reference, *      volatile, *      volatile &&);
HAMON_TRANSFORM_TEST(hamon::add_rvalue_reference, *const volatile, *const volatile &&);
HAMON_TRANSFORM_TEST(hamon::add_rvalue_reference, const          *, const          *&&);
HAMON_TRANSFORM_TEST(hamon::add_rvalue_reference,       volatile *,       volatile *&&);
HAMON_TRANSFORM_TEST(hamon::add_rvalue_reference, const volatile *, const volatile *&&);
HAMON_TRANSFORM_TEST(hamon::add_rvalue_reference,               [2],                (&&)[2]);
HAMON_TRANSFORM_TEST(hamon::add_rvalue_reference, const         [2], const          (&&)[2]);
HAMON_TRANSFORM_TEST(hamon::add_rvalue_reference,       volatile[2],       volatile (&&)[2]);
HAMON_TRANSFORM_TEST(hamon::add_rvalue_reference, const volatile[2], const volatile (&&)[2]);
HAMON_TRANSFORM_TEST(hamon::add_rvalue_reference,                (&)[2],                (&)[2]);
HAMON_TRANSFORM_TEST(hamon::add_rvalue_reference, const          (&)[2], const          (&)[2]);
HAMON_TRANSFORM_TEST(hamon::add_rvalue_reference,       volatile (&)[2],       volatile (&)[2]);
HAMON_TRANSFORM_TEST(hamon::add_rvalue_reference, const volatile (&)[2], const volatile (&)[2]);
HAMON_TRANSFORM_TEST(hamon::add_rvalue_reference,                &&,                &&);
HAMON_TRANSFORM_TEST(hamon::add_rvalue_reference, const          &&, const          &&);
HAMON_TRANSFORM_TEST(hamon::add_rvalue_reference,       volatile &&,       volatile &&);
HAMON_TRANSFORM_TEST(hamon::add_rvalue_reference, const volatile &&, const volatile &&);
HAMON_TRANSFORM_TEST(hamon::add_rvalue_reference,                (&&)[2],                (&&)[2]);
HAMON_TRANSFORM_TEST(hamon::add_rvalue_reference, const          (&&)[2], const          (&&)[2]);
HAMON_TRANSFORM_TEST(hamon::add_rvalue_reference,       volatile (&&)[2],       volatile (&&)[2]);
HAMON_TRANSFORM_TEST(hamon::add_rvalue_reference, const volatile (&&)[2], const volatile (&&)[2]);

#define HAMON_ADD_RVALUE_REFERENCE_TEST(T1, T2)	\
	static_assert(hamon::is_same<hamon::add_rvalue_reference_t<T1>, T2>::value, "");	\
	static_assert(hamon::is_same<hamon::add_rvalue_reference<T1>::type, T2>::value, "")

HAMON_ADD_RVALUE_REFERENCE_TEST(void(void), void(&&)(void));
HAMON_ADD_RVALUE_REFERENCE_TEST(int(void), int(&&)(void));
HAMON_ADD_RVALUE_REFERENCE_TEST(void(int), void(&&)(int));
HAMON_ADD_RVALUE_REFERENCE_TEST(int(int), int(&&)(int));
HAMON_ADD_RVALUE_REFERENCE_TEST(int(char, short), int(&&)(char, short));
HAMON_ADD_RVALUE_REFERENCE_TEST(int(float, double, long double), int(&&)(float, double, long double));
HAMON_ADD_RVALUE_REFERENCE_TEST(int(*)(int), int(*&&)(int));
HAMON_ADD_RVALUE_REFERENCE_TEST(int(&)(int), int(&)(int));
HAMON_ADD_RVALUE_REFERENCE_TEST(int(&&)(int), int(&&)(int));
HAMON_ADD_RVALUE_REFERENCE_TEST(void (UDT::*)(void), void (UDT::*&&)(void));
HAMON_ADD_RVALUE_REFERENCE_TEST(int (UDT::*)(int), int (UDT::*&&)(int));
HAMON_ADD_RVALUE_REFERENCE_TEST(int (UDT::*)(int, float), int (UDT::*&&)(int, float));
HAMON_ADD_RVALUE_REFERENCE_TEST(int (UDT::*)(int) const, int (UDT::*&&)(int) const);
HAMON_ADD_RVALUE_REFERENCE_TEST(int (UDT::*)(int) volatile, int (UDT::*&&)(int) volatile);
HAMON_ADD_RVALUE_REFERENCE_TEST(int (UDT::*)(int) const volatile, int (UDT::*&&)(int) const volatile);
HAMON_ADD_RVALUE_REFERENCE_TEST(int (UDT::*), int (UDT::*&&));
HAMON_ADD_RVALUE_REFERENCE_TEST(const float (UDT::*), const float (UDT::*&&));

#undef HAMON_ADD_RVALUE_REFERENCE_TEST
