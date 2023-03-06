/**
 *	@file	unit_test_type_traits_is_nothrow_move_constructible.cpp
 *
 *	@brief	is_nothrow_move_constructible のテスト
 */

#include <hamon/type_traits/is_nothrow_move_constructible.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "type_traits_test_utility.hpp"

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4510 4610)

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

#define HAMON_IS_NOTHROW_MOVE_CONSTRUCTIBLE_TEST(b, T)	\
	static_assert(hamon::is_nothrow_move_constructible_v<T>      == b, #T);	\
	static_assert(hamon::is_nothrow_move_constructible<T>::value == b, #T);	\
	static_assert(hamon::is_nothrow_move_constructible<T>{}()    == b, #T);	\
	static_assert(hamon::is_nothrow_move_constructible<T>{}      == b, #T)

#else

#define HAMON_IS_NOTHROW_MOVE_CONSTRUCTIBLE_TEST(b, T)	\
	static_assert(hamon::is_nothrow_move_constructible<T>::value == b, #T);	\
	static_assert(hamon::is_nothrow_move_constructible<T>{}()    == b, #T);	\
	static_assert(hamon::is_nothrow_move_constructible<T>{}      == b, #T)

#endif

namespace hamon_type_traits_test
{

namespace is_nothrow_move_constructible_test
{

// トリビアルなmoveコンストラクタを持つ
struct S1
{
	int n;
};

// 非トリビアルだが例外を投げないmoveコンストラクタを持つ
struct S2
{
	S2(S2&&) HAMON_NOEXCEPT_OR_NOTHROW;
};

// 非トリビアルだが例外を投げないmoveコンストラクタを持つクラスをメンバに持つ
struct S3
{
	S2 member;
};

// moveコンストラクタが例外を投げる
struct S4
{
	S4(S4&&) noexcept(false) {}
};

// moveコンストラクタを持たない
struct S5
{
	S5(const S5&);
};

// moveコンストラクタを持たないクラスをメンバに持つ
struct S6
{
	S5 member;
};

HAMON_IS_NOTHROW_MOVE_CONSTRUCTIBLE_TEST(true,  S1);
HAMON_IS_NOTHROW_MOVE_CONSTRUCTIBLE_TEST(true,  S2);
HAMON_IS_NOTHROW_MOVE_CONSTRUCTIBLE_TEST(true,  S3);
HAMON_IS_NOTHROW_MOVE_CONSTRUCTIBLE_TEST(false, S4);
HAMON_IS_NOTHROW_MOVE_CONSTRUCTIBLE_TEST(false, S5);
HAMON_IS_NOTHROW_MOVE_CONSTRUCTIBLE_TEST(false, S6);

HAMON_IS_NOTHROW_MOVE_CONSTRUCTIBLE_TEST(true,		int);
HAMON_IS_NOTHROW_MOVE_CONSTRUCTIBLE_TEST(true,		const int);
HAMON_IS_NOTHROW_MOVE_CONSTRUCTIBLE_TEST(true,		volatile int);
HAMON_IS_NOTHROW_MOVE_CONSTRUCTIBLE_TEST(true,		const volatile int);
HAMON_IS_NOTHROW_MOVE_CONSTRUCTIBLE_TEST(true,		int*);
HAMON_IS_NOTHROW_MOVE_CONSTRUCTIBLE_TEST(true,		int&);
HAMON_IS_NOTHROW_MOVE_CONSTRUCTIBLE_TEST(true,		int&&);
HAMON_IS_NOTHROW_MOVE_CONSTRUCTIBLE_TEST(false,		int[2]);
HAMON_IS_NOTHROW_MOVE_CONSTRUCTIBLE_TEST(false,		int[]);
HAMON_IS_NOTHROW_MOVE_CONSTRUCTIBLE_TEST(true,		int(&)[2]);
HAMON_IS_NOTHROW_MOVE_CONSTRUCTIBLE_TEST(true,		int(&)[]);
HAMON_IS_NOTHROW_MOVE_CONSTRUCTIBLE_TEST(true,		int(&&)[2]);
HAMON_IS_NOTHROW_MOVE_CONSTRUCTIBLE_TEST(true,		int(&&)[]);

HAMON_IS_NOTHROW_MOVE_CONSTRUCTIBLE_TEST(false,		               void);
HAMON_IS_NOTHROW_MOVE_CONSTRUCTIBLE_TEST(false,		const          void);
HAMON_IS_NOTHROW_MOVE_CONSTRUCTIBLE_TEST(false,		      volatile void);
HAMON_IS_NOTHROW_MOVE_CONSTRUCTIBLE_TEST(false,		const volatile void);

HAMON_IS_NOTHROW_MOVE_CONSTRUCTIBLE_TEST(true,		f1);
HAMON_IS_NOTHROW_MOVE_CONSTRUCTIBLE_TEST(true,		f2);
HAMON_IS_NOTHROW_MOVE_CONSTRUCTIBLE_TEST(true,		f3);
HAMON_IS_NOTHROW_MOVE_CONSTRUCTIBLE_TEST(true,		mf1);
HAMON_IS_NOTHROW_MOVE_CONSTRUCTIBLE_TEST(true,		mf2);
HAMON_IS_NOTHROW_MOVE_CONSTRUCTIBLE_TEST(true,		mf3);
HAMON_IS_NOTHROW_MOVE_CONSTRUCTIBLE_TEST(true,		mf4);
HAMON_IS_NOTHROW_MOVE_CONSTRUCTIBLE_TEST(true,		mp);
HAMON_IS_NOTHROW_MOVE_CONSTRUCTIBLE_TEST(true,		cmf);
HAMON_IS_NOTHROW_MOVE_CONSTRUCTIBLE_TEST(false,		foo0_t);
HAMON_IS_NOTHROW_MOVE_CONSTRUCTIBLE_TEST(false,		foo1_t);
HAMON_IS_NOTHROW_MOVE_CONSTRUCTIBLE_TEST(false,		foo2_t);
HAMON_IS_NOTHROW_MOVE_CONSTRUCTIBLE_TEST(false,		foo3_t);
HAMON_IS_NOTHROW_MOVE_CONSTRUCTIBLE_TEST(false,		foo4_t);

HAMON_IS_NOTHROW_MOVE_CONSTRUCTIBLE_TEST(false,		               UDT);
HAMON_IS_NOTHROW_MOVE_CONSTRUCTIBLE_TEST(false,		const          UDT);
HAMON_IS_NOTHROW_MOVE_CONSTRUCTIBLE_TEST(false,		      volatile UDT);
HAMON_IS_NOTHROW_MOVE_CONSTRUCTIBLE_TEST(false,		const volatile UDT);
HAMON_IS_NOTHROW_MOVE_CONSTRUCTIBLE_TEST(true,		UDT*);
HAMON_IS_NOTHROW_MOVE_CONSTRUCTIBLE_TEST(true,		UDT&);
HAMON_IS_NOTHROW_MOVE_CONSTRUCTIBLE_TEST(true,		UDT&&);
HAMON_IS_NOTHROW_MOVE_CONSTRUCTIBLE_TEST(false,		UDT[2]);
HAMON_IS_NOTHROW_MOVE_CONSTRUCTIBLE_TEST(false,		UDT[]);
HAMON_IS_NOTHROW_MOVE_CONSTRUCTIBLE_TEST(true,		UDT(&)[2]);
HAMON_IS_NOTHROW_MOVE_CONSTRUCTIBLE_TEST(true,		UDT(&)[]);
HAMON_IS_NOTHROW_MOVE_CONSTRUCTIBLE_TEST(true,		UDT(&&)[2]);
HAMON_IS_NOTHROW_MOVE_CONSTRUCTIBLE_TEST(true,		UDT(&&)[]);

HAMON_IS_NOTHROW_MOVE_CONSTRUCTIBLE_TEST(true,		               POD_UDT);
HAMON_IS_NOTHROW_MOVE_CONSTRUCTIBLE_TEST(true,		const          POD_UDT);
HAMON_IS_NOTHROW_MOVE_CONSTRUCTIBLE_TEST(false,		      volatile POD_UDT);
HAMON_IS_NOTHROW_MOVE_CONSTRUCTIBLE_TEST(false,		const volatile POD_UDT);
HAMON_IS_NOTHROW_MOVE_CONSTRUCTIBLE_TEST(true,		POD_UDT*);
HAMON_IS_NOTHROW_MOVE_CONSTRUCTIBLE_TEST(true,		POD_UDT&);
HAMON_IS_NOTHROW_MOVE_CONSTRUCTIBLE_TEST(true,		POD_UDT&&);
HAMON_IS_NOTHROW_MOVE_CONSTRUCTIBLE_TEST(false,		POD_UDT[2]);
HAMON_IS_NOTHROW_MOVE_CONSTRUCTIBLE_TEST(false,		POD_UDT[]);
HAMON_IS_NOTHROW_MOVE_CONSTRUCTIBLE_TEST(true,		POD_UDT(&)[2]);
HAMON_IS_NOTHROW_MOVE_CONSTRUCTIBLE_TEST(true,		POD_UDT(&)[]);
HAMON_IS_NOTHROW_MOVE_CONSTRUCTIBLE_TEST(true,		POD_UDT(&&)[2]);
HAMON_IS_NOTHROW_MOVE_CONSTRUCTIBLE_TEST(true,		POD_UDT(&&)[]);

HAMON_IS_NOTHROW_MOVE_CONSTRUCTIBLE_TEST(false,                nothrow_default_ctor_UDT);
HAMON_IS_NOTHROW_MOVE_CONSTRUCTIBLE_TEST(false, const          nothrow_default_ctor_UDT);
HAMON_IS_NOTHROW_MOVE_CONSTRUCTIBLE_TEST(false,       volatile nothrow_default_ctor_UDT);
HAMON_IS_NOTHROW_MOVE_CONSTRUCTIBLE_TEST(false, const volatile nothrow_default_ctor_UDT);
HAMON_IS_NOTHROW_MOVE_CONSTRUCTIBLE_TEST(false,                nothrow_dtor_UDT);
HAMON_IS_NOTHROW_MOVE_CONSTRUCTIBLE_TEST(false, const          nothrow_dtor_UDT);
HAMON_IS_NOTHROW_MOVE_CONSTRUCTIBLE_TEST(false,       volatile nothrow_dtor_UDT);
HAMON_IS_NOTHROW_MOVE_CONSTRUCTIBLE_TEST(false, const volatile nothrow_dtor_UDT);
HAMON_IS_NOTHROW_MOVE_CONSTRUCTIBLE_TEST(false,                nothrow_copy_ctor_UDT);
HAMON_IS_NOTHROW_MOVE_CONSTRUCTIBLE_TEST(true,  const          nothrow_copy_ctor_UDT);
HAMON_IS_NOTHROW_MOVE_CONSTRUCTIBLE_TEST(false,       volatile nothrow_copy_ctor_UDT);
HAMON_IS_NOTHROW_MOVE_CONSTRUCTIBLE_TEST(false, const volatile nothrow_copy_ctor_UDT);
HAMON_IS_NOTHROW_MOVE_CONSTRUCTIBLE_TEST(false,                nothrow_copy_assign_UDT);
HAMON_IS_NOTHROW_MOVE_CONSTRUCTIBLE_TEST(false, const          nothrow_copy_assign_UDT);
HAMON_IS_NOTHROW_MOVE_CONSTRUCTIBLE_TEST(false,       volatile nothrow_copy_assign_UDT);
HAMON_IS_NOTHROW_MOVE_CONSTRUCTIBLE_TEST(false, const volatile nothrow_copy_assign_UDT);
HAMON_IS_NOTHROW_MOVE_CONSTRUCTIBLE_TEST(true,                 nothrow_move_ctor_UDT);
HAMON_IS_NOTHROW_MOVE_CONSTRUCTIBLE_TEST(false, const          nothrow_move_ctor_UDT);
HAMON_IS_NOTHROW_MOVE_CONSTRUCTIBLE_TEST(false,       volatile nothrow_move_ctor_UDT);
HAMON_IS_NOTHROW_MOVE_CONSTRUCTIBLE_TEST(false, const volatile nothrow_move_ctor_UDT);
HAMON_IS_NOTHROW_MOVE_CONSTRUCTIBLE_TEST(false,                nothrow_move_assign_UDT);
HAMON_IS_NOTHROW_MOVE_CONSTRUCTIBLE_TEST(false, const          nothrow_move_assign_UDT);
HAMON_IS_NOTHROW_MOVE_CONSTRUCTIBLE_TEST(false,       volatile nothrow_move_assign_UDT);
HAMON_IS_NOTHROW_MOVE_CONSTRUCTIBLE_TEST(false, const volatile nothrow_move_assign_UDT);

}	// namespace is_nothrow_move_constructible_test

}	// namespace hamon_type_traits_test

#undef HAMON_IS_NOTHROW_MOVE_CONSTRUCTIBLE_TEST

HAMON_WARNING_POP()
