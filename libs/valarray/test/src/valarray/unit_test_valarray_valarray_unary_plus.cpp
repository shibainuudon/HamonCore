/**
 *	@file	unit_test_valarray_valarray_unary_plus.cpp
 *
 *	@brief	operator+ のテスト
 *
 *	valarray operator+() const;
 */

#include <hamon/valarray/valarray.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_valarray_test
{

namespace valarray_unary_plus_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	{
		hamon::valarray<T> a = { 1, -2, 3 };

#if !defined(HAMON_USE_STD_VALARRAY)
		static_assert(hamon::is_same<decltype(+a), hamon::valarray<T>>::value, "");
		static_assert(!noexcept(+a), "");
#endif

		hamon::valarray<T> result = +a;
		VERIFY(result.size() == 3u);
		VERIFY(result[0] == 1);
		VERIFY(result[1] == -2);
		VERIFY(result[2] == 3);
	}
	{
		// Make sure we don't have dangling reference problems with unary expressions
		T array[] = { 1, 2, 3 };
		hamon::valarray<T> a(array, 3);
		hamon::valarray<T> b(array, 3);
		auto c = +a * b;
		VERIFY(c.size() == 3);
		VERIFY(c[0] == 1);
		VERIFY(c[1] == 4);
		VERIFY(c[2] == 9);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(ValArrayTest, ValarrayUnaryPlusTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<int>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<char>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<float>()));
}

}	// namespace valarray_unary_plus_test

}	// namespace hamon_valarray_test
