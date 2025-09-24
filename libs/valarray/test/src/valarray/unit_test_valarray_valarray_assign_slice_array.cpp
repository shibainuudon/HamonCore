/**
 *	@file	unit_test_valarray_valarray_assign_slice_array.cpp
 *
 *	@brief	operator= のテスト
 *
 *	valarray& operator=(const slice_array<T>&);
 */

#include <hamon/valarray/valarray.hpp>
#include <hamon/valarray/slice.hpp>
#include <hamon/valarray/slice_array.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_valarray_test
{

namespace valarray_assign_slice_array_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	static_assert(hamon::is_assignable<hamon::valarray<T>, const hamon::slice_array<T>&>::value, "");
	static_assert(!hamon::is_nothrow_assignable<hamon::valarray<T>, const hamon::slice_array<T>&>::value, "");
	static_assert(!hamon::is_trivially_assignable<hamon::valarray<T>, const hamon::slice_array<T>&>::value, "");

	T a[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
	hamon::valarray<T> v1(a, sizeof(a) / sizeof(a[0]));
	hamon::valarray<T> v(5);
	v = v1[hamon::slice(1, 5, 3)];
	VERIFY(v.size() == 5);
	VERIFY(v[0] == 1);
	VERIFY(v[1] == 4);
	VERIFY(v[2] == 7);
	VERIFY(v[3] == 10);
	VERIFY(v[4] == 13);

	return true;
}

#undef VERIFY

GTEST_TEST(ValArrayTest, ValarrayAssignSliceArrayTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<int>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<short>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<char>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<float>()));
}

}	// namespace valarray_assign_slice_array_test

}	// namespace hamon_valarray_test
