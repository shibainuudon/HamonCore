/**
 *	@file	unit_test_valarray_valarray_subscript_slice_array.cpp
 *
 *	@brief	operator[] のテスト
 *
 *	valarray          operator[](slice) const;
 *	slice_array<T>    operator[](slice);
 */

#include <hamon/valarray/valarray.hpp>
#include <hamon/valarray/slice.hpp>
#include <hamon/valarray/slice_array.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_valarray_test
{

namespace valarray_subscript_slice_array_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	// valarray          operator[](slice) const;
	{
		const hamon::valarray<T> va = { 1, 2, 3, 4, 5, 6 };

		const hamon::size_t start = 1u;  // 開始位置
		const hamon::size_t length = 3u; // 要素数
		const hamon::size_t stride = 2u; // 何個置きに処理するか
		const hamon::slice sl(start, length, stride);

#if !defined(HAMON_USE_STD_VALARRAY)
		static_assert(hamon::is_same<decltype(va[sl]), hamon::valarray<T>>::value, "");
		static_assert(!noexcept(va[sl]), "");
#endif

		hamon::valarray<T> result = va[sl];

		VERIFY(result.size() == 3);
		VERIFY(result[0] == 2);
		VERIFY(result[1] == 4);
		VERIFY(result[2] == 6);
	}
	{
		T a1[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
		const hamon::valarray<T> v1(a1, sizeof(a1) / sizeof(a1[0]));
		hamon::valarray<T> v2 = v1[hamon::slice(1, 5, 3)];
		VERIFY(v2.size() == 5);
		VERIFY(v2[0] == 1);
		VERIFY(v2[1] == 4);
		VERIFY(v2[2] == 7);
		VERIFY(v2[3] == 10);
		VERIFY(v2[4] == 13);
	}
	{
		T a1[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
		const hamon::valarray<T> v1(a1, sizeof(a1) / sizeof(a1[0]));
		hamon::valarray<T> v2 = (v1 + 0)[hamon::slice(0, 2, 3)];
		VERIFY(v2.size() == 2);
		VERIFY(v2[0] == 0);
		VERIFY(v2[1] == 3);
}

	// slice_array<T>    operator[](slice);
	{
		hamon::valarray<T> va = { 1, 2, 3, 4, 5, 6 };

		const hamon::size_t start = 1u;  // 開始位置
		const hamon::size_t length = 3u; // 要素数
		const hamon::size_t stride = 2u; // 何個置きに処理するか
		const hamon::slice sl(start, length, stride);

		static_assert(hamon::is_same<decltype(va[sl]), hamon::slice_array<T>>::value, "");
#if !defined(HAMON_USE_STD_VALARRAY)
		static_assert(noexcept(va[sl]), "");
#endif

		hamon::slice_array<T> result = va[sl];

		result *= hamon::valarray<T>(2, length); // 抽出した要素を書き換える

		// 参照元が書き換わっていることを確認
		VERIFY(va[0] == 1);
		VERIFY(va[1] == 4); // result[0]
		VERIFY(va[2] == 3);
		VERIFY(va[3] == 8); // result[1]
		VERIFY(va[4] == 5);
		VERIFY(va[5] == 12); // result[2]
	}
	{
		T a1[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
		T a2[] = { -1, -2, -3, -4, -5 };
		hamon::valarray<T> v1(a1, sizeof(a1) / sizeof(a1[0]));
		hamon::valarray<T> v2(a2, sizeof(a2) / sizeof(a2[0]));
		v1[hamon::slice(1, 5, 3)] = v2;
		VERIFY(v1.size() == 16);
		VERIFY(v1[0] == 0);
		VERIFY(v1[1] == -1);
		VERIFY(v1[2] == 2);
		VERIFY(v1[3] == 3);
		VERIFY(v1[4] == -2);
		VERIFY(v1[5] == 5);
		VERIFY(v1[6] == 6);
		VERIFY(v1[7] == -3);
		VERIFY(v1[8] == 8);
		VERIFY(v1[9] == 9);
		VERIFY(v1[10] == -4);
		VERIFY(v1[11] == 11);
		VERIFY(v1[12] == 12);
		VERIFY(v1[13] == -5);
		VERIFY(v1[14] == 14);
		VERIFY(v1[15] == 15);
	}
	{
		T a1[] = { 0, 1, 2, 3, 4, 5 };
		hamon::valarray<T> v1(a1, sizeof(a1) / sizeof(a1[0]));
		hamon::valarray<T> v2((v1 + 0)[hamon::slice(0, 3, 2)]);
		VERIFY(v2.size() == 3);
		VERIFY(v2[0] == 0);
		VERIFY(v2[1] == 2);
		VERIFY(v2[2] == 4);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(ValArrayTest, ValarraySubscriptSliceArrayTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<int>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<short>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<char>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<float>()));
}

}	// namespace valarray_subscript_slice_array_test

}	// namespace hamon_valarray_test
