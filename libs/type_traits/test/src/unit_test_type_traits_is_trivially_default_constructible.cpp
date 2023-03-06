/**
 *	@file	unit_test_type_traits_is_trivially_default_constructible.cpp
 *
 *	@brief	is_trivially_default_constructible のテスト
 */

#include <hamon/type_traits/is_trivially_default_constructible.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "type_traits_test_utility.hpp"

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

#define HAMON_IS_TRIVIALLY_DEFAULT_CONSTRUCTIBLE_TEST(b, T)	\
	static_assert(hamon::is_trivially_default_constructible_v<T>      == b, #T);	\
	static_assert(hamon::is_trivially_default_constructible<T>::value == b, #T);	\
	static_assert(hamon::is_trivially_default_constructible<T>{}()    == b, #T);	\
	static_assert(hamon::is_trivially_default_constructible<T>{}      == b, #T)

#else

#define HAMON_IS_TRIVIALLY_DEFAULT_CONSTRUCTIBLE_TEST(b, T)	\
	static_assert(hamon::is_trivially_default_constructible<T>::value == b, #T);	\
	static_assert(hamon::is_trivially_default_constructible<T>{}()    == b, #T);	\
	static_assert(hamon::is_trivially_default_constructible<T>{}      == b, #T)

#endif

namespace hamon_type_traits_test
{

namespace is_trivially_default_constructible_test
{

// トリビアルなdefaultコンストラクタを持つ
struct S1
{
	int n;
};

// 非トリビアルだが例外を投げないdefaultコンストラクタを持つ
struct S2
{
	S2() HAMON_NOEXCEPT_OR_NOTHROW;
};

// 非トリビアルだが例外を投げないdefaultコンストラクタを持つクラスをメンバに持つ
struct S3
{
	S2 member;
};

// defaultコンストラクタが例外を投げる
struct S4
{
	S4() {}
};

// defaultコンストラクタを持たない
struct S5
{
	S5(const S5&);
};

HAMON_IS_TRIVIALLY_DEFAULT_CONSTRUCTIBLE_TEST(true,  S1);
HAMON_IS_TRIVIALLY_DEFAULT_CONSTRUCTIBLE_TEST(false, S2);
HAMON_IS_TRIVIALLY_DEFAULT_CONSTRUCTIBLE_TEST(false, S3);
HAMON_IS_TRIVIALLY_DEFAULT_CONSTRUCTIBLE_TEST(false, S4);
HAMON_IS_TRIVIALLY_DEFAULT_CONSTRUCTIBLE_TEST(false, S5);

HAMON_IS_TRIVIALLY_DEFAULT_CONSTRUCTIBLE_TEST(true,                 int);
HAMON_IS_TRIVIALLY_DEFAULT_CONSTRUCTIBLE_TEST(true,  const          int);
HAMON_IS_TRIVIALLY_DEFAULT_CONSTRUCTIBLE_TEST(true,        volatile int);
HAMON_IS_TRIVIALLY_DEFAULT_CONSTRUCTIBLE_TEST(true,  const volatile int);
HAMON_IS_TRIVIALLY_DEFAULT_CONSTRUCTIBLE_TEST(true,  int*);
HAMON_IS_TRIVIALLY_DEFAULT_CONSTRUCTIBLE_TEST(false, int&);
HAMON_IS_TRIVIALLY_DEFAULT_CONSTRUCTIBLE_TEST(false, int&&);
HAMON_IS_TRIVIALLY_DEFAULT_CONSTRUCTIBLE_TEST(true,  int[2]);
HAMON_IS_TRIVIALLY_DEFAULT_CONSTRUCTIBLE_TEST(false, int[]);
HAMON_IS_TRIVIALLY_DEFAULT_CONSTRUCTIBLE_TEST(false, int(&)[2]);
HAMON_IS_TRIVIALLY_DEFAULT_CONSTRUCTIBLE_TEST(false, int(&)[]);
HAMON_IS_TRIVIALLY_DEFAULT_CONSTRUCTIBLE_TEST(false, int(&&)[2]);
HAMON_IS_TRIVIALLY_DEFAULT_CONSTRUCTIBLE_TEST(false, int(&&)[]);

HAMON_IS_TRIVIALLY_DEFAULT_CONSTRUCTIBLE_TEST(false,                void);
HAMON_IS_TRIVIALLY_DEFAULT_CONSTRUCTIBLE_TEST(false, const          void);
HAMON_IS_TRIVIALLY_DEFAULT_CONSTRUCTIBLE_TEST(false,       volatile void);
HAMON_IS_TRIVIALLY_DEFAULT_CONSTRUCTIBLE_TEST(false, const volatile void);

HAMON_IS_TRIVIALLY_DEFAULT_CONSTRUCTIBLE_TEST(false,                UDT);
HAMON_IS_TRIVIALLY_DEFAULT_CONSTRUCTIBLE_TEST(false, const          UDT);
HAMON_IS_TRIVIALLY_DEFAULT_CONSTRUCTIBLE_TEST(false,       volatile UDT);
HAMON_IS_TRIVIALLY_DEFAULT_CONSTRUCTIBLE_TEST(false, const volatile UDT);
HAMON_IS_TRIVIALLY_DEFAULT_CONSTRUCTIBLE_TEST(true,  UDT*);
HAMON_IS_TRIVIALLY_DEFAULT_CONSTRUCTIBLE_TEST(false, UDT&);
HAMON_IS_TRIVIALLY_DEFAULT_CONSTRUCTIBLE_TEST(false, UDT&&);
//	HAMON_IS_TRIVIALLY_DEFAULT_CONSTRUCTIBLE_TEST(false, UDT[2]);
HAMON_IS_TRIVIALLY_DEFAULT_CONSTRUCTIBLE_TEST(false, UDT[]);
HAMON_IS_TRIVIALLY_DEFAULT_CONSTRUCTIBLE_TEST(false, UDT(&)[2]);
HAMON_IS_TRIVIALLY_DEFAULT_CONSTRUCTIBLE_TEST(false, UDT(&)[]);
HAMON_IS_TRIVIALLY_DEFAULT_CONSTRUCTIBLE_TEST(false, UDT(&&)[2]);
HAMON_IS_TRIVIALLY_DEFAULT_CONSTRUCTIBLE_TEST(false, UDT(&&)[]);

HAMON_IS_TRIVIALLY_DEFAULT_CONSTRUCTIBLE_TEST(true,                 POD_UDT);
HAMON_IS_TRIVIALLY_DEFAULT_CONSTRUCTIBLE_TEST(true,  const          POD_UDT);
HAMON_IS_TRIVIALLY_DEFAULT_CONSTRUCTIBLE_TEST(true,        volatile POD_UDT);
HAMON_IS_TRIVIALLY_DEFAULT_CONSTRUCTIBLE_TEST(true,  const volatile POD_UDT);
HAMON_IS_TRIVIALLY_DEFAULT_CONSTRUCTIBLE_TEST(true,  POD_UDT*);
HAMON_IS_TRIVIALLY_DEFAULT_CONSTRUCTIBLE_TEST(false, POD_UDT&);
HAMON_IS_TRIVIALLY_DEFAULT_CONSTRUCTIBLE_TEST(false, POD_UDT&&);
HAMON_IS_TRIVIALLY_DEFAULT_CONSTRUCTIBLE_TEST(true,  POD_UDT[2]);
HAMON_IS_TRIVIALLY_DEFAULT_CONSTRUCTIBLE_TEST(false, POD_UDT[]);
HAMON_IS_TRIVIALLY_DEFAULT_CONSTRUCTIBLE_TEST(false, POD_UDT(&)[2]);
HAMON_IS_TRIVIALLY_DEFAULT_CONSTRUCTIBLE_TEST(false, POD_UDT(&)[]);
HAMON_IS_TRIVIALLY_DEFAULT_CONSTRUCTIBLE_TEST(false, POD_UDT(&&)[2]);
HAMON_IS_TRIVIALLY_DEFAULT_CONSTRUCTIBLE_TEST(false, POD_UDT(&&)[]);

HAMON_IS_TRIVIALLY_DEFAULT_CONSTRUCTIBLE_TEST(false, trivial_except_construct);
HAMON_IS_TRIVIALLY_DEFAULT_CONSTRUCTIBLE_TEST(false, trivial_except_destroy);
HAMON_IS_TRIVIALLY_DEFAULT_CONSTRUCTIBLE_TEST(false, trivial_except_copy_ctor);
HAMON_IS_TRIVIALLY_DEFAULT_CONSTRUCTIBLE_TEST(true,  trivial_except_copy_assign);
HAMON_IS_TRIVIALLY_DEFAULT_CONSTRUCTIBLE_TEST(false, trivial_except_move_ctor);
HAMON_IS_TRIVIALLY_DEFAULT_CONSTRUCTIBLE_TEST(true,  trivial_except_move_assign);

HAMON_IS_TRIVIALLY_DEFAULT_CONSTRUCTIBLE_TEST(true,  f1);
HAMON_IS_TRIVIALLY_DEFAULT_CONSTRUCTIBLE_TEST(true,  f2);
HAMON_IS_TRIVIALLY_DEFAULT_CONSTRUCTIBLE_TEST(true,  f3);
HAMON_IS_TRIVIALLY_DEFAULT_CONSTRUCTIBLE_TEST(true,  mf1);
HAMON_IS_TRIVIALLY_DEFAULT_CONSTRUCTIBLE_TEST(true,  mf2);
HAMON_IS_TRIVIALLY_DEFAULT_CONSTRUCTIBLE_TEST(true,  mf3);
HAMON_IS_TRIVIALLY_DEFAULT_CONSTRUCTIBLE_TEST(true,  mf4);
HAMON_IS_TRIVIALLY_DEFAULT_CONSTRUCTIBLE_TEST(true,  mp);
HAMON_IS_TRIVIALLY_DEFAULT_CONSTRUCTIBLE_TEST(true,  cmf);
HAMON_IS_TRIVIALLY_DEFAULT_CONSTRUCTIBLE_TEST(false, foo0_t);
HAMON_IS_TRIVIALLY_DEFAULT_CONSTRUCTIBLE_TEST(false, foo1_t);
HAMON_IS_TRIVIALLY_DEFAULT_CONSTRUCTIBLE_TEST(false, foo2_t);
HAMON_IS_TRIVIALLY_DEFAULT_CONSTRUCTIBLE_TEST(false, foo3_t);
HAMON_IS_TRIVIALLY_DEFAULT_CONSTRUCTIBLE_TEST(false, foo4_t);

}	// namespace is_trivially_default_constructible_test

}	// namespace hamon_type_traits_test

#undef HAMON_IS_TRIVIALLY_DEFAULT_CONSTRUCTIBLE_TEST
