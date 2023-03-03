/**
 *	@file	unit_test_type_traits_is_base_of.cpp
 *
 *	@brief	is_base_of のテスト
 */

#include <hamon/type_traits/is_base_of.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "type_traits_test_utility.hpp"

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

#define HAMON_IS_BASE_OF_TEST(b, T, U)	\
	static_assert(hamon::is_base_of_v<T, U>      == b, "is_base_of<" #T ", " #U "> == " #b);	\
	static_assert(hamon::is_base_of<T, U>::value == b, "is_base_of<" #T ", " #U "> == " #b);	\
	static_assert(hamon::is_base_of<T, U>{}()    == b, "is_base_of<" #T ", " #U "> == " #b);	\
	static_assert(hamon::is_base_of<T, U>{}      == b, "is_base_of<" #T ", " #U "> == " #b)

#else

#define HAMON_IS_BASE_OF_TEST(b, T, U)	\
	static_assert(hamon::is_base_of<T, U>::value == b, "is_base_of<" #T ", " #U "> == " #b);	\
	static_assert(hamon::is_base_of<T, U>{}()    == b, "is_base_of<" #T ", " #U "> == " #b);	\
	static_assert(hamon::is_base_of<T, U>{}      == b, "is_base_of<" #T ", " #U "> == " #b)

#endif

#define HAMON_IS_BASE_OF_TEST_CV(b, T, U)	\
	HAMON_IS_BASE_OF_TEST(b,                T,                U);	\
	HAMON_IS_BASE_OF_TEST(b,                T, const          U);	\
	HAMON_IS_BASE_OF_TEST(b,                T,       volatile U);	\
	HAMON_IS_BASE_OF_TEST(b,                T, const volatile U);	\
	HAMON_IS_BASE_OF_TEST(b, const          T,                U);	\
	HAMON_IS_BASE_OF_TEST(b, const          T, const          U);	\
	HAMON_IS_BASE_OF_TEST(b, const          T,       volatile U);	\
	HAMON_IS_BASE_OF_TEST(b, const          T, const volatile U);	\
	HAMON_IS_BASE_OF_TEST(b,       volatile T,                U);	\
	HAMON_IS_BASE_OF_TEST(b,       volatile T, const          U);	\
	HAMON_IS_BASE_OF_TEST(b,       volatile T,       volatile U);	\
	HAMON_IS_BASE_OF_TEST(b,       volatile T, const volatile U);	\
	HAMON_IS_BASE_OF_TEST(b, const volatile T,                U);	\
	HAMON_IS_BASE_OF_TEST(b, const volatile T, const          U);	\
	HAMON_IS_BASE_OF_TEST(b, const volatile T,       volatile U);	\
	HAMON_IS_BASE_OF_TEST(b, const volatile T, const volatile U)

HAMON_IS_BASE_OF_TEST_CV(false, int, int);
HAMON_IS_BASE_OF_TEST_CV(false, int, char);
HAMON_IS_BASE_OF_TEST_CV(false, int, float);
HAMON_IS_BASE_OF_TEST_CV(false, int, void);
HAMON_IS_BASE_OF_TEST_CV(false, char, int);
HAMON_IS_BASE_OF_TEST_CV(false, float, int);
HAMON_IS_BASE_OF_TEST_CV(false, void, int);
HAMON_IS_BASE_OF_TEST_CV(false, void, void);
HAMON_IS_BASE_OF_TEST_CV(false, int, int*);
HAMON_IS_BASE_OF_TEST_CV(false, int, int&);
HAMON_IS_BASE_OF_TEST_CV(false, int, int&&);
HAMON_IS_BASE_OF_TEST_CV(false, int*, int);
HAMON_IS_BASE_OF_TEST_CV(false, int*, int*);
HAMON_IS_BASE_OF_TEST_CV(false, int*, int&);
HAMON_IS_BASE_OF_TEST_CV(false, int*, int&&);
HAMON_IS_BASE_OF_TEST_CV(false, int&, int);
HAMON_IS_BASE_OF_TEST_CV(false, int&, int*);
HAMON_IS_BASE_OF_TEST_CV(false, int&, int&);
HAMON_IS_BASE_OF_TEST_CV(false, int&, int&&);
HAMON_IS_BASE_OF_TEST_CV(false, int&&, int);
HAMON_IS_BASE_OF_TEST_CV(false, int&&, int*);
HAMON_IS_BASE_OF_TEST_CV(false, int&&, int&);
HAMON_IS_BASE_OF_TEST_CV(false, int&&, int&&);
HAMON_IS_BASE_OF_TEST_CV(false, enum_UDT, enum_UDT);
HAMON_IS_BASE_OF_TEST_CV(false, enum_class_UDT, enum_class_UDT);
HAMON_IS_BASE_OF_TEST_CV(false, f1, f1);
HAMON_IS_BASE_OF_TEST_CV(false, f2, f2);
HAMON_IS_BASE_OF_TEST_CV(false, f3, f3);
HAMON_IS_BASE_OF_TEST_CV(false, mf1, mf1);
HAMON_IS_BASE_OF_TEST_CV(false, mf2, mf2);
HAMON_IS_BASE_OF_TEST_CV(false, mf3, mf3);
HAMON_IS_BASE_OF_TEST_CV(false, mf4, mf4);
HAMON_IS_BASE_OF_TEST_CV(false, mp, mp);
HAMON_IS_BASE_OF_TEST_CV(false, cmf, cmf);
HAMON_IS_BASE_OF_TEST_CV(true,  UDT, UDT);
HAMON_IS_BASE_OF_TEST_CV(false, UDT*, UDT*);
HAMON_IS_BASE_OF_TEST_CV(false, UDT&, UDT&);
HAMON_IS_BASE_OF_TEST_CV(false, UDT&&, UDT&&);
HAMON_IS_BASE_OF_TEST_CV(true,  POD_UDT, POD_UDT);
HAMON_IS_BASE_OF_TEST_CV(true,  empty_UDT, empty_UDT);
HAMON_IS_BASE_OF_TEST_CV(true,  empty_POD_UDT, empty_POD_UDT);
HAMON_IS_BASE_OF_TEST_CV(false, union_UDT, union_UDT);
HAMON_IS_BASE_OF_TEST_CV(false, POD_union_UDT, POD_union_UDT);
HAMON_IS_BASE_OF_TEST_CV(false, empty_union_UDT, empty_union_UDT);
HAMON_IS_BASE_OF_TEST_CV(false, empty_POD_union_UDT, empty_POD_union_UDT);
HAMON_IS_BASE_OF_TEST_CV(false, Derived, Base);
HAMON_IS_BASE_OF_TEST_CV(true,  Derived, Derived);
HAMON_IS_BASE_OF_TEST_CV(true,  Base, Base);
HAMON_IS_BASE_OF_TEST_CV(true,  Base, Derived);
HAMON_IS_BASE_OF_TEST_CV(true,  Base, MultiBase);
HAMON_IS_BASE_OF_TEST_CV(true,  Derived, MultiBase);
HAMON_IS_BASE_OF_TEST_CV(true,  Derived2, MultiBase);
HAMON_IS_BASE_OF_TEST_CV(true,  Base, PrivateBase);
HAMON_IS_BASE_OF_TEST_CV(false, NonDerived, Base);
HAMON_IS_BASE_OF_TEST_CV(false, Base, void);
HAMON_IS_BASE_OF_TEST_CV(false, Derived, void);
HAMON_IS_BASE_OF_TEST_CV(false, void, Base);
HAMON_IS_BASE_OF_TEST_CV(false, void, Derived);
HAMON_IS_BASE_OF_TEST_CV(true,  VB, VD);
HAMON_IS_BASE_OF_TEST_CV(false, VD, VB);
HAMON_IS_BASE_OF_TEST_CV(true,  test_abc1, test_abc3);
HAMON_IS_BASE_OF_TEST_CV(false, test_abc3, test_abc1);
HAMON_IS_BASE_OF_TEST_CV(true,  Base, virtual_inherit1);
HAMON_IS_BASE_OF_TEST_CV(false, virtual_inherit1, Base);
HAMON_IS_BASE_OF_TEST_CV(true,  virtual_inherit1, virtual_inherit2);
HAMON_IS_BASE_OF_TEST_CV(false, virtual_inherit2, virtual_inherit1);
HAMON_IS_BASE_OF_TEST_CV(true,  Base, virtual_inherit3);
HAMON_IS_BASE_OF_TEST_CV(false, virtual_inherit3, Base);
HAMON_IS_BASE_OF_TEST_CV(true,  polymorphic_base, polymorphic_derived1);
HAMON_IS_BASE_OF_TEST_CV(true,  polymorphic_base, polymorphic_derived2);
HAMON_IS_BASE_OF_TEST_CV(true,  polymorphic_base, polymorphic_base);
HAMON_IS_BASE_OF_TEST_CV(true,  polymorphic_derived1, polymorphic_derived1);
HAMON_IS_BASE_OF_TEST_CV(true,  polymorphic_derived2, polymorphic_derived2);
HAMON_IS_BASE_OF_TEST_CV(false, polymorphic_derived1, polymorphic_base);
HAMON_IS_BASE_OF_TEST_CV(false, polymorphic_derived2, polymorphic_base);

#undef HAMON_IS_BASE_OF_TEST
#undef HAMON_IS_BASE_OF_TEST_CV
