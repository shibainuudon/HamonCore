/**
 *	@file	unit_test_valarray_valarray_ctor_pointer_size.cpp
 *
 *	@brief	ポインターとサイズを引数に取るコンストラクタのテスト
 *
 *	valarray(const T*, size_t);
 */

#include <hamon/valarray/valarray.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_valarray_test
{

namespace valarray_ctor_pointer_size_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	static_assert( hamon::is_constructible<hamon::valarray<T>, const T*, hamon::size_t>::value, "");
	static_assert(!hamon::is_nothrow_constructible<hamon::valarray<T>, const T*, hamon::size_t>::value, "");
	static_assert( hamon::is_implicitly_constructible<hamon::valarray<T>, const T*, hamon::size_t>::value, "");
	const T v[] {1, 2, 3, 4};
	hamon::valarray<T> va(v, hamon::size_t(3));
	VERIFY(va.size() == 3u);
	VERIFY(va[0] == T{1});
	VERIFY(va[1] == T{2});
	VERIFY(va[2] == T{3});

	return true;
}

#undef VERIFY

GTEST_TEST(ValArrayTest, ValarrayCtorPointerSizeTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<int>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<short>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<char>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<float>()));
}

}	// namespace valarray_ctor_pointer_size_test

}	// namespace hamon_valarray_test
