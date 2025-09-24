/**
 *	@file	unit_test_valarray_valarray_ctor_default.cpp
 *
 *	@brief	デフォルトコンストラクタのテスト
 *
 *	valarray();
 */

#include <hamon/valarray/valarray.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_valarray_test
{

namespace valarray_ctor_default_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	static_assert(hamon::is_default_constructible<hamon::valarray<T>>::value, "");
#if !defined(HAMON_USE_STD_VALARRAY)
	static_assert(hamon::is_nothrow_default_constructible<hamon::valarray<T>>::value, "");
#endif
	static_assert(!hamon::is_trivially_default_constructible<hamon::valarray<T>>::value, "");
	static_assert(hamon::is_implicitly_default_constructible<hamon::valarray<T>>::value, "");

	hamon::valarray<T> v;
	VERIFY(v.size() == 0u);

	return true;
}

struct S
{
	S() { ctor_called = true; }
	static bool ctor_called;
};

bool S::ctor_called = false;

inline bool test2()
{
	hamon::valarray<S> v;
	VERIFY(v.size() == 0);
	VERIFY(!S::ctor_called);

	return true;
}

#undef VERIFY

GTEST_TEST(ValArrayTest, ValarrayCtorDefaultTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<int>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<short>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<char>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<float>()));

	EXPECT_TRUE((test2()));
}

}	// namespace valarray_ctor_default_test

}	// namespace hamon_valarray_test
