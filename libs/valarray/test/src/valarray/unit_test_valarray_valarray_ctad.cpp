/**
 *	@file	unit_test_valarray_valarray_ctad.cpp
 *
 *	@brief	テンプレート引数推論のテスト
 *
 *	template<class T, size_t cnt> valarray(const T(&)[cnt], size_t) -> valarray<T>;
 */

#include <hamon/valarray/valarray.hpp>
#include <hamon/valarray/slice.hpp>
#include <hamon/valarray/gslice.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_valarray_test
{

namespace valarray_ctad_test
{

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
	{
		// From (initializer_list<T>)
		hamon::valarray v = {T{1}, T{2}, T{3}, T{4}, T{5}};
		static_assert(hamon::is_same<decltype(v), hamon::valarray<T>>::value, "");
	}

	{
		// From (const T(&)[N], size_t)
		T a[] = {1, 2, 3, 4, 5};
		hamon::valarray v(a, 5);
		static_assert(hamon::is_same<decltype(v), hamon::valarray<T>>::value, "");
	}

	{
		// From (const T&, size_t)
		T a[] = {1, 2, 3, 4, 5};
		hamon::valarray v(&a[0], 5);
		// Surprising but true.
		static_assert(hamon::is_same<decltype(v), hamon::valarray<T*>>::value, "");
	}

	{
		// From (slice_array<T>)
		hamon::valarray<T> v{1,2,3,4,5};
		hamon::valarray v2 = v[hamon::slice(2, 3, 1)];
		static_assert(hamon::is_same<decltype(v2), hamon::valarray<T>>::value, "");
	}

	{
		// From (gslice_array<T>)
		hamon::valarray<T> v{1,2,3,4,5};
		hamon::valarray v2 = v[hamon::gslice(0, {5}, {1})];
		static_assert(hamon::is_same<decltype(v2), hamon::valarray<T>>::value, "");
	}

	{
		// From (mask_array<T>)
		hamon::valarray<T> v ={ 1, 2, 3, 4, 5};
		hamon::valarray<bool> m = {true, false, true, false, true};
		hamon::valarray v2 = v[m];
		static_assert(hamon::is_same<decltype(v2), hamon::valarray<T>>::value, "");
	}

	{
		// From (indirect_array<T>)
		hamon::valarray<T> v ={1, 2, 3, 4, 5};
		hamon::valarray<hamon::size_t> i = {1, 2, 3};
		hamon::valarray v2 = v[i];
		static_assert(hamon::is_same<decltype(v2), hamon::valarray<T>>::value, "");
	}
#endif

	return true;
}

GTEST_TEST(ValArrayTest, ValarrayCtadTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<int>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<char>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<float>()));
}

}	// namespace valarray_ctad_test

}	// namespace hamon_valarray_test
