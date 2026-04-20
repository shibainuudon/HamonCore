/**
 *	@file	unit_test_type_traits_is_trivial.cpp
 *
 *	@brief	is_trivial のテスト
 */

#include <hamon/type_traits/is_trivial.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/cstddef/nullptr_t.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "type_traits_test_utility.hpp"

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

#define HAMON_IS_TRIVIAL_TEST(b, T)	\
	static_assert(hamon::is_trivial_v<T>      == b, #T);	\
	static_assert(hamon::is_trivial<T>::value == b, #T);	\
	static_assert(hamon::is_trivial<T>{}()    == b, #T);	\
	static_assert(hamon::is_trivial<T>{}      == b, #T)

#else

#define HAMON_IS_TRIVIAL_TEST(b, T)	\
	static_assert(hamon::is_trivial<T>::value == b, #T);	\
	static_assert(hamon::is_trivial<T>{}()    == b, #T);	\
	static_assert(hamon::is_trivial<T>{}      == b, #T)

#endif

#define HAMON_IS_TRIVIAL_TEST_CV(b, T)	\
	HAMON_IS_TRIVIAL_TEST(b,                T);	\
	HAMON_IS_TRIVIAL_TEST(b, const          T);	\
	HAMON_IS_TRIVIAL_TEST(b,       volatile T);	\
	HAMON_IS_TRIVIAL_TEST(b, const volatile T)

HAMON_IS_TRIVIAL_TEST_CV(true,  int);
HAMON_IS_TRIVIAL_TEST_CV(true,  int*);
HAMON_IS_TRIVIAL_TEST_CV(false, int&);
HAMON_IS_TRIVIAL_TEST_CV(false, int&&);
HAMON_IS_TRIVIAL_TEST_CV(true,  int[2]);
//HAMON_IS_TRIVIAL_TEST_CV(true,  int[]);
HAMON_IS_TRIVIAL_TEST_CV(true,  int(*)[2]);
HAMON_IS_TRIVIAL_TEST_CV(true,  int(*)[]);
HAMON_IS_TRIVIAL_TEST_CV(false, int(&)[2]);
HAMON_IS_TRIVIAL_TEST_CV(false, int(&)[]);
HAMON_IS_TRIVIAL_TEST_CV(false, int(&&)[2]);
HAMON_IS_TRIVIAL_TEST_CV(false, int(&&)[]);

HAMON_IS_TRIVIAL_TEST_CV(false, UDT);
HAMON_IS_TRIVIAL_TEST_CV(true,  UDT*);
HAMON_IS_TRIVIAL_TEST_CV(false, UDT&);
HAMON_IS_TRIVIAL_TEST_CV(false, UDT&&);
HAMON_IS_TRIVIAL_TEST_CV(false, UDT[2]);
HAMON_IS_TRIVIAL_TEST_CV(false, UDT[]);
HAMON_IS_TRIVIAL_TEST_CV(true,  UDT(*)[2]);
HAMON_IS_TRIVIAL_TEST_CV(true,  UDT(*)[]);
HAMON_IS_TRIVIAL_TEST_CV(false, UDT(&)[2]);
HAMON_IS_TRIVIAL_TEST_CV(false, UDT(&)[]);
HAMON_IS_TRIVIAL_TEST_CV(false, UDT(&&)[2]);
HAMON_IS_TRIVIAL_TEST_CV(false, UDT(&&)[]);

HAMON_IS_TRIVIAL_TEST_CV(true,  POD_UDT);
HAMON_IS_TRIVIAL_TEST_CV(true,  POD_UDT*);
HAMON_IS_TRIVIAL_TEST_CV(false, POD_UDT&);
HAMON_IS_TRIVIAL_TEST_CV(false, POD_UDT&&);
HAMON_IS_TRIVIAL_TEST_CV(true,  POD_UDT[2]);
//HAMON_IS_TRIVIAL_TEST_CV(true,  POD_UDT[]);
HAMON_IS_TRIVIAL_TEST_CV(true,  POD_UDT(*)[2]);
HAMON_IS_TRIVIAL_TEST_CV(true,  POD_UDT(*)[]);
HAMON_IS_TRIVIAL_TEST_CV(false, POD_UDT(&)[2]);
HAMON_IS_TRIVIAL_TEST_CV(false, POD_UDT(&)[]);
HAMON_IS_TRIVIAL_TEST_CV(false, POD_UDT(&&)[2]);
HAMON_IS_TRIVIAL_TEST_CV(false, POD_UDT(&&)[]);

HAMON_IS_TRIVIAL_TEST_CV(false, void);

HAMON_IS_TRIVIAL_TEST_CV(true, bool);
HAMON_IS_TRIVIAL_TEST_CV(true, char);
HAMON_IS_TRIVIAL_TEST_CV(true, wchar_t);
#if defined(HAMON_HAS_CXX20_CHAR8_T)
HAMON_IS_TRIVIAL_TEST_CV(true, char8_t);
#endif
HAMON_IS_TRIVIAL_TEST_CV(true, char16_t);
HAMON_IS_TRIVIAL_TEST_CV(true, char32_t);
HAMON_IS_TRIVIAL_TEST_CV(true, signed char);
HAMON_IS_TRIVIAL_TEST_CV(true, short);
HAMON_IS_TRIVIAL_TEST_CV(true, int);
HAMON_IS_TRIVIAL_TEST_CV(true, long);
HAMON_IS_TRIVIAL_TEST_CV(true, long long);
HAMON_IS_TRIVIAL_TEST_CV(true, unsigned char);
HAMON_IS_TRIVIAL_TEST_CV(true, unsigned short);
HAMON_IS_TRIVIAL_TEST_CV(true, unsigned int);
HAMON_IS_TRIVIAL_TEST_CV(true, unsigned long);
HAMON_IS_TRIVIAL_TEST_CV(true, unsigned long long);
HAMON_IS_TRIVIAL_TEST_CV(true, hamon::size_t);
HAMON_IS_TRIVIAL_TEST_CV(true, float);
HAMON_IS_TRIVIAL_TEST_CV(true, double);
HAMON_IS_TRIVIAL_TEST_CV(true, long double);
HAMON_IS_TRIVIAL_TEST_CV(true, void*);
HAMON_IS_TRIVIAL_TEST_CV(true, hamon::nullptr_t);
HAMON_IS_TRIVIAL_TEST_CV(true, decltype(nullptr));
HAMON_IS_TRIVIAL_TEST_CV(true, enum_UDT);
HAMON_IS_TRIVIAL_TEST_CV(true, enum_uint32_t_UDT);
HAMON_IS_TRIVIAL_TEST_CV(true, enum_uint16_t_UDT);
HAMON_IS_TRIVIAL_TEST_CV(true, enum_uint8_t_UDT);
HAMON_IS_TRIVIAL_TEST_CV(true, enum_int32_t_UDT);
HAMON_IS_TRIVIAL_TEST_CV(true, enum_int16_t_UDT);
HAMON_IS_TRIVIAL_TEST_CV(true, enum_int8_t_UDT);
HAMON_IS_TRIVIAL_TEST_CV(true, enum_class_UDT);
HAMON_IS_TRIVIAL_TEST_CV(true, enum_class_uint32_t_UDT);
HAMON_IS_TRIVIAL_TEST_CV(true, enum_class_uint16_t_UDT);
HAMON_IS_TRIVIAL_TEST_CV(true, enum_class_uint8_t_UDT);
HAMON_IS_TRIVIAL_TEST_CV(true, enum_class_int32_t_UDT);
HAMON_IS_TRIVIAL_TEST_CV(true, enum_class_int16_t_UDT);
HAMON_IS_TRIVIAL_TEST_CV(true, enum_class_int8_t_UDT);
HAMON_IS_TRIVIAL_TEST_CV(false, empty_UDT);
HAMON_IS_TRIVIAL_TEST_CV(true,  empty_POD_UDT);
HAMON_IS_TRIVIAL_TEST_CV(false, union_UDT);
HAMON_IS_TRIVIAL_TEST_CV(true,  POD_union_UDT);
HAMON_IS_TRIVIAL_TEST_CV(false, empty_union_UDT);
HAMON_IS_TRIVIAL_TEST_CV(true,  empty_POD_union_UDT);
HAMON_IS_TRIVIAL_TEST_CV(false, nothrow_default_ctor_UDT);
HAMON_IS_TRIVIAL_TEST_CV(false, nothrow_dtor_UDT);
HAMON_IS_TRIVIAL_TEST_CV(false, nothrow_copy_ctor_UDT);
HAMON_IS_TRIVIAL_TEST_CV(false, nothrow_copy_assign_UDT);
HAMON_IS_TRIVIAL_TEST_CV(false, nothrow_move_ctor_UDT);
HAMON_IS_TRIVIAL_TEST_CV(false, nothrow_move_assign_UDT);
HAMON_IS_TRIVIAL_TEST_CV(true, Base);
HAMON_IS_TRIVIAL_TEST_CV(true, Derived);
HAMON_IS_TRIVIAL_TEST_CV(true, Derived2);
HAMON_IS_TRIVIAL_TEST_CV(true, MultiBase);
HAMON_IS_TRIVIAL_TEST_CV(true, PrivateBase);
HAMON_IS_TRIVIAL_TEST_CV(true, NonDerived);
HAMON_IS_TRIVIAL_TEST_CV(true, enum1);
HAMON_IS_TRIVIAL_TEST_CV(true, enum2);
HAMON_IS_TRIVIAL_TEST_CV(false, VB);
HAMON_IS_TRIVIAL_TEST_CV(false, VD);
HAMON_IS_TRIVIAL_TEST_CV(true, non_pointer);
HAMON_IS_TRIVIAL_TEST_CV(true, non_int_pointer);
HAMON_IS_TRIVIAL_TEST_CV(false, int_constructible);
HAMON_IS_TRIVIAL_TEST_CV(true, int_convertible);
HAMON_IS_TRIVIAL_TEST_CV(false, test_abc1);
HAMON_IS_TRIVIAL_TEST_CV(false, test_abc2);
HAMON_IS_TRIVIAL_TEST_CV(false, test_abc3);
//	HAMON_IS_TRIVIAL_TEST_CV(true, incomplete_type);
HAMON_IS_TRIVIAL_TEST_CV(false, polymorphic_base);
HAMON_IS_TRIVIAL_TEST_CV(false, polymorphic_derived1);
HAMON_IS_TRIVIAL_TEST_CV(false, polymorphic_derived2);
HAMON_IS_TRIVIAL_TEST_CV(false, virtual_inherit1);
HAMON_IS_TRIVIAL_TEST_CV(false, virtual_inherit2);
HAMON_IS_TRIVIAL_TEST_CV(false, virtual_inherit3);
HAMON_IS_TRIVIAL_TEST_CV(false, virtual_inherit5);
HAMON_IS_TRIVIAL_TEST_CV(false, virtual_inherit6);
HAMON_IS_TRIVIAL_TEST_CV(false, trivial_except_construct);
HAMON_IS_TRIVIAL_TEST_CV(false, trivial_except_destroy);
HAMON_IS_TRIVIAL_TEST_CV(false, trivial_except_copy_ctor);
HAMON_IS_TRIVIAL_TEST_CV(false, trivial_except_move_ctor);
HAMON_IS_TRIVIAL_TEST_CV(false, trivial_except_copy_assign);
HAMON_IS_TRIVIAL_TEST_CV(false, trivial_except_move_assign);
HAMON_IS_TRIVIAL_TEST_CV(true, f1);
HAMON_IS_TRIVIAL_TEST_CV(true, f2);
HAMON_IS_TRIVIAL_TEST_CV(true, f3);
HAMON_IS_TRIVIAL_TEST_CV(true, mf1);
HAMON_IS_TRIVIAL_TEST_CV(true, mf2);
HAMON_IS_TRIVIAL_TEST_CV(true, mf3);
HAMON_IS_TRIVIAL_TEST_CV(true, mf4);
HAMON_IS_TRIVIAL_TEST_CV(true, mp);
HAMON_IS_TRIVIAL_TEST_CV(true, cmf);
HAMON_IS_TRIVIAL_TEST(false, foo0_t);
HAMON_IS_TRIVIAL_TEST(false, foo1_t);
HAMON_IS_TRIVIAL_TEST(false, foo2_t);
HAMON_IS_TRIVIAL_TEST(false, foo3_t);
HAMON_IS_TRIVIAL_TEST(false, foo4_t);

#if defined(HAMON_HAS_INT128)
HAMON_IS_TRIVIAL_TEST_CV(true, __int128_t);
HAMON_IS_TRIVIAL_TEST_CV(true, __uint128_t);
#endif

#undef HAMON_IS_TRIVIAL_TEST
#undef HAMON_IS_TRIVIAL_TEST_CV
