/**
 *	@file	unit_test_valarray_indirect_array_assign_value.cpp
 *
 *	@brief	operator= のテスト
 *
 *	// [indirect.array.fill]
 *	void operator=(const T&) const;
 */

#include <hamon/valarray/indirect_array.hpp>
#include <hamon/valarray/valarray.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_valarray_test
{

namespace indirect_array_assign_value_test
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
	hamon::size_t s[] = { 3,  4,  5,  7,  8,  9, 11, 12, 13, 15, 16, 17,
					   22, 23, 24, 26, 27, 28, 30, 31, 32, 34, 35, 36 };
	const hamon::size_t S = sizeof(s) / sizeof(s[0]);
	hamon::valarray<T> v1(a1, N1);
	hamon::valarray<hamon::size_t> ia(s, S);
	hamon::indirect_array<T> s1 = v1[ia];

	static_assert(hamon::is_same<decltype(s1 = hamon::declval<T const&>()), void>::value, "");
	static_assert(!noexcept(s1 = hamon::declval<T const&>()), "");

	s1 = T{51};
	VERIFY(v1.size() == 41);
	VERIFY(v1[0] == 0);
	VERIFY(v1[1] == 1);
	VERIFY(v1[2] == 2);
	VERIFY(v1[3] == 51);
	VERIFY(v1[4] == 51);
	VERIFY(v1[5] == 51);
	VERIFY(v1[6] == 6);
	VERIFY(v1[7] == 51);
	VERIFY(v1[8] == 51);
	VERIFY(v1[9] == 51);
	VERIFY(v1[10] == 10);
	VERIFY(v1[11] == 51);
	VERIFY(v1[12] == 51);
	VERIFY(v1[13] == 51);
	VERIFY(v1[14] == 14);
	VERIFY(v1[15] == 51);
	VERIFY(v1[16] == 51);
	VERIFY(v1[17] == 51);
	VERIFY(v1[18] == 18);
	VERIFY(v1[19] == 19);
	VERIFY(v1[20] == 20);
	VERIFY(v1[21] == 21);
	VERIFY(v1[22] == 51);
	VERIFY(v1[23] == 51);
	VERIFY(v1[24] == 51);
	VERIFY(v1[25] == 25);
	VERIFY(v1[26] == 51);
	VERIFY(v1[27] == 51);
	VERIFY(v1[28] == 51);
	VERIFY(v1[29] == 29);
	VERIFY(v1[30] == 51);
	VERIFY(v1[31] == 51);
	VERIFY(v1[32] == 51);
	VERIFY(v1[33] == 33);
	VERIFY(v1[34] == 51);
	VERIFY(v1[35] == 51);
	VERIFY(v1[36] == 51);
	VERIFY(v1[37] == 37);
	VERIFY(v1[38] == 38);
	VERIFY(v1[39] == 39);
	VERIFY(v1[40] == 40);

	return true;
}

#undef VERIFY

GTEST_TEST(ValArrayTest, IndirectArrayAssignValueTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<int>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<short>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<float>()));
}

}	// namespace indirect_array_assign_value_test

}	// namespace hamon_valarray_test
