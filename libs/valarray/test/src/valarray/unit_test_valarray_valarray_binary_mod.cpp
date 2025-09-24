/**
 *	@file	unit_test_valarray_valarray_binary_mod.cpp
 *
 *	@brief	operator% のテスト
 *
 *	template<class T> valarray<T> operator%(const valarray<T>&, const valarray<T>&);
 *	template<class T> valarray<T> operator%(const valarray<T>&, const typename valarray<T>::value_type&);
 *	template<class T> valarray<T> operator%(const typename valarray<T>::value_type&, const valarray<T>&);
 */

#include <hamon/valarray/valarray.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_valarray_test
{

namespace valarray_binary_mod_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	// template<class T> valarray<T> operator%(const valarray<T>&, const valarray<T>&);
	{
		T a1[] = { 6,  7,  8,  9, 10 };
		T a2[] = { 1,  2,  3,  4,  5 };
		T a3[] = { 0,  1,  2,  1,  0 };
		const unsigned N = sizeof(a1) / sizeof(a1[0]);
		hamon::valarray<T> v1(a1, N);
		hamon::valarray<T> v2(a2, N);

#if !defined(HAMON_USE_STD_VALARRAY)
		static_assert(hamon::is_same<decltype(v1 % v2), hamon::valarray<T>>::value, "");
		static_assert(!noexcept(v1 % v2), "");
#endif

		hamon::valarray<T> v3 = v1 % v2;
		VERIFY(v1.size() == v2.size());
		VERIFY(v1.size() == v3.size());
		for (hamon::size_t i = 0; i < v1.size(); ++i)
		{
			VERIFY(v3[i] == a3[i]);
		}
	}

	// template<class T> valarray<T> operator%(const valarray<T>&, const typename valarray<T>::value_type&);
	{
		T a1[] = { 1,  2,  3,  4,  5 };
		T a2[] = { 1,  2,  0,  1,  2 };
		const unsigned N = sizeof(a1) / sizeof(a1[0]);
		hamon::valarray<T> v1(a1, N);

#if !defined(HAMON_USE_STD_VALARRAY)
		static_assert(hamon::is_same<decltype(v1 % T{}), hamon::valarray<T>>::value, "");
		static_assert(!noexcept(v1 % T{}), "");
#endif

		hamon::valarray<T> v2 = v1 % T{3};
		VERIFY(v1.size() == v2.size());
		for (hamon::size_t i = 0; i < v2.size(); ++i)
		{
			VERIFY(v2[i] == a2[i]);
		}
	}

	// template<class T> valarray<T> operator%(const typename valarray<T>::value_type&, const valarray<T>&);
	{
		T a1[] = { 1,  2,  3,  4,  5 };
		T a2[] = { 0,  1,  0,  3,  3 };
		const unsigned N = sizeof(a1) / sizeof(a1[0]);
		hamon::valarray<T> v1(a1, N);

#if !defined(HAMON_USE_STD_VALARRAY)
		static_assert(hamon::is_same<decltype(T{} % v1), hamon::valarray<T>>::value, "");
		static_assert(!noexcept(T{} % v1), "");
#endif

		hamon::valarray<T> v2 = T{3} % v1;
		VERIFY(v1.size() == v2.size());
		for (hamon::size_t i = 0; i < v2.size(); ++i)
		{
			VERIFY(v2[i] == a2[i]);
		}
	}

	return true;
}

#undef VERIFY

GTEST_TEST(ValArrayTest, ValarrayBinaryModTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<int>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<short>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<char>()));
}

}	// namespace valarray_binary_mod_test

}	// namespace hamon_valarray_test
