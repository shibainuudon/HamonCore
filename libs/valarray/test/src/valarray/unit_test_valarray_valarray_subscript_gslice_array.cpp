/**
 *	@file	unit_test_valarray_valarray_subscript_gslice_array.cpp
 *
 *	@brief	operator[] のテスト
 *
 *	valarray          operator[](const gslice&) const;
 *	gslice_array<T>   operator[](const gslice&);
 */

#include <hamon/valarray/valarray.hpp>
#include <hamon/valarray/gslice.hpp>
#include <hamon/valarray/gslice_array.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_valarray_test
{

namespace valarray_subscript_gslice_array_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	// valarray          operator[](const gslice&) const;
	{
		hamon::valarray<T> const va{0,1,2,3,4,5,6,7,8,9,10,11,12,13,14};

		const hamon::size_t start = 1u;
		const hamon::valarray<hamon::size_t> lengths = { 3u, 2u };
		const hamon::valarray<hamon::size_t> strides = { 5u, 3u };
		const hamon::gslice sl(start, lengths, strides);

#if !defined(HAMON_USE_STD_VALARRAY)
		static_assert(hamon::is_same<decltype(va[sl]), hamon::valarray<T>>::value, "");
		static_assert(!noexcept(va[sl]), "");
#endif

		hamon::valarray<T> result = va[sl];

		VERIFY(result[0] == 1);
		VERIFY(result[1] == 4);
		VERIFY(result[2] == 6);
		VERIFY(result[3] == 9);
		VERIFY(result[4] == 11);
		VERIFY(result[5] == 14);
	}
	{
		T a1[] = { 0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11,
					12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23,
					24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35,
					36, 37, 38, 39, 40 };
		T a2[] = { -0,  -1,  -2,  -3,  -4,  -5,  -6,  -7,  -8,  -9, -10, -11,
					-12, -13, -14, -15, -16, -17, -18, -19, -20, -21, -22, -23 };
		hamon::valarray<T> v1(a1, sizeof(a1) / sizeof(a1[0]));
		hamon::valarray<T> v2(a2, sizeof(a2) / sizeof(a2[0]));
		hamon::size_t sz[] = { 2, 4, 3 };
		hamon::size_t st[] = { 19, 4, 1 };
		typedef hamon::valarray<hamon::size_t> sizes;
		typedef hamon::valarray<hamon::size_t> strides;
		v1[hamon::gslice(3, sizes(sz, sizeof(sz) / sizeof(sz[0])),
			strides(st, sizeof(st) / sizeof(st[0])))] = v2;
		VERIFY(v1.size() == 41);
		VERIFY(v1[0] == 0);
		VERIFY(v1[1] == 1);
		VERIFY(v1[2] == 2);
		VERIFY(v1[3] == 0);
		VERIFY(v1[4] == -1);
		VERIFY(v1[5] == -2);
		VERIFY(v1[6] == 6);
		VERIFY(v1[7] == -3);
		VERIFY(v1[8] == -4);
		VERIFY(v1[9] == -5);
		VERIFY(v1[10] == 10);
		VERIFY(v1[11] == -6);
		VERIFY(v1[12] == -7);
		VERIFY(v1[13] == -8);
		VERIFY(v1[14] == 14);
		VERIFY(v1[15] == -9);
		VERIFY(v1[16] == -10);
		VERIFY(v1[17] == -11);
		VERIFY(v1[18] == 18);
		VERIFY(v1[19] == 19);
		VERIFY(v1[20] == 20);
		VERIFY(v1[21] == 21);
		VERIFY(v1[22] == -12);
		VERIFY(v1[23] == -13);
		VERIFY(v1[24] == -14);
		VERIFY(v1[25] == 25);
		VERIFY(v1[26] == -15);
		VERIFY(v1[27] == -16);
		VERIFY(v1[28] == -17);
		VERIFY(v1[29] == 29);
		VERIFY(v1[30] == -18);
		VERIFY(v1[31] == -19);
		VERIFY(v1[32] == -20);
		VERIFY(v1[33] == 33);
		VERIFY(v1[34] == -21);
		VERIFY(v1[35] == -22);
		VERIFY(v1[36] == -23);
		VERIFY(v1[37] == 37);
		VERIFY(v1[38] == 38);
		VERIFY(v1[39] == 39);
		VERIFY(v1[40] == 40);
	}

	// gslice_array<T>   operator[](const gslice&);
	{
		hamon::valarray<T> va{0,1,2,3,4,5,6,7,8,9,10,11,12,13,14};

		const hamon::size_t start = 1u;
		const hamon::valarray<hamon::size_t> lengths = { 3u, 2u };
		const hamon::valarray<hamon::size_t> strides = { 5u, 1u };
		const hamon::gslice sl(start, lengths, strides);

		static_assert(hamon::is_same<decltype(va[sl]), hamon::gslice_array<T>>::value, "");
#if !defined(HAMON_USE_STD_VALARRAY)
		static_assert(!noexcept(va[sl]), "");
#endif

		hamon::gslice_array<T> result = va[sl];

		// 抽出した要素を99で埋める
		result = 99;

		// 参照元が書き換わっていることを確認する
		VERIFY(va[0] == 0);
		VERIFY(va[1] == 99);
		VERIFY(va[2] == 99);
		VERIFY(va[3] == 3);
		VERIFY(va[4] == 4);
		VERIFY(va[5] == 5);
		VERIFY(va[6] == 99);
		VERIFY(va[7] == 99);
		VERIFY(va[8] == 8);
		VERIFY(va[9] == 9);
		VERIFY(va[10] == 10);
		VERIFY(va[11] == 99);
		VERIFY(va[12] == 99);
		VERIFY(va[13] == 13);
		VERIFY(va[14] == 14);
	}
	{
		T a[] = { 0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11,
				   12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23,
				   24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35,
				   36, 37, 38, 39, 40 };
		hamon::valarray<T> v1(a, sizeof(a) / sizeof(a[0]));
		hamon::size_t sz[] = { 2, 4, 3 };
		hamon::size_t st[] = { 19, 4, 1 };
		typedef hamon::valarray<hamon::size_t> sizes;
		typedef hamon::valarray<hamon::size_t> strides;
		hamon::valarray<T> v(v1[hamon::gslice(3, sizes(sz, sizeof(sz) / sizeof(sz[0])),
			strides(st, sizeof(st) / sizeof(st[0])))]);
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
	}
	{
		T a[] = { 0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11,
					12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23,
					24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35,
					36, 37, 38, 39, 40 };
		hamon::valarray<T> v1(a, sizeof(a) / sizeof(a[0]));
		hamon::size_t sz[] = { 2, 4, 3 };
		hamon::size_t st[] = { 19, 4, 1 };
		typedef hamon::valarray<hamon::size_t> sizes;
		typedef hamon::valarray<hamon::size_t> strides;
		hamon::valarray<T> v((v1 + 0)[hamon::gslice(3, sizes(sz, sizeof(sz) / sizeof(sz[0])),
			strides(st, sizeof(st) / sizeof(st[0])))]);
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
	}

	return true;
}

#undef VERIFY

GTEST_TEST(ValArrayTest, ValarraySubscriptGsliceArrayTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<int>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<short>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<char>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<float>()));
}

}	// namespace valarray_subscript_gslice_array_test

}	// namespace hamon_valarray_test
