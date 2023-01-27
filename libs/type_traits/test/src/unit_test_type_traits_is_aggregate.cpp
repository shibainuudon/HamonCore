/**
 *	@file	unit_test_type_traits_is_aggregate.cpp
 *
 *	@brief	is_aggregate のテスト
 */

#include <hamon/type_traits/is_aggregate.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include <array>

#if defined(HAMON_HAS_IS_AGGREGATE)

namespace hamon_type_traits_test
{

namespace is_aggregate_test
{

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

#define HAMON_IS_AGGREGATE_TEST(b, T)	\
	static_assert(hamon::is_aggregate_v<T>      == b, #T);	\
	static_assert(hamon::is_aggregate<T>::value == b, #T);	\
	static_assert(hamon::is_aggregate<T>()      == b, #T)

#else

#define HAMON_IS_AGGREGATE_TEST(b, T)	\
	static_assert(hamon::is_aggregate<T>::value == b, #T);	\
	static_assert(hamon::is_aggregate<T>()      == b, #T)

#endif

#define HAMON_IS_AGGREGATE_TEST_CV(b, T)	\
	HAMON_IS_AGGREGATE_TEST(b,                T);	\
	HAMON_IS_AGGREGATE_TEST(b, const          T);	\
	HAMON_IS_AGGREGATE_TEST(b,       volatile T);	\
	HAMON_IS_AGGREGATE_TEST(b, const volatile T)

struct Base {};

struct HasBase : Base
{
	int x;
};

struct HasCtor { HasCtor(int){} };

struct HasPrivateMember
{
	void PreventUnusedPrivateMemberWarning();
private:
	int x;
};

struct HasVirtualFunc
{
	virtual void f() {}
};

struct Aggregate1
{
	int x;
};

struct Aggregate2
{
	int x, y;
};

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4510)	// 既定のコンストラクターを生成できません。
HAMON_WARNING_DISABLE_MSVC(4610)	// 'Aggregate3' を初期化できません。ユーザー定義のコンストラクターが必要です。

struct Aggregate3
{
	double d = 0.5;
	HasBase b;
	HasCtor c;
	HasPrivateMember p;
	HasVirtualFunc v;
private:
	void g() {}
};

HAMON_WARNING_POP()

HAMON_IS_AGGREGATE_TEST_CV(true,  Aggregate1);
HAMON_IS_AGGREGATE_TEST_CV(true,  Aggregate1[]);
HAMON_IS_AGGREGATE_TEST_CV(true,  Aggregate1[2][3]);
HAMON_IS_AGGREGATE_TEST_CV(false, Aggregate1&);
HAMON_IS_AGGREGATE_TEST_CV(false, Aggregate1&&);
HAMON_IS_AGGREGATE_TEST_CV(false, Aggregate1*);
HAMON_IS_AGGREGATE_TEST   (false, void(Aggregate1::*)(int) const);
HAMON_IS_AGGREGATE_TEST_CV(true,  Aggregate2);
HAMON_IS_AGGREGATE_TEST_CV(true,  Aggregate2);
HAMON_IS_AGGREGATE_TEST_CV(true,  Aggregate2[3]);
HAMON_IS_AGGREGATE_TEST_CV(false, Aggregate2&);
HAMON_IS_AGGREGATE_TEST_CV(false, Aggregate2&&);
HAMON_IS_AGGREGATE_TEST_CV(false, Aggregate2*);
#if HAMON_CXX_STANDARD >= 14
HAMON_IS_AGGREGATE_TEST_CV(true,  Aggregate3);
#endif
HAMON_IS_AGGREGATE_TEST_CV(false, HasCtor);
HAMON_IS_AGGREGATE_TEST_CV(true,  HasCtor[3]);
HAMON_IS_AGGREGATE_TEST_CV(false, HasPrivateMember);
HAMON_IS_AGGREGATE_TEST_CV(false, int);
HAMON_IS_AGGREGATE_TEST_CV(false, int*);
HAMON_IS_AGGREGATE_TEST_CV(false, int&);
HAMON_IS_AGGREGATE_TEST_CV(true,  int[3]);
HAMON_IS_AGGREGATE_TEST_CV(false, void);
HAMON_IS_AGGREGATE_TEST_CV(false, void*);
HAMON_IS_AGGREGATE_TEST   (false, void());
using ArrayType = std::array<Aggregate1, 4>;
HAMON_IS_AGGREGATE_TEST_CV(true,  ArrayType);

#undef HAMON_IS_AGGREGATE_TEST
#undef HAMON_IS_AGGREGATE_TEST_CV

}	// namespace is_aggregate_test

}	// namespace hamon_type_traits_test

#else
#pragma message("hamon doesn't have is_aggregate")
#endif
