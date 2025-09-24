/**
 *	@file	unit_test_valarray_valarray_cshift.cpp
 *
 *	@brief	cshift のテスト
 *
 *	valarray cshift(int) const;
 */

#include <hamon/valarray/valarray.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_valarray_test
{

namespace valarray_cshift_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	{
		hamon::valarray<T> const va{ 1,2,3,4,5 };

#if !defined(HAMON_USE_STD_VALARRAY)
		static_assert(hamon::is_same<decltype(va.cshift(0)), hamon::valarray<T>>::value, "");
		static_assert(!noexcept(va.cshift(0)), "");
#endif

		hamon::valarray<T> va2 = va.cshift(3);
		VERIFY(va2.size() == 5u);
		VERIFY(va2[0] == T{ 4 });
		VERIFY(va2[1] == T{ 5 });
		VERIFY(va2[2] == T{ 1 });
		VERIFY(va2[3] == T{ 2 });
		VERIFY(va2[4] == T{ 3 });

		hamon::valarray<T> va3 = va.cshift(-3);
		VERIFY(va3.size() == 5u);
		VERIFY(va3[0] == T{ 3 });
		VERIFY(va3[1] == T{ 4 });
		VERIFY(va3[2] == T{ 5 });
		VERIFY(va3[3] == T{ 1 });
		VERIFY(va3[4] == T{ 2 });
	}

	{
		T a1[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
		T a2[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
		const unsigned N1 = sizeof(a1) / sizeof(a1[0]);
		hamon::valarray<T> v1(a1, N1);
		hamon::valarray<T> v2 = v1.cshift(0);
		VERIFY(v2.size() == N1);
		for (unsigned i = 0; i < N1; ++i)
		{
			VERIFY(v2[i] == a2[i]);
		}
	}
	{
		T a1[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
		T a2[] = { 4, 5, 6, 7, 8, 9, 10, 1, 2, 3 };
		const unsigned N1 = sizeof(a1) / sizeof(a1[0]);
		hamon::valarray<T> v1(a1, N1);
		hamon::valarray<T> v2 = v1.cshift(3);
		VERIFY(v2.size() == N1);
		for (unsigned i = 0; i < N1; ++i)
		{
			VERIFY(v2[i] == a2[i]);
		}
	}
	{
		T a1[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
		T a2[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
		const unsigned N1 = sizeof(a1) / sizeof(a1[0]);
		hamon::valarray<T> v1(a1, N1);
		hamon::valarray<T> v2 = v1.cshift(10);
		VERIFY(v2.size() == N1);
		for (unsigned i = 0; i < N1; ++i)
		{
			VERIFY(v2[i] == a2[i]);
		}
	}
	{
		T a1[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
		T a2[] = { 8, 9, 10, 1, 2, 3, 4, 5, 6, 7 };
		const unsigned N1 = sizeof(a1) / sizeof(a1[0]);
		hamon::valarray<T> v1(a1, N1);
		hamon::valarray<T> v2 = v1.cshift(17);
		VERIFY(v2.size() == N1);
		for (unsigned i = 0; i < N1; ++i)
		{
			VERIFY(v2[i] == a2[i]);
		}
	}
	{
		T a1[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
		T a2[] = { 8, 9, 10, 1, 2, 3, 4, 5, 6, 7 };
		const unsigned N1 = sizeof(a1) / sizeof(a1[0]);
		hamon::valarray<T> v1(a1, N1);
		hamon::valarray<T> v2 = v1.cshift(-3);
		VERIFY(v2.size() == N1);
		for (unsigned i = 0; i < N1; ++i)
		{
			VERIFY(v2[i] == a2[i]);
		}
	}
	{
		T a1[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
		T a2[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
		const unsigned N1 = sizeof(a1) / sizeof(a1[0]);
		hamon::valarray<T> v1(a1, N1);
		hamon::valarray<T> v2 = v1.cshift(-10);
		VERIFY(v2.size() == N1);
		for (unsigned i = 0; i < N1; ++i)
		{
			VERIFY(v2[i] == a2[i]);
		}
	}
	{
		T a1[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
		T a2[] = { 4, 5, 6, 7, 8, 9, 10, 1, 2, 3 };
		const unsigned N1 = sizeof(a1) / sizeof(a1[0]);
		hamon::valarray<T> v1(a1, N1);
		hamon::valarray<T> v2 = v1.cshift(-17);
		VERIFY(v2.size() == N1);
		for (unsigned i = 0; i < N1; ++i)
		{
			VERIFY(v2[i] == a2[i]);
		}
	}
	{
		const unsigned N1 = 0;
		hamon::valarray<T> v1;
		hamon::valarray<T> v2 = v1.cshift(-17);
		VERIFY(v2.size() == N1);
	}
	{
		T a1[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
		T a2[] = { 8, 10, 12, 14, 16, 18, 20, 2, 4, 6 };
		const unsigned N1 = sizeof(a1) / sizeof(a1[0]);
		hamon::valarray<T> v1(a1, N1);
		hamon::valarray<T> v2 = (v1 + v1).cshift(3);
		VERIFY(v2.size() == N1);
		for (unsigned i = 0; i < N1; ++i)
		{
			VERIFY(v2[i] == a2[i]);
		}
	}
	{
		T a1[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
		T a2[] = { 16, 18, 20, 2, 4, 6, 8, 10, 12, 14 };
		const unsigned N1 = sizeof(a1) / sizeof(a1[0]);
		hamon::valarray<T> v1(a1, N1);
		hamon::valarray<T> v2 = (v1 + v1).cshift(-3);
		VERIFY(v2.size() == N1);
		for (unsigned i = 0; i < N1; ++i)
		{
			VERIFY(v2[i] == a2[i]);
		}
	}

	return true;
}

#undef VERIFY

GTEST_TEST(ValArrayTest, ValarrayCshiftTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<int>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<char>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<float>()));
}

}	// namespace valarray_cshift_test

}	// namespace hamon_valarray_test
