/**
 *	@file	unit_test_valarray_valarray_subscript_mask_array.cpp
 *
 *	@brief	operator[] のテスト
 *
 *	valarray          operator[](const valarray<bool>&) const;
 *	mask_array<T>     operator[](const valarray<bool>&);
 */

#include <hamon/valarray/valarray.hpp>
#include <hamon/valarray/mask_array.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_valarray_test
{

namespace valarray_subscript_mask_array_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	// valarray          operator[](const valarray<bool>&) const;
	{
		const hamon::valarray<T> va = { 1, 2, 3, 4, 5 };
		const hamon::valarray<bool> mask = { true, false, true, false, true };

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
		T a1[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
		const hamon::size_t N1 = sizeof(a1) / sizeof(a1[0]);
		bool b[N1] = { true,  false, false, true,  true,  false,
					  false, true,  false, false, false, true };
		hamon::valarray<T> v1(a1, N1);
		hamon::valarray<bool> vb(b, N1);
		hamon::valarray<T> v2(v1[vb]);
		VERIFY(v2.size() == 5);
		VERIFY(v2[0] == 0);
		VERIFY(v2[1] == 3);
		VERIFY(v2[2] == 4);
		VERIFY(v2[3] == 7);
		VERIFY(v2[4] == 11);
	}
	{
		T a1[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
		const hamon::size_t N1 = sizeof(a1) / sizeof(a1[0]);
		bool b[N1] = { true,  false, false, true,  true,  false,
					  false, true,  false, false, false, true };
		hamon::valarray<T> v1(a1, N1);
		hamon::valarray<bool> vb(b, N1);
		hamon::valarray<T> v2((v1 - 1)[vb]);
		VERIFY(v2.size() == 5);
		VERIFY(v2[0] == -1);
		VERIFY(v2[1] == 2);
		VERIFY(v2[2] == 3);
		VERIFY(v2[3] == 6);
		VERIFY(v2[4] == 10);
	}

	// mask_array<T>     operator[](const valarray<bool>&);
	{
		hamon::valarray<T> va = { 1, 2, 3, 4, 5 };
		const hamon::valarray<bool> mask = { true, false, true, false, true };

		static_assert(hamon::is_same<decltype(va[mask]), hamon::mask_array<T>>::value, "");
#if !defined(HAMON_USE_STD_VALARRAY)
		static_assert(!noexcept(va[mask]), "");
#endif

		hamon::mask_array<T> result = va[mask];

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
		T a1[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
		const hamon::size_t N1 = sizeof(a1) / sizeof(a1[0]);
		bool b[N1] = { true,  false, false, true,  true,  false,
					  false, true,  false, false, false, true };
		hamon::valarray<T> v1(a1, N1);
		hamon::valarray<bool> vb(b, N1);
		hamon::valarray<T> v2(5);
		v2 = v1[vb];
		VERIFY(v2.size() == 5);
		VERIFY(v2[0] == 0);
		VERIFY(v2[1] == 3);
		VERIFY(v2[2] == 4);
		VERIFY(v2[3] == 7);
		VERIFY(v2[4] == 11);
	}
	{
		T a1[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
		const hamon::size_t N1 = sizeof(a1) / sizeof(a1[0]);
		bool b[N1] = { true,  false, false, true,  true,  false,
					  false, true,  false, false, false, true };
		hamon::valarray<T> v1(a1, N1);
		hamon::valarray<bool> vb(b, N1);
		hamon::valarray<T> v2(5);
		v2 = (v1 + 0)[vb];
		VERIFY(v2.size() == 5);
		VERIFY(v2[0] == 0);
		VERIFY(v2[1] == 3);
		VERIFY(v2[2] == 4);
		VERIFY(v2[3] == 7);
		VERIFY(v2[4] == 11);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(ValArrayTest, ValarraySubscriptMaskArrayTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<int>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<short>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<char>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<float>()));
}

}	// namespace valarray_subscript_mask_array_test

}	// namespace hamon_valarray_test
