/**
 *	@file	unit_test_valarray_valarray_min.cpp
 *
 *	@brief	min のテスト
 *
 *	T min() const;
 */

#include <hamon/valarray/valarray.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_valarray_test
{

namespace valarray_min_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	{
		hamon::valarray<T> va{1,2,3};

		static_assert(hamon::is_same<decltype(va.min()), T>::value, "");
		static_assert(!noexcept(va.min()), "");

		VERIFY(va.min() == T{1});

		va = {6,5,7,4};
		VERIFY(va.min() == T{4});
	}
	{
		T a1[] = { 1, 2, -3, 4, 5 };
		const unsigned N1 = sizeof(a1) / sizeof(a1[0]);
		hamon::valarray<T> v1(a1, N1);
		VERIFY(v1.min() == -3);
	}
	{
		T a1[] = { 1, 2, -3, 4, 5 };
		const unsigned N1 = sizeof(a1) / sizeof(a1[0]);
		hamon::valarray<T> v1(a1, N1);
		VERIFY((2 * v1).min() == -6.0);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(ValArrayTest, ValarrayMinTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<int>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<char>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<float>()));
}

}	// namespace valarray_min_test

}	// namespace hamon_valarray_test
