/**
 *	@file	unit_test_valarray_mask_array_assign_value.cpp
 *
 *	@brief	operator= のテスト
 *
 *	// [mask.array.fill]
 *	void operator=(const T&) const;
 */

#include <hamon/valarray/mask_array.hpp>
#include <hamon/valarray/valarray.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_valarray_test
{

namespace mask_array_assign_value_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	T a1[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
	const hamon::size_t N1 = sizeof(a1) / sizeof(a1[0]);
	bool b[N1] = { true,  false, false, true,  true,  false,
				  false, true,  false, false, false, true };
	hamon::valarray<T> v1(a1, N1);
	hamon::valarray<bool> vb(b, N1);
	hamon::mask_array<T> s1 = v1[vb];

	static_assert(hamon::is_same<decltype(s1 = hamon::declval<T const&>()), void>::value, "");
	static_assert(!noexcept(s1 = hamon::declval<T const&>()), "");

	s1 = T{-5};
	VERIFY(v1.size() == 16);
	VERIFY(v1[0] == -5);
	VERIFY(v1[1] == 1);
	VERIFY(v1[2] == 2);
	VERIFY(v1[3] == -5);
	VERIFY(v1[4] == -5);
	VERIFY(v1[5] == 5);
	VERIFY(v1[6] == 6);
	VERIFY(v1[7] == -5);
	VERIFY(v1[8] == 8);
	VERIFY(v1[9] == 9);
	VERIFY(v1[10] == 10);
	VERIFY(v1[11] == -5);
	VERIFY(v1[12] == 12);
	VERIFY(v1[13] == 13);
	VERIFY(v1[14] == 14);
	VERIFY(v1[15] == 15);

	return true;
}

#undef VERIFY

GTEST_TEST(ValArrayTest, MaskArrayAssignValueTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<int>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<short>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<float>()));
}

}	// namespace mask_array_assign_value_test

}	// namespace hamon_valarray_test
