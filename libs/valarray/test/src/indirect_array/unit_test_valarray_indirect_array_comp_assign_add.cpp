/**
 *	@file	unit_test_valarray_indirect_array_comp_assign_add.cpp
 *
 *	@brief	operator+= のテスト
 *
 *	// [indirect.array.comp.assign]
 *	void operator+= (const valarray<T>&) const;
 */

#include <hamon/valarray/indirect_array.hpp>
#include <hamon/valarray/valarray.hpp>
#include <hamon/algorithm/count.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_valarray_test
{

namespace indirect_array_comp_assign_add_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	T a1[] = { 0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11,
			12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23,
			24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35,
			36, 37, 38, 39, 40 };
	const hamon::size_t N1 = sizeof(a1) / sizeof(a1[0]);
	T a2[] = { -0,  -1,  -2,  -3,  -4,  -5,  -6,  -7,  -8,  -9, -10, -11,
				-12, -13, -14, -15, -16, -17, -18, -19, -20, -21, -22, -23 };
	const hamon::size_t N2 = sizeof(a2) / sizeof(a2[0]);
	hamon::size_t s[N2] = { 3,  4,  5,  7,  8,  9, 11, 12, 13, 15, 16, 17,
						 22, 23, 24, 26, 27, 28, 30, 31, 32, 34, 35, 36 };
	hamon::valarray<T> v1(a1, N1);
	hamon::valarray<T> v2(a2, N2);
	hamon::valarray<hamon::size_t> ia(s, N2);
	hamon::indirect_array<T> s1 = v1[ia];

	static_assert(hamon::is_same<decltype(s1 += v2), void>::value, "");
	static_assert(!noexcept(s1 += v2), "");

	s1 += v2;
	VERIFY(v1.size() == 41);
	VERIFY(v1[0] == 0);
	VERIFY(v1[1] == 1);
	VERIFY(v1[2] == 2);
	VERIFY(v1[3] == 3);
	VERIFY(v1[4] == 3);
	VERIFY(v1[5] == 3);
	VERIFY(v1[6] == 6);
	VERIFY(v1[7] == 4);
	VERIFY(v1[8] == 4);
	VERIFY(v1[9] == 4);
	VERIFY(v1[10] == 10);
	VERIFY(v1[11] == 5);
	VERIFY(v1[12] == 5);
	VERIFY(v1[13] == 5);
	VERIFY(v1[14] == 14);
	VERIFY(v1[15] == 6);
	VERIFY(v1[16] == 6);
	VERIFY(v1[17] == 6);
	VERIFY(v1[18] == 18);
	VERIFY(v1[19] == 19);
	VERIFY(v1[20] == 20);
	VERIFY(v1[21] == 21);
	VERIFY(v1[22] == 10);
	VERIFY(v1[23] == 10);
	VERIFY(v1[24] == 10);
	VERIFY(v1[25] == 25);
	VERIFY(v1[26] == 11);
	VERIFY(v1[27] == 11);
	VERIFY(v1[28] == 11);
	VERIFY(v1[29] == 29);
	VERIFY(v1[30] == 12);
	VERIFY(v1[31] == 12);
	VERIFY(v1[32] == 12);
	VERIFY(v1[33] == 33);
	VERIFY(v1[34] == 13);
	VERIFY(v1[35] == 13);
	VERIFY(v1[36] == 13);
	VERIFY(v1[37] == 37);
	VERIFY(v1[38] == 38);
	VERIFY(v1[39] == 39);
	VERIFY(v1[40] == 40);

	return true;
}

#undef VERIFY

GTEST_TEST(ValArrayTest, IndirectArrayCompAssignAddTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<int>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<short>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<float>()));
}

}	// namespace indirect_array_comp_assign_add_test

}	// namespace hamon_valarray_test
