/**
 *	@file	unit_test_valarray_slice_array_comp_assign_mod.cpp
 *
 *	@brief	operator%= のテスト
 *
 *	// [slice.arr.comp.assign]
 *	void operator%= (const valarray<T>&) const;
 */

#include <hamon/valarray/slice_array.hpp>
#include <hamon/valarray/slice.hpp>
#include <hamon/valarray/valarray.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_valarray_test
{

namespace slice_array_comp_assign_mod_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	T a1[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
	T a2[] = { -1, -2, -3, -4, -5 };
	hamon::valarray<T> v1(a1, sizeof(a1) / sizeof(a1[0]));
	hamon::valarray<T> v2(a2, sizeof(a2) / sizeof(a2[0]));
	hamon::slice_array<T> s1 = v1[hamon::slice(1, 5, 3)];

	static_assert(hamon::is_same<decltype(s1 %= v2), void>::value, "");
	static_assert(!noexcept(s1 %= v2), "");

	s1 %= v2;
	VERIFY(v1.size() == 16);
	VERIFY(v1[0] == 0);
	VERIFY(v1[1] == 0);
	VERIFY(v1[2] == 2);
	VERIFY(v1[3] == 3);
	VERIFY(v1[4] == 0);
	VERIFY(v1[5] == 5);
	VERIFY(v1[6] == 6);
	VERIFY(v1[7] == 1);
	VERIFY(v1[8] == 8);
	VERIFY(v1[9] == 9);
	VERIFY(v1[10] == 2);
	VERIFY(v1[11] == 11);
	VERIFY(v1[12] == 12);
	VERIFY(v1[13] == 3);
	VERIFY(v1[14] == 14);
	VERIFY(v1[15] == 15);

	return true;
}

#undef VERIFY

GTEST_TEST(ValArrayTest, SliceArrayCompAssignModTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<int>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<short>()));
}

}	// namespace slice_array_comp_assign_mod_test

}	// namespace hamon_valarray_test
