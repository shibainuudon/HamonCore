/**
 *	@file	unit_test_valarray_valarray_subscript_indirect_array.cpp
 *
 *	@brief	operator[] のテスト
 *
 *	valarray          operator[](const valarray<size_t>&) const;
 *	indirect_array<T> operator[](const valarray<size_t>&);
 */

#include <hamon/valarray/valarray.hpp>
#include <hamon/valarray/indirect_array.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_valarray_test
{

namespace valarray_subscript_indirect_array_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	// valarray          operator[](const valarray<size_t>&) const;
	{
		const hamon::valarray<T> va = { 1, 2, 3, 4, 5 };
		const hamon::valarray<hamon::size_t> mask = { 0, 2, 4 };

#if !defined(HAMON_USE_STD_VALARRAY)
		static_assert(hamon::is_same<decltype(va[mask]), hamon::valarray<T>>::value, "");
		static_assert(!noexcept(va[mask]), "");
#endif

		hamon::valarray<T> result = va[mask];

		VERIFY(result.size() == 3);
		VERIFY(result[0] == 1);
		VERIFY(result[1] == 3);
		VERIFY(result[2] == 5);
	}
	{
		T a[] = { 0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11,
				   12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23,
				   24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35,
				   36, 37, 38, 39, 40 };
		const hamon::size_t N1 = sizeof(a) / sizeof(a[0]);
		hamon::size_t s[] = { 3,  4,  5,  7,  8,  9, 11, 12, 13, 15, 16, 17,
						   22, 23, 24, 26, 27, 28, 30, 31, 32, 34, 35, 36 };
		const hamon::size_t S = sizeof(s) / sizeof(s[0]);
		const hamon::valarray<T> v1(a, N1);
		hamon::valarray<hamon::size_t> ia(s, S);
		hamon::valarray<T> v = v1[ia];
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
		T raw_data[] = { 0,1,2,3,4,5,6,7,8,9 };
		hamon::size_t idx_data[] = { 0,2,4,6,8 };
		const hamon::valarray<T> data(raw_data, sizeof(raw_data) / sizeof(raw_data[0]));
		hamon::valarray<hamon::size_t> idx(idx_data, sizeof(idx_data) / sizeof(idx_data[0]));
		hamon::valarray<T> result = (data + 0)[idx];
		VERIFY(result.size() == 5);
		VERIFY(result[0] == data[idx[0]]);
		VERIFY(result[1] == data[idx[1]]);
		VERIFY(result[2] == data[idx[2]]);
		VERIFY(result[3] == data[idx[3]]);
		VERIFY(result[4] == data[idx[4]]);
	}

	// indirect_array<T> operator[](const valarray<size_t>&);
	{
		hamon::valarray<T> va = { 1, 2, 3, 4, 5 };
		const hamon::valarray<hamon::size_t> mask = { 0, 2, 4 };

		static_assert(hamon::is_same<decltype(va[mask]), hamon::indirect_array<T>>::value, "");
#if !defined(HAMON_USE_STD_VALARRAY)
		static_assert(!noexcept(va[mask]), "");
#endif

		hamon::indirect_array<T> result = va[mask];

		// 抽出した要素を99で埋める
		result = 99;

		// 参照元が書き換わっていることを確認する
		VERIFY(va[0] == 99);
		VERIFY(va[1] == 2);
		VERIFY(va[2] == 99);
		VERIFY(va[3] == 4);
		VERIFY(va[0] == 99);
	}
	{
		T a[] = { 0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11,
				   12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23,
				   24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35,
				   36, 37, 38, 39, 40 };
		const hamon::size_t N1 = sizeof(a) / sizeof(a[0]);
		hamon::size_t s[] = { 3,  4,  5,  7,  8,  9, 11, 12, 13, 15, 16, 17,
						   22, 23, 24, 26, 27, 28, 30, 31, 32, 34, 35, 36 };
		const hamon::size_t S = sizeof(s) / sizeof(s[0]);
		hamon::valarray<T> v1(a, N1);
		hamon::valarray<hamon::size_t> ia(s, S);
		hamon::valarray<T> v(24);
		v = v1[ia];
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
		T raw_data[] = { 0,1,2,3,4,5,6,7,8,9 };
		hamon::size_t idx_data[] = { 0,2,4,6,8 };
		hamon::valarray<T> data(raw_data, sizeof(raw_data) / sizeof(raw_data[0]));
		hamon::valarray<hamon::size_t> idx(idx_data, sizeof(idx_data) / sizeof(idx_data[0]));
		hamon::valarray<T> result = (data + 0)[idx];
		VERIFY(result.size() == 5);
		VERIFY(result[0] == data[idx[0]]);
		VERIFY(result[1] == data[idx[1]]);
		VERIFY(result[2] == data[idx[2]]);
		VERIFY(result[3] == data[idx[3]]);
		VERIFY(result[4] == data[idx[4]]);
	}

	return true;
	}

#undef VERIFY

GTEST_TEST(ValArrayTest, ValarraySubscriptIndirectArrayTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<int>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<short>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<char>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<float>()));
}

}	// namespace valarray_subscript_indirect_array_test

}	// namespace hamon_valarray_test
