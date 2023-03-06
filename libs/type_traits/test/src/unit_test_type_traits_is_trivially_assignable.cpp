/**
 *	@file	unit_test_type_traits_is_trivially_assignable.cpp
 *
 *	@brief	is_trivially_assignable のテスト
 */

#include <hamon/type_traits/is_trivially_assignable.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "type_traits_test_utility.hpp"

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

#define HAMON_IS_TRIVIALLY_ASSIGNABLE_TEST(b, T, U)	\
	static_assert(hamon::is_trivially_assignable_v<T, U>      == b, #T ", " #U);	\
	static_assert(hamon::is_trivially_assignable<T, U>::value == b, #T ", " #U);	\
	static_assert(hamon::is_trivially_assignable<T, U>{}()    == b, #T ", " #U);	\
	static_assert(hamon::is_trivially_assignable<T, U>{}      == b, #T ", " #U)

#else

#define HAMON_IS_TRIVIALLY_ASSIGNABLE_TEST(b, T, U)	\
	static_assert(hamon::is_trivially_assignable<T, U>::value == b, #T ", " #U);	\
	static_assert(hamon::is_trivially_assignable<T, U>{}()    == b, #T ", " #U);	\
	static_assert(hamon::is_trivially_assignable<T, U>{}      == b, #T ", " #U)

#endif

namespace hamon_type_traits_test
{

namespace is_trivially_assignable_test
{

struct S1
{
};

struct S2
{
	S2& operator=(const S2&);
};

HAMON_IS_TRIVIALLY_ASSIGNABLE_TEST(false, int,			int);
HAMON_IS_TRIVIALLY_ASSIGNABLE_TEST(false, int&&,		int);
HAMON_IS_TRIVIALLY_ASSIGNABLE_TEST(false, int&&,		int&&);
HAMON_IS_TRIVIALLY_ASSIGNABLE_TEST(false, int*,			int);
HAMON_IS_TRIVIALLY_ASSIGNABLE_TEST(false, int*,			int*);
HAMON_IS_TRIVIALLY_ASSIGNABLE_TEST(false, int[2],		int);
HAMON_IS_TRIVIALLY_ASSIGNABLE_TEST(false, int[2],		int[2]);
HAMON_IS_TRIVIALLY_ASSIGNABLE_TEST(false, int[],		int);
HAMON_IS_TRIVIALLY_ASSIGNABLE_TEST(false, int[],		int[]);
HAMON_IS_TRIVIALLY_ASSIGNABLE_TEST(false, int(&)[2],	int);
HAMON_IS_TRIVIALLY_ASSIGNABLE_TEST(false, int(&)[2],	int(&)[2]);
HAMON_IS_TRIVIALLY_ASSIGNABLE_TEST(false, int(&)[],	    int);
HAMON_IS_TRIVIALLY_ASSIGNABLE_TEST(false, int(&)[],	    int(&)[]);
HAMON_IS_TRIVIALLY_ASSIGNABLE_TEST(false, int(&&)[2],	int);
HAMON_IS_TRIVIALLY_ASSIGNABLE_TEST(false, int(&&)[2],	int(&&)[2]);
HAMON_IS_TRIVIALLY_ASSIGNABLE_TEST(false, int(&&)[],	int);
HAMON_IS_TRIVIALLY_ASSIGNABLE_TEST(false, int(&&)[],	int(&&)[]);
HAMON_IS_TRIVIALLY_ASSIGNABLE_TEST(true,                 int&,		int);
HAMON_IS_TRIVIALLY_ASSIGNABLE_TEST(false, const          int&,		int);
HAMON_IS_TRIVIALLY_ASSIGNABLE_TEST(true,        volatile int&,		int);
HAMON_IS_TRIVIALLY_ASSIGNABLE_TEST(false, const volatile int&,		int);
HAMON_IS_TRIVIALLY_ASSIGNABLE_TEST(true,                 int&,		int&);
HAMON_IS_TRIVIALLY_ASSIGNABLE_TEST(false, const          int&,		int&);
HAMON_IS_TRIVIALLY_ASSIGNABLE_TEST(true,        volatile int&,		int&);
HAMON_IS_TRIVIALLY_ASSIGNABLE_TEST(false, const volatile int&,		int&);
HAMON_IS_TRIVIALLY_ASSIGNABLE_TEST(true,                 int&,		int&&);
HAMON_IS_TRIVIALLY_ASSIGNABLE_TEST(false, const          int&,		int&&);
HAMON_IS_TRIVIALLY_ASSIGNABLE_TEST(true,        volatile int&,		int&&);
HAMON_IS_TRIVIALLY_ASSIGNABLE_TEST(false, const volatile int&,		int&&);
HAMON_IS_TRIVIALLY_ASSIGNABLE_TEST(false, int&, int*);
HAMON_IS_TRIVIALLY_ASSIGNABLE_TEST(false, int&, int[2]);
HAMON_IS_TRIVIALLY_ASSIGNABLE_TEST(true,  int&, enum_UDT);
HAMON_IS_TRIVIALLY_ASSIGNABLE_TEST(false, int&, enum_class_UDT);

HAMON_IS_TRIVIALLY_ASSIGNABLE_TEST(false,                void,                void);
HAMON_IS_TRIVIALLY_ASSIGNABLE_TEST(false, const          void, const          void);
HAMON_IS_TRIVIALLY_ASSIGNABLE_TEST(false,       volatile void,       volatile void);
HAMON_IS_TRIVIALLY_ASSIGNABLE_TEST(false, const volatile void, const volatile void);

HAMON_IS_TRIVIALLY_ASSIGNABLE_TEST(true,                 S1,                S1);
HAMON_IS_TRIVIALLY_ASSIGNABLE_TEST(false, const          S1,                S1);
HAMON_IS_TRIVIALLY_ASSIGNABLE_TEST(false,       volatile S1,                S1);
HAMON_IS_TRIVIALLY_ASSIGNABLE_TEST(false, const volatile S1,                S1);
HAMON_IS_TRIVIALLY_ASSIGNABLE_TEST(true,                 S1, const          S1);
HAMON_IS_TRIVIALLY_ASSIGNABLE_TEST(false, const          S1, const          S1);
HAMON_IS_TRIVIALLY_ASSIGNABLE_TEST(false,       volatile S1, const          S1);
HAMON_IS_TRIVIALLY_ASSIGNABLE_TEST(false, const volatile S1, const          S1);
HAMON_IS_TRIVIALLY_ASSIGNABLE_TEST(false,                S1,       volatile S1);
HAMON_IS_TRIVIALLY_ASSIGNABLE_TEST(false, const          S1,       volatile S1);
HAMON_IS_TRIVIALLY_ASSIGNABLE_TEST(false,       volatile S1,       volatile S1);
HAMON_IS_TRIVIALLY_ASSIGNABLE_TEST(false, const volatile S1,       volatile S1);
HAMON_IS_TRIVIALLY_ASSIGNABLE_TEST(false,                S1, const volatile S1);
HAMON_IS_TRIVIALLY_ASSIGNABLE_TEST(false, const          S1, const volatile S1);
HAMON_IS_TRIVIALLY_ASSIGNABLE_TEST(false,       volatile S1, const volatile S1);
HAMON_IS_TRIVIALLY_ASSIGNABLE_TEST(false, const volatile S1, const volatile S1);
HAMON_IS_TRIVIALLY_ASSIGNABLE_TEST(true,  S1&,  S1);
HAMON_IS_TRIVIALLY_ASSIGNABLE_TEST(true,  S1&&, S1);
HAMON_IS_TRIVIALLY_ASSIGNABLE_TEST(false, S1[2], S1[2]);
HAMON_IS_TRIVIALLY_ASSIGNABLE_TEST(false, S1,   int);

HAMON_IS_TRIVIALLY_ASSIGNABLE_TEST(false, S2,   S2);
HAMON_IS_TRIVIALLY_ASSIGNABLE_TEST(false, S2&,  S2);
HAMON_IS_TRIVIALLY_ASSIGNABLE_TEST(false, S2&&, S2);
HAMON_IS_TRIVIALLY_ASSIGNABLE_TEST(false, S2,   int);

HAMON_IS_TRIVIALLY_ASSIGNABLE_TEST(true,  trivial_except_construct,		trivial_except_construct);
HAMON_IS_TRIVIALLY_ASSIGNABLE_TEST(true,  trivial_except_destroy,		trivial_except_destroy);
HAMON_IS_TRIVIALLY_ASSIGNABLE_TEST(true,  trivial_except_copy_ctor,		trivial_except_copy_ctor);
HAMON_IS_TRIVIALLY_ASSIGNABLE_TEST(false, trivial_except_copy_assign,	trivial_except_copy_assign);
HAMON_IS_TRIVIALLY_ASSIGNABLE_TEST(false, trivial_except_move_ctor,		trivial_except_move_ctor);
HAMON_IS_TRIVIALLY_ASSIGNABLE_TEST(false, trivial_except_move_assign,	trivial_except_move_assign);
HAMON_IS_TRIVIALLY_ASSIGNABLE_TEST(false, trivial_except_move_assign,	trivial_except_move_assign&);
HAMON_IS_TRIVIALLY_ASSIGNABLE_TEST(false, trivial_except_move_assign,	const trivial_except_move_assign);
HAMON_IS_TRIVIALLY_ASSIGNABLE_TEST(false, trivial_except_move_assign,	const trivial_except_move_assign&);
HAMON_IS_TRIVIALLY_ASSIGNABLE_TEST(false, trivial_except_move_assign,	const trivial_except_move_assign&&);
HAMON_IS_TRIVIALLY_ASSIGNABLE_TEST(false, trivial_except_move_assign&,	trivial_except_move_assign&);
HAMON_IS_TRIVIALLY_ASSIGNABLE_TEST(false, trivial_except_move_assign&,	const trivial_except_move_assign);
HAMON_IS_TRIVIALLY_ASSIGNABLE_TEST(false, trivial_except_move_assign&,	const trivial_except_move_assign&);
HAMON_IS_TRIVIALLY_ASSIGNABLE_TEST(false, trivial_except_move_assign&,	const trivial_except_move_assign&&);
HAMON_IS_TRIVIALLY_ASSIGNABLE_TEST(false, trivial_except_move_assign&&,	trivial_except_move_assign&);
HAMON_IS_TRIVIALLY_ASSIGNABLE_TEST(false, trivial_except_move_assign&&,	const trivial_except_move_assign);
HAMON_IS_TRIVIALLY_ASSIGNABLE_TEST(false, trivial_except_move_assign&&,	const trivial_except_move_assign&);
HAMON_IS_TRIVIALLY_ASSIGNABLE_TEST(false, trivial_except_move_assign&&,	const trivial_except_move_assign&&);

}	// namespace is_trivially_assignable_test

}	// namespace hamon_type_traits_test

#undef HAMON_IS_TRIVIALLY_ASSIGNABLE_TEST
