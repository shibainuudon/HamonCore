/**
 *	@file	unit_test_type_traits_is_polymorphic.cpp
 *
 *	@brief	is_polymorphic のテスト
 */

#include <hamon/type_traits/is_polymorphic.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "type_traits_test_utility.hpp"

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

#define HAMON_IS_POLYMORPHIC_TEST_IMPL(b, T)	\
	static_assert(hamon::is_polymorphic_v<T>      == b, #T);	\
	static_assert(hamon::is_polymorphic<T>::value == b, #T);	\
	static_assert(hamon::is_polymorphic<T>{}()    == b, #T);	\
	static_assert(hamon::is_polymorphic<T>{}      == b, #T)

#else

#define HAMON_IS_POLYMORPHIC_TEST_IMPL(b, T)	\
	static_assert(hamon::is_polymorphic<T>::value == b, #T);	\
	static_assert(hamon::is_polymorphic<T>{}()    == b, #T);	\
	static_assert(hamon::is_polymorphic<T>{}      == b, #T)

#endif

#define HAMON_IS_POLYMORPHIC_TEST(b, T)	\
	HAMON_IS_POLYMORPHIC_TEST_IMPL(b,                T);	\
	HAMON_IS_POLYMORPHIC_TEST_IMPL(b, const          T);	\
	HAMON_IS_POLYMORPHIC_TEST_IMPL(b,       volatile T);	\
	HAMON_IS_POLYMORPHIC_TEST_IMPL(b, const volatile T);	\
	HAMON_IS_POLYMORPHIC_TEST_IMPL(false, T*);				\
	HAMON_IS_POLYMORPHIC_TEST_IMPL(false, T&);				\
	HAMON_IS_POLYMORPHIC_TEST_IMPL(false, T&&);				\
	HAMON_IS_POLYMORPHIC_TEST_IMPL(false, T[2]);			\
	HAMON_IS_POLYMORPHIC_TEST_IMPL(false, T[]);				\
	HAMON_IS_POLYMORPHIC_TEST_IMPL(false, T(*)[2]);			\
	HAMON_IS_POLYMORPHIC_TEST_IMPL(false, T(*)[]);			\
	HAMON_IS_POLYMORPHIC_TEST_IMPL(false, T(&)[2]);			\
	HAMON_IS_POLYMORPHIC_TEST_IMPL(false, T(&)[]);			\
	HAMON_IS_POLYMORPHIC_TEST_IMPL(false, T(&&)[2]);		\
	HAMON_IS_POLYMORPHIC_TEST_IMPL(false, T(&&)[])

HAMON_IS_POLYMORPHIC_TEST_IMPL(false,                void);
HAMON_IS_POLYMORPHIC_TEST_IMPL(false, const          void);
HAMON_IS_POLYMORPHIC_TEST_IMPL(false,       volatile void);
HAMON_IS_POLYMORPHIC_TEST_IMPL(false, const volatile void);

HAMON_IS_POLYMORPHIC_TEST(false, int);
HAMON_IS_POLYMORPHIC_TEST(false, float);
HAMON_IS_POLYMORPHIC_TEST(false, enum_UDT);
HAMON_IS_POLYMORPHIC_TEST(false, enum_class_UDT);
HAMON_IS_POLYMORPHIC_TEST(false, UDT);
HAMON_IS_POLYMORPHIC_TEST(false, POD_UDT);
HAMON_IS_POLYMORPHIC_TEST(false, Base);
HAMON_IS_POLYMORPHIC_TEST(false, Derived);
HAMON_IS_POLYMORPHIC_TEST(false, Derived2);
HAMON_IS_POLYMORPHIC_TEST(false, MultiBase);
HAMON_IS_POLYMORPHIC_TEST(false, PrivateBase);
HAMON_IS_POLYMORPHIC_TEST(false, NonDerived);
HAMON_IS_POLYMORPHIC_TEST(true, VB);
HAMON_IS_POLYMORPHIC_TEST(true, VD);
HAMON_IS_POLYMORPHIC_TEST_IMPL(true, test_abc1);
HAMON_IS_POLYMORPHIC_TEST_IMPL(true, test_abc2);
HAMON_IS_POLYMORPHIC_TEST_IMPL(true, test_abc3);
//HAMON_IS_POLYMORPHIC_TEST(false, incomplete_type);
HAMON_IS_POLYMORPHIC_TEST(true, polymorphic_base);
HAMON_IS_POLYMORPHIC_TEST(true, polymorphic_derived1);
HAMON_IS_POLYMORPHIC_TEST(true, polymorphic_derived2);
HAMON_IS_POLYMORPHIC_TEST(false, virtual_inherit1);
HAMON_IS_POLYMORPHIC_TEST(false, virtual_inherit2);
HAMON_IS_POLYMORPHIC_TEST(false, virtual_inherit3);
HAMON_IS_POLYMORPHIC_TEST(false, virtual_inherit5);
HAMON_IS_POLYMORPHIC_TEST(true, virtual_inherit6);
HAMON_IS_POLYMORPHIC_TEST_IMPL(false, f1);
HAMON_IS_POLYMORPHIC_TEST_IMPL(false, f2);
HAMON_IS_POLYMORPHIC_TEST_IMPL(false, f3);
HAMON_IS_POLYMORPHIC_TEST_IMPL(false, mf1);
HAMON_IS_POLYMORPHIC_TEST_IMPL(false, mf2);
HAMON_IS_POLYMORPHIC_TEST_IMPL(false, mf3);
HAMON_IS_POLYMORPHIC_TEST_IMPL(false, mf4);
HAMON_IS_POLYMORPHIC_TEST_IMPL(false, mp);
HAMON_IS_POLYMORPHIC_TEST_IMPL(false, cmf);
HAMON_IS_POLYMORPHIC_TEST_IMPL(false, foo0_t);
HAMON_IS_POLYMORPHIC_TEST_IMPL(false, foo1_t);
HAMON_IS_POLYMORPHIC_TEST_IMPL(false, foo2_t);
HAMON_IS_POLYMORPHIC_TEST_IMPL(false, foo3_t);
HAMON_IS_POLYMORPHIC_TEST_IMPL(false, foo4_t);

#undef HAMON_IS_POLYMORPHIC_TEST
#undef HAMON_IS_POLYMORPHIC_TEST_IMPL
