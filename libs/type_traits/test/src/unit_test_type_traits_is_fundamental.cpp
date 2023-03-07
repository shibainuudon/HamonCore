/**
 *	@file	unit_test_type_traits_is_fundamental.cpp
 *
 *	@brief	is_fundamental のテスト
 */

#include <hamon/type_traits/is_fundamental.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include <cstddef>
#include "type_traits_test_utility.hpp"

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

#define HAMON_IS_FUNDAMENTAL_TEST(b, T)	\
	static_assert(hamon::is_fundamental_v<T>      == b, #T);	\
	static_assert(hamon::is_fundamental<T>::value == b, #T);	\
	static_assert(hamon::is_fundamental<T>{}()    == b, #T);	\
	static_assert(hamon::is_fundamental<T>{}      == b, #T)

#else

#define HAMON_IS_FUNDAMENTAL_TEST(b, T)	\
	static_assert(hamon::is_fundamental<T>::value == b, #T);	\
	static_assert(hamon::is_fundamental<T>{}()    == b, #T);	\
	static_assert(hamon::is_fundamental<T>{}      == b, #T)

#endif

HAMON_IS_FUNDAMENTAL_TEST(true,                 int);
HAMON_IS_FUNDAMENTAL_TEST(true,  const          int);
HAMON_IS_FUNDAMENTAL_TEST(true,        volatile int);
HAMON_IS_FUNDAMENTAL_TEST(true,  const volatile int);
HAMON_IS_FUNDAMENTAL_TEST(false, int*);
HAMON_IS_FUNDAMENTAL_TEST(false, int&);
HAMON_IS_FUNDAMENTAL_TEST(false, int&&);
HAMON_IS_FUNDAMENTAL_TEST(false, int[2]);
HAMON_IS_FUNDAMENTAL_TEST(false, int[]);
HAMON_IS_FUNDAMENTAL_TEST(false, int(&)[2]);
HAMON_IS_FUNDAMENTAL_TEST(false, int(&)[]);
HAMON_IS_FUNDAMENTAL_TEST(false, int(&&)[2]);
HAMON_IS_FUNDAMENTAL_TEST(false, int(&&)[]);

HAMON_IS_FUNDAMENTAL_TEST(true, bool);
HAMON_IS_FUNDAMENTAL_TEST(true, char);
HAMON_IS_FUNDAMENTAL_TEST(true, wchar_t);
HAMON_IS_FUNDAMENTAL_TEST(true, signed char);
HAMON_IS_FUNDAMENTAL_TEST(true, int);
HAMON_IS_FUNDAMENTAL_TEST(true, short);
HAMON_IS_FUNDAMENTAL_TEST(true, long);
HAMON_IS_FUNDAMENTAL_TEST(true, long long);
HAMON_IS_FUNDAMENTAL_TEST(true, unsigned char);
HAMON_IS_FUNDAMENTAL_TEST(true, unsigned int);
HAMON_IS_FUNDAMENTAL_TEST(true, unsigned short);
HAMON_IS_FUNDAMENTAL_TEST(true, unsigned long);
HAMON_IS_FUNDAMENTAL_TEST(true, unsigned long long);
HAMON_IS_FUNDAMENTAL_TEST(true, hamon::size_t);
HAMON_IS_FUNDAMENTAL_TEST(true, float);
HAMON_IS_FUNDAMENTAL_TEST(true, double);
HAMON_IS_FUNDAMENTAL_TEST(true, long double);
HAMON_IS_FUNDAMENTAL_TEST(true, std::nullptr_t);
HAMON_IS_FUNDAMENTAL_TEST(true, decltype(nullptr));

HAMON_IS_FUNDAMENTAL_TEST(true,                 void);
HAMON_IS_FUNDAMENTAL_TEST(true,  const          void);
HAMON_IS_FUNDAMENTAL_TEST(true,        volatile void);
HAMON_IS_FUNDAMENTAL_TEST(true,  const volatile void);

HAMON_IS_FUNDAMENTAL_TEST(false, void*);
HAMON_IS_FUNDAMENTAL_TEST(false, enum_UDT);
HAMON_IS_FUNDAMENTAL_TEST(false, enum_uint32_t_UDT);
HAMON_IS_FUNDAMENTAL_TEST(false, enum_uint16_t_UDT);
HAMON_IS_FUNDAMENTAL_TEST(false, enum_uint8_t_UDT);
HAMON_IS_FUNDAMENTAL_TEST(false, enum_int32_t_UDT);
HAMON_IS_FUNDAMENTAL_TEST(false, enum_int16_t_UDT);
HAMON_IS_FUNDAMENTAL_TEST(false, enum_int8_t_UDT);
HAMON_IS_FUNDAMENTAL_TEST(false, enum_class_UDT);
HAMON_IS_FUNDAMENTAL_TEST(false, enum_class_uint32_t_UDT);
HAMON_IS_FUNDAMENTAL_TEST(false, enum_class_uint16_t_UDT);
HAMON_IS_FUNDAMENTAL_TEST(false, enum_class_uint8_t_UDT);
HAMON_IS_FUNDAMENTAL_TEST(false, enum_class_int32_t_UDT);
HAMON_IS_FUNDAMENTAL_TEST(false, enum_class_int16_t_UDT);
HAMON_IS_FUNDAMENTAL_TEST(false, enum_class_int8_t_UDT);
HAMON_IS_FUNDAMENTAL_TEST(false, UDT);
HAMON_IS_FUNDAMENTAL_TEST(false, POD_UDT);
HAMON_IS_FUNDAMENTAL_TEST(false, empty_UDT);
HAMON_IS_FUNDAMENTAL_TEST(false, empty_POD_UDT);
HAMON_IS_FUNDAMENTAL_TEST(false, union_UDT);
HAMON_IS_FUNDAMENTAL_TEST(false, POD_union_UDT);
HAMON_IS_FUNDAMENTAL_TEST(false, empty_union_UDT);
HAMON_IS_FUNDAMENTAL_TEST(false, empty_POD_union_UDT);
HAMON_IS_FUNDAMENTAL_TEST(false, nothrow_default_ctor_UDT);
HAMON_IS_FUNDAMENTAL_TEST(false, nothrow_dtor_UDT);
HAMON_IS_FUNDAMENTAL_TEST(false, nothrow_copy_ctor_UDT);
HAMON_IS_FUNDAMENTAL_TEST(false, nothrow_copy_assign_UDT);
HAMON_IS_FUNDAMENTAL_TEST(false, nothrow_move_ctor_UDT);
HAMON_IS_FUNDAMENTAL_TEST(false, nothrow_move_assign_UDT);
HAMON_IS_FUNDAMENTAL_TEST(false, Base);
HAMON_IS_FUNDAMENTAL_TEST(false, Derived);
HAMON_IS_FUNDAMENTAL_TEST(false, Derived2);
HAMON_IS_FUNDAMENTAL_TEST(false, MultiBase);
HAMON_IS_FUNDAMENTAL_TEST(false, PrivateBase);
HAMON_IS_FUNDAMENTAL_TEST(false, NonDerived);
HAMON_IS_FUNDAMENTAL_TEST(false, enum1);
HAMON_IS_FUNDAMENTAL_TEST(false, enum2);
HAMON_IS_FUNDAMENTAL_TEST(false, VB);
HAMON_IS_FUNDAMENTAL_TEST(false, VD);
HAMON_IS_FUNDAMENTAL_TEST(false, non_pointer);
HAMON_IS_FUNDAMENTAL_TEST(false, non_int_pointer);
HAMON_IS_FUNDAMENTAL_TEST(false, int_constructible);
HAMON_IS_FUNDAMENTAL_TEST(false, int_convertible);
HAMON_IS_FUNDAMENTAL_TEST(false, test_abc1);
HAMON_IS_FUNDAMENTAL_TEST(false, test_abc2);
HAMON_IS_FUNDAMENTAL_TEST(false, test_abc3);
HAMON_IS_FUNDAMENTAL_TEST(false, incomplete_type);
HAMON_IS_FUNDAMENTAL_TEST(false, polymorphic_base);
HAMON_IS_FUNDAMENTAL_TEST(false, polymorphic_derived1);
HAMON_IS_FUNDAMENTAL_TEST(false, polymorphic_derived2);
HAMON_IS_FUNDAMENTAL_TEST(false, virtual_inherit1);
HAMON_IS_FUNDAMENTAL_TEST(false, virtual_inherit2);
HAMON_IS_FUNDAMENTAL_TEST(false, virtual_inherit3);
HAMON_IS_FUNDAMENTAL_TEST(false, virtual_inherit5);
HAMON_IS_FUNDAMENTAL_TEST(false, virtual_inherit6);
HAMON_IS_FUNDAMENTAL_TEST(false, trivial_except_construct);
HAMON_IS_FUNDAMENTAL_TEST(false, trivial_except_destroy);
HAMON_IS_FUNDAMENTAL_TEST(false, trivial_except_copy_ctor);
HAMON_IS_FUNDAMENTAL_TEST(false, trivial_except_move_ctor);
HAMON_IS_FUNDAMENTAL_TEST(false, trivial_except_copy_assign);
HAMON_IS_FUNDAMENTAL_TEST(false, trivial_except_move_assign);
HAMON_IS_FUNDAMENTAL_TEST(false, f1);
HAMON_IS_FUNDAMENTAL_TEST(false, f2);
HAMON_IS_FUNDAMENTAL_TEST(false, f3);
HAMON_IS_FUNDAMENTAL_TEST(false, mf1);
HAMON_IS_FUNDAMENTAL_TEST(false, mf2);
HAMON_IS_FUNDAMENTAL_TEST(false, mf3);
HAMON_IS_FUNDAMENTAL_TEST(false, mf4);
HAMON_IS_FUNDAMENTAL_TEST(false, mp);
HAMON_IS_FUNDAMENTAL_TEST(false, cmf);
HAMON_IS_FUNDAMENTAL_TEST(false, foo0_t);
HAMON_IS_FUNDAMENTAL_TEST(false, foo1_t);
HAMON_IS_FUNDAMENTAL_TEST(false, foo2_t);
HAMON_IS_FUNDAMENTAL_TEST(false, foo3_t);
HAMON_IS_FUNDAMENTAL_TEST(false, foo4_t);

#undef HAMON_IS_FUNDAMENTAL_TEST
