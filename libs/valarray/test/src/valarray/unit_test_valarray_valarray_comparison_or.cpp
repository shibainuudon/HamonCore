/**
 *	@file	unit_test_valarray_valarray_comparison_or.cpp
 *
 *	@brief	operator+ のテスト
 *
 *	template<class T> valarray<bool> operator||(const valarray<T>&, const valarray<T>&);
 *	template<class T> valarray<bool> operator||(const valarray<T>&, const typename valarray<T>::value_type&);
 *	template<class T> valarray<bool> operator||(const typename valarray<T>::value_type&, const valarray<T>&);
 */

#include <hamon/valarray/valarray.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_valarray_test
{

namespace valarray_comparison_or_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	// template<class T> valarray<bool> operator||(const valarray<T>&, const valarray<T>&);
	{
		T a1[] = { 1,  2,  0,  4,  0 };
		T a2[] = { 6,  7,  0,  9, 10 };
		bool a3[] = { true,  true,  false,  true,  true };
		const unsigned N = 5;
		hamon::valarray<T> v1(a1, N);
		hamon::valarray<T> v2(a2, N);

#if !defined(HAMON_USE_STD_VALARRAY)
		static_assert(hamon::is_same<decltype(v1 || v2), hamon::valarray<bool>>::value, "");
		static_assert(!noexcept(v1 || v2), "");
#endif

		hamon::valarray<bool> v3 = v1 || v2;
		hamon::valarray<bool> v3a = +(v1 || v2);
		VERIFY(v3.size() == N);
		VERIFY(v3a.size() == N);
		for (hamon::size_t i = 0; i < N; ++i)
		{
			VERIFY(v3[i] == a3[i]);
			VERIFY(v3a[i] == a3[i]);
		}
	}

	// template<class T> valarray<bool> operator||(const valarray<T>&, const typename valarray<T>::value_type&);
	{
		T a1[] = { 1,  2,  3,  4,  0 };
		bool a3[] = { true,  true,  true,  true,  true };
		const unsigned N = 5;
		hamon::valarray<T> v1(a1, N);

#if !defined(HAMON_USE_STD_VALARRAY)
		static_assert(hamon::is_same<decltype(v1 || T{}), hamon::valarray<bool>>::value, "");
		static_assert(!noexcept(v1 || T{}), "");
#endif

		hamon::valarray<bool> v3 = v1 || 5;
		hamon::valarray<bool> v3a = +(v1 || 5);
		VERIFY(v3.size() == N);
		VERIFY(v3a.size() == N);
		for (hamon::size_t i = 0; i < N; ++i)
		{
			VERIFY(v3[i] == a3[i]);
			VERIFY(v3a[i] == a3[i]);
		}
	}
	{
		T a1[] = { 1,  2,  3,  4,  0 };
		bool a3[] = { true,  true,  true,  true,  false };
		const unsigned N = 5;
		hamon::valarray<T> v1(a1, N);
		hamon::valarray<bool> v3 = v1 || 0;
		hamon::valarray<bool> v3a = +(v1 || 0);
		VERIFY(v3.size() == N);
		VERIFY(v3a.size() == N);
		for (hamon::size_t i = 0; i < N; ++i)
		{
			VERIFY(v3[i] == a3[i]);
			VERIFY(v3a[i] == a3[i]);
		}
	}

	// template<class T> valarray<bool> operator||(const typename valarray<T>::value_type&, const valarray<T>&);
	{
		T a2[] = { 1,  2,  3,  4,  0 };
		bool a3[] = { true,  true,  true,  true,  true };
		const unsigned N = 5;
		hamon::valarray<T> v2(a2, N);

#if !defined(HAMON_USE_STD_VALARRAY)
		static_assert(hamon::is_same<decltype(T{} || v2), hamon::valarray<bool>>::value, "");
		static_assert(!noexcept(T{} || v2), "");
#endif

		hamon::valarray<bool> v3 = 5 || v2;
		hamon::valarray<bool> v3a = +(5 || v2);
		VERIFY(v3.size() == N);
		VERIFY(v3a.size() == N);
		for (hamon::size_t i = 0; i < N; ++i)
		{
			VERIFY(v3[i] == a3[i]);
			VERIFY(v3a[i] == a3[i]);
		}
	}
	{
		T a2[] = { 1,  2,  3,  4,  0 };
		bool a3[] = { true,  true,  true,  true,  false };
		const unsigned N = 5;
		hamon::valarray<T> v2(a2, N);
		hamon::valarray<bool> v3 = 0 || v2;
		hamon::valarray<bool> v3a = +(0 || v2);
		VERIFY(v3.size() == N);
		VERIFY(v3a.size() == N);
		for (hamon::size_t i = 0; i < N; ++i)
		{
			VERIFY(v3[i] == a3[i]);
			VERIFY(v3a[i] == a3[i]);
		}
	}

	return true;
}

#undef VERIFY

GTEST_TEST(ValArrayTest, ValarrayComparisonOrTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<int>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<char>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<float>()));
}

}	// namespace valarray_comparison_or_test

}	// namespace hamon_valarray_test
