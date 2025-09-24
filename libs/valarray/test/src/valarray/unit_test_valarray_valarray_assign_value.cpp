/**
 *	@file	unit_test_valarray_valarray_assign_value.cpp
 *
 *	@brief	operator= のテスト
 *
 *	valarray& operator=(const T&);
 */

#include <hamon/valarray/valarray.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_valarray_test
{

namespace valarray_assign_value_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	static_assert( hamon::is_assignable<hamon::valarray<T>, const T&>::value, "");
	static_assert(!hamon::is_nothrow_assignable<hamon::valarray<T>, const T&>::value, "");
	static_assert(!hamon::is_trivially_assignable<hamon::valarray<T>, const T&>::value, "");

	T a[] = { 1, 2, 3, 4, 5 };
	const unsigned N = sizeof(a) / sizeof(a[0]);
	hamon::valarray<T> v(a, N);
	v = 7;
	VERIFY(v.size() == N);
	for (hamon::size_t i = 0; i < v.size(); ++i)
	{
		VERIFY(v[i] == 7);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(ValArrayTest, ValarrayAssignValueTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<int>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<short>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<char>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<float>()));
}

}	// namespace valarray_assign_value_test

}	// namespace hamon_valarray_test
