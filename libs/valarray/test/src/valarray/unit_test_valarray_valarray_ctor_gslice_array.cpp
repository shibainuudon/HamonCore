/**
 *	@file	unit_test_valarray_valarray_ctor_gslice_array.cpp
 *
 *	@brief	gslice_arrayを引数に取るコンストラクタのテスト
 *
 *	valarray(const gslice_array<T>&);
 */

#include <hamon/valarray/valarray.hpp>
#include <hamon/valarray/gslice.hpp>
#include <hamon/valarray/gslice_array.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_valarray_test
{

namespace valarray_ctor_gslice_array_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	static_assert( hamon::is_constructible<hamon::valarray<T>, hamon::gslice_array<T> const&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<hamon::valarray<T>, hamon::gslice_array<T> const&>::value, "");
	static_assert( hamon::is_implicitly_constructible<hamon::valarray<T>, hamon::gslice_array<T> const&>::value, "");

	T a[] = { 0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11,
			   12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23,
			   24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35,
			   36, 37, 38, 39, 40 };
	hamon::valarray<T> v1(a, sizeof(a) / sizeof(a[0]));
	hamon::size_t sz[] = { 2, 4, 3 };
	hamon::size_t st[] = { 19, 4, 1 };
	typedef hamon::valarray<hamon::size_t> sizes;
	typedef hamon::valarray<hamon::size_t> strides;
	hamon::valarray<T> v(v1[hamon::gslice(3, sizes(sz, sizeof(sz) / sizeof(sz[0])), strides(st, sizeof(st) / sizeof(st[0])))]);
	VERIFY(v.size() == 24);
	VERIFY(v[0] == 3);
	VERIFY(v[1] == 4);
	VERIFY(v[2] == 5);
	VERIFY(v[3] == 7);
	VERIFY(v[4] == 8);
	VERIFY(v[5] == 9);
	VERIFY(v[6] == 11);
	VERIFY(v[7] == 12);
	VERIFY(v[8] == 13);
	VERIFY(v[9] == 15);
	VERIFY(v[10] == 16);
	VERIFY(v[11] == 17);
	VERIFY(v[12] == 22);
	VERIFY(v[13] == 23);
	VERIFY(v[14] == 24);
	VERIFY(v[15] == 26);
	VERIFY(v[16] == 27);
	VERIFY(v[17] == 28);
	VERIFY(v[18] == 30);
	VERIFY(v[19] == 31);
	VERIFY(v[20] == 32);
	VERIFY(v[21] == 34);
	VERIFY(v[22] == 35);
	VERIFY(v[23] == 36);

	return true;
}

#undef VERIFY

GTEST_TEST(ValArrayTest, ValarrayCtorGsliceArrayTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<int>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<short>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<char>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<float>()));
}

}	// namespace valarray_ctor_gslice_array_test

}	// namespace hamon_valarray_test
