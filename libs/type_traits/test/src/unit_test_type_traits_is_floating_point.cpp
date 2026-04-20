/**
 *	@file	unit_test_type_traits_is_floating_point.cpp
 *
 *	@brief	is_floating_point のテスト
 */

#include <hamon/type_traits/is_floating_point.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/cstddef/nullptr_t.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "type_traits_test_utility.hpp"

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

#define HAMON_IS_FLOATING_POINT_TEST(b, T)	\
	static_assert(hamon::is_floating_point_v<T>      == b, #T);	\
	static_assert(hamon::is_floating_point<T>::value == b, #T);	\
	static_assert(hamon::is_floating_point<T>()      == b, #T)

#else

#define HAMON_IS_FLOATING_POINT_TEST(b, T)	\
	static_assert(hamon::is_floating_point<T>::value == b, #T);	\
	static_assert(hamon::is_floating_point<T>()      == b, #T)

#endif

#define HAMON_IS_FLOATING_POINT_TEST_CV(b, T)	\
	HAMON_IS_FLOATING_POINT_TEST(b,                T);	\
	HAMON_IS_FLOATING_POINT_TEST(b, const          T);	\
	HAMON_IS_FLOATING_POINT_TEST(b,       volatile T);	\
	HAMON_IS_FLOATING_POINT_TEST(b, const volatile T)

HAMON_IS_FLOATING_POINT_TEST_CV(true,  float);
HAMON_IS_FLOATING_POINT_TEST_CV(true,  double);
HAMON_IS_FLOATING_POINT_TEST_CV(true,  long double);

HAMON_IS_FLOATING_POINT_TEST_CV(false, float*);
HAMON_IS_FLOATING_POINT_TEST_CV(false, float&);
HAMON_IS_FLOATING_POINT_TEST_CV(false, float&&);
HAMON_IS_FLOATING_POINT_TEST_CV(false, float[2]);
HAMON_IS_FLOATING_POINT_TEST_CV(false, float[]);
HAMON_IS_FLOATING_POINT_TEST_CV(false, float(*)[2]);
HAMON_IS_FLOATING_POINT_TEST_CV(false, float(*)[]);
HAMON_IS_FLOATING_POINT_TEST_CV(false, float(&)[2]);
HAMON_IS_FLOATING_POINT_TEST_CV(false, float(&)[]);
HAMON_IS_FLOATING_POINT_TEST_CV(false, float(&&)[2]);
HAMON_IS_FLOATING_POINT_TEST_CV(false, float(&&)[]);

HAMON_IS_FLOATING_POINT_TEST_CV(false, void);

HAMON_IS_FLOATING_POINT_TEST_CV(false, bool);
HAMON_IS_FLOATING_POINT_TEST_CV(false, char);
HAMON_IS_FLOATING_POINT_TEST_CV(false, wchar_t);
#if defined(HAMON_HAS_CXX20_CHAR8_T)
HAMON_IS_FLOATING_POINT_TEST_CV(false, char8_t);
#endif
HAMON_IS_FLOATING_POINT_TEST_CV(false, char16_t);
HAMON_IS_FLOATING_POINT_TEST_CV(false, char32_t);
HAMON_IS_FLOATING_POINT_TEST_CV(false, signed char);
HAMON_IS_FLOATING_POINT_TEST_CV(false, short);
HAMON_IS_FLOATING_POINT_TEST_CV(false, int);
HAMON_IS_FLOATING_POINT_TEST_CV(false, long);
HAMON_IS_FLOATING_POINT_TEST_CV(false, long long);
HAMON_IS_FLOATING_POINT_TEST_CV(false, unsigned char);
HAMON_IS_FLOATING_POINT_TEST_CV(false, unsigned short);
HAMON_IS_FLOATING_POINT_TEST_CV(false, unsigned int);
HAMON_IS_FLOATING_POINT_TEST_CV(false, unsigned long);
HAMON_IS_FLOATING_POINT_TEST_CV(false, unsigned long long);
HAMON_IS_FLOATING_POINT_TEST_CV(false, hamon::size_t);
HAMON_IS_FLOATING_POINT_TEST_CV(false, void*);
HAMON_IS_FLOATING_POINT_TEST_CV(false, hamon::nullptr_t);
HAMON_IS_FLOATING_POINT_TEST_CV(false, decltype(nullptr));
HAMON_IS_FLOATING_POINT_TEST_CV(false, enum_UDT);
HAMON_IS_FLOATING_POINT_TEST_CV(false, enum_uint32_t_UDT);
HAMON_IS_FLOATING_POINT_TEST_CV(false, enum_uint16_t_UDT);
HAMON_IS_FLOATING_POINT_TEST_CV(false, enum_uint8_t_UDT);
HAMON_IS_FLOATING_POINT_TEST_CV(false, enum_int32_t_UDT);
HAMON_IS_FLOATING_POINT_TEST_CV(false, enum_int16_t_UDT);
HAMON_IS_FLOATING_POINT_TEST_CV(false, enum_int8_t_UDT);
HAMON_IS_FLOATING_POINT_TEST_CV(false, enum_class_UDT);
HAMON_IS_FLOATING_POINT_TEST_CV(false, enum_class_uint32_t_UDT);
HAMON_IS_FLOATING_POINT_TEST_CV(false, enum_class_uint16_t_UDT);
HAMON_IS_FLOATING_POINT_TEST_CV(false, enum_class_uint8_t_UDT);
HAMON_IS_FLOATING_POINT_TEST_CV(false, enum_class_int32_t_UDT);
HAMON_IS_FLOATING_POINT_TEST_CV(false, enum_class_int16_t_UDT);
HAMON_IS_FLOATING_POINT_TEST_CV(false, enum_class_int8_t_UDT);
HAMON_IS_FLOATING_POINT_TEST_CV(false, UDT);
HAMON_IS_FLOATING_POINT_TEST_CV(false, POD_UDT);
HAMON_IS_FLOATING_POINT_TEST_CV(false, empty_UDT);
HAMON_IS_FLOATING_POINT_TEST_CV(false, empty_POD_UDT);
HAMON_IS_FLOATING_POINT_TEST_CV(false, union_UDT);
HAMON_IS_FLOATING_POINT_TEST_CV(false, POD_union_UDT);
HAMON_IS_FLOATING_POINT_TEST_CV(false, empty_union_UDT);
HAMON_IS_FLOATING_POINT_TEST_CV(false, empty_POD_union_UDT);
HAMON_IS_FLOATING_POINT_TEST_CV(false, nothrow_default_ctor_UDT);
HAMON_IS_FLOATING_POINT_TEST_CV(false, nothrow_dtor_UDT);
HAMON_IS_FLOATING_POINT_TEST_CV(false, nothrow_copy_ctor_UDT);
HAMON_IS_FLOATING_POINT_TEST_CV(false, nothrow_copy_assign_UDT);
HAMON_IS_FLOATING_POINT_TEST_CV(false, nothrow_move_ctor_UDT);
HAMON_IS_FLOATING_POINT_TEST_CV(false, nothrow_move_assign_UDT);
HAMON_IS_FLOATING_POINT_TEST_CV(false, Base);
HAMON_IS_FLOATING_POINT_TEST_CV(false, Derived);
HAMON_IS_FLOATING_POINT_TEST_CV(false, Derived2);
HAMON_IS_FLOATING_POINT_TEST_CV(false, MultiBase);
HAMON_IS_FLOATING_POINT_TEST_CV(false, PrivateBase);
HAMON_IS_FLOATING_POINT_TEST_CV(false, NonDerived);
HAMON_IS_FLOATING_POINT_TEST_CV(false, enum1);
HAMON_IS_FLOATING_POINT_TEST_CV(false, enum2);
HAMON_IS_FLOATING_POINT_TEST_CV(false, VB);
HAMON_IS_FLOATING_POINT_TEST_CV(false, VD);
HAMON_IS_FLOATING_POINT_TEST_CV(false, non_pointer);
HAMON_IS_FLOATING_POINT_TEST_CV(false, non_int_pointer);
HAMON_IS_FLOATING_POINT_TEST_CV(false, int_constructible);
HAMON_IS_FLOATING_POINT_TEST_CV(false, int_convertible);
HAMON_IS_FLOATING_POINT_TEST_CV(false, test_abc1);
HAMON_IS_FLOATING_POINT_TEST_CV(false, test_abc2);
HAMON_IS_FLOATING_POINT_TEST_CV(false, test_abc3);
HAMON_IS_FLOATING_POINT_TEST_CV(false, incomplete_type);
HAMON_IS_FLOATING_POINT_TEST_CV(false, polymorphic_base);
HAMON_IS_FLOATING_POINT_TEST_CV(false, polymorphic_derived1);
HAMON_IS_FLOATING_POINT_TEST_CV(false, polymorphic_derived2);
HAMON_IS_FLOATING_POINT_TEST_CV(false, virtual_inherit1);
HAMON_IS_FLOATING_POINT_TEST_CV(false, virtual_inherit2);
HAMON_IS_FLOATING_POINT_TEST_CV(false, virtual_inherit3);
HAMON_IS_FLOATING_POINT_TEST_CV(false, virtual_inherit5);
HAMON_IS_FLOATING_POINT_TEST_CV(false, virtual_inherit6);
HAMON_IS_FLOATING_POINT_TEST_CV(false, trivial_except_construct);
HAMON_IS_FLOATING_POINT_TEST_CV(false, trivial_except_destroy);
HAMON_IS_FLOATING_POINT_TEST_CV(false, trivial_except_copy_ctor);
HAMON_IS_FLOATING_POINT_TEST_CV(false, trivial_except_move_ctor);
HAMON_IS_FLOATING_POINT_TEST_CV(false, trivial_except_copy_assign);
HAMON_IS_FLOATING_POINT_TEST_CV(false, trivial_except_move_assign);
HAMON_IS_FLOATING_POINT_TEST_CV(false, f1);
HAMON_IS_FLOATING_POINT_TEST_CV(false, f2);
HAMON_IS_FLOATING_POINT_TEST_CV(false, f3);
HAMON_IS_FLOATING_POINT_TEST_CV(false, mf1);
HAMON_IS_FLOATING_POINT_TEST_CV(false, mf2);
HAMON_IS_FLOATING_POINT_TEST_CV(false, mf3);
HAMON_IS_FLOATING_POINT_TEST_CV(false, mf4);
HAMON_IS_FLOATING_POINT_TEST_CV(false, mp);
HAMON_IS_FLOATING_POINT_TEST_CV(false, cmf);
HAMON_IS_FLOATING_POINT_TEST(false, foo0_t);
HAMON_IS_FLOATING_POINT_TEST(false, foo1_t);
HAMON_IS_FLOATING_POINT_TEST(false, foo2_t);
HAMON_IS_FLOATING_POINT_TEST(false, foo3_t);
HAMON_IS_FLOATING_POINT_TEST(false, foo4_t);

#undef HAMON_IS_FLOATING_POINT_TEST
#undef HAMON_IS_FLOATING_POINT_TEST_CV
