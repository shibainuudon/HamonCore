/**
 *	@file	unit_test_type_traits_add_const.cpp
 *
 *	@brief	add_const のテスト
 */

#include <hamon/type_traits/add_const.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include "type_traits_test_utility.hpp"

HAMON_TRANSFORM_TEST(hamon::add_const, /**/,           const);
HAMON_TRANSFORM_TEST(hamon::add_const, const,          const);
HAMON_TRANSFORM_TEST(hamon::add_const,       volatile, const volatile);
HAMON_TRANSFORM_TEST(hamon::add_const, const volatile, const volatile);
HAMON_TRANSFORM_TEST(hamon::add_const,                &,                &);
HAMON_TRANSFORM_TEST(hamon::add_const, const          &, const          &);
HAMON_TRANSFORM_TEST(hamon::add_const,       volatile &,       volatile &);
HAMON_TRANSFORM_TEST(hamon::add_const, const volatile &, const volatile &);
HAMON_TRANSFORM_TEST(hamon::add_const, *,               *const);
HAMON_TRANSFORM_TEST(hamon::add_const, *const,          *const);
HAMON_TRANSFORM_TEST(hamon::add_const, *      volatile, *const volatile);
HAMON_TRANSFORM_TEST(hamon::add_const, *const volatile, *const volatile);
HAMON_TRANSFORM_TEST(hamon::add_const, const          *, const          * const);
HAMON_TRANSFORM_TEST(hamon::add_const,       volatile *,       volatile * const);
HAMON_TRANSFORM_TEST(hamon::add_const, const volatile *, const volatile * const);
HAMON_TRANSFORM_TEST(hamon::add_const,               [2], const         [2]);
HAMON_TRANSFORM_TEST(hamon::add_const, const         [2], const         [2]);
HAMON_TRANSFORM_TEST(hamon::add_const,       volatile[2], const volatile[2]);
HAMON_TRANSFORM_TEST(hamon::add_const, const volatile[2], const volatile[2]);
HAMON_TRANSFORM_TEST(hamon::add_const,                (&)[2],                (&)[2]);
HAMON_TRANSFORM_TEST(hamon::add_const, const          (&)[2], const          (&)[2]);
HAMON_TRANSFORM_TEST(hamon::add_const,       volatile (&)[2],       volatile (&)[2]);
HAMON_TRANSFORM_TEST(hamon::add_const, const volatile (&)[2], const volatile (&)[2]);
HAMON_TRANSFORM_TEST(hamon::add_const,                &&,                &&);
HAMON_TRANSFORM_TEST(hamon::add_const, const          &&, const          &&);
HAMON_TRANSFORM_TEST(hamon::add_const,       volatile &&,       volatile &&);
HAMON_TRANSFORM_TEST(hamon::add_const, const volatile &&, const volatile &&);
HAMON_TRANSFORM_TEST(hamon::add_const,                (&&)[2],                (&&)[2]);
HAMON_TRANSFORM_TEST(hamon::add_const, const          (&&)[2], const          (&&)[2]);
HAMON_TRANSFORM_TEST(hamon::add_const,       volatile (&&)[2],       volatile (&&)[2]);
HAMON_TRANSFORM_TEST(hamon::add_const, const volatile (&&)[2], const volatile (&&)[2]);

#define HAMON_ADD_CONST_TEST(T1, T2)	\
	static_assert(hamon::is_same<hamon::add_const_t<T1>, T2>::value, "");	\
	static_assert(hamon::is_same<hamon::add_const<T1>::type, T2>::value, "")

HAMON_ADD_CONST_TEST(               void, const          void);
HAMON_ADD_CONST_TEST(const          void, const          void);
HAMON_ADD_CONST_TEST(      volatile void, const volatile void);
HAMON_ADD_CONST_TEST(const volatile void, const volatile void);
HAMON_ADD_CONST_TEST(               void*,                void* const);
HAMON_ADD_CONST_TEST(const          void*, const          void* const);
HAMON_ADD_CONST_TEST(      volatile void*,       volatile void* const);
HAMON_ADD_CONST_TEST(const volatile void*, const volatile void* const);
HAMON_ADD_CONST_TEST(int(int), int(int));
HAMON_ADD_CONST_TEST(void (UDT::*)(void), void (UDT::* const)(void));
HAMON_ADD_CONST_TEST(int (UDT::*)(int), int (UDT::* const)(int));
HAMON_ADD_CONST_TEST(int (UDT::*)(int, float), int (UDT::* const)(int, float));
HAMON_ADD_CONST_TEST(int (UDT::*)(int) const, int (UDT::* const)(int) const);
HAMON_ADD_CONST_TEST(int (UDT::*)(int) volatile, int (UDT::* const)(int) volatile);
HAMON_ADD_CONST_TEST(int (UDT::*)(int) const volatile, int (UDT::* const)(int) const volatile);
HAMON_ADD_CONST_TEST(int (UDT::*), int (UDT::* const));
HAMON_ADD_CONST_TEST(const float (UDT::*), const float (UDT::* const));

#undef HAMON_ADD_CONST_TEST
