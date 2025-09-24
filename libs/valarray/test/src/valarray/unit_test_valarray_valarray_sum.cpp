/**
 *	@file	unit_test_valarray_valarray_sum.cpp
 *
 *	@brief	sum のテスト
 *
 *	T sum() const;
 */

#include <hamon/valarray/valarray.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_valarray_test
{

namespace valarray_sum_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	hamon::valarray<T> va{1,2,3};

	static_assert(hamon::is_same<decltype(va.sum()), T>::value, "");
	static_assert(!noexcept(va.sum()), "");

	VERIFY(va.sum() == T{6});

	va = {6,5,7,4};
	VERIFY(va.sum() == T{22});

	return true;
}

#undef VERIFY

GTEST_TEST(ValArrayTest, ValarraySumTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<int>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<char>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<float>()));
}

}	// namespace valarray_sum_test

}	// namespace hamon_valarray_test
