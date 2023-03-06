/**
 *	@file	unit_test_type_traits_is_destructible.cpp
 *
 *	@brief	is_destructible のテスト
 */

#include <hamon/type_traits/is_destructible.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "type_traits_test_utility.hpp"

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

#define HAMON_IS_DESTRUCTIBLE_TEST(b, T)	\
	static_assert(hamon::is_destructible_v<T>      == b, #T);	\
	static_assert(hamon::is_destructible<T>::value == b, #T);	\
	static_assert(hamon::is_destructible<T>{}()    == b, #T);	\
	static_assert(hamon::is_destructible<T>{}      == b, #T)

#else

#define HAMON_IS_DESTRUCTIBLE_TEST(b, T)	\
	static_assert(hamon::is_destructible<T>::value == b, #T);	\
	static_assert(hamon::is_destructible<T>{}()    == b, #T);	\
	static_assert(hamon::is_destructible<T>{}      == b, #T)

#endif

namespace hamon_type_traits_test
{

namespace is_destructible_test
{

// トリビアルなデストラクタを持つ
struct S1
{
	int n;
};

// 非トリビアルだが例外を投げないデストラクタを持つ
struct S2
{
	~S2() HAMON_NOEXCEPT_OR_NOTHROW;
};

// 非トリビアルだが例外を投げないデストラクタを持つクラスをメンバに持つ
struct S3
{
	S2 member;
};

// デストラクタが例外を投げる
struct S4
{
	~S4() HAMON_NOEXCEPT_IF(false);
};

// デストラクタが例外を投げるクラスをメンバに持つ
struct S5
{
	S4 member;
};

// デストラクタを持たない
struct S6
{
	~S6() = delete;
};

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4624)	// 基底クラスのデストラクターへのアクセスまたはその削除ができないため、デストラクターを生成できませんでした

// デストラクタを持たないクラスをメンバに持つ
struct S7
{
	S6 member;
};

HAMON_WARNING_POP()

HAMON_IS_DESTRUCTIBLE_TEST(true,  S1);
HAMON_IS_DESTRUCTIBLE_TEST(true,  S2);
HAMON_IS_DESTRUCTIBLE_TEST(true,  S3);
HAMON_IS_DESTRUCTIBLE_TEST(true,  S4);
HAMON_IS_DESTRUCTIBLE_TEST(true,  S5);
HAMON_IS_DESTRUCTIBLE_TEST(false, S6);
HAMON_IS_DESTRUCTIBLE_TEST(false, S7);

HAMON_IS_DESTRUCTIBLE_TEST(true,                 int);
HAMON_IS_DESTRUCTIBLE_TEST(true,  const          int);
HAMON_IS_DESTRUCTIBLE_TEST(true,        volatile int);
HAMON_IS_DESTRUCTIBLE_TEST(true,  const volatile int);
HAMON_IS_DESTRUCTIBLE_TEST(true,  int*);
HAMON_IS_DESTRUCTIBLE_TEST(true,  int&);
HAMON_IS_DESTRUCTIBLE_TEST(true,  int&&);
HAMON_IS_DESTRUCTIBLE_TEST(true,  int[2]);
HAMON_IS_DESTRUCTIBLE_TEST(false, int[]);
HAMON_IS_DESTRUCTIBLE_TEST(true,  int(&)[2]);
HAMON_IS_DESTRUCTIBLE_TEST(true,  int(&)[]);
HAMON_IS_DESTRUCTIBLE_TEST(true,  int(&&)[2]);
HAMON_IS_DESTRUCTIBLE_TEST(true,  int(&&)[]);

HAMON_IS_DESTRUCTIBLE_TEST(false,                void);
HAMON_IS_DESTRUCTIBLE_TEST(false, const          void);
HAMON_IS_DESTRUCTIBLE_TEST(false,       volatile void);
HAMON_IS_DESTRUCTIBLE_TEST(false, const volatile void);

HAMON_IS_DESTRUCTIBLE_TEST(true,                 UDT);
HAMON_IS_DESTRUCTIBLE_TEST(true,  const          UDT);
HAMON_IS_DESTRUCTIBLE_TEST(true,        volatile UDT);
HAMON_IS_DESTRUCTIBLE_TEST(true,  const volatile UDT);
HAMON_IS_DESTRUCTIBLE_TEST(true,  UDT*);
HAMON_IS_DESTRUCTIBLE_TEST(true,  UDT&);
HAMON_IS_DESTRUCTIBLE_TEST(true,  UDT&&);
HAMON_IS_DESTRUCTIBLE_TEST(true,  UDT[2]);
HAMON_IS_DESTRUCTIBLE_TEST(false, UDT[]);
HAMON_IS_DESTRUCTIBLE_TEST(true,  UDT(&)[2]);
HAMON_IS_DESTRUCTIBLE_TEST(true,  UDT(&)[]);
HAMON_IS_DESTRUCTIBLE_TEST(true,  UDT(&&)[2]);
HAMON_IS_DESTRUCTIBLE_TEST(true,  UDT(&&)[]);

HAMON_IS_DESTRUCTIBLE_TEST(false,                S6);
HAMON_IS_DESTRUCTIBLE_TEST(false, const          S6);
HAMON_IS_DESTRUCTIBLE_TEST(false,       volatile S6);
HAMON_IS_DESTRUCTIBLE_TEST(false, const volatile S6);
HAMON_IS_DESTRUCTIBLE_TEST(true,  S6*);
HAMON_IS_DESTRUCTIBLE_TEST(true,  S6&);
HAMON_IS_DESTRUCTIBLE_TEST(true,  S6&&);
HAMON_IS_DESTRUCTIBLE_TEST(false, S6[2]);
HAMON_IS_DESTRUCTIBLE_TEST(false, S6[]);
HAMON_IS_DESTRUCTIBLE_TEST(true,  S6(&)[2]);
HAMON_IS_DESTRUCTIBLE_TEST(true,  S6(&)[]);
HAMON_IS_DESTRUCTIBLE_TEST(true,  S6(&&)[2]);
HAMON_IS_DESTRUCTIBLE_TEST(true,  S6(&&)[]);

HAMON_IS_DESTRUCTIBLE_TEST(true,  test_abc1);
HAMON_IS_DESTRUCTIBLE_TEST(true,  test_abc2);
HAMON_IS_DESTRUCTIBLE_TEST(true,  test_abc3);
HAMON_IS_DESTRUCTIBLE_TEST(true,  test_concrete1);
HAMON_IS_DESTRUCTIBLE_TEST(true,  test_concrete2);

HAMON_IS_DESTRUCTIBLE_TEST(true,  f1);
HAMON_IS_DESTRUCTIBLE_TEST(true,  f2);
HAMON_IS_DESTRUCTIBLE_TEST(true,  f3);
HAMON_IS_DESTRUCTIBLE_TEST(true,  mf1);
HAMON_IS_DESTRUCTIBLE_TEST(true,  mf2);
HAMON_IS_DESTRUCTIBLE_TEST(true,  mf3);
HAMON_IS_DESTRUCTIBLE_TEST(true,  mf4);
HAMON_IS_DESTRUCTIBLE_TEST(true,  mp);
HAMON_IS_DESTRUCTIBLE_TEST(true,  cmf);
HAMON_IS_DESTRUCTIBLE_TEST(false, foo0_t);
HAMON_IS_DESTRUCTIBLE_TEST(false, foo1_t);
HAMON_IS_DESTRUCTIBLE_TEST(false, foo2_t);
HAMON_IS_DESTRUCTIBLE_TEST(false, foo3_t);
HAMON_IS_DESTRUCTIBLE_TEST(false, foo4_t);

}	// namespace is_destructible_test

}	// namespace hamon_type_traits_test

#undef HAMON_IS_DESTRUCTIBLE_TEST
