/**
 *	@file	unit_test_valarray_valarray_assign_mask_array.cpp
 *
 *	@brief	operator= のテスト
 *
 *	valarray& operator=(const mask_array<T>&);
 */

#include <hamon/valarray/valarray.hpp>
#include <hamon/valarray/mask_array.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_valarray_test
{

namespace valarray_assign_mask_array_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	static_assert(hamon::is_assignable<hamon::valarray<T>, const hamon::mask_array<T>&>::value, "");
	static_assert(!hamon::is_nothrow_assignable<hamon::valarray<T>, const hamon::mask_array<T>&>::value, "");
	static_assert(!hamon::is_trivially_assignable<hamon::valarray<T>, const hamon::mask_array<T>&>::value, "");

	T a1[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
	const hamon::size_t N1 = sizeof(a1) / sizeof(a1[0]);
	bool b[N1] = { true,  false, false, true,  true,  false,
				  false, true,  false, false, false, true };
	hamon::valarray<T> v1(a1, N1);
	hamon::valarray<bool> vb(b, N1);
	hamon::valarray<T> v2(5);
	v2 = v1[vb];
	VERIFY(v2.size() == 5);
	VERIFY(v2[0] == 0);
	VERIFY(v2[1] == 3);
	VERIFY(v2[2] == 4);
	VERIFY(v2[3] == 7);
	VERIFY(v2[4] == 11);

	return true;
}

#undef VERIFY

GTEST_TEST(ValArrayTest, ValarrayAssignMaskArrayTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<int>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<short>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<char>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<float>()));
}

}	// namespace valarray_assign_mask_array_test

}	// namespace hamon_valarray_test
