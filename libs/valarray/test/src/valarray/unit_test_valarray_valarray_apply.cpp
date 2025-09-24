/**
 *	@file	unit_test_valarray_valarray_apply.cpp
 *
 *	@brief	apply のテスト
 *
 *	valarray apply(T func(T)) const;
 *	valarray apply(T func(const T&)) const;
 */

#include <hamon/valarray/valarray.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_valarray_test
{

namespace valarray_apply_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	hamon::valarray<T> const va{1,2,3};

#if !defined(HAMON_USE_STD_VALARRAY)
	auto f1 = [](T t)->T {return t;};
	auto f2 = [](T const& t)->T {return t;};
	static_assert(hamon::is_same<decltype(va.apply(f1)), hamon::valarray<T>>::value, "");
	static_assert(hamon::is_same<decltype(va.apply(f2)), hamon::valarray<T>>::value, "");
	static_assert(!noexcept(va.apply(f1)), "");
	static_assert(!noexcept(va.apply(f2)), "");
#endif

	hamon::valarray<T> va2 = va.apply([](T x){return static_cast<T>(x + 2);});
	VERIFY(va2.size() == 3u);
	VERIFY(va2[0] == T{3});
	VERIFY(va2[1] == T{4});
	VERIFY(va2[2] == T{5});

	hamon::valarray<T> va3 = va.apply([](T const& x){return static_cast<T>(x * 2);});
	VERIFY(va3.size() == 3u);
	VERIFY(va3[0] == T{2});
	VERIFY(va3[1] == T{4});
	VERIFY(va3[2] == T{6});

	return true;
}

#undef VERIFY

GTEST_TEST(ValArrayTest, ValarrayApplyTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<int>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<char>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<float>()));
}

}	// namespace valarray_apply_test

}	// namespace hamon_valarray_test
