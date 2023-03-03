/**
 *	@file	unit_test_type_traits_is_class.cpp
 *
 *	@brief	is_class のテスト
 */

#include <hamon/type_traits/is_class.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include <cstddef>
#include "type_traits_test_utility.hpp"

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

#define HAMON_IS_CLASS_TEST(b, T)	\
	static_assert(hamon::is_class_v<T>      == b, #T);	\
	static_assert(hamon::is_class<T>::value == b, #T);	\
	static_assert(hamon::is_class<T>{}()    == b, #T);	\
	static_assert(hamon::is_class<T>{}      == b, #T)

#else

#define HAMON_IS_CLASS_TEST(b, T)	\
	static_assert(hamon::is_class<T>::value == b, #T);	\
	static_assert(hamon::is_class<T>{}()    == b, #T);	\
	static_assert(hamon::is_class<T>{}      == b, #T)

#endif

HAMON_IS_CLASS_TEST(true,                 UDT);
HAMON_IS_CLASS_TEST(true,  const          UDT);
HAMON_IS_CLASS_TEST(true,        volatile UDT);
HAMON_IS_CLASS_TEST(true,  const volatile UDT);
HAMON_IS_CLASS_TEST(false, UDT*);
HAMON_IS_CLASS_TEST(false, UDT&);
HAMON_IS_CLASS_TEST(false, UDT&&);
HAMON_IS_CLASS_TEST(false, UDT[2]);
HAMON_IS_CLASS_TEST(false, UDT[]);
HAMON_IS_CLASS_TEST(false, UDT(*)[2]);
HAMON_IS_CLASS_TEST(false, UDT(*)[]);
HAMON_IS_CLASS_TEST(false, UDT(&)[2]);
HAMON_IS_CLASS_TEST(false, UDT(&)[]);
HAMON_IS_CLASS_TEST(false, UDT(&&)[2]);
HAMON_IS_CLASS_TEST(false, UDT(&&)[]);

HAMON_IS_CLASS_TEST(false,                void);
HAMON_IS_CLASS_TEST(false, const          void);
HAMON_IS_CLASS_TEST(false,       volatile void);
HAMON_IS_CLASS_TEST(false, const volatile void);

HAMON_IS_CLASS_TEST(false, bool);
HAMON_IS_CLASS_TEST(false, char);
HAMON_IS_CLASS_TEST(false, wchar_t);
HAMON_IS_CLASS_TEST(false, signed char);
HAMON_IS_CLASS_TEST(false, int);
HAMON_IS_CLASS_TEST(false, short);
HAMON_IS_CLASS_TEST(false, long);
HAMON_IS_CLASS_TEST(false, long long);
HAMON_IS_CLASS_TEST(false, unsigned char);
HAMON_IS_CLASS_TEST(false, unsigned int);
HAMON_IS_CLASS_TEST(false, unsigned short);
HAMON_IS_CLASS_TEST(false, unsigned long);
HAMON_IS_CLASS_TEST(false, unsigned long long);
HAMON_IS_CLASS_TEST(false, std::size_t);
HAMON_IS_CLASS_TEST(false, float);
HAMON_IS_CLASS_TEST(false, double);
HAMON_IS_CLASS_TEST(false, long double);
HAMON_IS_CLASS_TEST(false, void*);
HAMON_IS_CLASS_TEST(false, std::nullptr_t);
HAMON_IS_CLASS_TEST(false, decltype(nullptr));
HAMON_IS_CLASS_TEST(false, enum_UDT);
HAMON_IS_CLASS_TEST(false, enum_uint32_t_UDT);
HAMON_IS_CLASS_TEST(false, enum_uint16_t_UDT);
HAMON_IS_CLASS_TEST(false, enum_uint8_t_UDT);
HAMON_IS_CLASS_TEST(false, enum_int32_t_UDT);
HAMON_IS_CLASS_TEST(false, enum_int16_t_UDT);
HAMON_IS_CLASS_TEST(false, enum_int8_t_UDT);
HAMON_IS_CLASS_TEST(false, enum_class_UDT);
HAMON_IS_CLASS_TEST(false, enum_class_uint32_t_UDT);
HAMON_IS_CLASS_TEST(false, enum_class_uint16_t_UDT);
HAMON_IS_CLASS_TEST(false, enum_class_uint8_t_UDT);
HAMON_IS_CLASS_TEST(false, enum_class_int32_t_UDT);
HAMON_IS_CLASS_TEST(false, enum_class_int16_t_UDT);
HAMON_IS_CLASS_TEST(false, enum_class_int8_t_UDT);
HAMON_IS_CLASS_TEST(true,  UDT);
HAMON_IS_CLASS_TEST(true,  POD_UDT);
HAMON_IS_CLASS_TEST(true,  empty_UDT);
HAMON_IS_CLASS_TEST(true,  empty_POD_UDT);
HAMON_IS_CLASS_TEST(false, union_UDT);
HAMON_IS_CLASS_TEST(false, POD_union_UDT);
HAMON_IS_CLASS_TEST(false, empty_union_UDT);
HAMON_IS_CLASS_TEST(false, empty_POD_union_UDT);
HAMON_IS_CLASS_TEST(true,  nothrow_default_ctor_UDT);
HAMON_IS_CLASS_TEST(true,  nothrow_dtor_UDT);
HAMON_IS_CLASS_TEST(true,  nothrow_copy_ctor_UDT);
HAMON_IS_CLASS_TEST(true,  nothrow_copy_assign_UDT);
HAMON_IS_CLASS_TEST(true,  nothrow_move_ctor_UDT);
HAMON_IS_CLASS_TEST(true,  nothrow_move_assign_UDT);
HAMON_IS_CLASS_TEST(true,  Base);
HAMON_IS_CLASS_TEST(true,  Derived);
HAMON_IS_CLASS_TEST(true,  Derived2);
HAMON_IS_CLASS_TEST(true,  MultiBase);
HAMON_IS_CLASS_TEST(true,  PrivateBase);
HAMON_IS_CLASS_TEST(true,  NonDerived);
HAMON_IS_CLASS_TEST(false, enum1);
HAMON_IS_CLASS_TEST(false, enum2);
HAMON_IS_CLASS_TEST(true,  VB);
HAMON_IS_CLASS_TEST(true,  VD);
HAMON_IS_CLASS_TEST(true,  non_pointer);
HAMON_IS_CLASS_TEST(true,  non_int_pointer);
HAMON_IS_CLASS_TEST(true,  int_constructible);
HAMON_IS_CLASS_TEST(true,  int_convertible);
HAMON_IS_CLASS_TEST(true, test_abc1);
HAMON_IS_CLASS_TEST(true, test_abc2);
HAMON_IS_CLASS_TEST(true, test_abc3);
HAMON_IS_CLASS_TEST(true, incomplete_type);
HAMON_IS_CLASS_TEST(true, polymorphic_base);
HAMON_IS_CLASS_TEST(true, polymorphic_derived1);
HAMON_IS_CLASS_TEST(true, polymorphic_derived2);
HAMON_IS_CLASS_TEST(true, virtual_inherit1);
HAMON_IS_CLASS_TEST(true, virtual_inherit2);
HAMON_IS_CLASS_TEST(true, virtual_inherit3);
HAMON_IS_CLASS_TEST(true, virtual_inherit5);
HAMON_IS_CLASS_TEST(true, virtual_inherit6);
HAMON_IS_CLASS_TEST(true, trivial_except_construct);
HAMON_IS_CLASS_TEST(true, trivial_except_destroy);
HAMON_IS_CLASS_TEST(true, trivial_except_copy_ctor);
HAMON_IS_CLASS_TEST(true, trivial_except_move_ctor);
HAMON_IS_CLASS_TEST(true, trivial_except_copy_assign);
HAMON_IS_CLASS_TEST(true, trivial_except_move_assign);
HAMON_IS_CLASS_TEST(false, f1);
HAMON_IS_CLASS_TEST(false, f2);
HAMON_IS_CLASS_TEST(false, f3);
HAMON_IS_CLASS_TEST(false, mf1);
HAMON_IS_CLASS_TEST(false, mf2);
HAMON_IS_CLASS_TEST(false, mf3);
HAMON_IS_CLASS_TEST(false, mf4);
HAMON_IS_CLASS_TEST(false, mp);
HAMON_IS_CLASS_TEST(false, cmf);
HAMON_IS_CLASS_TEST(false, foo0_t);
HAMON_IS_CLASS_TEST(false, foo1_t);
HAMON_IS_CLASS_TEST(false, foo2_t);
HAMON_IS_CLASS_TEST(false, foo3_t);
HAMON_IS_CLASS_TEST(false, foo4_t);

#undef HAMON_IS_CLASS_TEST
