/**
 *	@file	unit_test_valarray_gslice_array_comp_assign_or.cpp
 *
 *	@brief	operator|= のテスト
 *
 *	// [gslice.array.comp.assign]
 *	void operator|= (const valarray<T>&) const;
 */

#include <hamon/valarray/gslice_array.hpp>
#include <hamon/valarray/gslice.hpp>
#include <hamon/valarray/valarray.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_valarray_test
{

namespace gslice_array_comp_assign_or_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	T a1[] = { 0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11,
				12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23,
				24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35,
				36, 37, 38, 39, 40 };
	T a2[] = { 1,   2,   3,   4,   5,   6,   7,   8,   9,  10,  11, 12,
				 13,  14,  15,  16,  17,  18,  19,  20,  21,  22,  23, 24 };
	hamon::valarray<T> v1(a1, sizeof(a1) / sizeof(a1[0]));
	hamon::valarray<T> v2(a2, sizeof(a2) / sizeof(a2[0]));
	hamon::size_t sz[] = { 2, 4, 3 };
	hamon::size_t st[] = { 19, 4, 1 };
	typedef hamon::valarray<hamon::size_t> sizes;
	typedef hamon::valarray<hamon::size_t> strides;
	hamon::gslice gs(3, sizes(sz, sizeof(sz) / sizeof(sz[0])), strides(st, sizeof(st) / sizeof(st[0])));
	hamon::gslice_array<T> s1 = v1[gs];

	static_assert(hamon::is_same<decltype(s1 |= v2), void>::value, "");
	static_assert(!noexcept(s1 |= v2), "");

	s1 |= v2;
	VERIFY(v1.size() == 41);
	VERIFY(v1[0] == 0);
	VERIFY(v1[1] == 1);
	VERIFY(v1[2] == 2);
	VERIFY(v1[3] == 3);
	VERIFY(v1[4] == 6);
	VERIFY(v1[5] == 7);
	VERIFY(v1[6] == 6);
	VERIFY(v1[7] == 7);
	VERIFY(v1[8] == 13);
	VERIFY(v1[9] == 15);
	VERIFY(v1[10] == 10);
	VERIFY(v1[11] == 15);
	VERIFY(v1[12] == 12);
	VERIFY(v1[13] == 13);
	VERIFY(v1[14] == 14);
	VERIFY(v1[15] == 15);
	VERIFY(v1[16] == 27);
	VERIFY(v1[17] == 29);
	VERIFY(v1[18] == 18);
	VERIFY(v1[19] == 19);
	VERIFY(v1[20] == 20);
	VERIFY(v1[21] == 21);
	VERIFY(v1[22] == 31);
	VERIFY(v1[23] == 31);
	VERIFY(v1[24] == 31);
	VERIFY(v1[25] == 25);
	VERIFY(v1[26] == 26);
	VERIFY(v1[27] == 27);
	VERIFY(v1[28] == 30);
	VERIFY(v1[29] == 29);
	VERIFY(v1[30] == 31);
	VERIFY(v1[31] == 31);
	VERIFY(v1[32] == 53);
	VERIFY(v1[33] == 33);
	VERIFY(v1[34] == 54);
	VERIFY(v1[35] == 55);
	VERIFY(v1[36] == 60);
	VERIFY(v1[37] == 37);
	VERIFY(v1[38] == 38);
	VERIFY(v1[39] == 39);
	VERIFY(v1[40] == 40);

	return true;
}

#undef VERIFY

GTEST_TEST(ValArrayTest, GsliceArrayCompAssignOrTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<int>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<short>()));
}

}	// namespace gslice_array_comp_assign_or_test

}	// namespace hamon_valarray_test
