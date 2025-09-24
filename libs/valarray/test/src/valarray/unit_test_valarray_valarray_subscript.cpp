/**
 *	@file	unit_test_valarray_valarray_subscript.cpp
 *
 *	@brief	operator[] のテスト
 *
 *	const T&          operator[](size_t) const;
 *	T&                operator[](size_t);
 */

#include <hamon/valarray/valarray.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_valarray_test
{

namespace valarray_subscript_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	// const T&          operator[](size_t) const;
	{
		hamon::valarray<T> const va{1,2,3};

		static_assert(hamon::is_same<decltype(va[0]), T const&>::value, "");
#if !defined(HAMON_USE_STD_VALARRAY)
		static_assert(noexcept(va[0]), "");
#endif

		VERIFY(va[0] == T{1});
		VERIFY(va[1] == T{2});
		VERIFY(va[2] == T{3});
	}

	// T&                operator[](size_t);
	{
		hamon::valarray<T> va{1,2,3};

		static_assert(hamon::is_same<decltype(va[0]), T&>::value, "");
#if !defined(HAMON_USE_STD_VALARRAY)
		static_assert(noexcept(va[0]), "");
#endif

		VERIFY(va[0] == T{1});
		VERIFY(va[1] == T{2});
		VERIFY(va[2] == T{3});

		va[1] = T{10};

		VERIFY(va[0] == T{1});
		VERIFY(va[1] == T{10});
		VERIFY(va[2] == T{3});
	}

	return true;
}

#undef VERIFY

GTEST_TEST(ValArrayTest, ValarraySubscriptTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<int>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<short>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<char>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<float>()));
}

}	// namespace valarray_subscript_test

}	// namespace hamon_valarray_test
