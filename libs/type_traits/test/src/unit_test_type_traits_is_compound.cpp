/**
 *	@file	unit_test_type_traits_is_compound.cpp
 *
 *	@brief	is_compound のテスト
 */

#include <hamon/type_traits/is_compound.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include <cstddef>
#include "type_traits_test_utility.hpp"

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

#define HAMON_IS_COMPOUND_TEST(b, T)	\
	static_assert(hamon::is_compound_v<T>      == b, #T);	\
	static_assert(hamon::is_compound<T>::value == b, #T);	\
	static_assert(hamon::is_compound<T>{}()    == b, #T);	\
	static_assert(hamon::is_compound<T>{}      == b, #T)

#else

#define HAMON_IS_COMPOUND_TEST(b, T)	\
	static_assert(hamon::is_compound<T>::value == b, #T);	\
	static_assert(hamon::is_compound<T>{}()    == b, #T);	\
	static_assert(hamon::is_compound<T>{}      == b, #T)

#endif

HAMON_IS_COMPOUND_TEST(false,                int);
HAMON_IS_COMPOUND_TEST(false, const          int);
HAMON_IS_COMPOUND_TEST(false,       volatile int);
HAMON_IS_COMPOUND_TEST(false, const volatile int);
HAMON_IS_COMPOUND_TEST(true,  int*);
HAMON_IS_COMPOUND_TEST(true,  int&);
HAMON_IS_COMPOUND_TEST(true,  int&&);
HAMON_IS_COMPOUND_TEST(true,  int[2]);
HAMON_IS_COMPOUND_TEST(true,  int[]);
HAMON_IS_COMPOUND_TEST(true,  int(&)[2]);
HAMON_IS_COMPOUND_TEST(true,  int(&)[]);
HAMON_IS_COMPOUND_TEST(true,  int(&&)[2]);
HAMON_IS_COMPOUND_TEST(true,  int(&&)[]);

HAMON_IS_COMPOUND_TEST(false,                void);
HAMON_IS_COMPOUND_TEST(false, const          void);
HAMON_IS_COMPOUND_TEST(false,       volatile void);
HAMON_IS_COMPOUND_TEST(false, const volatile void);

HAMON_IS_COMPOUND_TEST(false, bool);
HAMON_IS_COMPOUND_TEST(false, char);
HAMON_IS_COMPOUND_TEST(false, wchar_t);
HAMON_IS_COMPOUND_TEST(false, signed char);
HAMON_IS_COMPOUND_TEST(false, short);
HAMON_IS_COMPOUND_TEST(false, long);
HAMON_IS_COMPOUND_TEST(false, long long);
HAMON_IS_COMPOUND_TEST(false, unsigned char);
HAMON_IS_COMPOUND_TEST(false, unsigned int);
HAMON_IS_COMPOUND_TEST(false, unsigned short);
HAMON_IS_COMPOUND_TEST(false, unsigned long);
HAMON_IS_COMPOUND_TEST(false, unsigned long long);
HAMON_IS_COMPOUND_TEST(false, hamon::size_t);
HAMON_IS_COMPOUND_TEST(false, float);
HAMON_IS_COMPOUND_TEST(false, double);
HAMON_IS_COMPOUND_TEST(false, long double);
HAMON_IS_COMPOUND_TEST(false, std::nullptr_t);
HAMON_IS_COMPOUND_TEST(false, decltype(nullptr));

HAMON_IS_COMPOUND_TEST(true,                 UDT);
HAMON_IS_COMPOUND_TEST(true,  const          UDT);
HAMON_IS_COMPOUND_TEST(true,        volatile UDT);
HAMON_IS_COMPOUND_TEST(true,  const volatile UDT);
HAMON_IS_COMPOUND_TEST(true,  UDT*);
HAMON_IS_COMPOUND_TEST(true,  UDT&);
HAMON_IS_COMPOUND_TEST(true,  UDT&&);
HAMON_IS_COMPOUND_TEST(true,  UDT[2]);
HAMON_IS_COMPOUND_TEST(true,  UDT[]);
HAMON_IS_COMPOUND_TEST(true,  UDT(&)[2]);
HAMON_IS_COMPOUND_TEST(true,  UDT(&)[]);
HAMON_IS_COMPOUND_TEST(true,  UDT(&&)[2]);
HAMON_IS_COMPOUND_TEST(true,  UDT(&&)[]);

HAMON_IS_COMPOUND_TEST(true, void*);
HAMON_IS_COMPOUND_TEST(true, enum_UDT);
HAMON_IS_COMPOUND_TEST(true, enum_uint32_t_UDT);
HAMON_IS_COMPOUND_TEST(true, enum_uint16_t_UDT);
HAMON_IS_COMPOUND_TEST(true, enum_uint8_t_UDT);
HAMON_IS_COMPOUND_TEST(true, enum_int32_t_UDT);
HAMON_IS_COMPOUND_TEST(true, enum_int16_t_UDT);
HAMON_IS_COMPOUND_TEST(true, enum_int8_t_UDT);
HAMON_IS_COMPOUND_TEST(true, enum_class_UDT);
HAMON_IS_COMPOUND_TEST(true, enum_class_uint32_t_UDT);
HAMON_IS_COMPOUND_TEST(true, enum_class_uint16_t_UDT);
HAMON_IS_COMPOUND_TEST(true, enum_class_uint8_t_UDT);
HAMON_IS_COMPOUND_TEST(true, enum_class_int32_t_UDT);
HAMON_IS_COMPOUND_TEST(true, enum_class_int16_t_UDT);
HAMON_IS_COMPOUND_TEST(true, enum_class_int8_t_UDT);
HAMON_IS_COMPOUND_TEST(true, UDT);
HAMON_IS_COMPOUND_TEST(true, POD_UDT);
HAMON_IS_COMPOUND_TEST(true, empty_UDT);
HAMON_IS_COMPOUND_TEST(true, empty_POD_UDT);
HAMON_IS_COMPOUND_TEST(true, union_UDT);
HAMON_IS_COMPOUND_TEST(true, POD_union_UDT);
HAMON_IS_COMPOUND_TEST(true, empty_union_UDT);
HAMON_IS_COMPOUND_TEST(true, empty_POD_union_UDT);
HAMON_IS_COMPOUND_TEST(true, nothrow_default_ctor_UDT);
HAMON_IS_COMPOUND_TEST(true, nothrow_dtor_UDT);
HAMON_IS_COMPOUND_TEST(true, nothrow_copy_ctor_UDT);
HAMON_IS_COMPOUND_TEST(true, nothrow_copy_assign_UDT);
HAMON_IS_COMPOUND_TEST(true, nothrow_move_ctor_UDT);
HAMON_IS_COMPOUND_TEST(true, nothrow_move_assign_UDT);
HAMON_IS_COMPOUND_TEST(true, Base);
HAMON_IS_COMPOUND_TEST(true, Derived);
HAMON_IS_COMPOUND_TEST(true, Derived2);
HAMON_IS_COMPOUND_TEST(true, MultiBase);
HAMON_IS_COMPOUND_TEST(true, PrivateBase);
HAMON_IS_COMPOUND_TEST(true, NonDerived);
HAMON_IS_COMPOUND_TEST(true, enum1);
HAMON_IS_COMPOUND_TEST(true, enum2);
HAMON_IS_COMPOUND_TEST(true, VB);
HAMON_IS_COMPOUND_TEST(true, VD);
HAMON_IS_COMPOUND_TEST(true, non_pointer);
HAMON_IS_COMPOUND_TEST(true, non_int_pointer);
HAMON_IS_COMPOUND_TEST(true, int_constructible);
HAMON_IS_COMPOUND_TEST(true, int_convertible);
HAMON_IS_COMPOUND_TEST(true, test_abc1);
HAMON_IS_COMPOUND_TEST(true, test_abc2);
HAMON_IS_COMPOUND_TEST(true, test_abc3);
HAMON_IS_COMPOUND_TEST(true, incomplete_type);
HAMON_IS_COMPOUND_TEST(true, polymorphic_base);
HAMON_IS_COMPOUND_TEST(true, polymorphic_derived1);
HAMON_IS_COMPOUND_TEST(true, polymorphic_derived2);
HAMON_IS_COMPOUND_TEST(true, virtual_inherit1);
HAMON_IS_COMPOUND_TEST(true, virtual_inherit2);
HAMON_IS_COMPOUND_TEST(true, virtual_inherit3);
HAMON_IS_COMPOUND_TEST(true, virtual_inherit5);
HAMON_IS_COMPOUND_TEST(true, virtual_inherit6);
HAMON_IS_COMPOUND_TEST(true, trivial_except_construct);
HAMON_IS_COMPOUND_TEST(true, trivial_except_destroy);
HAMON_IS_COMPOUND_TEST(true, trivial_except_copy_ctor);
HAMON_IS_COMPOUND_TEST(true, trivial_except_move_ctor);
HAMON_IS_COMPOUND_TEST(true, trivial_except_copy_assign);
HAMON_IS_COMPOUND_TEST(true, trivial_except_move_assign);
HAMON_IS_COMPOUND_TEST(true, f1);
HAMON_IS_COMPOUND_TEST(true, f2);
HAMON_IS_COMPOUND_TEST(true, f3);
HAMON_IS_COMPOUND_TEST(true, mf1);
HAMON_IS_COMPOUND_TEST(true, mf2);
HAMON_IS_COMPOUND_TEST(true, mf3);
HAMON_IS_COMPOUND_TEST(true, mf4);
HAMON_IS_COMPOUND_TEST(true, mp);
HAMON_IS_COMPOUND_TEST(true, cmf);
HAMON_IS_COMPOUND_TEST(true, foo0_t);
HAMON_IS_COMPOUND_TEST(true, foo1_t);
HAMON_IS_COMPOUND_TEST(true, foo2_t);
HAMON_IS_COMPOUND_TEST(true, foo3_t);
HAMON_IS_COMPOUND_TEST(true, foo4_t);

#undef HAMON_IS_COMPOUND_TEST
