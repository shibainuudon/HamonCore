/**
 *	@file	unit_test_type_traits_rank.cpp
 *
 *	@brief	rank のテスト
 */

#include <hamon/type_traits/rank.hpp>
#include <hamon/cstddef/nullptr_t.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "type_traits_test_utility.hpp"

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

#define HAMON_RANK_TEST_IMPL(T, N)	\
	static_assert(hamon::rank_v<T>      == N, "");	\
	static_assert(hamon::rank<T>::value == N, "");	\
	static_assert(hamon::rank<T>{}()    == N, "");	\
	static_assert(hamon::rank<T>{}      == N, "")

#else

#define HAMON_RANK_TEST_IMPL(T, N)	\
	static_assert(hamon::rank<T>::value == N, "");	\
	static_assert(hamon::rank<T>{}()    == N, "");	\
	static_assert(hamon::rank<T>{}      == N, "")

#endif

#define HAMON_RANK_TEST_CV(T, N)	\
	HAMON_RANK_TEST_IMPL(T, N);	\
	HAMON_RANK_TEST_IMPL(const T, N);	\
	HAMON_RANK_TEST_IMPL(volatile T, N);	\
	HAMON_RANK_TEST_IMPL(const volatile T, N)

#define HAMON_RANK_TEST(T)	\
	HAMON_RANK_TEST_CV(T, 0);	\
	HAMON_RANK_TEST_CV(T[], 1);	\
	HAMON_RANK_TEST_CV(T[2], 1);	\
	HAMON_RANK_TEST_CV(T[2][3], 2);	\
	HAMON_RANK_TEST_CV(T[][3], 2);	\
	HAMON_RANK_TEST_CV(T[4][5][6], 3);	\
	HAMON_RANK_TEST_CV(T[][2][3], 3);	\
	HAMON_RANK_TEST_CV(T[1][2][3][4], 4);	\
	HAMON_RANK_TEST_CV(T[][2][3][4][6], 5)

HAMON_RANK_TEST(bool);
HAMON_RANK_TEST(char);
HAMON_RANK_TEST(int);
HAMON_RANK_TEST(float);
HAMON_RANK_TEST(double);
HAMON_RANK_TEST(void*);
HAMON_RANK_TEST(hamon::nullptr_t);
HAMON_RANK_TEST(decltype(nullptr));
HAMON_RANK_TEST(enum_UDT);
HAMON_RANK_TEST(enum_class_UDT);
HAMON_RANK_TEST(UDT);
HAMON_RANK_TEST(POD_UDT);
HAMON_RANK_TEST(union_UDT);
HAMON_RANK_TEST(POD_union_UDT);
HAMON_RANK_TEST(f1);
HAMON_RANK_TEST(f2);
HAMON_RANK_TEST(f3);
HAMON_RANK_TEST(mf1);
HAMON_RANK_TEST(mf2);
HAMON_RANK_TEST(mf3);
HAMON_RANK_TEST(mf4);
HAMON_RANK_TEST(mp);
HAMON_RANK_TEST(cmf);

#undef HAMON_RANK_TEST
#undef HAMON_RANK_TEST_CV
#undef HAMON_RANK_TEST_IMPL
