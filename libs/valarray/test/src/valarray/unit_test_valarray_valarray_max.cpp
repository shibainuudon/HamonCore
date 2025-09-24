/**
 *	@file	unit_test_valarray_valarray_max.cpp
 *
 *	@brief	max のテスト
 *
 *	T max() const;
 */

#include <hamon/valarray/valarray.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_valarray_test
{

namespace valarray_max_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	{
		hamon::valarray<T> va{ 1,2,3 };

		static_assert(hamon::is_same<decltype(va.max()), T>::value, "");
		static_assert(!noexcept(va.max()), "");

		VERIFY(va.max() == T{ 3 });

		va = { 6,5,7,4 };
		VERIFY(va.max() == T{ 7 });
	}
	{
		T a1[] = { 1, 2, -3, 4, -5 };
		const unsigned N1 = sizeof(a1) / sizeof(a1[0]);
		hamon::valarray<T> v1(a1, N1);
		VERIFY(v1.max() == 4);
	}
	{
		T a1[] = { 1, 2, -3, 4, -5 };
		const unsigned N1 = sizeof(a1) / sizeof(a1[0]);
		hamon::valarray<T> v1(a1, N1);
		VERIFY((2 * v1).max() == 8);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(ValArrayTest, ValarrayMaxTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<int>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<char>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<float>()));
}

}	// namespace valarray_max_test

}	// namespace hamon_valarray_test
