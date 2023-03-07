/**
 *	@file	unit_test_type_traits_has_virtual_destructor.cpp
 *
 *	@brief	has_virtual_destructor のテスト
 */

#include <hamon/type_traits/has_virtual_destructor.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include <cstddef>
#include "type_traits_test_utility.hpp"

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

#define HAMON_HAS_VIRTUAL_DESTRUCTOR_TEST(b, T)	\
	static_assert(hamon::has_virtual_destructor_v<T>      == b, #T);	\
	static_assert(hamon::has_virtual_destructor<T>::value == b, #T);	\
	static_assert(hamon::has_virtual_destructor<T>{}()    == b, #T);	\
	static_assert(hamon::has_virtual_destructor<T>{}      == b, #T)

#else

#define HAMON_HAS_VIRTUAL_DESTRUCTOR_TEST(b, T)	\
	static_assert(hamon::has_virtual_destructor<T>::value == b, #T);	\
	static_assert(hamon::has_virtual_destructor<T>{}()    == b, #T);	\
	static_assert(hamon::has_virtual_destructor<T>{}      == b, #T)

#endif

HAMON_HAS_VIRTUAL_DESTRUCTOR_TEST(false,                int);
HAMON_HAS_VIRTUAL_DESTRUCTOR_TEST(false, const          int);
HAMON_HAS_VIRTUAL_DESTRUCTOR_TEST(false,       volatile int);
HAMON_HAS_VIRTUAL_DESTRUCTOR_TEST(false, const volatile int);
HAMON_HAS_VIRTUAL_DESTRUCTOR_TEST(false, int*);
HAMON_HAS_VIRTUAL_DESTRUCTOR_TEST(false, int&);
HAMON_HAS_VIRTUAL_DESTRUCTOR_TEST(false, int&&);
HAMON_HAS_VIRTUAL_DESTRUCTOR_TEST(false, int[2]);
HAMON_HAS_VIRTUAL_DESTRUCTOR_TEST(false, int[]);
HAMON_HAS_VIRTUAL_DESTRUCTOR_TEST(false, int(*)[2]);
HAMON_HAS_VIRTUAL_DESTRUCTOR_TEST(false, int(*)[]);
HAMON_HAS_VIRTUAL_DESTRUCTOR_TEST(false, int(&)[2]);
HAMON_HAS_VIRTUAL_DESTRUCTOR_TEST(false, int(&)[]);
HAMON_HAS_VIRTUAL_DESTRUCTOR_TEST(false, int(&&)[2]);
HAMON_HAS_VIRTUAL_DESTRUCTOR_TEST(false, int(&&)[]);

HAMON_HAS_VIRTUAL_DESTRUCTOR_TEST(true,                 VB);
HAMON_HAS_VIRTUAL_DESTRUCTOR_TEST(true,  const          VB);
HAMON_HAS_VIRTUAL_DESTRUCTOR_TEST(true,        volatile VB);
HAMON_HAS_VIRTUAL_DESTRUCTOR_TEST(true,  const volatile VB);
HAMON_HAS_VIRTUAL_DESTRUCTOR_TEST(false, VB*);
HAMON_HAS_VIRTUAL_DESTRUCTOR_TEST(false, VB&);
HAMON_HAS_VIRTUAL_DESTRUCTOR_TEST(false, VB&&);
HAMON_HAS_VIRTUAL_DESTRUCTOR_TEST(false, VB[2]);
HAMON_HAS_VIRTUAL_DESTRUCTOR_TEST(false, VB[]);
HAMON_HAS_VIRTUAL_DESTRUCTOR_TEST(false, VB(*)[2]);
HAMON_HAS_VIRTUAL_DESTRUCTOR_TEST(false, VB(*)[]);
HAMON_HAS_VIRTUAL_DESTRUCTOR_TEST(false, VB(&)[2]);
HAMON_HAS_VIRTUAL_DESTRUCTOR_TEST(false, VB(&)[]);
HAMON_HAS_VIRTUAL_DESTRUCTOR_TEST(false, VB(&&)[2]);
HAMON_HAS_VIRTUAL_DESTRUCTOR_TEST(false, VB(&&)[]);

HAMON_HAS_VIRTUAL_DESTRUCTOR_TEST(false,                void);
HAMON_HAS_VIRTUAL_DESTRUCTOR_TEST(false, const          void);
HAMON_HAS_VIRTUAL_DESTRUCTOR_TEST(false,       volatile void);
HAMON_HAS_VIRTUAL_DESTRUCTOR_TEST(false, const volatile int);

HAMON_HAS_VIRTUAL_DESTRUCTOR_TEST(false, bool);
HAMON_HAS_VIRTUAL_DESTRUCTOR_TEST(false, char);
HAMON_HAS_VIRTUAL_DESTRUCTOR_TEST(false, wchar_t);
HAMON_HAS_VIRTUAL_DESTRUCTOR_TEST(false, signed char);
HAMON_HAS_VIRTUAL_DESTRUCTOR_TEST(false, int);
HAMON_HAS_VIRTUAL_DESTRUCTOR_TEST(false, short);
HAMON_HAS_VIRTUAL_DESTRUCTOR_TEST(false, long);
HAMON_HAS_VIRTUAL_DESTRUCTOR_TEST(false, long long);
HAMON_HAS_VIRTUAL_DESTRUCTOR_TEST(false, unsigned char);
HAMON_HAS_VIRTUAL_DESTRUCTOR_TEST(false, unsigned int);
HAMON_HAS_VIRTUAL_DESTRUCTOR_TEST(false, unsigned short);
HAMON_HAS_VIRTUAL_DESTRUCTOR_TEST(false, unsigned long);
HAMON_HAS_VIRTUAL_DESTRUCTOR_TEST(false, unsigned long long);
HAMON_HAS_VIRTUAL_DESTRUCTOR_TEST(false, hamon::size_t);
HAMON_HAS_VIRTUAL_DESTRUCTOR_TEST(false, float);
HAMON_HAS_VIRTUAL_DESTRUCTOR_TEST(false, double);
HAMON_HAS_VIRTUAL_DESTRUCTOR_TEST(false, long double);
HAMON_HAS_VIRTUAL_DESTRUCTOR_TEST(false, void*);
HAMON_HAS_VIRTUAL_DESTRUCTOR_TEST(false, std::nullptr_t);
HAMON_HAS_VIRTUAL_DESTRUCTOR_TEST(false, decltype(nullptr));
HAMON_HAS_VIRTUAL_DESTRUCTOR_TEST(false, enum_UDT);
HAMON_HAS_VIRTUAL_DESTRUCTOR_TEST(false, enum_uint32_t_UDT);
HAMON_HAS_VIRTUAL_DESTRUCTOR_TEST(false, enum_uint16_t_UDT);
HAMON_HAS_VIRTUAL_DESTRUCTOR_TEST(false, enum_uint8_t_UDT);
HAMON_HAS_VIRTUAL_DESTRUCTOR_TEST(false, enum_int32_t_UDT);
HAMON_HAS_VIRTUAL_DESTRUCTOR_TEST(false, enum_int16_t_UDT);
HAMON_HAS_VIRTUAL_DESTRUCTOR_TEST(false, enum_int8_t_UDT);
HAMON_HAS_VIRTUAL_DESTRUCTOR_TEST(false, enum_class_UDT);
HAMON_HAS_VIRTUAL_DESTRUCTOR_TEST(false, enum_class_uint32_t_UDT);
HAMON_HAS_VIRTUAL_DESTRUCTOR_TEST(false, enum_class_uint16_t_UDT);
HAMON_HAS_VIRTUAL_DESTRUCTOR_TEST(false, enum_class_uint8_t_UDT);
HAMON_HAS_VIRTUAL_DESTRUCTOR_TEST(false, enum_class_int32_t_UDT);
HAMON_HAS_VIRTUAL_DESTRUCTOR_TEST(false, enum_class_int16_t_UDT);
HAMON_HAS_VIRTUAL_DESTRUCTOR_TEST(false, enum_class_int8_t_UDT);
HAMON_HAS_VIRTUAL_DESTRUCTOR_TEST(false, UDT);
HAMON_HAS_VIRTUAL_DESTRUCTOR_TEST(false, POD_UDT);
HAMON_HAS_VIRTUAL_DESTRUCTOR_TEST(false, empty_UDT);
HAMON_HAS_VIRTUAL_DESTRUCTOR_TEST(false, empty_POD_UDT);
HAMON_HAS_VIRTUAL_DESTRUCTOR_TEST(false, union_UDT);
HAMON_HAS_VIRTUAL_DESTRUCTOR_TEST(false, POD_union_UDT);
HAMON_HAS_VIRTUAL_DESTRUCTOR_TEST(false, empty_union_UDT);
HAMON_HAS_VIRTUAL_DESTRUCTOR_TEST(false, empty_POD_union_UDT);
HAMON_HAS_VIRTUAL_DESTRUCTOR_TEST(false, nothrow_default_ctor_UDT);
HAMON_HAS_VIRTUAL_DESTRUCTOR_TEST(false, nothrow_dtor_UDT);
HAMON_HAS_VIRTUAL_DESTRUCTOR_TEST(false, nothrow_copy_ctor_UDT);
HAMON_HAS_VIRTUAL_DESTRUCTOR_TEST(false, nothrow_copy_assign_UDT);
HAMON_HAS_VIRTUAL_DESTRUCTOR_TEST(false, nothrow_move_ctor_UDT);
HAMON_HAS_VIRTUAL_DESTRUCTOR_TEST(false, nothrow_move_assign_UDT);
HAMON_HAS_VIRTUAL_DESTRUCTOR_TEST(false, Base);
HAMON_HAS_VIRTUAL_DESTRUCTOR_TEST(false, Derived);
HAMON_HAS_VIRTUAL_DESTRUCTOR_TEST(false, Derived2);
HAMON_HAS_VIRTUAL_DESTRUCTOR_TEST(false, MultiBase);
HAMON_HAS_VIRTUAL_DESTRUCTOR_TEST(false, PrivateBase);
HAMON_HAS_VIRTUAL_DESTRUCTOR_TEST(false, NonDerived);
HAMON_HAS_VIRTUAL_DESTRUCTOR_TEST(false, enum1);
HAMON_HAS_VIRTUAL_DESTRUCTOR_TEST(false, enum2);
HAMON_HAS_VIRTUAL_DESTRUCTOR_TEST(true,  VB);
HAMON_HAS_VIRTUAL_DESTRUCTOR_TEST(true,  VD);
HAMON_HAS_VIRTUAL_DESTRUCTOR_TEST(false, non_pointer);
HAMON_HAS_VIRTUAL_DESTRUCTOR_TEST(false, non_int_pointer);
HAMON_HAS_VIRTUAL_DESTRUCTOR_TEST(false, int_constructible);
HAMON_HAS_VIRTUAL_DESTRUCTOR_TEST(false, int_convertible);
HAMON_HAS_VIRTUAL_DESTRUCTOR_TEST(true,  test_abc1);
HAMON_HAS_VIRTUAL_DESTRUCTOR_TEST(false, test_abc2);
HAMON_HAS_VIRTUAL_DESTRUCTOR_TEST(true,  test_abc3);
HAMON_HAS_VIRTUAL_DESTRUCTOR_TEST(false, test_concrete1);
HAMON_HAS_VIRTUAL_DESTRUCTOR_TEST(true,  test_concrete2);
//HAMON_HAS_VIRTUAL_DESTRUCTOR_TEST(false, incomplete_type);
HAMON_HAS_VIRTUAL_DESTRUCTOR_TEST(true,  polymorphic_base);
HAMON_HAS_VIRTUAL_DESTRUCTOR_TEST(true,  polymorphic_derived1);
HAMON_HAS_VIRTUAL_DESTRUCTOR_TEST(true,  polymorphic_derived2);
HAMON_HAS_VIRTUAL_DESTRUCTOR_TEST(false, virtual_inherit1);
HAMON_HAS_VIRTUAL_DESTRUCTOR_TEST(false, virtual_inherit2);
HAMON_HAS_VIRTUAL_DESTRUCTOR_TEST(false, virtual_inherit3);
HAMON_HAS_VIRTUAL_DESTRUCTOR_TEST(false, virtual_inherit5);
HAMON_HAS_VIRTUAL_DESTRUCTOR_TEST(true,  virtual_inherit6);
HAMON_HAS_VIRTUAL_DESTRUCTOR_TEST(false, trivial_except_construct);
HAMON_HAS_VIRTUAL_DESTRUCTOR_TEST(false, trivial_except_destroy);
HAMON_HAS_VIRTUAL_DESTRUCTOR_TEST(false, trivial_except_copy_ctor);
HAMON_HAS_VIRTUAL_DESTRUCTOR_TEST(false, trivial_except_move_ctor);
HAMON_HAS_VIRTUAL_DESTRUCTOR_TEST(false, trivial_except_copy_assign);
HAMON_HAS_VIRTUAL_DESTRUCTOR_TEST(false, trivial_except_move_assign);
HAMON_HAS_VIRTUAL_DESTRUCTOR_TEST(false, f1);
HAMON_HAS_VIRTUAL_DESTRUCTOR_TEST(false, f2);
HAMON_HAS_VIRTUAL_DESTRUCTOR_TEST(false, f3);
HAMON_HAS_VIRTUAL_DESTRUCTOR_TEST(false, mf1);
HAMON_HAS_VIRTUAL_DESTRUCTOR_TEST(false, mf2);
HAMON_HAS_VIRTUAL_DESTRUCTOR_TEST(false, mf3);
HAMON_HAS_VIRTUAL_DESTRUCTOR_TEST(false, mf4);
HAMON_HAS_VIRTUAL_DESTRUCTOR_TEST(false, mp);
HAMON_HAS_VIRTUAL_DESTRUCTOR_TEST(false, cmf);
HAMON_HAS_VIRTUAL_DESTRUCTOR_TEST(false, foo0_t);
HAMON_HAS_VIRTUAL_DESTRUCTOR_TEST(false, foo1_t);
HAMON_HAS_VIRTUAL_DESTRUCTOR_TEST(false, foo2_t);
HAMON_HAS_VIRTUAL_DESTRUCTOR_TEST(false, foo3_t);
HAMON_HAS_VIRTUAL_DESTRUCTOR_TEST(false, foo4_t);

#undef HAMON_HAS_VIRTUAL_DESTRUCTOR_TEST
