/**
 *	@file	unit_test_valarray_valarray_resize.cpp
 *
 *	@brief	resize のテスト
 *
 *	void resize(size_t sz, T c = T());
 */

#include <hamon/valarray/valarray.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_valarray_test
{

namespace valarray_resize_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	hamon::valarray<T> va{1,2,3,4,5};

	static_assert(hamon::is_same<decltype(va.resize(0u)), void>::value, "");
	static_assert(hamon::is_same<decltype(va.resize(0u, T{})), void>::value, "");
	static_assert(!noexcept(va.resize(0u)), "");
	static_assert(!noexcept(va.resize(0u, T{})), "");

	va.resize(2);
	VERIFY(va.size() == 2u);
	VERIFY(va[0] == T{0});
	VERIFY(va[1] == T{0});

	va.resize(6, T{42});
	VERIFY(va.size() == 6u);
	VERIFY(va[0] == T{42});
	VERIFY(va[1] == T{42});
	VERIFY(va[2] == T{42});
	VERIFY(va[3] == T{42});
	VERIFY(va[4] == T{42});
	VERIFY(va[5] == T{42});

	return true;
}

#undef VERIFY

GTEST_TEST(ValArrayTest, ValarrayResizeTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<int>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<char>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<float>()));
}

}	// namespace valarray_resize_test

}	// namespace hamon_valarray_test
