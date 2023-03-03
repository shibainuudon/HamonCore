/**
 *	@file	unit_test_type_traits_is_enum.cpp
 *
 *	@brief	is_enum のテスト
 */

#include <hamon/type_traits/is_enum.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include <cstddef>
#include "type_traits_test_utility.hpp"

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

#define HAMON_IS_ENUM_TEST(b, T)	\
	static_assert(hamon::is_enum_v<T>      == b, #T);	\
	static_assert(hamon::is_enum<T>::value == b, #T);	\
	static_assert(hamon::is_enum<T>{}()    == b, #T);	\
	static_assert(hamon::is_enum<T>{}      == b, #T)

#else

#define HAMON_IS_ENUM_TEST(b, T)	\
	static_assert(hamon::is_enum<T>::value == b, #T);	\
	static_assert(hamon::is_enum<T>{}()    == b, #T);	\
	static_assert(hamon::is_enum<T>{}      == b, #T)

#endif

HAMON_IS_ENUM_TEST(true,                 enum_UDT);
HAMON_IS_ENUM_TEST(true,  const          enum_UDT);
HAMON_IS_ENUM_TEST(true,        volatile enum_UDT);
HAMON_IS_ENUM_TEST(true,  const volatile enum_UDT);
HAMON_IS_ENUM_TEST(false, enum_UDT*);
HAMON_IS_ENUM_TEST(false, enum_UDT&);
HAMON_IS_ENUM_TEST(false, enum_UDT&&);
HAMON_IS_ENUM_TEST(false, enum_UDT[2]);
HAMON_IS_ENUM_TEST(false, enum_UDT[]);
HAMON_IS_ENUM_TEST(false, enum_UDT(*)[2]);
HAMON_IS_ENUM_TEST(false, enum_UDT(*)[]);
HAMON_IS_ENUM_TEST(false, enum_UDT(&)[2]);
HAMON_IS_ENUM_TEST(false, enum_UDT(&)[]);
HAMON_IS_ENUM_TEST(false, enum_UDT(&&)[2]);
HAMON_IS_ENUM_TEST(false, enum_UDT(&&)[]);

HAMON_IS_ENUM_TEST(false,                void);
HAMON_IS_ENUM_TEST(false, const          void);
HAMON_IS_ENUM_TEST(false,       volatile void);
HAMON_IS_ENUM_TEST(false, const volatile void);

HAMON_IS_ENUM_TEST(false,                int);
HAMON_IS_ENUM_TEST(false, const          int);
HAMON_IS_ENUM_TEST(false,       volatile int);
HAMON_IS_ENUM_TEST(false, const volatile int);

HAMON_IS_ENUM_TEST(false, bool);
HAMON_IS_ENUM_TEST(false, char);
HAMON_IS_ENUM_TEST(false, wchar_t);
HAMON_IS_ENUM_TEST(false, signed char);
HAMON_IS_ENUM_TEST(false, short);
HAMON_IS_ENUM_TEST(false, long);
HAMON_IS_ENUM_TEST(false, long long);
HAMON_IS_ENUM_TEST(false, unsigned char);
HAMON_IS_ENUM_TEST(false, unsigned int);
HAMON_IS_ENUM_TEST(false, unsigned short);
HAMON_IS_ENUM_TEST(false, unsigned long);
HAMON_IS_ENUM_TEST(false, unsigned long long);
HAMON_IS_ENUM_TEST(false, std::size_t);
HAMON_IS_ENUM_TEST(false, float);
HAMON_IS_ENUM_TEST(false, double);
HAMON_IS_ENUM_TEST(false, long double);
HAMON_IS_ENUM_TEST(false, void*);
HAMON_IS_ENUM_TEST(false, std::nullptr_t);
HAMON_IS_ENUM_TEST(false, decltype(nullptr));
HAMON_IS_ENUM_TEST(true,  enum_uint32_t_UDT);
HAMON_IS_ENUM_TEST(true,  enum_uint16_t_UDT);
HAMON_IS_ENUM_TEST(true,  enum_uint8_t_UDT);
HAMON_IS_ENUM_TEST(true,  enum_int32_t_UDT);
HAMON_IS_ENUM_TEST(true,  enum_int16_t_UDT);
HAMON_IS_ENUM_TEST(true,  enum_int8_t_UDT);
HAMON_IS_ENUM_TEST(true,  enum_class_UDT);
HAMON_IS_ENUM_TEST(true,  enum_class_uint32_t_UDT);
HAMON_IS_ENUM_TEST(true,  enum_class_uint16_t_UDT);
HAMON_IS_ENUM_TEST(true,  enum_class_uint8_t_UDT);
HAMON_IS_ENUM_TEST(true,  enum_class_int32_t_UDT);
HAMON_IS_ENUM_TEST(true,  enum_class_int16_t_UDT);
HAMON_IS_ENUM_TEST(true,  enum_class_int8_t_UDT);
HAMON_IS_ENUM_TEST(false, UDT);
HAMON_IS_ENUM_TEST(false, POD_UDT);
HAMON_IS_ENUM_TEST(false, empty_UDT);
HAMON_IS_ENUM_TEST(false, empty_POD_UDT);
HAMON_IS_ENUM_TEST(false, union_UDT);
HAMON_IS_ENUM_TEST(false, POD_union_UDT);
HAMON_IS_ENUM_TEST(false, empty_union_UDT);
HAMON_IS_ENUM_TEST(false, empty_POD_union_UDT);
HAMON_IS_ENUM_TEST(false, nothrow_default_ctor_UDT);
HAMON_IS_ENUM_TEST(false, nothrow_dtor_UDT);
HAMON_IS_ENUM_TEST(false, nothrow_copy_ctor_UDT);
HAMON_IS_ENUM_TEST(false, nothrow_copy_assign_UDT);
HAMON_IS_ENUM_TEST(false, nothrow_move_ctor_UDT);
HAMON_IS_ENUM_TEST(false, nothrow_move_assign_UDT);
HAMON_IS_ENUM_TEST(false, Base);
HAMON_IS_ENUM_TEST(false, Derived);
HAMON_IS_ENUM_TEST(false, Derived2);
HAMON_IS_ENUM_TEST(false, MultiBase);
HAMON_IS_ENUM_TEST(false, PrivateBase);
HAMON_IS_ENUM_TEST(false, NonDerived);
HAMON_IS_ENUM_TEST(true,  enum1);
HAMON_IS_ENUM_TEST(true,  enum2);
HAMON_IS_ENUM_TEST(false, VB);
HAMON_IS_ENUM_TEST(false, VD);
HAMON_IS_ENUM_TEST(false, non_pointer);
HAMON_IS_ENUM_TEST(false, non_int_pointer);
HAMON_IS_ENUM_TEST(false, int_constructible);
HAMON_IS_ENUM_TEST(false, int_convertible);
HAMON_IS_ENUM_TEST(false, test_abc1);
HAMON_IS_ENUM_TEST(false, test_abc2);
HAMON_IS_ENUM_TEST(false, test_abc3);
HAMON_IS_ENUM_TEST(false, incomplete_type);
HAMON_IS_ENUM_TEST(false, polymorphic_base);
HAMON_IS_ENUM_TEST(false, polymorphic_derived1);
HAMON_IS_ENUM_TEST(false, polymorphic_derived2);
HAMON_IS_ENUM_TEST(false, virtual_inherit1);
HAMON_IS_ENUM_TEST(false, virtual_inherit2);
HAMON_IS_ENUM_TEST(false, virtual_inherit3);
HAMON_IS_ENUM_TEST(false, virtual_inherit5);
HAMON_IS_ENUM_TEST(false, virtual_inherit6);
HAMON_IS_ENUM_TEST(false, trivial_except_construct);
HAMON_IS_ENUM_TEST(false, trivial_except_destroy);
HAMON_IS_ENUM_TEST(false, trivial_except_copy_ctor);
HAMON_IS_ENUM_TEST(false, trivial_except_move_ctor);
HAMON_IS_ENUM_TEST(false, trivial_except_copy_assign);
HAMON_IS_ENUM_TEST(false, trivial_except_move_assign);
HAMON_IS_ENUM_TEST(false, f1);
HAMON_IS_ENUM_TEST(false, f2);
HAMON_IS_ENUM_TEST(false, f3);
HAMON_IS_ENUM_TEST(false, mf1);
HAMON_IS_ENUM_TEST(false, mf2);
HAMON_IS_ENUM_TEST(false, mf3);
HAMON_IS_ENUM_TEST(false, mf4);
HAMON_IS_ENUM_TEST(false, mp);
HAMON_IS_ENUM_TEST(false, cmf);
HAMON_IS_ENUM_TEST(false, foo0_t);
HAMON_IS_ENUM_TEST(false, foo1_t);
HAMON_IS_ENUM_TEST(false, foo2_t);
HAMON_IS_ENUM_TEST(false, foo3_t);
HAMON_IS_ENUM_TEST(false, foo4_t);

#undef HAMON_IS_ENUM_TEST
