/**
 *	@file	unit_test_type_traits_is_union.cpp
 *
 *	@brief	is_union のテスト
 */

#include <hamon/type_traits/is_union.hpp>
#include <hamon/cstddef/nullptr_t.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "type_traits_test_utility.hpp"

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

#define HAMON_IS_UNION_TEST(b, T)	\
	static_assert(hamon::is_union_v<T>      == b, #T);	\
	static_assert(hamon::is_union<T>::value == b, #T);	\
	static_assert(hamon::is_union<T>{}()    == b, #T);	\
	static_assert(hamon::is_union<T>{}      == b, #T)

#else

#define HAMON_IS_UNION_TEST(b, T)	\
	static_assert(hamon::is_union<T>::value == b, #T);	\
	static_assert(hamon::is_union<T>{}()    == b, #T);	\
	static_assert(hamon::is_union<T>{}      == b, #T)

#endif

#define HAMON_IS_UNION_TEST_CV(b, T)	\
	HAMON_IS_UNION_TEST(b,                T);	\
	HAMON_IS_UNION_TEST(b, const          T);	\
	HAMON_IS_UNION_TEST(b,       volatile T);	\
	HAMON_IS_UNION_TEST(b, const volatile T)

HAMON_IS_UNION_TEST_CV(true,  union_UDT);
HAMON_IS_UNION_TEST_CV(false, union_UDT*);
HAMON_IS_UNION_TEST_CV(false, union_UDT&);
HAMON_IS_UNION_TEST_CV(false, union_UDT&&);
HAMON_IS_UNION_TEST_CV(false, union_UDT[2]);
HAMON_IS_UNION_TEST_CV(false, union_UDT[]);
HAMON_IS_UNION_TEST_CV(false, union_UDT(*)[2]);
HAMON_IS_UNION_TEST_CV(false, union_UDT(*)[]);
HAMON_IS_UNION_TEST_CV(false, union_UDT(&)[2]);
HAMON_IS_UNION_TEST_CV(false, union_UDT(&)[]);
HAMON_IS_UNION_TEST_CV(false, union_UDT(&&)[2]);
HAMON_IS_UNION_TEST_CV(false, union_UDT(&&)[]);

HAMON_IS_UNION_TEST_CV(false, UDT);
HAMON_IS_UNION_TEST_CV(false, UDT*);
HAMON_IS_UNION_TEST_CV(false, UDT&);
HAMON_IS_UNION_TEST_CV(false, UDT&&);
HAMON_IS_UNION_TEST_CV(false, UDT[2]);
HAMON_IS_UNION_TEST_CV(false, UDT[]);
HAMON_IS_UNION_TEST_CV(false, UDT(*)[2]);
HAMON_IS_UNION_TEST_CV(false, UDT(*)[]);
HAMON_IS_UNION_TEST_CV(false, UDT(&)[2]);
HAMON_IS_UNION_TEST_CV(false, UDT(&)[]);
HAMON_IS_UNION_TEST_CV(false, UDT(&&)[2]);
HAMON_IS_UNION_TEST_CV(false, UDT(&&)[]);

HAMON_IS_UNION_TEST_CV(false, void);

HAMON_IS_UNION_TEST_CV(false, bool);
HAMON_IS_UNION_TEST_CV(false, char);
HAMON_IS_UNION_TEST_CV(false, wchar_t);
#if defined(HAMON_HAS_CXX20_CHAR8_T)
HAMON_IS_UNION_TEST_CV(false, char8_t);
#endif
HAMON_IS_UNION_TEST_CV(false, char16_t);
HAMON_IS_UNION_TEST_CV(false, char32_t);
HAMON_IS_UNION_TEST_CV(false, signed char);
HAMON_IS_UNION_TEST_CV(false, short);
HAMON_IS_UNION_TEST_CV(false, int);
HAMON_IS_UNION_TEST_CV(false, long);
HAMON_IS_UNION_TEST_CV(false, long long);
HAMON_IS_UNION_TEST_CV(false, unsigned char);
HAMON_IS_UNION_TEST_CV(false, unsigned short);
HAMON_IS_UNION_TEST_CV(false, unsigned int);
HAMON_IS_UNION_TEST_CV(false, unsigned long);
HAMON_IS_UNION_TEST_CV(false, unsigned long long);
HAMON_IS_UNION_TEST_CV(false, float);
HAMON_IS_UNION_TEST_CV(false, double);
HAMON_IS_UNION_TEST_CV(false, long double);
HAMON_IS_UNION_TEST_CV(false, void*);
HAMON_IS_UNION_TEST_CV(false, hamon::nullptr_t);
HAMON_IS_UNION_TEST_CV(false, decltype(nullptr));
HAMON_IS_UNION_TEST_CV(false, enum_UDT);
HAMON_IS_UNION_TEST_CV(false, enum_uint32_t_UDT);
HAMON_IS_UNION_TEST_CV(false, enum_class_UDT);
HAMON_IS_UNION_TEST_CV(false, enum_class_uint32_t_UDT);
HAMON_IS_UNION_TEST_CV(false, UDT);
HAMON_IS_UNION_TEST_CV(false, POD_UDT);
HAMON_IS_UNION_TEST_CV(true,  union_UDT);
HAMON_IS_UNION_TEST_CV(true,  POD_union_UDT);
HAMON_IS_UNION_TEST_CV(true,  empty_union_UDT);
HAMON_IS_UNION_TEST_CV(true,  empty_POD_union_UDT);
HAMON_IS_UNION_TEST_CV(false, f1);
HAMON_IS_UNION_TEST_CV(false, f2);
HAMON_IS_UNION_TEST_CV(false, f3);
HAMON_IS_UNION_TEST_CV(false, mf1);
HAMON_IS_UNION_TEST_CV(false, mf2);
HAMON_IS_UNION_TEST_CV(false, mf3);
HAMON_IS_UNION_TEST_CV(false, mf4);
HAMON_IS_UNION_TEST_CV(false, mp);
HAMON_IS_UNION_TEST_CV(false, cmf);
HAMON_IS_UNION_TEST(false, foo0_t);
HAMON_IS_UNION_TEST(false, foo1_t);
HAMON_IS_UNION_TEST(false, foo2_t);
HAMON_IS_UNION_TEST(false, foo3_t);
HAMON_IS_UNION_TEST(false, foo4_t);

#undef HAMON_IS_UNION_TEST
#undef HAMON_IS_UNION_TEST_CV
