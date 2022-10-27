/**
 *	@file	unit_test_type_traits_is_nothrow_swappable.cpp
 *
 *	@brief	is_nothrow_swappable のテスト
 */

#include <hamon/type_traits/is_nothrow_swappable.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "type_traits_test_utility.hpp"

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

#define HAMON_IS_NOTHROW_SWAPPABLE_TEST(b, T)	\
	static_assert(hamon::is_nothrow_swappable_v<T>      == b, #T);	\
	static_assert(hamon::is_nothrow_swappable<T>::value == b, #T);	\
	static_assert(hamon::is_nothrow_swappable<T>()      == b, #T)

#else

#define HAMON_IS_NOTHROW_SWAPPABLE_TEST(b, T)	\
	static_assert(hamon::is_nothrow_swappable<T>::value == b, #T);	\
	static_assert(hamon::is_nothrow_swappable<T>()      == b, #T)

#endif

namespace hamon_type_traits_test
{

namespace is_nothrow_swappable_test
{

struct SwapThrow1 {};

void swap(SwapThrow1&, SwapThrow1&);

struct SwapThrow2
{
	SwapThrow2() HAMON_NOEXCEPT = default;
	SwapThrow2(const SwapThrow2&) HAMON_NOEXCEPT_IF(false);
	SwapThrow2& operator=(const SwapThrow2&) HAMON_NOEXCEPT_IF(false);
};

struct SwapNoThrow1
{
	SwapNoThrow1() HAMON_NOEXCEPT = default;
	SwapNoThrow1(const SwapNoThrow1&) HAMON_NOEXCEPT_IF(false);
	SwapNoThrow1& operator=(const SwapNoThrow1&) HAMON_NOEXCEPT_IF(false);
};

void swap(SwapNoThrow1&, SwapNoThrow1&) HAMON_NOEXCEPT;

struct SwapNoThrow2 {};

#if defined(HAMON_HAS_CXX11_NOEXCEPT)
HAMON_IS_NOTHROW_SWAPPABLE_TEST(false, SwapThrow1);
HAMON_IS_NOTHROW_SWAPPABLE_TEST(false, SwapThrow2);
#else
HAMON_IS_NOTHROW_SWAPPABLE_TEST(true,  SwapThrow1);
HAMON_IS_NOTHROW_SWAPPABLE_TEST(true,  SwapThrow2);
#endif
HAMON_IS_NOTHROW_SWAPPABLE_TEST(true,  SwapNoThrow1);
HAMON_IS_NOTHROW_SWAPPABLE_TEST(true,  SwapNoThrow2);

HAMON_IS_NOTHROW_SWAPPABLE_TEST(true,                 int);
HAMON_IS_NOTHROW_SWAPPABLE_TEST(false, const          int);
HAMON_IS_NOTHROW_SWAPPABLE_TEST(true,        volatile int);
HAMON_IS_NOTHROW_SWAPPABLE_TEST(false, const volatile int);
HAMON_IS_NOTHROW_SWAPPABLE_TEST(true,                 bool);
HAMON_IS_NOTHROW_SWAPPABLE_TEST(false, const          bool);
HAMON_IS_NOTHROW_SWAPPABLE_TEST(true,        volatile bool);
HAMON_IS_NOTHROW_SWAPPABLE_TEST(false, const volatile bool);
HAMON_IS_NOTHROW_SWAPPABLE_TEST(false,                int[]);
HAMON_IS_NOTHROW_SWAPPABLE_TEST(false, const          int[]);
HAMON_IS_NOTHROW_SWAPPABLE_TEST(false,       volatile int[]);
HAMON_IS_NOTHROW_SWAPPABLE_TEST(false, const volatile int[]);
HAMON_IS_NOTHROW_SWAPPABLE_TEST(true,                 int[2]);
HAMON_IS_NOTHROW_SWAPPABLE_TEST(false, const          int[2]);
HAMON_IS_NOTHROW_SWAPPABLE_TEST(true,        volatile int[2]);
HAMON_IS_NOTHROW_SWAPPABLE_TEST(false, const volatile int[2]);
HAMON_IS_NOTHROW_SWAPPABLE_TEST(false,                int[][3]);
HAMON_IS_NOTHROW_SWAPPABLE_TEST(false, const          int[][3]);
HAMON_IS_NOTHROW_SWAPPABLE_TEST(false,       volatile int[][3]);
HAMON_IS_NOTHROW_SWAPPABLE_TEST(false, const volatile int[][3]);
HAMON_IS_NOTHROW_SWAPPABLE_TEST(true,                 int[1][2][3]);
HAMON_IS_NOTHROW_SWAPPABLE_TEST(false, const          int[1][2][3]);
HAMON_IS_NOTHROW_SWAPPABLE_TEST(true,        volatile int[1][2][3]);
HAMON_IS_NOTHROW_SWAPPABLE_TEST(false, const volatile int[1][2][3]);
HAMON_IS_NOTHROW_SWAPPABLE_TEST(false,                int[][2][3]);
HAMON_IS_NOTHROW_SWAPPABLE_TEST(false, const          int[][2][3]);
HAMON_IS_NOTHROW_SWAPPABLE_TEST(false,       volatile int[][2][3]);
HAMON_IS_NOTHROW_SWAPPABLE_TEST(false, const volatile int[][2][3]);
HAMON_IS_NOTHROW_SWAPPABLE_TEST(true,                 int&);
HAMON_IS_NOTHROW_SWAPPABLE_TEST(false, const          int&);
HAMON_IS_NOTHROW_SWAPPABLE_TEST(true,        volatile int&);
HAMON_IS_NOTHROW_SWAPPABLE_TEST(false, const volatile int&);
HAMON_IS_NOTHROW_SWAPPABLE_TEST(true,                 int&&);
HAMON_IS_NOTHROW_SWAPPABLE_TEST(false, const          int&&);
HAMON_IS_NOTHROW_SWAPPABLE_TEST(true,        volatile int&&);
HAMON_IS_NOTHROW_SWAPPABLE_TEST(false, const volatile int&&);
HAMON_IS_NOTHROW_SWAPPABLE_TEST(true,                 int*);
HAMON_IS_NOTHROW_SWAPPABLE_TEST(true,  const          int*);
HAMON_IS_NOTHROW_SWAPPABLE_TEST(true,        volatile int*);
HAMON_IS_NOTHROW_SWAPPABLE_TEST(true,  const volatile int*);
HAMON_IS_NOTHROW_SWAPPABLE_TEST(true,                 int(&)[2]);
HAMON_IS_NOTHROW_SWAPPABLE_TEST(false, const          int(&)[2]);
HAMON_IS_NOTHROW_SWAPPABLE_TEST(true,        volatile int(&)[2]);
HAMON_IS_NOTHROW_SWAPPABLE_TEST(false, const volatile int(&)[2]);
HAMON_IS_NOTHROW_SWAPPABLE_TEST(false,                int(&)[]);
HAMON_IS_NOTHROW_SWAPPABLE_TEST(false, const          int(&)[]);
HAMON_IS_NOTHROW_SWAPPABLE_TEST(false,       volatile int(&)[]);
HAMON_IS_NOTHROW_SWAPPABLE_TEST(false, const volatile int(&)[]);
HAMON_IS_NOTHROW_SWAPPABLE_TEST(true,                 int(&&)[2]);
HAMON_IS_NOTHROW_SWAPPABLE_TEST(false, const          int(&&)[2]);
HAMON_IS_NOTHROW_SWAPPABLE_TEST(true,        volatile int(&&)[2]);
HAMON_IS_NOTHROW_SWAPPABLE_TEST(false, const volatile int(&&)[2]);
HAMON_IS_NOTHROW_SWAPPABLE_TEST(false,                int(&&)[]);
HAMON_IS_NOTHROW_SWAPPABLE_TEST(false, const          int(&&)[]);
HAMON_IS_NOTHROW_SWAPPABLE_TEST(false,       volatile int(&&)[]);
HAMON_IS_NOTHROW_SWAPPABLE_TEST(false, const volatile int(&&)[]);
HAMON_IS_NOTHROW_SWAPPABLE_TEST(true,                 int(*)[2]);
HAMON_IS_NOTHROW_SWAPPABLE_TEST(true,  const          int(*)[2]);
HAMON_IS_NOTHROW_SWAPPABLE_TEST(true,        volatile int(*)[2]);
HAMON_IS_NOTHROW_SWAPPABLE_TEST(true,  const volatile int(*)[2]);
HAMON_IS_NOTHROW_SWAPPABLE_TEST(true,                 int(*)[]);
HAMON_IS_NOTHROW_SWAPPABLE_TEST(true,  const          int(*)[]);
HAMON_IS_NOTHROW_SWAPPABLE_TEST(true,        volatile int(*)[]);
HAMON_IS_NOTHROW_SWAPPABLE_TEST(true,  const volatile int(*)[]);
HAMON_IS_NOTHROW_SWAPPABLE_TEST(false,                void);
HAMON_IS_NOTHROW_SWAPPABLE_TEST(false, const          void);
HAMON_IS_NOTHROW_SWAPPABLE_TEST(false,       volatile void);
HAMON_IS_NOTHROW_SWAPPABLE_TEST(false, const volatile void);
HAMON_IS_NOTHROW_SWAPPABLE_TEST(true,                 void*);
HAMON_IS_NOTHROW_SWAPPABLE_TEST(true,  const          void*);
HAMON_IS_NOTHROW_SWAPPABLE_TEST(true,        volatile void*);
HAMON_IS_NOTHROW_SWAPPABLE_TEST(true,  const volatile void*);
#if defined(HAMON_HAS_CXX11_NOEXCEPT)
HAMON_IS_NOTHROW_SWAPPABLE_TEST(false,                UDT);
#else
HAMON_IS_NOTHROW_SWAPPABLE_TEST(true,                 UDT);
#endif
HAMON_IS_NOTHROW_SWAPPABLE_TEST(false, const          UDT);
HAMON_IS_NOTHROW_SWAPPABLE_TEST(false,       volatile UDT);
HAMON_IS_NOTHROW_SWAPPABLE_TEST(false, const volatile UDT);
HAMON_IS_NOTHROW_SWAPPABLE_TEST(true,                 POD_UDT);
HAMON_IS_NOTHROW_SWAPPABLE_TEST(false, const          POD_UDT);
HAMON_IS_NOTHROW_SWAPPABLE_TEST(false,       volatile POD_UDT);
HAMON_IS_NOTHROW_SWAPPABLE_TEST(false, const volatile POD_UDT);
HAMON_IS_NOTHROW_SWAPPABLE_TEST(true,                 enum_UDT);
HAMON_IS_NOTHROW_SWAPPABLE_TEST(false, const          enum_UDT);
HAMON_IS_NOTHROW_SWAPPABLE_TEST(true,        volatile enum_UDT);
HAMON_IS_NOTHROW_SWAPPABLE_TEST(false, const volatile enum_UDT);
HAMON_IS_NOTHROW_SWAPPABLE_TEST(true,                 enum_class_UDT);
HAMON_IS_NOTHROW_SWAPPABLE_TEST(false, const          enum_class_UDT);
HAMON_IS_NOTHROW_SWAPPABLE_TEST(true,        volatile enum_class_UDT);
HAMON_IS_NOTHROW_SWAPPABLE_TEST(false, const volatile enum_class_UDT);
HAMON_IS_NOTHROW_SWAPPABLE_TEST(false,                test_abc1);
HAMON_IS_NOTHROW_SWAPPABLE_TEST(false, const          test_abc1);
HAMON_IS_NOTHROW_SWAPPABLE_TEST(false,       volatile test_abc1);
HAMON_IS_NOTHROW_SWAPPABLE_TEST(false, const volatile test_abc1);
HAMON_IS_NOTHROW_SWAPPABLE_TEST(false,                test_abc2);
HAMON_IS_NOTHROW_SWAPPABLE_TEST(false, const          test_abc2);
HAMON_IS_NOTHROW_SWAPPABLE_TEST(false,       volatile test_abc2);
HAMON_IS_NOTHROW_SWAPPABLE_TEST(false, const volatile test_abc2);
HAMON_IS_NOTHROW_SWAPPABLE_TEST(false,                test_abc3);
HAMON_IS_NOTHROW_SWAPPABLE_TEST(false, const          test_abc3);
HAMON_IS_NOTHROW_SWAPPABLE_TEST(false,       volatile test_abc3);
HAMON_IS_NOTHROW_SWAPPABLE_TEST(false, const volatile test_abc3);

HAMON_IS_NOTHROW_SWAPPABLE_TEST(true, f1);
HAMON_IS_NOTHROW_SWAPPABLE_TEST(true, f2);
HAMON_IS_NOTHROW_SWAPPABLE_TEST(true, f3);
HAMON_IS_NOTHROW_SWAPPABLE_TEST(true, mf1);
HAMON_IS_NOTHROW_SWAPPABLE_TEST(true, mf2);
HAMON_IS_NOTHROW_SWAPPABLE_TEST(true, mf3);
HAMON_IS_NOTHROW_SWAPPABLE_TEST(true, mf4);
HAMON_IS_NOTHROW_SWAPPABLE_TEST(true, mp);
HAMON_IS_NOTHROW_SWAPPABLE_TEST(true, cmf);
HAMON_IS_NOTHROW_SWAPPABLE_TEST(false, void());
HAMON_IS_NOTHROW_SWAPPABLE_TEST(false, foo0_t);
HAMON_IS_NOTHROW_SWAPPABLE_TEST(false, foo1_t);
HAMON_IS_NOTHROW_SWAPPABLE_TEST(false, foo2_t);
HAMON_IS_NOTHROW_SWAPPABLE_TEST(false, foo3_t);
HAMON_IS_NOTHROW_SWAPPABLE_TEST(false, foo4_t);

}	// namespace is_nothrow_swappable_test

}	// namespace hamon_type_traits_test

#undef HAMON_IS_NOTHROW_SWAPPABLE_TEST
