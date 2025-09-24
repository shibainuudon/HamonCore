/**
 *	@file	unit_test_valarray_slice_array_ctor.cpp
 *
 *	@brief	コンストラクタのテスト
 *
 *	slice_array(const slice_array&);
 *	slice_array() = delete;
 */

#include <hamon/valarray/slice_array.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_valarray_test
{

namespace slice_array_ctor_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	static_assert(!hamon::is_default_constructible<hamon::slice_array<T>>::value, "");

	static_assert(hamon::is_copy_constructible<hamon::slice_array<T>>::value, "");
#if !defined(HAMON_USE_STD_VALARRAY)
	static_assert(hamon::is_nothrow_copy_constructible<hamon::slice_array<T>>::value, "");
	static_assert(hamon::is_trivially_copy_constructible<hamon::slice_array<T>>::value, "");
#endif
	static_assert(hamon::is_implicitly_copy_constructible<hamon::slice_array<T>>::value, "");

	return true;
}

#undef VERIFY

GTEST_TEST(ValArrayTest, SliceArrayCtorTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<int>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<short>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<float>()));
}

}	// namespace slice_array_ctor_test

}	// namespace hamon_valarray_test
