/**
 *	@file	unit_test_type_traits_is_assignable.cpp
 *
 *	@brief	is_assignable のテスト
 */

#include <hamon/type_traits/is_assignable.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include <cstddef>
#include "type_traits_test_utility.hpp"

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

#define HAMON_IS_ASSIGNABLE_TEST(b, T, U)	\
	static_assert(hamon::is_assignable_v<T, U>      == b, #T ", " #U " == " #b);	\
	static_assert(hamon::is_assignable<T, U>::value == b, #T ", " #U " == " #b);	\
	static_assert(hamon::is_assignable<T, U>{}()    == b, #T ", " #U " == " #b);	\
	static_assert(hamon::is_assignable<T, U>{}      == b, #T ", " #U " == " #b)

#else

#define HAMON_IS_ASSIGNABLE_TEST(b, T, U)	\
	static_assert(hamon::is_assignable<T, U>::value == b, #T ", " #U " == " #b);	\
	static_assert(hamon::is_assignable<T, U>{}()    == b, #T ", " #U " == " #b);	\
	static_assert(hamon::is_assignable<T, U>{}      == b, #T ", " #U " == " #b)

#endif

namespace hamon_type_traits_test
{

namespace is_assignable_test
{

struct S1
{
	S1& operator=(const S1&);
};

struct S2
{
	S2& operator=(int);
};

#define HAMON_IS_ASSIGNABLE_TEST_0(b, T, U)	\
	HAMON_IS_ASSIGNABLE_TEST(b,                     T,                 U);	\
	HAMON_IS_ASSIGNABLE_TEST(b,                     T,  const          U);	\
	HAMON_IS_ASSIGNABLE_TEST(b,                     T,        volatile U);	\
	HAMON_IS_ASSIGNABLE_TEST(b,                     T,  const volatile U);	\
	HAMON_IS_ASSIGNABLE_TEST(b,      const          T,                 U);	\
	HAMON_IS_ASSIGNABLE_TEST(b,      const          T,  const          U);	\
	HAMON_IS_ASSIGNABLE_TEST(b,      const          T,        volatile U);	\
	HAMON_IS_ASSIGNABLE_TEST(b,      const          T,  const volatile U);	\
	HAMON_IS_ASSIGNABLE_TEST(b,            volatile T,                 U);	\
	HAMON_IS_ASSIGNABLE_TEST(b,            volatile T,  const          U);	\
	HAMON_IS_ASSIGNABLE_TEST(b,            volatile T,        volatile U);	\
	HAMON_IS_ASSIGNABLE_TEST(b,            volatile T,  const volatile U);	\
	HAMON_IS_ASSIGNABLE_TEST(b,      const volatile T,                 U);	\
	HAMON_IS_ASSIGNABLE_TEST(b,      const volatile T,  const          U);	\
	HAMON_IS_ASSIGNABLE_TEST(b,      const volatile T,        volatile U);	\
	HAMON_IS_ASSIGNABLE_TEST(b,      const volatile T,  const volatile U)

#define HAMON_IS_ASSIGNABLE_TEST_1(b, T, U)	\
	HAMON_IS_ASSIGNABLE_TEST(b,                     T,                 U);	\
	HAMON_IS_ASSIGNABLE_TEST(b,                     T,  const          U);	\
	HAMON_IS_ASSIGNABLE_TEST(false,                 T,        volatile U);	\
	HAMON_IS_ASSIGNABLE_TEST(false,                 T,  const volatile U);	\
	HAMON_IS_ASSIGNABLE_TEST(false,  const          T,                 U);	\
	HAMON_IS_ASSIGNABLE_TEST(false,  const          T,  const          U);	\
	HAMON_IS_ASSIGNABLE_TEST(false,  const          T,        volatile U);	\
	HAMON_IS_ASSIGNABLE_TEST(false,  const          T,  const volatile U);	\
	HAMON_IS_ASSIGNABLE_TEST(false,        volatile T,                 U);	\
	HAMON_IS_ASSIGNABLE_TEST(false,        volatile T,  const          U);	\
	HAMON_IS_ASSIGNABLE_TEST(false,        volatile T,        volatile U);	\
	HAMON_IS_ASSIGNABLE_TEST(false,        volatile T,  const volatile U);	\
	HAMON_IS_ASSIGNABLE_TEST(false,  const volatile T,                 U);	\
	HAMON_IS_ASSIGNABLE_TEST(false,  const volatile T,  const          U);	\
	HAMON_IS_ASSIGNABLE_TEST(false,  const volatile T,        volatile U);	\
	HAMON_IS_ASSIGNABLE_TEST(false,  const volatile T,  const volatile U)

#define HAMON_IS_ASSIGNABLE_TEST_2(b, T, U)	\
	HAMON_IS_ASSIGNABLE_TEST(b,                     T,                 U);	\
	HAMON_IS_ASSIGNABLE_TEST(b,                     T,  const          U);	\
	HAMON_IS_ASSIGNABLE_TEST(b,                     T,        volatile U);	\
	HAMON_IS_ASSIGNABLE_TEST(b,                     T,  const volatile U);	\
	HAMON_IS_ASSIGNABLE_TEST(false,  const          T,                 U);	\
	HAMON_IS_ASSIGNABLE_TEST(false,  const          T,  const          U);	\
	HAMON_IS_ASSIGNABLE_TEST(false,  const          T,        volatile U);	\
	HAMON_IS_ASSIGNABLE_TEST(false,  const          T,  const volatile U);	\
	HAMON_IS_ASSIGNABLE_TEST(b,            volatile T,                 U);	\
	HAMON_IS_ASSIGNABLE_TEST(b,            volatile T,  const          U);	\
	HAMON_IS_ASSIGNABLE_TEST(b,            volatile T,        volatile U);	\
	HAMON_IS_ASSIGNABLE_TEST(b,            volatile T,  const volatile U);	\
	HAMON_IS_ASSIGNABLE_TEST(false,  const volatile T,                 U);	\
	HAMON_IS_ASSIGNABLE_TEST(false,  const volatile T,  const          U);	\
	HAMON_IS_ASSIGNABLE_TEST(false,  const volatile T,        volatile U);	\
	HAMON_IS_ASSIGNABLE_TEST(false,  const volatile T,  const volatile U)

#define HAMON_IS_ASSIGNABLE_TEST_3(b, T, U)	\
	HAMON_IS_ASSIGNABLE_TEST(b,                     T,                 U);	\
	HAMON_IS_ASSIGNABLE_TEST(b,                     T,  const          U);	\
	HAMON_IS_ASSIGNABLE_TEST(b,                     T,        volatile U);	\
	HAMON_IS_ASSIGNABLE_TEST(b,                     T,  const volatile U);	\
	HAMON_IS_ASSIGNABLE_TEST(false,  const          T,                 U);	\
	HAMON_IS_ASSIGNABLE_TEST(false,  const          T,  const          U);	\
	HAMON_IS_ASSIGNABLE_TEST(false,  const          T,        volatile U);	\
	HAMON_IS_ASSIGNABLE_TEST(false,  const          T,  const volatile U);	\
	HAMON_IS_ASSIGNABLE_TEST(false,        volatile T,                 U);	\
	HAMON_IS_ASSIGNABLE_TEST(false,        volatile T,  const          U);	\
	HAMON_IS_ASSIGNABLE_TEST(false,        volatile T,        volatile U);	\
	HAMON_IS_ASSIGNABLE_TEST(false,        volatile T,  const volatile U);	\
	HAMON_IS_ASSIGNABLE_TEST(false,  const volatile T,                 U);	\
	HAMON_IS_ASSIGNABLE_TEST(false,  const volatile T,  const          U);	\
	HAMON_IS_ASSIGNABLE_TEST(false,  const volatile T,        volatile U);	\
	HAMON_IS_ASSIGNABLE_TEST(false,  const volatile T,  const volatile U)

#define HAMON_IS_ASSIGNABLE_TEST_PTR(b, T, U)	\
	HAMON_IS_ASSIGNABLE_TEST(b,                    T,                 U);	\
	HAMON_IS_ASSIGNABLE_TEST(false,                T,  const          U);	\
	HAMON_IS_ASSIGNABLE_TEST(false,                T,        volatile U);	\
	HAMON_IS_ASSIGNABLE_TEST(false,                T,  const volatile U);	\
	HAMON_IS_ASSIGNABLE_TEST(b,     const          T,                 U);	\
	HAMON_IS_ASSIGNABLE_TEST(b,     const          T,  const          U);	\
	HAMON_IS_ASSIGNABLE_TEST(false, const          T,        volatile U);	\
	HAMON_IS_ASSIGNABLE_TEST(false, const          T,  const volatile U);	\
	HAMON_IS_ASSIGNABLE_TEST(b,           volatile T,                 U);	\
	HAMON_IS_ASSIGNABLE_TEST(false,       volatile T,  const          U);	\
	HAMON_IS_ASSIGNABLE_TEST(b,           volatile T,        volatile U);	\
	HAMON_IS_ASSIGNABLE_TEST(false,       volatile T,  const volatile U);	\
	HAMON_IS_ASSIGNABLE_TEST(b,     const volatile T,                 U);	\
	HAMON_IS_ASSIGNABLE_TEST(b,     const volatile T,  const          U);	\
	HAMON_IS_ASSIGNABLE_TEST(b,     const volatile T,        volatile U);	\
	HAMON_IS_ASSIGNABLE_TEST(b,     const volatile T,  const volatile U)

HAMON_IS_ASSIGNABLE_TEST_1(true,  S1, S1);
HAMON_IS_ASSIGNABLE_TEST_1(true,  S1, S1&);
HAMON_IS_ASSIGNABLE_TEST_1(true,  S1, S1&&);
HAMON_IS_ASSIGNABLE_TEST  (false, S1, S1*);
HAMON_IS_ASSIGNABLE_TEST  (false, S1, S1[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, S1, S1[]);
HAMON_IS_ASSIGNABLE_TEST  (false, S1, S1(&)[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, S1, S1(&)[]);
HAMON_IS_ASSIGNABLE_TEST  (false, S1, S1(&&)[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, S1, S1(&&)[]);
HAMON_IS_ASSIGNABLE_TEST  (false, S1, S1(*)[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, S1, S1(*)[]);
HAMON_IS_ASSIGNABLE_TEST  (false, S1, S2);
HAMON_IS_ASSIGNABLE_TEST  (false, S1, int);
HAMON_IS_ASSIGNABLE_TEST  (false, S1, float);
HAMON_IS_ASSIGNABLE_TEST  (false, S1, bool);
HAMON_IS_ASSIGNABLE_TEST  (false, S1, enum_class_UDT);
HAMON_IS_ASSIGNABLE_TEST  (false, S1, void);
HAMON_IS_ASSIGNABLE_TEST  (false, S1, std::nullptr_t);
HAMON_IS_ASSIGNABLE_TEST_1(true,  S1&, S1);
HAMON_IS_ASSIGNABLE_TEST_1(true,  S1&, S1&);
HAMON_IS_ASSIGNABLE_TEST_1(true,  S1&, S1&&);
HAMON_IS_ASSIGNABLE_TEST  (false, S1&, S1*);
HAMON_IS_ASSIGNABLE_TEST  (false, S1&, S1[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, S1&, S1[]);
HAMON_IS_ASSIGNABLE_TEST  (false, S1&, S1(&)[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, S1&, S1(&)[]);
HAMON_IS_ASSIGNABLE_TEST  (false, S1&, S1(&&)[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, S1&, S1(&&)[]);
HAMON_IS_ASSIGNABLE_TEST  (false, S1&, S1(*)[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, S1&, S1(*)[]);
HAMON_IS_ASSIGNABLE_TEST  (false, S1&, S2);
HAMON_IS_ASSIGNABLE_TEST  (false, S1&, int);
HAMON_IS_ASSIGNABLE_TEST  (false, S1&, float);
HAMON_IS_ASSIGNABLE_TEST  (false, S1&, bool);
HAMON_IS_ASSIGNABLE_TEST  (false, S1&, enum_class_UDT);
HAMON_IS_ASSIGNABLE_TEST  (false, S1&, void);
HAMON_IS_ASSIGNABLE_TEST  (false, S1&, std::nullptr_t);
HAMON_IS_ASSIGNABLE_TEST_1(true,  S1&&, S1);
HAMON_IS_ASSIGNABLE_TEST_1(true,  S1&&, S1&);
HAMON_IS_ASSIGNABLE_TEST_1(true,  S1&&, S1&&);
HAMON_IS_ASSIGNABLE_TEST  (false, S1&&, S1*);
HAMON_IS_ASSIGNABLE_TEST  (false, S1&&, S1[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, S1&&, S1[]);
HAMON_IS_ASSIGNABLE_TEST  (false, S1&&, S1(&)[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, S1&&, S1(&)[]);
HAMON_IS_ASSIGNABLE_TEST  (false, S1&&, S1(&&)[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, S1&&, S1(&&)[]);
HAMON_IS_ASSIGNABLE_TEST  (false, S1&&, S1(*)[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, S1&&, S1(*)[]);
HAMON_IS_ASSIGNABLE_TEST  (false, S1&&, S2);
HAMON_IS_ASSIGNABLE_TEST  (false, S1&&, int);
HAMON_IS_ASSIGNABLE_TEST  (false, S1&&, float);
HAMON_IS_ASSIGNABLE_TEST  (false, S1&&, bool);
HAMON_IS_ASSIGNABLE_TEST  (false, S1&&, enum_class_UDT);
HAMON_IS_ASSIGNABLE_TEST  (false, S1&&, void);
HAMON_IS_ASSIGNABLE_TEST  (false, S1&&, std::nullptr_t);
HAMON_IS_ASSIGNABLE_TEST  (false, S1[2], S1);
HAMON_IS_ASSIGNABLE_TEST  (false, S1[2], S1&);
HAMON_IS_ASSIGNABLE_TEST  (false, S1[2], S1&&);
HAMON_IS_ASSIGNABLE_TEST  (false, S1[2], S1*);
HAMON_IS_ASSIGNABLE_TEST  (false, S1[2], S1[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, S1[2], S1[]);
HAMON_IS_ASSIGNABLE_TEST  (false, S1[2], S1(&)[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, S1[2], S1(&)[]);
HAMON_IS_ASSIGNABLE_TEST  (false, S1[2], S1(&&)[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, S1[2], S1(&&)[]);
HAMON_IS_ASSIGNABLE_TEST  (false, S1[2], S1(*)[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, S1[2], S1(*)[]);
HAMON_IS_ASSIGNABLE_TEST  (false, S1[2], S2);
HAMON_IS_ASSIGNABLE_TEST  (false, S1[2], int);
HAMON_IS_ASSIGNABLE_TEST  (false, S1[2], float);
HAMON_IS_ASSIGNABLE_TEST  (false, S1[2], bool);
HAMON_IS_ASSIGNABLE_TEST  (false, S1[2], enum_class_UDT);
HAMON_IS_ASSIGNABLE_TEST  (false, S1[2], void);
HAMON_IS_ASSIGNABLE_TEST  (false, S1[2], std::nullptr_t);
HAMON_IS_ASSIGNABLE_TEST  (false, S1[], S1);
HAMON_IS_ASSIGNABLE_TEST  (false, S1[], S1&);
HAMON_IS_ASSIGNABLE_TEST  (false, S1[], S1&&);
HAMON_IS_ASSIGNABLE_TEST  (false, S1[], S1*);
HAMON_IS_ASSIGNABLE_TEST  (false, S1[], S1[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, S1[], S1[]);
HAMON_IS_ASSIGNABLE_TEST  (false, S1[], S1(&)[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, S1[], S1(&)[]);
HAMON_IS_ASSIGNABLE_TEST  (false, S1[], S1(&&)[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, S1[], S1(&&)[]);
HAMON_IS_ASSIGNABLE_TEST  (false, S1[], S1(*)[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, S1[], S1(*)[]);
HAMON_IS_ASSIGNABLE_TEST  (false, S1[], S2);
HAMON_IS_ASSIGNABLE_TEST  (false, S1[], int);
HAMON_IS_ASSIGNABLE_TEST  (false, S1[], float);
HAMON_IS_ASSIGNABLE_TEST  (false, S1[], bool);
HAMON_IS_ASSIGNABLE_TEST  (false, S1[], enum_class_UDT);
HAMON_IS_ASSIGNABLE_TEST  (false, S1[], void);
HAMON_IS_ASSIGNABLE_TEST  (false, S1[], std::nullptr_t);
HAMON_IS_ASSIGNABLE_TEST  (false, S1(&)[2], S1);
HAMON_IS_ASSIGNABLE_TEST  (false, S1(&)[2], S1&);
HAMON_IS_ASSIGNABLE_TEST  (false, S1(&)[2], S1&&);
HAMON_IS_ASSIGNABLE_TEST  (false, S1(&)[2], S1*);
HAMON_IS_ASSIGNABLE_TEST  (false, S1(&)[2], S1[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, S1(&)[2], S1[]);
HAMON_IS_ASSIGNABLE_TEST  (false, S1(&)[2], S1(&)[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, S1(&)[2], S1(&)[]);
HAMON_IS_ASSIGNABLE_TEST  (false, S1(&)[2], S1(&&)[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, S1(&)[2], S1(&&)[]);
HAMON_IS_ASSIGNABLE_TEST  (false, S1(&)[2], S1(*)[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, S1(&)[2], S1(*)[]);
HAMON_IS_ASSIGNABLE_TEST  (false, S1(&)[2], S2);
HAMON_IS_ASSIGNABLE_TEST  (false, S1(&)[2], int);
HAMON_IS_ASSIGNABLE_TEST  (false, S1(&)[2], float);
HAMON_IS_ASSIGNABLE_TEST  (false, S1(&)[2], bool);
HAMON_IS_ASSIGNABLE_TEST  (false, S1(&)[2], enum_class_UDT);
HAMON_IS_ASSIGNABLE_TEST  (false, S1(&)[2], void);
HAMON_IS_ASSIGNABLE_TEST  (false, S1(&)[2], std::nullptr_t);
HAMON_IS_ASSIGNABLE_TEST  (false, S1(&)[], S1);
HAMON_IS_ASSIGNABLE_TEST  (false, S1(&)[], S1&);
HAMON_IS_ASSIGNABLE_TEST  (false, S1(&)[], S1&&);
HAMON_IS_ASSIGNABLE_TEST  (false, S1(&)[], S1*);
HAMON_IS_ASSIGNABLE_TEST  (false, S1(&)[], S1[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, S1(&)[], S1[]);
HAMON_IS_ASSIGNABLE_TEST  (false, S1(&)[], S1(&)[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, S1(&)[], S1(&)[]);
HAMON_IS_ASSIGNABLE_TEST  (false, S1(&)[], S1(&&)[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, S1(&)[], S1(&&)[]);
HAMON_IS_ASSIGNABLE_TEST  (false, S1(&)[], S1(*)[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, S1(&)[], S1(*)[]);
HAMON_IS_ASSIGNABLE_TEST  (false, S1(&)[], S2);
HAMON_IS_ASSIGNABLE_TEST  (false, S1(&)[], int);
HAMON_IS_ASSIGNABLE_TEST  (false, S1(&)[], float);
HAMON_IS_ASSIGNABLE_TEST  (false, S1(&)[], bool);
HAMON_IS_ASSIGNABLE_TEST  (false, S1(&)[], enum_class_UDT);
HAMON_IS_ASSIGNABLE_TEST  (false, S1(&)[], void);
HAMON_IS_ASSIGNABLE_TEST  (false, S1(&)[], std::nullptr_t);
HAMON_IS_ASSIGNABLE_TEST  (false, S1(&&)[2], S1);
HAMON_IS_ASSIGNABLE_TEST  (false, S1(&&)[2], S1&);
HAMON_IS_ASSIGNABLE_TEST  (false, S1(&&)[2], S1&&);
HAMON_IS_ASSIGNABLE_TEST  (false, S1(&&)[2], S1*);
HAMON_IS_ASSIGNABLE_TEST  (false, S1(&&)[2], S1[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, S1(&&)[2], S1[]);
HAMON_IS_ASSIGNABLE_TEST  (false, S1(&&)[2], S1(&)[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, S1(&&)[2], S1(&)[]);
HAMON_IS_ASSIGNABLE_TEST  (false, S1(&&)[2], S1(&&)[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, S1(&&)[2], S1(&&)[]);
HAMON_IS_ASSIGNABLE_TEST  (false, S1(&&)[2], S1(*)[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, S1(&&)[2], S1(*)[]);
HAMON_IS_ASSIGNABLE_TEST  (false, S1(&&)[2], S2);
HAMON_IS_ASSIGNABLE_TEST  (false, S1(&&)[2], int);
HAMON_IS_ASSIGNABLE_TEST  (false, S1(&&)[2], float);
HAMON_IS_ASSIGNABLE_TEST  (false, S1(&&)[2], bool);
HAMON_IS_ASSIGNABLE_TEST  (false, S1(&&)[2], enum_class_UDT);
HAMON_IS_ASSIGNABLE_TEST  (false, S1(&&)[2], void);
HAMON_IS_ASSIGNABLE_TEST  (false, S1(&&)[2], std::nullptr_t);
HAMON_IS_ASSIGNABLE_TEST  (false, S1(&&)[], S1);
HAMON_IS_ASSIGNABLE_TEST  (false, S1(&&)[], S1&);
HAMON_IS_ASSIGNABLE_TEST  (false, S1(&&)[], S1&&);
HAMON_IS_ASSIGNABLE_TEST  (false, S1(&&)[], S1*);
HAMON_IS_ASSIGNABLE_TEST  (false, S1(&&)[], S1[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, S1(&&)[], S1[]);
HAMON_IS_ASSIGNABLE_TEST  (false, S1(&&)[], S1(&)[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, S1(&&)[], S1(&)[]);
HAMON_IS_ASSIGNABLE_TEST  (false, S1(&&)[], S1(&&)[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, S1(&&)[], S1(&&)[]);
HAMON_IS_ASSIGNABLE_TEST  (false, S1(&&)[], S1(*)[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, S1(&&)[], S1(*)[]);
HAMON_IS_ASSIGNABLE_TEST  (false, S1(&&)[], S2);
HAMON_IS_ASSIGNABLE_TEST  (false, S1(&&)[], int);
HAMON_IS_ASSIGNABLE_TEST  (false, S1(&&)[], float);
HAMON_IS_ASSIGNABLE_TEST  (false, S1(&&)[], bool);
HAMON_IS_ASSIGNABLE_TEST  (false, S1(&&)[], enum_class_UDT);
HAMON_IS_ASSIGNABLE_TEST  (false, S1(&&)[], void);
HAMON_IS_ASSIGNABLE_TEST  (false, S1(&&)[], std::nullptr_t);
HAMON_IS_ASSIGNABLE_TEST  (false, S1(*)[2], S1);
HAMON_IS_ASSIGNABLE_TEST  (false, S1(*)[2], S1&);
HAMON_IS_ASSIGNABLE_TEST  (false, S1(*)[2], S1&&);
HAMON_IS_ASSIGNABLE_TEST  (false, S1(*)[2], S1*);
HAMON_IS_ASSIGNABLE_TEST  (false, S1(*)[2], S1[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, S1(*)[2], S1[]);
HAMON_IS_ASSIGNABLE_TEST  (false, S1(*)[2], S1(&)[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, S1(*)[2], S1(&)[]);
HAMON_IS_ASSIGNABLE_TEST  (false, S1(*)[2], S1(&&)[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, S1(*)[2], S1(&&)[]);
HAMON_IS_ASSIGNABLE_TEST  (false, S1(*)[2], S1(*)[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, S1(*)[2], S1(*)[]);
HAMON_IS_ASSIGNABLE_TEST  (false, S1(*)[2], S2);
HAMON_IS_ASSIGNABLE_TEST  (false, S1(*)[2], int);
HAMON_IS_ASSIGNABLE_TEST  (false, S1(*)[2], float);
HAMON_IS_ASSIGNABLE_TEST  (false, S1(*)[2], bool);
HAMON_IS_ASSIGNABLE_TEST  (false, S1(*)[2], enum_class_UDT);
HAMON_IS_ASSIGNABLE_TEST  (false, S1(*)[2], void);
HAMON_IS_ASSIGNABLE_TEST  (false, S1(*)[2], std::nullptr_t);
HAMON_IS_ASSIGNABLE_TEST  (false, S1(*)[], S1);
HAMON_IS_ASSIGNABLE_TEST  (false, S1(*)[], S1&);
HAMON_IS_ASSIGNABLE_TEST  (false, S1(*)[], S1&&);
HAMON_IS_ASSIGNABLE_TEST  (false, S1(*)[], S1*);
HAMON_IS_ASSIGNABLE_TEST  (false, S1(*)[], S1[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, S1(*)[], S1[]);
HAMON_IS_ASSIGNABLE_TEST  (false, S1(*)[], S1(&)[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, S1(*)[], S1(&)[]);
HAMON_IS_ASSIGNABLE_TEST  (false, S1(*)[], S1(&&)[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, S1(*)[], S1(&&)[]);
HAMON_IS_ASSIGNABLE_TEST  (false, S1(*)[], S1(*)[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, S1(*)[], S1(*)[]);
HAMON_IS_ASSIGNABLE_TEST  (false, S1(*)[], S2);
HAMON_IS_ASSIGNABLE_TEST  (false, S1(*)[], int);
HAMON_IS_ASSIGNABLE_TEST  (false, S1(*)[], float);
HAMON_IS_ASSIGNABLE_TEST  (false, S1(*)[], bool);
HAMON_IS_ASSIGNABLE_TEST  (false, S1(*)[], enum_class_UDT);
HAMON_IS_ASSIGNABLE_TEST  (false, S1(*)[], void);
HAMON_IS_ASSIGNABLE_TEST  (false, S1(*)[], std::nullptr_t);
HAMON_IS_ASSIGNABLE_TEST  (false, S1*, S1);
HAMON_IS_ASSIGNABLE_TEST  (false, S1*, S1&);
HAMON_IS_ASSIGNABLE_TEST  (false, S1*, S1&&);
HAMON_IS_ASSIGNABLE_TEST  (false, S1*, S1*);
HAMON_IS_ASSIGNABLE_TEST  (false, S1*, S1[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, S1*, S1[]);
HAMON_IS_ASSIGNABLE_TEST  (false, S1*, S1(&)[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, S1*, S1(&)[]);
HAMON_IS_ASSIGNABLE_TEST  (false, S1*, S1(&&)[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, S1*, S1(&&)[]);
HAMON_IS_ASSIGNABLE_TEST  (false, S1*, S1(*)[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, S1*, S1(*)[]);
HAMON_IS_ASSIGNABLE_TEST  (false, S1*, S2*);
HAMON_IS_ASSIGNABLE_TEST  (false, S1*, int*);
HAMON_IS_ASSIGNABLE_TEST  (false, S1*, float*);
HAMON_IS_ASSIGNABLE_TEST  (false, S1*, bool*);
HAMON_IS_ASSIGNABLE_TEST  (false, S1*, enum_class_UDT*);
HAMON_IS_ASSIGNABLE_TEST  (false, S1*, void*);
HAMON_IS_ASSIGNABLE_TEST  (false, S1*, std::nullptr_t);
HAMON_IS_ASSIGNABLE_TEST    (false, S1*&, S1);
HAMON_IS_ASSIGNABLE_TEST    (false, S1*&, S1&);
HAMON_IS_ASSIGNABLE_TEST    (false, S1*&, S1&&);
HAMON_IS_ASSIGNABLE_TEST_PTR(true,  S1*&, S1*);
HAMON_IS_ASSIGNABLE_TEST_PTR(true,  S1*&, S1[2]);			//
HAMON_IS_ASSIGNABLE_TEST_PTR(true,  S1*&, S1[]);			//
HAMON_IS_ASSIGNABLE_TEST_PTR(true,  S1*&, S1(&)[2]);		//
HAMON_IS_ASSIGNABLE_TEST_PTR(true,  S1*&, S1(&)[]);			//
HAMON_IS_ASSIGNABLE_TEST_PTR(true,  S1*&, S1(&&)[2]);		//
HAMON_IS_ASSIGNABLE_TEST_PTR(true,  S1*&, S1(&&)[]);		//
HAMON_IS_ASSIGNABLE_TEST    (false, S1*&, S1(*)[2]);
HAMON_IS_ASSIGNABLE_TEST    (false, S1*&, S1(*)[]);
HAMON_IS_ASSIGNABLE_TEST    (false, S1*&, S2*);
HAMON_IS_ASSIGNABLE_TEST    (false, S1*&, int*);
HAMON_IS_ASSIGNABLE_TEST    (false, S1*&, float*);
HAMON_IS_ASSIGNABLE_TEST    (false, S1*&, bool*);
HAMON_IS_ASSIGNABLE_TEST    (false, S1*&, enum_class_UDT*);
HAMON_IS_ASSIGNABLE_TEST    (false, S1*&, void*);
HAMON_IS_ASSIGNABLE_TEST_0  (true,  S1*&, std::nullptr_t);

HAMON_IS_ASSIGNABLE_TEST_1(true,  S2, S2);
HAMON_IS_ASSIGNABLE_TEST_1(true,  S2, S2&);
HAMON_IS_ASSIGNABLE_TEST_1(true,  S2, S2&&);
HAMON_IS_ASSIGNABLE_TEST  (false, S2, S2*);
HAMON_IS_ASSIGNABLE_TEST  (false, S2, S2[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, S2, S2[]);
HAMON_IS_ASSIGNABLE_TEST  (false, S2, S2(&)[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, S2, S2(&)[]);
HAMON_IS_ASSIGNABLE_TEST  (false, S2, S2(&&)[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, S2, S2(&&)[]);
HAMON_IS_ASSIGNABLE_TEST  (false, S2, S2(*)[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, S2, S2(*)[]);
HAMON_IS_ASSIGNABLE_TEST  (false, S2, S1);
HAMON_IS_ASSIGNABLE_TEST_3(true,  S2, int);
HAMON_IS_ASSIGNABLE_TEST_3(true,  S2, float);
HAMON_IS_ASSIGNABLE_TEST_3(true,  S2, bool);
HAMON_IS_ASSIGNABLE_TEST  (false, S2, enum_class_UDT);
HAMON_IS_ASSIGNABLE_TEST  (false, S2, void);
HAMON_IS_ASSIGNABLE_TEST  (false, S2, std::nullptr_t);
HAMON_IS_ASSIGNABLE_TEST_1(true,  S2&, S2);
HAMON_IS_ASSIGNABLE_TEST_1(true,  S2&, S2&);
HAMON_IS_ASSIGNABLE_TEST_1(true,  S2&, S2&&);
HAMON_IS_ASSIGNABLE_TEST  (false, S2&, S2*);
HAMON_IS_ASSIGNABLE_TEST  (false, S2&, S2[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, S2&, S2[]);
HAMON_IS_ASSIGNABLE_TEST  (false, S2&, S2(&)[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, S2&, S2(&)[]);
HAMON_IS_ASSIGNABLE_TEST  (false, S2&, S2(&&)[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, S2&, S2(&&)[]);
HAMON_IS_ASSIGNABLE_TEST  (false, S2&, S2(*)[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, S2&, S2(*)[]);
HAMON_IS_ASSIGNABLE_TEST  (false, S2&, S1);
HAMON_IS_ASSIGNABLE_TEST_3(true,  S2&, int);
HAMON_IS_ASSIGNABLE_TEST_3(true,  S2&, float);
HAMON_IS_ASSIGNABLE_TEST_3(true,  S2&, bool);
HAMON_IS_ASSIGNABLE_TEST  (false, S2&, enum_class_UDT);
HAMON_IS_ASSIGNABLE_TEST  (false, S2&, void);
HAMON_IS_ASSIGNABLE_TEST  (false, S2&, std::nullptr_t);
HAMON_IS_ASSIGNABLE_TEST_1(true,  S2&&, S2);
HAMON_IS_ASSIGNABLE_TEST_1(true,  S2&&, S2&);
HAMON_IS_ASSIGNABLE_TEST_1(true,  S2&&, S2&&);
HAMON_IS_ASSIGNABLE_TEST  (false, S2&&, S2*);
HAMON_IS_ASSIGNABLE_TEST  (false, S2&&, S2[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, S2&&, S2[]);
HAMON_IS_ASSIGNABLE_TEST  (false, S2&&, S2(&)[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, S2&&, S2(&)[]);
HAMON_IS_ASSIGNABLE_TEST  (false, S2&&, S2(&&)[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, S2&&, S2(&&)[]);
HAMON_IS_ASSIGNABLE_TEST  (false, S2&&, S2(*)[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, S2&&, S2(*)[]);
HAMON_IS_ASSIGNABLE_TEST  (false, S2&&, S1);
HAMON_IS_ASSIGNABLE_TEST_3(true,  S2&&, int);
HAMON_IS_ASSIGNABLE_TEST_3(true,  S2&&, float);
HAMON_IS_ASSIGNABLE_TEST_3(true,  S2&&, bool);
HAMON_IS_ASSIGNABLE_TEST  (false, S2&&, enum_class_UDT);
HAMON_IS_ASSIGNABLE_TEST  (false, S2&&, void);
HAMON_IS_ASSIGNABLE_TEST  (false, S2&&, std::nullptr_t);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2[2], S2);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2[2], S2&);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2[2], S2&&);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2[2], S2*);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2[2], S2[2]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2[2], S2[]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2[2], S2(&)[2]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2[2], S2(&)[]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2[2], S2(&&)[2]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2[2], S2(&&)[]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2[2], S2(*)[2]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2[2], S2(*)[]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2[2], S1);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2[2], int);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2[2], float);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2[2], bool);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2[2], enum_class_UDT);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2[2], void);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2[2], std::nullptr_t);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2[], S2);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2[], S2&);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2[], S2&&);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2[], S2*);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2[], S2[2]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2[], S2[]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2[], S2(&)[2]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2[], S2(&)[]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2[], S2(&&)[2]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2[], S2(&&)[]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2[], S2(*)[2]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2[], S2(*)[]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2[], S1);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2[], int);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2[], float);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2[], bool);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2[], enum_class_UDT);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2[], void);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2[], std::nullptr_t);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2(&)[2], S2);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2(&)[2], S2&);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2(&)[2], S2&&);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2(&)[2], S2*);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2(&)[2], S2[2]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2(&)[2], S2[]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2(&)[2], S2(&)[2]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2(&)[2], S2(&)[]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2(&)[2], S2(&&)[2]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2(&)[2], S2(&&)[]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2(&)[2], S2(*)[2]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2(&)[2], S2(*)[]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2(&)[2], S1);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2(&)[2], int);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2(&)[2], float);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2(&)[2], bool);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2(&)[2], enum_class_UDT);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2(&)[2], void);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2(&)[2], std::nullptr_t);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2(&)[], S2);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2(&)[], S2&);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2(&)[], S2&&);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2(&)[], S2*);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2(&)[], S2[2]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2(&)[], S2[]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2(&)[], S2(&)[2]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2(&)[], S2(&)[]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2(&)[], S2(&&)[2]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2(&)[], S2(&&)[]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2(&)[], S2(*)[2]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2(&)[], S2(*)[]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2(&)[], S1);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2(&)[], int);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2(&)[], float);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2(&)[], bool);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2(&)[], enum_class_UDT);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2(&)[], void);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2(&)[], std::nullptr_t);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2(&&)[2], S2);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2(&&)[2], S2&);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2(&&)[2], S2&&);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2(&&)[2], S2*);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2(&&)[2], S2[2]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2(&&)[2], S2[]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2(&&)[2], S2(&)[2]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2(&&)[2], S2(&)[]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2(&&)[2], S2(&&)[2]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2(&&)[2], S2(&&)[]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2(&&)[2], S2(*)[2]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2(&&)[2], S2(*)[]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2(&&)[2], S1);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2(&&)[2], int);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2(&&)[2], float);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2(&&)[2], bool);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2(&&)[2], enum_class_UDT);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2(&&)[2], void);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2(&&)[2], std::nullptr_t);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2(&&)[], S2);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2(&&)[], S2&);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2(&&)[], S2&&);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2(&&)[], S2*);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2(&&)[], S2[2]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2(&&)[], S2[]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2(&&)[], S2(&)[2]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2(&&)[], S2(&)[]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2(&&)[], S2(&&)[2]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2(&&)[], S2(&&)[]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2(&&)[], S2(*)[2]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2(&&)[], S2(*)[]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2(&&)[], S1);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2(&&)[], int);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2(&&)[], float);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2(&&)[], bool);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2(&&)[], enum_class_UDT);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2(&&)[], void);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2(&&)[], std::nullptr_t);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2(*)[2], S2);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2(*)[2], S2&);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2(*)[2], S2&&);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2(*)[2], S2*);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2(*)[2], S2[2]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2(*)[2], S2[]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2(*)[2], S2(&)[2]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2(*)[2], S2(&)[]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2(*)[2], S2(&&)[2]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2(*)[2], S2(&&)[]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2(*)[2], S2(*)[2]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2(*)[2], S2(*)[]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2(*)[2], S1);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2(*)[2], int);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2(*)[2], float);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2(*)[2], bool);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2(*)[2], enum_class_UDT);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2(*)[2], void);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2(*)[2], std::nullptr_t);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2(*)[], S2);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2(*)[], S2&);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2(*)[], S2&&);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2(*)[], S2*);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2(*)[], S2[2]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2(*)[], S2[]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2(*)[], S2(&)[2]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2(*)[], S2(&)[]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2(*)[], S2(&&)[2]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2(*)[], S2(&&)[]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2(*)[], S2(*)[2]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2(*)[], S2(*)[]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2(*)[], S1);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2(*)[], int);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2(*)[], float);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2(*)[], bool);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2(*)[], enum_class_UDT);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2(*)[], void);
//	HAMON_IS_ASSIGNABLE_TEST  (false, S2(*)[], std::nullptr_t);
HAMON_IS_ASSIGNABLE_TEST  (false, S2*, S2);
HAMON_IS_ASSIGNABLE_TEST  (false, S2*, S2&);
HAMON_IS_ASSIGNABLE_TEST  (false, S2*, S2&&);
HAMON_IS_ASSIGNABLE_TEST  (false, S2*, S2*);
HAMON_IS_ASSIGNABLE_TEST  (false, S2*, S2[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, S2*, S2[]);
HAMON_IS_ASSIGNABLE_TEST  (false, S2*, S2(&)[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, S2*, S2(&)[]);
HAMON_IS_ASSIGNABLE_TEST  (false, S2*, S2(&&)[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, S2*, S2(&&)[]);
HAMON_IS_ASSIGNABLE_TEST  (false, S2*, S2(*)[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, S2*, S2(*)[]);
HAMON_IS_ASSIGNABLE_TEST  (false, S2*, S1*);
HAMON_IS_ASSIGNABLE_TEST  (false, S2*, int*);
HAMON_IS_ASSIGNABLE_TEST  (false, S2*, float*);
HAMON_IS_ASSIGNABLE_TEST  (false, S2*, bool*);
HAMON_IS_ASSIGNABLE_TEST  (false, S2*, enum_class_UDT*);
HAMON_IS_ASSIGNABLE_TEST  (false, S2*, void*);
HAMON_IS_ASSIGNABLE_TEST  (false, S2*, std::nullptr_t);
HAMON_IS_ASSIGNABLE_TEST    (false, S2*&, S2);
HAMON_IS_ASSIGNABLE_TEST    (false, S2*&, S2&);
HAMON_IS_ASSIGNABLE_TEST    (false, S2*&, S2&&);
HAMON_IS_ASSIGNABLE_TEST_PTR(true,  S2*&, S2*);
HAMON_IS_ASSIGNABLE_TEST_PTR(true,  S2*&, S2[2]);			//
HAMON_IS_ASSIGNABLE_TEST_PTR(true,  S2*&, S2[]);			//
HAMON_IS_ASSIGNABLE_TEST_PTR(true,  S2*&, S2(&)[2]);		//
HAMON_IS_ASSIGNABLE_TEST_PTR(true,  S2*&, S2(&)[]);			//
HAMON_IS_ASSIGNABLE_TEST_PTR(true,  S2*&, S2(&&)[2]);		//
HAMON_IS_ASSIGNABLE_TEST_PTR(true,  S2*&, S2(&&)[]);		//
HAMON_IS_ASSIGNABLE_TEST    (false, S2*&, S2(*)[2]);
HAMON_IS_ASSIGNABLE_TEST    (false, S2*&, S2(*)[]);
HAMON_IS_ASSIGNABLE_TEST    (false, S2*&, S1*);
HAMON_IS_ASSIGNABLE_TEST    (false, S2*&, int*);
HAMON_IS_ASSIGNABLE_TEST    (false, S2*&, float*);
HAMON_IS_ASSIGNABLE_TEST    (false, S2*&, bool*);
HAMON_IS_ASSIGNABLE_TEST    (false, S2*&, enum_class_UDT*);
HAMON_IS_ASSIGNABLE_TEST    (false, S2*&, void*);
HAMON_IS_ASSIGNABLE_TEST_0  (true,  S2*&, std::nullptr_t);

HAMON_IS_ASSIGNABLE_TEST  (false, int, int);
HAMON_IS_ASSIGNABLE_TEST  (false, int, int&);
HAMON_IS_ASSIGNABLE_TEST  (false, int, int&&);
HAMON_IS_ASSIGNABLE_TEST  (false, int, int*);
HAMON_IS_ASSIGNABLE_TEST  (false, int, int[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, int, int[]);
HAMON_IS_ASSIGNABLE_TEST  (false, int, int(&)[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, int, int(&)[]);
HAMON_IS_ASSIGNABLE_TEST  (false, int, int(&&)[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, int, int(&&)[]);
HAMON_IS_ASSIGNABLE_TEST  (false, int, int(*)[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, int, int(*)[]);
HAMON_IS_ASSIGNABLE_TEST  (false, int, float);
HAMON_IS_ASSIGNABLE_TEST  (false, int, bool);
HAMON_IS_ASSIGNABLE_TEST  (false, int, enum_class_UDT);
HAMON_IS_ASSIGNABLE_TEST  (false, int, enum_UDT);
HAMON_IS_ASSIGNABLE_TEST  (false, int, void);
HAMON_IS_ASSIGNABLE_TEST  (false, int, std::nullptr_t);
HAMON_IS_ASSIGNABLE_TEST_2(true,  int&, int);				//
HAMON_IS_ASSIGNABLE_TEST_2(true,  int&, int&);				//
HAMON_IS_ASSIGNABLE_TEST_2(true,  int&, int&&);				//
HAMON_IS_ASSIGNABLE_TEST  (false, int&, int*);
HAMON_IS_ASSIGNABLE_TEST  (false, int&, int[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, int&, int[]);
HAMON_IS_ASSIGNABLE_TEST  (false, int&, int(&)[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, int&, int(&)[]);
HAMON_IS_ASSIGNABLE_TEST  (false, int&, int(&&)[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, int&, int(&&)[]);
HAMON_IS_ASSIGNABLE_TEST  (false, int&, int(*)[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, int&, int(*)[]);
HAMON_IS_ASSIGNABLE_TEST_2(true,  int&, float);				//
HAMON_IS_ASSIGNABLE_TEST_2(true,  int&, bool);				//
HAMON_IS_ASSIGNABLE_TEST_2(false, int&, enum_class_UDT);
HAMON_IS_ASSIGNABLE_TEST_2(true,  int&, enum_UDT);			//
HAMON_IS_ASSIGNABLE_TEST  (false, int&, void);
HAMON_IS_ASSIGNABLE_TEST  (false, int&, std::nullptr_t);
HAMON_IS_ASSIGNABLE_TEST  (false, int&&, int);
HAMON_IS_ASSIGNABLE_TEST  (false, int&&, int&);
HAMON_IS_ASSIGNABLE_TEST  (false, int&&, int&&);
HAMON_IS_ASSIGNABLE_TEST  (false, int&&, int*);
HAMON_IS_ASSIGNABLE_TEST  (false, int&&, int[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, int&&, int[]);
HAMON_IS_ASSIGNABLE_TEST  (false, int&&, int(&)[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, int&&, int(&)[]);
HAMON_IS_ASSIGNABLE_TEST  (false, int&&, int(&&)[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, int&&, int(&&)[]);
HAMON_IS_ASSIGNABLE_TEST  (false, int&&, int(*)[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, int&&, int(*)[]);
HAMON_IS_ASSIGNABLE_TEST  (false, int&&, float);
HAMON_IS_ASSIGNABLE_TEST  (false, int&&, bool);
HAMON_IS_ASSIGNABLE_TEST  (false, int&&, enum_class_UDT);
HAMON_IS_ASSIGNABLE_TEST  (false, int&&, enum_UDT);
HAMON_IS_ASSIGNABLE_TEST  (false, int&&, void);
HAMON_IS_ASSIGNABLE_TEST  (false, int&&, std::nullptr_t);
HAMON_IS_ASSIGNABLE_TEST  (false, int[2], int);
HAMON_IS_ASSIGNABLE_TEST  (false, int[2], int&);
HAMON_IS_ASSIGNABLE_TEST  (false, int[2], int&&);
HAMON_IS_ASSIGNABLE_TEST  (false, int[2], int*);
HAMON_IS_ASSIGNABLE_TEST  (false, int[2], int[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, int[2], int[]);
HAMON_IS_ASSIGNABLE_TEST  (false, int[2], int(&)[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, int[2], int(&)[]);
HAMON_IS_ASSIGNABLE_TEST  (false, int[2], int(&&)[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, int[2], int(&&)[]);
HAMON_IS_ASSIGNABLE_TEST  (false, int[2], int(*)[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, int[2], int(*)[]);
HAMON_IS_ASSIGNABLE_TEST  (false, int[2], float);
HAMON_IS_ASSIGNABLE_TEST  (false, int[2], bool);
HAMON_IS_ASSIGNABLE_TEST  (false, int[2], enum_class_UDT);
HAMON_IS_ASSIGNABLE_TEST  (false, int[2], enum_UDT);
HAMON_IS_ASSIGNABLE_TEST  (false, int[2], void);
HAMON_IS_ASSIGNABLE_TEST  (false, int[2], std::nullptr_t);
HAMON_IS_ASSIGNABLE_TEST  (false, int[], int);
HAMON_IS_ASSIGNABLE_TEST  (false, int[], int&);
HAMON_IS_ASSIGNABLE_TEST  (false, int[], int&&);
HAMON_IS_ASSIGNABLE_TEST  (false, int[], int*);
HAMON_IS_ASSIGNABLE_TEST  (false, int[], int[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, int[], int[]);
HAMON_IS_ASSIGNABLE_TEST  (false, int[], int(&)[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, int[], int(&)[]);
HAMON_IS_ASSIGNABLE_TEST  (false, int[], int(&&)[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, int[], int(&&)[]);
HAMON_IS_ASSIGNABLE_TEST  (false, int[], int(*)[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, int[], int(*)[]);
HAMON_IS_ASSIGNABLE_TEST  (false, int[], float);
HAMON_IS_ASSIGNABLE_TEST  (false, int[], bool);
HAMON_IS_ASSIGNABLE_TEST  (false, int[], enum_class_UDT);
HAMON_IS_ASSIGNABLE_TEST  (false, int[], enum_UDT);
HAMON_IS_ASSIGNABLE_TEST  (false, int[], void);
HAMON_IS_ASSIGNABLE_TEST  (false, int[], std::nullptr_t);
HAMON_IS_ASSIGNABLE_TEST  (false, int(&)[2], int);
HAMON_IS_ASSIGNABLE_TEST  (false, int(&)[2], int&);
HAMON_IS_ASSIGNABLE_TEST  (false, int(&)[2], int&&);
HAMON_IS_ASSIGNABLE_TEST  (false, int(&)[2], int*);
HAMON_IS_ASSIGNABLE_TEST  (false, int(&)[2], int[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, int(&)[2], int[]);
HAMON_IS_ASSIGNABLE_TEST  (false, int(&)[2], int(&)[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, int(&)[2], int(&)[]);
HAMON_IS_ASSIGNABLE_TEST  (false, int(&)[2], int(&&)[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, int(&)[2], int(&&)[]);
HAMON_IS_ASSIGNABLE_TEST  (false, int(&)[2], int(*)[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, int(&)[2], int(*)[]);
HAMON_IS_ASSIGNABLE_TEST  (false, int(&)[2], float);
HAMON_IS_ASSIGNABLE_TEST  (false, int(&)[2], bool);
HAMON_IS_ASSIGNABLE_TEST  (false, int(&)[2], enum_class_UDT);
HAMON_IS_ASSIGNABLE_TEST  (false, int(&)[2], enum_UDT);
HAMON_IS_ASSIGNABLE_TEST  (false, int(&)[2], void);
HAMON_IS_ASSIGNABLE_TEST  (false, int(&)[2], std::nullptr_t);
HAMON_IS_ASSIGNABLE_TEST  (false, int(&)[], int);
HAMON_IS_ASSIGNABLE_TEST  (false, int(&)[], int&);
HAMON_IS_ASSIGNABLE_TEST  (false, int(&)[], int&&);
HAMON_IS_ASSIGNABLE_TEST  (false, int(&)[], int*);
HAMON_IS_ASSIGNABLE_TEST  (false, int(&)[], int[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, int(&)[], int[]);
HAMON_IS_ASSIGNABLE_TEST  (false, int(&)[], int(&)[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, int(&)[], int(&)[]);
HAMON_IS_ASSIGNABLE_TEST  (false, int(&)[], int(&&)[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, int(&)[], int(&&)[]);
HAMON_IS_ASSIGNABLE_TEST  (false, int(&)[], int(*)[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, int(&)[], int(*)[]);
HAMON_IS_ASSIGNABLE_TEST  (false, int(&)[], float);
HAMON_IS_ASSIGNABLE_TEST  (false, int(&)[], bool);
HAMON_IS_ASSIGNABLE_TEST  (false, int(&)[], enum_class_UDT);
HAMON_IS_ASSIGNABLE_TEST  (false, int(&)[], enum_UDT);
HAMON_IS_ASSIGNABLE_TEST  (false, int(&)[], void);
HAMON_IS_ASSIGNABLE_TEST  (false, int(&)[], std::nullptr_t);
HAMON_IS_ASSIGNABLE_TEST  (false, int(&&)[2], int);
HAMON_IS_ASSIGNABLE_TEST  (false, int(&&)[2], int&);
HAMON_IS_ASSIGNABLE_TEST  (false, int(&&)[2], int&&);
HAMON_IS_ASSIGNABLE_TEST  (false, int(&&)[2], int*);
HAMON_IS_ASSIGNABLE_TEST  (false, int(&&)[2], int[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, int(&&)[2], int[]);
HAMON_IS_ASSIGNABLE_TEST  (false, int(&&)[2], int(&)[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, int(&&)[2], int(&)[]);
HAMON_IS_ASSIGNABLE_TEST  (false, int(&&)[2], int(&&)[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, int(&&)[2], int(&&)[]);
HAMON_IS_ASSIGNABLE_TEST  (false, int(&&)[2], int(*)[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, int(&&)[2], int(*)[]);
HAMON_IS_ASSIGNABLE_TEST  (false, int(&&)[2], float);
HAMON_IS_ASSIGNABLE_TEST  (false, int(&&)[2], bool);
HAMON_IS_ASSIGNABLE_TEST  (false, int(&&)[2], enum_class_UDT);
HAMON_IS_ASSIGNABLE_TEST  (false, int(&&)[2], enum_UDT);
HAMON_IS_ASSIGNABLE_TEST  (false, int(&&)[2], void);
HAMON_IS_ASSIGNABLE_TEST  (false, int(&&)[2], std::nullptr_t);
HAMON_IS_ASSIGNABLE_TEST  (false, int(&&)[], int);
HAMON_IS_ASSIGNABLE_TEST  (false, int(&&)[], int&);
HAMON_IS_ASSIGNABLE_TEST  (false, int(&&)[], int&&);
HAMON_IS_ASSIGNABLE_TEST  (false, int(&&)[], int*);
HAMON_IS_ASSIGNABLE_TEST  (false, int(&&)[], int[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, int(&&)[], int[]);
HAMON_IS_ASSIGNABLE_TEST  (false, int(&&)[], int(&)[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, int(&&)[], int(&)[]);
HAMON_IS_ASSIGNABLE_TEST  (false, int(&&)[], int(&&)[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, int(&&)[], int(&&)[]);
HAMON_IS_ASSIGNABLE_TEST  (false, int(&&)[], int(*)[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, int(&&)[], int(*)[]);
HAMON_IS_ASSIGNABLE_TEST  (false, int(&&)[], float);
HAMON_IS_ASSIGNABLE_TEST  (false, int(&&)[], bool);
HAMON_IS_ASSIGNABLE_TEST  (false, int(&&)[], enum_class_UDT);
HAMON_IS_ASSIGNABLE_TEST  (false, int(&&)[], enum_UDT);
HAMON_IS_ASSIGNABLE_TEST  (false, int(&&)[], void);
HAMON_IS_ASSIGNABLE_TEST  (false, int(&&)[], std::nullptr_t);
HAMON_IS_ASSIGNABLE_TEST  (false, int(*)[2], int);
HAMON_IS_ASSIGNABLE_TEST  (false, int(*)[2], int&);
HAMON_IS_ASSIGNABLE_TEST  (false, int(*)[2], int&&);
HAMON_IS_ASSIGNABLE_TEST  (false, int(*)[2], int*);
HAMON_IS_ASSIGNABLE_TEST  (false, int(*)[2], int[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, int(*)[2], int[]);
HAMON_IS_ASSIGNABLE_TEST  (false, int(*)[2], int(&)[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, int(*)[2], int(&)[]);
HAMON_IS_ASSIGNABLE_TEST  (false, int(*)[2], int(&&)[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, int(*)[2], int(&&)[]);
HAMON_IS_ASSIGNABLE_TEST  (false, int(*)[2], int(*)[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, int(*)[2], int(*)[]);
HAMON_IS_ASSIGNABLE_TEST  (false, int(*)[2], float);
HAMON_IS_ASSIGNABLE_TEST  (false, int(*)[2], bool);
HAMON_IS_ASSIGNABLE_TEST  (false, int(*)[2], enum_class_UDT);
HAMON_IS_ASSIGNABLE_TEST  (false, int(*)[2], enum_UDT);
HAMON_IS_ASSIGNABLE_TEST  (false, int(*)[2], void);
HAMON_IS_ASSIGNABLE_TEST  (false, int(*)[2], std::nullptr_t);
HAMON_IS_ASSIGNABLE_TEST  (false, int(*)[], int);
HAMON_IS_ASSIGNABLE_TEST  (false, int(*)[], int&);
HAMON_IS_ASSIGNABLE_TEST  (false, int(*)[], int&&);
HAMON_IS_ASSIGNABLE_TEST  (false, int(*)[], int*);
HAMON_IS_ASSIGNABLE_TEST  (false, int(*)[], int[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, int(*)[], int[]);
HAMON_IS_ASSIGNABLE_TEST  (false, int(*)[], int(&)[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, int(*)[], int(&)[]);
HAMON_IS_ASSIGNABLE_TEST  (false, int(*)[], int(&&)[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, int(*)[], int(&&)[]);
HAMON_IS_ASSIGNABLE_TEST  (false, int(*)[], int(*)[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, int(*)[], int(*)[]);
HAMON_IS_ASSIGNABLE_TEST  (false, int(*)[], float);
HAMON_IS_ASSIGNABLE_TEST  (false, int(*)[], bool);
HAMON_IS_ASSIGNABLE_TEST  (false, int(*)[], enum_class_UDT);
HAMON_IS_ASSIGNABLE_TEST  (false, int(*)[], enum_UDT);
HAMON_IS_ASSIGNABLE_TEST  (false, int(*)[], void);
HAMON_IS_ASSIGNABLE_TEST  (false, int(*)[], std::nullptr_t);
HAMON_IS_ASSIGNABLE_TEST  (false, int*, int);
HAMON_IS_ASSIGNABLE_TEST  (false, int*, int&);
HAMON_IS_ASSIGNABLE_TEST  (false, int*, int&&);
HAMON_IS_ASSIGNABLE_TEST  (false, int*, int*);
HAMON_IS_ASSIGNABLE_TEST  (false, int*, int[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, int*, int[]);
HAMON_IS_ASSIGNABLE_TEST  (false, int*, int(&)[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, int*, int(&)[]);
HAMON_IS_ASSIGNABLE_TEST  (false, int*, int(&&)[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, int*, int(&&)[]);
HAMON_IS_ASSIGNABLE_TEST  (false, int*, int(*)[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, int*, int(*)[]);
HAMON_IS_ASSIGNABLE_TEST  (false, int*, float*);
HAMON_IS_ASSIGNABLE_TEST  (false, int*, bool*);
HAMON_IS_ASSIGNABLE_TEST  (false, int*, enum_class_UDT*);
HAMON_IS_ASSIGNABLE_TEST  (false, int*, enum_UDT*);
HAMON_IS_ASSIGNABLE_TEST  (false, int*, void);
HAMON_IS_ASSIGNABLE_TEST  (false, int*, void*);
HAMON_IS_ASSIGNABLE_TEST  (false, int*, std::nullptr_t);
HAMON_IS_ASSIGNABLE_TEST    (false, int*&, int);
HAMON_IS_ASSIGNABLE_TEST    (false, int*&, int&);
HAMON_IS_ASSIGNABLE_TEST    (false, int*&, int&&);
HAMON_IS_ASSIGNABLE_TEST_PTR(true,  int*&, int*);
HAMON_IS_ASSIGNABLE_TEST_PTR(true,  int*&, int[2]);				//
HAMON_IS_ASSIGNABLE_TEST_PTR(true,  int*&, int[]);				//
HAMON_IS_ASSIGNABLE_TEST_PTR(true,  int*&, int(&)[2]);			//
HAMON_IS_ASSIGNABLE_TEST_PTR(true,  int*&, int(&)[]);			//
HAMON_IS_ASSIGNABLE_TEST_PTR(true,  int*&, int(&&)[2]);			//
HAMON_IS_ASSIGNABLE_TEST_PTR(true,  int*&, int(&&)[]);			//
HAMON_IS_ASSIGNABLE_TEST    (false, int*&, int(*)[2]);
HAMON_IS_ASSIGNABLE_TEST    (false, int*&, int(*)[]);
HAMON_IS_ASSIGNABLE_TEST    (false, int*&, float*);
HAMON_IS_ASSIGNABLE_TEST    (false, int*&, bool*);
HAMON_IS_ASSIGNABLE_TEST    (false, int*&, enum_class_UDT*);
HAMON_IS_ASSIGNABLE_TEST    (false, int*&, enum_UDT*);
HAMON_IS_ASSIGNABLE_TEST    (false, int*&, void);
HAMON_IS_ASSIGNABLE_TEST    (false, int*&, void*);
HAMON_IS_ASSIGNABLE_TEST_0  (true,  int*&, std::nullptr_t);

HAMON_IS_ASSIGNABLE_TEST_2(false, float, float);				//
HAMON_IS_ASSIGNABLE_TEST_2(false, float, float&);				//
HAMON_IS_ASSIGNABLE_TEST_2(false, float, float&&);				//
HAMON_IS_ASSIGNABLE_TEST  (false, float, float*);
HAMON_IS_ASSIGNABLE_TEST  (false, float, float[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, float, float[]);
HAMON_IS_ASSIGNABLE_TEST  (false, float, float(&)[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, float, float(&)[]);
HAMON_IS_ASSIGNABLE_TEST  (false, float, float(&&)[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, float, float(&&)[]);
HAMON_IS_ASSIGNABLE_TEST  (false, float, float(*)[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, float, float(*)[]);
HAMON_IS_ASSIGNABLE_TEST_2(false, float, int);					//
HAMON_IS_ASSIGNABLE_TEST_2(false, float, bool);					//
HAMON_IS_ASSIGNABLE_TEST_2(false, float, enum_class_UDT);
HAMON_IS_ASSIGNABLE_TEST_2(false, float, enum_UDT);				//
HAMON_IS_ASSIGNABLE_TEST  (false, float, void);
HAMON_IS_ASSIGNABLE_TEST  (false, float, std::nullptr_t);
HAMON_IS_ASSIGNABLE_TEST_2(true,  float&, float);				//
HAMON_IS_ASSIGNABLE_TEST_2(true,  float&, float&);				//
HAMON_IS_ASSIGNABLE_TEST_2(true,  float&, float&&);				//
HAMON_IS_ASSIGNABLE_TEST  (false, float&, float*);
HAMON_IS_ASSIGNABLE_TEST  (false, float&, float[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, float&, float[]);
HAMON_IS_ASSIGNABLE_TEST  (false, float&, float(&)[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, float&, float(&)[]);
HAMON_IS_ASSIGNABLE_TEST  (false, float&, float(&&)[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, float&, float(&&)[]);
HAMON_IS_ASSIGNABLE_TEST  (false, float&, float(*)[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, float&, float(*)[]);
HAMON_IS_ASSIGNABLE_TEST_2(true,  float&, int);					//
HAMON_IS_ASSIGNABLE_TEST_2(true,  float&, bool);				//
HAMON_IS_ASSIGNABLE_TEST_2(false, float&, enum_class_UDT);
HAMON_IS_ASSIGNABLE_TEST_2(true,  float&, enum_UDT);			//
HAMON_IS_ASSIGNABLE_TEST  (false, float&, void);
HAMON_IS_ASSIGNABLE_TEST  (false, float&, std::nullptr_t);
HAMON_IS_ASSIGNABLE_TEST_2(false, float&&, float);				//
HAMON_IS_ASSIGNABLE_TEST_2(false, float&&, float&);				//
HAMON_IS_ASSIGNABLE_TEST_2(false, float&&, float&&);			//
HAMON_IS_ASSIGNABLE_TEST  (false, float&&, float*);
HAMON_IS_ASSIGNABLE_TEST  (false, float&&, float[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, float&&, float[]);
HAMON_IS_ASSIGNABLE_TEST  (false, float&&, float(&)[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, float&&, float(&)[]);
HAMON_IS_ASSIGNABLE_TEST  (false, float&&, float(&&)[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, float&&, float(&&)[]);
HAMON_IS_ASSIGNABLE_TEST  (false, float&&, float(*)[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, float&&, float(*)[]);
HAMON_IS_ASSIGNABLE_TEST_2(false, float&&, int);				//
HAMON_IS_ASSIGNABLE_TEST_2(false, float&&, bool);				//
HAMON_IS_ASSIGNABLE_TEST  (false, float&&, enum_class_UDT);
HAMON_IS_ASSIGNABLE_TEST_2(false, float&&, enum_UDT);			//
HAMON_IS_ASSIGNABLE_TEST  (false, float&&, void);
HAMON_IS_ASSIGNABLE_TEST  (false, float&&, std::nullptr_t);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float[2], float);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float[2], float&);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float[2], float&&);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float[2], float*);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float[2], float[2]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float[2], float[]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float[2], float(&)[2]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float[2], float(&)[]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float[2], float(&&)[2]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float[2], float(&&)[]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float[2], float(*)[2]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float[2], float(*)[]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float[2], float);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float[2], bool);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float[2], enum_class_UDT);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float[2], enum_UDT);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float[2], void);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float[2], std::nullptr_t);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float[], float);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float[], float&);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float[], float&&);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float[], float*);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float[], float[2]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float[], float[]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float[], float(&)[2]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float[], float(&)[]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float[], float(&&)[2]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float[], float(&&)[]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float[], float(*)[2]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float[], float(*)[]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float[], int);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float[], bool);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float[], enum_class_UDT);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float[], enum_UDT);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float[], void);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float[], std::nullptr_t);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float(&)[2], float);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float(&)[2], float&);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float(&)[2], float&&);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float(&)[2], float*);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float(&)[2], float[2]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float(&)[2], float[]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float(&)[2], float(&)[2]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float(&)[2], float(&)[]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float(&)[2], float(&&)[2]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float(&)[2], float(&&)[]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float(&)[2], float(*)[2]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float(&)[2], float(*)[]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float(&)[2], int);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float(&)[2], bool);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float(&)[2], enum_class_UDT);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float(&)[2], enum_UDT);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float(&)[2], void);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float(&)[2], std::nullptr_t);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float(&)[], float);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float(&)[], float&);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float(&)[], float&&);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float(&)[], float*);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float(&)[], float[2]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float(&)[], float[]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float(&)[], float(&)[2]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float(&)[], float(&)[]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float(&)[], float(&&)[2]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float(&)[], float(&&)[]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float(&)[], float(*)[2]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float(&)[], float(*)[]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float(&)[], int);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float(&)[], bool);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float(&)[], enum_class_UDT);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float(&)[], enum_UDT);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float(&)[], void);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float(&)[], std::nullptr_t);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float(&&)[2], float);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float(&&)[2], float&);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float(&&)[2], float&&);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float(&&)[2], float*);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float(&&)[2], float[2]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float(&&)[2], float[]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float(&&)[2], float(&)[2]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float(&&)[2], float(&)[]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float(&&)[2], float(&&)[2]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float(&&)[2], float(&&)[]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float(&&)[2], float(*)[2]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float(&&)[2], float(*)[]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float(&&)[2], int);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float(&&)[2], bool);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float(&&)[2], enum_class_UDT);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float(&&)[2], enum_UDT);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float(&&)[2], void);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float(&&)[2], std::nullptr_t);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float(&&)[], float);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float(&&)[], float&);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float(&&)[], float&&);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float(&&)[], float*);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float(&&)[], float[2]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float(&&)[], float[]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float(&&)[], float(&)[2]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float(&&)[], float(&)[]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float(&&)[], float(&&)[2]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float(&&)[], float(&&)[]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float(&&)[], float(*)[2]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float(&&)[], float(*)[]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float(&&)[], int);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float(&&)[], bool);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float(&&)[], enum_class_UDT);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float(&&)[], enum_UDT);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float(&&)[], void);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float(&&)[], std::nullptr_t);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float(*)[2], float);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float(*)[2], float&);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float(*)[2], float&&);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float(*)[2], float*);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float(*)[2], float[2]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float(*)[2], float[]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float(*)[2], float(&)[2]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float(*)[2], float(&)[]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float(*)[2], float(&&)[2]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float(*)[2], float(&&)[]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float(*)[2], float(*)[2]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float(*)[2], float(*)[]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float(*)[2], int);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float(*)[2], bool);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float(*)[2], enum_class_UDT);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float(*)[2], enum_UDT);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float(*)[2], void);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float(*)[2], std::nullptr_t);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float(*)[], float);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float(*)[], float&);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float(*)[], float&&);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float(*)[], float*);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float(*)[], float[2]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float(*)[], float[]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float(*)[], float(&)[2]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float(*)[], float(&)[]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float(*)[], float(&&)[2]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float(*)[], float(&&)[]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float(*)[], float(*)[2]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float(*)[], float(*)[]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float(*)[], int);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float(*)[], bool);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float(*)[], enum_class_UDT);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float(*)[], enum_UDT);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float(*)[], void);
//	HAMON_IS_ASSIGNABLE_TEST  (false, float(*)[], std::nullptr_t);
HAMON_IS_ASSIGNABLE_TEST  (false, float*, float);
HAMON_IS_ASSIGNABLE_TEST  (false, float*, float&);
HAMON_IS_ASSIGNABLE_TEST  (false, float*, float&&);
HAMON_IS_ASSIGNABLE_TEST  (false, float*, float*);
HAMON_IS_ASSIGNABLE_TEST  (false, float*, float[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, float*, float[]);
HAMON_IS_ASSIGNABLE_TEST  (false, float*, float(&)[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, float*, float(&)[]);
HAMON_IS_ASSIGNABLE_TEST  (false, float*, float(&&)[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, float*, float(&&)[]);
HAMON_IS_ASSIGNABLE_TEST  (false, float*, float(*)[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, float*, float(*)[]);
HAMON_IS_ASSIGNABLE_TEST  (false, float*, int*);
HAMON_IS_ASSIGNABLE_TEST  (false, float*, bool*);
HAMON_IS_ASSIGNABLE_TEST  (false, float*, enum_class_UDT*);
HAMON_IS_ASSIGNABLE_TEST  (false, float*, enum_UDT*);
HAMON_IS_ASSIGNABLE_TEST  (false, float*, void);
HAMON_IS_ASSIGNABLE_TEST  (false, float*, void*);
HAMON_IS_ASSIGNABLE_TEST  (false, float*, std::nullptr_t);
HAMON_IS_ASSIGNABLE_TEST    (false, float*&, float);
HAMON_IS_ASSIGNABLE_TEST    (false, float*&, float&);
HAMON_IS_ASSIGNABLE_TEST    (false, float*&, float&&);
HAMON_IS_ASSIGNABLE_TEST_PTR(true,  float*&, float*);
HAMON_IS_ASSIGNABLE_TEST_PTR(true,  float*&, float[2]);			//
HAMON_IS_ASSIGNABLE_TEST_PTR(true,  float*&, float[]);			//
HAMON_IS_ASSIGNABLE_TEST_PTR(true,  float*&, float(&)[2]);		//
HAMON_IS_ASSIGNABLE_TEST_PTR(true,  float*&, float(&)[]);		//
HAMON_IS_ASSIGNABLE_TEST_PTR(true,  float*&, float(&&)[2]);		//
HAMON_IS_ASSIGNABLE_TEST_PTR(true,  float*&, float(&&)[]);		//
HAMON_IS_ASSIGNABLE_TEST    (false, float*&, float(*)[2]);
HAMON_IS_ASSIGNABLE_TEST    (false, float*&, float(*)[]);
HAMON_IS_ASSIGNABLE_TEST    (false, float*&, int*);
HAMON_IS_ASSIGNABLE_TEST    (false, float*&, bool*);
HAMON_IS_ASSIGNABLE_TEST    (false, float*&, enum_class_UDT*);
HAMON_IS_ASSIGNABLE_TEST    (false, float*&, enum_UDT*);
HAMON_IS_ASSIGNABLE_TEST    (false, float*&, void);
HAMON_IS_ASSIGNABLE_TEST    (false, float*&, void*);
HAMON_IS_ASSIGNABLE_TEST_0  (true,  float*&, std::nullptr_t);

HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT, enum_class_UDT);
HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT, enum_class_UDT&);
HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT, enum_class_UDT&&);
HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT, enum_class_UDT*);
HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT, enum_class_UDT[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT, enum_class_UDT[]);
HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT, enum_class_UDT(&)[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT, enum_class_UDT(&)[]);
HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT, enum_class_UDT(&&)[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT, enum_class_UDT(&&)[]);
HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT, enum_class_UDT(*)[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT, enum_class_UDT(*)[]);
HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT, float);
HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT, bool);
HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT, int);
HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT, enum_UDT);
HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT, void);
HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT, std::nullptr_t);
HAMON_IS_ASSIGNABLE_TEST_2(true,  enum_class_UDT&, enum_class_UDT);
HAMON_IS_ASSIGNABLE_TEST_2(true,  enum_class_UDT&, enum_class_UDT&);
HAMON_IS_ASSIGNABLE_TEST_2(true,  enum_class_UDT&, enum_class_UDT&&);
HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT&, enum_class_UDT*);
HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT&, enum_class_UDT[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT&, enum_class_UDT[]);
HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT&, enum_class_UDT(&)[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT&, enum_class_UDT(&)[]);
HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT&, enum_class_UDT(&&)[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT&, enum_class_UDT(&&)[]);
HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT&, enum_class_UDT(*)[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT&, enum_class_UDT(*)[]);
HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT&, float);
HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT&, bool);
HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT&, int);
HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT&, enum_UDT);
HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT&, void);
HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT&, std::nullptr_t);
HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT&&, enum_class_UDT);
HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT&&, enum_class_UDT&);
HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT&&, enum_class_UDT&&);
HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT&&, enum_class_UDT*);
HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT&&, enum_class_UDT[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT&&, enum_class_UDT[]);
HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT&&, enum_class_UDT(&)[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT&&, enum_class_UDT(&)[]);
HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT&&, enum_class_UDT(&&)[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT&&, enum_class_UDT(&&)[]);
HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT&&, enum_class_UDT(*)[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT&&, enum_class_UDT(*)[]);
HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT&&, float);
HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT&&, bool);
HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT&&, int);
HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT&&, enum_UDT);
HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT&&, void);
HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT&&, std::nullptr_t);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT[2], enum_class_UDT);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT[2], enum_class_UDT&);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT[2], enum_class_UDT&&);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT[2], enum_class_UDT*);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT[2], enum_class_UDT[2]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT[2], enum_class_UDT[]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT[2], enum_class_UDT(&)[2]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT[2], enum_class_UDT(&)[]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT[2], enum_class_UDT(&&)[2]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT[2], enum_class_UDT(&&)[]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT[2], enum_class_UDT(*)[2]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT[2], enum_class_UDT(*)[]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT[2], float);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT[2], bool);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT[2], int);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT[2], enum_UDT);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT[2], void);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT[2], std::nullptr_t);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT[], enum_class_UDT);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT[], enum_class_UDT&);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT[], enum_class_UDT&&);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT[], enum_class_UDT*);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT[], enum_class_UDT[2]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT[], enum_class_UDT[]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT[], enum_class_UDT(&)[2]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT[], enum_class_UDT(&)[]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT[], enum_class_UDT(&&)[2]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT[], enum_class_UDT(&&)[]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT[], enum_class_UDT(*)[2]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT[], enum_class_UDT(*)[]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT[], float);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT[], bool);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT[], int);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT[], enum_UDT);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT[], void);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT[], std::nullptr_t);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&)[2], enum_class_UDT);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&)[2], enum_class_UDT&);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&)[2], enum_class_UDT&&);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&)[2], enum_class_UDT*);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&)[2], enum_class_UDT[2]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&)[2], enum_class_UDT[]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&)[2], enum_class_UDT(&)[2]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&)[2], enum_class_UDT(&)[]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&)[2], enum_class_UDT(&&)[2]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&)[2], enum_class_UDT(&&)[]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&)[2], enum_class_UDT(*)[2]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&)[2], enum_class_UDT(*)[]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&)[2], float);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&)[2], bool);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&)[2], int);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&)[2], enum_UDT);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&)[2], void);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&)[2], std::nullptr_t);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&)[], enum_class_UDT);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&)[], enum_class_UDT&);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&)[], enum_class_UDT&&);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&)[], enum_class_UDT*);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&)[], enum_class_UDT[2]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&)[], enum_class_UDT[]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&)[], enum_class_UDT(&)[2]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&)[], enum_class_UDT(&)[]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&)[], enum_class_UDT(&&)[2]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&)[], enum_class_UDT(&&)[]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&)[], enum_class_UDT(*)[2]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&)[], enum_class_UDT(*)[]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&)[], float);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&)[], bool);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&)[], int);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&)[], enum_UDT);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&)[], void);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&)[], std::nullptr_t);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&&)[2], enum_class_UDT);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&&)[2], enum_class_UDT&);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&&)[2], enum_class_UDT&&);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&&)[2], enum_class_UDT*);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&&)[2], enum_class_UDT[2]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&&)[2], enum_class_UDT[]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&&)[2], enum_class_UDT(&)[2]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&&)[2], enum_class_UDT(&)[]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&&)[2], enum_class_UDT(&&)[2]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&&)[2], enum_class_UDT(&&)[]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&&)[2], enum_class_UDT(*)[2]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&&)[2], enum_class_UDT(*)[]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&&)[2], float);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&&)[2], bool);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&&)[2], int);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&&)[2], enum_UDT);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&&)[2], void);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&&)[2], std::nullptr_t);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&&)[], enum_class_UDT);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&&)[], enum_class_UDT&);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&&)[], enum_class_UDT&&);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&&)[], enum_class_UDT*);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&&)[], enum_class_UDT[2]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&&)[], enum_class_UDT[]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&&)[], enum_class_UDT(&)[2]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&&)[], enum_class_UDT(&)[]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&&)[], enum_class_UDT(&&)[2]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&&)[], enum_class_UDT(&&)[]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&&)[], enum_class_UDT(*)[2]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&&)[], enum_class_UDT(*)[]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&&)[], float);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&&)[], bool);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&&)[], enum_class_UDT);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&&)[], enum_UDT);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&&)[], void);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&&)[], std::nullptr_t);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(*)[2], enum_class_UDT);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(*)[2], enum_class_UDT&);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(*)[2], enum_class_UDT&&);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(*)[2], enum_class_UDT*);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(*)[2], enum_class_UDT[2]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(*)[2], enum_class_UDT[]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(*)[2], enum_class_UDT(&)[2]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(*)[2], enum_class_UDT(&)[]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(*)[2], enum_class_UDT(&&)[2]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(*)[2], enum_class_UDT(&&)[]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(*)[2], enum_class_UDT(*)[2]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(*)[2], enum_class_UDT(*)[]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(*)[2], float);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(*)[2], bool);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(*)[2], int);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(*)[2], enum_UDT);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(*)[2], void);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(*)[2], std::nullptr_t);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(*)[], enum_class_UDT);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(*)[], enum_class_UDT&);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(*)[], enum_class_UDT&&);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(*)[], enum_class_UDT*);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(*)[], enum_class_UDT[2]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(*)[], enum_class_UDT[]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(*)[], enum_class_UDT(&)[2]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(*)[], enum_class_UDT(&)[]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(*)[], enum_class_UDT(&&)[2]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(*)[], enum_class_UDT(&&)[]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(*)[], enum_class_UDT(*)[2]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(*)[], enum_class_UDT(*)[]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(*)[], float);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(*)[], bool);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(*)[], int);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(*)[], enum_UDT);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(*)[], void);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(*)[], std::nullptr_t);
HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT*, enum_class_UDT);
HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT*, enum_class_UDT&);
HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT*, enum_class_UDT&&);
HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT*, enum_class_UDT*);
HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT*, enum_class_UDT[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT*, enum_class_UDT[]);
HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT*, enum_class_UDT(&)[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT*, enum_class_UDT(&)[]);
HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT*, enum_class_UDT(&&)[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT*, enum_class_UDT(&&)[]);
HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT*, enum_class_UDT(*)[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT*, enum_class_UDT(*)[]);
HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT*, float*);
HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT*, bool*);
HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT*, int*);
HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT*, enum_UDT*);
HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT*, void);
HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT*, void*);
HAMON_IS_ASSIGNABLE_TEST  (false, enum_class_UDT*, std::nullptr_t);
HAMON_IS_ASSIGNABLE_TEST    (false, enum_class_UDT*&, enum_class_UDT);
HAMON_IS_ASSIGNABLE_TEST    (false, enum_class_UDT*&, enum_class_UDT&);
HAMON_IS_ASSIGNABLE_TEST    (false, enum_class_UDT*&, enum_class_UDT&&);
HAMON_IS_ASSIGNABLE_TEST_PTR(true,  enum_class_UDT*&, enum_class_UDT*);
HAMON_IS_ASSIGNABLE_TEST_PTR(true,  enum_class_UDT*&, enum_class_UDT[2]);			//
HAMON_IS_ASSIGNABLE_TEST_PTR(true,  enum_class_UDT*&, enum_class_UDT[]);			//
HAMON_IS_ASSIGNABLE_TEST_PTR(true,  enum_class_UDT*&, enum_class_UDT(&)[2]);		//
HAMON_IS_ASSIGNABLE_TEST_PTR(true,  enum_class_UDT*&, enum_class_UDT(&)[]);			//
HAMON_IS_ASSIGNABLE_TEST_PTR(true,  enum_class_UDT*&, enum_class_UDT(&&)[2]);		//
HAMON_IS_ASSIGNABLE_TEST_PTR(true,  enum_class_UDT*&, enum_class_UDT(&&)[]);		//
HAMON_IS_ASSIGNABLE_TEST    (false, enum_class_UDT*&, enum_class_UDT(*)[2]);
HAMON_IS_ASSIGNABLE_TEST    (false, enum_class_UDT*&, enum_class_UDT(*)[]);
HAMON_IS_ASSIGNABLE_TEST    (false, enum_class_UDT*&, float*);
HAMON_IS_ASSIGNABLE_TEST    (false, enum_class_UDT*&, bool*);
HAMON_IS_ASSIGNABLE_TEST    (false, enum_class_UDT*&, int*);
HAMON_IS_ASSIGNABLE_TEST    (false, enum_class_UDT*&, enum_UDT*);
HAMON_IS_ASSIGNABLE_TEST    (false, enum_class_UDT*&, void);
HAMON_IS_ASSIGNABLE_TEST    (false, enum_class_UDT*&, void*);
HAMON_IS_ASSIGNABLE_TEST_0  (true,  enum_class_UDT*&, std::nullptr_t);

HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT, enum_UDT);
HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT, enum_UDT&);
HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT, enum_UDT&&);
HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT, enum_UDT*);
HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT, enum_UDT[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT, enum_UDT[]);
HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT, enum_UDT(&)[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT, enum_UDT(&)[]);
HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT, enum_UDT(&&)[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT, enum_UDT(&&)[]);
HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT, enum_UDT(*)[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT, enum_UDT(*)[]);
HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT, float);
HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT, bool);
HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT, int);
HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT, enum_class_UDT);
HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT, void);
HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT, std::nullptr_t);
HAMON_IS_ASSIGNABLE_TEST_2(true,  enum_UDT&, enum_UDT);
HAMON_IS_ASSIGNABLE_TEST_2(true,  enum_UDT&, enum_UDT&);
HAMON_IS_ASSIGNABLE_TEST_2(true,  enum_UDT&, enum_UDT&&);
HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT&, enum_UDT*);
HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT&, enum_UDT[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT&, enum_UDT[]);
HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT&, enum_UDT(&)[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT&, enum_UDT(&)[]);
HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT&, enum_UDT(&&)[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT&, enum_UDT(&&)[]);
HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT&, enum_UDT(*)[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT&, enum_UDT(*)[]);
HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT&, float);
HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT&, bool);
HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT&, int);
HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT&, enum_class_UDT);
HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT&, void);
HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT&, std::nullptr_t);
HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT&&, enum_UDT);
HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT&&, enum_UDT&);
HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT&&, enum_UDT&&);
HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT&&, enum_UDT*);
HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT&&, enum_UDT[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT&&, enum_UDT[]);
HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT&&, enum_UDT(&)[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT&&, enum_UDT(&)[]);
HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT&&, enum_UDT(&&)[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT&&, enum_UDT(&&)[]);
HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT&&, enum_UDT(*)[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT&&, enum_UDT(*)[]);
HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT&&, float);
HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT&&, bool);
HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT&&, int);
HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT&&, enum_class_UDT);
HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT&&, void);
HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT&&, std::nullptr_t);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT[2], enum_UDT);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT[2], enum_UDT&);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT[2], enum_UDT&&);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT[2], enum_UDT*);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT[2], enum_UDT[2]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT[2], enum_UDT[]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT[2], enum_UDT(&)[2]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT[2], enum_UDT(&)[]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT[2], enum_UDT(&&)[2]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT[2], enum_UDT(&&)[]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT[2], enum_UDT(*)[2]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT[2], enum_UDT(*)[]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT[2], float);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT[2], bool);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT[2], int);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT[2], enum_class_UDT);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT[2], void);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT[2], std::nullptr_t);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT[], enum_UDT);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT[], enum_UDT&);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT[], enum_UDT&&);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT[], enum_UDT*);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT[], enum_UDT[2]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT[], enum_UDT[]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT[], enum_UDT(&)[2]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT[], enum_UDT(&)[]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT[], enum_UDT(&&)[2]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT[], enum_UDT(&&)[]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT[], enum_UDT(*)[2]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT[], enum_UDT(*)[]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT[], float);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT[], bool);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT[], int);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT[], enum_class_UDT);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT[], void);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT[], std::nullptr_t);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT(&)[2], enum_UDT);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT(&)[2], enum_UDT&);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT(&)[2], enum_UDT&&);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT(&)[2], enum_UDT*);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT(&)[2], enum_UDT[2]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT(&)[2], enum_UDT[]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT(&)[2], enum_UDT(&)[2]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT(&)[2], enum_UDT(&)[]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT(&)[2], enum_UDT(&&)[2]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT(&)[2], enum_UDT(&&)[]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT(&)[2], enum_UDT(*)[2]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT(&)[2], enum_UDT(*)[]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT(&)[2], float);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT(&)[2], bool);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT(&)[2], int);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT(&)[2], enum_class_UDT);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT(&)[2], void);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT(&)[2], std::nullptr_t);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT(&)[], enum_UDT);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT(&)[], enum_UDT&);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT(&)[], enum_UDT&&);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT(&)[], enum_UDT*);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT(&)[], enum_UDT[2]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT(&)[], enum_UDT[]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT(&)[], enum_UDT(&)[2]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT(&)[], enum_UDT(&)[]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT(&)[], enum_UDT(&&)[2]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT(&)[], enum_UDT(&&)[]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT(&)[], enum_UDT(*)[2]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT(&)[], enum_UDT(*)[]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT(&)[], float);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT(&)[], bool);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT(&)[], int);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT(&)[], enum_class_UDT);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT(&)[], void);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT(&)[], std::nullptr_t);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT(&&)[2], enum_UDT);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT(&&)[2], enum_UDT&);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT(&&)[2], enum_UDT&&);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT(&&)[2], enum_UDT*);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT(&&)[2], enum_UDT[2]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT(&&)[2], enum_UDT[]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT(&&)[2], enum_UDT(&)[2]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT(&&)[2], enum_UDT(&)[]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT(&&)[2], enum_UDT(&&)[2]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT(&&)[2], enum_UDT(&&)[]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT(&&)[2], enum_UDT(*)[2]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT(&&)[2], enum_UDT(*)[]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT(&&)[2], float);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT(&&)[2], bool);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT(&&)[2], int);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT(&&)[2], enum_class_UDT);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT(&&)[2], void);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT(&&)[2], std::nullptr_t);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT(&&)[], enum_UDT);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT(&&)[], enum_UDT&);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT(&&)[], enum_UDT&&);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT(&&)[], enum_UDT*);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT(&&)[], enum_UDT[2]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT(&&)[], enum_UDT[]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT(&&)[], enum_UDT(&)[2]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT(&&)[], enum_UDT(&)[]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT(&&)[], enum_UDT(&&)[2]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT(&&)[], enum_UDT(&&)[]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT(&&)[], enum_UDT(*)[2]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT(&&)[], enum_UDT(*)[]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT(&&)[], float);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT(&&)[], bool);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT(&&)[], enum_class_UDT);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT(&&)[], void);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT(&&)[], std::nullptr_t);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT(*)[2], enum_UDT);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT(*)[2], enum_UDT&);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT(*)[2], enum_UDT&&);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT(*)[2], enum_UDT*);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT(*)[2], enum_UDT[2]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT(*)[2], enum_UDT[]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT(*)[2], enum_UDT(&)[2]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT(*)[2], enum_UDT(&)[]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT(*)[2], enum_UDT(&&)[2]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT(*)[2], enum_UDT(&&)[]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT(*)[2], enum_UDT(*)[2]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT(*)[2], enum_UDT(*)[]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT(*)[2], float);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT(*)[2], bool);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT(*)[2], int);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT(*)[2], enum_class_UDT);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT(*)[2], void);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT(*)[2], std::nullptr_t);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT(*)[], enum_UDT);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT(*)[], enum_UDT&);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT(*)[], enum_UDT&&);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT(*)[], enum_UDT*);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT(*)[], enum_UDT[2]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT(*)[], enum_UDT[]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT(*)[], enum_UDT(&)[2]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT(*)[], enum_UDT(&)[]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT(*)[], enum_UDT(&&)[2]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT(*)[], enum_UDT(&&)[]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT(*)[], enum_UDT(*)[2]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT(*)[], enum_UDT(*)[]);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT(*)[], float);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT(*)[], bool);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT(*)[], int);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT(*)[], enum_class_UDT);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT(*)[], void);
//	HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT(*)[], std::nullptr_t);
HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT*, enum_UDT);
HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT*, enum_UDT&);
HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT*, enum_UDT&&);
HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT*, enum_UDT*);
HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT*, enum_UDT[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT*, enum_UDT[]);
HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT*, enum_UDT(&)[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT*, enum_UDT(&)[]);
HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT*, enum_UDT(&&)[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT*, enum_UDT(&&)[]);
HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT*, enum_UDT(*)[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT*, enum_UDT(*)[]);
HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT*, float*);
HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT*, bool*);
HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT*, int*);
HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT*, enum_class_UDT*);
HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT*, void);
HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT*, void*);
HAMON_IS_ASSIGNABLE_TEST  (false, enum_UDT*, std::nullptr_t);
HAMON_IS_ASSIGNABLE_TEST    (false, enum_UDT*&, enum_UDT);
HAMON_IS_ASSIGNABLE_TEST    (false, enum_UDT*&, enum_UDT&);
HAMON_IS_ASSIGNABLE_TEST    (false, enum_UDT*&, enum_UDT&&);
HAMON_IS_ASSIGNABLE_TEST_PTR(true,  enum_UDT*&, enum_UDT*);
HAMON_IS_ASSIGNABLE_TEST_PTR(true,  enum_UDT*&, enum_UDT[2]);			//
HAMON_IS_ASSIGNABLE_TEST_PTR(true,  enum_UDT*&, enum_UDT[]);			//
HAMON_IS_ASSIGNABLE_TEST_PTR(true,  enum_UDT*&, enum_UDT(&)[2]);		//
HAMON_IS_ASSIGNABLE_TEST_PTR(true,  enum_UDT*&, enum_UDT(&)[]);			//
HAMON_IS_ASSIGNABLE_TEST_PTR(true,  enum_UDT*&, enum_UDT(&&)[2]);		//
HAMON_IS_ASSIGNABLE_TEST_PTR(true,  enum_UDT*&, enum_UDT(&&)[]);		//
HAMON_IS_ASSIGNABLE_TEST    (false, enum_UDT*&, enum_UDT(*)[2]);
HAMON_IS_ASSIGNABLE_TEST    (false, enum_UDT*&, enum_UDT(*)[]);
HAMON_IS_ASSIGNABLE_TEST    (false, enum_UDT*&, float*);
HAMON_IS_ASSIGNABLE_TEST    (false, enum_UDT*&, bool*);
HAMON_IS_ASSIGNABLE_TEST    (false, enum_UDT*&, int*);
HAMON_IS_ASSIGNABLE_TEST    (false, enum_UDT*&, enum_class_UDT*);
HAMON_IS_ASSIGNABLE_TEST    (false, enum_UDT*&, void);
HAMON_IS_ASSIGNABLE_TEST    (false, enum_UDT*&, void*);
HAMON_IS_ASSIGNABLE_TEST_0  (true,  enum_UDT*&, std::nullptr_t);

HAMON_IS_ASSIGNABLE_TEST(false, void*, int);
HAMON_IS_ASSIGNABLE_TEST(false, void*, int&);
HAMON_IS_ASSIGNABLE_TEST(false, void*, int&&);
HAMON_IS_ASSIGNABLE_TEST(false, void*, int*);
HAMON_IS_ASSIGNABLE_TEST(false, void*, int[2]);
HAMON_IS_ASSIGNABLE_TEST(false, void*, int[]);
HAMON_IS_ASSIGNABLE_TEST(false, void*, int(&)[2]);
HAMON_IS_ASSIGNABLE_TEST(false, void*, int(&)[]);
HAMON_IS_ASSIGNABLE_TEST(false, void*, int(&&)[2]);
HAMON_IS_ASSIGNABLE_TEST(false, void*, int(&&)[]);
HAMON_IS_ASSIGNABLE_TEST(false, void*, int(*)[2]);
HAMON_IS_ASSIGNABLE_TEST(false, void*, int(*)[]);
HAMON_IS_ASSIGNABLE_TEST(false, void*, float*);
HAMON_IS_ASSIGNABLE_TEST(false, void*, bool*);
HAMON_IS_ASSIGNABLE_TEST(false, void*, enum_class_UDT*);
HAMON_IS_ASSIGNABLE_TEST(false, void*, enum_UDT*);
HAMON_IS_ASSIGNABLE_TEST(false, void*, void);
HAMON_IS_ASSIGNABLE_TEST(false, void*, void*);
HAMON_IS_ASSIGNABLE_TEST(false, void*, std::nullptr_t);
HAMON_IS_ASSIGNABLE_TEST    (false, void*&, int);
HAMON_IS_ASSIGNABLE_TEST    (false, void*&, int&);
HAMON_IS_ASSIGNABLE_TEST    (false, void*&, int&&);
HAMON_IS_ASSIGNABLE_TEST_PTR(true,  void*&, int*);
HAMON_IS_ASSIGNABLE_TEST_PTR(true,  void*&, int[2]);		//
HAMON_IS_ASSIGNABLE_TEST_PTR(true,  void*&, int[]);			//
HAMON_IS_ASSIGNABLE_TEST_PTR(true,  void*&, int(&)[2]);		//
HAMON_IS_ASSIGNABLE_TEST_PTR(true,  void*&, int(&)[]);		//
HAMON_IS_ASSIGNABLE_TEST_PTR(true,  void*&, int(&&)[2]);	//
HAMON_IS_ASSIGNABLE_TEST_PTR(true,  void*&, int(&&)[]);		//
HAMON_IS_ASSIGNABLE_TEST_PTR(true,  void*&, int(*)[2]);
HAMON_IS_ASSIGNABLE_TEST_PTR(true,  void*&, int(*)[]);
HAMON_IS_ASSIGNABLE_TEST_PTR(true,  void*&, float*);
HAMON_IS_ASSIGNABLE_TEST_PTR(true,  void*&, bool*);
HAMON_IS_ASSIGNABLE_TEST_PTR(true,  void*&, enum_class_UDT*);
HAMON_IS_ASSIGNABLE_TEST_PTR(true,  void*&, enum_UDT*);
HAMON_IS_ASSIGNABLE_TEST_PTR(false, void*&, void);
HAMON_IS_ASSIGNABLE_TEST_PTR(true,  void*&, void*);
HAMON_IS_ASSIGNABLE_TEST_0  (true,  void*&, std::nullptr_t);

HAMON_IS_ASSIGNABLE_TEST(false, void, void);
HAMON_IS_ASSIGNABLE_TEST(false, void, int);
HAMON_IS_ASSIGNABLE_TEST(false, void, void*);
HAMON_IS_ASSIGNABLE_TEST(false, void, std::nullptr_t);

HAMON_IS_ASSIGNABLE_TEST  (false, std::nullptr_t, std::nullptr_t);
HAMON_IS_ASSIGNABLE_TEST  (false, std::nullptr_t, std::nullptr_t&);
HAMON_IS_ASSIGNABLE_TEST  (false, std::nullptr_t, std::nullptr_t&&);
HAMON_IS_ASSIGNABLE_TEST  (false, std::nullptr_t, std::nullptr_t*);
HAMON_IS_ASSIGNABLE_TEST  (false, std::nullptr_t, std::nullptr_t[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, std::nullptr_t, std::nullptr_t[]);
HAMON_IS_ASSIGNABLE_TEST  (false, std::nullptr_t, std::nullptr_t(&)[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, std::nullptr_t, std::nullptr_t(&)[]);
HAMON_IS_ASSIGNABLE_TEST  (false, std::nullptr_t, std::nullptr_t(&&)[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, std::nullptr_t, std::nullptr_t(&&)[]);
HAMON_IS_ASSIGNABLE_TEST  (false, std::nullptr_t, std::nullptr_t(*)[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, std::nullptr_t, std::nullptr_t(*)[]);
HAMON_IS_ASSIGNABLE_TEST  (false, std::nullptr_t, float*);
HAMON_IS_ASSIGNABLE_TEST  (false, std::nullptr_t, bool*);
HAMON_IS_ASSIGNABLE_TEST  (false, std::nullptr_t, enum_class_UDT*);
HAMON_IS_ASSIGNABLE_TEST  (false, std::nullptr_t, enum_UDT*);
HAMON_IS_ASSIGNABLE_TEST  (false, std::nullptr_t, void);
HAMON_IS_ASSIGNABLE_TEST  (false, std::nullptr_t, void*);
HAMON_IS_ASSIGNABLE_TEST_2(true,  std::nullptr_t&, std::nullptr_t);
HAMON_IS_ASSIGNABLE_TEST_2(true,  std::nullptr_t&, std::nullptr_t&);
HAMON_IS_ASSIGNABLE_TEST_2(true,  std::nullptr_t&, std::nullptr_t&&);
HAMON_IS_ASSIGNABLE_TEST  (false, std::nullptr_t&, std::nullptr_t*);
HAMON_IS_ASSIGNABLE_TEST  (false, std::nullptr_t&, std::nullptr_t[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, std::nullptr_t&, std::nullptr_t[]);
HAMON_IS_ASSIGNABLE_TEST  (false, std::nullptr_t&, std::nullptr_t(&)[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, std::nullptr_t&, std::nullptr_t(&)[]);
HAMON_IS_ASSIGNABLE_TEST  (false, std::nullptr_t&, std::nullptr_t(&&)[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, std::nullptr_t&, std::nullptr_t(&&)[]);
HAMON_IS_ASSIGNABLE_TEST  (false, std::nullptr_t&, std::nullptr_t(*)[2]);
HAMON_IS_ASSIGNABLE_TEST  (false, std::nullptr_t&, std::nullptr_t(*)[]);
HAMON_IS_ASSIGNABLE_TEST  (false, std::nullptr_t&, float*);
HAMON_IS_ASSIGNABLE_TEST  (false, std::nullptr_t&, bool*);
HAMON_IS_ASSIGNABLE_TEST  (false, std::nullptr_t&, enum_class_UDT*);
HAMON_IS_ASSIGNABLE_TEST  (false, std::nullptr_t&, enum_UDT*);
HAMON_IS_ASSIGNABLE_TEST  (false, std::nullptr_t&, void);
HAMON_IS_ASSIGNABLE_TEST  (false, std::nullptr_t&, void*);

}	// namespace is_assignable_test

}	// namespace hamon_type_traits_test

#undef HAMON_IS_ASSIGNABLE_TEST
#undef HAMON_IS_ASSIGNABLE_TEST_0
#undef HAMON_IS_ASSIGNABLE_TEST_1
#undef HAMON_IS_ASSIGNABLE_TEST_2
#undef HAMON_IS_ASSIGNABLE_TEST_3
#undef HAMON_IS_ASSIGNABLE_TEST_PTR
