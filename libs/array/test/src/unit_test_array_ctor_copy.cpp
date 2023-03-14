/**
 *	@file	unit_test_array_ctor_copy.cpp
 *
 *	@brief	コピーコンストラクタのテスト
 */

#include <hamon/array/array.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_array_test
{

namespace ctor_copy_test
{

template <typename T>
void CtorCopyTest()
{
	static_assert( hamon::is_copy_constructible<hamon::array<T, 0>>::value, "");
	static_assert( hamon::is_copy_constructible<hamon::array<T, 1>>::value, "");
	static_assert( hamon::is_copy_constructible<hamon::array<T, 2>>::value, "");
	static_assert( hamon::is_copy_constructible<hamon::array<T, 3>>::value, "");

	static_assert( hamon::is_copy_constructible<hamon::array<T const, 0>>::value, "");
	static_assert( hamon::is_copy_constructible<hamon::array<T const, 1>>::value, "");
	static_assert( hamon::is_copy_constructible<hamon::array<T const, 2>>::value, "");
	static_assert( hamon::is_copy_constructible<hamon::array<T const, 3>>::value, "");

	static_assert( hamon::is_copy_assignable<hamon::array<T, 0>>::value, "");
	static_assert( hamon::is_copy_assignable<hamon::array<T, 1>>::value, "");
	static_assert( hamon::is_copy_assignable<hamon::array<T, 2>>::value, "");
	static_assert( hamon::is_copy_assignable<hamon::array<T, 3>>::value, "");

#if !defined(HAMON_USE_STD_ARRAY)
	static_assert( hamon::is_copy_assignable<hamon::array<T const, 0>>::value, "");
#endif
	static_assert(!hamon::is_copy_assignable<hamon::array<T const, 1>>::value, "");
	static_assert(!hamon::is_copy_assignable<hamon::array<T const, 2>>::value, "");
	static_assert(!hamon::is_copy_assignable<hamon::array<T const, 3>>::value, "");

	{
		HAMON_CXX11_CONSTEXPR hamon::array<T, 3> a1 { T(1), T(2), T(3) };
		HAMON_CXX11_CONSTEXPR hamon::array<T, 3> a2 = a1;
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(1), a2[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(2), a2[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(3), a2[2]);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::array<T, 0> a1 {};
		HAMON_CXX11_CONSTEXPR hamon::array<T, 0> a2 = a1;
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0u, a2.size());
	}
}

GTEST_TEST(ArrayTest, CtorCopyTest)
{
	CtorCopyTest<char>();
	CtorCopyTest<int>();
	CtorCopyTest<float>();
	CtorCopyTest<double>();
}

}	// namespace ctor_copy_test

}	// namespace hamon_array_test
