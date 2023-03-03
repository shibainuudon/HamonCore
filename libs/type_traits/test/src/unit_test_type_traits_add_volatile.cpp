/**
 *	@file	unit_test_type_traits_add_volatile.cpp
 *
 *	@brief	add_volatile のテスト
 */

#include <hamon/type_traits/add_volatile.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include "type_traits_test_utility.hpp"

HAMON_TRANSFORM_TEST(hamon::add_volatile, /**/,                 volatile);
HAMON_TRANSFORM_TEST(hamon::add_volatile, const,          const volatile);
HAMON_TRANSFORM_TEST(hamon::add_volatile,       volatile,       volatile);
HAMON_TRANSFORM_TEST(hamon::add_volatile, const volatile, const volatile);
HAMON_TRANSFORM_TEST(hamon::add_volatile,                &,                &);
HAMON_TRANSFORM_TEST(hamon::add_volatile, const          &, const          &);
HAMON_TRANSFORM_TEST(hamon::add_volatile,       volatile &,       volatile &);
HAMON_TRANSFORM_TEST(hamon::add_volatile, const volatile &, const volatile &);
HAMON_TRANSFORM_TEST(hamon::add_volatile, *,               *      volatile);
HAMON_TRANSFORM_TEST(hamon::add_volatile, *const,          *const volatile);
HAMON_TRANSFORM_TEST(hamon::add_volatile, *      volatile, *      volatile);
HAMON_TRANSFORM_TEST(hamon::add_volatile, *const volatile, *const volatile);
HAMON_TRANSFORM_TEST(hamon::add_volatile, const          *, const          * volatile);
HAMON_TRANSFORM_TEST(hamon::add_volatile,       volatile *,       volatile * volatile);
HAMON_TRANSFORM_TEST(hamon::add_volatile, const volatile *, const volatile * volatile);
HAMON_TRANSFORM_TEST(hamon::add_volatile,               [2],       volatile[2]);
HAMON_TRANSFORM_TEST(hamon::add_volatile, const         [2], const volatile[2]);
HAMON_TRANSFORM_TEST(hamon::add_volatile,       volatile[2],       volatile[2]);
HAMON_TRANSFORM_TEST(hamon::add_volatile, const volatile[2], const volatile[2]);
HAMON_TRANSFORM_TEST(hamon::add_volatile,                (&)[2],                (&)[2]);
HAMON_TRANSFORM_TEST(hamon::add_volatile, const          (&)[2], const          (&)[2]);
HAMON_TRANSFORM_TEST(hamon::add_volatile,       volatile (&)[2],       volatile (&)[2]);
HAMON_TRANSFORM_TEST(hamon::add_volatile, const volatile (&)[2], const volatile (&)[2]);
HAMON_TRANSFORM_TEST(hamon::add_volatile,                &&,                &&);
HAMON_TRANSFORM_TEST(hamon::add_volatile, const          &&, const          &&);
HAMON_TRANSFORM_TEST(hamon::add_volatile,       volatile &&,       volatile &&);
HAMON_TRANSFORM_TEST(hamon::add_volatile, const volatile &&, const volatile &&);
HAMON_TRANSFORM_TEST(hamon::add_volatile,                (&&)[2],                (&&)[2]);
HAMON_TRANSFORM_TEST(hamon::add_volatile, const          (&&)[2], const          (&&)[2]);
HAMON_TRANSFORM_TEST(hamon::add_volatile,       volatile (&&)[2],       volatile (&&)[2]);
HAMON_TRANSFORM_TEST(hamon::add_volatile, const volatile (&&)[2], const volatile (&&)[2]);

#define HAMON_ADD_VOLATILE_TEST(T1, T2)	\
	static_assert(hamon::is_same<hamon::add_volatile_t<T1>, T2>::value, "");	\
	static_assert(hamon::is_same<hamon::add_volatile<T1>::type, T2>::value, "")

HAMON_ADD_VOLATILE_TEST(               void,       volatile void);
HAMON_ADD_VOLATILE_TEST(const          void, const volatile void);
HAMON_ADD_VOLATILE_TEST(      volatile void,       volatile void);
HAMON_ADD_VOLATILE_TEST(const volatile void, const volatile void);
HAMON_ADD_VOLATILE_TEST(               void*,                void* volatile);
HAMON_ADD_VOLATILE_TEST(const          void*, const          void* volatile);
HAMON_ADD_VOLATILE_TEST(      volatile void*,       volatile void* volatile);
HAMON_ADD_VOLATILE_TEST(const volatile void*, const volatile void* volatile);
HAMON_ADD_VOLATILE_TEST(int(int), int(int));
HAMON_ADD_VOLATILE_TEST(void (UDT::*)(void), void (UDT::* volatile)(void));
HAMON_ADD_VOLATILE_TEST(int (UDT::*)(int), int (UDT::* volatile)(int));
HAMON_ADD_VOLATILE_TEST(int (UDT::*)(int, float), int (UDT::* volatile)(int, float));
HAMON_ADD_VOLATILE_TEST(int (UDT::*)(int) const, int (UDT::* volatile)(int) const);
HAMON_ADD_VOLATILE_TEST(int (UDT::*)(int) volatile, int (UDT::* volatile)(int) volatile);
HAMON_ADD_VOLATILE_TEST(int (UDT::*)(int) const volatile, int (UDT::* volatile)(int) const volatile);
HAMON_ADD_VOLATILE_TEST(int (UDT::*), int (UDT::* volatile));
HAMON_ADD_VOLATILE_TEST(const float (UDT::*), const float (UDT::* volatile));

#undef HAMON_ADD_VOLATILE_TEST
