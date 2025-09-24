/**
 *	@file	unit_test_valarray_valarray_ctor_initializer_list.cpp
 *
 *	@brief	initializer_listを引数に取るコンストラクタのテスト
 *
 *	valarray(initializer_list<T>);
 */

#include <hamon/valarray/valarray.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include <initializer_list>
#include "constexpr_test.hpp"

namespace hamon_valarray_test
{

namespace valarray_ctor_initializer_list_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	static_assert( hamon::is_constructible<hamon::valarray<T>, std::initializer_list<T>>::value, "");
	static_assert(!hamon::is_nothrow_constructible<hamon::valarray<T>, std::initializer_list<T>>::value, "");
	static_assert( hamon::is_implicitly_constructible<hamon::valarray<T>, std::initializer_list<T>>::value, "");
	hamon::valarray<T> va = {1,2,3,4};
	VERIFY(va.size() == 4u);
	VERIFY(va[0] == T{1});
	VERIFY(va[1] == T{2});
	VERIFY(va[2] == T{3});
	VERIFY(va[3] == T{4});

	return true;
}

#undef VERIFY

GTEST_TEST(ValArrayTest, ValarrayCtorInitializerListTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<int>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<short>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<char>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<float>()));
}

}	// namespace valarray_ctor_initializer_list_test

}	// namespace hamon_valarray_test
