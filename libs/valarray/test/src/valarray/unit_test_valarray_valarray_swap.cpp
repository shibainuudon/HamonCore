/**
 *	@file	unit_test_valarray_valarray_swap.cpp
 *
 *	@brief	swap のテスト
 *
 *	void swap(valarray&) noexcept;
 *
 *	template<class T> void swap(valarray<T>&, valarray<T>&) noexcept;
 */

#include <hamon/valarray/valarray.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_valarray_test
{

namespace valarray_swap_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	hamon::valarray<T> va1{1,2,3};
	hamon::valarray<T> va2{4,5,6,7};

	static_assert(hamon::is_same<decltype(va1.swap(va2)), void>::value, "");
	static_assert(noexcept(va1.swap(va2)), "");

	static_assert(hamon::is_same<decltype(swap(va1, va2)), void>::value, "");
	static_assert(noexcept(swap(va1, va2)), "");

	VERIFY(va1.size() == 3u);
	VERIFY(va1[0] == T{1});
	VERIFY(va1[1] == T{2});
	VERIFY(va1[2] == T{3});
	VERIFY(va2.size() == 4u);
	VERIFY(va2[0] == T{4});
	VERIFY(va2[1] == T{5});
	VERIFY(va2[2] == T{6});
	VERIFY(va2[3] == T{7});

	va1.swap(va2);

	VERIFY(va1.size() == 4u);
	VERIFY(va1[0] == T{4});
	VERIFY(va1[1] == T{5});
	VERIFY(va1[2] == T{6});
	VERIFY(va1[3] == T{7});
	VERIFY(va2.size() == 3u);
	VERIFY(va2[0] == T{1});
	VERIFY(va2[1] == T{2});
	VERIFY(va2[2] == T{3});

	swap(va1, va2);

	VERIFY(va1.size() == 3u);
	VERIFY(va1[0] == T{1});
	VERIFY(va1[1] == T{2});
	VERIFY(va1[2] == T{3});
	VERIFY(va2.size() == 4u);
	VERIFY(va2[0] == T{4});
	VERIFY(va2[1] == T{5});
	VERIFY(va2[2] == T{6});
	VERIFY(va2[3] == T{7});

	return true;
}

#undef VERIFY

GTEST_TEST(ValArrayTest, ValarraySwapTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<int>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<char>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<float>()));
}

}	// namespace valarray_swap_test

}	// namespace hamon_valarray_test
