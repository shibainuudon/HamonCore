/**
 *	@file	unit_test_type_traits_is_trivially_constructible.cpp
 *
 *	@brief	is_trivially_constructible のテスト
 */

#include <hamon/type_traits/is_trivially_constructible.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include <string>
#include "type_traits_test_utility.hpp"

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

#define HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(b, ...)	\
	static_assert(hamon::is_trivially_constructible_v<__VA_ARGS__>      == b, "");	\
	static_assert(hamon::is_trivially_constructible<__VA_ARGS__>::value == b, "");	\
	static_assert(hamon::is_trivially_constructible<__VA_ARGS__>{}()    == b, "");	\
	static_assert(hamon::is_trivially_constructible<__VA_ARGS__>{}      == b, "")

#else

#define HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(b, ...)	\
	static_assert(hamon::is_trivially_constructible<__VA_ARGS__>::value == b, "");	\
	static_assert(hamon::is_trivially_constructible<__VA_ARGS__>{}()    == b, "");	\
	static_assert(hamon::is_trivially_constructible<__VA_ARGS__>{}      == b, "")

#endif

namespace hamon_type_traits_test
{

namespace is_trivially_constructible_test
{

#if !(defined(HAMON_GCC_VERSION) && (HAMON_GCC_VERSION == 80100))	// gcc 8.1.0ではis_trivially_constructibleが正しくない

HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(true,  int);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(true,  int, int);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, int, int, int);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, int, std::string);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, int&, int);

HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, trivial_except_construct);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, trivial_except_destroy);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, trivial_except_copy_ctor);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(true,  trivial_except_copy_assign);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, trivial_except_move_ctor);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(true,  trivial_except_move_assign);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(true,  trivial_except_construct,		trivial_except_construct);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, trivial_except_destroy,		trivial_except_destroy);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, trivial_except_copy_ctor,		trivial_except_copy_ctor);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(true,  trivial_except_copy_assign,	trivial_except_copy_assign);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, trivial_except_move_ctor,		trivial_except_move_ctor);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, trivial_except_move_assign,	trivial_except_move_assign);
	
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(true,                 int);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(true,  const          int);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(true,        volatile int);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(true,  const volatile int);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(true,  int*);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, int&);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, int&&);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(true,  int[2]);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, int[]);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, int(&)[2]);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, int(&)[]);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, int(&&)[2]);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, int(&&)[]);

HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(true,  int,        int);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, int,        int*);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(true,  int,        int&);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(true,  int,        int&&);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, int,        int[2]);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, int,        int[]);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, int,        int(&)[2]);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, int,        int(&)[]);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, int,        int(&&)[2]);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, int,        int(&&)[]);

HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, int*,       int);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(true,                 int*,                int*);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(true,  const          int*,                int*);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(true,        volatile int*,                int*);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(true,  const volatile int*,                int*);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false,                int*, const          int*);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(true,  const          int*, const          int*);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false,       volatile int*, const          int*);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(true,  const volatile int*, const          int*);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false,                int*,       volatile int*);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, const          int*,       volatile int*);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(true,        volatile int*,       volatile int*);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(true,  const volatile int*,       volatile int*);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false,                int*, const volatile int*);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, const          int*, const volatile int*);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false,       volatile int*, const volatile int*);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(true,  const volatile int*, const volatile int*);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, int*,       int&);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, int*,       int&&);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(true,  int*,       int[2]);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(true,  int*,       int[]);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(true,  int*,       int(&)[2]);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(true,  int*,       int(&)[]);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(true,  int*,       int(&&)[2]);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(true,  int*,       int(&&)[]);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false,                int&, int);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(true,  const          int&, int);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false,       volatile int&, int);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, const volatile int&, int);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false,                int&, int*);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, const          int&, int*);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false,       volatile int&, int*);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, const volatile int&, int*);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(true,                 int&,                int&);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(true,  const          int&,                int&);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(true,        volatile int&,                int&);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(true,  const volatile int&,                int&);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false,                int&, const          int&);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(true,  const          int&, const          int&);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false,       volatile int&, const          int&);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(true,  const volatile int&, const          int&);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false,                int&,       volatile int&);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, const          int&,       volatile int&);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(true,        volatile int&,       volatile int&);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(true,  const volatile int&,       volatile int&);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false,                int&, const volatile int&);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, const          int&, const volatile int&);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false,       volatile int&, const volatile int&);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(true,  const volatile int&, const volatile int&);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false,                int&,                int&&);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(true,  const          int&,                int&&);	// const参照だけ特別
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false,       volatile int&,                int&&);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, const volatile int&,                int&&);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false,                int&, const          int&&);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(true,  const          int&, const          int&&);	// const参照だけ特別
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false,       volatile int&, const          int&&);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, const volatile int&, const          int&&);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false,                int&,       volatile int&&);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, const          int&,       volatile int&&);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false,       volatile int&,       volatile int&&);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, const volatile int&,       volatile int&&);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false,                int&, const volatile int&&);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, const          int&, const volatile int&&);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false,       volatile int&, const volatile int&&);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, const volatile int&, const volatile int&&);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, int&,       int[2]);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, int&,       int[]);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, int&,       int(&)[2]);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, int&,       int(&)[]);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, int&,       int(&&)[2]);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, int&,       int(&&)[]);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(true,  int&&,      int);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, int&&,      int*);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, int&&,      int&);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(true,  int&&,      int&&);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, int&&,      int[2]);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, int&&,      int[]);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, int&&,      int(&)[2]);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, int&&,      int(&)[]);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, int&&,      int(&&)[2]);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, int&&,      int(&&)[]);

HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, int, UDT);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, int, int, int);

HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false,                 UDT);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false,  const          UDT);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false,        volatile UDT);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false,  const volatile UDT);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(true,  UDT*);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, UDT&);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, UDT&&);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, UDT[2]);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, UDT[]);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, UDT(&)[2]);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, UDT(&)[]);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, UDT(&&)[2]);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, UDT(&&)[]);

HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(true,                 POD_UDT);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(true,  const          POD_UDT);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(true,        volatile POD_UDT);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(true,  const volatile POD_UDT);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(true,  POD_UDT*);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, POD_UDT&);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, POD_UDT&&);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(true,  POD_UDT[2]);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, POD_UDT[]);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, POD_UDT(&)[2]);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, POD_UDT(&)[]);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, POD_UDT(&&)[2]);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, POD_UDT(&&)[]);

HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, foo0_t);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, foo1_t);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, foo2_t);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, foo3_t);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, foo4_t);

HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, UDT,		UDT);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(true,  POD_UDT,	POD_UDT);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, foo0_t,	foo0_t);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, foo1_t,	foo1_t);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, foo2_t,	foo2_t);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, foo3_t,	foo3_t);
HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, foo4_t,	foo4_t);

#endif

}	// namespace is_trivially_constructible_test

}	// namespace hamon_type_traits_test

#undef HAMON_IS_TRIVIALLY_CONSTRUCTIBLE_TEST
