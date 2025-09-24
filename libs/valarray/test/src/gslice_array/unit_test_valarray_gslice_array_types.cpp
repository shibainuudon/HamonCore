/**
 *	@file	unit_test_valarray_gslice_array_types.cpp
 *
 *	@brief	typedef のテスト
 *
 *	using value_type = T;
 */

#include <hamon/valarray/gslice_array.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_valarray_test
{

namespace gslice_array_types_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	static_assert((hamon::is_same<typename hamon::gslice_array<T>::value_type, T>::value), "");
	return true;
}

#undef VERIFY

GTEST_TEST(ValArrayTest, GsliceArrayTypesTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<int>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<short>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<float>()));
}

}	// namespace gslice_array_types_test

}	// namespace hamon_valarray_test
