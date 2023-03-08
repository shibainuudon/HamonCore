/**
 *	@file	unit_test_type_traits_is_nothrow_move_assignable.cpp
 *
 *	@brief	is_nothrow_move_assignable のテスト
 */

#include <hamon/type_traits/is_nothrow_move_assignable.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/cstddef/nullptr_t.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "type_traits_test_utility.hpp"

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

#define HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(b, T)	\
	static_assert(hamon::is_nothrow_move_assignable_v<T>      == b, #T ", " #b);	\
	static_assert(hamon::is_nothrow_move_assignable<T>::value == b, #T ", " #b);	\
	static_assert(hamon::is_nothrow_move_assignable<T>{}()    == b, #T ", " #b);	\
	static_assert(hamon::is_nothrow_move_assignable<T>{}      == b, #T ", " #b)

#else

#define HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(b, T)	\
	static_assert(hamon::is_nothrow_move_assignable<T>::value == b, #T ", " #b);	\
	static_assert(hamon::is_nothrow_move_assignable<T>{}()    == b, #T ", " #b);	\
	static_assert(hamon::is_nothrow_move_assignable<T>{}      == b, #T ", " #b)

#endif

namespace hamon_type_traits_test
{

namespace is_nothrow_move_assignable_test
{

// トリビアルなムーブ代入演算子を持つ
struct S1
{
	int n;
};

// 非トリビアルだが例外を投げないムーブ代入演算子を持つ
struct S2
{
	S2& operator=(S2&&) HAMON_NOEXCEPT_OR_NOTHROW;
};

// 非トリビアルだが例外を投げないムーブ代入演算子を持つクラスをメンバに持つ
struct S3
{
	S2 member;
};

// ムーブ代入演算子が例外を投げる
struct S4
{
	S4& operator=(S4&&);
};

// ムーブ代入演算子が例外を投げる
struct S5
{
	S5& operator=(S5&&) HAMON_NOEXCEPT_IF(false);
};

// ムーブ代入演算子を持たない
struct S6
{
	S6& operator=(S6&&) = delete;
};

HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(true,  S1);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(true,  S2);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(true,  S3);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(false, S4);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(false, S5);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(false, S6);

HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(true,                 int);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(false, const          int);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(true,        volatile int);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(false, const volatile int);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(true,                 int*);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(true,  const          int*);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(true,        volatile int*);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(true,  const volatile int*);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(true,                 int&);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(false, const          int&);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(true,        volatile int&);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(false, const volatile int&);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(true,                 int&&);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(false, const          int&&);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(true,        volatile int&&);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(false, const volatile int&&);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(false, int[2]);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(false, int[]);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(false, int(&)[2]);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(false, int(&)[]);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(false, int(&&)[2]);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(false, int(&&)[]);

HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(false,                void);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(false, const          void);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(false,       volatile void);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(false, const volatile void);

HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(true, bool);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(true, char);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(true, wchar_t);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(true, signed char);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(true, int);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(true, short);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(true, long);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(true, long long);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(true, unsigned char);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(true, unsigned int);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(true, unsigned short);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(true, unsigned long);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(true, unsigned long long);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(true, hamon::size_t);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(true, float);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(true, double);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(true, long double);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(true, void*);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(true, hamon::nullptr_t);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(true, decltype(nullptr));
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(true, enum_UDT);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(true, enum_uint32_t_UDT);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(true, enum_uint16_t_UDT);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(true, enum_uint8_t_UDT);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(true, enum_int32_t_UDT);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(true, enum_int16_t_UDT);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(true, enum_int8_t_UDT);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(true, enum_class_UDT);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(true, enum_class_uint32_t_UDT);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(true, enum_class_uint16_t_UDT);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(true, enum_class_uint8_t_UDT);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(true, enum_class_int32_t_UDT);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(true, enum_class_int16_t_UDT);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(true, enum_class_int8_t_UDT);

HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(false,                UDT);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(false, const          UDT);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(false,       volatile UDT);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(false, const volatile UDT);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(true,                 UDT*);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(true,  const          UDT*);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(true,        volatile UDT*);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(true,  const volatile UDT*);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(false,                UDT&);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(false, const          UDT&);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(false,       volatile UDT&);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(false, const volatile UDT&);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(false,                UDT&&);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(false, const          UDT&&);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(false,       volatile UDT&&);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(false, const volatile UDT&&);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(false, UDT[2]);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(false, UDT[]);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(false, UDT(&)[2]);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(false, UDT(&)[]);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(false, UDT(&&)[2]);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(false, UDT(&&)[]);

HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(true,                 POD_UDT);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(false, const          POD_UDT);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(false,       volatile POD_UDT);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(false, const volatile POD_UDT);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(true,                 POD_UDT*);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(true,  const          POD_UDT*);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(true,        volatile POD_UDT*);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(true,  const volatile POD_UDT*);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(true,                 POD_UDT&);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(false, const          POD_UDT&);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(false,       volatile POD_UDT&);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(false, const volatile POD_UDT&);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(true,                 POD_UDT&&);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(false, const          POD_UDT&&);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(false,       volatile POD_UDT&&);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(false, const volatile POD_UDT&&);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(false, POD_UDT[2]);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(false, POD_UDT[]);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(false, POD_UDT(&)[2]);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(false, POD_UDT(&)[]);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(false, POD_UDT(&&)[2]);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(false, POD_UDT(&&)[]);

HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(false,                nothrow_default_ctor_UDT);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(false, const          nothrow_default_ctor_UDT);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(false,       volatile nothrow_default_ctor_UDT);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(false, const volatile nothrow_default_ctor_UDT);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(false,                nothrow_default_ctor_UDT&);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(false, const          nothrow_default_ctor_UDT&);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(false,       volatile nothrow_default_ctor_UDT&);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(false, const volatile nothrow_default_ctor_UDT&);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(false,                nothrow_default_ctor_UDT&&);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(false, const          nothrow_default_ctor_UDT&&);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(false,       volatile nothrow_default_ctor_UDT&&);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(false, const volatile nothrow_default_ctor_UDT&&);

HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(false,                nothrow_dtor_UDT);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(false, const          nothrow_dtor_UDT);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(false,       volatile nothrow_dtor_UDT);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(false, const volatile nothrow_dtor_UDT);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(false,                nothrow_dtor_UDT&);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(false, const          nothrow_dtor_UDT&);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(false,       volatile nothrow_dtor_UDT&);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(false, const volatile nothrow_dtor_UDT&);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(false,                nothrow_dtor_UDT&&);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(false, const          nothrow_dtor_UDT&&);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(false,       volatile nothrow_dtor_UDT&&);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(false, const volatile nothrow_dtor_UDT&&);

HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(false,                nothrow_copy_ctor_UDT);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(false, const          nothrow_copy_ctor_UDT);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(false,       volatile nothrow_copy_ctor_UDT);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(false, const volatile nothrow_copy_ctor_UDT);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(false,                nothrow_copy_ctor_UDT&);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(false, const          nothrow_copy_ctor_UDT&);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(false,       volatile nothrow_copy_ctor_UDT&);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(false, const volatile nothrow_copy_ctor_UDT&);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(false,                nothrow_copy_ctor_UDT&&);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(false, const          nothrow_copy_ctor_UDT&&);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(false,       volatile nothrow_copy_ctor_UDT&&);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(false, const volatile nothrow_copy_ctor_UDT&&);

HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(false,                nothrow_copy_assign_UDT);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(false, const          nothrow_copy_assign_UDT);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(false,       volatile nothrow_copy_assign_UDT);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(false, const volatile nothrow_copy_assign_UDT);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(true,                 nothrow_copy_assign_UDT&);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(false, const          nothrow_copy_assign_UDT&);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(false,       volatile nothrow_copy_assign_UDT&);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(false, const volatile nothrow_copy_assign_UDT&);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(false,                nothrow_copy_assign_UDT&&);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(false, const          nothrow_copy_assign_UDT&&);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(false,       volatile nothrow_copy_assign_UDT&&);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(false, const volatile nothrow_copy_assign_UDT&&);

HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(false,                nothrow_move_ctor_UDT);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(false, const          nothrow_move_ctor_UDT);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(false,       volatile nothrow_move_ctor_UDT);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(false, const volatile nothrow_move_ctor_UDT);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(false,                nothrow_move_ctor_UDT&);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(false, const          nothrow_move_ctor_UDT&);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(false,       volatile nothrow_move_ctor_UDT&);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(false, const volatile nothrow_move_ctor_UDT&);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(false,                nothrow_move_ctor_UDT&&);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(false, const          nothrow_move_ctor_UDT&&);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(false,       volatile nothrow_move_ctor_UDT&&);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(false, const volatile nothrow_move_ctor_UDT&&);

HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(true,                 nothrow_move_assign_UDT);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(false, const          nothrow_move_assign_UDT);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(false,       volatile nothrow_move_assign_UDT);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(false, const volatile nothrow_move_assign_UDT);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(false,                nothrow_move_assign_UDT&);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(false, const          nothrow_move_assign_UDT&);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(false,       volatile nothrow_move_assign_UDT&);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(false, const volatile nothrow_move_assign_UDT&);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(true,                 nothrow_move_assign_UDT&&);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(false, const          nothrow_move_assign_UDT&&);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(false,       volatile nothrow_move_assign_UDT&&);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(false, const volatile nothrow_move_assign_UDT&&);

HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(true, f1);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(true, f2);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(true, f3);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(true, mf1);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(true, mf2);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(true, mf3);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(true, mf4);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(true, mp);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(true, cmf);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(false, foo0_t);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(false, foo1_t);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(false, foo2_t);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(false, foo3_t);
HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST(false, foo4_t);

}	// namespace is_nothrow_move_assignable_test

}	// namespace hamon_type_traits_test

#undef HAMON_IS_NOTHROW_MOVE_ASSIGNABLE_TEST
