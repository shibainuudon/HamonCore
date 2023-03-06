/**
 *	@file	unit_test_type_traits_is_default_constructible.cpp
 *
 *	@brief	is_default_constructible のテスト
 */

#include <hamon/type_traits/is_default_constructible.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include <cstddef>
#include "type_traits_test_utility.hpp"

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

#define HAMON_IS_DEFAULT_CONSTRUCTIBLE_TEST(b, T)	\
	static_assert(hamon::is_default_constructible_v<T>      == b, #T);	\
	static_assert(hamon::is_default_constructible<T>::value == b, #T);	\
	static_assert(hamon::is_default_constructible<T>{}()    == b, #T);	\
	static_assert(hamon::is_default_constructible<T>{}      == b, #T)

#else

#define HAMON_IS_DEFAULT_CONSTRUCTIBLE_TEST(b, T)	\
	static_assert(hamon::is_default_constructible<T>::value == b, #T);	\
	static_assert(hamon::is_default_constructible<T>{}()    == b, #T);	\
	static_assert(hamon::is_default_constructible<T>{}      == b, #T)

#endif

namespace hamon_type_traits_test
{

namespace is_default_constructible_test
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

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4510)	// 既定のコンストラクターを生成できません。
HAMON_WARNING_DISABLE_MSVC(4610)	// ユーザー定義のコンストラクターが必要です。

// defaultコンストラクタを持たないクラスをメンバに持つ
struct S6
{
	S5 member;
};

HAMON_WARNING_POP()

HAMON_IS_DEFAULT_CONSTRUCTIBLE_TEST(true,  S1);
HAMON_IS_DEFAULT_CONSTRUCTIBLE_TEST(true,  S2);
HAMON_IS_DEFAULT_CONSTRUCTIBLE_TEST(true,  S3);
HAMON_IS_DEFAULT_CONSTRUCTIBLE_TEST(true,  S4);
HAMON_IS_DEFAULT_CONSTRUCTIBLE_TEST(false, S5);
HAMON_IS_DEFAULT_CONSTRUCTIBLE_TEST(false, S6);

HAMON_IS_DEFAULT_CONSTRUCTIBLE_TEST(true,  int);
HAMON_IS_DEFAULT_CONSTRUCTIBLE_TEST(true,  const int);
HAMON_IS_DEFAULT_CONSTRUCTIBLE_TEST(true,  volatile int);
HAMON_IS_DEFAULT_CONSTRUCTIBLE_TEST(true,  const volatile int);
HAMON_IS_DEFAULT_CONSTRUCTIBLE_TEST(true,  int*);
HAMON_IS_DEFAULT_CONSTRUCTIBLE_TEST(false, int&);
HAMON_IS_DEFAULT_CONSTRUCTIBLE_TEST(false, int&&);
HAMON_IS_DEFAULT_CONSTRUCTIBLE_TEST(true,  int[2]);
HAMON_IS_DEFAULT_CONSTRUCTIBLE_TEST(false, int[]);
HAMON_IS_DEFAULT_CONSTRUCTIBLE_TEST(false, int(&)[2]);
HAMON_IS_DEFAULT_CONSTRUCTIBLE_TEST(false, int(&)[]);
HAMON_IS_DEFAULT_CONSTRUCTIBLE_TEST(false, int(&&)[2]);
HAMON_IS_DEFAULT_CONSTRUCTIBLE_TEST(false, int(&&)[]);

HAMON_IS_DEFAULT_CONSTRUCTIBLE_TEST(false, void);
HAMON_IS_DEFAULT_CONSTRUCTIBLE_TEST(false, const void);
HAMON_IS_DEFAULT_CONSTRUCTIBLE_TEST(false, volatile void);
HAMON_IS_DEFAULT_CONSTRUCTIBLE_TEST(false, const volatile void);

HAMON_IS_DEFAULT_CONSTRUCTIBLE_TEST(true,  void*);
HAMON_IS_DEFAULT_CONSTRUCTIBLE_TEST(true,  std::nullptr_t);
HAMON_IS_DEFAULT_CONSTRUCTIBLE_TEST(true,  enum_UDT);
HAMON_IS_DEFAULT_CONSTRUCTIBLE_TEST(true,  enum_class_UDT);
HAMON_IS_DEFAULT_CONSTRUCTIBLE_TEST(true,  UDT);
HAMON_IS_DEFAULT_CONSTRUCTIBLE_TEST(false, int_constructible);
HAMON_IS_DEFAULT_CONSTRUCTIBLE_TEST(true,  int_convertible);
HAMON_IS_DEFAULT_CONSTRUCTIBLE_TEST(false, test_abc1);
HAMON_IS_DEFAULT_CONSTRUCTIBLE_TEST(false, test_abc2);
HAMON_IS_DEFAULT_CONSTRUCTIBLE_TEST(false, test_abc3);
HAMON_IS_DEFAULT_CONSTRUCTIBLE_TEST(true,  test_concrete1);
HAMON_IS_DEFAULT_CONSTRUCTIBLE_TEST(true,  test_concrete2);
HAMON_IS_DEFAULT_CONSTRUCTIBLE_TEST(true,  trivial_except_construct);
HAMON_IS_DEFAULT_CONSTRUCTIBLE_TEST(true,  trivial_except_destroy);
HAMON_IS_DEFAULT_CONSTRUCTIBLE_TEST(false, trivial_except_copy_ctor);
HAMON_IS_DEFAULT_CONSTRUCTIBLE_TEST(true,  trivial_except_copy_assign);
HAMON_IS_DEFAULT_CONSTRUCTIBLE_TEST(false, trivial_except_move_ctor);
HAMON_IS_DEFAULT_CONSTRUCTIBLE_TEST(true,  trivial_except_move_assign);
HAMON_IS_DEFAULT_CONSTRUCTIBLE_TEST(true,  f1);
HAMON_IS_DEFAULT_CONSTRUCTIBLE_TEST(true,  f2);
HAMON_IS_DEFAULT_CONSTRUCTIBLE_TEST(true,  f3);
HAMON_IS_DEFAULT_CONSTRUCTIBLE_TEST(true,  mf1);
HAMON_IS_DEFAULT_CONSTRUCTIBLE_TEST(true,  mf2);
HAMON_IS_DEFAULT_CONSTRUCTIBLE_TEST(true,  mf3);
HAMON_IS_DEFAULT_CONSTRUCTIBLE_TEST(true,  mf4);
HAMON_IS_DEFAULT_CONSTRUCTIBLE_TEST(true,  mp);
HAMON_IS_DEFAULT_CONSTRUCTIBLE_TEST(true,  cmf);
HAMON_IS_DEFAULT_CONSTRUCTIBLE_TEST(false, foo0_t);
HAMON_IS_DEFAULT_CONSTRUCTIBLE_TEST(false, foo1_t);
HAMON_IS_DEFAULT_CONSTRUCTIBLE_TEST(false, foo2_t);
HAMON_IS_DEFAULT_CONSTRUCTIBLE_TEST(false, foo3_t);
HAMON_IS_DEFAULT_CONSTRUCTIBLE_TEST(false, foo4_t);
HAMON_IS_DEFAULT_CONSTRUCTIBLE_TEST(false, int(&)());

}	// namespace is_default_constructible_test

}	// namespace hamon_type_traits_test

#undef HAMON_IS_DEFAULT_CONSTRUCTIBLE_TEST
