﻿/**
 *	@file	unit_test_concepts_swap.cpp
 *
 *	@brief	swap のテスト
 */

#include <hamon/concepts/swap.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_concepts_test
{

namespace swap_test
{

struct S { bool swapped = false; };
inline HAMON_CXX14_CONSTEXPR void
swap(S& l, S& r)
{
	l.swapped = r.swapped = true;
}

struct T { int i; };

union U { char c; int i; };
inline HAMON_CXX14_CONSTEXPR void
swap(U& l, U& r)
{
	l.i = r.i = 99;
}

inline HAMON_CXX14_CONSTEXPR bool
check_struct_with_adl_swap(int )
{
	S s1, s2;
	hamon::ranges::swap(s1, s2);
	return s1.swapped && s2.swapped;
}

inline HAMON_CXX14_CONSTEXPR bool
check_array_with_adl_swap(int )
{
	S s1[2], s2[2];
	hamon::ranges::swap(s1, s2);
	return
		s1[0].swapped && s1[1].swapped &&
		s2[0].swapped && s2[1].swapped;
}

inline HAMON_CXX14_CONSTEXPR bool
check_struct_without_adl_swap(int i)
{
	T t1{i}, t2{2*i};
	hamon::ranges::swap(t1, t2);
	return t1.i == 2*i && t2.i == i;
}

inline HAMON_CXX14_CONSTEXPR bool
check_array_without_adl_swap(int i)
{
	T t1[2]{{i}, {2*i}}, t2[2]{{3*i}, {4*i}};
	hamon::ranges::swap(t1, t2);
	return
		t1[0].i == 3*i && t1[1].i == 4*i &&
		t2[0].i == i   && t2[1].i == 2*i;
}

inline HAMON_CXX20_CONSTEXPR bool
check_union_with_adl_swap(int i)
{
	U u1{}, u2{};
	u1.i = u2.i = i;
	hamon::ranges::swap(u1, u2);
	return u1.i == 99 && u2.i == 99;
}

GTEST_TEST(ConceptsTest, SwapTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(check_struct_with_adl_swap(1));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(check_array_with_adl_swap(1));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(check_struct_without_adl_swap(1));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(check_array_without_adl_swap(1));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(check_union_with_adl_swap(1));
}

}	// namespace swap_test

}	// namespace hamon_concepts_test
