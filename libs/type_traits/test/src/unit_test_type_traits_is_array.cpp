/**
 *	@file	unit_test_type_traits_is_array.cpp
 *
 *	@brief	is_array のテスト
 */

#include <hamon/type_traits/is_array.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "type_traits_test_utility.hpp"

namespace hamon_type_traits_test
{

namespace is_array_test
{

struct convertible_to_pointer
{
	operator char*() const;
};

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

#define HAMON_IS_ARRAY_TEST_IMPL(b, T)	\
	static_assert(hamon::is_array_v<T>      == b, #T);	\
	static_assert(hamon::is_array<T>::value == b, #T);	\
	static_assert(hamon::is_array<T>{}()    == b, #T);	\
	static_assert(hamon::is_array<T>{}      == b, #T)

#else

#define HAMON_IS_ARRAY_TEST_IMPL(b, T)	\
	static_assert(hamon::is_array<T>::value == b, #T);	\
	static_assert(hamon::is_array<T>{}()    == b, #T);	\
	static_assert(hamon::is_array<T>{}      == b, #T)

#endif

#define HAMON_IS_ARRAY_TEST(T)	\
	HAMON_IS_ARRAY_TEST_IMPL(false,                T);	\
	HAMON_IS_ARRAY_TEST_IMPL(false, const          T);	\
	HAMON_IS_ARRAY_TEST_IMPL(false,       volatile T);	\
	HAMON_IS_ARRAY_TEST_IMPL(false, const volatile T);	\
	HAMON_IS_ARRAY_TEST_IMPL(false, T*);	\
	HAMON_IS_ARRAY_TEST_IMPL(false, T* const);	\
	HAMON_IS_ARRAY_TEST_IMPL(false, T* volatile);	\
	HAMON_IS_ARRAY_TEST_IMPL(false, T* const volatile);	\
	HAMON_IS_ARRAY_TEST_IMPL(false, T**);	\
	HAMON_IS_ARRAY_TEST_IMPL(true,                 T[]);	\
	HAMON_IS_ARRAY_TEST_IMPL(true,  const          T[]);	\
	HAMON_IS_ARRAY_TEST_IMPL(true,        volatile T[]);	\
	HAMON_IS_ARRAY_TEST_IMPL(true,  const volatile T[]);	\
	HAMON_IS_ARRAY_TEST_IMPL(true,                 T[2]);	\
	HAMON_IS_ARRAY_TEST_IMPL(true,  const          T[2]);	\
	HAMON_IS_ARRAY_TEST_IMPL(true,        volatile T[2]);	\
	HAMON_IS_ARRAY_TEST_IMPL(true,  const volatile T[2]);	\
	HAMON_IS_ARRAY_TEST_IMPL(true,                 T[2][3]);	\
	HAMON_IS_ARRAY_TEST_IMPL(true,  const          T[2][3]);	\
	HAMON_IS_ARRAY_TEST_IMPL(true,        volatile T[2][3]);	\
	HAMON_IS_ARRAY_TEST_IMPL(true,  const volatile T[2][3]);	\
	HAMON_IS_ARRAY_TEST_IMPL(false, T(*)[2]);	\
	HAMON_IS_ARRAY_TEST_IMPL(false, T(&)[2]);	\
	HAMON_IS_ARRAY_TEST_IMPL(false, T(&&)[2]);	\
	HAMON_IS_ARRAY_TEST_IMPL(false, T&);		\
	HAMON_IS_ARRAY_TEST_IMPL(false, T&&)

HAMON_IS_ARRAY_TEST(int);
HAMON_IS_ARRAY_TEST(char);
HAMON_IS_ARRAY_TEST(float);
HAMON_IS_ARRAY_TEST(void*);
HAMON_IS_ARRAY_TEST(enum_UDT);
HAMON_IS_ARRAY_TEST(enum_class_UDT);
HAMON_IS_ARRAY_TEST(UDT);
HAMON_IS_ARRAY_TEST(empty_UDT);
HAMON_IS_ARRAY_TEST(union_UDT);

HAMON_IS_ARRAY_TEST_IMPL(false, f1);
HAMON_IS_ARRAY_TEST_IMPL(false, f2);
HAMON_IS_ARRAY_TEST_IMPL(false, f3);
HAMON_IS_ARRAY_TEST_IMPL(false, mf1);
HAMON_IS_ARRAY_TEST_IMPL(false, mf2);
HAMON_IS_ARRAY_TEST_IMPL(false, mf3);
HAMON_IS_ARRAY_TEST_IMPL(false, mf4);
HAMON_IS_ARRAY_TEST_IMPL(false, mp);
HAMON_IS_ARRAY_TEST_IMPL(false, cmf);
HAMON_IS_ARRAY_TEST_IMPL(false, void);
HAMON_IS_ARRAY_TEST_IMPL(false, test_abc1);
HAMON_IS_ARRAY_TEST_IMPL(false, test_abc3);
HAMON_IS_ARRAY_TEST_IMPL(false, test_abc3);
HAMON_IS_ARRAY_TEST_IMPL(false, convertible_to_pointer);
HAMON_IS_ARRAY_TEST_IMPL(false, foo0_t);
HAMON_IS_ARRAY_TEST_IMPL(false, foo1_t);
HAMON_IS_ARRAY_TEST_IMPL(false, foo2_t);
HAMON_IS_ARRAY_TEST_IMPL(false, foo3_t);
HAMON_IS_ARRAY_TEST_IMPL(false, foo4_t);

#undef HAMON_IS_ARRAY_TEST
#undef HAMON_IS_ARRAY_TEST_IMPL

}	// namespace is_array_test

}	// namespace hamon_type_traits_test
