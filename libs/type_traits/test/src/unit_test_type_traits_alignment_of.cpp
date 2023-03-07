/**
 *	@file	unit_test_type_traits_alignment_of.cpp
 *
 *	@brief	alignment_of のテスト
 */

#include <hamon/type_traits/alignment_of.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include <cstddef>
#include "type_traits_test_utility.hpp"

namespace type_traits_test
{

namespace alignment_of_test
{

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

#define HAMON_ALIGNMENT_OF_TEST_IMPL(x, T)	\
	static_assert(hamon::alignment_of_v<T>      == x, #T);	\
	static_assert(hamon::alignment_of<T>::value == x, #T);	\
	static_assert(hamon::alignment_of<T>{}()    == x, #T);	\
	static_assert(hamon::alignment_of<T>{}      == x, #T)

#else

#define HAMON_ALIGNMENT_OF_TEST_IMPL(x, T)	\
	static_assert(hamon::alignment_of<T>::value == x, #T);	\
	static_assert(hamon::alignment_of<T>{}()    == x, #T);	\
	static_assert(hamon::alignment_of<T>{}      == x, #T)

#endif

#define HAMON_ALIGNMENT_OF_TEST(x, T)	\
	HAMON_ALIGNMENT_OF_TEST_IMPL(x, T);	\
	HAMON_ALIGNMENT_OF_TEST_IMPL(x, T&);	\
	HAMON_ALIGNMENT_OF_TEST_IMPL(x, T&&);	\
	HAMON_ALIGNMENT_OF_TEST_IMPL(x, T[2]);	\
	HAMON_ALIGNMENT_OF_TEST_IMPL(x, T[]);	\
	HAMON_ALIGNMENT_OF_TEST_IMPL(x, T(&)[2]);	\
	HAMON_ALIGNMENT_OF_TEST_IMPL(x, T(&)[]);	\
	HAMON_ALIGNMENT_OF_TEST_IMPL(x, T(&&)[2]);	\
	HAMON_ALIGNMENT_OF_TEST_IMPL(x, T(&&)[])

#define HAMON_ALIGNMENT_OF_TEST_PRIMITIVE(T)	\
	HAMON_ALIGNMENT_OF_TEST(sizeof(T), T)

static auto const alignment_of_mf = hamon::alignment_of<mf1>::value;

HAMON_ALIGNMENT_OF_TEST_PRIMITIVE(bool);
HAMON_ALIGNMENT_OF_TEST_PRIMITIVE(char);
HAMON_ALIGNMENT_OF_TEST_PRIMITIVE(wchar_t);
HAMON_ALIGNMENT_OF_TEST_PRIMITIVE(signed char);
HAMON_ALIGNMENT_OF_TEST_PRIMITIVE(int);
HAMON_ALIGNMENT_OF_TEST_PRIMITIVE(short);
HAMON_ALIGNMENT_OF_TEST_PRIMITIVE(long);
HAMON_ALIGNMENT_OF_TEST_PRIMITIVE(long long);
HAMON_ALIGNMENT_OF_TEST_PRIMITIVE(unsigned char);
HAMON_ALIGNMENT_OF_TEST_PRIMITIVE(unsigned int);
HAMON_ALIGNMENT_OF_TEST_PRIMITIVE(unsigned short);
HAMON_ALIGNMENT_OF_TEST_PRIMITIVE(unsigned long);
HAMON_ALIGNMENT_OF_TEST_PRIMITIVE(unsigned long long);
HAMON_ALIGNMENT_OF_TEST_PRIMITIVE(hamon::size_t);
HAMON_ALIGNMENT_OF_TEST_PRIMITIVE(float);
HAMON_ALIGNMENT_OF_TEST_PRIMITIVE(double);
HAMON_ALIGNMENT_OF_TEST_PRIMITIVE(long double);
//HAMON_ALIGNMENT_OF_TEST_PRIMITIVE(void);
HAMON_ALIGNMENT_OF_TEST_PRIMITIVE(void*);
//HAMON_ALIGNMENT_OF_TEST_PRIMITIVE(std::nullptr_t);
//HAMON_ALIGNMENT_OF_TEST_PRIMITIVE(decltype(nullptr));
HAMON_ALIGNMENT_OF_TEST_PRIMITIVE(enum_UDT);
HAMON_ALIGNMENT_OF_TEST_PRIMITIVE(enum_uint32_t_UDT);
HAMON_ALIGNMENT_OF_TEST_PRIMITIVE(enum_uint16_t_UDT);
HAMON_ALIGNMENT_OF_TEST_PRIMITIVE(enum_uint8_t_UDT);
HAMON_ALIGNMENT_OF_TEST_PRIMITIVE(enum_int32_t_UDT);
HAMON_ALIGNMENT_OF_TEST_PRIMITIVE(enum_int16_t_UDT);
HAMON_ALIGNMENT_OF_TEST_PRIMITIVE(enum_int8_t_UDT);
HAMON_ALIGNMENT_OF_TEST_PRIMITIVE(enum_class_UDT);
HAMON_ALIGNMENT_OF_TEST_PRIMITIVE(enum_class_uint32_t_UDT);
HAMON_ALIGNMENT_OF_TEST_PRIMITIVE(enum_class_uint16_t_UDT);
HAMON_ALIGNMENT_OF_TEST_PRIMITIVE(enum_class_uint8_t_UDT);
HAMON_ALIGNMENT_OF_TEST_PRIMITIVE(enum_class_int32_t_UDT);
HAMON_ALIGNMENT_OF_TEST_PRIMITIVE(enum_class_int16_t_UDT);
HAMON_ALIGNMENT_OF_TEST_PRIMITIVE(enum_class_int8_t_UDT);
HAMON_ALIGNMENT_OF_TEST(sizeof(int), UDT);
HAMON_ALIGNMENT_OF_TEST(sizeof(int), POD_UDT);
HAMON_ALIGNMENT_OF_TEST(1, empty_UDT);
HAMON_ALIGNMENT_OF_TEST(1, empty_POD_UDT);
HAMON_ALIGNMENT_OF_TEST(sizeof(double), union_UDT);
HAMON_ALIGNMENT_OF_TEST(sizeof(double), POD_union_UDT);
HAMON_ALIGNMENT_OF_TEST(1, empty_union_UDT);
HAMON_ALIGNMENT_OF_TEST(1, empty_POD_union_UDT);
HAMON_ALIGNMENT_OF_TEST(1, nothrow_default_ctor_UDT);
HAMON_ALIGNMENT_OF_TEST(1, nothrow_dtor_UDT);
HAMON_ALIGNMENT_OF_TEST(1, nothrow_copy_ctor_UDT);
HAMON_ALIGNMENT_OF_TEST(1, nothrow_copy_assign_UDT);
HAMON_ALIGNMENT_OF_TEST(1, nothrow_move_ctor_UDT);
HAMON_ALIGNMENT_OF_TEST(1, nothrow_move_assign_UDT);
HAMON_ALIGNMENT_OF_TEST(1, Base);
HAMON_ALIGNMENT_OF_TEST(1, Derived);
HAMON_ALIGNMENT_OF_TEST(1, Derived2);
HAMON_ALIGNMENT_OF_TEST(1, MultiBase);
HAMON_ALIGNMENT_OF_TEST(1, PrivateBase);
HAMON_ALIGNMENT_OF_TEST(1, NonDerived);
HAMON_ALIGNMENT_OF_TEST_PRIMITIVE(enum1);
HAMON_ALIGNMENT_OF_TEST_PRIMITIVE(enum2);
HAMON_ALIGNMENT_OF_TEST(alignment_of_mf, VB);
HAMON_ALIGNMENT_OF_TEST(alignment_of_mf, VD);
HAMON_ALIGNMENT_OF_TEST(1, non_pointer);
HAMON_ALIGNMENT_OF_TEST(sizeof(int), non_int_pointer);
HAMON_ALIGNMENT_OF_TEST(1, int_constructible);
HAMON_ALIGNMENT_OF_TEST(1, int_convertible);
//HAMON_ALIGNMENT_OF_TEST_2(8, test_abc1);
//HAMON_ALIGNMENT_OF_TEST_2(8, test_abc2);
//HAMON_ALIGNMENT_OF_TEST_2(8, test_abc3);
//HAMON_ALIGNMENT_OF_TEST(1, incomplete_type);
HAMON_ALIGNMENT_OF_TEST(alignment_of_mf, polymorphic_base);
HAMON_ALIGNMENT_OF_TEST(alignment_of_mf, polymorphic_derived1);
HAMON_ALIGNMENT_OF_TEST(alignment_of_mf, polymorphic_derived2);
HAMON_ALIGNMENT_OF_TEST(alignment_of_mf, virtual_inherit1);
HAMON_ALIGNMENT_OF_TEST(alignment_of_mf, virtual_inherit2);
HAMON_ALIGNMENT_OF_TEST(alignment_of_mf, virtual_inherit3);
HAMON_ALIGNMENT_OF_TEST(alignment_of_mf, virtual_inherit5);
HAMON_ALIGNMENT_OF_TEST(alignment_of_mf, virtual_inherit6);
HAMON_ALIGNMENT_OF_TEST(sizeof(int), trivial_except_construct);
HAMON_ALIGNMENT_OF_TEST(sizeof(int), trivial_except_destroy);
HAMON_ALIGNMENT_OF_TEST(sizeof(int), trivial_except_copy_ctor);
HAMON_ALIGNMENT_OF_TEST(sizeof(int), trivial_except_move_ctor);
HAMON_ALIGNMENT_OF_TEST(sizeof(int), trivial_except_copy_assign);
HAMON_ALIGNMENT_OF_TEST(sizeof(int), trivial_except_move_assign);
HAMON_ALIGNMENT_OF_TEST_IMPL(sizeof(f1),		f1);
HAMON_ALIGNMENT_OF_TEST_IMPL(sizeof(f2),		f2);
HAMON_ALIGNMENT_OF_TEST_IMPL(sizeof(f3),		f3);
HAMON_ALIGNMENT_OF_TEST_IMPL(alignment_of_mf,	mf1);
HAMON_ALIGNMENT_OF_TEST_IMPL(alignment_of_mf,	mf2);
HAMON_ALIGNMENT_OF_TEST_IMPL(alignment_of_mf,	mf3);
HAMON_ALIGNMENT_OF_TEST_IMPL(alignment_of_mf,	mf4);
//HAMON_ALIGNMENT_OF_TEST_IMPL(sizeof(mp),		mp);
HAMON_ALIGNMENT_OF_TEST_IMPL(alignment_of_mf,	cmf);
//HAMON_ALIGNMENT_OF_TEST_IMPL(8, foo0_t);
//HAMON_ALIGNMENT_OF_TEST_IMPL(8, foo1_t);
//HAMON_ALIGNMENT_OF_TEST_IMPL(8, foo2_t);
//HAMON_ALIGNMENT_OF_TEST_IMPL(8, foo3_t);
//HAMON_ALIGNMENT_OF_TEST_IMPL(8, foo4_t);

#undef HAMON_ALIGNMENT_OF_TEST_PRIMITIVE
#undef HAMON_ALIGNMENT_OF_TEST
#undef HAMON_ALIGNMENT_OF_TEST_IMPL

}	// namespace alignment_of_test

}	// namespace type_traits_test
