/**
 *	@file	unit_test_valarray_valarray_unary_bit_not.cpp
 *
 *	@brief	operator~ のテスト
 *
 *	valarray operator~() const;
 */

#include <hamon/valarray/valarray.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_valarray_test
{

namespace valarray_unary_bit_not_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	{
		T a[] = { 0,1,2,3,10 };
		hamon::valarray<T> va(a, 5u);

#if !defined(HAMON_USE_STD_VALARRAY)
		static_assert(hamon::is_same<decltype(~va), hamon::valarray<T>>::value, "");
		static_assert(!noexcept(~va), "");
#endif

		hamon::valarray<T> va2 = ~va;
		VERIFY(va2.size() == 5u);
		VERIFY(va2[0] == ~a[0]);
		VERIFY(va2[1] == ~a[1]);
		VERIFY(va2[2] == ~a[2]);
		VERIFY(va2[3] == ~a[3]);
		VERIFY(va2[4] == ~a[4]);
	}
	{
		// Make sure we don't have dangling reference problems with unary expressions
		T array[] = { 1, 2, 3 };
		hamon::valarray<T> a(array, 3);
		hamon::valarray<T> b(array, 3);
		auto c = ~a + b;
		VERIFY(c.size() == 3);
		VERIFY(c[0] == (~1 + 1));
		VERIFY(c[1] == (~2 + 2));
		VERIFY(c[2] == (~3 + 3));
	}

	return true;
}

#undef VERIFY

GTEST_TEST(ValArrayTest, ValarrayUnaryBitNotTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<int>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<char>()));
}

}	// namespace valarray_unary_bit_not_test

}	// namespace hamon_valarray_test
