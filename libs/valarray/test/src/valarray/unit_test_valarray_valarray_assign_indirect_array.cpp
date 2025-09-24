/**
 *	@file	unit_test_valarray_valarray_assign_indirect_array.cpp
 *
 *	@brief	operator= のテスト
 *
 *	valarray& operator=(const indirect_array<T>&);
 */

#include <hamon/valarray/valarray.hpp>
#include <hamon/valarray/indirect_array.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_valarray_test
{

namespace valarray_assign_indirect_array_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	static_assert(hamon::is_assignable<hamon::valarray<T>, const hamon::indirect_array<T>&>::value, "");
	static_assert(!hamon::is_nothrow_assignable<hamon::valarray<T>, const hamon::indirect_array<T>&>::value, "");
	static_assert(!hamon::is_trivially_assignable<hamon::valarray<T>, const hamon::indirect_array<T>&>::value, "");

	T a[] = { 0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11,
			   12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23,
			   24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35,
			   36, 37, 38, 39, 40 };
	const hamon::size_t N1 = sizeof(a) / sizeof(a[0]);
	hamon::size_t s[] = { 3,  4,  5,  7,  8,  9, 11, 12, 13, 15, 16, 17,
					   22, 23, 24, 26, 27, 28, 30, 31, 32, 34, 35, 36 };
	const hamon::size_t S = sizeof(s) / sizeof(s[0]);
	hamon::valarray<T> v1(a, N1);
	hamon::valarray<hamon::size_t> ia(s, S);
	hamon::valarray<T> v(24);
	v = v1[ia];
	VERIFY(v.size() == 24);
	VERIFY(v[0] == 3);
	VERIFY(v[1] == 4);
	VERIFY(v[2] == 5);
	VERIFY(v[3] == 7);
	VERIFY(v[4] == 8);
	VERIFY(v[5] == 9);
	VERIFY(v[6] == 11);
	VERIFY(v[7] == 12);
	VERIFY(v[8] == 13);
	VERIFY(v[9] == 15);
	VERIFY(v[10] == 16);
	VERIFY(v[11] == 17);
	VERIFY(v[12] == 22);
	VERIFY(v[13] == 23);
	VERIFY(v[14] == 24);
	VERIFY(v[15] == 26);
	VERIFY(v[16] == 27);
	VERIFY(v[17] == 28);
	VERIFY(v[18] == 30);
	VERIFY(v[19] == 31);
	VERIFY(v[20] == 32);
	VERIFY(v[21] == 34);
	VERIFY(v[22] == 35);
	VERIFY(v[23] == 36);

	return true;
}

#undef VERIFY

GTEST_TEST(ValArrayTest, ValarrayAssignIndirectArrayTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<int>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<short>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<char>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<float>()));
}

}	// namespace valarray_assign_indirect_array_test

}	// namespace hamon_valarray_test
