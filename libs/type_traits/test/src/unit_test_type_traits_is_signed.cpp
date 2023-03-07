/**
 *	@file	unit_test_type_traits_is_signed.cpp
 *
 *	@brief	is_signed のテスト
 */

#include <hamon/type_traits/is_signed.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/config.hpp>
#include <cstdint>	// WCHAR_MIN
#include <climits>	// CHAR_MIN
#include <cstddef>
#include <gtest/gtest.h>
#include "type_traits_test_utility.hpp"

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

#define HAMON_IS_SIGNED_TEST(b, T)	\
	static_assert(hamon::is_signed_v<T>      == b, #T);	\
	static_assert(hamon::is_signed<T>::value == b, #T);	\
	static_assert(hamon::is_signed<T>{}()    == b, #T);	\
	static_assert(hamon::is_signed<T>{}      == b, #T)

#else

#define HAMON_IS_SIGNED_TEST(b, T)	\
	static_assert(hamon::is_signed<T>::value == b, #T);	\
	static_assert(hamon::is_signed<T>{}()    == b, #T);	\
	static_assert(hamon::is_signed<T>{}      == b, #T)

#endif

HAMON_IS_SIGNED_TEST(true,                 int);
HAMON_IS_SIGNED_TEST(true,  const          int);
HAMON_IS_SIGNED_TEST(true,        volatile int);
HAMON_IS_SIGNED_TEST(true,  const volatile int);
HAMON_IS_SIGNED_TEST(false, int*);
HAMON_IS_SIGNED_TEST(false, int&);
HAMON_IS_SIGNED_TEST(false, int&&);
HAMON_IS_SIGNED_TEST(false, int[2]);
HAMON_IS_SIGNED_TEST(false, int[]);
HAMON_IS_SIGNED_TEST(false, int(*)[2]);
HAMON_IS_SIGNED_TEST(false, int(*)[]);
HAMON_IS_SIGNED_TEST(false, int(&)[2]);
HAMON_IS_SIGNED_TEST(false, int(&)[]);
HAMON_IS_SIGNED_TEST(false, int(&&)[2]);
HAMON_IS_SIGNED_TEST(false, int(&&)[]);

HAMON_IS_SIGNED_TEST(false, bool);
#if CHAR_MIN < 0
HAMON_IS_SIGNED_TEST(true, char);
#else
HAMON_IS_SIGNED_TEST(false, char);
#endif
#if WCHAR_MIN < 0
HAMON_IS_SIGNED_TEST(true, wchar_t);
#else
HAMON_IS_SIGNED_TEST(false, wchar_t);
#endif
HAMON_IS_SIGNED_TEST(true, signed char);
HAMON_IS_SIGNED_TEST(true, int);
HAMON_IS_SIGNED_TEST(true, short);
HAMON_IS_SIGNED_TEST(true, long);
HAMON_IS_SIGNED_TEST(true, long long);
HAMON_IS_SIGNED_TEST(false, unsigned char);
HAMON_IS_SIGNED_TEST(false, unsigned int);
HAMON_IS_SIGNED_TEST(false, unsigned short);
HAMON_IS_SIGNED_TEST(false, unsigned long);
HAMON_IS_SIGNED_TEST(false, unsigned long long);
HAMON_IS_SIGNED_TEST(false, hamon::size_t);
HAMON_IS_SIGNED_TEST(true, float);
HAMON_IS_SIGNED_TEST(true, double);
HAMON_IS_SIGNED_TEST(true, long double);
HAMON_IS_SIGNED_TEST(false, void);
HAMON_IS_SIGNED_TEST(false, void*);
HAMON_IS_SIGNED_TEST(false, std::nullptr_t);
HAMON_IS_SIGNED_TEST(false, decltype(nullptr));
HAMON_IS_SIGNED_TEST(false, enum_UDT);
HAMON_IS_SIGNED_TEST(false, enum_uint32_t_UDT);
HAMON_IS_SIGNED_TEST(false, enum_uint16_t_UDT);
HAMON_IS_SIGNED_TEST(false, enum_uint8_t_UDT);
HAMON_IS_SIGNED_TEST(false, enum_int32_t_UDT);
HAMON_IS_SIGNED_TEST(false, enum_int16_t_UDT);
HAMON_IS_SIGNED_TEST(false, enum_int8_t_UDT);
HAMON_IS_SIGNED_TEST(false, enum_class_UDT);
HAMON_IS_SIGNED_TEST(false, enum_class_uint32_t_UDT);
HAMON_IS_SIGNED_TEST(false, enum_class_uint16_t_UDT);
HAMON_IS_SIGNED_TEST(false, enum_class_uint8_t_UDT);
HAMON_IS_SIGNED_TEST(false, enum_class_int32_t_UDT);
HAMON_IS_SIGNED_TEST(false, enum_class_int16_t_UDT);
HAMON_IS_SIGNED_TEST(false, enum_class_int8_t_UDT);
HAMON_IS_SIGNED_TEST(false, UDT);
HAMON_IS_SIGNED_TEST(false, POD_UDT);
HAMON_IS_SIGNED_TEST(false, empty_UDT);
HAMON_IS_SIGNED_TEST(false, empty_POD_UDT);
HAMON_IS_SIGNED_TEST(false, union_UDT);
HAMON_IS_SIGNED_TEST(false, POD_union_UDT);
HAMON_IS_SIGNED_TEST(false, empty_union_UDT);
HAMON_IS_SIGNED_TEST(false, empty_POD_union_UDT);
HAMON_IS_SIGNED_TEST(false, nothrow_default_ctor_UDT);
HAMON_IS_SIGNED_TEST(false, nothrow_dtor_UDT);
HAMON_IS_SIGNED_TEST(false, nothrow_copy_ctor_UDT);
HAMON_IS_SIGNED_TEST(false, nothrow_copy_assign_UDT);
HAMON_IS_SIGNED_TEST(false, nothrow_move_ctor_UDT);
HAMON_IS_SIGNED_TEST(false, nothrow_move_assign_UDT);
HAMON_IS_SIGNED_TEST(false, Base);
HAMON_IS_SIGNED_TEST(false, Derived);
HAMON_IS_SIGNED_TEST(false, Derived2);
HAMON_IS_SIGNED_TEST(false, MultiBase);
HAMON_IS_SIGNED_TEST(false, PrivateBase);
HAMON_IS_SIGNED_TEST(false, NonDerived);
HAMON_IS_SIGNED_TEST(false, enum1);
HAMON_IS_SIGNED_TEST(false, enum2);
HAMON_IS_SIGNED_TEST(false, VB);
HAMON_IS_SIGNED_TEST(false, VD);
HAMON_IS_SIGNED_TEST(false, non_pointer);
HAMON_IS_SIGNED_TEST(false, non_int_pointer);
HAMON_IS_SIGNED_TEST(false, int_constructible);
HAMON_IS_SIGNED_TEST(false, int_convertible);
HAMON_IS_SIGNED_TEST(false, test_abc1);
HAMON_IS_SIGNED_TEST(false, test_abc2);
HAMON_IS_SIGNED_TEST(false, test_abc3);
HAMON_IS_SIGNED_TEST(false, incomplete_type);
HAMON_IS_SIGNED_TEST(false, polymorphic_base);
HAMON_IS_SIGNED_TEST(false, polymorphic_derived1);
HAMON_IS_SIGNED_TEST(false, polymorphic_derived2);
HAMON_IS_SIGNED_TEST(false, virtual_inherit1);
HAMON_IS_SIGNED_TEST(false, virtual_inherit2);
HAMON_IS_SIGNED_TEST(false, virtual_inherit3);
HAMON_IS_SIGNED_TEST(false, virtual_inherit5);
HAMON_IS_SIGNED_TEST(false, virtual_inherit6);
HAMON_IS_SIGNED_TEST(false, trivial_except_construct);
HAMON_IS_SIGNED_TEST(false, trivial_except_destroy);
HAMON_IS_SIGNED_TEST(false, trivial_except_copy_ctor);
HAMON_IS_SIGNED_TEST(false, trivial_except_move_ctor);
HAMON_IS_SIGNED_TEST(false, trivial_except_copy_assign);
HAMON_IS_SIGNED_TEST(false, trivial_except_move_assign);
HAMON_IS_SIGNED_TEST(false, f1);
HAMON_IS_SIGNED_TEST(false, f2);
HAMON_IS_SIGNED_TEST(false, f3);
HAMON_IS_SIGNED_TEST(false, mf1);
HAMON_IS_SIGNED_TEST(false, mf2);
HAMON_IS_SIGNED_TEST(false, mf3);
HAMON_IS_SIGNED_TEST(false, mf4);
HAMON_IS_SIGNED_TEST(false, mp);
HAMON_IS_SIGNED_TEST(false, cmf);
HAMON_IS_SIGNED_TEST(false, foo0_t);
HAMON_IS_SIGNED_TEST(false, foo1_t);
HAMON_IS_SIGNED_TEST(false, foo2_t);
HAMON_IS_SIGNED_TEST(false, foo3_t);
HAMON_IS_SIGNED_TEST(false, foo4_t);

#undef HAMON_IS_SIGNED_TEST
