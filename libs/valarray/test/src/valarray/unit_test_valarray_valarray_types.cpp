/**
 *	@file	unit_test_valarray_valarray_types.cpp
 *
 *	@brief	typedef のテスト
 *
 *	using value_type = T;
 */

#include <hamon/valarray/valarray.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_valarray_test
{

namespace valarray_types_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	static_assert(hamon::is_same<typename hamon::valarray<T>::value_type, T>::value, "");
	return true;
}

#undef VERIFY

GTEST_TEST(ValArrayTest, ValarrayTypesTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<int>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<float>()));
}

}	// namespace valarray_types_test

}	// namespace hamon_valarray_test
