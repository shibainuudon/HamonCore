/**
 *	@file	unit_test_type_traits_is_unbounded_array.cpp
 *
 *	@brief	is_unbounded_array のテスト
 */

#include <hamon/type_traits/is_unbounded_array.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "type_traits_test_utility.hpp"

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

#define HAMON_IS_UNBOUNDED_ARRAY_TEST(b, T)	\
	static_assert(hamon::is_unbounded_array_v<T>      == b, #T);	\
	static_assert(hamon::is_unbounded_array<T>::value == b, #T);	\
	static_assert(hamon::is_unbounded_array<T>()      == b, #T)

#else

#define HAMON_IS_UNBOUNDED_ARRAY_TEST(b, T)	\
	static_assert(hamon::is_unbounded_array<T>::value == b, #T);	\
	static_assert(hamon::is_unbounded_array<T>()      == b, #T)

#endif

#define HAMON_IS_UNBOUNDED_ARRAY_TEST_CV(b, T)	\
	HAMON_IS_UNBOUNDED_ARRAY_TEST(b,                T);	\
	HAMON_IS_UNBOUNDED_ARRAY_TEST(b, const          T);	\
	HAMON_IS_UNBOUNDED_ARRAY_TEST(b,       volatile T);	\
	HAMON_IS_UNBOUNDED_ARRAY_TEST(b, const volatile T)

HAMON_IS_UNBOUNDED_ARRAY_TEST_CV(false, int);
HAMON_IS_UNBOUNDED_ARRAY_TEST_CV(true,  int[]);
HAMON_IS_UNBOUNDED_ARRAY_TEST_CV(false, int[3]);
HAMON_IS_UNBOUNDED_ARRAY_TEST_CV(false, int[4][5]);
HAMON_IS_UNBOUNDED_ARRAY_TEST_CV(true,  int[][5]);
HAMON_IS_UNBOUNDED_ARRAY_TEST_CV(false, int*);
HAMON_IS_UNBOUNDED_ARRAY_TEST_CV(false, int&);
HAMON_IS_UNBOUNDED_ARRAY_TEST_CV(false, int&&);

HAMON_IS_UNBOUNDED_ARRAY_TEST_CV(false, char);
HAMON_IS_UNBOUNDED_ARRAY_TEST_CV(true,  char[]);
HAMON_IS_UNBOUNDED_ARRAY_TEST_CV(false, char[4]);
HAMON_IS_UNBOUNDED_ARRAY_TEST_CV(false, float);
HAMON_IS_UNBOUNDED_ARRAY_TEST_CV(false, void*);
HAMON_IS_UNBOUNDED_ARRAY_TEST_CV(false, enum_UDT);
HAMON_IS_UNBOUNDED_ARRAY_TEST_CV(false, enum_class_UDT);
HAMON_IS_UNBOUNDED_ARRAY_TEST_CV(false, UDT);
HAMON_IS_UNBOUNDED_ARRAY_TEST_CV(false, empty_UDT);
HAMON_IS_UNBOUNDED_ARRAY_TEST_CV(false, union_UDT);
HAMON_IS_UNBOUNDED_ARRAY_TEST_CV(false, incomplete_type);
HAMON_IS_UNBOUNDED_ARRAY_TEST_CV(true,  incomplete_type[]);
HAMON_IS_UNBOUNDED_ARRAY_TEST_CV(false, incomplete_type[5]);

#undef HAMON_IS_UNBOUNDED_ARRAY_TEST
#undef HAMON_IS_UNBOUNDED_ARRAY_TEST_CV
