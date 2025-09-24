/**
 *	@file	unit_test_valarray_valarray_ctor_copy.cpp
 *
 *	@brief	コピーコンストラクタのテスト
 *
 *	valarray(const valarray&);
 */

#include <hamon/valarray/valarray.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_valarray_test
{

namespace valarray_ctor_copy_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	static_assert( hamon::is_copy_constructible<hamon::valarray<T>>::value, "");
	static_assert(!hamon::is_nothrow_copy_constructible<hamon::valarray<T>>::value, "");
	static_assert(!hamon::is_trivially_copy_constructible<hamon::valarray<T>>::value, "");
	static_assert( hamon::is_implicitly_copy_constructible<hamon::valarray<T>>::value, "");

	T a[] = { 1, 2, 3, 4, 5 };
	const unsigned N = sizeof(a) / sizeof(a[0]);
	hamon::valarray<T> v(a, N);
	hamon::valarray<T> v2 = v;
	VERIFY(v2.size() == v.size());
	for (hamon::size_t i = 0; i < v2.size(); ++i)
	{
		VERIFY(v2[i] == v[i]);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(ValArrayTest, ValarrayCtorCopyTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<int>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<short>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<char>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<float>()));
}

}	// namespace valarray_ctor_copy_test

}	// namespace hamon_valarray_test
