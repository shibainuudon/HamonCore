/**
 *	@file	unit_test_type_traits_is_nothrow_swappable_with.cpp
 *
 *	@brief	is_nothrow_swappable_with のテスト
 */

#include <hamon/type_traits/is_nothrow_swappable_with.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "type_traits_test_utility.hpp"

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

#define HAMON_IS_NOTHROW_SWAPPABLE_WITH_TEST(b, T1, T2)	\
	static_assert(hamon::is_nothrow_swappable_with_v<T1, T2>      == b, #T1 ", " #T2);	\
	static_assert(hamon::is_nothrow_swappable_with<T1, T2>::value == b, #T1 ", " #T2);	\
	static_assert(hamon::is_nothrow_swappable_with<T1, T2>()      == b, #T1 ", " #T2)

#else

#define HAMON_IS_NOTHROW_SWAPPABLE_WITH_TEST(b, T1, T2)	\
	static_assert(hamon::is_nothrow_swappable_with<T1, T2>::value == b, #T1 ", " #T2);	\
	static_assert(hamon::is_nothrow_swappable_with<T1, T2>()      == b, #T1 ", " #T2)

#endif

namespace hamon_type_traits_test
{

namespace is_nothrow_swappable_with_test
{

struct SwapThrow1 {};

void swap(SwapThrow1&, SwapThrow1&);

struct SwapThrow2
{
	SwapThrow2() HAMON_NOEXCEPT = default;
	SwapThrow2(const SwapThrow2&) HAMON_NOEXCEPT_IF(false);
	SwapThrow2& operator=(const SwapThrow2&) HAMON_NOEXCEPT_IF(false);
};

void swap(SwapThrow1&, SwapThrow2&);
void swap(SwapThrow2&, SwapThrow1&);

struct SwapNoThrow1
{
	SwapNoThrow1() HAMON_NOEXCEPT = default;
	SwapNoThrow1(const SwapNoThrow1&) HAMON_NOEXCEPT_IF(false);
	SwapNoThrow1& operator=(const SwapNoThrow1&) HAMON_NOEXCEPT_IF(false);
};

void swap(SwapNoThrow1&, SwapNoThrow1&) HAMON_NOEXCEPT;

struct SwapNoThrow2 {};

void swap(SwapNoThrow1&, SwapNoThrow2&) HAMON_NOEXCEPT;
void swap(SwapNoThrow2&, SwapNoThrow1&) HAMON_NOEXCEPT;

#if defined(HAMON_HAS_CXX11_NOEXCEPT)
HAMON_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, SwapThrow1&, SwapThrow1&);
HAMON_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, SwapThrow1&, SwapThrow2&);
HAMON_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, SwapThrow2&, SwapThrow1&);
HAMON_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, SwapThrow2&, SwapThrow2&);
#else
HAMON_IS_NOTHROW_SWAPPABLE_WITH_TEST(true,  SwapThrow1&, SwapThrow1&);
HAMON_IS_NOTHROW_SWAPPABLE_WITH_TEST(true,  SwapThrow1&, SwapThrow2&);
HAMON_IS_NOTHROW_SWAPPABLE_WITH_TEST(true,  SwapThrow2&, SwapThrow1&);
HAMON_IS_NOTHROW_SWAPPABLE_WITH_TEST(true,  SwapThrow2&, SwapThrow2&);
#endif
HAMON_IS_NOTHROW_SWAPPABLE_WITH_TEST(true,  SwapNoThrow1&, SwapNoThrow1&);
HAMON_IS_NOTHROW_SWAPPABLE_WITH_TEST(true,  SwapNoThrow1&, SwapNoThrow2&);
HAMON_IS_NOTHROW_SWAPPABLE_WITH_TEST(true,  SwapNoThrow2&, SwapNoThrow1&);
HAMON_IS_NOTHROW_SWAPPABLE_WITH_TEST(true,  SwapNoThrow2&, SwapNoThrow2&);

HAMON_IS_NOTHROW_SWAPPABLE_WITH_TEST(false,                int,                int);
HAMON_IS_NOTHROW_SWAPPABLE_WITH_TEST(false,                int, const          int);
HAMON_IS_NOTHROW_SWAPPABLE_WITH_TEST(false,                int,       volatile int);
HAMON_IS_NOTHROW_SWAPPABLE_WITH_TEST(false,                int, const volatile int);
HAMON_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, const          int,                int);
HAMON_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, const          int, const          int);
HAMON_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, const          int,       volatile int);
HAMON_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, const          int, const volatile int);
HAMON_IS_NOTHROW_SWAPPABLE_WITH_TEST(false,       volatile int,                int);
HAMON_IS_NOTHROW_SWAPPABLE_WITH_TEST(false,       volatile int, const          int);
HAMON_IS_NOTHROW_SWAPPABLE_WITH_TEST(false,       volatile int,       volatile int);
HAMON_IS_NOTHROW_SWAPPABLE_WITH_TEST(false,       volatile int, const volatile int);
HAMON_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, const volatile int,                int);
HAMON_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, const volatile int, const          int);
HAMON_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, const volatile int,       volatile int);
HAMON_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, const volatile int, const volatile int);

HAMON_IS_NOTHROW_SWAPPABLE_WITH_TEST(true,                 int&,                int&);
HAMON_IS_NOTHROW_SWAPPABLE_WITH_TEST(false,                int&, const          int&);
HAMON_IS_NOTHROW_SWAPPABLE_WITH_TEST(false,                int&,       volatile int&);
HAMON_IS_NOTHROW_SWAPPABLE_WITH_TEST(false,                int&, const volatile int&);
HAMON_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, const          int&,                int&);
HAMON_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, const          int&, const          int&);
HAMON_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, const          int&,       volatile int&);
HAMON_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, const          int&, const volatile int&);
HAMON_IS_NOTHROW_SWAPPABLE_WITH_TEST(false,       volatile int&,                int&);
HAMON_IS_NOTHROW_SWAPPABLE_WITH_TEST(false,       volatile int&, const          int&);
HAMON_IS_NOTHROW_SWAPPABLE_WITH_TEST(true,        volatile int&,       volatile int&);
HAMON_IS_NOTHROW_SWAPPABLE_WITH_TEST(false,       volatile int&, const volatile int&);
HAMON_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, const volatile int&,                int&);
HAMON_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, const volatile int&, const          int&);
HAMON_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, const volatile int&,       volatile int&);
HAMON_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, const volatile int&, const volatile int&);

HAMON_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, int, int*);
HAMON_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, int, int&);
HAMON_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, int, int&&);
HAMON_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, int, int[2]);
HAMON_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, int, int[]);
HAMON_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, int, int(&)[2]);
HAMON_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, int, int(&)[]);
HAMON_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, int, int(&&)[2]);
HAMON_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, int, int(&&)[]);
HAMON_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, int, int(*)[2]);
HAMON_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, int, int(*)[]);
HAMON_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, int, short);
HAMON_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, int, long);
HAMON_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, int, unsigned int);
HAMON_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, int, float);
HAMON_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, int, void);
HAMON_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, int, void*);
HAMON_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, int, enum_UDT);

HAMON_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, int*, int*);
HAMON_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, int*, int&);
HAMON_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, int*, int&&);
HAMON_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, int*, int[2]);
HAMON_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, int*, int[]);
HAMON_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, int*, int(&)[2]);
HAMON_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, int*, int(&)[]);
HAMON_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, int*, int(&&)[2]);
HAMON_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, int*, int(&&)[]);
HAMON_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, int*, int(*)[2]);
HAMON_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, int*, int(*)[]);
HAMON_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, int*, short*);
HAMON_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, int*, long*);
HAMON_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, int*, unsigned int*);
HAMON_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, int*, float*);
HAMON_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, int*, void);
HAMON_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, int*, void*);
HAMON_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, int*, enum_UDT);

HAMON_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, int&, int*);
HAMON_IS_NOTHROW_SWAPPABLE_WITH_TEST(true,  int&, int&);
HAMON_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, int&, int&&);
HAMON_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, int&, int[2]);
HAMON_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, int&, int[]);
HAMON_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, int&, int(&)[2]);
HAMON_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, int&, int(&)[]);
HAMON_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, int&, int(&&)[2]);
HAMON_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, int&, int(&&)[]);
HAMON_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, int&, int(*)[2]);
HAMON_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, int&, int(*)[]);
HAMON_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, int&, short&);
HAMON_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, int&, long&);
HAMON_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, int&, unsigned int&);
HAMON_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, int&, float&);
HAMON_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, int&, void);
HAMON_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, int&, void*);
HAMON_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, int&, enum_UDT);

HAMON_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, int&&, int*);
HAMON_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, int&&, int&);
HAMON_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, int&&, int&&);
HAMON_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, int&&, int[2]);
HAMON_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, int&&, int[]);
HAMON_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, int&&, int(&)[2]);
HAMON_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, int&&, int(&)[]);
HAMON_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, int&&, int(&&)[2]);
HAMON_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, int&&, int(&&)[]);
HAMON_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, int&&, int(*)[2]);
HAMON_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, int&&, int(*)[]);
HAMON_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, int&&, short&&);
HAMON_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, int&&, long&&);
HAMON_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, int&&, unsigned int&&);
HAMON_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, int&&, float&&);
HAMON_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, int&&, void);
HAMON_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, int&&, void*);
HAMON_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, int&&, enum_UDT);

}	// namespace is_nothrow_swappable_with_test

}	// namespace hamon_type_traits_test

#undef HAMON_IS_NOTHROW_SWAPPABLE_WITH_TEST
