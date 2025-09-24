/**
 *	@file	unit_test_valarray_mask_array_assign_mask_array.cpp
 *
 *	@brief	operator= のテスト
 *
 *	// [mask.array.assign]
 *	const mask_array& operator=(const mask_array&) const;
 */

#include <hamon/valarray/mask_array.hpp>
#include <hamon/valarray/valarray.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_valarray_test
{

namespace mask_array_assign_mask_array_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	T a1[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
	const hamon::size_t N1 = sizeof(a1) / sizeof(a1[0]);
	bool b1[N1] = { true,  false, false, true,  true,  false,
					false, true,  false, false, false, true };
	T a2[] = { -1, -2, -3, -4, -5, -6, -7, -8 };
	const hamon::size_t N2 = sizeof(a2) / sizeof(a2[0]);
	bool b2[N2] = { true,  false, true, true,
					false, false, true, true };
	hamon::valarray<T> v1(a1, N1);
	hamon::valarray<T> v2(a2, N2);
	hamon::valarray<bool> vb1(b1, N1);
	hamon::valarray<bool> vb2(b2, N2);
	hamon::mask_array<T> s1 = v1[vb1];
	hamon::mask_array<T> s2 = v2[vb2];

#if !defined(HAMON_USE_STD_VALARRAY)
	static_assert(hamon::is_same<decltype(s1 = s2), hamon::mask_array<T> const&>::value, "");
	static_assert(noexcept(s1 = s2), "");
#endif

	auto& t = (s1 = s2);
	VERIFY(&t == &s1);

	VERIFY(v1.size() == 16);
	VERIFY(v1[0] == -1);
	VERIFY(v1[1] == 1);
	VERIFY(v1[2] == 2);
	VERIFY(v1[3] == -3);
	VERIFY(v1[4] == -4);
	VERIFY(v1[5] == 5);
	VERIFY(v1[6] == 6);
	VERIFY(v1[7] == -7);
	VERIFY(v1[8] == 8);
	VERIFY(v1[9] == 9);
	VERIFY(v1[10] == 10);
	VERIFY(v1[11] == -8);
	VERIFY(v1[12] == 12);
	VERIFY(v1[13] == 13);
	VERIFY(v1[14] == 14);
	VERIFY(v1[15] == 15);

	return true;
}

#undef VERIFY

GTEST_TEST(ValArrayTest, MaskArrayAssignMaskArrayTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<int>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<short>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<float>()));
}

}	// namespace mask_array_assign_mask_array_test

}	// namespace hamon_valarray_test
