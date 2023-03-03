/**
 *	@file	unit_test_type_traits_is_union.cpp
 *
 *	@brief	is_union のテスト
 */

#include <hamon/type_traits/is_union.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include <cstddef>
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

HAMON_IS_UNION_TEST(true,                 union_UDT);
HAMON_IS_UNION_TEST(true,  const          union_UDT);
HAMON_IS_UNION_TEST(true,        volatile union_UDT);
HAMON_IS_UNION_TEST(true,  const volatile union_UDT);
HAMON_IS_UNION_TEST(false, union_UDT*);
HAMON_IS_UNION_TEST(false, union_UDT&);
HAMON_IS_UNION_TEST(false, union_UDT&&);
HAMON_IS_UNION_TEST(false, union_UDT[2]);
HAMON_IS_UNION_TEST(false, union_UDT[]);
HAMON_IS_UNION_TEST(false, union_UDT(*)[2]);
HAMON_IS_UNION_TEST(false, union_UDT(*)[]);
HAMON_IS_UNION_TEST(false, union_UDT(&)[2]);
HAMON_IS_UNION_TEST(false, union_UDT(&)[]);
HAMON_IS_UNION_TEST(false, union_UDT(&&)[2]);
HAMON_IS_UNION_TEST(false, union_UDT(&&)[]);

HAMON_IS_UNION_TEST(false,                UDT);
HAMON_IS_UNION_TEST(false, const          UDT);
HAMON_IS_UNION_TEST(false,       volatile UDT);
HAMON_IS_UNION_TEST(false, const volatile UDT);
HAMON_IS_UNION_TEST(false, UDT*);
HAMON_IS_UNION_TEST(false, UDT&);
HAMON_IS_UNION_TEST(false, UDT&&);
HAMON_IS_UNION_TEST(false, UDT[2]);
HAMON_IS_UNION_TEST(false, UDT[]);
HAMON_IS_UNION_TEST(false, UDT(*)[2]);
HAMON_IS_UNION_TEST(false, UDT(*)[]);
HAMON_IS_UNION_TEST(false, UDT(&)[2]);
HAMON_IS_UNION_TEST(false, UDT(&)[]);
HAMON_IS_UNION_TEST(false, UDT(&&)[2]);
HAMON_IS_UNION_TEST(false, UDT(&&)[]);

HAMON_IS_UNION_TEST(false,                void);
HAMON_IS_UNION_TEST(false, const          void);
HAMON_IS_UNION_TEST(false,       volatile void);
HAMON_IS_UNION_TEST(false, const volatile void);

HAMON_IS_UNION_TEST(false, bool);
HAMON_IS_UNION_TEST(false, char);
HAMON_IS_UNION_TEST(false, int);
HAMON_IS_UNION_TEST(false, float);
HAMON_IS_UNION_TEST(false, void*);
HAMON_IS_UNION_TEST(false, std::nullptr_t);
HAMON_IS_UNION_TEST(false, decltype(nullptr));
HAMON_IS_UNION_TEST(false, enum_UDT);
HAMON_IS_UNION_TEST(false, enum_uint32_t_UDT);
HAMON_IS_UNION_TEST(false, enum_class_UDT);
HAMON_IS_UNION_TEST(false, enum_class_uint32_t_UDT);
HAMON_IS_UNION_TEST(false, UDT);
HAMON_IS_UNION_TEST(false, POD_UDT);
HAMON_IS_UNION_TEST(true,  union_UDT);
HAMON_IS_UNION_TEST(true,  POD_union_UDT);
HAMON_IS_UNION_TEST(true,  empty_union_UDT);
HAMON_IS_UNION_TEST(true,  empty_POD_union_UDT);
HAMON_IS_UNION_TEST(false, f1);
HAMON_IS_UNION_TEST(false, f2);
HAMON_IS_UNION_TEST(false, f3);
HAMON_IS_UNION_TEST(false, mf1);
HAMON_IS_UNION_TEST(false, mf2);
HAMON_IS_UNION_TEST(false, mf3);
HAMON_IS_UNION_TEST(false, mf4);
HAMON_IS_UNION_TEST(false, mp);
HAMON_IS_UNION_TEST(false, cmf);
HAMON_IS_UNION_TEST(false, foo0_t);
HAMON_IS_UNION_TEST(false, foo1_t);
HAMON_IS_UNION_TEST(false, foo2_t);
HAMON_IS_UNION_TEST(false, foo3_t);
HAMON_IS_UNION_TEST(false, foo4_t);

#undef HAMON_IS_UNION_TEST
